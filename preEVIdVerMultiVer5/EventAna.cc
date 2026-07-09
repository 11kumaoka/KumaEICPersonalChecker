#include "EventAna.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <unordered_map>

#include <TVector3.h>

namespace {
    using RawHitKey = std::uint64_t;
    constexpr Int_t kEtaPhiBins = 10;
    constexpr Double_t kPi = 3.14159;
    using EtaPhiGrid = std::array<std::array<Int_t, kEtaPhiBins>, kEtaPhiBins>;

    enum TrkCollectionIndex : size_t {
        kTrkSiBarrelVertex = 0,
        kTrkSiBarrel = 1,
        kTrkSiEndcap = 2,
        kTrkMPGDBarrel = 3,
        kTrkOuterMPGDBarrel = 4,
        kTrkBackwardMPGD = 5,
        kTrkForwardMPGD = 6,
        kTrkTOFBarrel = 7,
        kTrkTOFEndcap = 8,
        kTrkB0 = 9
    };

    enum kCalRecCollections : size_t {
        kCalB0ECal = 0,
        kCalBarrelImg = 1,
        kCalBarrelScifi = 2,
        kCalEndcapN = 3,
        kCalEndcapP = 4,
        kCalZDC = 5,
        kCalLumi = 6
    };

    struct HitScanState {
        size_t nextHit = 0;
        bool done = false;
    };

    template <typename ObjectID>
    RawHitKey makeRawHitKey(const ObjectID& id) {
        return (static_cast<RawHitKey>(static_cast<std::uint32_t>(id.collectionID)) << 32)
             | static_cast<std::uint32_t>(id.index);
    }

    Int_t trackerRepDetId(size_t iDet) {
        if(iDet > 9) return 7; // FarForwardMT
        if(iDet > 8) return 6; // B0
        if(iDet > 7) return 5; // ETOF
        if(iDet > 6) return 4; // BTOF
        if(iDet > 4) return 3; // EMPGD
        if(iDet > 2) return 2; // BMPGD
        if(iDet > 1) return 1; // ESi
        return 0;              // BSi
    }

    Int_t physKindId(Int_t generatorStatus) {
        return std::clamp(generatorStatus / 1000 - 1, 0, 5);
    }

    Int_t biPhysId(Int_t generatorStatus) {
        return generatorStatus < 1999 ? 0 : 1;
    }

    bool isValidEtaPhiBin(Int_t etaBin, Int_t phiBin) {
        return 0 <= etaBin && etaBin < kEtaPhiBins && 0 <= phiBin && phiBin < kEtaPhiBins;
    }

    bool isHitInTimeSlice(Double_t hitTime, Double_t timeResolution, Double_t timeSliceStart, Double_t timeSliceEnd) {
        return !(hitTime + timeResolution < timeSliceStart || hitTime - timeResolution > timeSliceEnd);
    }

    std::pair<Int_t, Int_t> etaPhiBins(Double_t hitEta, Double_t hitPhi,
                                       Double_t etaMin, Double_t etaMax, Int_t bShift) {
        const Double_t etaBinWidth = (etaMax - etaMin) / kEtaPhiBins;
        const Double_t phiMin = -kPi;
        const Double_t phiMax = kPi;
        const Double_t phiBinWidth = (phiMax - phiMin) / kEtaPhiBins;

        const Double_t halfEtaBin = 0.5 * etaBinWidth * bShift;
        const Double_t halfPhiBin = 0.5 * phiBinWidth * bShift;
        const Int_t etaBin = static_cast<Int_t>((hitEta - etaMin - halfEtaBin) / etaBinWidth);
        const Int_t phiBin = static_cast<Int_t>((hitPhi - phiMin - halfPhiBin) / phiBinWidth);

        return {etaBin, phiBin};
    }

    TVector3 hitPosition(const SimTrackerHitKuma& hits, size_t iHit) {
        return TVector3(hits.getPosiX(iHit), hits.getPosiY(iHit), hits.getPosiZ(iHit));
    }

    template <typename BinFunc>
    void fillEtaPhiGrids(const SimTrackerHitKuma& hits, HitScanState& state,
                         Double_t timeResolution, Double_t timeSliceStart, Double_t timeSliceEnd,
                         EtaPhiGrid& grid0, EtaPhiGrid& gridShifted, BinFunc binFunc) {
        if(state.done) return;

        const size_t hitCount = hits.getHitSize();
        for(size_t iHit = state.nextHit; iHit < hitCount; ++iHit) {
            const Double_t hitT = hits.getTime(iHit);
            if(hitT - timeResolution > timeSliceEnd) {
                state.nextHit = iHit;
                return;
            }
            if(!isHitInTimeSlice(hitT, timeResolution, timeSliceStart, timeSliceEnd)) continue;

            const TVector3 hitPos = hitPosition(hits, iHit);
            const auto [eta0, phi0] = binFunc(hitPos.Eta(), hitPos.Phi(), 0);
            const auto [eta1, phi1] = binFunc(hitPos.Eta(), hitPos.Phi(), 1);

            if(isValidEtaPhiBin(eta0, phi0)) grid0[eta0][phi0]++;
            if(isValidEtaPhiBin(eta1, phi1)) gridShifted[eta1][phi1]++;
        }

        state.nextHit = hitCount;
        state.done = true;
    }

    template <typename BinFunc>
    size_t countEtaPhiMatches(const SimTrackerHitKuma& hits, HitScanState& state,
                              Double_t timeResolution, Double_t timeSliceStart, Double_t timeSliceEnd,
                              const EtaPhiGrid& grid0, const EtaPhiGrid& gridShifted, Int_t requiredGridCount,
                              BinFunc binFunc) {
        if(state.done) return 0;

        size_t matches = 0;
        const size_t hitCount = hits.getHitSize();
        for(size_t iHit = state.nextHit; iHit < hitCount; ++iHit) {
            const Double_t hitT = hits.getTime(iHit);
            if(hitT - timeResolution > timeSliceEnd) {
                state.nextHit = iHit;
                return matches;
            }
            if(!isHitInTimeSlice(hitT, timeResolution, timeSliceStart, timeSliceEnd)) continue;

            const TVector3 hitPos = hitPosition(hits, iHit);
            const auto [eta0, phi0] = binFunc(hitPos.Eta(), hitPos.Phi(), 0);
            const auto [eta1, phi1] = binFunc(hitPos.Eta(), hitPos.Phi(), 1);

            if((isValidEtaPhiBin(eta0, phi0) && grid0[eta0][phi0] >= requiredGridCount) ||
               (isValidEtaPhiBin(eta1, phi1) && gridShifted[eta1][phi1] >= requiredGridCount)) {
                matches++;
            }
        }

        state.nextHit = hitCount;
        state.done = true;
        return matches;
    }

    size_t countGridCellsWithMultiplicity(const EtaPhiGrid& grid0, const EtaPhiGrid& gridShifted, Int_t threshold) {
        size_t count = 0;
        for(size_t iEta = 0; iEta < kEtaPhiBins; ++iEta) {
            for(size_t iPhi = 0; iPhi < kEtaPhiBins; ++iPhi) {
                if(grid0[iEta][iPhi] >= threshold || gridShifted[iEta][iPhi] >= threshold) count++;
            }
        }
        return count;
    }

    size_t countTimedHits(const SimTrackerHitKuma& hits, HitScanState& state,
                          Double_t timeResolution, Double_t timeSliceStart, Double_t timeSliceEnd) {
        if(state.done) return 0;

        size_t count = 0;
        const size_t hitCount = hits.getHitSize();
        for(size_t iHit = state.nextHit; iHit < hitCount; ++iHit) {
            const Double_t hitT = hits.getTime(iHit);
            if(hitT - timeResolution > timeSliceEnd) {
                state.nextHit = iHit;
                return count;
            }
            if(isHitInTimeSlice(hitT, timeResolution, timeSliceStart, timeSliceEnd)) count++;
        }

        state.nextHit = hitCount;
        state.done = true;
        return count;
    }

    template <typename AssociationCollection>
    std::unordered_multimap<RawHitKey, size_t> makeAssociationIndex(const AssociationCollection& associations) {
        std::unordered_multimap<RawHitKey, size_t> index;
        index.reserve(associations.size());
        for(size_t iAssoc = 0; iAssoc < associations.size(); ++iAssoc) {
            index.emplace(makeRawHitKey(associations.at(iAssoc).getRawHit().getObjectID()), iAssoc);
        }
        return index;
    }
}

EventAna::EventAna(const std::string& inputFile, const std::string& outputFile) : 
    m_iFileName(inputFile), m_oFileName(outputFile)
{
    TH1::AddDirectory(kFALSE);
    m_reader.openFile(m_iFileName);
}


void EventAna::EventLoop() {
    OFileInit();
    auto nEvents = m_reader.getEntries("events");
    const bool bTargetEV = false;
    m_vTargetEvents = {};

    // 3, 7, 10, 11, 15, 16, 19, 23

    // 21, 53, 55, 61, 76, 128, 135, 139, 142, 159, 169, 174, 198, 205, 210, 227, 231, 237, 241, 249, 269, 271, 273, 275, 276, 281, 284, 287, 297, 317, 320, 355, 359, 360, 380, 389, 434, 443, 447, 465, 479, 506, 521, 526, 541, 546, 548, 551, 564, 598, 605, 614, 623, 625, 636, 642, 665, 669, 670, 720, 728, 742, 743, 744, 746, 754, 759, 783, 795, 797, 813, 814, 816, 820, 821, 826, 856, 863, 876, 877, 879, 888, 897, 903, 919, 938, 959, 961, 963, 969, 988, 991, 993

    nEvents = 1000;
    // nEvents = 10;
    if(bTargetEV) nEvents = m_vTargetEvents.size();

    std::cout << "Number of events = " << nEvents << std::endl;

    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        unsigned tempIEvent = iEvent;
        if(bTargetEV) iEvent =  m_vTargetEvents.at(iEvent);
        m_pubEvNum = iEvent;

        if(iEvent%10==0) std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        const Double_t physCollTime = FindPhysCollTime(frame);
        
        m_trkDetsHits = LoadTrackerHitsFromFrame(frame);
        m_calDetsHits = LoadCalHitsFromFrame(frame);

        preEventIDVer5(frame, physCollTime);

        ResetValuesForEachEvent();

        iEvent = tempIEvent;
    }

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hTrkRecEDep[iTrkDet][iPKind]->Scale(1./nEvents);
        }
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrkTimeDist[iTrkDet][iPKind]->Scale(1./nEvents);
            // Int_t totCount = m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Integral();
            // m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Scale(1./totCount);
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Scale(1./nEvents);
        }
    }
    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalRecEDep[iCalRec][iPKind]->Scale(1./nEvents);
        }
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hCalRecTimeDist[iCalRec][iPKind]->Scale(1./nEvents);
            m_hCalRecNumOfHitsInTS[iCalRec][iPKind]->Scale(1./nEvents);
        }
    }

    Double_t TrigRate_Phys = m_numOfPhysTrig / (1.0*nEvents);
    Double_t TrigRate_Fake = m_numOfFakeTrig / (1.0*nEvents);
    Double_t numOfTS = m_timeframe_width / m_timesplit_width;
    TrigRate_Fake *= (numOfTS - 1);

    EditHists();
    OFileWrite();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;
    
}

Double_t EventAna::FindPhysCollTime(const podio::Frame& frame){
    const auto& mcP = frame.get<edm4hep::MCParticleCollection>("MCParticles");

    Double_t vtxT = -99999.;
    for(size_t iMcP = 0; iMcP < mcP.size(); iMcP++){
        // if(mcP.at(iMcP).getGeneratorStatus() != 61) continue;
        if(mcP.at(iMcP).getGeneratorStatus() == 1){
        // if(mcP.at(iMcP).getParents_begin() == 0){
            vtxT = mcP.at(iMcP).getTime();
            break;
        }
        
    }
    return vtxT;
}

std::pair<Int_t, Int_t> EventAna::backEndEtaPhiBins(Double_t hitEta, Double_t hitPhi, Int_t bShift) {
    // MPGD backward Endcap range −3.6 < eta < −1.72, +5%: −3.78 < eta < −1.634
    const Double_t etaMin = -3.78;
    const Double_t etaMax = -1.634;
    return etaPhiBins(hitEta, hitPhi, etaMin, etaMax, bShift);
}

std::pair<Int_t, Int_t> EventAna::barrelEtaPhiBins(Double_t hitEta, Double_t hitPhi, Int_t bShift) {
    // MPGD barrel In range -1.49 < eta < 1.722, +5%: -1.56 < eta < 1.81
    // MPGD barrel Out range -1.56 < eta < 1.61, +5%: -1.64 < eta < 1.70
    // TOF barrel range -1.39 < eta < 1.39, +5%: -1.46 < eta < 1.46
    // ECal barrel range -1.71 < eta < 1.31, +5%: -1.80 < eta < 1.38
    // => -1.80< eta < 1.81
    const Double_t etaMin = -1.80;
    const Double_t etaMax = 1.81;
    return etaPhiBins(hitEta, hitPhi, etaMin, etaMax, bShift);
}

std::pair<Int_t, Int_t> EventAna::forwardEndEtaPhiBins(Double_t hitEta, Double_t hitPhi, Int_t bShift) {
    // MPGD forward Endcap range 2.0 < eta < 3.35, +5%: 1.90 < eta < 3.52
    // TOF forward Endcap range 1.86 < eta < 3.85, +5%: 1.77 < eta < 4.04
    // ECal forward Endcap range 1.4 < eta < 3.5, +5%: 1.33 < eta < 3.68
    const Double_t etaMin = 1.77;
    const Double_t etaMax = 4.04;
    return etaPhiBins(hitEta, hitPhi, etaMin, etaMax, bShift);
}



void EventAna::preEventIDVer5(const podio::Frame& frame, Double_t vtxTime){
    (void)frame;
    (void)vtxTime;

    size_t iTimeSlice = 0;

    const auto& recHitsMPGDBackEnd = m_trkDetsHits.at(kTrkBackwardMPGD);
    const auto& recHitsECalBackEnd = m_calDetsHits.at(kCalEndcapN);
    
    const auto& recHitsMPGDBarrelIn = m_trkDetsHits.at(kTrkMPGDBarrel);
    const auto& recHitsMPGDBarrelOut = m_trkDetsHits.at(kTrkOuterMPGDBarrel);
    const auto& recHitsTOFBarrel = m_trkDetsHits.at(kTrkTOFBarrel);
    const auto& recHitsECalBarrel = m_calDetsHits.at(kCalBarrelScifi);

    const auto& recHitsMPGDForwardEnd = m_trkDetsHits.at(kTrkForwardMPGD);
    const auto& recHitsTOFForwardEnd = m_trkDetsHits.at(kTrkTOFEndcap);
    const auto& recHitsECalForwardEnd = m_calDetsHits.at(kCalEndcapP);

    const auto& recHitsB0Trk = m_trkDetsHits.at(kTrkB0);

    const auto& recHitsZDCECal = m_calDetsHits.at(kCalZDC);

    std::array<HitScanState, InputDataConfig::kTrkRecCollections.size()> trkScanStates;
    std::array<HitScanState, InputDataConfig::kCalRecCollections.size()> calScanStates;

    const auto backEndBins = [this](Double_t eta, Double_t phi, Int_t shift) {
        return backEndEtaPhiBins(eta, phi, shift);
    };
    const auto barrelBins = [this](Double_t eta, Double_t phi, Int_t shift) {
        return barrelEtaPhiBins(eta, phi, shift);
    };
    const auto forwardEndBins = [this](Double_t eta, Double_t phi, Int_t shift) {
        return forwardEndEtaPhiBins(eta, phi, shift);
    };

    

    while(true){
        const Double_t tsTimeS = iTimeSlice * m_timesplit_width;
        const Double_t tsTimeE = (iTimeSlice + 1) * m_timesplit_width;
        if(tsTimeE > m_timeframe_width) break;
        iTimeSlice++;
        
        const Double_t margin = 100.; // ns
        bool bBkgTS = true;
        if(vtxTime >= tsTimeS && vtxTime < tsTimeE) bBkgTS = false;
        if(bBkgTS && (std::abs(vtxTime - tsTimeS) < margin && std::abs(vtxTime - tsTimeE) < margin)) continue;// skip the time slice if the vertex time is within 100 ns of the time slice boundaries;

        // if(bBkgTS) continue;
        // std::cout << "sssssssss MPGD hit Cheeeeeeeeeeeeeeeeeeck" << std::endl;
        EtaPhiGrid backEndGridTest0 = {};
        EtaPhiGrid backEndGridShiftedTest0 = {};
 
        // Int_t numOfECalHitTrk[10][10] = {};
        // Double_t eOfECalHitTrk[10][10] = {};
        // Int_t numOfECalHitCal[10][10] = {};
        // Double_t eOfECalHitCal[10][10] = {};
        // for(size_t iTrkHit = 0; iTrkHit < recHitsMPGDBarrelIn.getHitSize(); ++iTrkHit){
        //         const Double_t hitT = recHitsMPGDBarrelIn.getTime(iTrkHit);
        //     if(hitT + timeResolution_MPGD < tsTimeS || hitT - timeResolution_MPGD > tsTimeE) continue;
        //     const TVector3 hitPos = hitPosition(recHitsMPGDBarrelIn, iTrkHit);
        //     const auto [eta0, phi0] = barrelBins(hitPos.Eta(), hitPos.Phi(), 0);
        //     const auto [eta1, phi1] = barrelBins(hitPos.Eta(), hitPos.Phi(), 1);
        //     if(isValidEtaPhiBin(eta0, phi0)) numOfECalHitTrk[eta0][phi0]++;
        //     if(isValidEtaPhiBin(eta1, phi1)) numOfECalHitTrk[eta1][phi1]++;
        // }
        // for(size_t iTrkHit = 0; iTrkHit < recHitsMPGDBarrelOut.getHitSize(); ++iTrkHit){
        //         const Double_t hitT = recHitsMPGDBarrelOut.getTime(iTrkHit);
        //     if(hitT + timeResolution_MPGD < tsTimeS || hitT - timeResolution_MPGD > tsTimeE) continue;
        //     const TVector3 hitPos = hitPosition(recHitsMPGDBarrelOut, iTrkHit);
        //     const auto [eta0, phi0] = barrelBins(hitPos.Eta(), hitPos.Phi(), 0);
        //     const auto [eta1, phi1] = barrelBins(hitPos.Eta(), hitPos.Phi(), 1);
        //     if(isValidEtaPhiBin(eta0, phi0)) numOfECalHitTrk[eta0][phi0]++;
        //     if(isValidEtaPhiBin(eta1, phi1)) numOfECalHitTrk[eta1][phi1]++;
        // }
        // for(size_t iTrkHit = 0; iTrkHit < recHitsTOFBarrel.getHitSize(); ++iTrkHit){
        //         const Double_t hitT = recHitsTOFBarrel.getTime(iTrkHit);
        //     if(hitT + timeResolution_ACLGad < tsTimeS || hitT - timeResolution_ACLGad > tsTimeE) continue;
        //     const TVector3 hitPos = hitPosition(recHitsTOFBarrel, iTrkHit);
        //     const auto [eta0, phi0] = barrelBins(hitPos.Eta(), hitPos.Phi(), 0);
        //     const auto [eta1, phi1] = barrelBins(hitPos.Eta(), hitPos.Phi(), 1);
        //     if(isValidEtaPhiBin(eta0, phi0)) numOfECalHitTrk[eta0][phi0]++;
        //     if(isValidEtaPhiBin(eta1, phi1)) numOfECalHitTrk[eta1][phi1]++;
        // }
        // for(size_t iECal_BE = 0; iECal_BE < recHitsECalBarrel.getHitSize(); ++iECal_BE){
        //         const Double_t hitT = recHitsECalBarrel.getTime(iECal_BE);
        //     if(hitT + timeResolution_EMCal < tsTimeS || hitT - timeResolution_EMCal > tsTimeE) continue;
        //     const TVector3 hitPos = hitPosition(recHitsECalBarrel, iECal_BE);
        //     const auto [eta0, phi0] = barrelBins(hitPos.Eta(), hitPos.Phi(), 0);
        //     const auto [eta1, phi1] = barrelBins(hitPos.Eta(), hitPos.Phi(), 1);

        //     // std::cout << "Time Slice:" << iTimeSlice << " :: ECal ZDC hit: eta = " << hitPos.Eta() << ", phi = " << hitPos.Phi() << ", (eta0:phi0) = (" << eta0 << ":" << phi0 << "), (eta1:phi1) = (" << eta1 << ":" << phi1 << ")" << std::endl;
        //     if(isValidEtaPhiBin(eta0, phi0) && numOfECalHitTrk[eta0][phi0] > 0) {
        //         numOfECalHitCal[eta0][phi0]++;
        //         eOfECalHitCal[eta0][phi0] += recHitsECalBarrel.getEDep(iECal_BE);
        //     }
        // }
        // for(size_t iEtaBin = 0; iEtaBin < kEtaPhiBins; ++iEtaBin){
        //     for(size_t iPhiBin = 0; iPhiBin < kEtaPhiBins; ++iPhiBin){
        //         if(numOfECalHitCal[iEtaBin][iPhiBin] < 1) continue;
        //         std::cout << "TF:" << m_pubEvNum << ", TS:" << iTimeSlice << " :: ECal Barrel hit in tower: etaBin = " << iEtaBin << ", phiBin = " << iPhiBin << ", numOfHits = " << numOfECalHitCal[iEtaBin][iPhiBin] << ", totalEDep = " << eOfECalHitCal[iEtaBin][iPhiBin] << std::endl;
        //         m_hECalBarrelNumOfHitsInTower[bBkgTS]->Fill(numOfECalHitCal[iEtaBin][iPhiBin]);
        //         m_hECalBarrelNumOfHitsTimesEInTower[bBkgTS]->Fill(eOfECalHitCal[iEtaBin][iPhiBin]);
        //     }
        // }

        // Int_t tempNumOfZDC_ECalHit = 0;
        // Double_t tempEDepOfZDC_ECalHit = 0.0;
        // for(size_t iECal_BE = 0; iECal_BE < recHitsZDCECal.getHitSize(); ++iECal_BE){
        //     const Double_t hitT = recHitsZDCECal.getTime(iECal_BE);
        //     if(hitT + timeResolution_EMCal < tsTimeS || hitT - timeResolution_EMCal > tsTimeE) continue;
        //     tempNumOfZDC_ECalHit++;
        //     tempEDepOfZDC_ECalHit += recHitsZDCECal.getEDep(iECal_BE);
        // }
        // if(tempNumOfZDC_ECalHit > 0) std::cout << "TF:" << m_pubEvNum << ", TS:" << iTimeSlice << " :: ECal ZDC hit in tower: numOfHits = " << tempNumOfZDC_ECalHit << ", totalEDep = " << tempEDepOfZDC_ECalHit << std::endl;
        // m_hECalBarrelNumOfHitsInTower[bBkgTS]->Fill(tempNumOfZDC_ECalHit);
        // m_hECalBarrelNumOfHitsTimesEInTower[bBkgTS]->Fill(tempEDepOfZDC_ECalHit);
        // std::cout << "eeeeeeeee MPGD hit Cheeeeeeeeeeeeeeeeeeck" << std::endl;


        std::array<size_t, 5> multiHits = {0, 0, 0, 0, 0};

        EtaPhiGrid backEndTrkGrid = {};
        EtaPhiGrid backEndTrkGridShifted = {};
        EtaPhiGrid backEndCalGrid = {};
        EtaPhiGrid backEndCalGridShifted = {};
        fillEtaPhiGrids(recHitsMPGDBackEnd, trkScanStates[kTrkBackwardMPGD],
                        timeResolution_MPGD, tsTimeS, tsTimeE,
                        backEndTrkGrid, backEndTrkGridShifted, backEndBins);
        multiHits[0] = countEtaPhiMatches(recHitsECalBackEnd, calScanStates[kCalEndcapN],
                                          timeResolution_EMCal, tsTimeS, tsTimeE,
                                          backEndCalGrid, backEndCalGridShifted, 1, backEndBins);
        for(size_t iECal_BE = 0; iECal_BE < recHitsECalBackEnd.getHitSize(); ++iECal_BE){
                const Double_t hitT = recHitsECalBackEnd.getTime(iECal_BE);
            if(hitT + timeResolution_EMCal < tsTimeS || hitT - timeResolution_EMCal > tsTimeE) continue;
            const TVector3 hitPos = hitPosition(recHitsECalBackEnd, iECal_BE);
            const auto [eta0, phi0] = barrelBins(hitPos.Eta(), hitPos.Phi(), 0);
            const auto [eta1, phi1] = barrelBins(hitPos.Eta(), hitPos.Phi(), 1);
            if(isValidEtaPhiBin(eta0, phi0) && backEndTrkGrid[eta0][phi0] > 0) {
                backEndCalGrid[eta0][phi0]++;
            }
            if(isValidEtaPhiBin(eta1, phi1) && backEndTrkGridShifted[eta1][phi1] > 0) {
                backEndCalGridShifted[eta1][phi1]++;
            }

        }
        multiHits[0] = countGridCellsWithMultiplicity(backEndCalGrid, backEndCalGridShifted, 10);
        // for(size_t iEtaBin = 0; iEtaBin < kEtaPhiBins; ++iEtaBin){
        //     for(size_t iPhiBin = 0; iPhiBin < kEtaPhiBins; ++iPhiBin){
        //         if(backEndCalGrid[iEtaBin][iPhiBin] < 1) continue;
        //         std::cout << "TF:" << m_pubEvNum << ", TS:" << iTimeSlice << " :: ECal Barrel hit in tower: etaBin = " << iEtaBin << ", phiBin = " << iPhiBin << ", numOfHits = " << backEndCalGrid[iEtaBin][iPhiBin] << std::endl;
        //         // m_hECalBarrelNumOfHitsInTower[bBkgTS]->Fill(backEndCalGrid[iEtaBin][iPhiBin]);
        //     }
        // }

        EtaPhiGrid barrelTrkGrid = {};
        EtaPhiGrid barrelTrkGridShifted = {};
        EtaPhiGrid barrelCalGrid = {};
        EtaPhiGrid barrelCalGridShifted = {};
        fillEtaPhiGrids(recHitsMPGDBarrelIn, trkScanStates[kTrkMPGDBarrel],
                        timeResolution_MPGD, tsTimeS, tsTimeE,
                        barrelTrkGrid, barrelTrkGridShifted, barrelBins);
        fillEtaPhiGrids(recHitsMPGDBarrelOut, trkScanStates[kTrkOuterMPGDBarrel],
                        timeResolution_MPGD, tsTimeS, tsTimeE,
                        barrelTrkGrid, barrelTrkGridShifted, barrelBins);
        fillEtaPhiGrids(recHitsTOFBarrel, trkScanStates[kTrkTOFBarrel],
                        timeResolution_ACLGad, tsTimeS, tsTimeE,
                        barrelTrkGrid, barrelTrkGridShifted, barrelBins);
        for(size_t iECal_BE = 0; iECal_BE < recHitsECalBarrel.getHitSize(); ++iECal_BE){
                const Double_t hitT = recHitsECalBarrel.getTime(iECal_BE);
            if(hitT + timeResolution_EMCal < tsTimeS || hitT - timeResolution_EMCal > tsTimeE) continue;
            const TVector3 hitPos = hitPosition(recHitsECalBarrel, iECal_BE);
            const auto [eta0, phi0] = barrelBins(hitPos.Eta(), hitPos.Phi(), 0);
            const auto [eta1, phi1] = barrelBins(hitPos.Eta(), hitPos.Phi(), 1);
            if(isValidEtaPhiBin(eta0, phi0) && barrelTrkGrid[eta0][phi0] > 0) {
                barrelCalGrid[eta0][phi0]++;
            }
            if(isValidEtaPhiBin(eta1, phi1) && barrelTrkGridShifted[eta1][phi1] > 0) {
                barrelCalGridShifted[eta1][phi1]++;
            }
        }
        multiHits[1] = countGridCellsWithMultiplicity(barrelCalGrid, barrelCalGridShifted, 10);

        EtaPhiGrid frontEndTrkGrid = {};
        EtaPhiGrid frontEndTrkGridShifted = {};
        EtaPhiGrid frontEndCalGrid = {};
        EtaPhiGrid frontEndCalGridShifted = {};
        fillEtaPhiGrids(recHitsMPGDForwardEnd, trkScanStates[kTrkForwardMPGD],
                        timeResolution_MPGD, tsTimeS, tsTimeE,
                        frontEndTrkGrid, frontEndTrkGridShifted, forwardEndBins);
        fillEtaPhiGrids(recHitsTOFForwardEnd, trkScanStates[kTrkTOFEndcap],
                        timeResolution_ACLGad, tsTimeS, tsTimeE,
                        frontEndTrkGrid, frontEndTrkGridShifted, forwardEndBins);
        for(size_t iECal_BE = 0; iECal_BE < recHitsECalForwardEnd.getHitSize(); ++iECal_BE){
                const Double_t hitT = recHitsECalForwardEnd.getTime(iECal_BE);
            if(hitT + timeResolution_EMCal < tsTimeS || hitT - timeResolution_EMCal > tsTimeE) continue;
            const TVector3 hitPos = hitPosition(recHitsECalForwardEnd, iECal_BE);
            const auto [eta0, phi0] = forwardEndBins(hitPos.Eta(), hitPos.Phi(), 0);
            const auto [eta1, phi1] = forwardEndBins(hitPos.Eta(), hitPos.Phi(), 1);
            if(isValidEtaPhiBin(eta0, phi0) && frontEndTrkGrid[eta0][phi0] > 0) {
                frontEndCalGrid[eta0][phi0]++;
            }
            if(isValidEtaPhiBin(eta1, phi1) && frontEndTrkGridShifted[eta1][phi1] > 0) {
                frontEndCalGridShifted[eta1][phi1]++;
            }
        }
        multiHits[2] = countGridCellsWithMultiplicity(frontEndCalGrid, frontEndCalGridShifted, 5);
        // for(size_t iEtaBin = 0; iEtaBin < kEtaPhiBins; ++iEtaBin){
        //     for(size_t iPhiBin = 0; iPhiBin < kEtaPhiBins; ++iPhiBin){
        //         if(frontEndCalGrid[iEtaBin][iPhiBin] < 1) continue;
        //         std::cout << "TF:" << m_pubEvNum << ", TS:" << iTimeSlice << " :: ECal Front End hit in tower: etaBin = " << iEtaBin << ", phiBin = " << iPhiBin << ", numOfHits = " << frontEndCalGrid[iEtaBin][iPhiBin] << std::endl;
        //         // m_hECalBarrelNumOfHitsInTower[bBkgTS]->Fill(frontEndCalGrid[iEtaBin][iPhiBin]);
        //     }
        // }

        Int_t numOfBOTrk = 0;
        Int_t totEDepOfBOCal = 0;
        for(size_t iB0Trk = 0; iB0Trk < recHitsB0Trk.getHitSize(); ++iB0Trk){
            const Double_t hitT = recHitsB0Trk.getTime(iB0Trk);
            if(hitT + timeResolution_ACLGad < tsTimeS || hitT - timeResolution_ACLGad > tsTimeE) continue;
            numOfBOTrk++;
        }
        multiHits[3] = numOfBOTrk;
        // multiHits[3] = countTimedHits(recHitsB0Trk, trkScanStates[kTrkB0],
        //                               timeResolution_ACLGad, tsTimeS, tsTimeE);

        
        // multiHits[4] = countTimedHits(recHitsZDCECal, calScanStates[kCalZDC],
        //                               timeResolution_EMCal, tsTimeS, tsTimeE);
        Int_t totEDepOfZDC = 0;
        for(size_t iECalZDC = 0; iECalZDC < recHitsZDCECal.getHitSize(); ++iECalZDC){
            const Double_t hitT = recHitsZDCECal.getTime(iECalZDC);
            if(hitT + timeResolution_EMCal < tsTimeS || hitT - timeResolution_EMCal > tsTimeE) continue;
            totEDepOfZDC += recHitsZDCECal.getEDep(iECalZDC);
        }
        multiHits[4] = totEDepOfZDC;
        
        for(size_t iEtaBin = 0; iEtaBin < kEtaPhiBins; ++iEtaBin){
            for(size_t iPhiBin = 0; iPhiBin < kEtaPhiBins; ++iPhiBin){
                m_hTrigMultiHits[0][bBkgTS]->Fill(backEndCalGrid[iEtaBin][iPhiBin]);
                m_hTrigMultiHits[0][bBkgTS]->Fill(backEndCalGridShifted[iEtaBin][iPhiBin]);
                m_hTrigMultiHits[1][bBkgTS]->Fill(barrelCalGrid[iEtaBin][iPhiBin]);
                m_hTrigMultiHits[1][bBkgTS]->Fill(barrelCalGridShifted[iEtaBin][iPhiBin]);
                m_hTrigMultiHits[2][bBkgTS]->Fill(frontEndCalGrid[iEtaBin][iPhiBin]);
                m_hTrigMultiHits[2][bBkgTS]->Fill(frontEndCalGridShifted[iEtaBin][iPhiBin]);
            }
        }
        m_hTrigThreHits[0][bBkgTS]->Fill(multiHits[0]);
        m_hTrigThreHits[1][bBkgTS]->Fill(multiHits[1]);
        m_hTrigThreHits[2][bBkgTS]->Fill(multiHits[2]);
        m_hTrigThreHits[3][bBkgTS]->Fill(multiHits[3]);
        m_hTrigThreHits[4][bBkgTS]->Fill(multiHits[4]);

        Bool_t bTrigs[6] = {};
        if((multiHits[0] + multiHits[1] + multiHits[2]) > 0 && multiHits[3] > 4) bTrigs[0] = kTRUE;
        if((multiHits[0] + multiHits[1] + multiHits[2]) > 0 && multiHits[4] > 50) bTrigs[1] = kTRUE;
        // if(multiHits[1] > 2 && multiHits[2] > 2) bTrigs[2] = kTRUE;
        // if(multiHits[0] > 0 && multiHits[3] > 0) bTrigs[3] = kTRUE;
        // if(multiHits[0] > 0 && multiHits[2] > 0) bTrigs[4] = kTRUE;
        // if(multiHits[2] > 0 && multiHits[4] > 50) bTrigs[5] = kTRUE;


        if(bTrigs[0]) m_hCombTriggerEfficiency[bBkgTS]->Fill(2); // CentralTrk+B0Trk
        if(bTrigs[1]) m_hCombTriggerEfficiency[bBkgTS]->Fill(3); // CentralTrk+ZDC
        if(bTrigs[2]) m_hCombTriggerEfficiency[bBkgTS]->Fill(4); // Barrel + Forward
        if(bTrigs[3]) m_hCombTriggerEfficiency[bBkgTS]->Fill(5); // BackEndTrk+B0Trk
        if(bTrigs[4]) m_hCombTriggerEfficiency[bBkgTS]->Fill(6); // CentralTrk+B0Trk
        if(bTrigs[5]) m_hCombTriggerEfficiency[bBkgTS]->Fill(7); // CentralTrk+ZDC

        if(bTrigs[0] || bTrigs[1] || bTrigs[2] || bTrigs[3] || bTrigs[4] || bTrigs[5]) m_hCombTriggerEfficiency[bBkgTS]->Fill(1);
        else if(!bBkgTS) m_vTargetEvents.push_back(m_pubEvNum);
    } // == e == while loop for time slices ==
}


void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;

    m_dirTrkRecDepE = oFile->mkdir("TrkRecDepEDirs");
    for (const auto& trkName : m_trkShortDetName) {
        m_mapTrkRecDepEDirs[trkName.Data()] = m_dirTrkRecDepE->mkdir(trkName.Data());
    }
    m_dirCalRecDepE = oFile->mkdir("CalRecDepEDirs");
    for (const auto& calName : m_calRecShortDetName) {
        m_mapCalRecDepEDirs[calName.Data()] = m_dirCalRecDepE->mkdir(calName.Data());
    }
    m_dirTrkRecTimeDist = oFile->mkdir("TrkRecTimeDistDirs");
    for (const auto& trkName : m_trkShortDetName) {
        m_mapTrkRecTimeDistDirs[trkName.Data()] = m_dirTrkRecTimeDist->mkdir(trkName.Data());
    }
    m_dirCalRecTimeDist = oFile->mkdir("CalRecTimeDistDirs");
    for (const auto& calName : m_calRecShortDetName) {
        m_mapCalRecTimeDistDirs[calName.Data()] = m_dirCalRecTimeDist->mkdir(calName.Data());
    }

    m_dirTrkRecNumOfHitsInTS = oFile->mkdir("TrkRecNumOfHitsInTSDirs");
    for (const auto& trkName : m_trkShortDetName) {
        m_mapTrkRecNumOfHitsInTSDirs[trkName.Data()] = m_dirTrkRecNumOfHitsInTS->mkdir(trkName.Data());
    }
    m_dirCalRecNumOfHitsInTS = oFile->mkdir("CalRecNumOfHitsInTSDirs");
    for (const auto& calName : m_calRecShortDetName) {
        m_mapCalRecNumOfHitsInTSDirs[calName.Data()] = m_dirCalRecNumOfHitsInTS->mkdir(calName.Data());
    }

    TString histName = "";
    TString histTitle = "";

    m_hBSiRecDepE = new TH1D("m_hBSiRecDepE", "m_hBSiRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hESiRecDepE = new TH1D("m_hESiRecDepE", "m_hESiRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hBMPGDRecDepE = new TH1D("m_hBMPGDRecDepE", "m_hBMPGDRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hEMPGDRecDepE = new TH1D("m_hEMPGDRecDepE", "m_hEMPGDRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hBTOFRecDepE = new TH1D("m_hBTOFRecDepE", "m_hBTOFRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hETOFRecDepE = new TH1D("m_hETOFRecDepE", "m_hETOFRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hB0RecDepE = new TH1D("m_hB0RecDepE", "m_hB0RecDepE; depE [MeV];count", 100, 0, 0.1);

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hDetRecDepE_%s_%s",m_trkShortDetName[iTrkDet].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hTrkRecEDep[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 0.50);
        }
    }

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempPhysName = "Phys";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hTrkTimeDist%s_%s",m_trkShortDetName[iTrkDet].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hTrkTimeDist[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hTrkNumOfHitsInTS%s_%s",m_trkShortDetName[iTrkDet].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 20, 0, 20);
        }
    }


    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hCalRecRecDepE_%s_%s",m_calRecShortDetName[iCalRec].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hCalRecEDep[iCalRec][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100.0);
        }
    }

    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempPhysName = "Phys";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hCalRecTimeDist%s_%s",m_calRecShortDetName[iCalRec].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hCalRecTimeDist[iCalRec][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hCalRecNumOfHitsInTS%s_%s",m_calRecShortDetName[iCalRec].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hCalRecNumOfHitsInTS[iCalRec][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100);
        }
    }

    for(size_t iTrig = 0; iTrig < 5; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempTrigName = "BTOF+BMPGD";
            if(iTrig == 1) tempTrigName = "ETOF+EMPGD";
            else if(iTrig == 2) tempTrigName = "B0";
            else if(iTrig == 3) tempTrigName = "EcalP";
            else if(iTrig == 4) tempTrigName = "ZDC";
            TString tempPhysName = "Phys+BKG";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hTrigDetNumOfHitsInTS_%s_%s", tempTrigName.Data(), tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count", histName.Data());
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100);
        }
    }


    m_dirTrigMultiHits = oFile->mkdir("TrigMultiHitsDirs");
    m_dirTrigThreHits = oFile->mkdir("TrigThreHitsDirs");

    for(size_t iPreTrig = 0; iPreTrig < 5; iPreTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            histName = TString::Format("m_hTrigMultiHits_%s_%s",m_PreTrigName[iPreTrig].Data(),m_biPhysName[iPKind].Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hTrigMultiHits[iPreTrig][iPKind] = new TH1I(histName.Data(), histTitle.Data(), 100, 0, 100);

            histName = TString::Format("m_hTrigThreHits_%s_%s",m_PreTrigName[iPreTrig].Data(),m_biPhysName[iPKind].Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hTrigThreHits[iPreTrig][iPKind] = new TH1I(histName.Data(), histTitle.Data(), 100, 0, 100);
        }
    }

    for(size_t iPKind = 0; iPKind < 2; iPKind++){
        m_hCombTriggerEfficiency[iPKind] = new TH1I(TString::Format("m_hCombTriggerEfficiency_%s", m_biPhysName[iPKind].Data()),
                                                      TString::Format("m_hCombTriggerEfficiency_%s;trigger combination;count", m_biPhysName[iPKind].Data()),
                                                      3, 0.5, 3.5);
        m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(1, "Total");
        m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(2, "CentralTrk+B0Trk");
        m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(3, "CentralTrk+ZDC");
        // m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(4, "BackEnd+B0Trk");
        // m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(5, "Barrel+ZDC");
        // m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(6, "CentralTrk+B0Trk");
        // m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(7, "CentralTrk+ZDC");
        // m_hCombTriggerEfficiency[iPKind]->GetXaxis()->SetBinLabel(8, "Other");
    }


    for(size_t iPKind = 0; iPKind < 2; iPKind++){
        m_hECalBarrelNumOfHitsInTower[iPKind] = new TH1I(TString::Format("m_hECalBarrelNumOfHitsInTower_%s", m_biPhysName[iPKind].Data()),
                                                      TString::Format("m_hECalBarrelNumOfHitsInTower_%s;number of hits;count", m_biPhysName[iPKind].Data()),
                                                      500, 0, 500);
        m_hECalBarrelNumOfHitsTimesEInTower[iPKind] = new TH1D(TString::Format("m_hECalBarrelNumOfHitsTimesEInTower_%s", m_biPhysName[iPKind].Data()),
                                                      TString::Format("m_hECalBarrelNumOfHitsTimesEInTower_%s;number of hits times E;count", m_biPhysName[iPKind].Data()),
                                                      100, 0, 500);
    }

}

void EventAna::EditHists() {
    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hTrkRecEDep[iTrkDet][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hTrkRecEDep[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hTrkTimeDist[iTrkDet][iPKind]->SetLineColor(histColor);
            m_hTrkTimeDist[iTrkDet][iPKind]->SetLineWidth(5);

            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->SetLineColor(histColor);
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalRecEDep[iCalRec][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hCalRecEDep[iCalRec][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hCalRecTimeDist[iCalRec][iPKind]->SetLineColor(histColor);
            m_hCalRecTimeDist[iCalRec][iPKind]->SetLineWidth(5);

            m_hCalRecNumOfHitsInTS[iCalRec][iPKind]->SetLineColor(histColor);
            m_hCalRecNumOfHitsInTS[iCalRec][iPKind]->SetLineWidth(5);
        }
    }



    for(size_t iTrig = 0; iTrig < 5; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->SetLineColor(histColor);
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->SetLineWidth(5);
        }
    }


    
    for(size_t iPKind = 0; iPKind < 2; iPKind++){
        Int_t histColor = 820+4;
        if(iPKind == 1) histColor = 880 -1;
        for(size_t iTrig = 0; iTrig < 5; iTrig++){
            m_hTrigMultiHits[iTrig][iPKind]->SetLineColor(histColor);
            m_hTrigMultiHits[iTrig][iPKind]->SetLineWidth(5);
        }
        m_hCombTriggerEfficiency[iPKind]->SetLineColor(histColor);
        m_hCombTriggerEfficiency[iPKind]->SetLineWidth(5);
    }

    for(size_t iPKind = 0; iPKind < 2; iPKind++){
        Int_t histColor = 820+4;
        if(iPKind == 1) histColor = 880 -1;
        for(size_t iTrig = 0; iTrig < 5; iTrig++){
            m_hTrigThreHits[iTrig][iPKind]->SetLineColor(histColor);
            m_hTrigThreHits[iTrig][iPKind]->SetLineWidth(5);
        }
    }
    
}

void EventAna::OFileWrite() {
    std::cout << "OFileWrite" << std::endl;
    oFile->cd();

    m_hBSiRecDepE->Write();
    m_hESiRecDepE->Write();
    m_hBMPGDRecDepE->Write();
    m_hEMPGDRecDepE->Write();
    m_hBTOFRecDepE->Write();
    m_hETOFRecDepE->Write();
    m_hB0RecDepE->Write();

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        const auto& detName = m_trkShortDetName[iTrkDet];
        TDirectory* dirTrkRecDepE = m_dirTrkRecDepE->GetDirectory(detName.Data());
        if (!dirTrkRecDepE) dirTrkRecDepE = m_dirTrkRecDepE->mkdir(detName.Data());

        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            const auto& pKindName = m_physKindShortName[iPKind];
            dirTrkRecDepE->WriteObject(m_hTrkRecEDep[iTrkDet][iPKind], pKindName.Data());
        }

        TDirectory* dirTrkTimeDist = m_dirTrkRecTimeDist->GetDirectory(detName.Data());
        if (!dirTrkTimeDist) dirTrkTimeDist = m_dirTrkRecTimeDist->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirTrkTimeDist->WriteObject(m_hTrkTimeDist[iTrkDet][iPKind], pKindName.Data());
        }

        TDirectory* dirTrkNumOfHitsInTS = m_dirTrkRecNumOfHitsInTS->GetDirectory(detName.Data());
        if (!dirTrkNumOfHitsInTS) dirTrkNumOfHitsInTS = m_dirTrkRecNumOfHitsInTS->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirTrkNumOfHitsInTS->WriteObject(m_hTrkNumOfHitsInTS[iTrkDet][iPKind], pKindName.Data());
        }
    }
    
    
    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        const auto& detName = m_calRecShortDetName[iCalRec];
        TDirectory* dirCalRecDepE = m_dirCalRecDepE->GetDirectory(detName.Data());
        if (!dirCalRecDepE) dirCalRecDepE = m_dirCalRecDepE->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            const auto& pKindName = m_physKindShortName[iPKind];
            dirCalRecDepE->WriteObject(m_hCalRecEDep[iCalRec][iPKind], pKindName.Data());
        }
        TDirectory* dirCalRecTimeDist = m_dirCalRecTimeDist->GetDirectory(detName.Data());
        if (!dirCalRecTimeDist) dirCalRecTimeDist = m_dirCalRecTimeDist->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirCalRecTimeDist->WriteObject(m_hCalRecTimeDist[iCalRec][iPKind], pKindName.Data());
        }
        TDirectory* dirCalRecNumOfHitsInTS = m_dirCalRecNumOfHitsInTS->GetDirectory(detName.Data());
        if (!dirCalRecNumOfHitsInTS) dirCalRecNumOfHitsInTS = m_dirCalRecNumOfHitsInTS->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirCalRecNumOfHitsInTS->WriteObject(m_hCalRecNumOfHitsInTS[iCalRec][iPKind], pKindName.Data());
        }
    }

    for(size_t iTrig = 0; iTrig < 5; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->Write();
        }
    }
    

    for(size_t iPKind = 0; iPKind < 2; iPKind++){
        for(size_t iTrig = 0; iTrig < 5; iTrig++){
            m_dirTrigMultiHits->cd();
            m_hTrigMultiHits[iTrig][iPKind]->Write();
            m_dirTrigThreHits->cd();
            m_hTrigThreHits[iTrig][iPKind]->Write();
        }
        oFile->cd();
        m_hCombTriggerEfficiency[iPKind]->Write();
    }

    oFile->cd();
    for(size_t iPKind = 0; iPKind < 2; iPKind++){
        m_hECalBarrelNumOfHitsInTower[iPKind]->Write();
        m_hECalBarrelNumOfHitsTimesEInTower[iPKind]->Write();
    }


    oFile->Close();
}

void EventAna::ResetValuesForEachEvent() {
    m_trkDetsHits.clear();
    m_calDetsHits.clear();
}

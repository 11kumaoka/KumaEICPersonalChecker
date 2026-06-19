#ifndef EVENT_ANA_H
#define EVENT_ANA_H

#include <string>
#include <vector>

#include "Rtypes.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TMath.h>
#include "Fit/Fitter.h"
#include <Math/Functor.h>

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TProfile2D.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TView.h>
#include <TAxis3D.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLatex.h>

#include "podio/ROOTReader.h"
#include "podio/Frame.h"

#include "edm4hep/MCParticleCollection.h"

#include <edm4hep/SimTrackerHitCollection.h>
#include <edm4eic/RawTrackerHitCollection.h>
#include <edm4eic/MCRecoTrackerHitAssociationCollection.h>
#include "edm4eic/TrackerHitCollection.h"
#include <edm4hep/RawCalorimeterHitCollection.h>
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/CalorimeterHitCollection.h>
#include <edm4eic/MCRecoCalorimeterHitAssociationCollection.h>
#include <edm4eic/MCRecoClusterParticleAssociationCollection.h>

#include "InputDataConfig.h"
#include "SimTrackerHitKuma.h"


class EventAna {

public:
    EventAna(const std::string& inputFile, const std::string& outputFile = "test.root");
    void EventLoop();

private:
    SimTrackerHitKuma makeTrkHitsV(const edm4eic::TrackerHitCollection& podioHits);
    SimTrackerHitKuma makeCalHitsV(const edm4eic::ClusterCollection& podioHits);
    std::vector<SimTrackerHitKuma> LoadTrackerHitsFromFrame(const podio::Frame& frame);
    std::vector<SimTrackerHitKuma> LoadCalHitsFromFrame(const podio::Frame& frame);

    void OFileInit();
    void EditHists();
    void OFileWrite();
    void ResetValuesForEachEvent();

    Double_t FindPhysCollTime(const podio::Frame& frame);

    void FillEachSubDetRecDepE(const podio::Frame& frame);
    void FillEachSubDetDepE();

    // inline Double_t calibDeltaT;
    Double_t calibT(Double_t hitT, Double_t hitR);
    void FillHitTimesDist(const podio::Frame& frame, Double_t vtxTime);

private:
    std::string m_iFileName;
    std::string m_oFileName;
    podio::ROOTReader m_reader;

    TFile* oFile;

    std::vector<Int_t> m_vTargetEvents;
    Int_t m_pubEvNum = 0;

    std::vector<SimTrackerHitKuma> m_trkDetsHits;
    std::vector<SimTrackerHitKuma> m_calDetsHits;

    double m_timeWindow = 2000.0;
    double m_timeSliceWidth = 20.0;

    Double_t m_TrkTimeRes[9] = {2000., 2000., 10., 10., 0.05, 0.05, 0.05, 10., 10.}; // ns [s] // BSi, ESi, BMPGD, EMPGD, BTOF, ETOF, B0, FOffMT, FRoman
    Double_t m_CalTimeRes[7] = {50., 50., 50., 50., 50., 50., 50.}; // ns [s] // EcalB0, EcalBImag, EcalBScFi, EcalEN, EcalEP, EcalFFZDCC, EcalLumi

    // TOFBarrelRecHits, TOFEndcapRecHits, BackwardMPGDEndcapRecHits, ForwardMPGDEndcapRecHits, MPGDBarrelRecHits, OuterMPGDBarrelRecHits, SiBarrelVertexRecHits, SiBarrelTrackerRecHits, SiEndcapTrackerRecHits, B0TrackerRecHits
    Int_t m_TrackDetColors[10] = {880+10, 880+10, 880-2, 880-2, 880-2, 880-2, 880+4, 880+2, 880+2, 880+10,};
    // , ,  EcalBarrelScFiClusters, EcalEndcapNClusters, EcalEndcapPClusters, EcalFarForwardZDCClusters, EcalLumiSpecClusters, ForwardRomanPotRecHits, LFHCALClusters
    Int_t m_CalDetColors[8] = {860-3, 840-3, 600-9, 600-9, 880+1, 860+10, 880-6, 600-3};
    // B0ECalClusters:  860+7, ,EcalBarrelClusters: 880-4, EcalBarrelImagingClusters: 600-7
    // DIRCRawHits, DRICHRawHits, 
    Int_t m_PIDDetColors[2] = {860-6, 860};

    Int_t m_BKGColors[6] = {820+4, 860+10, 860-3, 800-3, 840+9, 900+9};

    std::array<TString, 6> m_physKindShortName = {"Phys", "SR", "Brems", "Coulomb", "Touscheck", "PGas"};
    std::array<TString, 2> m_biPhysName = {"Phys", "BKG"};
    std::array<TString, 9> m_trkShortDetName = {"BSi", "ESi", "BMPGD", "EMPGD", "BTOF", "ETOF", "B0", "FOffMT", "FRoman"};
    std::array<TString, 7> m_calRecShortDetName = {"EcalB0","EcalBImag","EcalBScFi","EcalEN","EcalEP","EcalFFZDCC","EcalLumi"};
    std::array<TString, 6> m_calShortDetName = {"EcalB0","EcalB","EcalEN","EcalEP","EcalFFZDCC","EcalLumi"};

    std::map<std::string, TDirectory*> m_mapTrkRecDepEDirs;
    std::map<std::string, TDirectory*> m_mapCalRecDepEDirs;
    std::map<std::string, TDirectory*> m_mapCalCluDepEDirs;
    std::map<std::string, TDirectory*> m_mapTrkRecTimeDistDirs;
    std::map<std::string, TDirectory*> m_mapCalRecTimeDistDirs;
    std::map<std::string, TDirectory*> m_mapCalCluTimeDistDirs;
    std::map<std::string, TDirectory*> m_mapTrkRecNumOfHitsInTSDirs;
    std::map<std::string, TDirectory*> m_mapCalRecNumOfHitsInTSDirs;
    std::map<std::string, TDirectory*> m_mapCalCluNumOfHitsInTSDirs;
    TDirectory* m_dirTrkRecDepE;
    TDirectory* m_dirCalRecDepE;
    TDirectory* m_dirCalCluDepE;
    TDirectory* m_dirTrkRecTimeDist;
    TDirectory* m_dirCalRecTimeDist;
    TDirectory* m_dirCalCluTimeDist;
    TDirectory* m_dirTrkRecNumOfHitsInTS;
    TDirectory* m_dirCalRecNumOfHitsInTS;
    TDirectory* m_dirCalCluNumOfHitsInTS;

    TH1D* m_hBSiRecDepE;
    TH1D* m_hESiRecDepE;
    TH1D* m_hBMPGDRecDepE;
    TH1D* m_hEMPGDRecDepE;
    TH1D* m_hBTOFRecDepE;
    TH1D* m_hETOFRecDepE;
    TH1D* m_hB0RecDepE;

    TH1D* m_hTrkRecEDep[9][6];// Det:BSi, ESi, BMPGD, EMPGD, BTOF, ETOF, B0, FOffMT, FRoman / Hit: Phys, Bkg
    TH1D* m_hCalRecEDep[6][6];
    TH1D* m_hCalCluEDep[6][6];

    TH1D* m_hTrkTimeDist[9][2]; // Det:BSi, ESi, BMPGD, EMPGD, BTOF, ETOF, B0, FOffMT, FRoman / Hit: Phys, Bkg
    TH1D* m_hTrkNumOfHitsInTS[9][2]; //  Det:BSi, ESi, BMPGD, EMPGD, BTOF, ETOF, B0, FOffMT, FRoman / Hit: Phys, Bkg

    TH1D* m_hCalRecTimeDist[7][2]; // Det:B0, EcalBImag, EcalBScFi, EcalEN, EcalEP, EcalFFZDCC, EcalLumi / Hit: Phys, Bkg
    TH1D* m_hCalRecNumOfHitsInTS[7][2]; //  Det:B0, EcalBImag, EcalBScFi, EcalEN, EcalEP, EcalFFZDCC, EcalLumi / Hit: Phys, Bkg

    TH1D* m_hCalCluTimeDist[6][2]; // Det:BMPGD, EMPGD, BTOF, ETOF, B0, FOffMT, FRoman / Hit: Phys, Bkg
    TH1D* m_hCalCluNumOfHitsInTS[6][2]; //  Det:BMPGD, EMPGD, BTOF, ETOF, B0, FOffMT, FRoman / Hit: Phys, Bkg

    TH1D* m_hTrigDetNumOfHitsInTS[5][2]; //  Det:BMPGD+TOF, EMPGD+TOF, B0 / Hit: Phys+BKG, Bkg

    Int_t m_numOfPhysTrig = 0;
    Int_t m_numOfFakeTrig = 0;
    TH1D* m_hTrigEfficiency;
};

#endif
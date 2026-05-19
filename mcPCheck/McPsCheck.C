// #define McPsCheck_cxx
#include "McPsCheck.h"

#include <random>

#include <TStyle.h>
#include <TCanvas.h>

McPsCheck::McPsCheck(TTree *tree, std::string iTempFileName,std::string oTempFileName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   iFileName = iTempFileName;
   oFileName = oTempFileName;

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(iFileName.c_str());
      if (!f || !f->IsOpen()) {
         f = new TFile(iFileName.c_str());
      }
      // "kuma example": you need to replace "tree" to your tree name in the input root file.
      f->GetObject("events",tree);

   }
   Init(tree);
}

McPsCheck::~McPsCheck()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void McPsCheck::Loop()
{
   if (fChain == 0) return;

   
   HistInit();

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   Double_t numOfEvents[18] = {};
   Double_t numOfEvents_EachDet_TrigRegion[4][18] = {};
   Double_t numOfEvents_TrigRegion[4] = {}; // 0: Phys W/O Trig23, 1: Phys W Trig23, 2: Noise W/O Trig23, 3: Noise W Trig23
   
   size_t numOfPhys = 0;
   size_t numOfNoise = 0;

   bool bTargetEV = false;

   //  m_vTargetEvents = {0, 1 ,2, 3, 4, 5,6, 7, 8};
    m_vTargetEvents = {};

   //  Int_t numOfEventLoops = 74000;
   Int_t numOfEventLoops = 1000;
   // Int_t numOfEventLoops = 10;
   // Int_t numOfEventLoops = nentries;
   if(bTargetEV) numOfEventLoops = m_vTargetEvents.size();

   
   
   // for (Long64_t jentry=0; jentry<1000; jentry++) {
   for (Long64_t jentry = 0; jentry < numOfEventLoops; ++jentry) {
   // for (Long64_t jentry=0; jentry < nentries;++jentry) {
      Long64_t tempJEntry = jentry;
      if(bTargetEV) jentry =  m_vTargetEvents.at(jentry);
      m_pubEvNum = jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(jentry%1000 == 0) std::cout << " == event" << jentry << " =====" << std::endl;
      // std::cout << " == event" << jentry << " =====" << std::endl;
      numOfEvents[17]++;

      // if(VertexBarrelHits_){
      //    std::cout << "VertexBarrelHits_: " << VertexBarrelHits_ << "_VertexBarrelHits_particles: " << _VertexBarrelHits_particle_ << std::endl;
      //    for(size_t iPart = 0; iPart < _VertexBarrelHits_particle_; iPart++){
      //       Int_t pTagId = _VertexBarrelHits_particle_index[iPart];
      //       std::cout << "pTagId: " << pTagId << ", PID: " << MCParticles_PDG[pTagId] << ", generatorStatus: " << MCParticles_generatorStatus[pTagId] << std::endl;

      //    }
         
      // }
      // if(SiBarrelHits_){
      //    std::cout << "count Event " << tempCount << ":: VertexBarrelHits_ = " << VertexBarrelHits_ << ", SiBarrelHits_: " << SiBarrelHits_ << ", TrackerEndcapHits_: " << TrackerEndcapHits_\
      //    << ", MPGDBarrelHits_: " << MPGDBarrelHits_ << ", OuterMPGDBarrelHits_ = " << OuterMPGDBarrelHits_ << ", ForwardMPGDEndcapHits_ = " << ForwardMPGDEndcapHits_\
      //    << ", BackwardMPGDEndcapHits_ = " << BackwardMPGDEndcapHits_ << ", TOFBarrelHits_ = " << TOFBarrelHits_ << ", TOFEndcapHits_ = " << TOFEndcapHits_ << std::endl;
      //    tempCount++;
      // }
      CountMcParticles();

      FillHitTimeDispersion();
      FillHitTimeDispersionForMixBKG();
      
      FillZRHitMaps();
      FillEtaPtMaps();

      countTrkDetHits();
      countCalDetHits();
      
      
      if(m_iDisplayCount < numOfED){
         if(1){
         // if(TOFBarrelHits_ && SiBarrelHits_){
            m_iDisplayCount++;
            recordMCPsForED();
            recordTrkHitsForED();
            recordCalHitsForED();

            // for(size_t iTofP = 0; iTofP < _TOFBarrelHits_particle_; iTofP++){
            //    Int_t iP = _TOFBarrelHits_particle_index[iTofP];
            //    std::cout << "iP: [" << iP\
            //    << "], PID: " << MCParticles_PDG[iP] << std::endl;
            // }
            // for(size_t iMCP = 0; iMCP < MCParticles_; iMCP++){
            //    std::cout << "iMCP: [" << iMCP\
            //    << "], PID: " << MCParticles_PDG[iMCP]\
            //    << ", charge: " << MCParticles_charge[iMCP]\
            //    << ", generatorStatus: " << MCParticles_generatorStatus[iMCP]\
            //    << ", vertex: (" << MCParticles_vertex_x[iMCP] << ", " << MCParticles_vertex_y[iMCP] << ", " << MCParticles_vertex_z[iMCP] << ")"\
            //    << ", momentum: (" << MCParticles_momentum_x[iMCP] << ", " << MCParticles_momentum_y[iMCP] << ", " << MCParticles_momentum_z[iMCP] << ")"\
            //    << std::endl;
            // }

         } 

      }
   }


   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      m_hZRHitRatio_All_BKG[iBkg]->Scale(1./(1.0*(numOfEventLoops)));
      m_hZRHitRatio_ChMcP_BKG[iBkg]->Scale(1./(1.0*(numOfEventLoops)));
      m_hZRHitRatio_NMcP_BKG[iBkg]->Scale(1./(1.0*(numOfEventLoops)));

      m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Scale(1./(1.0*(numOfEventLoops)));
      m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Scale(1./(1.0*(numOfEventLoops)));
   }
   m_NumOfEventsOfBKG->Scale(1./(1.0*(numOfEventLoops)));


   Int_t numOfHEndBinPhys = m_HitTCalcT0Dispersion_Phys->GetNbinsX();
   Int_t totCountPhys = m_HitTCalcT0Dispersion_Phys->Integral(1, numOfHEndBinPhys);
   Int_t inteCountPhys = 0;
   Double_t numOfPhysHits95 = 0;
   Double_t threBinVal95 = 0;
   Double_t numOfPhysHits99 = 0;
   Double_t threBinVal99 = 0;
   for (int iBin = 1; iBin <= numOfHEndBinPhys; ++iBin) {
      Int_t binContent = m_HitTCalcT0Dispersion_Phys->GetBinContent(iBin);
      inteCountPhys += binContent;
      std::cout << "iBin: " << iBin << ", binCenter: " << m_HitTCalcT0Dispersion_Phys->GetXaxis()->GetBinCenter(iBin) << ", binContent: " << binContent << ", inteCountPhys: " << inteCountPhys << std::endl;
      if(inteCountPhys > 0.95 * totCountPhys){
         std::cout << "95% threshold reached at iBin: " << iBin << ", binCenter: " << m_HitTCalcT0Dispersion_Phys->GetXaxis()->GetBinCenter(iBin) << ", inteCountPhys: " << inteCountPhys << std::endl;
         if(threBinVal95 == 0){
                     std::cout << "95% threshold reached at iBin: " << iBin << ", binCenter: " << m_HitTCalcT0Dispersion_Phys->GetXaxis()->GetBinCenter(iBin) << ", inteCountPhys: " << inteCountPhys << std::endl;
            threBinVal95 = m_HitTCalcT0Dispersion_Phys->GetXaxis()->GetBinCenter(iBin - 1);
            numOfPhysHits95 = inteCountPhys;
         }
      }
      if(inteCountPhys > 0.99 * totCountPhys){
         if(threBinVal99 == 0){
            threBinVal99 = m_HitTCalcT0Dispersion_Phys->GetXaxis()->GetBinCenter(iBin - 1);
            numOfPhysHits99 = inteCountPhys;
         }
         break;
      }
   }
   Double_t threSBinIDVal95 = m_HitTCalcT0Dispersion_Phys->GetXaxis()->FindBin(-threBinVal95);
   Double_t threEBinIDVal95 = m_HitTCalcT0Dispersion_Phys->GetXaxis()->FindBin(threBinVal95);
   Double_t threSBinIDVal99 = m_HitTCalcT0Dispersion_Phys->GetXaxis()->FindBin(-threBinVal99);
   Double_t threEBinIDVal99 = m_HitTCalcT0Dispersion_Phys->GetXaxis()->FindBin(threBinVal99);
   Int_t inteCountBKG95 = 0;
   for (int iBin = threSBinIDVal95; iBin <= threEBinIDVal95; ++iBin) {
      Int_t binContent = m_HitTCalcT0Dispersion_Phys->GetBinContent(iBin);
      inteCountBKG95 += binContent;
   }
   Int_t inteCountBKG99 = 0;
   for (int iBin = threSBinIDVal99; iBin <= threEBinIDVal99; ++iBin) {
      Int_t binContent = m_HitTCalcT0Dispersion_Phys->GetBinContent(iBin);
      inteCountBKG99 += binContent;
   }
   std::cout<< "-threBinVal95, threSBinIDVal95 = " << - threBinVal95 << ", " << threSBinIDVal95 << std::endl;
   std::cout<< "threBinVal95, threEBinIDVal95 = " << threBinVal95 << ", " << threEBinIDVal95 << std::endl;

   std::cout << "95 percents hits contain time = " << threBinVal95 << " ns, numOfPhysHits95 = " << numOfPhysHits95 << ", numOfBKGHits95 = " << inteCountBKG95 << std::endl;
   std::cout << "99 percents hits contain time = " << threBinVal99 << " ns, numOfPhysHits99 = " << numOfPhysHits99 << ", numOfBKGHits99 = " << inteCountBKG99 << std::endl;
   m_HitTCalcT0Dispersion_Phys->Scale(1./(1.0*(numOfEventLoops)));
   m_HitTCalcT0Dispersion_BKG->Scale(1./(1.0*(numOfEventLoops)));
   m_HitTCalcT0Dispersion_Phys_BTOF->Scale(1./(1.0*(numOfEventLoops)));
   m_HitTCalcT0Dispersion_BKG_BTOF->Scale(1./(1.0*(numOfEventLoops)));


   Int_t numOfHEndBin = m_HitTCalcT0Dispersion->GetNbinsX();
   Int_t totCount = m_HitTCalcT0Dispersion->Integral(1, numOfHEndBin);
   Int_t inteCount = 0;
   Double_t threBinVal = 0;
   for (int iBin = 1; iBin <= numOfHEndBin; ++iBin) {
      Int_t binContent = m_HitTCalcT0Dispersion->GetBinContent(iBin);
      inteCount += binContent;
      if(inteCount > 0.9 * totCount){
          threBinVal = m_HitTCalcT0Dispersion->GetXaxis()->GetBinCenter(iBin - 1);
         break;
      }
   }
   std::cout << "90 percents hits contain time = " << threBinVal << " ns" <<  std::endl;


   WriteHists();

   drawOnlyOneEvent(m_eventsForED[0]);

   // TApplication app("app", &argc, argv);
   for (size_t nHist = 0; nHist < numOfED; nHist++) {
      m_hEventDisplays[nHist] = nullptr;
      m_hEventDisplays[nHist] = new TH3D(
         Form("hEventDisplays%zu", nHist), ";z [mm];x [mm]; y [mm]", 100, -5000, 5000, 100, -2000, 2000, 100, -2000, 2000
      );
   }
   drawEightEvents();


   for (int i = 0; i < numOfED; ++i) {
      m_hEventDisplays2D[i] = new TH2D(
         Form("hEventDisplay2D_%d", i),
         Form("Event %d;z [mm];x [mm]", i),
         100, -5000, 5000,
         100, -4000, 4000
      );
   }

   drawEightEvents2D_ZX();

   std::cout << "tempCount = " << tempCount << std::endl;
   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

   std::cout << "Number of noise events: " << numOfNoise << std::endl;
   std::cout << "Handled number of Events: " << numOfEventLoops << std::endl;

}

void McPsCheck::CountMcParticles(){
   for(size_t iMCP = 0; iMCP < MCParticles_; iMCP++){
      if(MCParticles_generatorStatus[iMCP] == 6004) m_NumOfEventsOfBKG->Fill(5);
      else if(MCParticles_generatorStatus[iMCP] == 5004) m_NumOfEventsOfBKG->Fill(4);
      else if(MCParticles_generatorStatus[iMCP] == 4004) m_NumOfEventsOfBKG->Fill(3);
      else if(MCParticles_generatorStatus[iMCP] == 3004) m_NumOfEventsOfBKG->Fill(2);
      else if(MCParticles_generatorStatus[iMCP] == 2004) m_NumOfEventsOfBKG->Fill(1);

   }
}


void McPsCheck::FillZRHitMaps(){

   bool bIsBkg[5] = {false, false, false, false, false};
   Int_t eachBkgHitCountTrk[5][17] = {};
   Int_t eachBkgHitCountCal[5][12] = {};
   
   for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
   for(size_t iHit = 0; iHit < VertexBarrelHits_; iHit++){
      Int_t pTagId = _VertexBarrelHits_particle_index[iHit];
      Double_t hitR = TMath::Sqrt(
         VertexBarrelHits_position_x[iHit] * VertexBarrelHits_position_x[iHit] +
         VertexBarrelHits_position_y[iHit] * VertexBarrelHits_position_y[iHit]
      );

      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(VertexBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[4][0]++;
         bIsBkg[4] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(VertexBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[3][0]++;
         bIsBkg[3] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(VertexBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[2][0]++;
         bIsBkg[2] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(VertexBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[1][0]++;
         bIsBkg[1] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(VertexBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[0][0]++;
         bIsBkg[0] = true;
      }      
   }
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(1);
      m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(1, eachBkgHitCountTrk[iBkg][0]);
   }


   for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
   for(size_t iHit = 0; iHit < SiBarrelHits_; iHit++){
      Int_t pTagId = _SiBarrelHits_particle_index[iHit];
      Double_t hitR = TMath::Sqrt(
         SiBarrelHits_position_x[iHit] * SiBarrelHits_position_x[iHit] +
         SiBarrelHits_position_y[iHit] * SiBarrelHits_position_y[iHit]
      );

      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(SiBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[4][1]++;
         bIsBkg[4] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(SiBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[3][1]++;
         bIsBkg[3] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(SiBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[2][1]++;
         bIsBkg[2] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(SiBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[1][1]++;
         bIsBkg[1] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(SiBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[0][1]++;
         bIsBkg[0] = true;
      }

   }
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(2);
      m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(2, eachBkgHitCountTrk[iBkg][1]);
   }


   for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
   for(size_t iHit = 0; iHit < TrackerEndcapHits_; iHit++){
      Int_t pTagId = _TrackerEndcapHits_particle_index[iHit];
      Double_t hitR = TMath::Sqrt(
         TrackerEndcapHits_position_x[iHit] * TrackerEndcapHits_position_x[iHit] +
         TrackerEndcapHits_position_y[iHit] * TrackerEndcapHits_position_y[iHit]
      );

      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(TrackerEndcapHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[4][2]++;
         bIsBkg[4] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(TrackerEndcapHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[3][2]++;
         bIsBkg[3] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(TrackerEndcapHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[2][2]++;
         bIsBkg[2] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(TrackerEndcapHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[1][2]++;
         bIsBkg[1] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(TrackerEndcapHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[0][2]++;
         bIsBkg[0] = true;
      }
   }
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(3);
      m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(3, eachBkgHitCountTrk[iBkg][2]);
   }


   for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
   for(size_t iHit = 0; iHit < MPGDBarrelHits_; iHit++){
      Int_t pTagId = _MPGDBarrelHits_particle_index[iHit];
      Double_t hitR = TMath::Sqrt(
         MPGDBarrelHits_position_x[iHit] * MPGDBarrelHits_position_x[iHit] +
         MPGDBarrelHits_position_y[iHit] * MPGDBarrelHits_position_y[iHit]
      );

      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(MPGDBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[4][3]++;
         bIsBkg[4] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(MPGDBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[3][3]++;
         bIsBkg[3] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(MPGDBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[2][3]++;
         bIsBkg[2] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(MPGDBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[1][3]++;
         bIsBkg[1] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(MPGDBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountTrk[0][3]++;
         bIsBkg[0] = true;
      }
   }
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(4);
      m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(4, eachBkgHitCountTrk[iBkg][3]);
   }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < OuterMPGDBarrelHits_; iHit++){
         Int_t pTagId = _OuterMPGDBarrelHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            OuterMPGDBarrelHits_position_x[iHit] * OuterMPGDBarrelHits_position_x[iHit] +
            OuterMPGDBarrelHits_position_y[iHit] * OuterMPGDBarrelHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(OuterMPGDBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][4]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(OuterMPGDBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][4]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(OuterMPGDBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[2][4]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(OuterMPGDBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][4]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(OuterMPGDBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][4]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(5);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(5, eachBkgHitCountTrk[iBkg][4]);
      }


      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < ForwardMPGDEndcapHits_; iHit++){
         Int_t pTagId = _ForwardMPGDEndcapHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            ForwardMPGDEndcapHits_position_x[iHit] * ForwardMPGDEndcapHits_position_x[iHit] +
            ForwardMPGDEndcapHits_position_y[iHit] * ForwardMPGDEndcapHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(ForwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][5]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(ForwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][5]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(ForwardMPGDEndcapHits_position_z[iHit], hitR);                
            eachBkgHitCountTrk[2][5]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(ForwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][5]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(ForwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][5]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(6);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(6, eachBkgHitCountTrk[iBkg][5]);
      }


      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < BackwardMPGDEndcapHits_; iHit++){
         Int_t pTagId = _BackwardMPGDEndcapHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            BackwardMPGDEndcapHits_position_x[iHit] * BackwardMPGDEndcapHits_position_x[iHit] +
            BackwardMPGDEndcapHits_position_y[iHit] * BackwardMPGDEndcapHits_position_y[iHit]
         );
         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(BackwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][6]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(BackwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][6]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(BackwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[2][6]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(BackwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][6]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(BackwardMPGDEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][6]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(7);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(7, eachBkgHitCountTrk[iBkg][6]);
      }

      
      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < TOFBarrelHits_; iHit++){
         Int_t pTagId = _TOFBarrelHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            TOFBarrelHits_position_x[iHit] * TOFBarrelHits_position_x[iHit] +
            TOFBarrelHits_position_y[iHit] * TOFBarrelHits_position_y[iHit]
         );
         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(TOFBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][7]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(TOFBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][7]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(TOFBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[2][7]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(TOFBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][7]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(TOFBarrelHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][7]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(8);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(8, eachBkgHitCountTrk[iBkg][7]);
      }


      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < TOFEndcapHits_; iHit++){
         Int_t pTagId = _TOFEndcapHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            TOFEndcapHits_position_x[iHit] * TOFEndcapHits_position_x[iHit] +
            TOFEndcapHits_position_y[iHit] * TOFEndcapHits_position_y[iHit]
         );
         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(TOFEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][8]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(TOFEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][8]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(TOFEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[2][8]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(TOFEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][8]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(TOFEndcapHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][8]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(9);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(9, eachBkgHitCountTrk[iBkg][8]);
      }


      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < B0TrackerHits_; iHit++){
         Int_t pTagId = _B0TrackerHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            B0TrackerHits_position_x[iHit] * B0TrackerHits_position_x[iHit] +
            B0TrackerHits_position_y[iHit] * B0TrackerHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(B0TrackerHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][9]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(B0TrackerHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][9]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(B0TrackerHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[2][9]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(B0TrackerHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][9]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(B0TrackerHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][9]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(10);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(10, eachBkgHitCountTrk[iBkg][9]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < DIRCBarHits_; iHit++){
         Int_t pTagId = _DIRCBarHits_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
            DIRCBarHits_position_x[iHit] * DIRCBarHits_position_x[iHit] +
            DIRCBarHits_position_y[iHit] * DIRCBarHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
            m_hZRHitRatio_All_BKG[4]->Fill(DIRCBarHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[4][10]++;
            bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
            m_hZRHitRatio_All_BKG[3]->Fill(DIRCBarHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[3][10]++;
            bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
            m_hZRHitRatio_All_BKG[2]->Fill(DIRCBarHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[2][10]++;
            bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
            m_hZRHitRatio_All_BKG[1]->Fill(DIRCBarHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[1][10]++;
            bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
            m_hZRHitRatio_All_BKG[0]->Fill(DIRCBarHits_position_z[iHit], hitR);
            eachBkgHitCountTrk[0][10]++;
            bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(11);
         m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(11, eachBkgHitCountTrk[iBkg][10]);
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
         for(size_t iHit = 0; iHit < DRICHHits_; iHit++){
            Int_t pTagId = _DRICHHits_particle_index[iHit];
            Double_t hitR = TMath::Sqrt(
               DRICHHits_position_x[iHit] * DRICHHits_position_x[iHit] +
               DRICHHits_position_y[iHit] * DRICHHits_position_y[iHit]
            );

            if(MCParticles_generatorStatus[pTagId] > 5999){
               m_hZRHitRatio_All_BKG[4]->Fill(DRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[4][11]++;
               bIsBkg[4] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 4999){
               m_hZRHitRatio_All_BKG[3]->Fill(DRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[3][11]++;
               bIsBkg[3] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 3999){
               m_hZRHitRatio_All_BKG[2]->Fill(DRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[2][11]++;
               bIsBkg[2] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 2999){
               m_hZRHitRatio_All_BKG[1]->Fill(DRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[1][11]++;
               bIsBkg[1] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 1999){
               m_hZRHitRatio_All_BKG[0]->Fill(DRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[0][11]++;
               bIsBkg[0] = true;
            }
         }
         for(size_t iBkg = 0; iBkg < 5; iBkg++){
            if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(12);
            m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(12, eachBkgHitCountTrk[iBkg][11]);
         }


         for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
         for(size_t iHit = 0; iHit < ForwardOffMTrackerHits_; iHit++){
            Int_t pTagId = _ForwardOffMTrackerHits_particle_index[iHit];
            Double_t hitR = TMath::Sqrt(
               ForwardOffMTrackerHits_position_x[iHit] * ForwardOffMTrackerHits_position_x[iHit] +
               ForwardOffMTrackerHits_position_y[iHit] * ForwardOffMTrackerHits_position_y[iHit]
            );

            if(MCParticles_generatorStatus[pTagId] > 5999){
               m_hZRHitRatio_All_BKG[4]->Fill(ForwardOffMTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[4][12]++;
               bIsBkg[4] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 4999){
               m_hZRHitRatio_All_BKG[3]->Fill(ForwardOffMTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[3][12]++;
               bIsBkg[3] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 3999){
               m_hZRHitRatio_All_BKG[2]->Fill(ForwardOffMTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[2][12]++;
               bIsBkg[2] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 2999){
               m_hZRHitRatio_All_BKG[1]->Fill(ForwardOffMTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[1][12]++;
               bIsBkg[1] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 1999){
               m_hZRHitRatio_All_BKG[0]->Fill(ForwardOffMTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[0][12]++;
               bIsBkg[0] = true;
            }
         }
         for(size_t iBkg = 0; iBkg < 5; iBkg++){
            if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(13);
            m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(13, eachBkgHitCountTrk[iBkg][12]);
         }

         for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
         for(size_t iHit = 0; iHit < ForwardRomanPotHits_; iHit++){
            Int_t pTagId = _ForwardRomanPotHits_particle_index[iHit];
            Double_t hitR = TMath::Sqrt(
               ForwardRomanPotHits_position_x[iHit] * ForwardRomanPotHits_position_x[iHit] +
               ForwardRomanPotHits_position_y[iHit] * ForwardRomanPotHits_position_y[iHit]
            );

            if(MCParticles_generatorStatus[pTagId] > 5999){
               m_hZRHitRatio_All_BKG[4]->Fill(ForwardRomanPotHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[4][13]++;
               bIsBkg[4] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 4999){
               m_hZRHitRatio_All_BKG[3]->Fill(ForwardRomanPotHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[3][13]++;
               bIsBkg[3] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 3999){
               m_hZRHitRatio_All_BKG[2]->Fill(ForwardRomanPotHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[2][13]++;
               bIsBkg[2] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 2999){
               m_hZRHitRatio_All_BKG[1]->Fill(ForwardRomanPotHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[1][13]++;
               bIsBkg[1] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 1999){
               m_hZRHitRatio_All_BKG[0]->Fill(ForwardRomanPotHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[0][13]++;
               bIsBkg[0] = true;
            }
         }
         for(size_t iBkg = 0; iBkg < 5; iBkg++){
            if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(14);
            m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(14, eachBkgHitCountTrk[iBkg][13]);
         }


         for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
         for(size_t iHit = 0; iHit < LumiSpecTrackerHits_; iHit++){
            Int_t pTagId = _LumiSpecTrackerHits_particle_index[iHit];
            Double_t hitR = TMath::Sqrt(
               LumiSpecTrackerHits_position_x[iHit] * LumiSpecTrackerHits_position_x[iHit] +
               LumiSpecTrackerHits_position_y[iHit] * LumiSpecTrackerHits_position_y[iHit]
            );

            if(MCParticles_generatorStatus[pTagId] > 5999){
               m_hZRHitRatio_All_BKG[4]->Fill(LumiSpecTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[4][14]++;
               bIsBkg[4] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 4999){
               m_hZRHitRatio_All_BKG[3]->Fill(LumiSpecTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[3][14]++;
               bIsBkg[3] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 3999){
               m_hZRHitRatio_All_BKG[2]->Fill(LumiSpecTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[2][14]++;
               bIsBkg[2] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 2999){
               m_hZRHitRatio_All_BKG[1]->Fill(LumiSpecTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[1][14]++;
               bIsBkg[1] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 1999){
               m_hZRHitRatio_All_BKG[0]->Fill(LumiSpecTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[0][14]++;
               bIsBkg[0] = true;
            }
         }
         for(size_t iBkg = 0; iBkg < 5; iBkg++){
            if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(15);
            m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(15, eachBkgHitCountTrk[iBkg][14]);
         }

         for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
         for(size_t iHit = 0; iHit < PFRICHHits_; iHit++){
            Int_t pTagId = _PFRICHHits_particle_index[iHit];
            Double_t hitR = TMath::Sqrt(
               PFRICHHits_position_x[iHit] * PFRICHHits_position_x[iHit] +
               PFRICHHits_position_y[iHit] * PFRICHHits_position_y[iHit]
            );

            if(MCParticles_generatorStatus[pTagId] > 5999){
               m_hZRHitRatio_All_BKG[4]->Fill(PFRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[4][15]++;
               bIsBkg[4] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 4999){
               m_hZRHitRatio_All_BKG[3]->Fill(PFRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[3][15]++;
               bIsBkg[3] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 3999){
               m_hZRHitRatio_All_BKG[2]->Fill(PFRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[2][15]++;
               bIsBkg[2] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 2999){
               m_hZRHitRatio_All_BKG[1]->Fill(PFRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[1][15]++;
               bIsBkg[1] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 1999){
               m_hZRHitRatio_All_BKG[0]->Fill(PFRICHHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[0][15]++;
               bIsBkg[0] = true;
            }
         }
         for(size_t iBkg = 0; iBkg < 5; iBkg++){
            if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(16);
            m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(16, eachBkgHitCountTrk[iBkg][15]);
         }

         for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
         for(size_t iHit = 0; iHit < TaggerTrackerHits_; iHit++){
            Int_t pTagId = _TaggerTrackerHits_particle_index[iHit];
            Double_t hitR = TMath::Sqrt(
               TaggerTrackerHits_position_x[iHit] * TaggerTrackerHits_position_x[iHit] +
               TaggerTrackerHits_position_y[iHit] * TaggerTrackerHits_position_y[iHit]
            );

            if(MCParticles_generatorStatus[pTagId] > 5999){
               m_hZRHitRatio_All_BKG[4]->Fill(TaggerTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[4][16]++;
               bIsBkg[4] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 4999){
               m_hZRHitRatio_All_BKG[3]->Fill(TaggerTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[3][16]++;
               bIsBkg[3] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 3999){
               m_hZRHitRatio_All_BKG[2]->Fill(TaggerTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[2][16]++;
               bIsBkg[2] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 2999){
               m_hZRHitRatio_All_BKG[1]->Fill(TaggerTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[1][16]++;
               bIsBkg[1] = true;
            }else if(MCParticles_generatorStatus[pTagId] > 1999){
               m_hZRHitRatio_All_BKG[0]->Fill(TaggerTrackerHits_position_z[iHit], hitR);
               eachBkgHitCountTrk[0][16]++;
               bIsBkg[0] = true;
            }
         }
         for(size_t iBkg = 0; iBkg < 5; iBkg++){
            if(bIsBkg[iBkg]) m_EveCountWithDetHits_Trk_BKG[iBkg] ->Fill(17);
            m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Fill(17, eachBkgHitCountTrk[iBkg][16]);
         }


   // Calorimeter contributions: use contribution indices and Cal histograms
   for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
   for(size_t iHit = 0; iHit < B0ECalHits_; iHit++){
      Int_t pTagId = _B0ECalHitsContributions_particle_index[iHit];
      Double_t hitR = TMath::Sqrt(
         B0ECalHits_position_x[iHit] * B0ECalHits_position_x[iHit] +
         B0ECalHits_position_y[iHit] * B0ECalHits_position_y[iHit]
      );

      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(B0ECalHits_position_z[iHit], hitR);
         bIsBkg[4] = true;
         eachBkgHitCountCal[4][0]++;
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(B0ECalHits_position_z[iHit], hitR);
         bIsBkg[3] = true;
         eachBkgHitCountCal[3][0]++;
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(B0ECalHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][0]++;
         bIsBkg[2] = true;
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(B0ECalHits_position_z[iHit], hitR);
         bIsBkg[1] = true;
         eachBkgHitCountCal[1][0]++;
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(B0ECalHits_position_z[iHit], hitR);
         bIsBkg[0] = true;
         eachBkgHitCountCal[0][0]++;
      }

   }
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(1);
      m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(1, eachBkgHitCountCal[iBkg][0]);
   }


      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < EcalBarrelImagingHits_; iHit++){
         Int_t pTagId = _EcalBarrelImagingHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         EcalBarrelImagingHits_position_x[iHit] * EcalBarrelImagingHits_position_x[iHit] +
         EcalBarrelImagingHits_position_y[iHit] * EcalBarrelImagingHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(EcalBarrelImagingHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][1]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(EcalBarrelImagingHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][1]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(EcalBarrelImagingHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][1]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(EcalBarrelImagingHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][1]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(EcalBarrelImagingHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][1]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(2);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(2, eachBkgHitCountCal[iBkg][1]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < EcalBarrelScFiHits_; iHit++){
         Int_t pTagId = _EcalBarrelScFiHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         EcalBarrelScFiHits_position_x[iHit] * EcalBarrelScFiHits_position_x[iHit] +
         EcalBarrelScFiHits_position_y[iHit] * EcalBarrelScFiHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(EcalBarrelScFiHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][2]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(EcalBarrelScFiHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][2]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(EcalBarrelScFiHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][2]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(EcalBarrelScFiHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][2]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(EcalBarrelScFiHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][2]++;
         bIsBkg[0] = true;
         }
         
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(3);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(3, eachBkgHitCountCal[iBkg][2]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < EcalEndcapNHits_; iHit++){
         Int_t pTagId = _EcalEndcapNHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         EcalEndcapNHits_position_x[iHit] * EcalEndcapNHits_position_x[iHit] +
         EcalEndcapNHits_position_y[iHit] * EcalEndcapNHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(EcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][3]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(EcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][3]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(EcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][3]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(EcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][3]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(EcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][3]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(4);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(4, eachBkgHitCountCal[iBkg][3]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < EcalEndcapPHits_; iHit++){
         Int_t pTagId = _EcalEndcapPHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         EcalEndcapPHits_position_x[iHit] * EcalEndcapPHits_position_x[iHit] +
         EcalEndcapPHits_position_y[iHit] * EcalEndcapPHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(EcalEndcapPHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][4]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(EcalEndcapPHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][4]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(EcalEndcapPHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][4]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(EcalEndcapPHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][4]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(EcalEndcapPHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][4]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(5);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(5, eachBkgHitCountCal[iBkg][4]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < EcalFarForwardZDCHits_; iHit++){
         Int_t pTagId = _EcalFarForwardZDCHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         EcalFarForwardZDCHits_position_x[iHit] * EcalFarForwardZDCHits_position_x[iHit] +
         EcalFarForwardZDCHits_position_y[iHit] * EcalFarForwardZDCHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(EcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][5]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(EcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][5]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(EcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][5]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(EcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][5]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(EcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][5]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(6);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(6, eachBkgHitCountCal[iBkg][5]);
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < EcalLumiSpecHits_; iHit++){
         Int_t pTagId = _EcalLumiSpecHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         EcalLumiSpecHits_position_x[iHit] * EcalLumiSpecHits_position_x[iHit] +
         EcalLumiSpecHits_position_y[iHit] * EcalLumiSpecHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(EcalLumiSpecHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][6]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(EcalLumiSpecHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][6]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(EcalLumiSpecHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][6]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(EcalLumiSpecHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][6]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(EcalLumiSpecHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][6]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(7);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(7, eachBkgHitCountCal[iBkg][6]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < HcalBarrelHits_; iHit++){
         Int_t pTagId = _HcalBarrelHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         HcalBarrelHits_position_x[iHit] * HcalBarrelHits_position_x[iHit] +
         HcalBarrelHits_position_y[iHit] * HcalBarrelHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(HcalBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][7]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(HcalBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][7]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(HcalBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][7]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(HcalBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][7]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(HcalBarrelHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][7]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(8);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(8, eachBkgHitCountCal[iBkg][7]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < HcalEndcapNHits_; iHit++){
         Int_t pTagId = _HcalEndcapNHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         HcalEndcapNHits_position_x[iHit] * HcalEndcapNHits_position_x[iHit] +
         HcalEndcapNHits_position_y[iHit] * HcalEndcapNHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(HcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][8]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(HcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][8]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(HcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][8]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(HcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][8]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(HcalEndcapNHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][8]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(9);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(9, eachBkgHitCountCal[iBkg][8]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < HcalEndcapPInsertHits_; iHit++){
         Int_t pTagId = _HcalEndcapPInsertHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         HcalEndcapPInsertHits_position_x[iHit] * HcalEndcapPInsertHits_position_x[iHit] +
         HcalEndcapPInsertHits_position_y[iHit] * HcalEndcapPInsertHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(HcalEndcapPInsertHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][9]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(HcalEndcapPInsertHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][9]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(HcalEndcapPInsertHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][9]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(HcalEndcapPInsertHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][9]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(HcalEndcapPInsertHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][9]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(10);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(10, eachBkgHitCountCal[iBkg][9]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < HcalFarForwardZDCHits_; iHit++){
         Int_t pTagId = _HcalFarForwardZDCHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         HcalFarForwardZDCHits_position_x[iHit] * HcalFarForwardZDCHits_position_x[iHit] +
         HcalFarForwardZDCHits_position_y[iHit] * HcalFarForwardZDCHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(HcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][10]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(HcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][10]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(HcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][10]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(HcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][10]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(HcalFarForwardZDCHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][10]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(11);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(11, eachBkgHitCountCal[iBkg][10]);
      }

      for(size_t iBkg = 0; iBkg < 5; iBkg++) bIsBkg[iBkg] = false;
      for(size_t iHit = 0; iHit < LFHCALHits_; iHit++){
         Int_t pTagId = _LFHCALHitsContributions_particle_index[iHit];
         Double_t hitR = TMath::Sqrt(
         LFHCALHits_position_x[iHit] * LFHCALHits_position_x[iHit] +
         LFHCALHits_position_y[iHit] * LFHCALHits_position_y[iHit]
         );

         if(MCParticles_generatorStatus[pTagId] > 5999){
         m_hZRHitRatio_All_BKG[4]->Fill(LFHCALHits_position_z[iHit], hitR);
         eachBkgHitCountCal[4][11]++;
         bIsBkg[4] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_hZRHitRatio_All_BKG[3]->Fill(LFHCALHits_position_z[iHit], hitR);
         eachBkgHitCountCal[3][11]++;
         bIsBkg[3] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_hZRHitRatio_All_BKG[2]->Fill(LFHCALHits_position_z[iHit], hitR);
         eachBkgHitCountCal[2][11]++;
         bIsBkg[2] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_hZRHitRatio_All_BKG[1]->Fill(LFHCALHits_position_z[iHit], hitR);
         eachBkgHitCountCal[1][11]++;
         bIsBkg[1] = true;
         }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_hZRHitRatio_All_BKG[0]->Fill(LFHCALHits_position_z[iHit], hitR);
         eachBkgHitCountCal[0][11]++;
         bIsBkg[0] = true;
         }
      }
      for(size_t iBkg = 0; iBkg < 5; iBkg++){
         if(bIsBkg[iBkg]) m_EveCountWithDetHits_Cal_BKG[iBkg] ->Fill(12);
         m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Fill(12, eachBkgHitCountCal[iBkg][11]);
      }


}



void McPsCheck::countTrkDetHits(){
   // std::cout << "VertexBarrelHits_ = " << VertexBarrelHits_ << ", SiBarrelHits_ = " << SiBarrelHits_ << ", B0TrackerHits_ = " << B0TrackerHits_ << ", TrackerEndcapHits_ = " << TrackerEndcapHits_ << ", ForwardOffMTrackerHits_ = " << ForwardOffMTrackerHits_ << ", MPGDBarrelHits_ = " << MPGDBarrelHits_ << std::endl;  // ChecKuma

   // for(size_t iVtxHitP = 0; iVtxHitP < _VertexBarrelHits_particle_; iVtxHitP++){
   //    Int_t iMcP = _VertexBarrelHits_particle_index[iVtxHitP];
   //    std::cout << "iMcP : " << iMcP << ": MCParticles_generatorStatus = " << MCParticles_generatorStatus[iMcP] << ", PID = " << MCParticles_PDG[iMcP] << std::endl;  // ChecKuma

   // }


   if(VertexBarrelHits_){
      numOfEventsForEachTrkDet[0]++;
      m_EveCountWithDetHits_Trk->Fill(1);
      m_HitsPerEveWithDetHits_Trk->Fill(VertexBarrelHits_);
   }

   if(SiBarrelHits_){
      numOfEventsForEachTrkDet[1]++;
      m_EveCountWithDetHits_Trk->Fill(2);
      m_HitsPerEveWithDetHits_Trk->Fill(SiBarrelHits_);
   }

   if(TrackerEndcapHits_){
      numOfEventsForEachTrkDet[2]++;
      m_EveCountWithDetHits_Trk->Fill(3);
      m_HitsPerEveWithDetHits_Trk->Fill(TrackerEndcapHits_);
   }

   if(MPGDBarrelHits_){
      numOfEventsForEachTrkDet[3]++;
      m_EveCountWithDetHits_Trk->Fill(4);
      m_HitsPerEveWithDetHits_Trk->Fill(MPGDBarrelHits_);
   }

   if(OuterMPGDBarrelHits_){
      numOfEventsForEachTrkDet[4]++;
      m_EveCountWithDetHits_Trk->Fill(5);
      m_HitsPerEveWithDetHits_Trk->Fill(OuterMPGDBarrelHits_);
   }

   if(ForwardMPGDEndcapHits_){
      numOfEventsForEachTrkDet[5]++;
      m_EveCountWithDetHits_Trk->Fill(6);
      m_HitsPerEveWithDetHits_Trk->Fill(ForwardMPGDEndcapHits_);
   }

   if(BackwardMPGDEndcapHits_){
      numOfEventsForEachTrkDet[6]++;
      m_EveCountWithDetHits_Trk->Fill(7);
      m_HitsPerEveWithDetHits_Trk->Fill(BackwardMPGDEndcapHits_);
   }

   if(TOFBarrelHits_){
      numOfEventsForEachTrkDet[7]++;
      m_EveCountWithDetHits_Trk->Fill(8);
      m_HitsPerEveWithDetHits_Trk->Fill(TOFBarrelHits_);
   }

   if(TOFEndcapHits_){
      numOfEventsForEachTrkDet[8]++;
      m_EveCountWithDetHits_Trk->Fill(9);
      m_HitsPerEveWithDetHits_Trk->Fill(TOFEndcapHits_);
   }

   if(B0TrackerHits_){
      numOfEventsForEachTrkDet[9]++;
      m_EveCountWithDetHits_Trk->Fill(10);
      m_HitsPerEveWithDetHits_Trk->Fill(B0TrackerHits_);
   }

   if(DIRCBarHits_){
      numOfEventsForEachTrkDet[10]++;
      m_EveCountWithDetHits_Trk->Fill(11);
      m_HitsPerEveWithDetHits_Trk->Fill(DIRCBarHits_);
   }

   if(DRICHHits_){
      numOfEventsForEachTrkDet[11]++;
      m_EveCountWithDetHits_Trk->Fill(12);
      m_HitsPerEveWithDetHits_Trk->Fill(DRICHHits_);
   }

   if(ForwardOffMTrackerHits_){
      numOfEventsForEachTrkDet[12]++;
      m_EveCountWithDetHits_Trk->Fill(13);
      m_HitsPerEveWithDetHits_Trk->Fill(ForwardOffMTrackerHits_);
   }

   if(ForwardRomanPotHits_){
      numOfEventsForEachTrkDet[13]++;
      m_EveCountWithDetHits_Trk->Fill(14);
      m_HitsPerEveWithDetHits_Trk->Fill(ForwardRomanPotHits_);
   }

   if(LumiSpecTrackerHits_){
      numOfEventsForEachTrkDet[14]++;
      m_EveCountWithDetHits_Trk->Fill(15);
      m_HitsPerEveWithDetHits_Trk->Fill(LumiSpecTrackerHits_);
   }

   if(PFRICHHits_){
      numOfEventsForEachTrkDet[15]++;
      m_EveCountWithDetHits_Trk->Fill(16);
      m_HitsPerEveWithDetHits_Trk->Fill(PFRICHHits_);
   }

   if(TaggerTrackerHits_){
      numOfEventsForEachTrkDet[16]++;
      m_EveCountWithDetHits_Trk->Fill(17);
      m_HitsPerEveWithDetHits_Trk->Fill(TaggerTrackerHits_);
   }

}


void McPsCheck::countCalDetHits(){
   if(B0ECalHits_){
      numOfEventsForEachCalDet[0]++;
      m_EveCountWithDetHits_Cal->Fill(1);
      m_HitsPerEveWithDetHits_Cal->Fill(B0ECalHits_);
   }

   if(EcalBarrelImagingHits_){
      numOfEventsForEachCalDet[1]++;
      m_EveCountWithDetHits_Cal->Fill(2);
      m_HitsPerEveWithDetHits_Cal->Fill(EcalBarrelImagingHits_);
   }

   if(EcalBarrelScFiHits_){
      numOfEventsForEachCalDet[2]++;
      m_EveCountWithDetHits_Cal->Fill(3);
      m_HitsPerEveWithDetHits_Cal->Fill(EcalBarrelScFiHits_);
   }

   if(EcalEndcapNHits_){
      numOfEventsForEachCalDet[3]++;
      m_EveCountWithDetHits_Cal->Fill(4);
      m_HitsPerEveWithDetHits_Cal->Fill(EcalEndcapNHits_);
   }

   if(EcalEndcapPHits_){
      numOfEventsForEachCalDet[4]++;
      m_EveCountWithDetHits_Cal->Fill(5);
      m_HitsPerEveWithDetHits_Cal->Fill(EcalEndcapPHits_);
   }

   if(EcalFarForwardZDCHits_){
      numOfEventsForEachCalDet[5]++;
      m_EveCountWithDetHits_Cal->Fill(6);
      m_HitsPerEveWithDetHits_Cal->Fill(EcalFarForwardZDCHits_);
   }

   if(EcalLumiSpecHits_){
      numOfEventsForEachCalDet[6]++;
      m_EveCountWithDetHits_Cal->Fill(7);
      m_HitsPerEveWithDetHits_Cal->Fill(EcalLumiSpecHits_);
   }

   if(HcalBarrelHits_){
      numOfEventsForEachCalDet[7]++;
      m_EveCountWithDetHits_Cal->Fill(8);
      m_HitsPerEveWithDetHits_Cal->Fill(HcalBarrelHits_);
   }

   if(HcalEndcapNHits_){
      numOfEventsForEachCalDet[8]++;
      m_EveCountWithDetHits_Cal->Fill(9);
      m_HitsPerEveWithDetHits_Cal->Fill(HcalEndcapNHits_);
   }

   if(HcalEndcapPInsertHits_){
      numOfEventsForEachCalDet[9]++;
      m_EveCountWithDetHits_Cal->Fill(10);
      m_HitsPerEveWithDetHits_Cal->Fill(HcalEndcapPInsertHits_);
   }

   if(HcalFarForwardZDCHits_){
      numOfEventsForEachCalDet[10]++;
      m_EveCountWithDetHits_Cal->Fill(11);
      m_HitsPerEveWithDetHits_Cal->Fill(HcalFarForwardZDCHits_);
   }

   if(LFHCALHits_){
      numOfEventsForEachCalDet[11]++;
      m_EveCountWithDetHits_Cal->Fill(12);
      m_HitsPerEveWithDetHits_Cal->Fill(LFHCALHits_);
   }

}

// === s === For Event Display =========== #########################################################
void McPsCheck::recordMCPsForED(){
   bool speID = true;  // special ID for checking the contribution of specific particles, e.g. beam background particles with ID > 1999 and < 3000, or primary particles with ID = 1 or 2. Set to false to disable this special ID check and include all particles regardless of their ID.
   Event ev;

   // std::cout << "MCParticles_ =  " << MCParticles_ << std::endl;

   for (size_t i = 0; i < MCParticles_; ++i) {

      // == s == Particle Selection  #############################################
      // if(MCParticles_generatorStatus[i] != 1 && MCParticles_generatorStatus[i] != 2) continue;
      // if(MCParticles_generatorStatus[i] > 1999) continue;
      // bool bBkgParent = false;
      // for (size_t iParent = MCParticles_parents_begin[i]; iParent < MCParticles_parents_end[i]; ++iParent) {
      //    if(MCParticles_generatorStatus[iParent] < 1999){
      //       bBkgParent = true;
      //       break;
      //    }
      // }
      // if(bBkgParent) continue;
      // == e == Particle Selection  #############################################

      if((MCParticles_generatorStatus[i] < 1999 || MCParticles_generatorStatus[i] > 2999)) continue;
      // if(1) continue;

      Particle p;
      p.vertex = {MCParticles_vertex_x[i], MCParticles_vertex_y[i], MCParticles_vertex_z[i]};
      p.momentum = {MCParticles_momentum_x[i], MCParticles_momentum_y[i], MCParticles_momentum_z[i]};
      p.pdg = MCParticles_PDG[i];
      p.charge = MCParticles_charge[i];
      p.hasEndpoint = true;
      p.endpoint = {MCParticles_endpoint_x[i], MCParticles_endpoint_y[i], MCParticles_endpoint_z[i]};


      ev.particles.push_back(p);
   }
   m_eventsForED.push_back(ev);
}

void McPsCheck::recordTrkHitsForED(){
  std::vector<std::vector<Vec3> > vTrkDetsHits;

   bool speID = true;  // special ID for checking the contribution of specific particles, e.g. beam background particles with ID > 1999 and < 3000, or primary particles with ID = 1 or 2. Set to false to disable this special ID check and include all hits regardless of their contributing particle's ID.
   std::vector<Vec3> vVertexBarrelHits;
   for(size_t iHit = 0; iHit < VertexBarrelHits_; iHit++){
      if( (MCParticles_generatorStatus[_VertexBarrelHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_VertexBarrelHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {VertexBarrelHits_position_x[iHit], VertexBarrelHits_position_y[iHit], VertexBarrelHits_position_z[iHit]};
      vVertexBarrelHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vVertexBarrelHits);


   std::vector<Vec3> vSiBarrelHits;
   for(size_t iHit = 0; iHit < SiBarrelHits_; iHit++){
      if( (MCParticles_generatorStatus[_SiBarrelHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_SiBarrelHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {SiBarrelHits_position_x[iHit], SiBarrelHits_position_y[iHit], SiBarrelHits_position_z[iHit]};
      vSiBarrelHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vSiBarrelHits);

   std::vector<Vec3> vTrackerEndcapHits;
   for(size_t iHit = 0; iHit < TrackerEndcapHits_; iHit++){
      if( (MCParticles_generatorStatus[_TrackerEndcapHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_TrackerEndcapHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {TrackerEndcapHits_position_x[iHit], TrackerEndcapHits_position_y[iHit], TrackerEndcapHits_position_z[iHit]};
      vTrackerEndcapHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vTrackerEndcapHits);


   std::vector<Vec3> vMPGDBarrelHits;
   for(size_t iHit = 0; iHit < MPGDBarrelHits_; iHit++){
      if( (MCParticles_generatorStatus[_MPGDBarrelHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_MPGDBarrelHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {MPGDBarrelHits_position_x[iHit], MPGDBarrelHits_position_y[iHit], MPGDBarrelHits_position_z[iHit]};
      vMPGDBarrelHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vMPGDBarrelHits);


   std::vector<Vec3> vOuterMPGDBarrelHits;
   for(size_t iHit = 0; iHit < OuterMPGDBarrelHits_; iHit++){
      if( (MCParticles_generatorStatus[_OuterMPGDBarrelHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_OuterMPGDBarrelHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {OuterMPGDBarrelHits_position_x[iHit], OuterMPGDBarrelHits_position_y[iHit], OuterMPGDBarrelHits_position_z[iHit]};
      vOuterMPGDBarrelHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vOuterMPGDBarrelHits);
   

   std::vector<Vec3> vForwardMPGDEndcapHits;
   for(size_t iHit = 0; iHit < ForwardMPGDEndcapHits_; iHit++){
      if( (MCParticles_generatorStatus[_ForwardMPGDEndcapHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_ForwardMPGDEndcapHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {ForwardMPGDEndcapHits_position_x[iHit], ForwardMPGDEndcapHits_position_y[iHit], ForwardMPGDEndcapHits_position_z[iHit]};
      vForwardMPGDEndcapHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vForwardMPGDEndcapHits);
   

   std::vector<Vec3> vBackwardMPGDEndcapHits;
   for(size_t iHit = 0; iHit < BackwardMPGDEndcapHits_; iHit++){
      if( (MCParticles_generatorStatus[_BackwardMPGDEndcapHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_BackwardMPGDEndcapHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {BackwardMPGDEndcapHits_position_x[iHit], BackwardMPGDEndcapHits_position_y[iHit], BackwardMPGDEndcapHits_position_z[iHit]};
      vBackwardMPGDEndcapHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vBackwardMPGDEndcapHits);
   

   std::vector<Vec3> vTOFBarrelHits;
   for(size_t iHit = 0; iHit < TOFBarrelHits_; iHit++){
      if( (MCParticles_generatorStatus[_TOFBarrelHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_TOFBarrelHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {TOFBarrelHits_position_x[iHit], TOFBarrelHits_position_y[iHit], TOFBarrelHits_position_z[iHit]};
      vTOFBarrelHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vTOFBarrelHits);



   std::vector<Vec3> vTOFEndcapHits;
   for(size_t iHit = 0; iHit < TOFEndcapHits_; iHit++){
      if( (MCParticles_generatorStatus[_TOFEndcapHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_TOFEndcapHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {TOFEndcapHits_position_x[iHit], TOFEndcapHits_position_y[iHit], TOFEndcapHits_position_z[iHit]};
      vTOFEndcapHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vTOFEndcapHits);


   std::vector<Vec3> vB0TrackerHits;
   for(size_t iHit = 0; iHit < B0TrackerHits_; iHit++){
      if( (MCParticles_generatorStatus[_B0TrackerHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_B0TrackerHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {B0TrackerHits_position_x[iHit], B0TrackerHits_position_y[iHit], B0TrackerHits_position_z[iHit]};
      vB0TrackerHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vB0TrackerHits);


   std::vector<Vec3> vDIRCBarHits;
   for(size_t iHit = 0; iHit < DIRCBarHits_; iHit++){
      if( (MCParticles_generatorStatus[_DIRCBarHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_DIRCBarHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {DIRCBarHits_position_x[iHit], DIRCBarHits_position_y[iHit], DIRCBarHits_position_z[iHit]};
      vDIRCBarHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vDIRCBarHits);


   std::vector<Vec3> vDRICHHits;
   for(size_t iHit = 0; iHit < DRICHHits_; iHit++){
      if( (MCParticles_generatorStatus[_DRICHHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_DRICHHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {DRICHHits_position_x[iHit], DRICHHits_position_y[iHit], DRICHHits_position_z[iHit]};
      vDRICHHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vDRICHHits);


   std::vector<Vec3> vForwardOffMTrackerHits;
   for(size_t iHit = 0; iHit < ForwardOffMTrackerHits_; iHit++){
      if( (MCParticles_generatorStatus[_ForwardOffMTrackerHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_ForwardOffMTrackerHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {ForwardOffMTrackerHits_position_x[iHit], ForwardOffMTrackerHits_position_y[iHit], ForwardOffMTrackerHits_position_z[iHit]};
      vForwardOffMTrackerHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vForwardOffMTrackerHits);


   std::vector<Vec3> vForwardRomanPotHits;
   for(size_t iHit = 0; iHit < ForwardRomanPotHits_; iHit++){
      if( (MCParticles_generatorStatus[_ForwardRomanPotHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_ForwardRomanPotHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {ForwardRomanPotHits_position_x[iHit], ForwardRomanPotHits_position_y[iHit], ForwardRomanPotHits_position_z[iHit]};
      vForwardRomanPotHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vForwardRomanPotHits);


   std::vector<Vec3> vLumiSpecTrackerHits;
   for(size_t iHit = 0; iHit < LumiSpecTrackerHits_; iHit++){
      if( (MCParticles_generatorStatus[_LumiSpecTrackerHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_LumiSpecTrackerHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {LumiSpecTrackerHits_position_x[iHit], LumiSpecTrackerHits_position_y[iHit], LumiSpecTrackerHits_position_z[iHit]};
      vLumiSpecTrackerHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vLumiSpecTrackerHits);

   std::vector<Vec3> vPFRICHHits;
   for(size_t iHit = 0; iHit < PFRICHHits_; iHit++){
      if( (MCParticles_generatorStatus[_PFRICHHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_PFRICHHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {PFRICHHits_position_x[iHit], PFRICHHits_position_y[iHit], PFRICHHits_position_z[iHit]};
      vPFRICHHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vPFRICHHits);


   std::vector<Vec3> vTaggerTrackerHits;
   for(size_t iHit = 0; iHit < TaggerTrackerHits_; iHit++){
      if( (MCParticles_generatorStatus[_TaggerTrackerHits_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_TaggerTrackerHits_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {TaggerTrackerHits_position_x[iHit], TaggerTrackerHits_position_y[iHit], TaggerTrackerHits_position_z[iHit]};
      vTaggerTrackerHits.push_back(hitPos);
   }
   vTrkDetsHits.push_back(vTaggerTrackerHits);

   m_vRecordedTrkDetHits.push_back(vTrkDetsHits);
}

void McPsCheck::recordCalHitsForED(){
   bool speID = false;  // special ID for checking the contribution of specific particles, e.g. beam background particles with ID > 1999 and < 3000, or primary particles with ID = 1 or 2. Set to false to disable this special ID check and include all particles regardless of their ID.

   std::vector<std::vector<Vec3> > vCalDetsHits;
   std::vector<Vec3> vB0ECalHits;
   for(size_t iHit = 0; iHit < B0ECalHits_; iHit++){
      if( (MCParticles_generatorStatus[_B0ECalHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_B0ECalHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {B0ECalHits_position_x[iHit], B0ECalHits_position_y[iHit], B0ECalHits_position_z[iHit]};
      vB0ECalHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vB0ECalHits);

   std::vector<Vec3> vEcalBarrelImagingHits;
   for(size_t iHit = 0; iHit < EcalBarrelImagingHits_; iHit++){
      if( (MCParticles_generatorStatus[_EcalBarrelImagingHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_EcalBarrelImagingHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {EcalBarrelImagingHits_position_x[iHit], EcalBarrelImagingHits_position_y[iHit], EcalBarrelImagingHits_position_z[iHit]};
      vEcalBarrelImagingHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vEcalBarrelImagingHits);

   std::vector<Vec3> vEcalBarrelScFiHits;
   for(size_t iHit = 0; iHit < EcalBarrelScFiHits_; iHit++){
      if( (MCParticles_generatorStatus[_EcalBarrelScFiHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_EcalBarrelScFiHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {EcalBarrelScFiHits_position_x[iHit], EcalBarrelScFiHits_position_y[iHit], EcalBarrelScFiHits_position_z[iHit]};
      vEcalBarrelScFiHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vEcalBarrelScFiHits);


   std::vector<Vec3> vEcalEndcapNHits;
   for(size_t iHit = 0; iHit < EcalEndcapNHits_; iHit++){
      if( (MCParticles_generatorStatus[_EcalEndcapNHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_EcalEndcapNHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {EcalEndcapNHits_position_x[iHit], EcalEndcapNHits_position_y[iHit], EcalEndcapNHits_position_z[iHit]};
      vEcalEndcapNHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vEcalEndcapNHits);

   std::vector<Vec3> vEcalEndcapPHits;
   for(size_t iHit = 0; iHit < EcalEndcapPHits_; iHit++){
      if( (MCParticles_generatorStatus[_EcalEndcapPHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_EcalEndcapPHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {EcalEndcapPHits_position_x[iHit], EcalEndcapPHits_position_y[iHit], EcalEndcapPHits_position_z[iHit]};
      vEcalEndcapPHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vEcalEndcapPHits);

   std::vector<Vec3> vEcalFarForwardZDCHits;
   for(size_t iHit = 0; iHit < EcalFarForwardZDCHits_; iHit++){
      if( (MCParticles_generatorStatus[_EcalFarForwardZDCHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_EcalFarForwardZDCHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {EcalFarForwardZDCHits_position_x[iHit], EcalFarForwardZDCHits_position_y[iHit], EcalFarForwardZDCHits_position_z[iHit]};
      vEcalFarForwardZDCHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vEcalFarForwardZDCHits);

   std::vector<Vec3> vEcalLumiSpecHits;
   for(size_t iHit = 0; iHit < EcalLumiSpecHits_; iHit++){
      if( (MCParticles_generatorStatus[_EcalLumiSpecHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_EcalLumiSpecHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {EcalLumiSpecHits_position_x[iHit], EcalLumiSpecHits_position_y[iHit], EcalLumiSpecHits_position_z[iHit]};
      vEcalLumiSpecHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vEcalLumiSpecHits);


   std::vector<Vec3> vHcalBarrelHits;
   for(size_t iHit = 0; iHit < HcalBarrelHits_; iHit++){
      if( (MCParticles_generatorStatus[_HcalBarrelHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_HcalBarrelHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {HcalBarrelHits_position_x[iHit], HcalBarrelHits_position_y[iHit], HcalBarrelHits_position_z[iHit]};
      vHcalBarrelHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vHcalBarrelHits);

   std::vector<Vec3> vHcalEndcapNHits;
   for(size_t iHit = 0; iHit < HcalEndcapNHits_; iHit++){
      if( (MCParticles_generatorStatus[_HcalEndcapNHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_HcalEndcapNHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {HcalEndcapNHits_position_x[iHit], HcalEndcapNHits_position_y[iHit], HcalEndcapNHits_position_z[iHit]};
      vHcalEndcapNHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vHcalEndcapNHits);


   std::vector<Vec3> vHcalEndcapPInsertHits;
   for(size_t iHit = 0; iHit < HcalEndcapPInsertHits_; iHit++){
      if( (MCParticles_generatorStatus[_HcalEndcapPInsertHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_HcalEndcapPInsertHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {HcalEndcapPInsertHits_position_x[iHit], HcalEndcapPInsertHits_position_y[iHit], HcalEndcapPInsertHits_position_z[iHit]};
      vHcalEndcapPInsertHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vHcalEndcapPInsertHits);


   std::vector<Vec3> vHcalFarForwardZDCHits;
   for(size_t iHit = 0; iHit < HcalFarForwardZDCHits_; iHit++){
      if( (MCParticles_generatorStatus[_HcalFarForwardZDCHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_HcalFarForwardZDCHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {HcalFarForwardZDCHits_position_x[iHit], HcalFarForwardZDCHits_position_y[iHit], HcalFarForwardZDCHits_position_z[iHit]};
      vHcalFarForwardZDCHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vHcalFarForwardZDCHits);


   std::vector<Vec3> vLFHCALHits;
   for(size_t iHit = 0; iHit < LFHCALHits_; iHit++){
      if( (MCParticles_generatorStatus[_LFHCALHitsContributions_particle_index[iHit]] < 1999 || MCParticles_generatorStatus[_LFHCALHitsContributions_particle_index[iHit]] > 2999)) continue;
      Vec3 hitPos = {LFHCALHits_position_x[iHit], LFHCALHits_position_y[iHit], LFHCALHits_position_z[iHit]};
      vLFHCALHits.push_back(hitPos);
   }
   vCalDetsHits.push_back(vLFHCALHits);

   m_vRecordedCalDetHits.push_back(vCalDetsHits);
}

void McPsCheck::FillEtaPtMaps(){
   for (size_t i = 0; i < MCParticles_; ++i) {
      double px = MCParticles_momentum_x[i];
      double py = MCParticles_momentum_y[i];
      double pz = MCParticles_momentum_z[i];
      double pt = sqrt(px * px + py * py);
      double p = sqrt(px * px + py * py + pz * pz);
      double eta = 0.5 * log((p + pz) / (p - pz));

      double kinE = sqrt(px * px + py * py + pz * pz + pow(MCParticles_mass[i], 2)) - MCParticles_mass[i];
      double allE = sqrt(px * px + py * py + pz * pz + pow(MCParticles_mass[i], 2));

      // if(!TOFBarrelHits_) continue;
      // std::cout << "MCParticle " << i << ": PDG = " << MCParticles_PDG[i] << ", charge = " << MCParticles_charge[i] << ", generatorStatus = " << MCParticles_generatorStatus[i] << ", eta = " << eta << ", pt = " << pt << std::endl;  // ChecKuma
      m_hEtaPt_All->Fill(eta, pt);
      m_hEtaKinE_All->Fill(eta, kinE);
      m_hEtaAllE_All->Fill(eta, allE);

      //CheeeeeCkuma for BTOF
      m_hEta_All->Fill(eta);
      if(TOFBarrelHits_ > 0){
         m_hEta_BTOF->Fill(eta);
      }else if(TOFEndcapHits_ > 0){
         m_hEta_ETOF->Fill(eta);
      }
      


      if (MCParticles_charge[i] != 0){
         m_hEtaPt_ChMcP->Fill(eta, pt);
         m_hEtaKinE_ChMcP->Fill(eta, kinE);
         m_hEtaAllE_ChMcP->Fill(eta, allE);
      }else{
         m_hEtaPt_NMcP->Fill(eta, pt);
         m_hEtaKinE_NMcP->Fill(eta, kinE);
         m_hEtaAllE_NMcP->Fill(eta, allE);
      }

      // if(MCParticles_generatorStatus[i] == 2001){
      if(1){
         // std::cout << "z = " << MCParticles_vertex_z[i] << ", r = " << sqrt(MCParticles_vertex_x[i] * MCParticles_vertex_x[i] + MCParticles_vertex_y[i] * MCParticles_vertex_y[i]) << std::endl;  // ChecKuma
         m_CollSourcePosiZR->Fill(MCParticles_vertex_z[i], sqrt(MCParticles_vertex_x[i] * MCParticles_vertex_x[i] + MCParticles_vertex_y[i] * MCParticles_vertex_y[i]));
      }
      
   }
}


void McPsCheck::drawOnlyOneEvent(const Event& ev) {
   auto* c = new TCanvas("cCheckEventDisplays", "one event", 1000, 800);
   gPad->SetTheta(20);
   gPad->SetPhi(30);

   m_hCheckEventDisplays = new TH3D("hCheckEventDisplays", "MCParticle Event Display;Z (mm);X (mm);Y (mm)", 100, -3000, 3000, 100, -2000, 2000, 100, -2000, 2000);
   m_hCheckEventDisplays->SetStats(0);
   m_hCheckEventDisplays->Draw();
   gStyle->SetOptStat(0);
   for (size_t i = 0; i < ev.particles.size(); ++i) {
      
      const auto& p = ev.particles[i];
      const Vec3 a = p.vertex;
      const Vec3 b = p.endpoint;

      if (mag(sub(b, a)) < 1e-12) continue;

      auto* line = new TPolyLine3D(2);
      line->SetPoint(0, a.z, a.x, a.y);
      line->SetPoint(1, b.z, b.x, b.y);
      line->SetLineColor(colorFromPDG(p.pdg, p.charge));
      line->SetLineWidth(1);
      line->Draw("same");
   
   }
   
   for(size_t iDet =0; iDet < m_vRecordedTrkDetHits.at(0).size(); iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedTrkDetHits.at(0).at(iDet).size(); iHit++){
         // std::cout << "Track Det Hit: (" << m_vRecordedTrkDetHits.at(0).at(iDet).at(iHit).x << ", " << m_vRecordedTrkDetHits.at(0).at(iDet).at(iHit).y << ", " << m_vRecordedTrkDetHits.at(0).at(iDet).at(iHit).z << ")" << std::endl; // ChecKuma
         auto* marker = new TPolyMarker3D(1);
         marker->SetPoint(1., m_vRecordedTrkDetHits.at(0).at(iDet).at(iHit).z, m_vRecordedTrkDetHits.at(0).at(iDet).at(iHit).x, m_vRecordedTrkDetHits.at(0).at(iDet).at(iHit).y);
         marker->SetMarkerSize(0.5);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(m_TrkDetColors[iDet]);
         
         marker->Draw("same");
      }

   }

   for(size_t iDet =0; iDet < m_vRecordedCalDetHits.at(0).size(); iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedCalDetHits.at(0).at(iDet).size(); iHit++){
         auto* marker = new TMarker(m_vRecordedCalDetHits.at(0).at(iDet).at(iHit).z, m_vRecordedCalDetHits.at(0).at(iDet).at(iHit).x, m_vRecordedCalDetHits.at(0).at(iDet).at(iHit).y);
         marker->SetMarkerSize(0.8);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(m_CalDetColors[iDet]);
         marker->Draw("same");
      }
   }

   // m_hCheckEventDisplays->SaveAs("hCheckEventDisplays.root");
   c->Update();
   TFile fout("hCheckEventDisplays.root", "RECREATE");
  c->Write();
  fout.Close();
   
}

void McPsCheck::drawOneEvent(const Event& ev, int eventIndex, double fallbackLength) {
  double xmin, xmax, ymin, ymax, zmin, zmax;
   
   computeEventBounds(ev, xmin, xmax, ymin, ymax, zmin, zmax, fallbackLength);
   
   m_hEventDisplays[eventIndex]->SetStats(0);
   m_hEventDisplays[eventIndex]->Draw();
   gStyle->SetOptStat(0);
   for (size_t i = 0; i < ev.particles.size(); ++i) {
      
      const auto& p = ev.particles[i];
      const Vec3 a = p.vertex;
      const Vec3 b = p.endpoint;

      if (mag(sub(b, a)) < 1e-12) continue;

      auto* line = new TPolyLine3D(2);
      line->SetPoint(0, a.z, a.x, a.y);
      line->SetPoint(1, b.z, b.x, b.y);
      line->SetLineColor(colorFromPDG(p.pdg, p.charge));
      line->SetLineWidth(2);
      line->Draw("same");
   
   }
   
   for(size_t iDet =0; iDet < m_vRecordedTrkDetHits.at(eventIndex).size(); iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedTrkDetHits.at(eventIndex).at(iDet).size(); iHit++){
         // std::cout << "Track Det Hit: (" << m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).x << ", " << m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).y << ", " << m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).z << ")" << std::endl; // ChecKuma
         auto* marker = new TMarker(m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).z, m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).x, m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).y);
         marker->SetMarkerSize(0.8);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(m_TrkDetColors[iDet]);
         
         marker->Draw("same");
      }
   }

   for(size_t iDet =0; iDet < m_vRecordedCalDetHits.at(eventIndex).size(); iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedCalDetHits.at(eventIndex).at(iDet).size(); iHit++){
         auto* marker = new TMarker(m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).z, m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).x, m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).y);
         marker->SetMarkerSize(0.8);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(m_CalDetColors[iDet]);
         marker->Draw("same");
      }
   }


}

void McPsCheck::drawEightEvents(double fallbackLength) {
  auto* c = new TCanvas("c_events", "MCParticle Event Display", 1800, 900);
  c->Divide(4, 2, 0.001, 0.001);
   gStyle->SetOptStat(0);
  const int nPads = 8;
//   const int nDraw = std::min<int>(nPads, m_eventsForED.size());

  for (int i = 0; i < numOfED; ++i) {
// for (int i = 0; i < nDraw; ++i) {
      c->cd(i + 1);
      gStyle->SetOptStat(0);
      gPad->SetTheta(20);
      gPad->SetPhi(30);
      gPad->SetLeftMargin(0.02);
      gPad->SetRightMargin(0.02);
      gPad->SetTopMargin(0.08);
      gPad->SetBottomMargin(0.02);
      drawOneEvent(m_eventsForED[i], i, fallbackLength);
  }
  c->Update();

  TFile fout("EventDisplays.root", "RECREATE");
  c->Write();
  fout.Close();

  c->SaveAs("EventDisplays.pdf");
}


// === s === 2D event display
void McPsCheck::drawEightEvents2D_ZX(double fallbackLength) {
   auto* c = new TCanvas("c_events_2d", "Track Event Display 2D", 1800, 900);
   c->Divide(4, 2, 0.001, 0.001);
   gStyle->SetOptStat(0);

   for (int i = 0; i < numOfED; ++i) {
      c->cd(i + 1);
      gStyle->SetOptStat(0);
      gPad->SetLeftMargin(0.12);
      gPad->SetRightMargin(0.05);
      gPad->SetTopMargin(0.08);
      gPad->SetBottomMargin(0.12);

      drawOneEvent2D_ZX(m_eventsForED[i], i, fallbackLength);
   }

   c->Update();

   TFile fout("EventDisplays2D.root", "RECREATE");
   c->Write();
   fout.Close();

   c->SaveAs("EventDisplays2D.pdf");
}


void McPsCheck::drawOneEvent2D_ZX(const Event& ev, int eventIndex, double fallbackLength) {
   m_hEventDisplays2D[eventIndex]->SetStats(0);
   m_hEventDisplays2D[eventIndex]->Draw();
   gStyle->SetOptStat(0);

   for (size_t i = 0; i < ev.particles.size(); ++i) {
      const auto& p = ev.particles[i];
      const Vec3 a = p.vertex;
      const Vec3 b = p.endpoint;

      if (mag(sub(b, a)) < 1e-12) continue;

      auto* line = new TLine(a.z, a.y, b.z, b.y);  // x-axis = z, y-axis = x
      line->SetLineColor(colorFromPDG(p.pdg, p.charge));
      line->SetLineWidth(2);
      line->Draw("same");
   }
   
   for(size_t iDet =0; iDet < m_vRecordedTrkDetHits.at(eventIndex).size(); iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedTrkDetHits.at(eventIndex).at(iDet).size(); iHit++){
         // std::cout << "Track Det Hit: (" << m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).x << ", " << m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).y << ", " << m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).z << ")" << std::endl; // ChecKuma
         auto* marker = new TMarker(m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).z, m_vRecordedTrkDetHits.at(eventIndex).at(iDet).at(iHit).y, 20);
         marker->SetMarkerSize(0.8);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(m_TrkDetColors[iDet]);
         
         marker->Draw("same");
      }

   }

   for(size_t iDet =0; iDet < m_vRecordedCalDetHits.at(eventIndex).size(); iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedCalDetHits.at(eventIndex).at(iDet).size(); iHit++){
         // std::cout << "Calib Det Hit: (" << m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).x << ", " << m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).y << ", " << m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).z << ")" << std::endl; // ChecKuma
         auto* marker = new TMarker(m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).z, m_vRecordedCalDetHits.at(eventIndex).at(iDet).at(iHit).y, 20);
         marker->SetMarkerSize(0.8);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(m_CalDetColors[iDet]);
         marker->Draw("same");
      }

   }


}


// === e === For Event Display =========== #########################################################



void McPsCheck::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");
   m_hMCEtaDist = new TH1D("m_hMCEtaDist",";#it{#eta}; count",100, -5, 5);
   m_hMCThetaDist = new TH1D("m_hMCThetaDist","; #it{#theta} [rad]; count", 70, 3.5, 3.5);

   m_HitRTimeDispersion = new TH2D("m_HitRTimeDispersion", ";r [mm];time dispersion [ns]", 1000, -50, 5000, 2000, -50, 150);
   m_CalibHitRTimeDispersion = new TH2D("m_CalibHitRTimeDispersion", ";r [mm];time dispersion [ns]", 1000, -50, 5000, 2000, -50, 150);
   m_HitTCalcT0Dispersion = new TH1D("m_HitTCalcT0Dispersion", "; #it{t}_{hit} - #it{t}_{0, calc} [ns]; count", 2000, -50, 150);

   m_hEtaPt_All = new TH2D("m_hEtaPt_All",";#it{#eta};#it{p}_{T} [GeV/#it{c}]",100, -15, 15,1000, 0, 10);
   m_hEtaPt_ChMcP = new TH2D("m_hEtaPt_ChMcP",";#it{#eta};#it{p}_{T} [GeV/#it{c}]",100, -15, 15,1000, 0, 10);
   m_hEtaPt_NMcP = new TH2D("m_hEtaPt_NMcP",";#it{#eta};#it{p}_{T} [GeV/#it{c}]",100, -15, 15, 1000, 0, 10);

   m_hEtaKinE_All = new TH2D("m_hEtaKinE_All",";#it{#eta};#it{E}_{kin} [GeV]",100, -15, 15,1000, 0, 10);
   m_hEtaKinE_ChMcP = new TH2D("m_hEtaKinE_ChMcP",";#it{#eta};#it{E}_{kin} [GeV]",100, -15, 15,1000, 0, 10);
   m_hEtaKinE_NMcP = new TH2D("m_hEtaKinE_NMcP",";#it{#eta};#it{E}_{kin} [GeV]",100, -15, 15, 1000, 0, 10);

   m_hEtaAllE_All = new TH2D("m_hEtaAllE_All",";#it{#eta};#it{E} [GeV]",100, -15, 15,1000, 0, 10);
   m_hEtaAllE_ChMcP = new TH2D("m_hEtaAllE_ChMcP",";#it{#eta};#it{E} [GeV]",100, -15, 15,1000, 0, 10);
   m_hEtaAllE_NMcP = new TH2D("m_hEtaAllE_NMcP",";#it{#eta};#it{E} [GeV]",100, -15, 15, 1000, 0, 10);

   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      m_hZRHitRatio_All_BKG[iBkg] = new TH2D(Form("m_hZRHitRatio_All_%s", m_BkgNames[iBkg].Data()), Form(";#it{z} [mm];#it{r} [mm] (%s)", m_BkgNames[iBkg].Data()), 1000, -3000, 3000, 500, 0, 1500);
      m_hZRHitRatio_ChMcP_BKG[iBkg] = new TH2D(Form("m_hZRHitRatio_ChMcP_%s", m_BkgNames[iBkg].Data()), Form(";#it{z} [mm];#it{r} [mm] (%s)", m_BkgNames[iBkg].Data()), 1000, -3000, 3000, 500, 0, 1500);
      m_hZRHitRatio_NMcP_BKG[iBkg] = new TH2D(Form("m_hZRHitRatio_NMcP_%s", m_BkgNames[iBkg].Data()), Form(";#it{z} [mm];#it{r} [mm] (%s)", m_BkgNames[iBkg].Data()), 1000, -3000, 3000, 1000, 0, 3000);

      m_EveCountWithDetHits_Trk_BKG[iBkg] = new TH1D(Form("m_EveCountWithDetHits_Trk_%s", m_BkgNames[iBkg].Data()), ";; count", 17, 0.5, 17);
      m_EveCountWithDetHits_Cal_BKG[iBkg] = new TH1D(Form("m_EveCountWithDetHits_Cal_%s", m_BkgNames[iBkg].Data()), ";; count", 12, 0.5, 12);

      for (int i = 0; i < 17; ++i) m_EveCountWithDetHits_Trk_BKG[iBkg]->GetXaxis()->SetBinLabel(i + 1, m_TrkDetNames[i].Data());
      for (int i = 0; i < 12; ++i) m_EveCountWithDetHits_Cal_BKG[iBkg]->GetXaxis()->SetBinLabel(i + 1, m_CalDetNames[i].Data());


      m_HitsPerEveWithDetHits_Trk_BKG[iBkg] = new TH1D(Form("m_HitsPerEveWithDetHits_Trk_%s", m_BkgNames[iBkg].Data()), ";; count", 17, 0.5, 17);
      m_HitsPerEveWithDetHits_Cal_BKG[iBkg] = new TH1D(Form("m_HitsPerEveWithDetHits_Cal_%s", m_BkgNames[iBkg].Data()), ";; count", 12, 0.5, 12);

      for (int i = 0; i < 17; ++i) m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->GetXaxis()->SetBinLabel(i + 1, m_TrkDetNames[i].Data());
      for (int i = 0; i < 12; ++i) m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->GetXaxis()->SetBinLabel(i + 1, m_CalDetNames[i].Data());

   }


   m_CollSourcePosiZR = new TH2D("m_CollSourcePosiZR",";z [mm];r [mm]",2000, -5000, 5000, 1000, 0, 100);

   m_EveCountWithDetHits_Trk = new TH1D("m_EveCountWithDetHits_Trk", ";; count", 17, 0.5, 17);
   m_EveCountWithDetHits_Cal = new TH1D("m_EveCountWithDetHits_Cal", ";; count", 12, 0.5, 12);

   m_HitsPerEveWithDetHits_Trk = new TH1D("m_HitsPerEveWithDetHits_Trk", ";; count", 17, 0.5, 17);
   m_HitsPerEveWithDetHits_Cal = new TH1D( "m_HitsPerEveWithDetHits_Cal", ";; count", 12, 0.5, 12);

   for (int i = 0; i < 17; ++i) {
      m_EveCountWithDetHits_Trk->GetXaxis()->SetBinLabel(i + 1, m_TrkDetNames[i].Data());
      m_HitsPerEveWithDetHits_Trk->GetXaxis()->SetBinLabel(i + 1, m_TrkDetNames[i].Data());
   }
   for (int i = 0; i < 12; ++i) {
      m_EveCountWithDetHits_Cal->GetXaxis()->SetBinLabel(i + 1, m_CalDetNames[i].Data());
      m_HitsPerEveWithDetHits_Cal->GetXaxis()->SetBinLabel(i + 1, m_CalDetNames[i].Data());
   }

   m_NumOfEventsOfBKG = new TH1D("m_NumOfEventsOfBKG", ";; events/time frame [2 #mu s]", 5, 0.5, 5.5);
   for (int i = 0; i < 5; ++i) m_NumOfEventsOfBKG->GetXaxis()->SetBinLabel(i + 1, m_BkgNames[i].Data());

   // for(size_t nHist = 0; nHist < 8; nHist++) m_hMomEventDisplays[nHist] = new TH2D(Form("hEventDisplays%d", nHist),"", nBins[nHist], minX[nHist],maxX[nHist]);

   
   // for (size_t nHist = 0; nHist < 8; nHist++) {
   //    m_hEventDisplays[nHist] = nullptr;
   //    m_hEventDisplays[nHist] = new TH3D(
   //       Form("hEventDisplays%zu", nHist), "",
   //       100, -5000, 5000,
   //       100, -5000, 5000,
   //       100, -5000, 5000
   //    );
   // }



   m_hEta_All = new TH1D("m_hEta_All",";#it{#eta};count",100, -15, 15);
   m_hEta_BTOF = new TH1D("m_hEta_BTOF",";#it{#eta};count",100, -15, 15);
   m_hEta_ETOF = new TH1D("m_hEta_ETOF",";#it{#eta};count",100, -15, 15);


   m_HitTCalcT0Dispersion_Phys = new TH1D("m_HitTCalcT0Dispersion_Phys", "; #it{t}_{hit} - #it{t}_{0, calc} [ns]; count", 600, -100, 500);
   m_HitTCalcT0Dispersion_BKG = new TH1D("m_HitTCalcT0Dispersion_BKG", "; #it{t}_{hit} - #it{t}_{0, calc} [ns]; count", 600, -100, 500);
   m_HitTCalcT0Dispersion_Phys_BTOF = new TH1D("m_HitTCalcT0Dispersion_Phys_BTOF", "; #it{t}_{hit} - #it{t}_{0, calc} [ns]; count", 600, -100, 500);
   m_HitTCalcT0Dispersion_BKG_BTOF = new TH1D("m_HitTCalcT0Dispersion_BKG_BTOF", "; #it{t}_{hit} - #it{t}_{0, calc} [ns]; count", 600, -100, 500);




   m_HitDepE_Phys = new TH1D("m_HitDepE_Phys", ";depE [MeV]; count", 100, 0, 1.0);
   m_HitDepE_Phys_BSVT = new TH1D("m_HitDepE_Phys_BSVT", ";depE [MeV]; count", 100, 0, 0.1);
   m_HitDepE_Phys_ESVT = new TH1D("m_HitDepE_Phys_ESVT", ";depE [MeV]; count", 100, 0, 0.1);
   m_HitDepE_Phys_BMPGD = new TH1D("m_HitDepE_Phys_BMPGD", ";depE [MeV]; count", 300, 0, 0.03);
   m_HitDepE_Phys_EMPGD = new TH1D("m_HitDepE_Phys_EMPGD", ";depE [MeV]; count", 300, 0, 0.03);
   m_HitDepE_Phys_BTOF = new TH1D("m_HitDepE_Phys_BTOF", ";depE [MeV]; count", 100, 0, 1.0);
   m_HitDepE_Phys_ETOF = new TH1D("m_HitDepE_Phys_ETOF", ";depE [MeV]; count", 100, 0, 1.0);
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      m_HitDepE_BKG[iBkg] = new TH1D(Form("m_HitDepE_%s", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 100, 0, 1.0);
      m_HitDepE_BKG_BSVT[iBkg] = new TH1D(Form("m_HitDepE_%s_BSVT", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 100, 0, 0.1);
      m_HitDepE_BKG_ESVT[iBkg] = new TH1D(Form("m_HitDepE_%s_ESVT", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 100, 0, 0.1);
      m_HitDepE_BKG_BMPGD[iBkg] = new TH1D(Form("m_HitDepE_%s_BMPGD", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 300, 0, 0.03);
      m_HitDepE_BKG_EMPGD[iBkg] = new TH1D(Form("m_HitDepE_%s_EMPGD", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 300, 0, 0.03);
      m_HitDepE_BKG_BTOF[iBkg] = new TH1D(Form("m_HitDepE_%s_BTOF", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 100, 0, 1.0);
      m_HitDepE_BKG_ETOF[iBkg] = new TH1D(Form("m_HitDepE_%s_ETOF", m_BkgNames[iBkg].Data()), ";depE [MeV]; count", 100, 0, 1.0);
   }
}


void McPsCheck::FillHitTimeDispersion(){

   Double_t timeVtx = -99999.;
   for(size_t iMcP = 0; iMcP < MCParticles_; iMcP++){
      // std::cout << "MCParticle " << iMcP << ": generatorStatus = " << MCParticles_generatorStatus[iMcP] << ", time = " << MCParticles_time[iMcP] << std::endl; // ChecKuma
      if(MCParticles_generatorStatus[iMcP] != 61) continue;
      timeVtx = MCParticles_time[iMcP];
   }
   if(timeVtx == -99999.) return; // No valid timeVtx found, skip filling the histogram
   

   for(size_t iHit = 0; iHit < VertexBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(VertexBarrelHits_position_x[iHit]*VertexBarrelHits_position_x[iHit]\
         + VertexBarrelHits_position_y[iHit]*VertexBarrelHits_position_y[iHit]\
         + VertexBarrelHits_position_z[iHit]*VertexBarrelHits_position_z[iHit]);
      Double_t hitT = VertexBarrelHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "VertexBarrelHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "VertexBarrelHits R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < SiBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(SiBarrelHits_position_x[iHit]*SiBarrelHits_position_x[iHit]\
         + SiBarrelHits_position_y[iHit]*SiBarrelHits_position_y[iHit]\
         + SiBarrelHits_position_z[iHit]*SiBarrelHits_position_z[iHit]);
      Double_t hitT = SiBarrelHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "SiBarrelHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "SiBarrelHits R : " << hitR << std::endl; // ChecKuma
   }


   for(size_t iHit = 0; iHit < TrackerEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(TrackerEndcapHits_position_x[iHit]*TrackerEndcapHits_position_x[iHit]\
         + TrackerEndcapHits_position_y[iHit]*TrackerEndcapHits_position_y[iHit]\
         + TrackerEndcapHits_position_z[iHit]*TrackerEndcapHits_position_z[iHit]);
      Double_t hitT = TrackerEndcapHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
         // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "TrackerEndcapHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
         // if(hitR > 0 && hitR < 200) std::cout << "TrackerEndcapHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < MPGDBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(MPGDBarrelHits_position_x[iHit]*MPGDBarrelHits_position_x[iHit]\
         + MPGDBarrelHits_position_y[iHit]*MPGDBarrelHits_position_y[iHit]\
         + MPGDBarrelHits_position_z[iHit]*MPGDBarrelHits_position_z[iHit]);
      Double_t hitT = MPGDBarrelHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "MPGDBarrelHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "MPGDBarrelHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < OuterMPGDBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(OuterMPGDBarrelHits_position_x[iHit]*OuterMPGDBarrelHits_position_x[iHit]\
         + OuterMPGDBarrelHits_position_y[iHit]*OuterMPGDBarrelHits_position_y[iHit]\
         + OuterMPGDBarrelHits_position_z[iHit]*OuterMPGDBarrelHits_position_z[iHit]);
      Double_t hitT = OuterMPGDBarrelHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "OuterMPGDBarrelHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "OuterMPGDBarrelHits_ R : " << hitR << std::endl; // ChecKuma
      

   }

   for(size_t iHit = 0; iHit < ForwardMPGDEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(ForwardMPGDEndcapHits_position_x[iHit]*ForwardMPGDEndcapHits_position_x[iHit]\
         + ForwardMPGDEndcapHits_position_y[iHit]*ForwardMPGDEndcapHits_position_y[iHit]\
         + ForwardMPGDEndcapHits_position_z[iHit]*ForwardMPGDEndcapHits_position_z[iHit]);
      Double_t hitT = ForwardMPGDEndcapHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "ForwardMPGDEndcapHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "ForwardMPGDEndcapHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < BackwardMPGDEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(BackwardMPGDEndcapHits_position_x[iHit]*BackwardMPGDEndcapHits_position_x[iHit]\
         + BackwardMPGDEndcapHits_position_y[iHit]*BackwardMPGDEndcapHits_position_y[iHit]\
         + BackwardMPGDEndcapHits_position_z[iHit]*BackwardMPGDEndcapHits_position_z[iHit]);
      Double_t hitT = BackwardMPGDEndcapHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "BackwardMPGDEndcapHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "BackwardMPGDEndcapHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < TOFBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(TOFBarrelHits_position_x[iHit]*TOFBarrelHits_position_x[iHit]\
         + TOFBarrelHits_position_y[iHit]*TOFBarrelHits_position_y[iHit]\
         + TOFBarrelHits_position_z[iHit]*TOFBarrelHits_position_z[iHit]);
      Double_t hitT = TOFBarrelHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "TOFBarrelHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "TOFBarrelHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < TOFEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(TOFEndcapHits_position_x[iHit]*TOFEndcapHits_position_x[iHit]\
         + TOFEndcapHits_position_y[iHit]*TOFEndcapHits_position_y[iHit]\
         + TOFEndcapHits_position_z[iHit]*TOFEndcapHits_position_z[iHit]);
      Double_t hitT = TOFEndcapHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "TOFEndcapHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "TOFEndcapHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < B0TrackerHits_; iHit++){
      Double_t hitR = std::sqrt(B0TrackerHits_position_x[iHit]*B0TrackerHits_position_x[iHit]\
         + B0TrackerHits_position_y[iHit]*B0TrackerHits_position_y[iHit]\
         + B0TrackerHits_position_z[iHit]*B0TrackerHits_position_z[iHit]);
      Double_t hitT = B0TrackerHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "B0TrackerHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "B0TrackerHits_ R : " << hitR << std::endl; // ChecKuma
   }


   // for(size_t iHit = 0; iHit < DIRCBarHits_; iHit++){
   //    Double_t hitR = std::sqrt(DIRCBarHits_position_x[iHit]*DIRCBarHits_position_x[iHit]\
   //       + DIRCBarHits_position_y[iHit]*DIRCBarHits_position_y[iHit]\
   //       + DIRCBarHits_position_z[iHit]*DIRCBarHits_position_z[iHit]);
   //    Double_t hitT = DIRCBarHits_time[iHit] - timeVtx;
   //    m_HitRTimeDispersion->Fill(hitR, hitT);
   //    Double_t t0Calc = hitR * 0.0034;
   //    m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
   //    if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "DIRCBarHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
   // }

   // for(size_t iHit = 0; iHit < DRICHHits_; iHit++){
   //    Double_t hitR = std::sqrt(DRICHHits_position_x[iHit]*DRICHHits_position_x[iHit]\
   //       + DRICHHits_position_y[iHit]*DRICHHits_position_y[iHit]\
   //       + DRICHHits_position_z[iHit]*DRICHHits_position_z[iHit]);
   //    Double_t hitT = DRICHHits_time[iHit] - timeVtx;
   //    m_HitRTimeDispersion->Fill(hitR, hitT);
   //    Double_t t0Calc = hitR * 0.0034;
   //    m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
   //    if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "DRICHHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
   // }


   for(size_t iHit = 0; iHit < ForwardOffMTrackerHits_; iHit++){
      Double_t hitR = std::sqrt(ForwardOffMTrackerHits_position_x[iHit]*ForwardOffMTrackerHits_position_x[iHit]\
         + ForwardOffMTrackerHits_position_y[iHit]*ForwardOffMTrackerHits_position_y[iHit]\
         + ForwardOffMTrackerHits_position_z[iHit]*ForwardOffMTrackerHits_position_z[iHit]);
      Double_t hitT = ForwardOffMTrackerHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "ForwardOffMTrackerHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "ForwardOffMTrackerHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < ForwardRomanPotHits_; iHit++){
      Double_t hitR = std::sqrt(ForwardRomanPotHits_position_x[iHit]*ForwardRomanPotHits_position_x[iHit]\
         + ForwardRomanPotHits_position_y[iHit]*ForwardRomanPotHits_position_y[iHit]\
         + ForwardRomanPotHits_position_z[iHit]*ForwardRomanPotHits_position_z[iHit]);
      Double_t hitT = ForwardRomanPotHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "ForwardRomanPotHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "ForwardRomanPotHits_ R : " << hitR << std::endl; // ChecKuma
   }

   for(size_t iHit = 0; iHit < LumiSpecTrackerHits_; iHit++){
      Double_t hitR = std::sqrt(LumiSpecTrackerHits_position_x[iHit]*LumiSpecTrackerHits_position_x[iHit]\
         + LumiSpecTrackerHits_position_y[iHit]*LumiSpecTrackerHits_position_y[iHit]\
         + LumiSpecTrackerHits_position_z[iHit]*LumiSpecTrackerHits_position_z[iHit]);
      Double_t hitT = LumiSpecTrackerHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "LumiSpecTrackerHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
         // if(hitR > 0 && hitR < 200) std::cout << "LumiSpecTrackerHits_ R : " << hitR << std::endl; // ChecKuma
   }


   for(size_t iHit = 0; iHit < PFRICHHits_; iHit++){
      Double_t hitR = std::sqrt(PFRICHHits_position_x[iHit]*PFRICHHits_position_x[iHit]\
         + PFRICHHits_position_y[iHit]*PFRICHHits_position_y[iHit]\
         + PFRICHHits_position_z[iHit]*PFRICHHits_position_z[iHit]);
      Double_t hitT = PFRICHHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "PFRICHHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "PFRICHHits_ R : " << hitR << std::endl; // ChecKuma
   }


   for(size_t iHit = 0; iHit < TaggerTrackerHits_; iHit++){
      Double_t hitR = std::sqrt(TaggerTrackerHits_position_x[iHit]*TaggerTrackerHits_position_x[iHit]\
         + TaggerTrackerHits_position_y[iHit]*TaggerTrackerHits_position_y[iHit]\
         + TaggerTrackerHits_position_z[iHit]*TaggerTrackerHits_position_z[iHit]);
      Double_t hitT = TaggerTrackerHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      m_HitTCalcT0Dispersion->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);
      // if(hitT - t0Calc > 4.5 && hitT - t0Calc < 5.5) std::cout << "TaggerTrackerHits Time: " << hitT - t0Calc << std::endl; // ChecKuma
      // if(hitR > 0 && hitR < 200) std::cout << "TaggerTrackerHits_ R : " << hitR << std::endl; // ChecKuma
   }




}


void McPsCheck::FillHitTimeDispersionForMixBKG(){

   Double_t timeVtx = -99999.;
   for(size_t iMcP = 0; iMcP < MCParticles_; iMcP++){
      // std::cout << "MCParticle " << iMcP << ": generatorStatus = " << MCParticles_generatorStatus[iMcP] << ", time = " << MCParticles_time[iMcP] << std::endl; // ChecKuma
      if(MCParticles_generatorStatus[iMcP] != 61) continue;
      timeVtx = MCParticles_time[iMcP];
   }
   if(timeVtx == -99999.) return; // No valid timeVtx found, skip filling the histogram
   

   for(size_t iHit = 0; iHit < VertexBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(VertexBarrelHits_position_x[iHit]*VertexBarrelHits_position_x[iHit]\
         + VertexBarrelHits_position_y[iHit]*VertexBarrelHits_position_y[iHit]\
         + VertexBarrelHits_position_z[iHit]*VertexBarrelHits_position_z[iHit]);
      Double_t hitT = VertexBarrelHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      

      Int_t pTagId = _VertexBarrelHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);
   
      Double_t depE = VertexBarrelHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_BSVT[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_BSVT[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_BSVT[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_BSVT[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_BSVT[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
         m_HitDepE_Phys_BSVT->Fill(depE);
      }


   }

   for(size_t iHit = 0; iHit < SiBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(SiBarrelHits_position_x[iHit]*SiBarrelHits_position_x[iHit]\
         + SiBarrelHits_position_y[iHit]*SiBarrelHits_position_y[iHit]\
         + SiBarrelHits_position_z[iHit]*SiBarrelHits_position_z[iHit]);
      Double_t hitT = SiBarrelHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      
      Int_t pTagId = _SiBarrelHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = SiBarrelHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_BSVT[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_BSVT[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_BSVT[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_BSVT[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_BSVT[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
         m_HitDepE_Phys_BSVT->Fill(depE);
      }

   }


   for(size_t iHit = 0; iHit < TrackerEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(TrackerEndcapHits_position_x[iHit]*TrackerEndcapHits_position_x[iHit]\
         + TrackerEndcapHits_position_y[iHit]*TrackerEndcapHits_position_y[iHit]\
         + TrackerEndcapHits_position_z[iHit]*TrackerEndcapHits_position_z[iHit]);
      Double_t hitT = TrackerEndcapHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _TrackerEndcapHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = TrackerEndcapHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_ESVT[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_ESVT[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_ESVT[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_ESVT[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_ESVT[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
         m_HitDepE_Phys_ESVT->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < MPGDBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(MPGDBarrelHits_position_x[iHit]*MPGDBarrelHits_position_x[iHit]\
         + MPGDBarrelHits_position_y[iHit]*MPGDBarrelHits_position_y[iHit]\
         + MPGDBarrelHits_position_z[iHit]*MPGDBarrelHits_position_z[iHit]);
      Double_t hitT = MPGDBarrelHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _MPGDBarrelHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = MPGDBarrelHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_BMPGD[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_BMPGD[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_BMPGD[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_BMPGD[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_BMPGD[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys_BMPGD->Fill(depE);
         m_HitDepE_Phys->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < OuterMPGDBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(OuterMPGDBarrelHits_position_x[iHit]*OuterMPGDBarrelHits_position_x[iHit]\
         + OuterMPGDBarrelHits_position_y[iHit]*OuterMPGDBarrelHits_position_y[iHit]\
         + OuterMPGDBarrelHits_position_z[iHit]*OuterMPGDBarrelHits_position_z[iHit]);
      Double_t hitT = OuterMPGDBarrelHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _OuterMPGDBarrelHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = OuterMPGDBarrelHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_BMPGD[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_BMPGD[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_BMPGD[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_BMPGD[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_BMPGD[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys_BMPGD->Fill(depE);
         m_HitDepE_Phys->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < ForwardMPGDEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(ForwardMPGDEndcapHits_position_x[iHit]*ForwardMPGDEndcapHits_position_x[iHit]\
         + ForwardMPGDEndcapHits_position_y[iHit]*ForwardMPGDEndcapHits_position_y[iHit]\
         + ForwardMPGDEndcapHits_position_z[iHit]*ForwardMPGDEndcapHits_position_z[iHit]);
      Double_t hitT = ForwardMPGDEndcapHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _ForwardMPGDEndcapHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = ForwardMPGDEndcapHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_EMPGD[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_EMPGD[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_EMPGD[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_EMPGD[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_EMPGD[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys_EMPGD->Fill(depE);
         m_HitDepE_Phys->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < BackwardMPGDEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(BackwardMPGDEndcapHits_position_x[iHit]*BackwardMPGDEndcapHits_position_x[iHit]\
         + BackwardMPGDEndcapHits_position_y[iHit]*BackwardMPGDEndcapHits_position_y[iHit]\
         + BackwardMPGDEndcapHits_position_z[iHit]*BackwardMPGDEndcapHits_position_z[iHit]);
      Double_t hitT = BackwardMPGDEndcapHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _BackwardMPGDEndcapHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = BackwardMPGDEndcapHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_EMPGD[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_EMPGD[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_EMPGD[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_EMPGD[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_EMPGD[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys_EMPGD->Fill(depE);
         m_HitDepE_Phys->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < TOFBarrelHits_; iHit++){
      Double_t hitR = std::sqrt(TOFBarrelHits_position_x[iHit]*TOFBarrelHits_position_x[iHit]\
         + TOFBarrelHits_position_y[iHit]*TOFBarrelHits_position_y[iHit]\
         + TOFBarrelHits_position_z[iHit]*TOFBarrelHits_position_z[iHit]);
      Double_t hitT = TOFBarrelHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _TOFBarrelHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = TOFBarrelHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
         m_HitDepE_BKG_BTOF[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
         m_HitDepE_BKG_BTOF[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
         m_HitDepE_BKG_BTOF[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
         m_HitDepE_BKG_BTOF[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
         m_HitDepE_BKG_BTOF[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
         m_HitDepE_Phys_BTOF->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < TOFEndcapHits_; iHit++){
      Double_t hitR = std::sqrt(TOFEndcapHits_position_x[iHit]*TOFEndcapHits_position_x[iHit]\
         + TOFEndcapHits_position_y[iHit]*TOFEndcapHits_position_y[iHit]\
         + TOFEndcapHits_position_z[iHit]*TOFEndcapHits_position_z[iHit]);
      Double_t hitT = TOFEndcapHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _TOFEndcapHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = TOFEndcapHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG_ETOF[4]->Fill(depE);
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG_ETOF[3]->Fill(depE);
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG_ETOF[2]->Fill(depE);
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG_ETOF[1]->Fill(depE);
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG_ETOF[0]->Fill(depE);
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
         m_HitDepE_Phys_ETOF->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < B0TrackerHits_; iHit++){
      Double_t hitR = std::sqrt(B0TrackerHits_position_x[iHit]*B0TrackerHits_position_x[iHit]\
         + B0TrackerHits_position_y[iHit]*B0TrackerHits_position_y[iHit]\
         + B0TrackerHits_position_z[iHit]*B0TrackerHits_position_z[iHit]);
      Double_t hitT = B0TrackerHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _B0TrackerHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = B0TrackerHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
      }
   }


   for(size_t iHit = 0; iHit < ForwardOffMTrackerHits_; iHit++){
      Double_t hitR = std::sqrt(ForwardOffMTrackerHits_position_x[iHit]*ForwardOffMTrackerHits_position_x[iHit]\
         + ForwardOffMTrackerHits_position_y[iHit]*ForwardOffMTrackerHits_position_y[iHit]\
         + ForwardOffMTrackerHits_position_z[iHit]*ForwardOffMTrackerHits_position_z[iHit]);
      Double_t hitT = ForwardOffMTrackerHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
         Int_t pTagId = _ForwardOffMTrackerHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = ForwardOffMTrackerHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < ForwardRomanPotHits_; iHit++){
      Double_t hitR = std::sqrt(ForwardRomanPotHits_position_x[iHit]*ForwardRomanPotHits_position_x[iHit]\
         + ForwardRomanPotHits_position_y[iHit]*ForwardRomanPotHits_position_y[iHit]\
         + ForwardRomanPotHits_position_z[iHit]*ForwardRomanPotHits_position_z[iHit]);
      Double_t hitT = ForwardRomanPotHits_time[iHit] - timeVtx;
      m_HitRTimeDispersion->Fill(hitR, hitT);
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _ForwardRomanPotHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);
      m_CalibHitRTimeDispersion->Fill(hitR, hitT - t0Calc);

      Double_t depE = ForwardRomanPotHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
      }
   }

   for(size_t iHit = 0; iHit < LumiSpecTrackerHits_; iHit++){
      Double_t hitR = std::sqrt(LumiSpecTrackerHits_position_x[iHit]*LumiSpecTrackerHits_position_x[iHit]\
         + LumiSpecTrackerHits_position_y[iHit]*LumiSpecTrackerHits_position_y[iHit]\
         + LumiSpecTrackerHits_position_z[iHit]*LumiSpecTrackerHits_position_z[iHit]);
      Double_t hitT = LumiSpecTrackerHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _LumiSpecTrackerHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = LumiSpecTrackerHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
      }
   }


   for(size_t iHit = 0; iHit < PFRICHHits_; iHit++){
      Double_t hitR = std::sqrt(PFRICHHits_position_x[iHit]*PFRICHHits_position_x[iHit]\
         + PFRICHHits_position_y[iHit]*PFRICHHits_position_y[iHit]\
         + PFRICHHits_position_z[iHit]*PFRICHHits_position_z[iHit]);
      Double_t hitT = PFRICHHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _PFRICHHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = PFRICHHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
      }
   }


   for(size_t iHit = 0; iHit < TaggerTrackerHits_; iHit++){
      Double_t hitR = std::sqrt(TaggerTrackerHits_position_x[iHit]*TaggerTrackerHits_position_x[iHit]\
         + TaggerTrackerHits_position_y[iHit]*TaggerTrackerHits_position_y[iHit]\
         + TaggerTrackerHits_position_z[iHit]*TaggerTrackerHits_position_z[iHit]);
      Double_t hitT = TaggerTrackerHits_time[iHit] - timeVtx;
      Double_t t0Calc = hitR * 0.0034;
      Int_t pTagId = _TaggerTrackerHits_particle_index[iHit];
      if(MCParticles_generatorStatus[pTagId] < 1999) m_HitTCalcT0Dispersion_Phys->Fill(hitT - t0Calc);
      else m_HitTCalcT0Dispersion_BKG->Fill(hitT - t0Calc);

      Double_t depE = TaggerTrackerHits_eDep[iHit] * 1000; // Convert GeV to MeV
      if(MCParticles_generatorStatus[pTagId] > 5999){
         m_HitDepE_BKG[4]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 4999){
         m_HitDepE_BKG[3]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 3999){
         m_HitDepE_BKG[2]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 2999){
         m_HitDepE_BKG[1]->Fill(depE);
      }else if(MCParticles_generatorStatus[pTagId] > 1999){
         m_HitDepE_BKG[0]->Fill(depE);
      }else{
         m_HitDepE_Phys->Fill(depE);
      }
   }




}


void McPsCheck::ResetValuesForEachEvent(){
   bool a = true;
   // m_SimTrackerHitsKuma.clear();
   // m_SimTrackerHitsKuma.shrink_to_fit();

}

void McPsCheck::WriteHists(){
   oFile->cd();

   m_hMCEtaDist->Write();
   m_hMCThetaDist->Write();

   m_HitRTimeDispersion->Write();
   m_CalibHitRTimeDispersion->Write();
   m_HitTCalcT0Dispersion->Write();

   m_hEtaPt_All->Write();
   m_hEtaPt_ChMcP->Write();
   m_hEtaPt_NMcP->Write();

   m_hEtaKinE_All->Write();
   m_hEtaKinE_ChMcP->Write();
   m_hEtaKinE_NMcP->Write();

   m_hEtaAllE_All->Write();
   m_hEtaAllE_ChMcP->Write();
   m_hEtaAllE_NMcP->Write();

   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      m_hZRHitRatio_All_BKG[iBkg]->Write();
      m_hZRHitRatio_ChMcP_BKG[iBkg]->Write();
      m_hZRHitRatio_NMcP_BKG[iBkg]->Write();

      m_EveCountWithDetHits_Trk_BKG[iBkg]->Write();
      m_EveCountWithDetHits_Cal_BKG[iBkg]->Write();

      m_HitsPerEveWithDetHits_Trk_BKG[iBkg]->Write();
      m_HitsPerEveWithDetHits_Cal_BKG[iBkg]->Write();

   }

   m_NumOfEventsOfBKG->Write();

   m_CollSourcePosiZR->Write();

   m_EveCountWithDetHits_Trk->Write();
   m_EveCountWithDetHits_Cal->Write();
   m_HitsPerEveWithDetHits_Trk->Write();
   m_HitsPerEveWithDetHits_Cal->Write();


   m_hEta_All->Write();
   m_hEta_BTOF->Write();
   m_hEta_ETOF->Write();

   m_HitTCalcT0Dispersion_Phys->Write();
   m_HitTCalcT0Dispersion_BKG->Write();
   m_HitTCalcT0Dispersion_Phys_BTOF->Write();
   m_HitTCalcT0Dispersion_BKG_BTOF->Write();

   m_HitDepE_Phys->Write();
   m_HitDepE_Phys_BSVT->Write();
   m_HitDepE_Phys_ESVT->Write();
   m_HitDepE_Phys_BMPGD->Write();
   m_HitDepE_Phys_EMPGD->Write();
   m_HitDepE_Phys_BTOF->Write();
   m_HitDepE_Phys_ETOF->Write();
   for(size_t iBkg = 0; iBkg < 5; iBkg++){
      m_HitDepE_BKG[iBkg]->Write();
      
      m_HitDepE_BKG_BSVT[iBkg]->Write();
      m_HitDepE_BKG_ESVT[iBkg]->Write();
      m_HitDepE_BKG_BMPGD[iBkg]->Write();
      m_HitDepE_BKG_EMPGD[iBkg]->Write();
      m_HitDepE_BKG_BTOF[iBkg]->Write();
      m_HitDepE_BKG_ETOF[iBkg]->Write();
   }


   oFile->Close();
}


// == s == MakeClass Default Functions == s ==
Int_t McPsCheck::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t McPsCheck::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void McPsCheck::Init(TTree *tree)
{

   GPIntKeys = 0;
   GPIntValues = 0;
   GPFloatKeys = 0;
   GPFloatValues = 0;
   GPDoubleKeys = 0;
   GPDoubleValues = 0;
   GPStringKeys = 0;
   GPStringValues = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchStatus("*", 0);

   fChain->SetBranchStatus("*", 1);


   fChain->SetBranchAddress("B0ECalHits", &B0ECalHits_, &b_B0ECalHits_);
   fChain->SetBranchAddress("B0ECalHits.cellID", &B0ECalHits_cellID, &b_B0ECalHits_cellID);
   fChain->SetBranchAddress("B0ECalHits.energy", &B0ECalHits_energy, &b_B0ECalHits_energy);
   fChain->SetBranchAddress("B0ECalHits.position.x", &B0ECalHits_position_x, &b_B0ECalHits_position_x);
   fChain->SetBranchAddress("B0ECalHits.position.y", &B0ECalHits_position_y, &b_B0ECalHits_position_y);
   fChain->SetBranchAddress("B0ECalHits.position.z", &B0ECalHits_position_z, &b_B0ECalHits_position_z);
   fChain->SetBranchAddress("B0ECalHits.contributions_begin", &B0ECalHits_contributions_begin, &b_B0ECalHits_contributions_begin);
   fChain->SetBranchAddress("B0ECalHits.contributions_end", &B0ECalHits_contributions_end, &b_B0ECalHits_contributions_end);
   fChain->SetBranchAddress("_B0ECalHits_contributions", &_B0ECalHits_contributions_, &b__B0ECalHits_contributions_);
   fChain->SetBranchAddress("_B0ECalHits_contributions.index", &_B0ECalHits_contributions_index, &b__B0ECalHits_contributions_index);
   fChain->SetBranchAddress("_B0ECalHits_contributions.collectionID", &_B0ECalHits_contributions_collectionID, &b__B0ECalHits_contributions_collectionID);
   fChain->SetBranchAddress("B0ECalHitsContributions", &B0ECalHitsContributions_, &b_B0ECalHitsContributions_);
   fChain->SetBranchAddress("B0ECalHitsContributions.PDG", &B0ECalHitsContributions_PDG, &b_B0ECalHitsContributions_PDG);
   fChain->SetBranchAddress("B0ECalHitsContributions.energy", &B0ECalHitsContributions_energy, &b_B0ECalHitsContributions_energy);
   fChain->SetBranchAddress("B0ECalHitsContributions.time", &B0ECalHitsContributions_time, &b_B0ECalHitsContributions_time);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepPosition.x", &B0ECalHitsContributions_stepPosition_x, &b_B0ECalHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepPosition.y", &B0ECalHitsContributions_stepPosition_y, &b_B0ECalHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepPosition.z", &B0ECalHitsContributions_stepPosition_z, &b_B0ECalHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepLength", &B0ECalHitsContributions_stepLength, &b_B0ECalHitsContributions_stepLength);
   fChain->SetBranchAddress("_B0ECalHitsContributions_particle", &_B0ECalHitsContributions_particle_, &b__B0ECalHitsContributions_particle_);
   fChain->SetBranchAddress("_B0ECalHitsContributions_particle.index", &_B0ECalHitsContributions_particle_index, &b__B0ECalHitsContributions_particle_index);
   fChain->SetBranchAddress("_B0ECalHitsContributions_particle.collectionID", &_B0ECalHitsContributions_particle_collectionID, &b__B0ECalHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("B0TrackerHits", &B0TrackerHits_, &b_B0TrackerHits_);
   fChain->SetBranchAddress("B0TrackerHits.cellID", &B0TrackerHits_cellID, &b_B0TrackerHits_cellID);
   fChain->SetBranchAddress("B0TrackerHits.eDep", &B0TrackerHits_eDep, &b_B0TrackerHits_eDep);
   fChain->SetBranchAddress("B0TrackerHits.time", &B0TrackerHits_time, &b_B0TrackerHits_time);
   fChain->SetBranchAddress("B0TrackerHits.pathLength", &B0TrackerHits_pathLength, &b_B0TrackerHits_pathLength);
   fChain->SetBranchAddress("B0TrackerHits.quality", &B0TrackerHits_quality, &b_B0TrackerHits_quality);
   fChain->SetBranchAddress("B0TrackerHits.position.x", &B0TrackerHits_position_x, &b_B0TrackerHits_position_x);
   fChain->SetBranchAddress("B0TrackerHits.position.y", &B0TrackerHits_position_y, &b_B0TrackerHits_position_y);
   fChain->SetBranchAddress("B0TrackerHits.position.z", &B0TrackerHits_position_z, &b_B0TrackerHits_position_z);
   fChain->SetBranchAddress("B0TrackerHits.momentum.x", &B0TrackerHits_momentum_x, &b_B0TrackerHits_momentum_x);
   fChain->SetBranchAddress("B0TrackerHits.momentum.y", &B0TrackerHits_momentum_y, &b_B0TrackerHits_momentum_y);
   fChain->SetBranchAddress("B0TrackerHits.momentum.z", &B0TrackerHits_momentum_z, &b_B0TrackerHits_momentum_z);
   fChain->SetBranchAddress("_B0TrackerHits_particle", &_B0TrackerHits_particle_, &b__B0TrackerHits_particle_);
   fChain->SetBranchAddress("_B0TrackerHits_particle.index", &_B0TrackerHits_particle_index, &b__B0TrackerHits_particle_index);
   fChain->SetBranchAddress("_B0TrackerHits_particle.collectionID", &_B0TrackerHits_particle_collectionID, &b__B0TrackerHits_particle_collectionID);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits", &BackwardMPGDEndcapHits_, &b_BackwardMPGDEndcapHits_);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.cellID", BackwardMPGDEndcapHits_cellID, &b_BackwardMPGDEndcapHits_cellID);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.eDep", BackwardMPGDEndcapHits_eDep, &b_BackwardMPGDEndcapHits_eDep);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.time", BackwardMPGDEndcapHits_time, &b_BackwardMPGDEndcapHits_time);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.pathLength", BackwardMPGDEndcapHits_pathLength, &b_BackwardMPGDEndcapHits_pathLength);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.quality", BackwardMPGDEndcapHits_quality, &b_BackwardMPGDEndcapHits_quality);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.position.x", BackwardMPGDEndcapHits_position_x, &b_BackwardMPGDEndcapHits_position_x);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.position.y", BackwardMPGDEndcapHits_position_y, &b_BackwardMPGDEndcapHits_position_y);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.position.z", BackwardMPGDEndcapHits_position_z, &b_BackwardMPGDEndcapHits_position_z);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.momentum.x", BackwardMPGDEndcapHits_momentum_x, &b_BackwardMPGDEndcapHits_momentum_x);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.momentum.y", BackwardMPGDEndcapHits_momentum_y, &b_BackwardMPGDEndcapHits_momentum_y);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.momentum.z", BackwardMPGDEndcapHits_momentum_z, &b_BackwardMPGDEndcapHits_momentum_z);
   fChain->SetBranchAddress("_BackwardMPGDEndcapHits_particle", &_BackwardMPGDEndcapHits_particle_, &b__BackwardMPGDEndcapHits_particle_);
   fChain->SetBranchAddress("_BackwardMPGDEndcapHits_particle.index", _BackwardMPGDEndcapHits_particle_index, &b__BackwardMPGDEndcapHits_particle_index);
   fChain->SetBranchAddress("_BackwardMPGDEndcapHits_particle.collectionID", _BackwardMPGDEndcapHits_particle_collectionID, &b__BackwardMPGDEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("DIRCBarHits", &DIRCBarHits_, &b_DIRCBarHits_);
   fChain->SetBranchAddress("DIRCBarHits.cellID", &DIRCBarHits_cellID, &b_DIRCBarHits_cellID);
   fChain->SetBranchAddress("DIRCBarHits.eDep", &DIRCBarHits_eDep, &b_DIRCBarHits_eDep);
   fChain->SetBranchAddress("DIRCBarHits.time", &DIRCBarHits_time, &b_DIRCBarHits_time);
   fChain->SetBranchAddress("DIRCBarHits.pathLength", &DIRCBarHits_pathLength, &b_DIRCBarHits_pathLength);
   fChain->SetBranchAddress("DIRCBarHits.quality", &DIRCBarHits_quality, &b_DIRCBarHits_quality);
   fChain->SetBranchAddress("DIRCBarHits.position.x", &DIRCBarHits_position_x, &b_DIRCBarHits_position_x);
   fChain->SetBranchAddress("DIRCBarHits.position.y", &DIRCBarHits_position_y, &b_DIRCBarHits_position_y);
   fChain->SetBranchAddress("DIRCBarHits.position.z", &DIRCBarHits_position_z, &b_DIRCBarHits_position_z);
   fChain->SetBranchAddress("DIRCBarHits.momentum.x", &DIRCBarHits_momentum_x, &b_DIRCBarHits_momentum_x);
   fChain->SetBranchAddress("DIRCBarHits.momentum.y", &DIRCBarHits_momentum_y, &b_DIRCBarHits_momentum_y);
   fChain->SetBranchAddress("DIRCBarHits.momentum.z", &DIRCBarHits_momentum_z, &b_DIRCBarHits_momentum_z);
   fChain->SetBranchAddress("_DIRCBarHits_particle", &_DIRCBarHits_particle_, &b__DIRCBarHits_particle_);
   fChain->SetBranchAddress("_DIRCBarHits_particle.index", &_DIRCBarHits_particle_index, &b__DIRCBarHits_particle_index);
   fChain->SetBranchAddress("_DIRCBarHits_particle.collectionID", &_DIRCBarHits_particle_collectionID, &b__DIRCBarHits_particle_collectionID);
   fChain->SetBranchAddress("DRICHHits", &DRICHHits_, &b_DRICHHits_);
   fChain->SetBranchAddress("DRICHHits.cellID", &DRICHHits_cellID, &b_DRICHHits_cellID);
   fChain->SetBranchAddress("DRICHHits.eDep", &DRICHHits_eDep, &b_DRICHHits_eDep);
   fChain->SetBranchAddress("DRICHHits.time", &DRICHHits_time, &b_DRICHHits_time);
   fChain->SetBranchAddress("DRICHHits.pathLength", &DRICHHits_pathLength, &b_DRICHHits_pathLength);
   fChain->SetBranchAddress("DRICHHits.quality", &DRICHHits_quality, &b_DRICHHits_quality);
   fChain->SetBranchAddress("DRICHHits.position.x", &DRICHHits_position_x, &b_DRICHHits_position_x);
   fChain->SetBranchAddress("DRICHHits.position.y", &DRICHHits_position_y, &b_DRICHHits_position_y);
   fChain->SetBranchAddress("DRICHHits.position.z", &DRICHHits_position_z, &b_DRICHHits_position_z);
   fChain->SetBranchAddress("DRICHHits.momentum.x", &DRICHHits_momentum_x, &b_DRICHHits_momentum_x);
   fChain->SetBranchAddress("DRICHHits.momentum.y", &DRICHHits_momentum_y, &b_DRICHHits_momentum_y);
   fChain->SetBranchAddress("DRICHHits.momentum.z", &DRICHHits_momentum_z, &b_DRICHHits_momentum_z);
   fChain->SetBranchAddress("_DRICHHits_particle", &_DRICHHits_particle_, &b__DRICHHits_particle_);
   fChain->SetBranchAddress("_DRICHHits_particle.index", &_DRICHHits_particle_index, &b__DRICHHits_particle_index);
   fChain->SetBranchAddress("_DRICHHits_particle.collectionID", &_DRICHHits_particle_collectionID, &b__DRICHHits_particle_collectionID);
   fChain->SetBranchAddress("EcalBarrelImagingHits", &EcalBarrelImagingHits_, &b_EcalBarrelImagingHits_);
   fChain->SetBranchAddress("EcalBarrelImagingHits.cellID", EcalBarrelImagingHits_cellID, &b_EcalBarrelImagingHits_cellID);
   fChain->SetBranchAddress("EcalBarrelImagingHits.energy", EcalBarrelImagingHits_energy, &b_EcalBarrelImagingHits_energy);
   fChain->SetBranchAddress("EcalBarrelImagingHits.position.x", EcalBarrelImagingHits_position_x, &b_EcalBarrelImagingHits_position_x);
   fChain->SetBranchAddress("EcalBarrelImagingHits.position.y", EcalBarrelImagingHits_position_y, &b_EcalBarrelImagingHits_position_y);
   fChain->SetBranchAddress("EcalBarrelImagingHits.position.z", EcalBarrelImagingHits_position_z, &b_EcalBarrelImagingHits_position_z);
   fChain->SetBranchAddress("EcalBarrelImagingHits.contributions_begin", EcalBarrelImagingHits_contributions_begin, &b_EcalBarrelImagingHits_contributions_begin);
   fChain->SetBranchAddress("EcalBarrelImagingHits.contributions_end", EcalBarrelImagingHits_contributions_end, &b_EcalBarrelImagingHits_contributions_end);
   fChain->SetBranchAddress("_EcalBarrelImagingHits_contributions", &_EcalBarrelImagingHits_contributions_, &b__EcalBarrelImagingHits_contributions_);
   fChain->SetBranchAddress("_EcalBarrelImagingHits_contributions.index", _EcalBarrelImagingHits_contributions_index, &b__EcalBarrelImagingHits_contributions_index);
   fChain->SetBranchAddress("_EcalBarrelImagingHits_contributions.collectionID", _EcalBarrelImagingHits_contributions_collectionID, &b__EcalBarrelImagingHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions", &EcalBarrelImagingHitsContributions_, &b_EcalBarrelImagingHitsContributions_);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.PDG", EcalBarrelImagingHitsContributions_PDG, &b_EcalBarrelImagingHitsContributions_PDG);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.energy", EcalBarrelImagingHitsContributions_energy, &b_EcalBarrelImagingHitsContributions_energy);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.time", EcalBarrelImagingHitsContributions_time, &b_EcalBarrelImagingHitsContributions_time);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepPosition.x", EcalBarrelImagingHitsContributions_stepPosition_x, &b_EcalBarrelImagingHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepPosition.y", EcalBarrelImagingHitsContributions_stepPosition_y, &b_EcalBarrelImagingHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepPosition.z", EcalBarrelImagingHitsContributions_stepPosition_z, &b_EcalBarrelImagingHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepLength", EcalBarrelImagingHitsContributions_stepLength, &b_EcalBarrelImagingHitsContributions_stepLength);
   fChain->SetBranchAddress("_EcalBarrelImagingHitsContributions_particle", &_EcalBarrelImagingHitsContributions_particle_, &b__EcalBarrelImagingHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalBarrelImagingHitsContributions_particle.index", _EcalBarrelImagingHitsContributions_particle_index, &b__EcalBarrelImagingHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalBarrelImagingHitsContributions_particle.collectionID", _EcalBarrelImagingHitsContributions_particle_collectionID, &b__EcalBarrelImagingHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalBarrelScFiHits", &EcalBarrelScFiHits_, &b_EcalBarrelScFiHits_);
   fChain->SetBranchAddress("EcalBarrelScFiHits.cellID", &EcalBarrelScFiHits_cellID, &b_EcalBarrelScFiHits_cellID);
   fChain->SetBranchAddress("EcalBarrelScFiHits.energy", &EcalBarrelScFiHits_energy, &b_EcalBarrelScFiHits_energy);
   fChain->SetBranchAddress("EcalBarrelScFiHits.position.x", &EcalBarrelScFiHits_position_x, &b_EcalBarrelScFiHits_position_x);
   fChain->SetBranchAddress("EcalBarrelScFiHits.position.y", &EcalBarrelScFiHits_position_y, &b_EcalBarrelScFiHits_position_y);
   fChain->SetBranchAddress("EcalBarrelScFiHits.position.z", &EcalBarrelScFiHits_position_z, &b_EcalBarrelScFiHits_position_z);
   fChain->SetBranchAddress("EcalBarrelScFiHits.contributions_begin", &EcalBarrelScFiHits_contributions_begin, &b_EcalBarrelScFiHits_contributions_begin);
   fChain->SetBranchAddress("EcalBarrelScFiHits.contributions_end", &EcalBarrelScFiHits_contributions_end, &b_EcalBarrelScFiHits_contributions_end);
   fChain->SetBranchAddress("_EcalBarrelScFiHits_contributions", &_EcalBarrelScFiHits_contributions_, &b__EcalBarrelScFiHits_contributions_);
   fChain->SetBranchAddress("_EcalBarrelScFiHits_contributions.index", &_EcalBarrelScFiHits_contributions_index, &b__EcalBarrelScFiHits_contributions_index);
   fChain->SetBranchAddress("_EcalBarrelScFiHits_contributions.collectionID", &_EcalBarrelScFiHits_contributions_collectionID, &b__EcalBarrelScFiHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions", &EcalBarrelScFiHitsContributions_, &b_EcalBarrelScFiHitsContributions_);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.PDG", &EcalBarrelScFiHitsContributions_PDG, &b_EcalBarrelScFiHitsContributions_PDG);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.energy", &EcalBarrelScFiHitsContributions_energy, &b_EcalBarrelScFiHitsContributions_energy);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.time", &EcalBarrelScFiHitsContributions_time, &b_EcalBarrelScFiHitsContributions_time);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepPosition.x", &EcalBarrelScFiHitsContributions_stepPosition_x, &b_EcalBarrelScFiHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepPosition.y", &EcalBarrelScFiHitsContributions_stepPosition_y, &b_EcalBarrelScFiHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepPosition.z", &EcalBarrelScFiHitsContributions_stepPosition_z, &b_EcalBarrelScFiHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepLength", &EcalBarrelScFiHitsContributions_stepLength, &b_EcalBarrelScFiHitsContributions_stepLength);
   fChain->SetBranchAddress("_EcalBarrelScFiHitsContributions_particle", &_EcalBarrelScFiHitsContributions_particle_, &b__EcalBarrelScFiHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalBarrelScFiHitsContributions_particle.index", &_EcalBarrelScFiHitsContributions_particle_index, &b__EcalBarrelScFiHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalBarrelScFiHitsContributions_particle.collectionID", &_EcalBarrelScFiHitsContributions_particle_collectionID, &b__EcalBarrelScFiHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalEndcapNHits", &EcalEndcapNHits_, &b_EcalEndcapNHits_);
   fChain->SetBranchAddress("EcalEndcapNHits.cellID", EcalEndcapNHits_cellID, &b_EcalEndcapNHits_cellID);
   fChain->SetBranchAddress("EcalEndcapNHits.energy", EcalEndcapNHits_energy, &b_EcalEndcapNHits_energy);
   fChain->SetBranchAddress("EcalEndcapNHits.position.x", EcalEndcapNHits_position_x, &b_EcalEndcapNHits_position_x);
   fChain->SetBranchAddress("EcalEndcapNHits.position.y", EcalEndcapNHits_position_y, &b_EcalEndcapNHits_position_y);
   fChain->SetBranchAddress("EcalEndcapNHits.position.z", EcalEndcapNHits_position_z, &b_EcalEndcapNHits_position_z);
   fChain->SetBranchAddress("EcalEndcapNHits.contributions_begin", EcalEndcapNHits_contributions_begin, &b_EcalEndcapNHits_contributions_begin);
   fChain->SetBranchAddress("EcalEndcapNHits.contributions_end", EcalEndcapNHits_contributions_end, &b_EcalEndcapNHits_contributions_end);
   fChain->SetBranchAddress("_EcalEndcapNHits_contributions", &_EcalEndcapNHits_contributions_, &b__EcalEndcapNHits_contributions_);
   fChain->SetBranchAddress("_EcalEndcapNHits_contributions.index", _EcalEndcapNHits_contributions_index, &b__EcalEndcapNHits_contributions_index);
   fChain->SetBranchAddress("_EcalEndcapNHits_contributions.collectionID", _EcalEndcapNHits_contributions_collectionID, &b__EcalEndcapNHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions", &EcalEndcapNHitsContributions_, &b_EcalEndcapNHitsContributions_);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.PDG", EcalEndcapNHitsContributions_PDG, &b_EcalEndcapNHitsContributions_PDG);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.energy", EcalEndcapNHitsContributions_energy, &b_EcalEndcapNHitsContributions_energy);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.time", EcalEndcapNHitsContributions_time, &b_EcalEndcapNHitsContributions_time);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepPosition.x", EcalEndcapNHitsContributions_stepPosition_x, &b_EcalEndcapNHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepPosition.y", EcalEndcapNHitsContributions_stepPosition_y, &b_EcalEndcapNHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepPosition.z", EcalEndcapNHitsContributions_stepPosition_z, &b_EcalEndcapNHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepLength", EcalEndcapNHitsContributions_stepLength, &b_EcalEndcapNHitsContributions_stepLength);
   fChain->SetBranchAddress("_EcalEndcapNHitsContributions_particle", &_EcalEndcapNHitsContributions_particle_, &b__EcalEndcapNHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalEndcapNHitsContributions_particle.index", _EcalEndcapNHitsContributions_particle_index, &b__EcalEndcapNHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalEndcapNHitsContributions_particle.collectionID", _EcalEndcapNHitsContributions_particle_collectionID, &b__EcalEndcapNHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalEndcapPHits", &EcalEndcapPHits_, &b_EcalEndcapPHits_);
   fChain->SetBranchAddress("EcalEndcapPHits.cellID", EcalEndcapPHits_cellID, &b_EcalEndcapPHits_cellID);
   fChain->SetBranchAddress("EcalEndcapPHits.energy", EcalEndcapPHits_energy, &b_EcalEndcapPHits_energy);
   fChain->SetBranchAddress("EcalEndcapPHits.position.x", EcalEndcapPHits_position_x, &b_EcalEndcapPHits_position_x);
   fChain->SetBranchAddress("EcalEndcapPHits.position.y", EcalEndcapPHits_position_y, &b_EcalEndcapPHits_position_y);
   fChain->SetBranchAddress("EcalEndcapPHits.position.z", EcalEndcapPHits_position_z, &b_EcalEndcapPHits_position_z);
   fChain->SetBranchAddress("EcalEndcapPHits.contributions_begin", EcalEndcapPHits_contributions_begin, &b_EcalEndcapPHits_contributions_begin);
   fChain->SetBranchAddress("EcalEndcapPHits.contributions_end", EcalEndcapPHits_contributions_end, &b_EcalEndcapPHits_contributions_end);
   fChain->SetBranchAddress("_EcalEndcapPHits_contributions", &_EcalEndcapPHits_contributions_, &b__EcalEndcapPHits_contributions_);
   fChain->SetBranchAddress("_EcalEndcapPHits_contributions.index", _EcalEndcapPHits_contributions_index, &b__EcalEndcapPHits_contributions_index);
   fChain->SetBranchAddress("_EcalEndcapPHits_contributions.collectionID", _EcalEndcapPHits_contributions_collectionID, &b__EcalEndcapPHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions", &EcalEndcapPHitsContributions_, &b_EcalEndcapPHitsContributions_);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.PDG", EcalEndcapPHitsContributions_PDG, &b_EcalEndcapPHitsContributions_PDG);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.energy", EcalEndcapPHitsContributions_energy, &b_EcalEndcapPHitsContributions_energy);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.time", EcalEndcapPHitsContributions_time, &b_EcalEndcapPHitsContributions_time);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepPosition.x", EcalEndcapPHitsContributions_stepPosition_x, &b_EcalEndcapPHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepPosition.y", EcalEndcapPHitsContributions_stepPosition_y, &b_EcalEndcapPHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepPosition.z", EcalEndcapPHitsContributions_stepPosition_z, &b_EcalEndcapPHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepLength", EcalEndcapPHitsContributions_stepLength, &b_EcalEndcapPHitsContributions_stepLength);
   fChain->SetBranchAddress("_EcalEndcapPHitsContributions_particle", &_EcalEndcapPHitsContributions_particle_, &b__EcalEndcapPHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalEndcapPHitsContributions_particle.index", _EcalEndcapPHitsContributions_particle_index, &b__EcalEndcapPHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalEndcapPHitsContributions_particle.collectionID", _EcalEndcapPHitsContributions_particle_collectionID, &b__EcalEndcapPHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalFarForwardZDCHits", &EcalFarForwardZDCHits_, &b_EcalFarForwardZDCHits_);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.cellID", &EcalFarForwardZDCHits_cellID, &b_EcalFarForwardZDCHits_cellID);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.energy", &EcalFarForwardZDCHits_energy, &b_EcalFarForwardZDCHits_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.position.x", &EcalFarForwardZDCHits_position_x, &b_EcalFarForwardZDCHits_position_x);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.position.y", &EcalFarForwardZDCHits_position_y, &b_EcalFarForwardZDCHits_position_y);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.position.z", &EcalFarForwardZDCHits_position_z, &b_EcalFarForwardZDCHits_position_z);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.contributions_begin", &EcalFarForwardZDCHits_contributions_begin, &b_EcalFarForwardZDCHits_contributions_begin);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.contributions_end", &EcalFarForwardZDCHits_contributions_end, &b_EcalFarForwardZDCHits_contributions_end);
   fChain->SetBranchAddress("_EcalFarForwardZDCHits_contributions", &_EcalFarForwardZDCHits_contributions_, &b__EcalFarForwardZDCHits_contributions_);
   fChain->SetBranchAddress("_EcalFarForwardZDCHits_contributions.index", &_EcalFarForwardZDCHits_contributions_index, &b__EcalFarForwardZDCHits_contributions_index);
   fChain->SetBranchAddress("_EcalFarForwardZDCHits_contributions.collectionID", &_EcalFarForwardZDCHits_contributions_collectionID, &b__EcalFarForwardZDCHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions", &EcalFarForwardZDCHitsContributions_, &b_EcalFarForwardZDCHitsContributions_);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.PDG", &EcalFarForwardZDCHitsContributions_PDG, &b_EcalFarForwardZDCHitsContributions_PDG);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.energy", &EcalFarForwardZDCHitsContributions_energy, &b_EcalFarForwardZDCHitsContributions_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.time", &EcalFarForwardZDCHitsContributions_time, &b_EcalFarForwardZDCHitsContributions_time);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepPosition.x", &EcalFarForwardZDCHitsContributions_stepPosition_x, &b_EcalFarForwardZDCHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepPosition.y", &EcalFarForwardZDCHitsContributions_stepPosition_y, &b_EcalFarForwardZDCHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepPosition.z", &EcalFarForwardZDCHitsContributions_stepPosition_z, &b_EcalFarForwardZDCHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepLength", &EcalFarForwardZDCHitsContributions_stepLength, &b_EcalFarForwardZDCHitsContributions_stepLength);
   fChain->SetBranchAddress("_EcalFarForwardZDCHitsContributions_particle", &_EcalFarForwardZDCHitsContributions_particle_, &b__EcalFarForwardZDCHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalFarForwardZDCHitsContributions_particle.index", &_EcalFarForwardZDCHitsContributions_particle_index, &b__EcalFarForwardZDCHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalFarForwardZDCHitsContributions_particle.collectionID", &_EcalFarForwardZDCHitsContributions_particle_collectionID, &b__EcalFarForwardZDCHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalLumiSpecHits", &EcalLumiSpecHits_, &b_EcalLumiSpecHits_);
   fChain->SetBranchAddress("EcalLumiSpecHits.cellID", &EcalLumiSpecHits_cellID, &b_EcalLumiSpecHits_cellID);
   fChain->SetBranchAddress("EcalLumiSpecHits.energy", &EcalLumiSpecHits_energy, &b_EcalLumiSpecHits_energy);
   fChain->SetBranchAddress("EcalLumiSpecHits.position.x", &EcalLumiSpecHits_position_x, &b_EcalLumiSpecHits_position_x);
   fChain->SetBranchAddress("EcalLumiSpecHits.position.y", &EcalLumiSpecHits_position_y, &b_EcalLumiSpecHits_position_y);
   fChain->SetBranchAddress("EcalLumiSpecHits.position.z", &EcalLumiSpecHits_position_z, &b_EcalLumiSpecHits_position_z);
   fChain->SetBranchAddress("EcalLumiSpecHits.contributions_begin", &EcalLumiSpecHits_contributions_begin, &b_EcalLumiSpecHits_contributions_begin);
   fChain->SetBranchAddress("EcalLumiSpecHits.contributions_end", &EcalLumiSpecHits_contributions_end, &b_EcalLumiSpecHits_contributions_end);
   fChain->SetBranchAddress("_EcalLumiSpecHits_contributions", &_EcalLumiSpecHits_contributions_, &b__EcalLumiSpecHits_contributions_);
   fChain->SetBranchAddress("_EcalLumiSpecHits_contributions.index", &_EcalLumiSpecHits_contributions_index, &b__EcalLumiSpecHits_contributions_index);
   fChain->SetBranchAddress("_EcalLumiSpecHits_contributions.collectionID", &_EcalLumiSpecHits_contributions_collectionID, &b__EcalLumiSpecHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions", &EcalLumiSpecHitsContributions_, &b_EcalLumiSpecHitsContributions_);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.PDG", &EcalLumiSpecHitsContributions_PDG, &b_EcalLumiSpecHitsContributions_PDG);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.energy", &EcalLumiSpecHitsContributions_energy, &b_EcalLumiSpecHitsContributions_energy);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.time", &EcalLumiSpecHitsContributions_time, &b_EcalLumiSpecHitsContributions_time);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepPosition.x", &EcalLumiSpecHitsContributions_stepPosition_x, &b_EcalLumiSpecHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepPosition.y", &EcalLumiSpecHitsContributions_stepPosition_y, &b_EcalLumiSpecHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepPosition.z", &EcalLumiSpecHitsContributions_stepPosition_z, &b_EcalLumiSpecHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepLength", &EcalLumiSpecHitsContributions_stepLength, &b_EcalLumiSpecHitsContributions_stepLength);
   fChain->SetBranchAddress("_EcalLumiSpecHitsContributions_particle", &_EcalLumiSpecHitsContributions_particle_, &b__EcalLumiSpecHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalLumiSpecHitsContributions_particle.index", &_EcalLumiSpecHitsContributions_particle_index, &b__EcalLumiSpecHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalLumiSpecHitsContributions_particle.collectionID", &_EcalLumiSpecHitsContributions_particle_collectionID, &b__EcalLumiSpecHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EventHeader", &EventHeader_, &b_EventHeader_);
   fChain->SetBranchAddress("EventHeader.eventNumber", EventHeader_eventNumber, &b_EventHeader_eventNumber);
   fChain->SetBranchAddress("EventHeader.runNumber", EventHeader_runNumber, &b_EventHeader_runNumber);
   fChain->SetBranchAddress("EventHeader.timeStamp", EventHeader_timeStamp, &b_EventHeader_timeStamp);
   fChain->SetBranchAddress("EventHeader.weight", EventHeader_weight, &b_EventHeader_weight);
   fChain->SetBranchAddress("EventHeader.weights_begin", EventHeader_weights_begin, &b_EventHeader_weights_begin);
   fChain->SetBranchAddress("EventHeader.weights_end", EventHeader_weights_end, &b_EventHeader_weights_end);
   fChain->SetBranchAddress("_EventHeader_weights", &_EventHeader_weights, &b__EventHeader_weights);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits", &ForwardMPGDEndcapHits_, &b_ForwardMPGDEndcapHits_);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.cellID", ForwardMPGDEndcapHits_cellID, &b_ForwardMPGDEndcapHits_cellID);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.eDep", ForwardMPGDEndcapHits_eDep, &b_ForwardMPGDEndcapHits_eDep);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.time", ForwardMPGDEndcapHits_time, &b_ForwardMPGDEndcapHits_time);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.pathLength", ForwardMPGDEndcapHits_pathLength, &b_ForwardMPGDEndcapHits_pathLength);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.quality", ForwardMPGDEndcapHits_quality, &b_ForwardMPGDEndcapHits_quality);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.position.x", ForwardMPGDEndcapHits_position_x, &b_ForwardMPGDEndcapHits_position_x);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.position.y", ForwardMPGDEndcapHits_position_y, &b_ForwardMPGDEndcapHits_position_y);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.position.z", ForwardMPGDEndcapHits_position_z, &b_ForwardMPGDEndcapHits_position_z);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.momentum.x", ForwardMPGDEndcapHits_momentum_x, &b_ForwardMPGDEndcapHits_momentum_x);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.momentum.y", ForwardMPGDEndcapHits_momentum_y, &b_ForwardMPGDEndcapHits_momentum_y);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.momentum.z", ForwardMPGDEndcapHits_momentum_z, &b_ForwardMPGDEndcapHits_momentum_z);
   fChain->SetBranchAddress("_ForwardMPGDEndcapHits_particle", &_ForwardMPGDEndcapHits_particle_, &b__ForwardMPGDEndcapHits_particle_);
   fChain->SetBranchAddress("_ForwardMPGDEndcapHits_particle.index", _ForwardMPGDEndcapHits_particle_index, &b__ForwardMPGDEndcapHits_particle_index);
   fChain->SetBranchAddress("_ForwardMPGDEndcapHits_particle.collectionID", _ForwardMPGDEndcapHits_particle_collectionID, &b__ForwardMPGDEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("ForwardOffMTrackerHits", &ForwardOffMTrackerHits_, &b_ForwardOffMTrackerHits_);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.cellID", &ForwardOffMTrackerHits_cellID, &b_ForwardOffMTrackerHits_cellID);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.eDep", &ForwardOffMTrackerHits_eDep, &b_ForwardOffMTrackerHits_eDep);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.time", &ForwardOffMTrackerHits_time, &b_ForwardOffMTrackerHits_time);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.pathLength", &ForwardOffMTrackerHits_pathLength, &b_ForwardOffMTrackerHits_pathLength);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.quality", &ForwardOffMTrackerHits_quality, &b_ForwardOffMTrackerHits_quality);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.position.x", &ForwardOffMTrackerHits_position_x, &b_ForwardOffMTrackerHits_position_x);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.position.y", &ForwardOffMTrackerHits_position_y, &b_ForwardOffMTrackerHits_position_y);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.position.z", &ForwardOffMTrackerHits_position_z, &b_ForwardOffMTrackerHits_position_z);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.momentum.x", &ForwardOffMTrackerHits_momentum_x, &b_ForwardOffMTrackerHits_momentum_x);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.momentum.y", &ForwardOffMTrackerHits_momentum_y, &b_ForwardOffMTrackerHits_momentum_y);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.momentum.z", &ForwardOffMTrackerHits_momentum_z, &b_ForwardOffMTrackerHits_momentum_z);
   fChain->SetBranchAddress("_ForwardOffMTrackerHits_particle", &_ForwardOffMTrackerHits_particle_, &b__ForwardOffMTrackerHits_particle_);
   fChain->SetBranchAddress("_ForwardOffMTrackerHits_particle.index", &_ForwardOffMTrackerHits_particle_index, &b__ForwardOffMTrackerHits_particle_index);
   fChain->SetBranchAddress("_ForwardOffMTrackerHits_particle.collectionID", &_ForwardOffMTrackerHits_particle_collectionID, &b__ForwardOffMTrackerHits_particle_collectionID);
   fChain->SetBranchAddress("ForwardRomanPotHits", &ForwardRomanPotHits_, &b_ForwardRomanPotHits_);
   fChain->SetBranchAddress("ForwardRomanPotHits.cellID", &ForwardRomanPotHits_cellID, &b_ForwardRomanPotHits_cellID);
   fChain->SetBranchAddress("ForwardRomanPotHits.eDep", &ForwardRomanPotHits_eDep, &b_ForwardRomanPotHits_eDep);
   fChain->SetBranchAddress("ForwardRomanPotHits.time", &ForwardRomanPotHits_time, &b_ForwardRomanPotHits_time);
   fChain->SetBranchAddress("ForwardRomanPotHits.pathLength", &ForwardRomanPotHits_pathLength, &b_ForwardRomanPotHits_pathLength);
   fChain->SetBranchAddress("ForwardRomanPotHits.quality", &ForwardRomanPotHits_quality, &b_ForwardRomanPotHits_quality);
   fChain->SetBranchAddress("ForwardRomanPotHits.position.x", &ForwardRomanPotHits_position_x, &b_ForwardRomanPotHits_position_x);
   fChain->SetBranchAddress("ForwardRomanPotHits.position.y", &ForwardRomanPotHits_position_y, &b_ForwardRomanPotHits_position_y);
   fChain->SetBranchAddress("ForwardRomanPotHits.position.z", &ForwardRomanPotHits_position_z, &b_ForwardRomanPotHits_position_z);
   fChain->SetBranchAddress("ForwardRomanPotHits.momentum.x", &ForwardRomanPotHits_momentum_x, &b_ForwardRomanPotHits_momentum_x);
   fChain->SetBranchAddress("ForwardRomanPotHits.momentum.y", &ForwardRomanPotHits_momentum_y, &b_ForwardRomanPotHits_momentum_y);
   fChain->SetBranchAddress("ForwardRomanPotHits.momentum.z", &ForwardRomanPotHits_momentum_z, &b_ForwardRomanPotHits_momentum_z);
   fChain->SetBranchAddress("_ForwardRomanPotHits_particle", &_ForwardRomanPotHits_particle_, &b__ForwardRomanPotHits_particle_);
   fChain->SetBranchAddress("_ForwardRomanPotHits_particle.index", &_ForwardRomanPotHits_particle_index, &b__ForwardRomanPotHits_particle_index);
   fChain->SetBranchAddress("_ForwardRomanPotHits_particle.collectionID", &_ForwardRomanPotHits_particle_collectionID, &b__ForwardRomanPotHits_particle_collectionID);
   fChain->SetBranchAddress("HcalBarrelHits", &HcalBarrelHits_, &b_HcalBarrelHits_);
   fChain->SetBranchAddress("HcalBarrelHits.cellID", &HcalBarrelHits_cellID, &b_HcalBarrelHits_cellID);
   fChain->SetBranchAddress("HcalBarrelHits.energy", &HcalBarrelHits_energy, &b_HcalBarrelHits_energy);
   fChain->SetBranchAddress("HcalBarrelHits.position.x", &HcalBarrelHits_position_x, &b_HcalBarrelHits_position_x);
   fChain->SetBranchAddress("HcalBarrelHits.position.y", &HcalBarrelHits_position_y, &b_HcalBarrelHits_position_y);
   fChain->SetBranchAddress("HcalBarrelHits.position.z", &HcalBarrelHits_position_z, &b_HcalBarrelHits_position_z);
   fChain->SetBranchAddress("HcalBarrelHits.contributions_begin", &HcalBarrelHits_contributions_begin, &b_HcalBarrelHits_contributions_begin);
   fChain->SetBranchAddress("HcalBarrelHits.contributions_end", &HcalBarrelHits_contributions_end, &b_HcalBarrelHits_contributions_end);
   fChain->SetBranchAddress("_HcalBarrelHits_contributions", &_HcalBarrelHits_contributions_, &b__HcalBarrelHits_contributions_);
   fChain->SetBranchAddress("_HcalBarrelHits_contributions.index", &_HcalBarrelHits_contributions_index, &b__HcalBarrelHits_contributions_index);
   fChain->SetBranchAddress("_HcalBarrelHits_contributions.collectionID", &_HcalBarrelHits_contributions_collectionID, &b__HcalBarrelHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalBarrelHitsContributions", &HcalBarrelHitsContributions_, &b_HcalBarrelHitsContributions_);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.PDG", &HcalBarrelHitsContributions_PDG, &b_HcalBarrelHitsContributions_PDG);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.energy", &HcalBarrelHitsContributions_energy, &b_HcalBarrelHitsContributions_energy);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.time", &HcalBarrelHitsContributions_time, &b_HcalBarrelHitsContributions_time);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepPosition.x", &HcalBarrelHitsContributions_stepPosition_x, &b_HcalBarrelHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepPosition.y", &HcalBarrelHitsContributions_stepPosition_y, &b_HcalBarrelHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepPosition.z", &HcalBarrelHitsContributions_stepPosition_z, &b_HcalBarrelHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepLength", &HcalBarrelHitsContributions_stepLength, &b_HcalBarrelHitsContributions_stepLength);
   fChain->SetBranchAddress("_HcalBarrelHitsContributions_particle", &_HcalBarrelHitsContributions_particle_, &b__HcalBarrelHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalBarrelHitsContributions_particle.index", &_HcalBarrelHitsContributions_particle_index, &b__HcalBarrelHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalBarrelHitsContributions_particle.collectionID", &_HcalBarrelHitsContributions_particle_collectionID, &b__HcalBarrelHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("HcalEndcapNHits", &HcalEndcapNHits_, &b_HcalEndcapNHits_);
   fChain->SetBranchAddress("HcalEndcapNHits.cellID", &HcalEndcapNHits_cellID, &b_HcalEndcapNHits_cellID);
   fChain->SetBranchAddress("HcalEndcapNHits.energy", &HcalEndcapNHits_energy, &b_HcalEndcapNHits_energy);
   fChain->SetBranchAddress("HcalEndcapNHits.position.x", &HcalEndcapNHits_position_x, &b_HcalEndcapNHits_position_x);
   fChain->SetBranchAddress("HcalEndcapNHits.position.y", &HcalEndcapNHits_position_y, &b_HcalEndcapNHits_position_y);
   fChain->SetBranchAddress("HcalEndcapNHits.position.z", &HcalEndcapNHits_position_z, &b_HcalEndcapNHits_position_z);
   fChain->SetBranchAddress("HcalEndcapNHits.contributions_begin", &HcalEndcapNHits_contributions_begin, &b_HcalEndcapNHits_contributions_begin);
   fChain->SetBranchAddress("HcalEndcapNHits.contributions_end", &HcalEndcapNHits_contributions_end, &b_HcalEndcapNHits_contributions_end);
   fChain->SetBranchAddress("_HcalEndcapNHits_contributions", &_HcalEndcapNHits_contributions_, &b__HcalEndcapNHits_contributions_);
   fChain->SetBranchAddress("_HcalEndcapNHits_contributions.index", &_HcalEndcapNHits_contributions_index, &b__HcalEndcapNHits_contributions_index);
   fChain->SetBranchAddress("_HcalEndcapNHits_contributions.collectionID", &_HcalEndcapNHits_contributions_collectionID, &b__HcalEndcapNHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions", &HcalEndcapNHitsContributions_, &b_HcalEndcapNHitsContributions_);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.PDG", &HcalEndcapNHitsContributions_PDG, &b_HcalEndcapNHitsContributions_PDG);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.energy", &HcalEndcapNHitsContributions_energy, &b_HcalEndcapNHitsContributions_energy);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.time", &HcalEndcapNHitsContributions_time, &b_HcalEndcapNHitsContributions_time);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepPosition.x", &HcalEndcapNHitsContributions_stepPosition_x, &b_HcalEndcapNHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepPosition.y", &HcalEndcapNHitsContributions_stepPosition_y, &b_HcalEndcapNHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepPosition.z", &HcalEndcapNHitsContributions_stepPosition_z, &b_HcalEndcapNHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepLength", &HcalEndcapNHitsContributions_stepLength, &b_HcalEndcapNHitsContributions_stepLength);
   fChain->SetBranchAddress("_HcalEndcapNHitsContributions_particle", &_HcalEndcapNHitsContributions_particle_, &b__HcalEndcapNHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalEndcapNHitsContributions_particle.index", &_HcalEndcapNHitsContributions_particle_index, &b__HcalEndcapNHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalEndcapNHitsContributions_particle.collectionID", &_HcalEndcapNHitsContributions_particle_collectionID, &b__HcalEndcapNHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("HcalEndcapPInsertHits", &HcalEndcapPInsertHits_, &b_HcalEndcapPInsertHits_);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.cellID", &HcalEndcapPInsertHits_cellID, &b_HcalEndcapPInsertHits_cellID);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.energy", &HcalEndcapPInsertHits_energy, &b_HcalEndcapPInsertHits_energy);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.position.x", &HcalEndcapPInsertHits_position_x, &b_HcalEndcapPInsertHits_position_x);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.position.y", &HcalEndcapPInsertHits_position_y, &b_HcalEndcapPInsertHits_position_y);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.position.z", &HcalEndcapPInsertHits_position_z, &b_HcalEndcapPInsertHits_position_z);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.contributions_begin", &HcalEndcapPInsertHits_contributions_begin, &b_HcalEndcapPInsertHits_contributions_begin);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.contributions_end", &HcalEndcapPInsertHits_contributions_end, &b_HcalEndcapPInsertHits_contributions_end);
   fChain->SetBranchAddress("_HcalEndcapPInsertHits_contributions", &_HcalEndcapPInsertHits_contributions_, &b__HcalEndcapPInsertHits_contributions_);
   fChain->SetBranchAddress("_HcalEndcapPInsertHits_contributions.index", &_HcalEndcapPInsertHits_contributions_index, &b__HcalEndcapPInsertHits_contributions_index);
   fChain->SetBranchAddress("_HcalEndcapPInsertHits_contributions.collectionID", &_HcalEndcapPInsertHits_contributions_collectionID, &b__HcalEndcapPInsertHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions", &HcalEndcapPInsertHitsContributions_, &b_HcalEndcapPInsertHitsContributions_);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.PDG", &HcalEndcapPInsertHitsContributions_PDG, &b_HcalEndcapPInsertHitsContributions_PDG);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.energy", &HcalEndcapPInsertHitsContributions_energy, &b_HcalEndcapPInsertHitsContributions_energy);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.time", &HcalEndcapPInsertHitsContributions_time, &b_HcalEndcapPInsertHitsContributions_time);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepPosition.x", &HcalEndcapPInsertHitsContributions_stepPosition_x, &b_HcalEndcapPInsertHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepPosition.y", &HcalEndcapPInsertHitsContributions_stepPosition_y, &b_HcalEndcapPInsertHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepPosition.z", &HcalEndcapPInsertHitsContributions_stepPosition_z, &b_HcalEndcapPInsertHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepLength", &HcalEndcapPInsertHitsContributions_stepLength, &b_HcalEndcapPInsertHitsContributions_stepLength);
   fChain->SetBranchAddress("_HcalEndcapPInsertHitsContributions_particle", &_HcalEndcapPInsertHitsContributions_particle_, &b__HcalEndcapPInsertHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalEndcapPInsertHitsContributions_particle.index", &_HcalEndcapPInsertHitsContributions_particle_index, &b__HcalEndcapPInsertHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalEndcapPInsertHitsContributions_particle.collectionID", &_HcalEndcapPInsertHitsContributions_particle_collectionID, &b__HcalEndcapPInsertHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("HcalFarForwardZDCHits", &HcalFarForwardZDCHits_, &b_HcalFarForwardZDCHits_);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.cellID", &HcalFarForwardZDCHits_cellID, &b_HcalFarForwardZDCHits_cellID);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.energy", &HcalFarForwardZDCHits_energy, &b_HcalFarForwardZDCHits_energy);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.position.x", &HcalFarForwardZDCHits_position_x, &b_HcalFarForwardZDCHits_position_x);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.position.y", &HcalFarForwardZDCHits_position_y, &b_HcalFarForwardZDCHits_position_y);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.position.z", &HcalFarForwardZDCHits_position_z, &b_HcalFarForwardZDCHits_position_z);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.contributions_begin", &HcalFarForwardZDCHits_contributions_begin, &b_HcalFarForwardZDCHits_contributions_begin);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.contributions_end", &HcalFarForwardZDCHits_contributions_end, &b_HcalFarForwardZDCHits_contributions_end);
   fChain->SetBranchAddress("_HcalFarForwardZDCHits_contributions", &_HcalFarForwardZDCHits_contributions_, &b__HcalFarForwardZDCHits_contributions_);
   fChain->SetBranchAddress("_HcalFarForwardZDCHits_contributions.index", &_HcalFarForwardZDCHits_contributions_index, &b__HcalFarForwardZDCHits_contributions_index);
   fChain->SetBranchAddress("_HcalFarForwardZDCHits_contributions.collectionID", &_HcalFarForwardZDCHits_contributions_collectionID, &b__HcalFarForwardZDCHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions", &HcalFarForwardZDCHitsContributions_, &b_HcalFarForwardZDCHitsContributions_);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.PDG", &HcalFarForwardZDCHitsContributions_PDG, &b_HcalFarForwardZDCHitsContributions_PDG);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.energy", &HcalFarForwardZDCHitsContributions_energy, &b_HcalFarForwardZDCHitsContributions_energy);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.time", &HcalFarForwardZDCHitsContributions_time, &b_HcalFarForwardZDCHitsContributions_time);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepPosition.x", &HcalFarForwardZDCHitsContributions_stepPosition_x, &b_HcalFarForwardZDCHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepPosition.y", &HcalFarForwardZDCHitsContributions_stepPosition_y, &b_HcalFarForwardZDCHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepPosition.z", &HcalFarForwardZDCHitsContributions_stepPosition_z, &b_HcalFarForwardZDCHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepLength", &HcalFarForwardZDCHitsContributions_stepLength, &b_HcalFarForwardZDCHitsContributions_stepLength);
   fChain->SetBranchAddress("_HcalFarForwardZDCHitsContributions_particle", &_HcalFarForwardZDCHitsContributions_particle_, &b__HcalFarForwardZDCHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalFarForwardZDCHitsContributions_particle.index", &_HcalFarForwardZDCHitsContributions_particle_index, &b__HcalFarForwardZDCHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalFarForwardZDCHitsContributions_particle.collectionID", &_HcalFarForwardZDCHitsContributions_particle_collectionID, &b__HcalFarForwardZDCHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("LFHCALHits", &LFHCALHits_, &b_LFHCALHits_);
   fChain->SetBranchAddress("LFHCALHits.cellID", &LFHCALHits_cellID, &b_LFHCALHits_cellID);
   fChain->SetBranchAddress("LFHCALHits.energy", &LFHCALHits_energy, &b_LFHCALHits_energy);
   fChain->SetBranchAddress("LFHCALHits.position.x", &LFHCALHits_position_x, &b_LFHCALHits_position_x);
   fChain->SetBranchAddress("LFHCALHits.position.y", &LFHCALHits_position_y, &b_LFHCALHits_position_y);
   fChain->SetBranchAddress("LFHCALHits.position.z", &LFHCALHits_position_z, &b_LFHCALHits_position_z);
   fChain->SetBranchAddress("LFHCALHits.contributions_begin", &LFHCALHits_contributions_begin, &b_LFHCALHits_contributions_begin);
   fChain->SetBranchAddress("LFHCALHits.contributions_end", &LFHCALHits_contributions_end, &b_LFHCALHits_contributions_end);
   fChain->SetBranchAddress("_LFHCALHits_contributions", &_LFHCALHits_contributions_, &b__LFHCALHits_contributions_);
   fChain->SetBranchAddress("_LFHCALHits_contributions.index", &_LFHCALHits_contributions_index, &b__LFHCALHits_contributions_index);
   fChain->SetBranchAddress("_LFHCALHits_contributions.collectionID", &_LFHCALHits_contributions_collectionID, &b__LFHCALHits_contributions_collectionID);
   fChain->SetBranchAddress("LFHCALHitsContributions", &LFHCALHitsContributions_, &b_LFHCALHitsContributions_);
   fChain->SetBranchAddress("LFHCALHitsContributions.PDG", &LFHCALHitsContributions_PDG, &b_LFHCALHitsContributions_PDG);
   fChain->SetBranchAddress("LFHCALHitsContributions.energy", &LFHCALHitsContributions_energy, &b_LFHCALHitsContributions_energy);
   fChain->SetBranchAddress("LFHCALHitsContributions.time", &LFHCALHitsContributions_time, &b_LFHCALHitsContributions_time);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepPosition.x", &LFHCALHitsContributions_stepPosition_x, &b_LFHCALHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepPosition.y", &LFHCALHitsContributions_stepPosition_y, &b_LFHCALHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepPosition.z", &LFHCALHitsContributions_stepPosition_z, &b_LFHCALHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepLength", &LFHCALHitsContributions_stepLength, &b_LFHCALHitsContributions_stepLength);
   fChain->SetBranchAddress("_LFHCALHitsContributions_particle", &_LFHCALHitsContributions_particle_, &b__LFHCALHitsContributions_particle_);
   fChain->SetBranchAddress("_LFHCALHitsContributions_particle.index", &_LFHCALHitsContributions_particle_index, &b__LFHCALHitsContributions_particle_index);
   fChain->SetBranchAddress("_LFHCALHitsContributions_particle.collectionID", &_LFHCALHitsContributions_particle_collectionID, &b__LFHCALHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("LumiDirectPCALHits", &LumiDirectPCALHits_, &b_LumiDirectPCALHits_);
   fChain->SetBranchAddress("LumiDirectPCALHits.cellID", &LumiDirectPCALHits_cellID, &b_LumiDirectPCALHits_cellID);
   fChain->SetBranchAddress("LumiDirectPCALHits.energy", &LumiDirectPCALHits_energy, &b_LumiDirectPCALHits_energy);
   fChain->SetBranchAddress("LumiDirectPCALHits.position.x", &LumiDirectPCALHits_position_x, &b_LumiDirectPCALHits_position_x);
   fChain->SetBranchAddress("LumiDirectPCALHits.position.y", &LumiDirectPCALHits_position_y, &b_LumiDirectPCALHits_position_y);
   fChain->SetBranchAddress("LumiDirectPCALHits.position.z", &LumiDirectPCALHits_position_z, &b_LumiDirectPCALHits_position_z);
   fChain->SetBranchAddress("LumiDirectPCALHits.contributions_begin", &LumiDirectPCALHits_contributions_begin, &b_LumiDirectPCALHits_contributions_begin);
   fChain->SetBranchAddress("LumiDirectPCALHits.contributions_end", &LumiDirectPCALHits_contributions_end, &b_LumiDirectPCALHits_contributions_end);
   fChain->SetBranchAddress("_LumiDirectPCALHits_contributions", &_LumiDirectPCALHits_contributions_, &b__LumiDirectPCALHits_contributions_);
   fChain->SetBranchAddress("_LumiDirectPCALHits_contributions.index", &_LumiDirectPCALHits_contributions_index, &b__LumiDirectPCALHits_contributions_index);
   fChain->SetBranchAddress("_LumiDirectPCALHits_contributions.collectionID", &_LumiDirectPCALHits_contributions_collectionID, &b__LumiDirectPCALHits_contributions_collectionID);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions", &LumiDirectPCALHitsContributions_, &b_LumiDirectPCALHitsContributions_);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.PDG", &LumiDirectPCALHitsContributions_PDG, &b_LumiDirectPCALHitsContributions_PDG);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.energy", &LumiDirectPCALHitsContributions_energy, &b_LumiDirectPCALHitsContributions_energy);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.time", &LumiDirectPCALHitsContributions_time, &b_LumiDirectPCALHitsContributions_time);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepPosition.x", &LumiDirectPCALHitsContributions_stepPosition_x, &b_LumiDirectPCALHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepPosition.y", &LumiDirectPCALHitsContributions_stepPosition_y, &b_LumiDirectPCALHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepPosition.z", &LumiDirectPCALHitsContributions_stepPosition_z, &b_LumiDirectPCALHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepLength", &LumiDirectPCALHitsContributions_stepLength, &b_LumiDirectPCALHitsContributions_stepLength);
   fChain->SetBranchAddress("_LumiDirectPCALHitsContributions_particle", &_LumiDirectPCALHitsContributions_particle_, &b__LumiDirectPCALHitsContributions_particle_);
   fChain->SetBranchAddress("_LumiDirectPCALHitsContributions_particle.index", &_LumiDirectPCALHitsContributions_particle_index, &b__LumiDirectPCALHitsContributions_particle_index);
   fChain->SetBranchAddress("_LumiDirectPCALHitsContributions_particle.collectionID", &_LumiDirectPCALHitsContributions_particle_collectionID, &b__LumiDirectPCALHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("LumiSpecTrackerHits", &LumiSpecTrackerHits_, &b_LumiSpecTrackerHits_);
   fChain->SetBranchAddress("LumiSpecTrackerHits.cellID", &LumiSpecTrackerHits_cellID, &b_LumiSpecTrackerHits_cellID);
   fChain->SetBranchAddress("LumiSpecTrackerHits.eDep", &LumiSpecTrackerHits_eDep, &b_LumiSpecTrackerHits_eDep);
   fChain->SetBranchAddress("LumiSpecTrackerHits.time", &LumiSpecTrackerHits_time, &b_LumiSpecTrackerHits_time);
   fChain->SetBranchAddress("LumiSpecTrackerHits.pathLength", &LumiSpecTrackerHits_pathLength, &b_LumiSpecTrackerHits_pathLength);
   fChain->SetBranchAddress("LumiSpecTrackerHits.quality", &LumiSpecTrackerHits_quality, &b_LumiSpecTrackerHits_quality);
   fChain->SetBranchAddress("LumiSpecTrackerHits.position.x", &LumiSpecTrackerHits_position_x, &b_LumiSpecTrackerHits_position_x);
   fChain->SetBranchAddress("LumiSpecTrackerHits.position.y", &LumiSpecTrackerHits_position_y, &b_LumiSpecTrackerHits_position_y);
   fChain->SetBranchAddress("LumiSpecTrackerHits.position.z", &LumiSpecTrackerHits_position_z, &b_LumiSpecTrackerHits_position_z);
   fChain->SetBranchAddress("LumiSpecTrackerHits.momentum.x", &LumiSpecTrackerHits_momentum_x, &b_LumiSpecTrackerHits_momentum_x);
   fChain->SetBranchAddress("LumiSpecTrackerHits.momentum.y", &LumiSpecTrackerHits_momentum_y, &b_LumiSpecTrackerHits_momentum_y);
   fChain->SetBranchAddress("LumiSpecTrackerHits.momentum.z", &LumiSpecTrackerHits_momentum_z, &b_LumiSpecTrackerHits_momentum_z);
   fChain->SetBranchAddress("_LumiSpecTrackerHits_particle", &_LumiSpecTrackerHits_particle_, &b__LumiSpecTrackerHits_particle_);
   fChain->SetBranchAddress("_LumiSpecTrackerHits_particle.index", &_LumiSpecTrackerHits_particle_index, &b__LumiSpecTrackerHits_particle_index);
   fChain->SetBranchAddress("_LumiSpecTrackerHits_particle.collectionID", &_LumiSpecTrackerHits_particle_collectionID, &b__LumiSpecTrackerHits_particle_collectionID);
   fChain->SetBranchAddress("MCParticles", &MCParticles_, &b_MCParticles_);
   fChain->SetBranchAddress("MCParticles.PDG", MCParticles_PDG, &b_MCParticles_PDG);
   fChain->SetBranchAddress("MCParticles.generatorStatus", MCParticles_generatorStatus, &b_MCParticles_generatorStatus);
   fChain->SetBranchAddress("MCParticles.simulatorStatus", MCParticles_simulatorStatus, &b_MCParticles_simulatorStatus);
   fChain->SetBranchAddress("MCParticles.charge", MCParticles_charge, &b_MCParticles_charge);
   fChain->SetBranchAddress("MCParticles.time", MCParticles_time, &b_MCParticles_time);
   fChain->SetBranchAddress("MCParticles.mass", MCParticles_mass, &b_MCParticles_mass);
   fChain->SetBranchAddress("MCParticles.vertex.x", MCParticles_vertex_x, &b_MCParticles_vertex_x);
   fChain->SetBranchAddress("MCParticles.vertex.y", MCParticles_vertex_y, &b_MCParticles_vertex_y);
   fChain->SetBranchAddress("MCParticles.vertex.z", MCParticles_vertex_z, &b_MCParticles_vertex_z);
   fChain->SetBranchAddress("MCParticles.endpoint.x", MCParticles_endpoint_x, &b_MCParticles_endpoint_x);
   fChain->SetBranchAddress("MCParticles.endpoint.y", MCParticles_endpoint_y, &b_MCParticles_endpoint_y);
   fChain->SetBranchAddress("MCParticles.endpoint.z", MCParticles_endpoint_z, &b_MCParticles_endpoint_z);
   fChain->SetBranchAddress("MCParticles.momentum.x", MCParticles_momentum_x, &b_MCParticles_momentum_x);
   fChain->SetBranchAddress("MCParticles.momentum.y", MCParticles_momentum_y, &b_MCParticles_momentum_y);
   fChain->SetBranchAddress("MCParticles.momentum.z", MCParticles_momentum_z, &b_MCParticles_momentum_z);
   fChain->SetBranchAddress("MCParticles.momentumAtEndpoint.x", MCParticles_momentumAtEndpoint_x, &b_MCParticles_momentumAtEndpoint_x);
   fChain->SetBranchAddress("MCParticles.momentumAtEndpoint.y", MCParticles_momentumAtEndpoint_y, &b_MCParticles_momentumAtEndpoint_y);
   fChain->SetBranchAddress("MCParticles.momentumAtEndpoint.z", MCParticles_momentumAtEndpoint_z, &b_MCParticles_momentumAtEndpoint_z);
   fChain->SetBranchAddress("MCParticles.helicity", MCParticles_helicity, &b_MCParticles_helicity);
   fChain->SetBranchAddress("MCParticles.parents_begin", MCParticles_parents_begin, &b_MCParticles_parents_begin);
   fChain->SetBranchAddress("MCParticles.parents_end", MCParticles_parents_end, &b_MCParticles_parents_end);
   fChain->SetBranchAddress("MCParticles.daughters_begin", MCParticles_daughters_begin, &b_MCParticles_daughters_begin);
   fChain->SetBranchAddress("MCParticles.daughters_end", MCParticles_daughters_end, &b_MCParticles_daughters_end);
   fChain->SetBranchAddress("_MCParticles_parents", &_MCParticles_parents_, &b__MCParticles_parents_);
   fChain->SetBranchAddress("_MCParticles_parents.index", _MCParticles_parents_index, &b__MCParticles_parents_index);
   fChain->SetBranchAddress("_MCParticles_parents.collectionID", _MCParticles_parents_collectionID, &b__MCParticles_parents_collectionID);
   fChain->SetBranchAddress("_MCParticles_daughters", &_MCParticles_daughters_, &b__MCParticles_daughters_);
   fChain->SetBranchAddress("_MCParticles_daughters.index", _MCParticles_daughters_index, &b__MCParticles_daughters_index);
   fChain->SetBranchAddress("_MCParticles_daughters.collectionID", _MCParticles_daughters_collectionID, &b__MCParticles_daughters_collectionID);
   fChain->SetBranchAddress("MPGDBarrelHits", &MPGDBarrelHits_, &b_MPGDBarrelHits_);
   fChain->SetBranchAddress("MPGDBarrelHits.cellID", MPGDBarrelHits_cellID, &b_MPGDBarrelHits_cellID);
   fChain->SetBranchAddress("MPGDBarrelHits.eDep", MPGDBarrelHits_eDep, &b_MPGDBarrelHits_eDep);
   fChain->SetBranchAddress("MPGDBarrelHits.time", MPGDBarrelHits_time, &b_MPGDBarrelHits_time);
   fChain->SetBranchAddress("MPGDBarrelHits.pathLength", MPGDBarrelHits_pathLength, &b_MPGDBarrelHits_pathLength);
   fChain->SetBranchAddress("MPGDBarrelHits.quality", MPGDBarrelHits_quality, &b_MPGDBarrelHits_quality);
   fChain->SetBranchAddress("MPGDBarrelHits.position.x", MPGDBarrelHits_position_x, &b_MPGDBarrelHits_position_x);
   fChain->SetBranchAddress("MPGDBarrelHits.position.y", MPGDBarrelHits_position_y, &b_MPGDBarrelHits_position_y);
   fChain->SetBranchAddress("MPGDBarrelHits.position.z", MPGDBarrelHits_position_z, &b_MPGDBarrelHits_position_z);
   fChain->SetBranchAddress("MPGDBarrelHits.momentum.x", MPGDBarrelHits_momentum_x, &b_MPGDBarrelHits_momentum_x);
   fChain->SetBranchAddress("MPGDBarrelHits.momentum.y", MPGDBarrelHits_momentum_y, &b_MPGDBarrelHits_momentum_y);
   fChain->SetBranchAddress("MPGDBarrelHits.momentum.z", MPGDBarrelHits_momentum_z, &b_MPGDBarrelHits_momentum_z);
   fChain->SetBranchAddress("_MPGDBarrelHits_particle", &_MPGDBarrelHits_particle_, &b__MPGDBarrelHits_particle_);
   fChain->SetBranchAddress("_MPGDBarrelHits_particle.index", _MPGDBarrelHits_particle_index, &b__MPGDBarrelHits_particle_index);
   fChain->SetBranchAddress("_MPGDBarrelHits_particle.collectionID", _MPGDBarrelHits_particle_collectionID, &b__MPGDBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("OuterMPGDBarrelHits", &OuterMPGDBarrelHits_, &b_OuterMPGDBarrelHits_);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.cellID", OuterMPGDBarrelHits_cellID, &b_OuterMPGDBarrelHits_cellID);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.eDep", OuterMPGDBarrelHits_eDep, &b_OuterMPGDBarrelHits_eDep);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.time", OuterMPGDBarrelHits_time, &b_OuterMPGDBarrelHits_time);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.pathLength", OuterMPGDBarrelHits_pathLength, &b_OuterMPGDBarrelHits_pathLength);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.quality", OuterMPGDBarrelHits_quality, &b_OuterMPGDBarrelHits_quality);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.position.x", OuterMPGDBarrelHits_position_x, &b_OuterMPGDBarrelHits_position_x);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.position.y", OuterMPGDBarrelHits_position_y, &b_OuterMPGDBarrelHits_position_y);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.position.z", OuterMPGDBarrelHits_position_z, &b_OuterMPGDBarrelHits_position_z);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.momentum.x", OuterMPGDBarrelHits_momentum_x, &b_OuterMPGDBarrelHits_momentum_x);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.momentum.y", OuterMPGDBarrelHits_momentum_y, &b_OuterMPGDBarrelHits_momentum_y);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.momentum.z", OuterMPGDBarrelHits_momentum_z, &b_OuterMPGDBarrelHits_momentum_z);
   fChain->SetBranchAddress("_OuterMPGDBarrelHits_particle", &_OuterMPGDBarrelHits_particle_, &b__OuterMPGDBarrelHits_particle_);
   fChain->SetBranchAddress("_OuterMPGDBarrelHits_particle.index", _OuterMPGDBarrelHits_particle_index, &b__OuterMPGDBarrelHits_particle_index);
   fChain->SetBranchAddress("_OuterMPGDBarrelHits_particle.collectionID", _OuterMPGDBarrelHits_particle_collectionID, &b__OuterMPGDBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("PFRICHHits", &PFRICHHits_, &b_PFRICHHits_);
   fChain->SetBranchAddress("PFRICHHits.cellID", &PFRICHHits_cellID, &b_PFRICHHits_cellID);
   fChain->SetBranchAddress("PFRICHHits.eDep", &PFRICHHits_eDep, &b_PFRICHHits_eDep);
   fChain->SetBranchAddress("PFRICHHits.time", &PFRICHHits_time, &b_PFRICHHits_time);
   fChain->SetBranchAddress("PFRICHHits.pathLength", &PFRICHHits_pathLength, &b_PFRICHHits_pathLength);
   fChain->SetBranchAddress("PFRICHHits.quality", &PFRICHHits_quality, &b_PFRICHHits_quality);
   fChain->SetBranchAddress("PFRICHHits.position.x", &PFRICHHits_position_x, &b_PFRICHHits_position_x);
   fChain->SetBranchAddress("PFRICHHits.position.y", &PFRICHHits_position_y, &b_PFRICHHits_position_y);
   fChain->SetBranchAddress("PFRICHHits.position.z", &PFRICHHits_position_z, &b_PFRICHHits_position_z);
   fChain->SetBranchAddress("PFRICHHits.momentum.x", &PFRICHHits_momentum_x, &b_PFRICHHits_momentum_x);
   fChain->SetBranchAddress("PFRICHHits.momentum.y", &PFRICHHits_momentum_y, &b_PFRICHHits_momentum_y);
   fChain->SetBranchAddress("PFRICHHits.momentum.z", &PFRICHHits_momentum_z, &b_PFRICHHits_momentum_z);
   fChain->SetBranchAddress("_PFRICHHits_particle", &_PFRICHHits_particle_, &b__PFRICHHits_particle_);
   fChain->SetBranchAddress("_PFRICHHits_particle.index", &_PFRICHHits_particle_index, &b__PFRICHHits_particle_index);
   fChain->SetBranchAddress("_PFRICHHits_particle.collectionID", &_PFRICHHits_particle_collectionID, &b__PFRICHHits_particle_collectionID);
   fChain->SetBranchAddress("SiBarrelHits", &SiBarrelHits_, &b_SiBarrelHits_);
   fChain->SetBranchAddress("SiBarrelHits.cellID", SiBarrelHits_cellID, &b_SiBarrelHits_cellID);
   fChain->SetBranchAddress("SiBarrelHits.eDep", SiBarrelHits_eDep, &b_SiBarrelHits_eDep);
   fChain->SetBranchAddress("SiBarrelHits.time", SiBarrelHits_time, &b_SiBarrelHits_time);
   fChain->SetBranchAddress("SiBarrelHits.pathLength", SiBarrelHits_pathLength, &b_SiBarrelHits_pathLength);
   fChain->SetBranchAddress("SiBarrelHits.quality", SiBarrelHits_quality, &b_SiBarrelHits_quality);
   fChain->SetBranchAddress("SiBarrelHits.position.x", SiBarrelHits_position_x, &b_SiBarrelHits_position_x);
   fChain->SetBranchAddress("SiBarrelHits.position.y", SiBarrelHits_position_y, &b_SiBarrelHits_position_y);
   fChain->SetBranchAddress("SiBarrelHits.position.z", SiBarrelHits_position_z, &b_SiBarrelHits_position_z);
   fChain->SetBranchAddress("SiBarrelHits.momentum.x", SiBarrelHits_momentum_x, &b_SiBarrelHits_momentum_x);
   fChain->SetBranchAddress("SiBarrelHits.momentum.y", SiBarrelHits_momentum_y, &b_SiBarrelHits_momentum_y);
   fChain->SetBranchAddress("SiBarrelHits.momentum.z", SiBarrelHits_momentum_z, &b_SiBarrelHits_momentum_z);
   fChain->SetBranchAddress("_SiBarrelHits_particle", &_SiBarrelHits_particle_, &b__SiBarrelHits_particle_);
   fChain->SetBranchAddress("_SiBarrelHits_particle.index", _SiBarrelHits_particle_index, &b__SiBarrelHits_particle_index);
   fChain->SetBranchAddress("_SiBarrelHits_particle.collectionID", _SiBarrelHits_particle_collectionID, &b__SiBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("TaggerTrackerHits", &TaggerTrackerHits_, &b_TaggerTrackerHits_);
   fChain->SetBranchAddress("TaggerTrackerHits.cellID", &TaggerTrackerHits_cellID, &b_TaggerTrackerHits_cellID);
   fChain->SetBranchAddress("TaggerTrackerHits.eDep", &TaggerTrackerHits_eDep, &b_TaggerTrackerHits_eDep);
   fChain->SetBranchAddress("TaggerTrackerHits.time", &TaggerTrackerHits_time, &b_TaggerTrackerHits_time);
   fChain->SetBranchAddress("TaggerTrackerHits.pathLength", &TaggerTrackerHits_pathLength, &b_TaggerTrackerHits_pathLength);
   fChain->SetBranchAddress("TaggerTrackerHits.quality", &TaggerTrackerHits_quality, &b_TaggerTrackerHits_quality);
   fChain->SetBranchAddress("TaggerTrackerHits.position.x", &TaggerTrackerHits_position_x, &b_TaggerTrackerHits_position_x);
   fChain->SetBranchAddress("TaggerTrackerHits.position.y", &TaggerTrackerHits_position_y, &b_TaggerTrackerHits_position_y);
   fChain->SetBranchAddress("TaggerTrackerHits.position.z", &TaggerTrackerHits_position_z, &b_TaggerTrackerHits_position_z);
   fChain->SetBranchAddress("TaggerTrackerHits.momentum.x", &TaggerTrackerHits_momentum_x, &b_TaggerTrackerHits_momentum_x);
   fChain->SetBranchAddress("TaggerTrackerHits.momentum.y", &TaggerTrackerHits_momentum_y, &b_TaggerTrackerHits_momentum_y);
   fChain->SetBranchAddress("TaggerTrackerHits.momentum.z", &TaggerTrackerHits_momentum_z, &b_TaggerTrackerHits_momentum_z);
   fChain->SetBranchAddress("_TaggerTrackerHits_particle", &_TaggerTrackerHits_particle_, &b__TaggerTrackerHits_particle_);
   fChain->SetBranchAddress("_TaggerTrackerHits_particle.index", &_TaggerTrackerHits_particle_index, &b__TaggerTrackerHits_particle_index);
   fChain->SetBranchAddress("_TaggerTrackerHits_particle.collectionID", &_TaggerTrackerHits_particle_collectionID, &b__TaggerTrackerHits_particle_collectionID);
   fChain->SetBranchAddress("TOFBarrelHits", &TOFBarrelHits_, &b_TOFBarrelHits_);
   fChain->SetBranchAddress("TOFBarrelHits.cellID", TOFBarrelHits_cellID, &b_TOFBarrelHits_cellID);
   fChain->SetBranchAddress("TOFBarrelHits.eDep", TOFBarrelHits_eDep, &b_TOFBarrelHits_eDep);
   fChain->SetBranchAddress("TOFBarrelHits.time", TOFBarrelHits_time, &b_TOFBarrelHits_time);
   fChain->SetBranchAddress("TOFBarrelHits.pathLength", TOFBarrelHits_pathLength, &b_TOFBarrelHits_pathLength);
   fChain->SetBranchAddress("TOFBarrelHits.quality", TOFBarrelHits_quality, &b_TOFBarrelHits_quality);
   fChain->SetBranchAddress("TOFBarrelHits.position.x", TOFBarrelHits_position_x, &b_TOFBarrelHits_position_x);
   fChain->SetBranchAddress("TOFBarrelHits.position.y", TOFBarrelHits_position_y, &b_TOFBarrelHits_position_y);
   fChain->SetBranchAddress("TOFBarrelHits.position.z", TOFBarrelHits_position_z, &b_TOFBarrelHits_position_z);
   fChain->SetBranchAddress("TOFBarrelHits.momentum.x", TOFBarrelHits_momentum_x, &b_TOFBarrelHits_momentum_x);
   fChain->SetBranchAddress("TOFBarrelHits.momentum.y", TOFBarrelHits_momentum_y, &b_TOFBarrelHits_momentum_y);
   fChain->SetBranchAddress("TOFBarrelHits.momentum.z", TOFBarrelHits_momentum_z, &b_TOFBarrelHits_momentum_z);
   fChain->SetBranchAddress("_TOFBarrelHits_particle", &_TOFBarrelHits_particle_, &b__TOFBarrelHits_particle_);
   fChain->SetBranchAddress("_TOFBarrelHits_particle.index", _TOFBarrelHits_particle_index, &b__TOFBarrelHits_particle_index);
   fChain->SetBranchAddress("_TOFBarrelHits_particle.collectionID", _TOFBarrelHits_particle_collectionID, &b__TOFBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("TOFEndcapHits", &TOFEndcapHits_, &b_TOFEndcapHits_);
   fChain->SetBranchAddress("TOFEndcapHits.cellID", TOFEndcapHits_cellID, &b_TOFEndcapHits_cellID);
   fChain->SetBranchAddress("TOFEndcapHits.eDep", TOFEndcapHits_eDep, &b_TOFEndcapHits_eDep);
   fChain->SetBranchAddress("TOFEndcapHits.time", TOFEndcapHits_time, &b_TOFEndcapHits_time);
   fChain->SetBranchAddress("TOFEndcapHits.pathLength", TOFEndcapHits_pathLength, &b_TOFEndcapHits_pathLength);
   fChain->SetBranchAddress("TOFEndcapHits.quality", TOFEndcapHits_quality, &b_TOFEndcapHits_quality);
   fChain->SetBranchAddress("TOFEndcapHits.position.x", TOFEndcapHits_position_x, &b_TOFEndcapHits_position_x);
   fChain->SetBranchAddress("TOFEndcapHits.position.y", TOFEndcapHits_position_y, &b_TOFEndcapHits_position_y);
   fChain->SetBranchAddress("TOFEndcapHits.position.z", TOFEndcapHits_position_z, &b_TOFEndcapHits_position_z);
   fChain->SetBranchAddress("TOFEndcapHits.momentum.x", TOFEndcapHits_momentum_x, &b_TOFEndcapHits_momentum_x);
   fChain->SetBranchAddress("TOFEndcapHits.momentum.y", TOFEndcapHits_momentum_y, &b_TOFEndcapHits_momentum_y);
   fChain->SetBranchAddress("TOFEndcapHits.momentum.z", TOFEndcapHits_momentum_z, &b_TOFEndcapHits_momentum_z);
   fChain->SetBranchAddress("_TOFEndcapHits_particle", &_TOFEndcapHits_particle_, &b__TOFEndcapHits_particle_);
   fChain->SetBranchAddress("_TOFEndcapHits_particle.index", _TOFEndcapHits_particle_index, &b__TOFEndcapHits_particle_index);
   fChain->SetBranchAddress("_TOFEndcapHits_particle.collectionID", _TOFEndcapHits_particle_collectionID, &b__TOFEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("TrackerEndcapHits", &TrackerEndcapHits_, &b_TrackerEndcapHits_);
   fChain->SetBranchAddress("TrackerEndcapHits.cellID", TrackerEndcapHits_cellID, &b_TrackerEndcapHits_cellID);
   fChain->SetBranchAddress("TrackerEndcapHits.eDep", TrackerEndcapHits_eDep, &b_TrackerEndcapHits_eDep);
   fChain->SetBranchAddress("TrackerEndcapHits.time", TrackerEndcapHits_time, &b_TrackerEndcapHits_time);
   fChain->SetBranchAddress("TrackerEndcapHits.pathLength", TrackerEndcapHits_pathLength, &b_TrackerEndcapHits_pathLength);
   fChain->SetBranchAddress("TrackerEndcapHits.quality", TrackerEndcapHits_quality, &b_TrackerEndcapHits_quality);
   fChain->SetBranchAddress("TrackerEndcapHits.position.x", TrackerEndcapHits_position_x, &b_TrackerEndcapHits_position_x);
   fChain->SetBranchAddress("TrackerEndcapHits.position.y", TrackerEndcapHits_position_y, &b_TrackerEndcapHits_position_y);
   fChain->SetBranchAddress("TrackerEndcapHits.position.z", TrackerEndcapHits_position_z, &b_TrackerEndcapHits_position_z);
   fChain->SetBranchAddress("TrackerEndcapHits.momentum.x", TrackerEndcapHits_momentum_x, &b_TrackerEndcapHits_momentum_x);
   fChain->SetBranchAddress("TrackerEndcapHits.momentum.y", TrackerEndcapHits_momentum_y, &b_TrackerEndcapHits_momentum_y);
   fChain->SetBranchAddress("TrackerEndcapHits.momentum.z", TrackerEndcapHits_momentum_z, &b_TrackerEndcapHits_momentum_z);
   fChain->SetBranchAddress("_TrackerEndcapHits_particle", &_TrackerEndcapHits_particle_, &b__TrackerEndcapHits_particle_);
   fChain->SetBranchAddress("_TrackerEndcapHits_particle.index", _TrackerEndcapHits_particle_index, &b__TrackerEndcapHits_particle_index);
   fChain->SetBranchAddress("_TrackerEndcapHits_particle.collectionID", _TrackerEndcapHits_particle_collectionID, &b__TrackerEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("VertexBarrelHits", &VertexBarrelHits_, &b_VertexBarrelHits_);
   fChain->SetBranchAddress("VertexBarrelHits.cellID", VertexBarrelHits_cellID, &b_VertexBarrelHits_cellID);
   fChain->SetBranchAddress("VertexBarrelHits.eDep", VertexBarrelHits_eDep, &b_VertexBarrelHits_eDep);
   fChain->SetBranchAddress("VertexBarrelHits.time", VertexBarrelHits_time, &b_VertexBarrelHits_time);
   fChain->SetBranchAddress("VertexBarrelHits.pathLength", VertexBarrelHits_pathLength, &b_VertexBarrelHits_pathLength);
   fChain->SetBranchAddress("VertexBarrelHits.quality", VertexBarrelHits_quality, &b_VertexBarrelHits_quality);
   fChain->SetBranchAddress("VertexBarrelHits.position.x", VertexBarrelHits_position_x, &b_VertexBarrelHits_position_x);
   fChain->SetBranchAddress("VertexBarrelHits.position.y", VertexBarrelHits_position_y, &b_VertexBarrelHits_position_y);
   fChain->SetBranchAddress("VertexBarrelHits.position.z", VertexBarrelHits_position_z, &b_VertexBarrelHits_position_z);
   fChain->SetBranchAddress("VertexBarrelHits.momentum.x", VertexBarrelHits_momentum_x, &b_VertexBarrelHits_momentum_x);
   fChain->SetBranchAddress("VertexBarrelHits.momentum.y", VertexBarrelHits_momentum_y, &b_VertexBarrelHits_momentum_y);
   fChain->SetBranchAddress("VertexBarrelHits.momentum.z", VertexBarrelHits_momentum_z, &b_VertexBarrelHits_momentum_z);
   fChain->SetBranchAddress("_VertexBarrelHits_particle", &_VertexBarrelHits_particle_, &b__VertexBarrelHits_particle_);
   fChain->SetBranchAddress("_VertexBarrelHits_particle.index", _VertexBarrelHits_particle_index, &b__VertexBarrelHits_particle_index);
   fChain->SetBranchAddress("_VertexBarrelHits_particle.collectionID", _VertexBarrelHits_particle_collectionID, &b__VertexBarrelHits_particle_collectionID);


   fChain->SetBranchAddress("GPIntKeys", &GPIntKeys, &b_GPIntKeys);
   fChain->SetBranchAddress("GPIntValues", &GPIntValues, &b_GPIntValues);
   fChain->SetBranchAddress("GPFloatKeys", &GPFloatKeys, &b_GPFloatKeys);
   fChain->SetBranchAddress("GPFloatValues", &GPFloatValues, &b_GPFloatValues);
   fChain->SetBranchAddress("GPDoubleKeys", &GPDoubleKeys, &b_GPDoubleKeys);
   fChain->SetBranchAddress("GPDoubleValues", &GPDoubleValues, &b_GPDoubleValues);
   fChain->SetBranchAddress("GPStringKeys", &GPStringKeys, &b_GPStringKeys);
   fChain->SetBranchAddress("GPStringValues", &GPStringValues, &b_GPStringValues);
   Notify();
}

Bool_t   McPsCheck::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void McPsCheck::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t McPsCheck::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

// == e == MakeClass Default Functions == s ==


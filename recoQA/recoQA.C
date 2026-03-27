// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

// Based on Barak codes:
// 
// 

// #define recoQA_cxx
#include "recoQA.h"

#include <random>

#include <TLorentzVector.h>
#include <TVector3.h>

#include <TStyle.h>
#include <TCanvas.h>

recoQA::recoQA(TTree *tree, std::string iTempFileName,std::string oTempFileName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   iFileName = iTempFileName;
   oFileName = "/Users/tkumaoka/eic/outputFiles/timeSplit/eicreconOutputCheck/" + oTempFileName;

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

recoQA::~recoQA()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void recoQA::Loop()
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

   int pureTrkCount(0);
   int mixTrkCount(0);
   int totalAssocCount(0);


   bool bTargetEV = false;

   // 140
   m_vTargetEvents = {148};
   // 0, 1, 2, 5, 7, 8, 10
   // m_vTargetEvents = {23, 84, 89, 92, 102};
   // m_vTargetEvents = {106};
   

   Int_t numOfEventLoops = 5000;
   // Int_t numOfEventLoops = 5;
   // Int_t numOfEventLoops = nentries;
   if(bTargetEV) numOfEventLoops = m_vTargetEvents.size();

   // float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   // float m_timeslice_width = 20.0; // width of time split for a time frame [ns]   
   
   // for (Long64_t jentry=0; jentry<1000; jentry++) {
   for (Long64_t jentry = 0; jentry < numOfEventLoops; ++jentry) {
   // for (Long64_t jentry=0; jentry < nentries;++jentry) {
      Long64_t tempJEntry = jentry;
      if(bTargetEV) jentry =  m_vTargetEvents.at(jentry);
      m_pubEvNum = jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if(jentry%100 == 0)std::cout << " == event" << jentry << " =====" << std::endl;
      std::cout << " == event" << jentry << " =====" << std::endl;
      numOfEvents[17]++;
      
      if(EventHeader_TS_weight[0] > 1) continue; // time slice including physics
      // if(EventHeader_TS_weight[0] < 2) continue;


      TLorentzVector rec_vec;
      TVector3 track_vec;

      for(size_t iMCP = 0; iMCP < MCParticles_; iMCP++){
         Int_t mcPGenStatus = MCParticles_generatorStatus[iMCP];
         Float_t mcPCharge = MCParticles_charge[iMCP];

         //Require final-state, charged particle (no secondaries)
         if( mcPGenStatus==1 && fabs(mcPCharge) > 0.01 ){
            TLorentzVector momVecMC;
            TVector3 vtxMC;
            
            momVecMC.SetXYZM(MCParticles_momentum_x[iMCP],MCParticles_momentum_y[iMCP],MCParticles_momentum_z[iMCP],MCParticles_mass[iMCP]);
            vtxMC.SetXYZ(MCParticles_vertex_x[iMCP],MCParticles_vertex_y[iMCP],MCParticles_vertex_z[iMCP]);
            
            auto eta = momVecMC.Eta();
            auto pt = momVecMC.Pt();

            //Fill eta histograms
            // m_hPtDist_MC->Fill(eta);

            //Fill Pt histogram
            if( fabs(eta) < 3.5 ) m_hPtDist_MC->Fill(pt);		

            //For |eta| < 3.5, find if there is an associated reconstructed track with weight > 0.8
            
            //Real-seeded tracks
            for(int iassoc = 0; iassoc < ReconstructedChargedParticleAssociations_; iassoc++){
               std::cout << "pt = " << pt << std::endl;
               if(fabs(eta) < 3.5 && ReconstructedChargedParticleAssociations_simID[iassoc] == iMCP && ReconstructedChargedParticleAssociations_weight[iassoc]>0.8){
                  //For a given track,, only one MC Particle can have a weight > 0.8
                  //---
                  //It is possible that a given MC Particle is associated to multiple
                  //tracks with weight > 0.8, although this is unlikely due to shared hit
                  //cut in ambiguity solver
                  m_hPtDist_Reco->Fill(pt);
               }
            }


         }
      }



      //Loop over (real-seeded) hit-based associations
      for(int iAsso=0; iAsso < CentralCKFTrackAssociations_; iAsso++){

         auto assoWeight = CentralCKFTrackAssociations_weight[iAsso];
         m_hTrackPurity->Fill(assoWeight);

         //Count pure and mixed tracks (avoid double-counting of mixed tracks)
         if(assoWeight > 0.99) pureTrkCount++;
         else if(iAsso==0) mixTrkCount++;
         else if(iAsso>0 && _CentralCKFTrackAssociations_rec_index[iAsso] != _CentralCKFTrackAssociations_rec_index[iAsso-1]) mixTrkCount++;
 
         //Get the associated track and MC particle
         //N.B. We use the fact that (right now) the track collection index is the same as the track parameter collection index
         int iMCP = _CentralCKFTrackAssociations_sim_index[iAsso];
         int iTrk = _CentralCKFTrackAssociations_rec_index[iAsso];

         TLorentzVector momVecMC;
         TVector3 vtxMC;
         momVecMC.SetXYZM(MCParticles_momentum_x[iMCP],MCParticles_momentum_y[iMCP],MCParticles_momentum_z[iMCP],MCParticles_mass[iMCP]);
         
         auto momMC = momVecMC.P();
         auto momTrk = fabs(1./CentralCKFTrackParameters_qOverP[iTrk]);

         m_hPtCompMCVsReco->Fill(momMC, momTrk);
         // if( fabs(gen_vec.Eta()) < 3 ) h3b->Fill(gen_mom, trk_mom);
         
         m_hPtReso->Fill((momTrk - momMC) / momMC);
         
      }
      if(CentralCKFTrackAssociations_>0) totalAssocCount += CentralCKFTrackAssociations_;

      //Fill some track quality histograms
      for(size_t iTrk = 0; iTrk < CentralCKFTracks_; iTrk++){
         m_hTrackChi2->Fill(CentralCKFTracks_chi2[iTrk]/CentralCKFTracks_ndf[iTrk]);
      }
      for(size_t iVtr = 0; iVtr < CentralTrackVertices_; iVtr++){
         m_hVertexChi2->Fill(CentralTrackVertices_chi2[iVtr]/CentralTrackVertices_ndf[iVtr]);
         m_hVertexPosiZ->Fill(CentralTrackVertices_position_z[iVtr]);
      }

      // if(checkPhysCount > 1) m_vTargetEvents.push_back(m_pubEvNum);
      if(bTargetEV) jentry = tempJEntry;
   } // == end of loop over events

   m_hPtReso->Scale(1./(1.0*totalAssocCount));
   m_hTrackPurity->Scale(1./(1.0*totalAssocCount));

   m_hTrkEfficiency = (TH1D*) m_hPtDist_Reco->Clone("m_hTrkEfficiency");
   m_hTrkEfficiency->Divide(m_hPtDist_MC);

   float totalPurity = ((float) pureTrkCount) / ((float) (pureTrkCount + mixTrkCount));
   m_hTotalTrackPurity->Fill(totalPurity);

   WriteHists();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

   std::cout << "Number of noise events: " << numOfNoise << std::endl;

}




void recoQA::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");

   m_hTrackChi2 = new TH1D(
      "m_hTrackChi2",
      "m_hTrackChi2; #chi^{2}/ndf; count",
      50,0,50
   );

   m_hVertexChi2 = new TH1D(
      "m_hVertexChi2",
      "m_hVertexChi2; #chi^{2}/ndf; count",
      100,0,100
   );

   m_hVertexPosiZ = new TH1D(
      "m_hVertexPosiZ",
      "m_hVertexPosiZ; #chi^{2}/ndf; count",
      200,-100,100
   );

   m_hPtDist_MC = new TH1D(
      "m_hPtDist_MC",
      "MC charged particle pt distribution; #it{p}_{T} [GeV/c]; count",
      30,0,15
   );

   m_hPtDist_Reco = new TH1D(
      "m_hPtDist_Reco",
      "Reconstructed charged particle pt distribution; #it{p}_{T} [GeV/c]; count",
      30,0,15
   );


   m_hPtCompMCVsReco = new TH2D(
      "m_hPtCompMCVsReco",
      "m_hPtCompMCVsReco; Associated generated particle momentum [GeV/c]; Reconstructed track momentum [GeV/c]",
      100,0,50,100,0,50
   );

   m_hPtReso = new TH1D(
      "m_hPtReso",
      "m_hPtReso; #frac{#it{p}_{T, reco} - #it{p}_{T, MC}}{#it{p}_{T, MC}} ; count",
      100, -1, 1
   );

   m_hTrackPurity = new TH1D(
      "m_hTrackPurity",
      "Fraction of track measurements from a given MC Particle; purity; Number of Tracks",
      100,0,1.1
   );

   m_hTotalTrackPurity = new TH1D(
      "m_hTotalTrackPurity",
      "m_hTotalTrackPurity; Total Evetn Purity",
      1,0,1
   );


   m_hTrkEfficiency = new TH1D(
      "m_hTrkEfficiency",
      "Tracking Efficiency; #it{p}_{T} [GeV/c]; Efficiency",
      30,0,15
   );

}


void recoQA::WriteHists(){
   oFile->cd();

   m_hTrackChi2->Write();
   m_hVertexChi2->Write();
   m_hVertexPosiZ->Write();

   m_hPtDist_MC->Write();
   m_hPtDist_Reco->Write();

   m_hPtCompMCVsReco->Write();
   m_hPtReso->Write();

   m_hTrackPurity->Write();
   m_hTotalTrackPurity->Write();
   m_hTrkEfficiency->Write();

   oFile->Close();
}


// == s == MakeClass Default Functions == s ==
Int_t recoQA::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t recoQA::LoadTree(Long64_t entry)
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

void recoQA::Init(TTree *tree)
{
   _EventHeader_TS_weights = 0;

   _CentralCKFTrajectories_measurementChi2 = 0;
   _CentralCKFTrajectories_outlierChi2 = 0;
   _CentralCKFTrajectoriesUnfiltered_measurementChi2 = 0;
   _CentralCKFTrajectoriesUnfiltered_outlierChi2 = 0;
   _CentralCKFTruthSeededTrajectories_measurementChi2 = 0;
   _CentralCKFTruthSeededTrajectories_outlierChi2 = 0;
   _CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2 = 0;
   _CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2 = 0;
   _CentralTrackerMeasurements_weights = 0;
   

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

   fChain->SetBranchStatus("EventHeader_TS", 1);
   fChain->SetBranchStatus("EventHeader_TS.*", 1);

   fChain->SetBranchStatus("MCParticles", 1);
   fChain->SetBranchStatus("MCParticles.*", 1);
   fChain->SetBranchStatus("_MCParticles_parents", 1);
   fChain->SetBranchStatus("_MCParticles_parents.*", 1);
   fChain->SetBranchStatus("_MCParticles_daughters", 1);
   fChain->SetBranchStatus("_MCParticles_daughters.*", 1);


   fChain->SetBranchAddress("EventHeader_TS", &EventHeader_TS_, &b_EventHeader_TS_);
   fChain->SetBranchAddress("EventHeader_TS.eventNumber", EventHeader_TS_eventNumber, &b_EventHeader_TS_eventNumber);
   fChain->SetBranchAddress("EventHeader_TS.runNumber", EventHeader_TS_runNumber, &b_EventHeader_TS_runNumber);
   fChain->SetBranchAddress("EventHeader_TS.timeStamp", EventHeader_TS_timeStamp, &b_EventHeader_TS_timeStamp);
   fChain->SetBranchAddress("EventHeader_TS.weight", EventHeader_TS_weight, &b_EventHeader_TS_weight);
   fChain->SetBranchAddress("EventHeader_TS.weights_begin", EventHeader_TS_weights_begin, &b_EventHeader_TS_weights_begin);
   fChain->SetBranchAddress("EventHeader_TS.weights_end", EventHeader_TS_weights_end, &b_EventHeader_TS_weights_end);
   fChain->SetBranchAddress("_EventHeader_TS_weights", &_EventHeader_TS_weights, &b__EventHeader_TS_weights);

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
   fChain->SetBranchAddress("MCParticles.spin.x", MCParticles_spin_x, &b_MCParticles_spin_x);
   fChain->SetBranchAddress("MCParticles.spin.y", MCParticles_spin_y, &b_MCParticles_spin_y);
   fChain->SetBranchAddress("MCParticles.spin.z", MCParticles_spin_z, &b_MCParticles_spin_z);
   fChain->SetBranchAddress("MCParticles.colorFlow.a", MCParticles_colorFlow_a, &b_MCParticles_colorFlow_a);
   fChain->SetBranchAddress("MCParticles.colorFlow.b", MCParticles_colorFlow_b, &b_MCParticles_colorFlow_b);
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


   fChain->SetBranchAddress("CentralCKFTrackAssociations", &CentralCKFTrackAssociations_, &b_CentralCKFTrackAssociations_);
   fChain->SetBranchAddress("CentralCKFTrackAssociations.simID", CentralCKFTrackAssociations_simID, &b_CentralCKFTrackAssociations_simID);
   fChain->SetBranchAddress("CentralCKFTrackAssociations.recID", CentralCKFTrackAssociations_recID, &b_CentralCKFTrackAssociations_recID);
   fChain->SetBranchAddress("CentralCKFTrackAssociations.weight", CentralCKFTrackAssociations_weight, &b_CentralCKFTrackAssociations_weight);
   fChain->SetBranchAddress("_CentralCKFTrackAssociations_rec", &_CentralCKFTrackAssociations_rec_, &b__CentralCKFTrackAssociations_rec_);
   fChain->SetBranchAddress("_CentralCKFTrackAssociations_rec.index", _CentralCKFTrackAssociations_rec_index, &b__CentralCKFTrackAssociations_rec_index);
   fChain->SetBranchAddress("_CentralCKFTrackAssociations_rec.collectionID", _CentralCKFTrackAssociations_rec_collectionID, &b__CentralCKFTrackAssociations_rec_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrackAssociations_sim", &_CentralCKFTrackAssociations_sim_, &b__CentralCKFTrackAssociations_sim_);
   fChain->SetBranchAddress("_CentralCKFTrackAssociations_sim.index", _CentralCKFTrackAssociations_sim_index, &b__CentralCKFTrackAssociations_sim_index);
   fChain->SetBranchAddress("_CentralCKFTrackAssociations_sim.collectionID", _CentralCKFTrackAssociations_sim_collectionID, &b__CentralCKFTrackAssociations_sim_collectionID);
   fChain->SetBranchAddress("CentralCKFTrackParameters", &CentralCKFTrackParameters_, &b_CentralCKFTrackParameters_);
   fChain->SetBranchAddress("CentralCKFTrackParameters.type", CentralCKFTrackParameters_type, &b_CentralCKFTrackParameters_type);
   fChain->SetBranchAddress("CentralCKFTrackParameters.surface", CentralCKFTrackParameters_surface, &b_CentralCKFTrackParameters_surface);
   fChain->SetBranchAddress("CentralCKFTrackParameters.loc.a", CentralCKFTrackParameters_loc_a, &b_CentralCKFTrackParameters_loc_a);
   fChain->SetBranchAddress("CentralCKFTrackParameters.loc.b", CentralCKFTrackParameters_loc_b, &b_CentralCKFTrackParameters_loc_b);
   fChain->SetBranchAddress("CentralCKFTrackParameters.theta", CentralCKFTrackParameters_theta, &b_CentralCKFTrackParameters_theta);
   fChain->SetBranchAddress("CentralCKFTrackParameters.phi", CentralCKFTrackParameters_phi, &b_CentralCKFTrackParameters_phi);
   fChain->SetBranchAddress("CentralCKFTrackParameters.qOverP", CentralCKFTrackParameters_qOverP, &b_CentralCKFTrackParameters_qOverP);
   fChain->SetBranchAddress("CentralCKFTrackParameters.time", CentralCKFTrackParameters_time, &b_CentralCKFTrackParameters_time);
   fChain->SetBranchAddress("CentralCKFTrackParameters.pdg", CentralCKFTrackParameters_pdg, &b_CentralCKFTrackParameters_pdg);
   fChain->SetBranchAddress("CentralCKFTrackParameters.covariance.covariance[21]", CentralCKFTrackParameters_covariance_covariance, &b_CentralCKFTrackParameters_covariance_covariance);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered", &CentralCKFTrackParametersUnfiltered_, &b_CentralCKFTrackParametersUnfiltered_);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.type", CentralCKFTrackParametersUnfiltered_type, &b_CentralCKFTrackParametersUnfiltered_type);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.surface", CentralCKFTrackParametersUnfiltered_surface, &b_CentralCKFTrackParametersUnfiltered_surface);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.loc.a", CentralCKFTrackParametersUnfiltered_loc_a, &b_CentralCKFTrackParametersUnfiltered_loc_a);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.loc.b", CentralCKFTrackParametersUnfiltered_loc_b, &b_CentralCKFTrackParametersUnfiltered_loc_b);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.theta", CentralCKFTrackParametersUnfiltered_theta, &b_CentralCKFTrackParametersUnfiltered_theta);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.phi", CentralCKFTrackParametersUnfiltered_phi, &b_CentralCKFTrackParametersUnfiltered_phi);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.qOverP", CentralCKFTrackParametersUnfiltered_qOverP, &b_CentralCKFTrackParametersUnfiltered_qOverP);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.time", CentralCKFTrackParametersUnfiltered_time, &b_CentralCKFTrackParametersUnfiltered_time);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.pdg", CentralCKFTrackParametersUnfiltered_pdg, &b_CentralCKFTrackParametersUnfiltered_pdg);
   fChain->SetBranchAddress("CentralCKFTrackParametersUnfiltered.covariance.covariance[21]", CentralCKFTrackParametersUnfiltered_covariance_covariance, &b_CentralCKFTrackParametersUnfiltered_covariance_covariance);
   fChain->SetBranchAddress("CentralCKFTracks", &CentralCKFTracks_, &b_CentralCKFTracks_);
   fChain->SetBranchAddress("CentralCKFTracks.type", CentralCKFTracks_type, &b_CentralCKFTracks_type);
   fChain->SetBranchAddress("CentralCKFTracks.position.x", CentralCKFTracks_position_x, &b_CentralCKFTracks_position_x);
   fChain->SetBranchAddress("CentralCKFTracks.position.y", CentralCKFTracks_position_y, &b_CentralCKFTracks_position_y);
   fChain->SetBranchAddress("CentralCKFTracks.position.z", CentralCKFTracks_position_z, &b_CentralCKFTracks_position_z);
   fChain->SetBranchAddress("CentralCKFTracks.momentum.x", CentralCKFTracks_momentum_x, &b_CentralCKFTracks_momentum_x);
   fChain->SetBranchAddress("CentralCKFTracks.momentum.y", CentralCKFTracks_momentum_y, &b_CentralCKFTracks_momentum_y);
   fChain->SetBranchAddress("CentralCKFTracks.momentum.z", CentralCKFTracks_momentum_z, &b_CentralCKFTracks_momentum_z);
   fChain->SetBranchAddress("CentralCKFTracks.positionMomentumCovariance.covariance[21]", CentralCKFTracks_positionMomentumCovariance_covariance, &b_CentralCKFTracks_positionMomentumCovariance_covariance);
   fChain->SetBranchAddress("CentralCKFTracks.time", CentralCKFTracks_time, &b_CentralCKFTracks_time);
   fChain->SetBranchAddress("CentralCKFTracks.timeError", CentralCKFTracks_timeError, &b_CentralCKFTracks_timeError);
   fChain->SetBranchAddress("CentralCKFTracks.charge", CentralCKFTracks_charge, &b_CentralCKFTracks_charge);
   fChain->SetBranchAddress("CentralCKFTracks.chi2", CentralCKFTracks_chi2, &b_CentralCKFTracks_chi2);
   fChain->SetBranchAddress("CentralCKFTracks.ndf", CentralCKFTracks_ndf, &b_CentralCKFTracks_ndf);
   fChain->SetBranchAddress("CentralCKFTracks.pdg", CentralCKFTracks_pdg, &b_CentralCKFTracks_pdg);
   fChain->SetBranchAddress("CentralCKFTracks.measurements_begin", CentralCKFTracks_measurements_begin, &b_CentralCKFTracks_measurements_begin);
   fChain->SetBranchAddress("CentralCKFTracks.measurements_end", CentralCKFTracks_measurements_end, &b_CentralCKFTracks_measurements_end);
   fChain->SetBranchAddress("CentralCKFTracks.tracks_begin", CentralCKFTracks_tracks_begin, &b_CentralCKFTracks_tracks_begin);
   fChain->SetBranchAddress("CentralCKFTracks.tracks_end", CentralCKFTracks_tracks_end, &b_CentralCKFTracks_tracks_end);
   fChain->SetBranchAddress("_CentralCKFTracks_measurements", &_CentralCKFTracks_measurements_, &b__CentralCKFTracks_measurements_);
   fChain->SetBranchAddress("_CentralCKFTracks_measurements.index", _CentralCKFTracks_measurements_index, &b__CentralCKFTracks_measurements_index);
   fChain->SetBranchAddress("_CentralCKFTracks_measurements.collectionID", _CentralCKFTracks_measurements_collectionID, &b__CentralCKFTracks_measurements_collectionID);
   fChain->SetBranchAddress("_CentralCKFTracks_tracks", &_CentralCKFTracks_tracks_, &b__CentralCKFTracks_tracks_);
   fChain->SetBranchAddress("_CentralCKFTracks_tracks.index", &_CentralCKFTracks_tracks_index, &b__CentralCKFTracks_tracks_index);
   fChain->SetBranchAddress("_CentralCKFTracks_tracks.collectionID", &_CentralCKFTracks_tracks_collectionID, &b__CentralCKFTracks_tracks_collectionID);
   fChain->SetBranchAddress("_CentralCKFTracks_trajectory", &_CentralCKFTracks_trajectory_, &b__CentralCKFTracks_trajectory_);
   fChain->SetBranchAddress("_CentralCKFTracks_trajectory.index", _CentralCKFTracks_trajectory_index, &b__CentralCKFTracks_trajectory_index);
   fChain->SetBranchAddress("_CentralCKFTracks_trajectory.collectionID", _CentralCKFTracks_trajectory_collectionID, &b__CentralCKFTracks_trajectory_collectionID);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered", &CentralCKFTracksUnfiltered_, &b_CentralCKFTracksUnfiltered_);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.type", CentralCKFTracksUnfiltered_type, &b_CentralCKFTracksUnfiltered_type);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.position.x", CentralCKFTracksUnfiltered_position_x, &b_CentralCKFTracksUnfiltered_position_x);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.position.y", CentralCKFTracksUnfiltered_position_y, &b_CentralCKFTracksUnfiltered_position_y);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.position.z", CentralCKFTracksUnfiltered_position_z, &b_CentralCKFTracksUnfiltered_position_z);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.momentum.x", CentralCKFTracksUnfiltered_momentum_x, &b_CentralCKFTracksUnfiltered_momentum_x);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.momentum.y", CentralCKFTracksUnfiltered_momentum_y, &b_CentralCKFTracksUnfiltered_momentum_y);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.momentum.z", CentralCKFTracksUnfiltered_momentum_z, &b_CentralCKFTracksUnfiltered_momentum_z);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.positionMomentumCovariance.covariance[21]", CentralCKFTracksUnfiltered_positionMomentumCovariance_covariance, &b_CentralCKFTracksUnfiltered_positionMomentumCovariance_covariance);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.time", CentralCKFTracksUnfiltered_time, &b_CentralCKFTracksUnfiltered_time);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.timeError", CentralCKFTracksUnfiltered_timeError, &b_CentralCKFTracksUnfiltered_timeError);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.charge", CentralCKFTracksUnfiltered_charge, &b_CentralCKFTracksUnfiltered_charge);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.chi2", CentralCKFTracksUnfiltered_chi2, &b_CentralCKFTracksUnfiltered_chi2);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.ndf", CentralCKFTracksUnfiltered_ndf, &b_CentralCKFTracksUnfiltered_ndf);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.pdg", CentralCKFTracksUnfiltered_pdg, &b_CentralCKFTracksUnfiltered_pdg);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.measurements_begin", CentralCKFTracksUnfiltered_measurements_begin, &b_CentralCKFTracksUnfiltered_measurements_begin);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.measurements_end", CentralCKFTracksUnfiltered_measurements_end, &b_CentralCKFTracksUnfiltered_measurements_end);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.tracks_begin", CentralCKFTracksUnfiltered_tracks_begin, &b_CentralCKFTracksUnfiltered_tracks_begin);
   fChain->SetBranchAddress("CentralCKFTracksUnfiltered.tracks_end", CentralCKFTracksUnfiltered_tracks_end, &b_CentralCKFTracksUnfiltered_tracks_end);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_measurements", &_CentralCKFTracksUnfiltered_measurements_, &b__CentralCKFTracksUnfiltered_measurements_);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_measurements.index", _CentralCKFTracksUnfiltered_measurements_index, &b__CentralCKFTracksUnfiltered_measurements_index);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_measurements.collectionID", _CentralCKFTracksUnfiltered_measurements_collectionID, &b__CentralCKFTracksUnfiltered_measurements_collectionID);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_tracks", &_CentralCKFTracksUnfiltered_tracks_, &b__CentralCKFTracksUnfiltered_tracks_);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_tracks.index", &_CentralCKFTracksUnfiltered_tracks_index, &b__CentralCKFTracksUnfiltered_tracks_index);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_tracks.collectionID", &_CentralCKFTracksUnfiltered_tracks_collectionID, &b__CentralCKFTracksUnfiltered_tracks_collectionID);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_trajectory", &_CentralCKFTracksUnfiltered_trajectory_, &b__CentralCKFTracksUnfiltered_trajectory_);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_trajectory.index", _CentralCKFTracksUnfiltered_trajectory_index, &b__CentralCKFTracksUnfiltered_trajectory_index);
   fChain->SetBranchAddress("_CentralCKFTracksUnfiltered_trajectory.collectionID", _CentralCKFTracksUnfiltered_trajectory_collectionID, &b__CentralCKFTracksUnfiltered_trajectory_collectionID);
   fChain->SetBranchAddress("CentralCKFTrackUnfilteredAssociations", &CentralCKFTrackUnfilteredAssociations_, &b_CentralCKFTrackUnfilteredAssociations_);
   fChain->SetBranchAddress("CentralCKFTrackUnfilteredAssociations.simID", CentralCKFTrackUnfilteredAssociations_simID, &b_CentralCKFTrackUnfilteredAssociations_simID);
   fChain->SetBranchAddress("CentralCKFTrackUnfilteredAssociations.recID", CentralCKFTrackUnfilteredAssociations_recID, &b_CentralCKFTrackUnfilteredAssociations_recID);
   fChain->SetBranchAddress("CentralCKFTrackUnfilteredAssociations.weight", CentralCKFTrackUnfilteredAssociations_weight, &b_CentralCKFTrackUnfilteredAssociations_weight);
   fChain->SetBranchAddress("_CentralCKFTrackUnfilteredAssociations_rec", &_CentralCKFTrackUnfilteredAssociations_rec_, &b__CentralCKFTrackUnfilteredAssociations_rec_);
   fChain->SetBranchAddress("_CentralCKFTrackUnfilteredAssociations_rec.index", _CentralCKFTrackUnfilteredAssociations_rec_index, &b__CentralCKFTrackUnfilteredAssociations_rec_index);
   fChain->SetBranchAddress("_CentralCKFTrackUnfilteredAssociations_rec.collectionID", _CentralCKFTrackUnfilteredAssociations_rec_collectionID, &b__CentralCKFTrackUnfilteredAssociations_rec_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrackUnfilteredAssociations_sim", &_CentralCKFTrackUnfilteredAssociations_sim_, &b__CentralCKFTrackUnfilteredAssociations_sim_);
   fChain->SetBranchAddress("_CentralCKFTrackUnfilteredAssociations_sim.index", _CentralCKFTrackUnfilteredAssociations_sim_index, &b__CentralCKFTrackUnfilteredAssociations_sim_index);
   fChain->SetBranchAddress("_CentralCKFTrackUnfilteredAssociations_sim.collectionID", _CentralCKFTrackUnfilteredAssociations_sim_collectionID, &b__CentralCKFTrackUnfilteredAssociations_sim_collectionID);
   fChain->SetBranchAddress("CentralCKFTrajectories", &CentralCKFTrajectories_, &b_CentralCKFTrajectories_);
   fChain->SetBranchAddress("CentralCKFTrajectories.type", CentralCKFTrajectories_type, &b_CentralCKFTrajectories_type);
   fChain->SetBranchAddress("CentralCKFTrajectories.nStates", CentralCKFTrajectories_nStates, &b_CentralCKFTrajectories_nStates);
   fChain->SetBranchAddress("CentralCKFTrajectories.nMeasurements", CentralCKFTrajectories_nMeasurements, &b_CentralCKFTrajectories_nMeasurements);
   fChain->SetBranchAddress("CentralCKFTrajectories.nOutliers", CentralCKFTrajectories_nOutliers, &b_CentralCKFTrajectories_nOutliers);
   fChain->SetBranchAddress("CentralCKFTrajectories.nHoles", CentralCKFTrajectories_nHoles, &b_CentralCKFTrajectories_nHoles);
   fChain->SetBranchAddress("CentralCKFTrajectories.nSharedHits", CentralCKFTrajectories_nSharedHits, &b_CentralCKFTrajectories_nSharedHits);
   fChain->SetBranchAddress("CentralCKFTrajectories.measurementChi2_begin", CentralCKFTrajectories_measurementChi2_begin, &b_CentralCKFTrajectories_measurementChi2_begin);
   fChain->SetBranchAddress("CentralCKFTrajectories.measurementChi2_end", CentralCKFTrajectories_measurementChi2_end, &b_CentralCKFTrajectories_measurementChi2_end);
   fChain->SetBranchAddress("CentralCKFTrajectories.outlierChi2_begin", CentralCKFTrajectories_outlierChi2_begin, &b_CentralCKFTrajectories_outlierChi2_begin);
   fChain->SetBranchAddress("CentralCKFTrajectories.outlierChi2_end", CentralCKFTrajectories_outlierChi2_end, &b_CentralCKFTrajectories_outlierChi2_end);
   fChain->SetBranchAddress("CentralCKFTrajectories.trackParameters_begin", CentralCKFTrajectories_trackParameters_begin, &b_CentralCKFTrajectories_trackParameters_begin);
   fChain->SetBranchAddress("CentralCKFTrajectories.trackParameters_end", CentralCKFTrajectories_trackParameters_end, &b_CentralCKFTrajectories_trackParameters_end);
   fChain->SetBranchAddress("CentralCKFTrajectories.measurements_deprecated_begin", CentralCKFTrajectories_measurements_deprecated_begin, &b_CentralCKFTrajectories_measurements_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTrajectories.measurements_deprecated_end", CentralCKFTrajectories_measurements_deprecated_end, &b_CentralCKFTrajectories_measurements_deprecated_end);
   fChain->SetBranchAddress("CentralCKFTrajectories.outliers_deprecated_begin", CentralCKFTrajectories_outliers_deprecated_begin, &b_CentralCKFTrajectories_outliers_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTrajectories.outliers_deprecated_end", CentralCKFTrajectories_outliers_deprecated_end, &b_CentralCKFTrajectories_outliers_deprecated_end);
   fChain->SetBranchAddress("_CentralCKFTrajectories_trackParameters", &_CentralCKFTrajectories_trackParameters_, &b__CentralCKFTrajectories_trackParameters_);
   fChain->SetBranchAddress("_CentralCKFTrajectories_trackParameters.index", _CentralCKFTrajectories_trackParameters_index, &b__CentralCKFTrajectories_trackParameters_index);
   fChain->SetBranchAddress("_CentralCKFTrajectories_trackParameters.collectionID", _CentralCKFTrajectories_trackParameters_collectionID, &b__CentralCKFTrajectories_trackParameters_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectories_measurements_deprecated", &_CentralCKFTrajectories_measurements_deprecated_, &b__CentralCKFTrajectories_measurements_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTrajectories_measurements_deprecated.index", _CentralCKFTrajectories_measurements_deprecated_index, &b__CentralCKFTrajectories_measurements_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTrajectories_measurements_deprecated.collectionID", _CentralCKFTrajectories_measurements_deprecated_collectionID, &b__CentralCKFTrajectories_measurements_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectories_outliers_deprecated", &_CentralCKFTrajectories_outliers_deprecated_, &b__CentralCKFTrajectories_outliers_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTrajectories_outliers_deprecated.index", _CentralCKFTrajectories_outliers_deprecated_index, &b__CentralCKFTrajectories_outliers_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTrajectories_outliers_deprecated.collectionID", _CentralCKFTrajectories_outliers_deprecated_collectionID, &b__CentralCKFTrajectories_outliers_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectories_seed", &_CentralCKFTrajectories_seed_, &b__CentralCKFTrajectories_seed_);
   fChain->SetBranchAddress("_CentralCKFTrajectories_seed.index", _CentralCKFTrajectories_seed_index, &b__CentralCKFTrajectories_seed_index);
   fChain->SetBranchAddress("_CentralCKFTrajectories_seed.collectionID", _CentralCKFTrajectories_seed_collectionID, &b__CentralCKFTrajectories_seed_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectories_measurementChi2", &_CentralCKFTrajectories_measurementChi2, &b__CentralCKFTrajectories_measurementChi2);
   fChain->SetBranchAddress("_CentralCKFTrajectories_outlierChi2", &_CentralCKFTrajectories_outlierChi2, &b__CentralCKFTrajectories_outlierChi2);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered", &CentralCKFTrajectoriesUnfiltered_, &b_CentralCKFTrajectoriesUnfiltered_);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.type", CentralCKFTrajectoriesUnfiltered_type, &b_CentralCKFTrajectoriesUnfiltered_type);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.nStates", CentralCKFTrajectoriesUnfiltered_nStates, &b_CentralCKFTrajectoriesUnfiltered_nStates);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.nMeasurements", CentralCKFTrajectoriesUnfiltered_nMeasurements, &b_CentralCKFTrajectoriesUnfiltered_nMeasurements);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.nOutliers", CentralCKFTrajectoriesUnfiltered_nOutliers, &b_CentralCKFTrajectoriesUnfiltered_nOutliers);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.nHoles", CentralCKFTrajectoriesUnfiltered_nHoles, &b_CentralCKFTrajectoriesUnfiltered_nHoles);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.nSharedHits", CentralCKFTrajectoriesUnfiltered_nSharedHits, &b_CentralCKFTrajectoriesUnfiltered_nSharedHits);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.measurementChi2_begin", CentralCKFTrajectoriesUnfiltered_measurementChi2_begin, &b_CentralCKFTrajectoriesUnfiltered_measurementChi2_begin);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.measurementChi2_end", CentralCKFTrajectoriesUnfiltered_measurementChi2_end, &b_CentralCKFTrajectoriesUnfiltered_measurementChi2_end);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.outlierChi2_begin", CentralCKFTrajectoriesUnfiltered_outlierChi2_begin, &b_CentralCKFTrajectoriesUnfiltered_outlierChi2_begin);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.outlierChi2_end", CentralCKFTrajectoriesUnfiltered_outlierChi2_end, &b_CentralCKFTrajectoriesUnfiltered_outlierChi2_end);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.trackParameters_begin", CentralCKFTrajectoriesUnfiltered_trackParameters_begin, &b_CentralCKFTrajectoriesUnfiltered_trackParameters_begin);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.trackParameters_end", CentralCKFTrajectoriesUnfiltered_trackParameters_end, &b_CentralCKFTrajectoriesUnfiltered_trackParameters_end);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.measurements_deprecated_begin", CentralCKFTrajectoriesUnfiltered_measurements_deprecated_begin, &b_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.measurements_deprecated_end", CentralCKFTrajectoriesUnfiltered_measurements_deprecated_end, &b_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_end);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.outliers_deprecated_begin", CentralCKFTrajectoriesUnfiltered_outliers_deprecated_begin, &b_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTrajectoriesUnfiltered.outliers_deprecated_end", CentralCKFTrajectoriesUnfiltered_outliers_deprecated_end, &b_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_end);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_trackParameters", &_CentralCKFTrajectoriesUnfiltered_trackParameters_, &b__CentralCKFTrajectoriesUnfiltered_trackParameters_);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_trackParameters.index", _CentralCKFTrajectoriesUnfiltered_trackParameters_index, &b__CentralCKFTrajectoriesUnfiltered_trackParameters_index);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_trackParameters.collectionID", _CentralCKFTrajectoriesUnfiltered_trackParameters_collectionID, &b__CentralCKFTrajectoriesUnfiltered_trackParameters_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_measurements_deprecated", &_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_, &b__CentralCKFTrajectoriesUnfiltered_measurements_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_measurements_deprecated.index", _CentralCKFTrajectoriesUnfiltered_measurements_deprecated_index, &b__CentralCKFTrajectoriesUnfiltered_measurements_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_measurements_deprecated.collectionID", _CentralCKFTrajectoriesUnfiltered_measurements_deprecated_collectionID, &b__CentralCKFTrajectoriesUnfiltered_measurements_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_outliers_deprecated", &_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_, &b__CentralCKFTrajectoriesUnfiltered_outliers_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_outliers_deprecated.index", _CentralCKFTrajectoriesUnfiltered_outliers_deprecated_index, &b__CentralCKFTrajectoriesUnfiltered_outliers_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_outliers_deprecated.collectionID", _CentralCKFTrajectoriesUnfiltered_outliers_deprecated_collectionID, &b__CentralCKFTrajectoriesUnfiltered_outliers_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_seed", &_CentralCKFTrajectoriesUnfiltered_seed_, &b__CentralCKFTrajectoriesUnfiltered_seed_);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_seed.index", _CentralCKFTrajectoriesUnfiltered_seed_index, &b__CentralCKFTrajectoriesUnfiltered_seed_index);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_seed.collectionID", _CentralCKFTrajectoriesUnfiltered_seed_collectionID, &b__CentralCKFTrajectoriesUnfiltered_seed_collectionID);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_measurementChi2", &_CentralCKFTrajectoriesUnfiltered_measurementChi2, &b__CentralCKFTrajectoriesUnfiltered_measurementChi2);
   fChain->SetBranchAddress("_CentralCKFTrajectoriesUnfiltered_outlierChi2", &_CentralCKFTrajectoriesUnfiltered_outlierChi2, &b__CentralCKFTrajectoriesUnfiltered_outlierChi2);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackAssociations", &CentralCKFTruthSeededTrackAssociations_, &b_CentralCKFTruthSeededTrackAssociations_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackAssociations.simID", CentralCKFTruthSeededTrackAssociations_simID, &b_CentralCKFTruthSeededTrackAssociations_simID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackAssociations.recID", CentralCKFTruthSeededTrackAssociations_recID, &b_CentralCKFTruthSeededTrackAssociations_recID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackAssociations.weight", CentralCKFTruthSeededTrackAssociations_weight, &b_CentralCKFTruthSeededTrackAssociations_weight);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackAssociations_rec", &_CentralCKFTruthSeededTrackAssociations_rec_, &b__CentralCKFTruthSeededTrackAssociations_rec_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackAssociations_rec.index", _CentralCKFTruthSeededTrackAssociations_rec_index, &b__CentralCKFTruthSeededTrackAssociations_rec_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackAssociations_rec.collectionID", _CentralCKFTruthSeededTrackAssociations_rec_collectionID, &b__CentralCKFTruthSeededTrackAssociations_rec_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackAssociations_sim", &_CentralCKFTruthSeededTrackAssociations_sim_, &b__CentralCKFTruthSeededTrackAssociations_sim_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackAssociations_sim.index", _CentralCKFTruthSeededTrackAssociations_sim_index, &b__CentralCKFTruthSeededTrackAssociations_sim_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackAssociations_sim.collectionID", _CentralCKFTruthSeededTrackAssociations_sim_collectionID, &b__CentralCKFTruthSeededTrackAssociations_sim_collectionID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters", &CentralCKFTruthSeededTrackParameters_, &b_CentralCKFTruthSeededTrackParameters_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.type", CentralCKFTruthSeededTrackParameters_type, &b_CentralCKFTruthSeededTrackParameters_type);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.surface", CentralCKFTruthSeededTrackParameters_surface, &b_CentralCKFTruthSeededTrackParameters_surface);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.loc.a", CentralCKFTruthSeededTrackParameters_loc_a, &b_CentralCKFTruthSeededTrackParameters_loc_a);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.loc.b", CentralCKFTruthSeededTrackParameters_loc_b, &b_CentralCKFTruthSeededTrackParameters_loc_b);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.theta", CentralCKFTruthSeededTrackParameters_theta, &b_CentralCKFTruthSeededTrackParameters_theta);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.phi", CentralCKFTruthSeededTrackParameters_phi, &b_CentralCKFTruthSeededTrackParameters_phi);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.qOverP", CentralCKFTruthSeededTrackParameters_qOverP, &b_CentralCKFTruthSeededTrackParameters_qOverP);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.time", CentralCKFTruthSeededTrackParameters_time, &b_CentralCKFTruthSeededTrackParameters_time);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.pdg", CentralCKFTruthSeededTrackParameters_pdg, &b_CentralCKFTruthSeededTrackParameters_pdg);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParameters.covariance.covariance[21]", CentralCKFTruthSeededTrackParameters_covariance_covariance, &b_CentralCKFTruthSeededTrackParameters_covariance_covariance);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered", &CentralCKFTruthSeededTrackParametersUnfiltered_, &b_CentralCKFTruthSeededTrackParametersUnfiltered_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.type", CentralCKFTruthSeededTrackParametersUnfiltered_type, &b_CentralCKFTruthSeededTrackParametersUnfiltered_type);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.surface", CentralCKFTruthSeededTrackParametersUnfiltered_surface, &b_CentralCKFTruthSeededTrackParametersUnfiltered_surface);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.loc.a", CentralCKFTruthSeededTrackParametersUnfiltered_loc_a, &b_CentralCKFTruthSeededTrackParametersUnfiltered_loc_a);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.loc.b", CentralCKFTruthSeededTrackParametersUnfiltered_loc_b, &b_CentralCKFTruthSeededTrackParametersUnfiltered_loc_b);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.theta", CentralCKFTruthSeededTrackParametersUnfiltered_theta, &b_CentralCKFTruthSeededTrackParametersUnfiltered_theta);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.phi", CentralCKFTruthSeededTrackParametersUnfiltered_phi, &b_CentralCKFTruthSeededTrackParametersUnfiltered_phi);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.qOverP", CentralCKFTruthSeededTrackParametersUnfiltered_qOverP, &b_CentralCKFTruthSeededTrackParametersUnfiltered_qOverP);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.time", CentralCKFTruthSeededTrackParametersUnfiltered_time, &b_CentralCKFTruthSeededTrackParametersUnfiltered_time);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.pdg", CentralCKFTruthSeededTrackParametersUnfiltered_pdg, &b_CentralCKFTruthSeededTrackParametersUnfiltered_pdg);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackParametersUnfiltered.covariance.covariance[21]", CentralCKFTruthSeededTrackParametersUnfiltered_covariance_covariance, &b_CentralCKFTruthSeededTrackParametersUnfiltered_covariance_covariance);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks", &CentralCKFTruthSeededTracks_, &b_CentralCKFTruthSeededTracks_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.type", CentralCKFTruthSeededTracks_type, &b_CentralCKFTruthSeededTracks_type);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.position.x", CentralCKFTruthSeededTracks_position_x, &b_CentralCKFTruthSeededTracks_position_x);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.position.y", CentralCKFTruthSeededTracks_position_y, &b_CentralCKFTruthSeededTracks_position_y);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.position.z", CentralCKFTruthSeededTracks_position_z, &b_CentralCKFTruthSeededTracks_position_z);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.momentum.x", CentralCKFTruthSeededTracks_momentum_x, &b_CentralCKFTruthSeededTracks_momentum_x);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.momentum.y", CentralCKFTruthSeededTracks_momentum_y, &b_CentralCKFTruthSeededTracks_momentum_y);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.momentum.z", CentralCKFTruthSeededTracks_momentum_z, &b_CentralCKFTruthSeededTracks_momentum_z);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.positionMomentumCovariance.covariance[21]", CentralCKFTruthSeededTracks_positionMomentumCovariance_covariance, &b_CentralCKFTruthSeededTracks_positionMomentumCovariance_covariance);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.time", CentralCKFTruthSeededTracks_time, &b_CentralCKFTruthSeededTracks_time);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.timeError", CentralCKFTruthSeededTracks_timeError, &b_CentralCKFTruthSeededTracks_timeError);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.charge", CentralCKFTruthSeededTracks_charge, &b_CentralCKFTruthSeededTracks_charge);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.chi2", CentralCKFTruthSeededTracks_chi2, &b_CentralCKFTruthSeededTracks_chi2);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.ndf", CentralCKFTruthSeededTracks_ndf, &b_CentralCKFTruthSeededTracks_ndf);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.pdg", CentralCKFTruthSeededTracks_pdg, &b_CentralCKFTruthSeededTracks_pdg);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.measurements_begin", CentralCKFTruthSeededTracks_measurements_begin, &b_CentralCKFTruthSeededTracks_measurements_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.measurements_end", CentralCKFTruthSeededTracks_measurements_end, &b_CentralCKFTruthSeededTracks_measurements_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.tracks_begin", CentralCKFTruthSeededTracks_tracks_begin, &b_CentralCKFTruthSeededTracks_tracks_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracks.tracks_end", CentralCKFTruthSeededTracks_tracks_end, &b_CentralCKFTruthSeededTracks_tracks_end);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_measurements", &_CentralCKFTruthSeededTracks_measurements_, &b__CentralCKFTruthSeededTracks_measurements_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_measurements.index", _CentralCKFTruthSeededTracks_measurements_index, &b__CentralCKFTruthSeededTracks_measurements_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_measurements.collectionID", _CentralCKFTruthSeededTracks_measurements_collectionID, &b__CentralCKFTruthSeededTracks_measurements_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_tracks", &_CentralCKFTruthSeededTracks_tracks_, &b__CentralCKFTruthSeededTracks_tracks_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_tracks.index", &_CentralCKFTruthSeededTracks_tracks_index, &b__CentralCKFTruthSeededTracks_tracks_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_tracks.collectionID", &_CentralCKFTruthSeededTracks_tracks_collectionID, &b__CentralCKFTruthSeededTracks_tracks_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_trajectory", &_CentralCKFTruthSeededTracks_trajectory_, &b__CentralCKFTruthSeededTracks_trajectory_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_trajectory.index", _CentralCKFTruthSeededTracks_trajectory_index, &b__CentralCKFTruthSeededTracks_trajectory_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracks_trajectory.collectionID", _CentralCKFTruthSeededTracks_trajectory_collectionID, &b__CentralCKFTruthSeededTracks_trajectory_collectionID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered", &CentralCKFTruthSeededTracksUnfiltered_, &b_CentralCKFTruthSeededTracksUnfiltered_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.type", CentralCKFTruthSeededTracksUnfiltered_type, &b_CentralCKFTruthSeededTracksUnfiltered_type);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.position.x", CentralCKFTruthSeededTracksUnfiltered_position_x, &b_CentralCKFTruthSeededTracksUnfiltered_position_x);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.position.y", CentralCKFTruthSeededTracksUnfiltered_position_y, &b_CentralCKFTruthSeededTracksUnfiltered_position_y);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.position.z", CentralCKFTruthSeededTracksUnfiltered_position_z, &b_CentralCKFTruthSeededTracksUnfiltered_position_z);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.momentum.x", CentralCKFTruthSeededTracksUnfiltered_momentum_x, &b_CentralCKFTruthSeededTracksUnfiltered_momentum_x);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.momentum.y", CentralCKFTruthSeededTracksUnfiltered_momentum_y, &b_CentralCKFTruthSeededTracksUnfiltered_momentum_y);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.momentum.z", CentralCKFTruthSeededTracksUnfiltered_momentum_z, &b_CentralCKFTruthSeededTracksUnfiltered_momentum_z);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.positionMomentumCovariance.covariance[21]", CentralCKFTruthSeededTracksUnfiltered_positionMomentumCovariance_covariance, &b_CentralCKFTruthSeededTracksUnfiltered_positionMomentumCovariance_covariance);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.time", CentralCKFTruthSeededTracksUnfiltered_time, &b_CentralCKFTruthSeededTracksUnfiltered_time);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.timeError", CentralCKFTruthSeededTracksUnfiltered_timeError, &b_CentralCKFTruthSeededTracksUnfiltered_timeError);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.charge", CentralCKFTruthSeededTracksUnfiltered_charge, &b_CentralCKFTruthSeededTracksUnfiltered_charge);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.chi2", CentralCKFTruthSeededTracksUnfiltered_chi2, &b_CentralCKFTruthSeededTracksUnfiltered_chi2);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.ndf", CentralCKFTruthSeededTracksUnfiltered_ndf, &b_CentralCKFTruthSeededTracksUnfiltered_ndf);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.pdg", CentralCKFTruthSeededTracksUnfiltered_pdg, &b_CentralCKFTruthSeededTracksUnfiltered_pdg);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.measurements_begin", CentralCKFTruthSeededTracksUnfiltered_measurements_begin, &b_CentralCKFTruthSeededTracksUnfiltered_measurements_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.measurements_end", CentralCKFTruthSeededTracksUnfiltered_measurements_end, &b_CentralCKFTruthSeededTracksUnfiltered_measurements_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.tracks_begin", CentralCKFTruthSeededTracksUnfiltered_tracks_begin, &b_CentralCKFTruthSeededTracksUnfiltered_tracks_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTracksUnfiltered.tracks_end", CentralCKFTruthSeededTracksUnfiltered_tracks_end, &b_CentralCKFTruthSeededTracksUnfiltered_tracks_end);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_measurements", &_CentralCKFTruthSeededTracksUnfiltered_measurements_, &b__CentralCKFTruthSeededTracksUnfiltered_measurements_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_measurements.index", _CentralCKFTruthSeededTracksUnfiltered_measurements_index, &b__CentralCKFTruthSeededTracksUnfiltered_measurements_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_measurements.collectionID", _CentralCKFTruthSeededTracksUnfiltered_measurements_collectionID, &b__CentralCKFTruthSeededTracksUnfiltered_measurements_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_tracks", &_CentralCKFTruthSeededTracksUnfiltered_tracks_, &b__CentralCKFTruthSeededTracksUnfiltered_tracks_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_tracks.index", &_CentralCKFTruthSeededTracksUnfiltered_tracks_index, &b__CentralCKFTruthSeededTracksUnfiltered_tracks_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_tracks.collectionID", &_CentralCKFTruthSeededTracksUnfiltered_tracks_collectionID, &b__CentralCKFTruthSeededTracksUnfiltered_tracks_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_trajectory", &_CentralCKFTruthSeededTracksUnfiltered_trajectory_, &b__CentralCKFTruthSeededTracksUnfiltered_trajectory_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_trajectory.index", _CentralCKFTruthSeededTracksUnfiltered_trajectory_index, &b__CentralCKFTruthSeededTracksUnfiltered_trajectory_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTracksUnfiltered_trajectory.collectionID", _CentralCKFTruthSeededTracksUnfiltered_trajectory_collectionID, &b__CentralCKFTruthSeededTracksUnfiltered_trajectory_collectionID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackUnfilteredAssociations", &CentralCKFTruthSeededTrackUnfilteredAssociations_, &b_CentralCKFTruthSeededTrackUnfilteredAssociations_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackUnfilteredAssociations.simID", CentralCKFTruthSeededTrackUnfilteredAssociations_simID, &b_CentralCKFTruthSeededTrackUnfilteredAssociations_simID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackUnfilteredAssociations.recID", CentralCKFTruthSeededTrackUnfilteredAssociations_recID, &b_CentralCKFTruthSeededTrackUnfilteredAssociations_recID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrackUnfilteredAssociations.weight", CentralCKFTruthSeededTrackUnfilteredAssociations_weight, &b_CentralCKFTruthSeededTrackUnfilteredAssociations_weight);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackUnfilteredAssociations_rec", &_CentralCKFTruthSeededTrackUnfilteredAssociations_rec_, &b__CentralCKFTruthSeededTrackUnfilteredAssociations_rec_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackUnfilteredAssociations_rec.index", _CentralCKFTruthSeededTrackUnfilteredAssociations_rec_index, &b__CentralCKFTruthSeededTrackUnfilteredAssociations_rec_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackUnfilteredAssociations_rec.collectionID", _CentralCKFTruthSeededTrackUnfilteredAssociations_rec_collectionID, &b__CentralCKFTruthSeededTrackUnfilteredAssociations_rec_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackUnfilteredAssociations_sim", &_CentralCKFTruthSeededTrackUnfilteredAssociations_sim_, &b__CentralCKFTruthSeededTrackUnfilteredAssociations_sim_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackUnfilteredAssociations_sim.index", _CentralCKFTruthSeededTrackUnfilteredAssociations_sim_index, &b__CentralCKFTruthSeededTrackUnfilteredAssociations_sim_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrackUnfilteredAssociations_sim.collectionID", _CentralCKFTruthSeededTrackUnfilteredAssociations_sim_collectionID, &b__CentralCKFTruthSeededTrackUnfilteredAssociations_sim_collectionID);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories", &CentralCKFTruthSeededTrajectories_, &b_CentralCKFTruthSeededTrajectories_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.type", CentralCKFTruthSeededTrajectories_type, &b_CentralCKFTruthSeededTrajectories_type);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.nStates", CentralCKFTruthSeededTrajectories_nStates, &b_CentralCKFTruthSeededTrajectories_nStates);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.nMeasurements", CentralCKFTruthSeededTrajectories_nMeasurements, &b_CentralCKFTruthSeededTrajectories_nMeasurements);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.nOutliers", CentralCKFTruthSeededTrajectories_nOutliers, &b_CentralCKFTruthSeededTrajectories_nOutliers);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.nHoles", CentralCKFTruthSeededTrajectories_nHoles, &b_CentralCKFTruthSeededTrajectories_nHoles);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.nSharedHits", CentralCKFTruthSeededTrajectories_nSharedHits, &b_CentralCKFTruthSeededTrajectories_nSharedHits);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.measurementChi2_begin", CentralCKFTruthSeededTrajectories_measurementChi2_begin, &b_CentralCKFTruthSeededTrajectories_measurementChi2_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.measurementChi2_end", CentralCKFTruthSeededTrajectories_measurementChi2_end, &b_CentralCKFTruthSeededTrajectories_measurementChi2_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.outlierChi2_begin", CentralCKFTruthSeededTrajectories_outlierChi2_begin, &b_CentralCKFTruthSeededTrajectories_outlierChi2_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.outlierChi2_end", CentralCKFTruthSeededTrajectories_outlierChi2_end, &b_CentralCKFTruthSeededTrajectories_outlierChi2_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.trackParameters_begin", CentralCKFTruthSeededTrajectories_trackParameters_begin, &b_CentralCKFTruthSeededTrajectories_trackParameters_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.trackParameters_end", CentralCKFTruthSeededTrajectories_trackParameters_end, &b_CentralCKFTruthSeededTrajectories_trackParameters_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.measurements_deprecated_begin", CentralCKFTruthSeededTrajectories_measurements_deprecated_begin, &b_CentralCKFTruthSeededTrajectories_measurements_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.measurements_deprecated_end", CentralCKFTruthSeededTrajectories_measurements_deprecated_end, &b_CentralCKFTruthSeededTrajectories_measurements_deprecated_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.outliers_deprecated_begin", CentralCKFTruthSeededTrajectories_outliers_deprecated_begin, &b_CentralCKFTruthSeededTrajectories_outliers_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectories.outliers_deprecated_end", CentralCKFTruthSeededTrajectories_outliers_deprecated_end, &b_CentralCKFTruthSeededTrajectories_outliers_deprecated_end);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_trackParameters", &_CentralCKFTruthSeededTrajectories_trackParameters_, &b__CentralCKFTruthSeededTrajectories_trackParameters_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_trackParameters.index", _CentralCKFTruthSeededTrajectories_trackParameters_index, &b__CentralCKFTruthSeededTrajectories_trackParameters_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_trackParameters.collectionID", _CentralCKFTruthSeededTrajectories_trackParameters_collectionID, &b__CentralCKFTruthSeededTrajectories_trackParameters_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_measurements_deprecated", &_CentralCKFTruthSeededTrajectories_measurements_deprecated_, &b__CentralCKFTruthSeededTrajectories_measurements_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_measurements_deprecated.index", _CentralCKFTruthSeededTrajectories_measurements_deprecated_index, &b__CentralCKFTruthSeededTrajectories_measurements_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_measurements_deprecated.collectionID", _CentralCKFTruthSeededTrajectories_measurements_deprecated_collectionID, &b__CentralCKFTruthSeededTrajectories_measurements_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_outliers_deprecated", &_CentralCKFTruthSeededTrajectories_outliers_deprecated_, &b__CentralCKFTruthSeededTrajectories_outliers_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_outliers_deprecated.index", _CentralCKFTruthSeededTrajectories_outliers_deprecated_index, &b__CentralCKFTruthSeededTrajectories_outliers_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_outliers_deprecated.collectionID", _CentralCKFTruthSeededTrajectories_outliers_deprecated_collectionID, &b__CentralCKFTruthSeededTrajectories_outliers_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_seed", &_CentralCKFTruthSeededTrajectories_seed_, &b__CentralCKFTruthSeededTrajectories_seed_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_seed.index", _CentralCKFTruthSeededTrajectories_seed_index, &b__CentralCKFTruthSeededTrajectories_seed_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_seed.collectionID", _CentralCKFTruthSeededTrajectories_seed_collectionID, &b__CentralCKFTruthSeededTrajectories_seed_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_measurementChi2", &_CentralCKFTruthSeededTrajectories_measurementChi2, &b__CentralCKFTruthSeededTrajectories_measurementChi2);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectories_outlierChi2", &_CentralCKFTruthSeededTrajectories_outlierChi2, &b__CentralCKFTruthSeededTrajectories_outlierChi2);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered", &CentralCKFTruthSeededTrajectoriesUnfiltered_, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.type", CentralCKFTruthSeededTrajectoriesUnfiltered_type, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_type);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.nStates", CentralCKFTruthSeededTrajectoriesUnfiltered_nStates, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_nStates);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.nMeasurements", CentralCKFTruthSeededTrajectoriesUnfiltered_nMeasurements, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_nMeasurements);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.nOutliers", CentralCKFTruthSeededTrajectoriesUnfiltered_nOutliers, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_nOutliers);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.nHoles", CentralCKFTruthSeededTrajectoriesUnfiltered_nHoles, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_nHoles);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.nSharedHits", CentralCKFTruthSeededTrajectoriesUnfiltered_nSharedHits, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_nSharedHits);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.measurementChi2_begin", CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_begin, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.measurementChi2_end", CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_end, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.outlierChi2_begin", CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_begin, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.outlierChi2_end", CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_end, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.trackParameters_begin", CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_begin, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.trackParameters_end", CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_end, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.measurements_deprecated_begin", CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_begin, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.measurements_deprecated_end", CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_end, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_end);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.outliers_deprecated_begin", CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_begin, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_begin);
   fChain->SetBranchAddress("CentralCKFTruthSeededTrajectoriesUnfiltered.outliers_deprecated_end", CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_end, &b_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_end);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters", &_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters.index", _CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_index, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters.collectionID", _CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_collectionID, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated", &_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated.index", _CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_index, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated.collectionID", _CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_collectionID, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated", &_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated.index", _CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_index, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated.collectionID", _CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_collectionID, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_seed", &_CentralCKFTruthSeededTrajectoriesUnfiltered_seed_, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_seed_);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_seed.index", _CentralCKFTruthSeededTrajectoriesUnfiltered_seed_index, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_seed_index);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_seed.collectionID", _CentralCKFTruthSeededTrajectoriesUnfiltered_seed_collectionID, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_seed_collectionID);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2", &_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2);
   fChain->SetBranchAddress("_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2", &_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2, &b__CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2);
   fChain->SetBranchAddress("CentralTrackerMeasurements", &CentralTrackerMeasurements_, &b_CentralTrackerMeasurements_);
   fChain->SetBranchAddress("CentralTrackerMeasurements.surface", CentralTrackerMeasurements_surface, &b_CentralTrackerMeasurements_surface);
   fChain->SetBranchAddress("CentralTrackerMeasurements.loc.a", CentralTrackerMeasurements_loc_a, &b_CentralTrackerMeasurements_loc_a);
   fChain->SetBranchAddress("CentralTrackerMeasurements.loc.b", CentralTrackerMeasurements_loc_b, &b_CentralTrackerMeasurements_loc_b);
   fChain->SetBranchAddress("CentralTrackerMeasurements.time", CentralTrackerMeasurements_time, &b_CentralTrackerMeasurements_time);
   fChain->SetBranchAddress("CentralTrackerMeasurements.covariance.xx", CentralTrackerMeasurements_covariance_xx, &b_CentralTrackerMeasurements_covariance_xx);
   fChain->SetBranchAddress("CentralTrackerMeasurements.covariance.yy", CentralTrackerMeasurements_covariance_yy, &b_CentralTrackerMeasurements_covariance_yy);
   fChain->SetBranchAddress("CentralTrackerMeasurements.covariance.zz", CentralTrackerMeasurements_covariance_zz, &b_CentralTrackerMeasurements_covariance_zz);
   fChain->SetBranchAddress("CentralTrackerMeasurements.covariance.xy", CentralTrackerMeasurements_covariance_xy, &b_CentralTrackerMeasurements_covariance_xy);
   fChain->SetBranchAddress("CentralTrackerMeasurements.covariance.xz", CentralTrackerMeasurements_covariance_xz, &b_CentralTrackerMeasurements_covariance_xz);
   fChain->SetBranchAddress("CentralTrackerMeasurements.covariance.yz", CentralTrackerMeasurements_covariance_yz, &b_CentralTrackerMeasurements_covariance_yz);
   fChain->SetBranchAddress("CentralTrackerMeasurements.weights_begin", CentralTrackerMeasurements_weights_begin, &b_CentralTrackerMeasurements_weights_begin);
   fChain->SetBranchAddress("CentralTrackerMeasurements.weights_end", CentralTrackerMeasurements_weights_end, &b_CentralTrackerMeasurements_weights_end);
   fChain->SetBranchAddress("CentralTrackerMeasurements.hits_begin", CentralTrackerMeasurements_hits_begin, &b_CentralTrackerMeasurements_hits_begin);
   fChain->SetBranchAddress("CentralTrackerMeasurements.hits_end", CentralTrackerMeasurements_hits_end, &b_CentralTrackerMeasurements_hits_end);
   fChain->SetBranchAddress("_CentralTrackerMeasurements_hits", &_CentralTrackerMeasurements_hits_, &b__CentralTrackerMeasurements_hits_);
   fChain->SetBranchAddress("_CentralTrackerMeasurements_hits.index", _CentralTrackerMeasurements_hits_index, &b__CentralTrackerMeasurements_hits_index);
   fChain->SetBranchAddress("_CentralTrackerMeasurements_hits.collectionID", _CentralTrackerMeasurements_hits_collectionID, &b__CentralTrackerMeasurements_hits_collectionID);
   fChain->SetBranchAddress("_CentralTrackerMeasurements_weights", &_CentralTrackerMeasurements_weights, &b__CentralTrackerMeasurements_weights);
   fChain->SetBranchAddress("CentralTrackerTruthSeeds_objIdx", &CentralTrackerTruthSeeds_objIdx_, &b_CentralTrackerTruthSeeds_objIdx_);
   fChain->SetBranchAddress("CentralTrackerTruthSeeds_objIdx.index", CentralTrackerTruthSeeds_objIdx_index, &b_CentralTrackerTruthSeeds_objIdx_index);
   fChain->SetBranchAddress("CentralTrackerTruthSeeds_objIdx.collectionID", CentralTrackerTruthSeeds_objIdx_collectionID, &b_CentralTrackerTruthSeeds_objIdx_collectionID);
   fChain->SetBranchAddress("CentralTrackingRawHitAssociations_objIdx", &CentralTrackingRawHitAssociations_objIdx_, &b_CentralTrackingRawHitAssociations_objIdx_);
   fChain->SetBranchAddress("CentralTrackingRawHitAssociations_objIdx.index", CentralTrackingRawHitAssociations_objIdx_index, &b_CentralTrackingRawHitAssociations_objIdx_index);
   fChain->SetBranchAddress("CentralTrackingRawHitAssociations_objIdx.collectionID", CentralTrackingRawHitAssociations_objIdx_collectionID, &b_CentralTrackingRawHitAssociations_objIdx_collectionID);
   fChain->SetBranchAddress("CentralTrackingRecHits_objIdx", &CentralTrackingRecHits_objIdx_, &b_CentralTrackingRecHits_objIdx_);
   fChain->SetBranchAddress("CentralTrackingRecHits_objIdx.index", CentralTrackingRecHits_objIdx_index, &b_CentralTrackingRecHits_objIdx_index);
   fChain->SetBranchAddress("CentralTrackingRecHits_objIdx.collectionID", CentralTrackingRecHits_objIdx_collectionID, &b_CentralTrackingRecHits_objIdx_collectionID);
   fChain->SetBranchAddress("CentralTrackSeedingResults", &CentralTrackSeedingResults_, &b_CentralTrackSeedingResults_);
   fChain->SetBranchAddress("CentralTrackSeedingResults.type", CentralTrackSeedingResults_type, &b_CentralTrackSeedingResults_type);
   fChain->SetBranchAddress("CentralTrackSeedingResults.surface", CentralTrackSeedingResults_surface, &b_CentralTrackSeedingResults_surface);
   fChain->SetBranchAddress("CentralTrackSeedingResults.loc.a", CentralTrackSeedingResults_loc_a, &b_CentralTrackSeedingResults_loc_a);
   fChain->SetBranchAddress("CentralTrackSeedingResults.loc.b", CentralTrackSeedingResults_loc_b, &b_CentralTrackSeedingResults_loc_b);
   fChain->SetBranchAddress("CentralTrackSeedingResults.theta", CentralTrackSeedingResults_theta, &b_CentralTrackSeedingResults_theta);
   fChain->SetBranchAddress("CentralTrackSeedingResults.phi", CentralTrackSeedingResults_phi, &b_CentralTrackSeedingResults_phi);
   fChain->SetBranchAddress("CentralTrackSeedingResults.qOverP", CentralTrackSeedingResults_qOverP, &b_CentralTrackSeedingResults_qOverP);
   fChain->SetBranchAddress("CentralTrackSeedingResults.time", CentralTrackSeedingResults_time, &b_CentralTrackSeedingResults_time);
   fChain->SetBranchAddress("CentralTrackSeedingResults.pdg", CentralTrackSeedingResults_pdg, &b_CentralTrackSeedingResults_pdg);
   fChain->SetBranchAddress("CentralTrackSeedingResults.covariance.covariance[21]", CentralTrackSeedingResults_covariance_covariance, &b_CentralTrackSeedingResults_covariance_covariance);
   fChain->SetBranchAddress("CentralTrackSegments", &CentralTrackSegments_, &b_CentralTrackSegments_);
   fChain->SetBranchAddress("CentralTrackSegments.length", CentralTrackSegments_length, &b_CentralTrackSegments_length);
   fChain->SetBranchAddress("CentralTrackSegments.lengthError", CentralTrackSegments_lengthError, &b_CentralTrackSegments_lengthError);
   fChain->SetBranchAddress("CentralTrackSegments.points_begin", CentralTrackSegments_points_begin, &b_CentralTrackSegments_points_begin);
   fChain->SetBranchAddress("CentralTrackSegments.points_end", CentralTrackSegments_points_end, &b_CentralTrackSegments_points_end);
   fChain->SetBranchAddress("_CentralTrackSegments_track", &_CentralTrackSegments_track_, &b__CentralTrackSegments_track_);
   fChain->SetBranchAddress("_CentralTrackSegments_track.index", _CentralTrackSegments_track_index, &b__CentralTrackSegments_track_index);
   fChain->SetBranchAddress("_CentralTrackSegments_track.collectionID", _CentralTrackSegments_track_collectionID, &b__CentralTrackSegments_track_collectionID);
   fChain->SetBranchAddress("_CentralTrackSegments_points", &_CentralTrackSegments_points_, &b__CentralTrackSegments_points_);
   fChain->SetBranchAddress("_CentralTrackSegments_points.surface", _CentralTrackSegments_points_surface, &b__CentralTrackSegments_points_surface);
   fChain->SetBranchAddress("_CentralTrackSegments_points.system", _CentralTrackSegments_points_system, &b__CentralTrackSegments_points_system);
   fChain->SetBranchAddress("_CentralTrackSegments_points.position.x", _CentralTrackSegments_points_position_x, &b__CentralTrackSegments_points_position_x);
   fChain->SetBranchAddress("_CentralTrackSegments_points.position.y", _CentralTrackSegments_points_position_y, &b__CentralTrackSegments_points_position_y);
   fChain->SetBranchAddress("_CentralTrackSegments_points.position.z", _CentralTrackSegments_points_position_z, &b__CentralTrackSegments_points_position_z);
   fChain->SetBranchAddress("_CentralTrackSegments_points.positionError.xx", _CentralTrackSegments_points_positionError_xx, &b__CentralTrackSegments_points_positionError_xx);
   fChain->SetBranchAddress("_CentralTrackSegments_points.positionError.yy", _CentralTrackSegments_points_positionError_yy, &b__CentralTrackSegments_points_positionError_yy);
   fChain->SetBranchAddress("_CentralTrackSegments_points.positionError.zz", _CentralTrackSegments_points_positionError_zz, &b__CentralTrackSegments_points_positionError_zz);
   fChain->SetBranchAddress("_CentralTrackSegments_points.positionError.xy", _CentralTrackSegments_points_positionError_xy, &b__CentralTrackSegments_points_positionError_xy);
   fChain->SetBranchAddress("_CentralTrackSegments_points.positionError.xz", _CentralTrackSegments_points_positionError_xz, &b__CentralTrackSegments_points_positionError_xz);
   fChain->SetBranchAddress("_CentralTrackSegments_points.positionError.yz", _CentralTrackSegments_points_positionError_yz, &b__CentralTrackSegments_points_positionError_yz);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentum.x", _CentralTrackSegments_points_momentum_x, &b__CentralTrackSegments_points_momentum_x);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentum.y", _CentralTrackSegments_points_momentum_y, &b__CentralTrackSegments_points_momentum_y);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentum.z", _CentralTrackSegments_points_momentum_z, &b__CentralTrackSegments_points_momentum_z);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentumError.xx", _CentralTrackSegments_points_momentumError_xx, &b__CentralTrackSegments_points_momentumError_xx);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentumError.yy", _CentralTrackSegments_points_momentumError_yy, &b__CentralTrackSegments_points_momentumError_yy);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentumError.zz", _CentralTrackSegments_points_momentumError_zz, &b__CentralTrackSegments_points_momentumError_zz);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentumError.xy", _CentralTrackSegments_points_momentumError_xy, &b__CentralTrackSegments_points_momentumError_xy);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentumError.xz", _CentralTrackSegments_points_momentumError_xz, &b__CentralTrackSegments_points_momentumError_xz);
   fChain->SetBranchAddress("_CentralTrackSegments_points.momentumError.yz", _CentralTrackSegments_points_momentumError_yz, &b__CentralTrackSegments_points_momentumError_yz);
   fChain->SetBranchAddress("_CentralTrackSegments_points.time", _CentralTrackSegments_points_time, &b__CentralTrackSegments_points_time);
   fChain->SetBranchAddress("_CentralTrackSegments_points.timeError", _CentralTrackSegments_points_timeError, &b__CentralTrackSegments_points_timeError);
   fChain->SetBranchAddress("_CentralTrackSegments_points.theta", _CentralTrackSegments_points_theta, &b__CentralTrackSegments_points_theta);
   fChain->SetBranchAddress("_CentralTrackSegments_points.phi", _CentralTrackSegments_points_phi, &b__CentralTrackSegments_points_phi);
   fChain->SetBranchAddress("_CentralTrackSegments_points.directionError.xx", _CentralTrackSegments_points_directionError_xx, &b__CentralTrackSegments_points_directionError_xx);
   fChain->SetBranchAddress("_CentralTrackSegments_points.directionError.yy", _CentralTrackSegments_points_directionError_yy, &b__CentralTrackSegments_points_directionError_yy);
   fChain->SetBranchAddress("_CentralTrackSegments_points.directionError.xy", _CentralTrackSegments_points_directionError_xy, &b__CentralTrackSegments_points_directionError_xy);
   fChain->SetBranchAddress("_CentralTrackSegments_points.pathlength", _CentralTrackSegments_points_pathlength, &b__CentralTrackSegments_points_pathlength);
   fChain->SetBranchAddress("_CentralTrackSegments_points.pathlengthError", _CentralTrackSegments_points_pathlengthError, &b__CentralTrackSegments_points_pathlengthError);
   fChain->SetBranchAddress("CentralTrackVertices", &CentralTrackVertices_, &b_CentralTrackVertices_);
   fChain->SetBranchAddress("CentralTrackVertices.type", CentralTrackVertices_type, &b_CentralTrackVertices_type);
   fChain->SetBranchAddress("CentralTrackVertices.chi2", CentralTrackVertices_chi2, &b_CentralTrackVertices_chi2);
   fChain->SetBranchAddress("CentralTrackVertices.ndf", CentralTrackVertices_ndf, &b_CentralTrackVertices_ndf);
   fChain->SetBranchAddress("CentralTrackVertices.position.x", CentralTrackVertices_position_x, &b_CentralTrackVertices_position_x);
   fChain->SetBranchAddress("CentralTrackVertices.position.y", CentralTrackVertices_position_y, &b_CentralTrackVertices_position_y);
   fChain->SetBranchAddress("CentralTrackVertices.position.z", CentralTrackVertices_position_z, &b_CentralTrackVertices_position_z);
   fChain->SetBranchAddress("CentralTrackVertices.position.t", CentralTrackVertices_position_t, &b_CentralTrackVertices_position_t);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.xx", CentralTrackVertices_positionError_xx, &b_CentralTrackVertices_positionError_xx);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.yy", CentralTrackVertices_positionError_yy, &b_CentralTrackVertices_positionError_yy);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.zz", CentralTrackVertices_positionError_zz, &b_CentralTrackVertices_positionError_zz);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.tt", CentralTrackVertices_positionError_tt, &b_CentralTrackVertices_positionError_tt);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.xy", CentralTrackVertices_positionError_xy, &b_CentralTrackVertices_positionError_xy);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.xz", CentralTrackVertices_positionError_xz, &b_CentralTrackVertices_positionError_xz);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.xt", CentralTrackVertices_positionError_xt, &b_CentralTrackVertices_positionError_xt);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.yz", CentralTrackVertices_positionError_yz, &b_CentralTrackVertices_positionError_yz);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.yt", CentralTrackVertices_positionError_yt, &b_CentralTrackVertices_positionError_yt);
   fChain->SetBranchAddress("CentralTrackVertices.positionError.zt", CentralTrackVertices_positionError_zt, &b_CentralTrackVertices_positionError_zt);
   fChain->SetBranchAddress("CentralTrackVertices.associatedParticles_begin", CentralTrackVertices_associatedParticles_begin, &b_CentralTrackVertices_associatedParticles_begin);
   fChain->SetBranchAddress("CentralTrackVertices.associatedParticles_end", CentralTrackVertices_associatedParticles_end, &b_CentralTrackVertices_associatedParticles_end);
   fChain->SetBranchAddress("_CentralTrackVertices_associatedParticles", &_CentralTrackVertices_associatedParticles_, &b__CentralTrackVertices_associatedParticles_);
   fChain->SetBranchAddress("_CentralTrackVertices_associatedParticles.index", _CentralTrackVertices_associatedParticles_index, &b__CentralTrackVertices_associatedParticles_index);
   fChain->SetBranchAddress("_CentralTrackVertices_associatedParticles.collectionID", _CentralTrackVertices_associatedParticles_collectionID, &b__CentralTrackVertices_associatedParticles_collectionID);


      fChain->SetBranchAddress("ReconstructedChargedParticleAssociations", &ReconstructedChargedParticleAssociations_, &b_ReconstructedChargedParticleAssociations_);
   fChain->SetBranchAddress("ReconstructedChargedParticleAssociations.simID", ReconstructedChargedParticleAssociations_simID, &b_ReconstructedChargedParticleAssociations_simID);
   fChain->SetBranchAddress("ReconstructedChargedParticleAssociations.recID", ReconstructedChargedParticleAssociations_recID, &b_ReconstructedChargedParticleAssociations_recID);
   fChain->SetBranchAddress("ReconstructedChargedParticleAssociations.weight", ReconstructedChargedParticleAssociations_weight, &b_ReconstructedChargedParticleAssociations_weight);
   fChain->SetBranchAddress("_ReconstructedChargedParticleAssociations_rec", &_ReconstructedChargedParticleAssociations_rec_, &b__ReconstructedChargedParticleAssociations_rec_);
   fChain->SetBranchAddress("_ReconstructedChargedParticleAssociations_rec.index", _ReconstructedChargedParticleAssociations_rec_index, &b__ReconstructedChargedParticleAssociations_rec_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticleAssociations_rec.collectionID", _ReconstructedChargedParticleAssociations_rec_collectionID, &b__ReconstructedChargedParticleAssociations_rec_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedParticleAssociations_sim", &_ReconstructedChargedParticleAssociations_sim_, &b__ReconstructedChargedParticleAssociations_sim_);
   fChain->SetBranchAddress("_ReconstructedChargedParticleAssociations_sim.index", _ReconstructedChargedParticleAssociations_sim_index, &b__ReconstructedChargedParticleAssociations_sim_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticleAssociations_sim.collectionID", _ReconstructedChargedParticleAssociations_sim_collectionID, &b__ReconstructedChargedParticleAssociations_sim_collectionID);
   fChain->SetBranchAddress("ReconstructedChargedParticles", &ReconstructedChargedParticles_, &b_ReconstructedChargedParticles_);
   fChain->SetBranchAddress("ReconstructedChargedParticles.type", ReconstructedChargedParticles_type, &b_ReconstructedChargedParticles_type);
   fChain->SetBranchAddress("ReconstructedChargedParticles.energy", ReconstructedChargedParticles_energy, &b_ReconstructedChargedParticles_energy);
   fChain->SetBranchAddress("ReconstructedChargedParticles.momentum.x", ReconstructedChargedParticles_momentum_x, &b_ReconstructedChargedParticles_momentum_x);
   fChain->SetBranchAddress("ReconstructedChargedParticles.momentum.y", ReconstructedChargedParticles_momentum_y, &b_ReconstructedChargedParticles_momentum_y);
   fChain->SetBranchAddress("ReconstructedChargedParticles.momentum.z", ReconstructedChargedParticles_momentum_z, &b_ReconstructedChargedParticles_momentum_z);
   fChain->SetBranchAddress("ReconstructedChargedParticles.referencePoint.x", ReconstructedChargedParticles_referencePoint_x, &b_ReconstructedChargedParticles_referencePoint_x);
   fChain->SetBranchAddress("ReconstructedChargedParticles.referencePoint.y", ReconstructedChargedParticles_referencePoint_y, &b_ReconstructedChargedParticles_referencePoint_y);
   fChain->SetBranchAddress("ReconstructedChargedParticles.referencePoint.z", ReconstructedChargedParticles_referencePoint_z, &b_ReconstructedChargedParticles_referencePoint_z);
   fChain->SetBranchAddress("ReconstructedChargedParticles.charge", ReconstructedChargedParticles_charge, &b_ReconstructedChargedParticles_charge);
   fChain->SetBranchAddress("ReconstructedChargedParticles.mass", ReconstructedChargedParticles_mass, &b_ReconstructedChargedParticles_mass);
   fChain->SetBranchAddress("ReconstructedChargedParticles.goodnessOfPID", ReconstructedChargedParticles_goodnessOfPID, &b_ReconstructedChargedParticles_goodnessOfPID);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.xx", ReconstructedChargedParticles_covMatrix_xx, &b_ReconstructedChargedParticles_covMatrix_xx);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.yy", ReconstructedChargedParticles_covMatrix_yy, &b_ReconstructedChargedParticles_covMatrix_yy);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.zz", ReconstructedChargedParticles_covMatrix_zz, &b_ReconstructedChargedParticles_covMatrix_zz);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.tt", ReconstructedChargedParticles_covMatrix_tt, &b_ReconstructedChargedParticles_covMatrix_tt);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.xy", ReconstructedChargedParticles_covMatrix_xy, &b_ReconstructedChargedParticles_covMatrix_xy);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.xz", ReconstructedChargedParticles_covMatrix_xz, &b_ReconstructedChargedParticles_covMatrix_xz);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.xt", ReconstructedChargedParticles_covMatrix_xt, &b_ReconstructedChargedParticles_covMatrix_xt);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.yz", ReconstructedChargedParticles_covMatrix_yz, &b_ReconstructedChargedParticles_covMatrix_yz);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.yt", ReconstructedChargedParticles_covMatrix_yt, &b_ReconstructedChargedParticles_covMatrix_yt);
   fChain->SetBranchAddress("ReconstructedChargedParticles.covMatrix.zt", ReconstructedChargedParticles_covMatrix_zt, &b_ReconstructedChargedParticles_covMatrix_zt);
   fChain->SetBranchAddress("ReconstructedChargedParticles.PDG", ReconstructedChargedParticles_PDG, &b_ReconstructedChargedParticles_PDG);
   fChain->SetBranchAddress("ReconstructedChargedParticles.clusters_begin", ReconstructedChargedParticles_clusters_begin, &b_ReconstructedChargedParticles_clusters_begin);
   fChain->SetBranchAddress("ReconstructedChargedParticles.clusters_end", ReconstructedChargedParticles_clusters_end, &b_ReconstructedChargedParticles_clusters_end);
   fChain->SetBranchAddress("ReconstructedChargedParticles.tracks_begin", ReconstructedChargedParticles_tracks_begin, &b_ReconstructedChargedParticles_tracks_begin);
   fChain->SetBranchAddress("ReconstructedChargedParticles.tracks_end", ReconstructedChargedParticles_tracks_end, &b_ReconstructedChargedParticles_tracks_end);
   fChain->SetBranchAddress("ReconstructedChargedParticles.particles_begin", ReconstructedChargedParticles_particles_begin, &b_ReconstructedChargedParticles_particles_begin);
   fChain->SetBranchAddress("ReconstructedChargedParticles.particles_end", ReconstructedChargedParticles_particles_end, &b_ReconstructedChargedParticles_particles_end);
   fChain->SetBranchAddress("ReconstructedChargedParticles.particleIDs_begin", ReconstructedChargedParticles_particleIDs_begin, &b_ReconstructedChargedParticles_particleIDs_begin);
   fChain->SetBranchAddress("ReconstructedChargedParticles.particleIDs_end", ReconstructedChargedParticles_particleIDs_end, &b_ReconstructedChargedParticles_particleIDs_end);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_clusters", &_ReconstructedChargedParticles_clusters_, &b__ReconstructedChargedParticles_clusters_);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_clusters.index", &_ReconstructedChargedParticles_clusters_index, &b__ReconstructedChargedParticles_clusters_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_clusters.collectionID", &_ReconstructedChargedParticles_clusters_collectionID, &b__ReconstructedChargedParticles_clusters_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_tracks", &_ReconstructedChargedParticles_tracks_, &b__ReconstructedChargedParticles_tracks_);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_tracks.index", _ReconstructedChargedParticles_tracks_index, &b__ReconstructedChargedParticles_tracks_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_tracks.collectionID", _ReconstructedChargedParticles_tracks_collectionID, &b__ReconstructedChargedParticles_tracks_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particles", &_ReconstructedChargedParticles_particles_, &b__ReconstructedChargedParticles_particles_);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particles.index", &_ReconstructedChargedParticles_particles_index, &b__ReconstructedChargedParticles_particles_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particles.collectionID", &_ReconstructedChargedParticles_particles_collectionID, &b__ReconstructedChargedParticles_particles_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particleIDs", &_ReconstructedChargedParticles_particleIDs_, &b__ReconstructedChargedParticles_particleIDs_);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particleIDs.index", _ReconstructedChargedParticles_particleIDs_index, &b__ReconstructedChargedParticles_particleIDs_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particleIDs.collectionID", _ReconstructedChargedParticles_particleIDs_collectionID, &b__ReconstructedChargedParticles_particleIDs_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_startVertex", &_ReconstructedChargedParticles_startVertex_, &b__ReconstructedChargedParticles_startVertex_);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_startVertex.index", _ReconstructedChargedParticles_startVertex_index, &b__ReconstructedChargedParticles_startVertex_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_startVertex.collectionID", _ReconstructedChargedParticles_startVertex_collectionID, &b__ReconstructedChargedParticles_startVertex_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particleIDUsed", &_ReconstructedChargedParticles_particleIDUsed_, &b__ReconstructedChargedParticles_particleIDUsed_);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particleIDUsed.index", _ReconstructedChargedParticles_particleIDUsed_index, &b__ReconstructedChargedParticles_particleIDUsed_index);
   fChain->SetBranchAddress("_ReconstructedChargedParticles_particleIDUsed.collectionID", _ReconstructedChargedParticles_particleIDUsed_collectionID, &b__ReconstructedChargedParticles_particleIDUsed_collectionID);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs", &ReconstructedChargedRealPIDParticleIDs_, &b_ReconstructedChargedRealPIDParticleIDs_);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs.type", &ReconstructedChargedRealPIDParticleIDs_type, &b_ReconstructedChargedRealPIDParticleIDs_type);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs.PDG", &ReconstructedChargedRealPIDParticleIDs_PDG, &b_ReconstructedChargedRealPIDParticleIDs_PDG);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs.algorithmType", &ReconstructedChargedRealPIDParticleIDs_algorithmType, &b_ReconstructedChargedRealPIDParticleIDs_algorithmType);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs.likelihood", &ReconstructedChargedRealPIDParticleIDs_likelihood, &b_ReconstructedChargedRealPIDParticleIDs_likelihood);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs.parameters_begin", &ReconstructedChargedRealPIDParticleIDs_parameters_begin, &b_ReconstructedChargedRealPIDParticleIDs_parameters_begin);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticleIDs.parameters_end", &ReconstructedChargedRealPIDParticleIDs_parameters_end, &b_ReconstructedChargedRealPIDParticleIDs_parameters_end);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticleIDs_particle", &_ReconstructedChargedRealPIDParticleIDs_particle_, &b__ReconstructedChargedRealPIDParticleIDs_particle_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticleIDs_particle.index", &_ReconstructedChargedRealPIDParticleIDs_particle_index, &b__ReconstructedChargedRealPIDParticleIDs_particle_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticleIDs_particle.collectionID", &_ReconstructedChargedRealPIDParticleIDs_particle_collectionID, &b__ReconstructedChargedRealPIDParticleIDs_particle_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticleIDs_parameters", &_ReconstructedChargedRealPIDParticleIDs_parameters, &b__ReconstructedChargedRealPIDParticleIDs_parameters);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles", &ReconstructedChargedRealPIDParticles_, &b_ReconstructedChargedRealPIDParticles_);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.type", ReconstructedChargedRealPIDParticles_type, &b_ReconstructedChargedRealPIDParticles_type);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.energy", ReconstructedChargedRealPIDParticles_energy, &b_ReconstructedChargedRealPIDParticles_energy);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.momentum.x", ReconstructedChargedRealPIDParticles_momentum_x, &b_ReconstructedChargedRealPIDParticles_momentum_x);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.momentum.y", ReconstructedChargedRealPIDParticles_momentum_y, &b_ReconstructedChargedRealPIDParticles_momentum_y);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.momentum.z", ReconstructedChargedRealPIDParticles_momentum_z, &b_ReconstructedChargedRealPIDParticles_momentum_z);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.referencePoint.x", ReconstructedChargedRealPIDParticles_referencePoint_x, &b_ReconstructedChargedRealPIDParticles_referencePoint_x);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.referencePoint.y", ReconstructedChargedRealPIDParticles_referencePoint_y, &b_ReconstructedChargedRealPIDParticles_referencePoint_y);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.referencePoint.z", ReconstructedChargedRealPIDParticles_referencePoint_z, &b_ReconstructedChargedRealPIDParticles_referencePoint_z);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.charge", ReconstructedChargedRealPIDParticles_charge, &b_ReconstructedChargedRealPIDParticles_charge);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.mass", ReconstructedChargedRealPIDParticles_mass, &b_ReconstructedChargedRealPIDParticles_mass);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.goodnessOfPID", ReconstructedChargedRealPIDParticles_goodnessOfPID, &b_ReconstructedChargedRealPIDParticles_goodnessOfPID);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.xx", ReconstructedChargedRealPIDParticles_covMatrix_xx, &b_ReconstructedChargedRealPIDParticles_covMatrix_xx);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.yy", ReconstructedChargedRealPIDParticles_covMatrix_yy, &b_ReconstructedChargedRealPIDParticles_covMatrix_yy);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.zz", ReconstructedChargedRealPIDParticles_covMatrix_zz, &b_ReconstructedChargedRealPIDParticles_covMatrix_zz);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.tt", ReconstructedChargedRealPIDParticles_covMatrix_tt, &b_ReconstructedChargedRealPIDParticles_covMatrix_tt);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.xy", ReconstructedChargedRealPIDParticles_covMatrix_xy, &b_ReconstructedChargedRealPIDParticles_covMatrix_xy);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.xz", ReconstructedChargedRealPIDParticles_covMatrix_xz, &b_ReconstructedChargedRealPIDParticles_covMatrix_xz);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.xt", ReconstructedChargedRealPIDParticles_covMatrix_xt, &b_ReconstructedChargedRealPIDParticles_covMatrix_xt);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.yz", ReconstructedChargedRealPIDParticles_covMatrix_yz, &b_ReconstructedChargedRealPIDParticles_covMatrix_yz);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.yt", ReconstructedChargedRealPIDParticles_covMatrix_yt, &b_ReconstructedChargedRealPIDParticles_covMatrix_yt);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.covMatrix.zt", ReconstructedChargedRealPIDParticles_covMatrix_zt, &b_ReconstructedChargedRealPIDParticles_covMatrix_zt);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.PDG", ReconstructedChargedRealPIDParticles_PDG, &b_ReconstructedChargedRealPIDParticles_PDG);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.clusters_begin", ReconstructedChargedRealPIDParticles_clusters_begin, &b_ReconstructedChargedRealPIDParticles_clusters_begin);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.clusters_end", ReconstructedChargedRealPIDParticles_clusters_end, &b_ReconstructedChargedRealPIDParticles_clusters_end);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.tracks_begin", ReconstructedChargedRealPIDParticles_tracks_begin, &b_ReconstructedChargedRealPIDParticles_tracks_begin);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.tracks_end", ReconstructedChargedRealPIDParticles_tracks_end, &b_ReconstructedChargedRealPIDParticles_tracks_end);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.particles_begin", ReconstructedChargedRealPIDParticles_particles_begin, &b_ReconstructedChargedRealPIDParticles_particles_begin);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.particles_end", ReconstructedChargedRealPIDParticles_particles_end, &b_ReconstructedChargedRealPIDParticles_particles_end);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.particleIDs_begin", ReconstructedChargedRealPIDParticles_particleIDs_begin, &b_ReconstructedChargedRealPIDParticles_particleIDs_begin);
   fChain->SetBranchAddress("ReconstructedChargedRealPIDParticles.particleIDs_end", ReconstructedChargedRealPIDParticles_particleIDs_end, &b_ReconstructedChargedRealPIDParticles_particleIDs_end);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_clusters", &_ReconstructedChargedRealPIDParticles_clusters_, &b__ReconstructedChargedRealPIDParticles_clusters_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_clusters.index", &_ReconstructedChargedRealPIDParticles_clusters_index, &b__ReconstructedChargedRealPIDParticles_clusters_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_clusters.collectionID", &_ReconstructedChargedRealPIDParticles_clusters_collectionID, &b__ReconstructedChargedRealPIDParticles_clusters_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_tracks", &_ReconstructedChargedRealPIDParticles_tracks_, &b__ReconstructedChargedRealPIDParticles_tracks_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_tracks.index", _ReconstructedChargedRealPIDParticles_tracks_index, &b__ReconstructedChargedRealPIDParticles_tracks_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_tracks.collectionID", _ReconstructedChargedRealPIDParticles_tracks_collectionID, &b__ReconstructedChargedRealPIDParticles_tracks_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particles", &_ReconstructedChargedRealPIDParticles_particles_, &b__ReconstructedChargedRealPIDParticles_particles_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particles.index", &_ReconstructedChargedRealPIDParticles_particles_index, &b__ReconstructedChargedRealPIDParticles_particles_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particles.collectionID", &_ReconstructedChargedRealPIDParticles_particles_collectionID, &b__ReconstructedChargedRealPIDParticles_particles_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particleIDs", &_ReconstructedChargedRealPIDParticles_particleIDs_, &b__ReconstructedChargedRealPIDParticles_particleIDs_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particleIDs.index", &_ReconstructedChargedRealPIDParticles_particleIDs_index, &b__ReconstructedChargedRealPIDParticles_particleIDs_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particleIDs.collectionID", &_ReconstructedChargedRealPIDParticles_particleIDs_collectionID, &b__ReconstructedChargedRealPIDParticles_particleIDs_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_startVertex", &_ReconstructedChargedRealPIDParticles_startVertex_, &b__ReconstructedChargedRealPIDParticles_startVertex_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_startVertex.index", _ReconstructedChargedRealPIDParticles_startVertex_index, &b__ReconstructedChargedRealPIDParticles_startVertex_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_startVertex.collectionID", _ReconstructedChargedRealPIDParticles_startVertex_collectionID, &b__ReconstructedChargedRealPIDParticles_startVertex_collectionID);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particleIDUsed", &_ReconstructedChargedRealPIDParticles_particleIDUsed_, &b__ReconstructedChargedRealPIDParticles_particleIDUsed_);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particleIDUsed.index", _ReconstructedChargedRealPIDParticles_particleIDUsed_index, &b__ReconstructedChargedRealPIDParticles_particleIDUsed_index);
   fChain->SetBranchAddress("_ReconstructedChargedRealPIDParticles_particleIDUsed.collectionID", _ReconstructedChargedRealPIDParticles_particleIDUsed_collectionID, &b__ReconstructedChargedRealPIDParticles_particleIDUsed_collectionID);
   fChain->SetBranchAddress("ReconstructedElectrons_objIdx", &ReconstructedElectrons_objIdx_, &b_ReconstructedElectrons_objIdx_);
   fChain->SetBranchAddress("ReconstructedElectrons_objIdx.index", &ReconstructedElectrons_objIdx_index, &b_ReconstructedElectrons_objIdx_index);
   fChain->SetBranchAddress("ReconstructedElectrons_objIdx.collectionID", &ReconstructedElectrons_objIdx_collectionID, &b_ReconstructedElectrons_objIdx_collectionID);

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

Bool_t   recoQA::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void recoQA::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t recoQA::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

// == e == MakeClass Default Functions == s ==

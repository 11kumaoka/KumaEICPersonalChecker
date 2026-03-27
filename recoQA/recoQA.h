//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 23 01:35:33 2024 by ROOT version 6.26/06
// from TTree tree/sPHENIX info.
// found on file: .root
//////////////////////////////////////////////////////////

// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// And please search for the word "kuma example",
// You will find lines to need to modify
//
// Additionally, you need to modify Algorithm.cc and compile.C
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

#ifndef recoQA_h
#define recoQA_h

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>

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


class recoQA {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any. 
   recoQA(TTree *tree=0, std::string iFileName="", std::string oFileName="");
   virtual ~recoQA();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::string fDir = "./";
   std::string iFileName = "";
   std::string oFileName = "";
   TFile *oFile; // output root file


// Fixed size dimensions of array or collections stored in the TTree if any.


// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxEventHeader_TS = 1;

   static constexpr Int_t kMaxMCParticles = 9999;
   static constexpr Int_t kMax_MCParticles_parents = 9999;
   static constexpr Int_t kMax_MCParticles_daughters = 9999;

   static constexpr Int_t kMaxCentralCKFTrackAssociations = 99999;
   static constexpr Int_t kMax_CentralCKFTrackAssociations_rec = 99999;
   static constexpr Int_t kMax_CentralCKFTrackAssociations_sim = 99999;
   static constexpr Int_t kMaxCentralCKFTrackParameters = 99999;
   static constexpr Int_t kMaxCentralCKFTrackParametersUnfiltered = 99999;
   static constexpr Int_t kMaxCentralCKFTracks = 99999;
   static constexpr Int_t kMax_CentralCKFTracks_measurements = 99999;
   static constexpr Int_t kMax_CentralCKFTracks_tracks = 99999;
   static constexpr Int_t kMax_CentralCKFTracks_trajectory = 99999;
   static constexpr Int_t kMaxCentralCKFTracksUnfiltered = 99999;
   static constexpr Int_t kMax_CentralCKFTracksUnfiltered_measurements = 99999;
   static constexpr Int_t kMax_CentralCKFTracksUnfiltered_tracks = 99999;
   static constexpr Int_t kMax_CentralCKFTracksUnfiltered_trajectory = 99999;
   static constexpr Int_t kMaxCentralCKFTrackUnfilteredAssociations = 99999;
   static constexpr Int_t kMax_CentralCKFTrackUnfilteredAssociations_rec = 99999;
   static constexpr Int_t kMax_CentralCKFTrackUnfilteredAssociations_sim = 99999;
   static constexpr Int_t kMaxCentralCKFTrajectories = 99999;
   static constexpr Int_t kMax_CentralCKFTrajectories_trackParameters = 99999;
   static constexpr Int_t kMax_CentralCKFTrajectories_measurements_deprecated = 99999;
   static constexpr Int_t kMax_CentralCKFTrajectories_outliers_deprecated = 99999;
   static constexpr Int_t kMax_CentralCKFTrajectories_seed = 99999;
   static constexpr Int_t kMaxCentralCKFTrajectoriesUnfiltered = 99999;
   static constexpr Int_t kMax_CentralCKFTrajectoriesUnfiltered_trackParameters = 999999;
   static constexpr Int_t kMax_CentralCKFTrajectoriesUnfiltered_measurements_deprecated = 999999;
   static constexpr Int_t kMax_CentralCKFTrajectoriesUnfiltered_outliers_deprecated = 999999;
   static constexpr Int_t kMax_CentralCKFTrajectoriesUnfiltered_seed = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTrackAssociations = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrackAssociations_rec = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrackAssociations_sim = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTrackParameters = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTrackParametersUnfiltered = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTracks = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTracks_measurements = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTracks_tracks = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTracks_trajectory = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTracksUnfiltered = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTracksUnfiltered_measurements = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTracksUnfiltered_tracks = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTracksUnfiltered_trajectory = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTrackUnfilteredAssociations = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrackUnfilteredAssociations_rec = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrackUnfilteredAssociations_sim = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTrajectories = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectories_trackParameters = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectories_measurements_deprecated = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectories_outliers_deprecated = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectories_seed = 99999;
   static constexpr Int_t kMaxCentralCKFTruthSeededTrajectoriesUnfiltered = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated = 99999;
   static constexpr Int_t kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_seed = 99999;
   static constexpr Int_t kMaxCentralTrackerMeasurements = 999999;
   static constexpr Int_t kMax_CentralTrackerMeasurements_hits = 999999;
   static constexpr Int_t kMaxCentralTrackerTruthSeeds_objIdx = 31;
   static constexpr Int_t kMaxCentralTrackingRawHitAssociations_objIdx = 999999;
   static constexpr Int_t kMaxCentralTrackingRecHits_objIdx = 99999;
   static constexpr Int_t kMaxCentralTrackSeedingResults = 99999;
   static constexpr Int_t kMaxCentralTrackSegments = 99999;
   static constexpr Int_t kMax_CentralTrackSegments_track = 99999;
   static constexpr Int_t kMax_CentralTrackSegments_points = 99999;
   static constexpr Int_t kMaxCentralTrackVertices = 99999;
   static constexpr Int_t kMax_CentralTrackVertices_associatedParticles = 99999;

   static constexpr Int_t kMaxReconstructedChargedParticleAssociations = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticleAssociations_rec = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticleAssociations_sim = 99999;
   static constexpr Int_t kMaxReconstructedChargedParticles = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticles_clusters = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticles_tracks = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticles_particles = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticles_particleIDs = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticles_startVertex = 99999;
   static constexpr Int_t kMax_ReconstructedChargedParticles_particleIDUsed = 99999;
   static constexpr Int_t kMaxReconstructedChargedRealPIDParticleIDs = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticleIDs_particle = 99999;
   static constexpr Int_t kMaxReconstructedChargedRealPIDParticles = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticles_clusters = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticles_tracks = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticles_particles = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticles_particleIDs = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticles_startVertex = 99999;
   static constexpr Int_t kMax_ReconstructedChargedRealPIDParticles_particleIDUsed = 99999;
   static constexpr Int_t kMaxReconstructedElectrons_objIdx = 99999;


   // Declaration of leaf types
   Int_t           EventHeader_TS_;
   Int_t           EventHeader_TS_eventNumber[kMaxEventHeader_TS];   //[EventHeader_TS_]
   Int_t           EventHeader_TS_runNumber[kMaxEventHeader_TS];   //[EventHeader_TS_]
   ULong_t         EventHeader_TS_timeStamp[kMaxEventHeader_TS];   //[EventHeader_TS_]
   Double_t        EventHeader_TS_weight[kMaxEventHeader_TS];   //[EventHeader_TS_]
   UInt_t          EventHeader_TS_weights_begin[kMaxEventHeader_TS];   //[EventHeader_TS_]
   UInt_t          EventHeader_TS_weights_end[kMaxEventHeader_TS];   //[EventHeader_TS_]
   std::vector<double>  *_EventHeader_TS_weights;
   
   Int_t           MCParticles_;
   Int_t           MCParticles_PDG[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_generatorStatus[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_simulatorStatus[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_charge[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_time[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_mass[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_vertex_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_vertex_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_vertex_z[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_endpoint_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_endpoint_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_endpoint_z[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentum_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentum_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentum_z[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentumAtEndpoint_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentumAtEndpoint_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentumAtEndpoint_z[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_spin_x[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_spin_y[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_spin_z[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_colorFlow_a[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_colorFlow_b[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_parents_begin[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_parents_end[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_daughters_begin[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_daughters_end[kMaxMCParticles];   //[MCParticles_]
   Int_t           _MCParticles_parents_;
   Int_t           _MCParticles_parents_index[kMax_MCParticles_parents];   //[_MCParticles_parents_]
   UInt_t          _MCParticles_parents_collectionID[kMax_MCParticles_parents];   //[_MCParticles_parents_]
   Int_t           _MCParticles_daughters_;
   Int_t           _MCParticles_daughters_index[kMax_MCParticles_daughters];   //[_MCParticles_daughters_]
   UInt_t          _MCParticles_daughters_collectionID[kMax_MCParticles_daughters];   //[_MCParticles_daughters_]


   Int_t           CentralCKFTrackAssociations_;
   UInt_t          CentralCKFTrackAssociations_simID[kMaxCentralCKFTrackAssociations];   //[CentralCKFTrackAssociations_]
   UInt_t          CentralCKFTrackAssociations_recID[kMaxCentralCKFTrackAssociations];   //[CentralCKFTrackAssociations_]
   Float_t         CentralCKFTrackAssociations_weight[kMaxCentralCKFTrackAssociations];   //[CentralCKFTrackAssociations_]
   Int_t           _CentralCKFTrackAssociations_rec_;
   Int_t           _CentralCKFTrackAssociations_rec_index[kMax_CentralCKFTrackAssociations_rec];   //[_CentralCKFTrackAssociations_rec_]
   UInt_t          _CentralCKFTrackAssociations_rec_collectionID[kMax_CentralCKFTrackAssociations_rec];   //[_CentralCKFTrackAssociations_rec_]
   Int_t           _CentralCKFTrackAssociations_sim_;
   Int_t           _CentralCKFTrackAssociations_sim_index[kMax_CentralCKFTrackAssociations_sim];   //[_CentralCKFTrackAssociations_sim_]
   UInt_t          _CentralCKFTrackAssociations_sim_collectionID[kMax_CentralCKFTrackAssociations_sim];   //[_CentralCKFTrackAssociations_sim_]
   Int_t           CentralCKFTrackParameters_;
   Int_t           CentralCKFTrackParameters_type[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   ULong_t         CentralCKFTrackParameters_surface[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_loc_a[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_loc_b[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_theta[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_phi[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_qOverP[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_time[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Int_t           CentralCKFTrackParameters_pdg[kMaxCentralCKFTrackParameters];   //[CentralCKFTrackParameters_]
   Float_t         CentralCKFTrackParameters_covariance_covariance[kMaxCentralCKFTrackParameters][21];   //[CentralCKFTrackParameters_]
   Int_t           CentralCKFTrackParametersUnfiltered_;
   Int_t           CentralCKFTrackParametersUnfiltered_type[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   ULong_t         CentralCKFTrackParametersUnfiltered_surface[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_loc_a[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_loc_b[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_theta[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_phi[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_qOverP[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_time[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Int_t           CentralCKFTrackParametersUnfiltered_pdg[kMaxCentralCKFTrackParametersUnfiltered];   //[CentralCKFTrackParametersUnfiltered_]
   Float_t         CentralCKFTrackParametersUnfiltered_covariance_covariance[kMaxCentralCKFTrackParametersUnfiltered][21];   //[CentralCKFTrackParametersUnfiltered_]
   Int_t           CentralCKFTracks_;
   Int_t           CentralCKFTracks_type[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_position_x[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_position_y[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_position_z[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_momentum_x[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_momentum_y[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_momentum_z[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_positionMomentumCovariance_covariance[kMaxCentralCKFTracks][21];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_time[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_timeError[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_charge[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Float_t         CentralCKFTracks_chi2[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   UInt_t          CentralCKFTracks_ndf[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Int_t           CentralCKFTracks_pdg[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   UInt_t          CentralCKFTracks_measurements_begin[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   UInt_t          CentralCKFTracks_measurements_end[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   UInt_t          CentralCKFTracks_tracks_begin[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   UInt_t          CentralCKFTracks_tracks_end[kMaxCentralCKFTracks];   //[CentralCKFTracks_]
   Int_t           _CentralCKFTracks_measurements_;
   Int_t           _CentralCKFTracks_measurements_index[kMax_CentralCKFTracks_measurements];   //[_CentralCKFTracks_measurements_]
   UInt_t          _CentralCKFTracks_measurements_collectionID[kMax_CentralCKFTracks_measurements];   //[_CentralCKFTracks_measurements_]
   Int_t           _CentralCKFTracks_tracks_;
   Int_t           _CentralCKFTracks_tracks_index[kMax_CentralCKFTracks_tracks];   //[_CentralCKFTracks_tracks_]
   UInt_t          _CentralCKFTracks_tracks_collectionID[kMax_CentralCKFTracks_tracks];   //[_CentralCKFTracks_tracks_]
   Int_t           _CentralCKFTracks_trajectory_;
   Int_t           _CentralCKFTracks_trajectory_index[kMax_CentralCKFTracks_trajectory];   //[_CentralCKFTracks_trajectory_]
   UInt_t          _CentralCKFTracks_trajectory_collectionID[kMax_CentralCKFTracks_trajectory];   //[_CentralCKFTracks_trajectory_]
   Int_t           CentralCKFTracksUnfiltered_;
   Int_t           CentralCKFTracksUnfiltered_type[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_position_x[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_position_y[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_position_z[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_momentum_x[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_momentum_y[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_momentum_z[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_positionMomentumCovariance_covariance[kMaxCentralCKFTracksUnfiltered][21];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_time[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_timeError[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_charge[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Float_t         CentralCKFTracksUnfiltered_chi2[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   UInt_t          CentralCKFTracksUnfiltered_ndf[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Int_t           CentralCKFTracksUnfiltered_pdg[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   UInt_t          CentralCKFTracksUnfiltered_measurements_begin[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   UInt_t          CentralCKFTracksUnfiltered_measurements_end[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   UInt_t          CentralCKFTracksUnfiltered_tracks_begin[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   UInt_t          CentralCKFTracksUnfiltered_tracks_end[kMaxCentralCKFTracksUnfiltered];   //[CentralCKFTracksUnfiltered_]
   Int_t           _CentralCKFTracksUnfiltered_measurements_;
   Int_t           _CentralCKFTracksUnfiltered_measurements_index[kMax_CentralCKFTracksUnfiltered_measurements];   //[_CentralCKFTracksUnfiltered_measurements_]
   UInt_t          _CentralCKFTracksUnfiltered_measurements_collectionID[kMax_CentralCKFTracksUnfiltered_measurements];   //[_CentralCKFTracksUnfiltered_measurements_]
   Int_t           _CentralCKFTracksUnfiltered_tracks_;
   Int_t           _CentralCKFTracksUnfiltered_tracks_index[kMax_CentralCKFTracksUnfiltered_tracks];   //[_CentralCKFTracksUnfiltered_tracks_]
   UInt_t          _CentralCKFTracksUnfiltered_tracks_collectionID[kMax_CentralCKFTracksUnfiltered_tracks];   //[_CentralCKFTracksUnfiltered_tracks_]
   Int_t           _CentralCKFTracksUnfiltered_trajectory_;
   Int_t           _CentralCKFTracksUnfiltered_trajectory_index[kMax_CentralCKFTracksUnfiltered_trajectory];   //[_CentralCKFTracksUnfiltered_trajectory_]
   UInt_t          _CentralCKFTracksUnfiltered_trajectory_collectionID[kMax_CentralCKFTracksUnfiltered_trajectory];   //[_CentralCKFTracksUnfiltered_trajectory_]
   Int_t           CentralCKFTrackUnfilteredAssociations_;
   UInt_t          CentralCKFTrackUnfilteredAssociations_simID[kMaxCentralCKFTrackUnfilteredAssociations];   //[CentralCKFTrackUnfilteredAssociations_]
   UInt_t          CentralCKFTrackUnfilteredAssociations_recID[kMaxCentralCKFTrackUnfilteredAssociations];   //[CentralCKFTrackUnfilteredAssociations_]
   Float_t         CentralCKFTrackUnfilteredAssociations_weight[kMaxCentralCKFTrackUnfilteredAssociations];   //[CentralCKFTrackUnfilteredAssociations_]
   Int_t           _CentralCKFTrackUnfilteredAssociations_rec_;
   Int_t           _CentralCKFTrackUnfilteredAssociations_rec_index[kMax_CentralCKFTrackUnfilteredAssociations_rec];   //[_CentralCKFTrackUnfilteredAssociations_rec_]
   UInt_t          _CentralCKFTrackUnfilteredAssociations_rec_collectionID[kMax_CentralCKFTrackUnfilteredAssociations_rec];   //[_CentralCKFTrackUnfilteredAssociations_rec_]
   Int_t           _CentralCKFTrackUnfilteredAssociations_sim_;
   Int_t           _CentralCKFTrackUnfilteredAssociations_sim_index[kMax_CentralCKFTrackUnfilteredAssociations_sim];   //[_CentralCKFTrackUnfilteredAssociations_sim_]
   UInt_t          _CentralCKFTrackUnfilteredAssociations_sim_collectionID[kMax_CentralCKFTrackUnfilteredAssociations_sim];   //[_CentralCKFTrackUnfilteredAssociations_sim_]
   Int_t           CentralCKFTrajectories_;
   UInt_t          CentralCKFTrajectories_type[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_nStates[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_nMeasurements[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_nOutliers[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_nHoles[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_nSharedHits[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_measurementChi2_begin[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_measurementChi2_end[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_outlierChi2_begin[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_outlierChi2_end[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_trackParameters_begin[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_trackParameters_end[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_measurements_deprecated_begin[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_measurements_deprecated_end[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_outliers_deprecated_begin[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   UInt_t          CentralCKFTrajectories_outliers_deprecated_end[kMaxCentralCKFTrajectories];   //[CentralCKFTrajectories_]
   Int_t           _CentralCKFTrajectories_trackParameters_;
   Int_t           _CentralCKFTrajectories_trackParameters_index[kMax_CentralCKFTrajectories_trackParameters];   //[_CentralCKFTrajectories_trackParameters_]
   UInt_t          _CentralCKFTrajectories_trackParameters_collectionID[kMax_CentralCKFTrajectories_trackParameters];   //[_CentralCKFTrajectories_trackParameters_]
   Int_t           _CentralCKFTrajectories_measurements_deprecated_;
   Int_t           _CentralCKFTrajectories_measurements_deprecated_index[kMax_CentralCKFTrajectories_measurements_deprecated];   //[_CentralCKFTrajectories_measurements_deprecated_]
   UInt_t          _CentralCKFTrajectories_measurements_deprecated_collectionID[kMax_CentralCKFTrajectories_measurements_deprecated];   //[_CentralCKFTrajectories_measurements_deprecated_]
   Int_t           _CentralCKFTrajectories_outliers_deprecated_;
   Int_t           _CentralCKFTrajectories_outliers_deprecated_index[kMax_CentralCKFTrajectories_outliers_deprecated];   //[_CentralCKFTrajectories_outliers_deprecated_]
   UInt_t          _CentralCKFTrajectories_outliers_deprecated_collectionID[kMax_CentralCKFTrajectories_outliers_deprecated];   //[_CentralCKFTrajectories_outliers_deprecated_]
   Int_t           _CentralCKFTrajectories_seed_;
   Int_t           _CentralCKFTrajectories_seed_index[kMax_CentralCKFTrajectories_seed];   //[_CentralCKFTrajectories_seed_]
   UInt_t          _CentralCKFTrajectories_seed_collectionID[kMax_CentralCKFTrajectories_seed];   //[_CentralCKFTrajectories_seed_]
   std::vector<float>   *_CentralCKFTrajectories_measurementChi2;
   std::vector<float>   *_CentralCKFTrajectories_outlierChi2;
   Int_t           CentralCKFTrajectoriesUnfiltered_;
   UInt_t          CentralCKFTrajectoriesUnfiltered_type[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_nStates[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_nMeasurements[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_nOutliers[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_nHoles[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_nSharedHits[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_measurementChi2_begin[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_measurementChi2_end[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_outlierChi2_begin[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_outlierChi2_end[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_trackParameters_begin[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_trackParameters_end[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_measurements_deprecated_begin[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_measurements_deprecated_end[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_outliers_deprecated_begin[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTrajectoriesUnfiltered_outliers_deprecated_end[kMaxCentralCKFTrajectoriesUnfiltered];   //[CentralCKFTrajectoriesUnfiltered_]
   Int_t           _CentralCKFTrajectoriesUnfiltered_trackParameters_;
   Int_t           _CentralCKFTrajectoriesUnfiltered_trackParameters_index[kMax_CentralCKFTrajectoriesUnfiltered_trackParameters];   //[_CentralCKFTrajectoriesUnfiltered_trackParameters_]
   UInt_t          _CentralCKFTrajectoriesUnfiltered_trackParameters_collectionID[kMax_CentralCKFTrajectoriesUnfiltered_trackParameters];   //[_CentralCKFTrajectoriesUnfiltered_trackParameters_]
   Int_t           _CentralCKFTrajectoriesUnfiltered_measurements_deprecated_;
   Int_t           _CentralCKFTrajectoriesUnfiltered_measurements_deprecated_index[kMax_CentralCKFTrajectoriesUnfiltered_measurements_deprecated];   //[_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_]
   UInt_t          _CentralCKFTrajectoriesUnfiltered_measurements_deprecated_collectionID[kMax_CentralCKFTrajectoriesUnfiltered_measurements_deprecated];   //[_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_]
   Int_t           _CentralCKFTrajectoriesUnfiltered_outliers_deprecated_;
   Int_t           _CentralCKFTrajectoriesUnfiltered_outliers_deprecated_index[kMax_CentralCKFTrajectoriesUnfiltered_outliers_deprecated];   //[_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_]
   UInt_t          _CentralCKFTrajectoriesUnfiltered_outliers_deprecated_collectionID[kMax_CentralCKFTrajectoriesUnfiltered_outliers_deprecated];   //[_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_]
   Int_t           _CentralCKFTrajectoriesUnfiltered_seed_;
   Int_t           _CentralCKFTrajectoriesUnfiltered_seed_index[kMax_CentralCKFTrajectoriesUnfiltered_seed];   //[_CentralCKFTrajectoriesUnfiltered_seed_]
   UInt_t          _CentralCKFTrajectoriesUnfiltered_seed_collectionID[kMax_CentralCKFTrajectoriesUnfiltered_seed];   //[_CentralCKFTrajectoriesUnfiltered_seed_]
   std::vector<float>   *_CentralCKFTrajectoriesUnfiltered_measurementChi2;
   std::vector<float>   *_CentralCKFTrajectoriesUnfiltered_outlierChi2;
   Int_t           CentralCKFTruthSeededTrackAssociations_;
   UInt_t          CentralCKFTruthSeededTrackAssociations_simID[kMaxCentralCKFTruthSeededTrackAssociations];   //[CentralCKFTruthSeededTrackAssociations_]
   UInt_t          CentralCKFTruthSeededTrackAssociations_recID[kMaxCentralCKFTruthSeededTrackAssociations];   //[CentralCKFTruthSeededTrackAssociations_]
   Float_t         CentralCKFTruthSeededTrackAssociations_weight[kMaxCentralCKFTruthSeededTrackAssociations];   //[CentralCKFTruthSeededTrackAssociations_]
   Int_t           _CentralCKFTruthSeededTrackAssociations_rec_;
   Int_t           _CentralCKFTruthSeededTrackAssociations_rec_index[kMax_CentralCKFTruthSeededTrackAssociations_rec];   //[_CentralCKFTruthSeededTrackAssociations_rec_]
   UInt_t          _CentralCKFTruthSeededTrackAssociations_rec_collectionID[kMax_CentralCKFTruthSeededTrackAssociations_rec];   //[_CentralCKFTruthSeededTrackAssociations_rec_]
   Int_t           _CentralCKFTruthSeededTrackAssociations_sim_;
   Int_t           _CentralCKFTruthSeededTrackAssociations_sim_index[kMax_CentralCKFTruthSeededTrackAssociations_sim];   //[_CentralCKFTruthSeededTrackAssociations_sim_]
   UInt_t          _CentralCKFTruthSeededTrackAssociations_sim_collectionID[kMax_CentralCKFTruthSeededTrackAssociations_sim];   //[_CentralCKFTruthSeededTrackAssociations_sim_]
   Int_t           CentralCKFTruthSeededTrackParameters_;
   Int_t           CentralCKFTruthSeededTrackParameters_type[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   ULong_t         CentralCKFTruthSeededTrackParameters_surface[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_loc_a[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_loc_b[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_theta[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_phi[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_qOverP[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_time[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Int_t           CentralCKFTruthSeededTrackParameters_pdg[kMaxCentralCKFTruthSeededTrackParameters];   //[CentralCKFTruthSeededTrackParameters_]
   Float_t         CentralCKFTruthSeededTrackParameters_covariance_covariance[kMaxCentralCKFTruthSeededTrackParameters][21];   //[CentralCKFTruthSeededTrackParameters_]
   Int_t           CentralCKFTruthSeededTrackParametersUnfiltered_;
   Int_t           CentralCKFTruthSeededTrackParametersUnfiltered_type[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   ULong_t         CentralCKFTruthSeededTrackParametersUnfiltered_surface[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_loc_a[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_loc_b[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_theta[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_phi[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_qOverP[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_time[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Int_t           CentralCKFTruthSeededTrackParametersUnfiltered_pdg[kMaxCentralCKFTruthSeededTrackParametersUnfiltered];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Float_t         CentralCKFTruthSeededTrackParametersUnfiltered_covariance_covariance[kMaxCentralCKFTruthSeededTrackParametersUnfiltered][21];   //[CentralCKFTruthSeededTrackParametersUnfiltered_]
   Int_t           CentralCKFTruthSeededTracks_;
   Int_t           CentralCKFTruthSeededTracks_type[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_position_x[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_position_y[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_position_z[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_momentum_x[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_momentum_y[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_momentum_z[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_positionMomentumCovariance_covariance[kMaxCentralCKFTruthSeededTracks][21];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_time[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_timeError[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_charge[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Float_t         CentralCKFTruthSeededTracks_chi2[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   UInt_t          CentralCKFTruthSeededTracks_ndf[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Int_t           CentralCKFTruthSeededTracks_pdg[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   UInt_t          CentralCKFTruthSeededTracks_measurements_begin[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   UInt_t          CentralCKFTruthSeededTracks_measurements_end[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   UInt_t          CentralCKFTruthSeededTracks_tracks_begin[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   UInt_t          CentralCKFTruthSeededTracks_tracks_end[kMaxCentralCKFTruthSeededTracks];   //[CentralCKFTruthSeededTracks_]
   Int_t           _CentralCKFTruthSeededTracks_measurements_;
   Int_t           _CentralCKFTruthSeededTracks_measurements_index[kMax_CentralCKFTruthSeededTracks_measurements];   //[_CentralCKFTruthSeededTracks_measurements_]
   UInt_t          _CentralCKFTruthSeededTracks_measurements_collectionID[kMax_CentralCKFTruthSeededTracks_measurements];   //[_CentralCKFTruthSeededTracks_measurements_]
   Int_t           _CentralCKFTruthSeededTracks_tracks_;
   Int_t           _CentralCKFTruthSeededTracks_tracks_index[kMax_CentralCKFTruthSeededTracks_tracks];   //[_CentralCKFTruthSeededTracks_tracks_]
   UInt_t          _CentralCKFTruthSeededTracks_tracks_collectionID[kMax_CentralCKFTruthSeededTracks_tracks];   //[_CentralCKFTruthSeededTracks_tracks_]
   Int_t           _CentralCKFTruthSeededTracks_trajectory_;
   Int_t           _CentralCKFTruthSeededTracks_trajectory_index[kMax_CentralCKFTruthSeededTracks_trajectory];   //[_CentralCKFTruthSeededTracks_trajectory_]
   UInt_t          _CentralCKFTruthSeededTracks_trajectory_collectionID[kMax_CentralCKFTruthSeededTracks_trajectory];   //[_CentralCKFTruthSeededTracks_trajectory_]
   Int_t           CentralCKFTruthSeededTracksUnfiltered_;
   Int_t           CentralCKFTruthSeededTracksUnfiltered_type[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_position_x[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_position_y[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_position_z[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_momentum_x[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_momentum_y[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_momentum_z[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_positionMomentumCovariance_covariance[kMaxCentralCKFTruthSeededTracksUnfiltered][21];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_time[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_timeError[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_charge[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Float_t         CentralCKFTruthSeededTracksUnfiltered_chi2[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   UInt_t          CentralCKFTruthSeededTracksUnfiltered_ndf[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Int_t           CentralCKFTruthSeededTracksUnfiltered_pdg[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   UInt_t          CentralCKFTruthSeededTracksUnfiltered_measurements_begin[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   UInt_t          CentralCKFTruthSeededTracksUnfiltered_measurements_end[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   UInt_t          CentralCKFTruthSeededTracksUnfiltered_tracks_begin[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   UInt_t          CentralCKFTruthSeededTracksUnfiltered_tracks_end[kMaxCentralCKFTruthSeededTracksUnfiltered];   //[CentralCKFTruthSeededTracksUnfiltered_]
   Int_t           _CentralCKFTruthSeededTracksUnfiltered_measurements_;
   Int_t           _CentralCKFTruthSeededTracksUnfiltered_measurements_index[kMax_CentralCKFTruthSeededTracksUnfiltered_measurements];   //[_CentralCKFTruthSeededTracksUnfiltered_measurements_]
   UInt_t          _CentralCKFTruthSeededTracksUnfiltered_measurements_collectionID[kMax_CentralCKFTruthSeededTracksUnfiltered_measurements];   //[_CentralCKFTruthSeededTracksUnfiltered_measurements_]
   Int_t           _CentralCKFTruthSeededTracksUnfiltered_tracks_;
   Int_t           _CentralCKFTruthSeededTracksUnfiltered_tracks_index[kMax_CentralCKFTruthSeededTracksUnfiltered_tracks];   //[_CentralCKFTruthSeededTracksUnfiltered_tracks_]
   UInt_t          _CentralCKFTruthSeededTracksUnfiltered_tracks_collectionID[kMax_CentralCKFTruthSeededTracksUnfiltered_tracks];   //[_CentralCKFTruthSeededTracksUnfiltered_tracks_]
   Int_t           _CentralCKFTruthSeededTracksUnfiltered_trajectory_;
   Int_t           _CentralCKFTruthSeededTracksUnfiltered_trajectory_index[kMax_CentralCKFTruthSeededTracksUnfiltered_trajectory];   //[_CentralCKFTruthSeededTracksUnfiltered_trajectory_]
   UInt_t          _CentralCKFTruthSeededTracksUnfiltered_trajectory_collectionID[kMax_CentralCKFTruthSeededTracksUnfiltered_trajectory];   //[_CentralCKFTruthSeededTracksUnfiltered_trajectory_]
   Int_t           CentralCKFTruthSeededTrackUnfilteredAssociations_;
   UInt_t          CentralCKFTruthSeededTrackUnfilteredAssociations_simID[kMaxCentralCKFTruthSeededTrackUnfilteredAssociations];   //[CentralCKFTruthSeededTrackUnfilteredAssociations_]
   UInt_t          CentralCKFTruthSeededTrackUnfilteredAssociations_recID[kMaxCentralCKFTruthSeededTrackUnfilteredAssociations];   //[CentralCKFTruthSeededTrackUnfilteredAssociations_]
   Float_t         CentralCKFTruthSeededTrackUnfilteredAssociations_weight[kMaxCentralCKFTruthSeededTrackUnfilteredAssociations];   //[CentralCKFTruthSeededTrackUnfilteredAssociations_]
   Int_t           _CentralCKFTruthSeededTrackUnfilteredAssociations_rec_;
   Int_t           _CentralCKFTruthSeededTrackUnfilteredAssociations_rec_index[kMax_CentralCKFTruthSeededTrackUnfilteredAssociations_rec];   //[_CentralCKFTruthSeededTrackUnfilteredAssociations_rec_]
   UInt_t          _CentralCKFTruthSeededTrackUnfilteredAssociations_rec_collectionID[kMax_CentralCKFTruthSeededTrackUnfilteredAssociations_rec];   //[_CentralCKFTruthSeededTrackUnfilteredAssociations_rec_]
   Int_t           _CentralCKFTruthSeededTrackUnfilteredAssociations_sim_;
   Int_t           _CentralCKFTruthSeededTrackUnfilteredAssociations_sim_index[kMax_CentralCKFTruthSeededTrackUnfilteredAssociations_sim];   //[_CentralCKFTruthSeededTrackUnfilteredAssociations_sim_]
   UInt_t          _CentralCKFTruthSeededTrackUnfilteredAssociations_sim_collectionID[kMax_CentralCKFTruthSeededTrackUnfilteredAssociations_sim];   //[_CentralCKFTruthSeededTrackUnfilteredAssociations_sim_]
   Int_t           CentralCKFTruthSeededTrajectories_;
   UInt_t          CentralCKFTruthSeededTrajectories_type[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_nStates[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_nMeasurements[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_nOutliers[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_nHoles[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_nSharedHits[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_measurementChi2_begin[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_measurementChi2_end[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_outlierChi2_begin[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_outlierChi2_end[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_trackParameters_begin[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_trackParameters_end[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_measurements_deprecated_begin[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_measurements_deprecated_end[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_outliers_deprecated_begin[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   UInt_t          CentralCKFTruthSeededTrajectories_outliers_deprecated_end[kMaxCentralCKFTruthSeededTrajectories];   //[CentralCKFTruthSeededTrajectories_]
   Int_t           _CentralCKFTruthSeededTrajectories_trackParameters_;
   Int_t           _CentralCKFTruthSeededTrajectories_trackParameters_index[kMax_CentralCKFTruthSeededTrajectories_trackParameters];   //[_CentralCKFTruthSeededTrajectories_trackParameters_]
   UInt_t          _CentralCKFTruthSeededTrajectories_trackParameters_collectionID[kMax_CentralCKFTruthSeededTrajectories_trackParameters];   //[_CentralCKFTruthSeededTrajectories_trackParameters_]
   Int_t           _CentralCKFTruthSeededTrajectories_measurements_deprecated_;
   Int_t           _CentralCKFTruthSeededTrajectories_measurements_deprecated_index[kMax_CentralCKFTruthSeededTrajectories_measurements_deprecated];   //[_CentralCKFTruthSeededTrajectories_measurements_deprecated_]
   UInt_t          _CentralCKFTruthSeededTrajectories_measurements_deprecated_collectionID[kMax_CentralCKFTruthSeededTrajectories_measurements_deprecated];   //[_CentralCKFTruthSeededTrajectories_measurements_deprecated_]
   Int_t           _CentralCKFTruthSeededTrajectories_outliers_deprecated_;
   Int_t           _CentralCKFTruthSeededTrajectories_outliers_deprecated_index[kMax_CentralCKFTruthSeededTrajectories_outliers_deprecated];   //[_CentralCKFTruthSeededTrajectories_outliers_deprecated_]
   UInt_t          _CentralCKFTruthSeededTrajectories_outliers_deprecated_collectionID[kMax_CentralCKFTruthSeededTrajectories_outliers_deprecated];   //[_CentralCKFTruthSeededTrajectories_outliers_deprecated_]
   Int_t           _CentralCKFTruthSeededTrajectories_seed_;
   Int_t           _CentralCKFTruthSeededTrajectories_seed_index[kMax_CentralCKFTruthSeededTrajectories_seed];   //[_CentralCKFTruthSeededTrajectories_seed_]
   UInt_t          _CentralCKFTruthSeededTrajectories_seed_collectionID[kMax_CentralCKFTruthSeededTrajectories_seed];   //[_CentralCKFTruthSeededTrajectories_seed_]
   std::vector<float>   *_CentralCKFTruthSeededTrajectories_measurementChi2;
   std::vector<float>   *_CentralCKFTruthSeededTrajectories_outlierChi2;
   Int_t           CentralCKFTruthSeededTrajectoriesUnfiltered_;
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_type[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_nStates[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_nMeasurements[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_nOutliers[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_nHoles[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_nSharedHits[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_begin[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_end[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_begin[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_end[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_begin[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_end[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_begin[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_end[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_begin[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   UInt_t          CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_end[kMaxCentralCKFTruthSeededTrajectoriesUnfiltered];   //[CentralCKFTruthSeededTrajectoriesUnfiltered_]
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_;
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_index[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_]
   UInt_t          _CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_collectionID[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_]
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_;
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_index[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_]
   UInt_t          _CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_collectionID[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_]
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_;
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_index[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_]
   UInt_t          _CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_collectionID[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_]
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_seed_;
   Int_t           _CentralCKFTruthSeededTrajectoriesUnfiltered_seed_index[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_seed];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_seed_]
   UInt_t          _CentralCKFTruthSeededTrajectoriesUnfiltered_seed_collectionID[kMax_CentralCKFTruthSeededTrajectoriesUnfiltered_seed];   //[_CentralCKFTruthSeededTrajectoriesUnfiltered_seed_]
   std::vector<float>   *_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2;
   std::vector<float>   *_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2;
   Int_t           CentralTrackerMeasurements_;
   ULong_t         CentralTrackerMeasurements_surface[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_loc_a[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_loc_b[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_time[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_covariance_xx[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_covariance_yy[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_covariance_zz[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_covariance_xy[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_covariance_xz[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Float_t         CentralTrackerMeasurements_covariance_yz[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   UInt_t          CentralTrackerMeasurements_weights_begin[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   UInt_t          CentralTrackerMeasurements_weights_end[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   UInt_t          CentralTrackerMeasurements_hits_begin[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   UInt_t          CentralTrackerMeasurements_hits_end[kMaxCentralTrackerMeasurements];   //[CentralTrackerMeasurements_]
   Int_t           _CentralTrackerMeasurements_hits_;
   Int_t           _CentralTrackerMeasurements_hits_index[kMax_CentralTrackerMeasurements_hits];   //[_CentralTrackerMeasurements_hits_]
   UInt_t          _CentralTrackerMeasurements_hits_collectionID[kMax_CentralTrackerMeasurements_hits];   //[_CentralTrackerMeasurements_hits_]
   std::vector<float>   *_CentralTrackerMeasurements_weights;
   Int_t           CentralTrackerTruthSeeds_objIdx_;
   Int_t           CentralTrackerTruthSeeds_objIdx_index[kMaxCentralTrackerTruthSeeds_objIdx];   //[CentralTrackerTruthSeeds_objIdx_]
   UInt_t          CentralTrackerTruthSeeds_objIdx_collectionID[kMaxCentralTrackerTruthSeeds_objIdx];   //[CentralTrackerTruthSeeds_objIdx_]
   Int_t           CentralTrackingRawHitAssociations_objIdx_;
   Int_t           CentralTrackingRawHitAssociations_objIdx_index[kMaxCentralTrackingRawHitAssociations_objIdx];   //[CentralTrackingRawHitAssociations_objIdx_]
   UInt_t          CentralTrackingRawHitAssociations_objIdx_collectionID[kMaxCentralTrackingRawHitAssociations_objIdx];   //[CentralTrackingRawHitAssociations_objIdx_]
   Int_t           CentralTrackingRecHits_objIdx_;
   Int_t           CentralTrackingRecHits_objIdx_index[kMaxCentralTrackingRecHits_objIdx];   //[CentralTrackingRecHits_objIdx_]
   UInt_t          CentralTrackingRecHits_objIdx_collectionID[kMaxCentralTrackingRecHits_objIdx];   //[CentralTrackingRecHits_objIdx_]
   Int_t           CentralTrackSeedingResults_;
   Int_t           CentralTrackSeedingResults_type[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   ULong_t         CentralTrackSeedingResults_surface[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_loc_a[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_loc_b[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_theta[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_phi[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_qOverP[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_time[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Int_t           CentralTrackSeedingResults_pdg[kMaxCentralTrackSeedingResults];   //[CentralTrackSeedingResults_]
   Float_t         CentralTrackSeedingResults_covariance_covariance[kMaxCentralTrackSeedingResults][21];   //[CentralTrackSeedingResults_]
   Int_t           CentralTrackSegments_;
   Float_t         CentralTrackSegments_length[kMaxCentralTrackSegments];   //[CentralTrackSegments_]
   Float_t         CentralTrackSegments_lengthError[kMaxCentralTrackSegments];   //[CentralTrackSegments_]
   UInt_t          CentralTrackSegments_points_begin[kMaxCentralTrackSegments];   //[CentralTrackSegments_]
   UInt_t          CentralTrackSegments_points_end[kMaxCentralTrackSegments];   //[CentralTrackSegments_]
   Int_t           _CentralTrackSegments_track_;
   Int_t           _CentralTrackSegments_track_index[kMax_CentralTrackSegments_track];   //[_CentralTrackSegments_track_]
   UInt_t          _CentralTrackSegments_track_collectionID[kMax_CentralTrackSegments_track];   //[_CentralTrackSegments_track_]
   Int_t           _CentralTrackSegments_points_;
   ULong_t         _CentralTrackSegments_points_surface[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   UInt_t          _CentralTrackSegments_points_system[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_position_x[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_position_y[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_position_z[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_positionError_xx[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_positionError_yy[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_positionError_zz[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_positionError_xy[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_positionError_xz[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_positionError_yz[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentum_x[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentum_y[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentum_z[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentumError_xx[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentumError_yy[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentumError_zz[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentumError_xy[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentumError_xz[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_momentumError_yz[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_time[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_timeError[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_theta[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_phi[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_directionError_xx[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_directionError_yy[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_directionError_xy[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_pathlength[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Float_t         _CentralTrackSegments_points_pathlengthError[kMax_CentralTrackSegments_points];   //[_CentralTrackSegments_points_]
   Int_t           CentralTrackVertices_;
   Int_t           CentralTrackVertices_type[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_chi2[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Int_t           CentralTrackVertices_ndf[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_position_x[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_position_y[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_position_z[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_position_t[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_xx[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_yy[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_zz[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_tt[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_xy[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_xz[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_xt[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_yz[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_yt[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Float_t         CentralTrackVertices_positionError_zt[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   UInt_t          CentralTrackVertices_associatedParticles_begin[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   UInt_t          CentralTrackVertices_associatedParticles_end[kMaxCentralTrackVertices];   //[CentralTrackVertices_]
   Int_t           _CentralTrackVertices_associatedParticles_;
   Int_t           _CentralTrackVertices_associatedParticles_index[kMax_CentralTrackVertices_associatedParticles];   //[_CentralTrackVertices_associatedParticles_]
   UInt_t          _CentralTrackVertices_associatedParticles_collectionID[kMax_CentralTrackVertices_associatedParticles];   //[_CentralTrackVertices_associatedParticles_]
   

   Int_t           ReconstructedChargedParticleAssociations_;
   UInt_t          ReconstructedChargedParticleAssociations_simID[kMaxReconstructedChargedParticleAssociations];   //[ReconstructedChargedParticleAssociations_]
   UInt_t          ReconstructedChargedParticleAssociations_recID[kMaxReconstructedChargedParticleAssociations];   //[ReconstructedChargedParticleAssociations_]
   Float_t         ReconstructedChargedParticleAssociations_weight[kMaxReconstructedChargedParticleAssociations];   //[ReconstructedChargedParticleAssociations_]
   Int_t           _ReconstructedChargedParticleAssociations_rec_;
   Int_t           _ReconstructedChargedParticleAssociations_rec_index[kMax_ReconstructedChargedParticleAssociations_rec];   //[_ReconstructedChargedParticleAssociations_rec_]
   UInt_t          _ReconstructedChargedParticleAssociations_rec_collectionID[kMax_ReconstructedChargedParticleAssociations_rec];   //[_ReconstructedChargedParticleAssociations_rec_]
   Int_t           _ReconstructedChargedParticleAssociations_sim_;
   Int_t           _ReconstructedChargedParticleAssociations_sim_index[kMax_ReconstructedChargedParticleAssociations_sim];   //[_ReconstructedChargedParticleAssociations_sim_]
   UInt_t          _ReconstructedChargedParticleAssociations_sim_collectionID[kMax_ReconstructedChargedParticleAssociations_sim];   //[_ReconstructedChargedParticleAssociations_sim_]
   Int_t           ReconstructedChargedParticles_;
   Int_t           ReconstructedChargedParticles_type[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_energy[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_momentum_x[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_momentum_y[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_momentum_z[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_referencePoint_x[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_referencePoint_y[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_referencePoint_z[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_charge[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_mass[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_goodnessOfPID[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_xx[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_yy[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_zz[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_tt[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_xy[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_xz[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_xt[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_yz[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_yt[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Float_t         ReconstructedChargedParticles_covMatrix_zt[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Int_t           ReconstructedChargedParticles_PDG[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_clusters_begin[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_clusters_end[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_tracks_begin[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_tracks_end[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_particles_begin[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_particles_end[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_particleIDs_begin[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   UInt_t          ReconstructedChargedParticles_particleIDs_end[kMaxReconstructedChargedParticles];   //[ReconstructedChargedParticles_]
   Int_t           _ReconstructedChargedParticles_clusters_;
   Int_t           _ReconstructedChargedParticles_clusters_index[kMax_ReconstructedChargedParticles_clusters];   //[_ReconstructedChargedParticles_clusters_]
   UInt_t          _ReconstructedChargedParticles_clusters_collectionID[kMax_ReconstructedChargedParticles_clusters];   //[_ReconstructedChargedParticles_clusters_]
   Int_t           _ReconstructedChargedParticles_tracks_;
   Int_t           _ReconstructedChargedParticles_tracks_index[kMax_ReconstructedChargedParticles_tracks];   //[_ReconstructedChargedParticles_tracks_]
   UInt_t          _ReconstructedChargedParticles_tracks_collectionID[kMax_ReconstructedChargedParticles_tracks];   //[_ReconstructedChargedParticles_tracks_]
   Int_t           _ReconstructedChargedParticles_particles_;
   Int_t           _ReconstructedChargedParticles_particles_index[kMax_ReconstructedChargedParticles_particles];   //[_ReconstructedChargedParticles_particles_]
   UInt_t          _ReconstructedChargedParticles_particles_collectionID[kMax_ReconstructedChargedParticles_particles];   //[_ReconstructedChargedParticles_particles_]
   Int_t           _ReconstructedChargedParticles_particleIDs_;
   Int_t           _ReconstructedChargedParticles_particleIDs_index[kMax_ReconstructedChargedParticles_particleIDs];   //[_ReconstructedChargedParticles_particleIDs_]
   UInt_t          _ReconstructedChargedParticles_particleIDs_collectionID[kMax_ReconstructedChargedParticles_particleIDs];   //[_ReconstructedChargedParticles_particleIDs_]
   Int_t           _ReconstructedChargedParticles_startVertex_;
   Int_t           _ReconstructedChargedParticles_startVertex_index[kMax_ReconstructedChargedParticles_startVertex];   //[_ReconstructedChargedParticles_startVertex_]
   UInt_t          _ReconstructedChargedParticles_startVertex_collectionID[kMax_ReconstructedChargedParticles_startVertex];   //[_ReconstructedChargedParticles_startVertex_]
   Int_t           _ReconstructedChargedParticles_particleIDUsed_;
   Int_t           _ReconstructedChargedParticles_particleIDUsed_index[kMax_ReconstructedChargedParticles_particleIDUsed];   //[_ReconstructedChargedParticles_particleIDUsed_]
   UInt_t          _ReconstructedChargedParticles_particleIDUsed_collectionID[kMax_ReconstructedChargedParticles_particleIDUsed];   //[_ReconstructedChargedParticles_particleIDUsed_]
   Int_t           ReconstructedChargedRealPIDParticleIDs_;
   Int_t           ReconstructedChargedRealPIDParticleIDs_type[kMaxReconstructedChargedRealPIDParticleIDs];   //[ReconstructedChargedRealPIDParticleIDs_]
   Int_t           ReconstructedChargedRealPIDParticleIDs_PDG[kMaxReconstructedChargedRealPIDParticleIDs];   //[ReconstructedChargedRealPIDParticleIDs_]
   Int_t           ReconstructedChargedRealPIDParticleIDs_algorithmType[kMaxReconstructedChargedRealPIDParticleIDs];   //[ReconstructedChargedRealPIDParticleIDs_]
   Float_t         ReconstructedChargedRealPIDParticleIDs_likelihood[kMaxReconstructedChargedRealPIDParticleIDs];   //[ReconstructedChargedRealPIDParticleIDs_]
   UInt_t          ReconstructedChargedRealPIDParticleIDs_parameters_begin[kMaxReconstructedChargedRealPIDParticleIDs];   //[ReconstructedChargedRealPIDParticleIDs_]
   UInt_t          ReconstructedChargedRealPIDParticleIDs_parameters_end[kMaxReconstructedChargedRealPIDParticleIDs];   //[ReconstructedChargedRealPIDParticleIDs_]
   Int_t           _ReconstructedChargedRealPIDParticleIDs_particle_;
   Int_t           _ReconstructedChargedRealPIDParticleIDs_particle_index[kMax_ReconstructedChargedRealPIDParticleIDs_particle];   //[_ReconstructedChargedRealPIDParticleIDs_particle_]
   UInt_t          _ReconstructedChargedRealPIDParticleIDs_particle_collectionID[kMax_ReconstructedChargedRealPIDParticleIDs_particle];   //[_ReconstructedChargedRealPIDParticleIDs_particle_]
   std::vector<float>   *_ReconstructedChargedRealPIDParticleIDs_parameters;
   Int_t           ReconstructedChargedRealPIDParticles_;
   Int_t           ReconstructedChargedRealPIDParticles_type[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_energy[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_momentum_x[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_momentum_y[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_momentum_z[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_referencePoint_x[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_referencePoint_y[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_referencePoint_z[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_charge[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_mass[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_goodnessOfPID[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_xx[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_yy[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_zz[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_tt[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_xy[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_xz[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_xt[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_yz[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_yt[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Float_t         ReconstructedChargedRealPIDParticles_covMatrix_zt[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Int_t           ReconstructedChargedRealPIDParticles_PDG[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_clusters_begin[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_clusters_end[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_tracks_begin[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_tracks_end[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_particles_begin[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_particles_end[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_particleIDs_begin[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   UInt_t          ReconstructedChargedRealPIDParticles_particleIDs_end[kMaxReconstructedChargedRealPIDParticles];   //[ReconstructedChargedRealPIDParticles_]
   Int_t           _ReconstructedChargedRealPIDParticles_clusters_;
   Int_t           _ReconstructedChargedRealPIDParticles_clusters_index[kMax_ReconstructedChargedRealPIDParticles_clusters];   //[_ReconstructedChargedRealPIDParticles_clusters_]
   UInt_t          _ReconstructedChargedRealPIDParticles_clusters_collectionID[kMax_ReconstructedChargedRealPIDParticles_clusters];   //[_ReconstructedChargedRealPIDParticles_clusters_]
   Int_t           _ReconstructedChargedRealPIDParticles_tracks_;
   Int_t           _ReconstructedChargedRealPIDParticles_tracks_index[kMax_ReconstructedChargedRealPIDParticles_tracks];   //[_ReconstructedChargedRealPIDParticles_tracks_]
   UInt_t          _ReconstructedChargedRealPIDParticles_tracks_collectionID[kMax_ReconstructedChargedRealPIDParticles_tracks];   //[_ReconstructedChargedRealPIDParticles_tracks_]
   Int_t           _ReconstructedChargedRealPIDParticles_particles_;
   Int_t           _ReconstructedChargedRealPIDParticles_particles_index[kMax_ReconstructedChargedRealPIDParticles_particles];   //[_ReconstructedChargedRealPIDParticles_particles_]
   UInt_t          _ReconstructedChargedRealPIDParticles_particles_collectionID[kMax_ReconstructedChargedRealPIDParticles_particles];   //[_ReconstructedChargedRealPIDParticles_particles_]
   Int_t           _ReconstructedChargedRealPIDParticles_particleIDs_;
   Int_t           _ReconstructedChargedRealPIDParticles_particleIDs_index[kMax_ReconstructedChargedRealPIDParticles_particleIDs];   //[_ReconstructedChargedRealPIDParticles_particleIDs_]
   UInt_t          _ReconstructedChargedRealPIDParticles_particleIDs_collectionID[kMax_ReconstructedChargedRealPIDParticles_particleIDs];   //[_ReconstructedChargedRealPIDParticles_particleIDs_]
   Int_t           _ReconstructedChargedRealPIDParticles_startVertex_;
   Int_t           _ReconstructedChargedRealPIDParticles_startVertex_index[kMax_ReconstructedChargedRealPIDParticles_startVertex];   //[_ReconstructedChargedRealPIDParticles_startVertex_]
   UInt_t          _ReconstructedChargedRealPIDParticles_startVertex_collectionID[kMax_ReconstructedChargedRealPIDParticles_startVertex];   //[_ReconstructedChargedRealPIDParticles_startVertex_]
   Int_t           _ReconstructedChargedRealPIDParticles_particleIDUsed_;
   Int_t           _ReconstructedChargedRealPIDParticles_particleIDUsed_index[kMax_ReconstructedChargedRealPIDParticles_particleIDUsed];   //[_ReconstructedChargedRealPIDParticles_particleIDUsed_]
   UInt_t          _ReconstructedChargedRealPIDParticles_particleIDUsed_collectionID[kMax_ReconstructedChargedRealPIDParticles_particleIDUsed];   //[_ReconstructedChargedRealPIDParticles_particleIDUsed_]
   Int_t           ReconstructedElectrons_objIdx_;
   Int_t           ReconstructedElectrons_objIdx_index[kMaxReconstructedElectrons_objIdx];   //[ReconstructedElectrons_objIdx_]
   UInt_t          ReconstructedElectrons_objIdx_collectionID[kMaxReconstructedElectrons_objIdx];   //[ReconstructedElectrons_objIdx_]


   std::vector<std::string>  *GPIntKeys;
   std::vector<std::vector<int> > *GPIntValues;
   std::vector<std::string>  *GPFloatKeys;
   std::vector<std::vector<float> > *GPFloatValues;
   std::vector<std::string>  *GPDoubleKeys;
   std::vector<std::vector<double> > *GPDoubleValues;
   std::vector<std::string>  *GPStringKeys;
   std::vector<std::vector<std::string> > *GPStringValues;


   // List of branches
   TBranch        *b_EventHeader_TS_;   //!
   TBranch        *b_EventHeader_TS_eventNumber;   //!
   TBranch        *b_EventHeader_TS_runNumber;   //!
   TBranch        *b_EventHeader_TS_timeStamp;   //!
   TBranch        *b_EventHeader_TS_weight;   //!
   TBranch        *b_EventHeader_TS_weights_begin;   //!
   TBranch        *b_EventHeader_TS_weights_end;   //!
   TBranch        *b__EventHeader_TS_weights;   //!

   TBranch        *b_MCParticles_;   //!
   TBranch        *b_MCParticles_PDG;   //!
   TBranch        *b_MCParticles_generatorStatus;   //!
   TBranch        *b_MCParticles_simulatorStatus;   //!
   TBranch        *b_MCParticles_charge;   //!
   TBranch        *b_MCParticles_time;   //!
   TBranch        *b_MCParticles_mass;   //!
   TBranch        *b_MCParticles_vertex_x;   //!
   TBranch        *b_MCParticles_vertex_y;   //!
   TBranch        *b_MCParticles_vertex_z;   //!
   TBranch        *b_MCParticles_endpoint_x;   //!
   TBranch        *b_MCParticles_endpoint_y;   //!
   TBranch        *b_MCParticles_endpoint_z;   //!
   TBranch        *b_MCParticles_momentum_x;   //!
   TBranch        *b_MCParticles_momentum_y;   //!
   TBranch        *b_MCParticles_momentum_z;   //!
   TBranch        *b_MCParticles_momentumAtEndpoint_x;   //!
   TBranch        *b_MCParticles_momentumAtEndpoint_y;   //!
   TBranch        *b_MCParticles_momentumAtEndpoint_z;   //!
   TBranch        *b_MCParticles_spin_x;   //!
   TBranch        *b_MCParticles_spin_y;   //!
   TBranch        *b_MCParticles_spin_z;   //!
   TBranch        *b_MCParticles_colorFlow_a;   //!
   TBranch        *b_MCParticles_colorFlow_b;   //!
   TBranch        *b_MCParticles_parents_begin;   //!
   TBranch        *b_MCParticles_parents_end;   //!
   TBranch        *b_MCParticles_daughters_begin;   //!
   TBranch        *b_MCParticles_daughters_end;   //!
   TBranch        *b__MCParticles_parents_;   //!
   TBranch        *b__MCParticles_parents_index;   //!
   TBranch        *b__MCParticles_parents_collectionID;   //!
   TBranch        *b__MCParticles_daughters_;   //!
   TBranch        *b__MCParticles_daughters_index;   //!
   TBranch        *b__MCParticles_daughters_collectionID;   //!


   TBranch        *b_CentralCKFTrackAssociations_;   //!
   TBranch        *b_CentralCKFTrackAssociations_simID;   //!
   TBranch        *b_CentralCKFTrackAssociations_recID;   //!
   TBranch        *b_CentralCKFTrackAssociations_weight;   //!
   TBranch        *b__CentralCKFTrackAssociations_rec_;   //!
   TBranch        *b__CentralCKFTrackAssociations_rec_index;   //!
   TBranch        *b__CentralCKFTrackAssociations_rec_collectionID;   //!
   TBranch        *b__CentralCKFTrackAssociations_sim_;   //!
   TBranch        *b__CentralCKFTrackAssociations_sim_index;   //!
   TBranch        *b__CentralCKFTrackAssociations_sim_collectionID;   //!
   TBranch        *b_CentralCKFTrackParameters_;   //!
   TBranch        *b_CentralCKFTrackParameters_type;   //!
   TBranch        *b_CentralCKFTrackParameters_surface;   //!
   TBranch        *b_CentralCKFTrackParameters_loc_a;   //!
   TBranch        *b_CentralCKFTrackParameters_loc_b;   //!
   TBranch        *b_CentralCKFTrackParameters_theta;   //!
   TBranch        *b_CentralCKFTrackParameters_phi;   //!
   TBranch        *b_CentralCKFTrackParameters_qOverP;   //!
   TBranch        *b_CentralCKFTrackParameters_time;   //!
   TBranch        *b_CentralCKFTrackParameters_pdg;   //!
   TBranch        *b_CentralCKFTrackParameters_covariance_covariance;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_type;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_surface;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_loc_a;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_loc_b;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_theta;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_phi;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_qOverP;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_time;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_pdg;   //!
   TBranch        *b_CentralCKFTrackParametersUnfiltered_covariance_covariance;   //!
   TBranch        *b_CentralCKFTracks_;   //!
   TBranch        *b_CentralCKFTracks_type;   //!
   TBranch        *b_CentralCKFTracks_position_x;   //!
   TBranch        *b_CentralCKFTracks_position_y;   //!
   TBranch        *b_CentralCKFTracks_position_z;   //!
   TBranch        *b_CentralCKFTracks_momentum_x;   //!
   TBranch        *b_CentralCKFTracks_momentum_y;   //!
   TBranch        *b_CentralCKFTracks_momentum_z;   //!
   TBranch        *b_CentralCKFTracks_positionMomentumCovariance_covariance;   //!
   TBranch        *b_CentralCKFTracks_time;   //!
   TBranch        *b_CentralCKFTracks_timeError;   //!
   TBranch        *b_CentralCKFTracks_charge;   //!
   TBranch        *b_CentralCKFTracks_chi2;   //!
   TBranch        *b_CentralCKFTracks_ndf;   //!
   TBranch        *b_CentralCKFTracks_pdg;   //!
   TBranch        *b_CentralCKFTracks_measurements_begin;   //!
   TBranch        *b_CentralCKFTracks_measurements_end;   //!
   TBranch        *b_CentralCKFTracks_tracks_begin;   //!
   TBranch        *b_CentralCKFTracks_tracks_end;   //!
   TBranch        *b__CentralCKFTracks_measurements_;   //!
   TBranch        *b__CentralCKFTracks_measurements_index;   //!
   TBranch        *b__CentralCKFTracks_measurements_collectionID;   //!
   TBranch        *b__CentralCKFTracks_tracks_;   //!
   TBranch        *b__CentralCKFTracks_tracks_index;   //!
   TBranch        *b__CentralCKFTracks_tracks_collectionID;   //!
   TBranch        *b__CentralCKFTracks_trajectory_;   //!
   TBranch        *b__CentralCKFTracks_trajectory_index;   //!
   TBranch        *b__CentralCKFTracks_trajectory_collectionID;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_type;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_position_x;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_position_y;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_position_z;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_momentum_x;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_momentum_y;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_momentum_z;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_positionMomentumCovariance_covariance;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_time;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_timeError;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_charge;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_chi2;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_ndf;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_pdg;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_measurements_begin;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_measurements_end;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_tracks_begin;   //!
   TBranch        *b_CentralCKFTracksUnfiltered_tracks_end;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_measurements_;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_measurements_index;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_measurements_collectionID;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_tracks_;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_tracks_index;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_tracks_collectionID;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_trajectory_;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_trajectory_index;   //!
   TBranch        *b__CentralCKFTracksUnfiltered_trajectory_collectionID;   //!
   TBranch        *b_CentralCKFTrackUnfilteredAssociations_;   //!
   TBranch        *b_CentralCKFTrackUnfilteredAssociations_simID;   //!
   TBranch        *b_CentralCKFTrackUnfilteredAssociations_recID;   //!
   TBranch        *b_CentralCKFTrackUnfilteredAssociations_weight;   //!
   TBranch        *b__CentralCKFTrackUnfilteredAssociations_rec_;   //!
   TBranch        *b__CentralCKFTrackUnfilteredAssociations_rec_index;   //!
   TBranch        *b__CentralCKFTrackUnfilteredAssociations_rec_collectionID;   //!
   TBranch        *b__CentralCKFTrackUnfilteredAssociations_sim_;   //!
   TBranch        *b__CentralCKFTrackUnfilteredAssociations_sim_index;   //!
   TBranch        *b__CentralCKFTrackUnfilteredAssociations_sim_collectionID;   //!
   TBranch        *b_CentralCKFTrajectories_;   //!
   TBranch        *b_CentralCKFTrajectories_type;   //!
   TBranch        *b_CentralCKFTrajectories_nStates;   //!
   TBranch        *b_CentralCKFTrajectories_nMeasurements;   //!
   TBranch        *b_CentralCKFTrajectories_nOutliers;   //!
   TBranch        *b_CentralCKFTrajectories_nHoles;   //!
   TBranch        *b_CentralCKFTrajectories_nSharedHits;   //!
   TBranch        *b_CentralCKFTrajectories_measurementChi2_begin;   //!
   TBranch        *b_CentralCKFTrajectories_measurementChi2_end;   //!
   TBranch        *b_CentralCKFTrajectories_outlierChi2_begin;   //!
   TBranch        *b_CentralCKFTrajectories_outlierChi2_end;   //!
   TBranch        *b_CentralCKFTrajectories_trackParameters_begin;   //!
   TBranch        *b_CentralCKFTrajectories_trackParameters_end;   //!
   TBranch        *b_CentralCKFTrajectories_measurements_deprecated_begin;   //!
   TBranch        *b_CentralCKFTrajectories_measurements_deprecated_end;   //!
   TBranch        *b_CentralCKFTrajectories_outliers_deprecated_begin;   //!
   TBranch        *b_CentralCKFTrajectories_outliers_deprecated_end;   //!
   TBranch        *b__CentralCKFTrajectories_trackParameters_;   //!
   TBranch        *b__CentralCKFTrajectories_trackParameters_index;   //!
   TBranch        *b__CentralCKFTrajectories_trackParameters_collectionID;   //!
   TBranch        *b__CentralCKFTrajectories_measurements_deprecated_;   //!
   TBranch        *b__CentralCKFTrajectories_measurements_deprecated_index;   //!
   TBranch        *b__CentralCKFTrajectories_measurements_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTrajectories_outliers_deprecated_;   //!
   TBranch        *b__CentralCKFTrajectories_outliers_deprecated_index;   //!
   TBranch        *b__CentralCKFTrajectories_outliers_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTrajectories_seed_;   //!
   TBranch        *b__CentralCKFTrajectories_seed_index;   //!
   TBranch        *b__CentralCKFTrajectories_seed_collectionID;   //!
   TBranch        *b__CentralCKFTrajectories_measurementChi2;   //!
   TBranch        *b__CentralCKFTrajectories_outlierChi2;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_type;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_nStates;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_nMeasurements;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_nOutliers;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_nHoles;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_nSharedHits;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_measurementChi2_begin;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_measurementChi2_end;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_outlierChi2_begin;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_outlierChi2_end;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_trackParameters_begin;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_trackParameters_end;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_begin;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_measurements_deprecated_end;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_begin;   //!
   TBranch        *b_CentralCKFTrajectoriesUnfiltered_outliers_deprecated_end;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_trackParameters_;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_trackParameters_index;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_trackParameters_collectionID;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_measurements_deprecated_;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_measurements_deprecated_index;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_measurements_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_outliers_deprecated_;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_outliers_deprecated_index;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_outliers_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_seed_;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_seed_index;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_seed_collectionID;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_measurementChi2;   //!
   TBranch        *b__CentralCKFTrajectoriesUnfiltered_outlierChi2;   //!
   TBranch        *b_CentralCKFTruthSeededTrackAssociations_;   //!
   TBranch        *b_CentralCKFTruthSeededTrackAssociations_simID;   //!
   TBranch        *b_CentralCKFTruthSeededTrackAssociations_recID;   //!
   TBranch        *b_CentralCKFTruthSeededTrackAssociations_weight;   //!
   TBranch        *b__CentralCKFTruthSeededTrackAssociations_rec_;   //!
   TBranch        *b__CentralCKFTruthSeededTrackAssociations_rec_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrackAssociations_rec_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrackAssociations_sim_;   //!
   TBranch        *b__CentralCKFTruthSeededTrackAssociations_sim_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrackAssociations_sim_collectionID;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_type;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_surface;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_loc_a;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_loc_b;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_theta;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_phi;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_qOverP;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_time;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_pdg;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParameters_covariance_covariance;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_type;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_surface;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_loc_a;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_loc_b;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_theta;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_phi;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_qOverP;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_time;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_pdg;   //!
   TBranch        *b_CentralCKFTruthSeededTrackParametersUnfiltered_covariance_covariance;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_type;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_position_x;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_position_y;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_position_z;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_momentum_x;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_momentum_y;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_momentum_z;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_positionMomentumCovariance_covariance;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_time;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_timeError;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_charge;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_chi2;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_ndf;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_pdg;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_measurements_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_measurements_end;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_tracks_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTracks_tracks_end;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_measurements_;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_measurements_index;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_measurements_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_tracks_;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_tracks_index;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_tracks_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_trajectory_;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_trajectory_index;   //!
   TBranch        *b__CentralCKFTruthSeededTracks_trajectory_collectionID;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_type;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_position_x;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_position_y;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_position_z;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_momentum_x;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_momentum_y;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_momentum_z;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_positionMomentumCovariance_covariance;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_time;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_timeError;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_charge;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_chi2;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_ndf;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_pdg;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_measurements_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_measurements_end;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_tracks_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTracksUnfiltered_tracks_end;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_measurements_;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_measurements_index;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_measurements_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_tracks_;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_tracks_index;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_tracks_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_trajectory_;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_trajectory_index;   //!
   TBranch        *b__CentralCKFTruthSeededTracksUnfiltered_trajectory_collectionID;   //!
   TBranch        *b_CentralCKFTruthSeededTrackUnfilteredAssociations_;   //!
   TBranch        *b_CentralCKFTruthSeededTrackUnfilteredAssociations_simID;   //!
   TBranch        *b_CentralCKFTruthSeededTrackUnfilteredAssociations_recID;   //!
   TBranch        *b_CentralCKFTruthSeededTrackUnfilteredAssociations_weight;   //!
   TBranch        *b__CentralCKFTruthSeededTrackUnfilteredAssociations_rec_;   //!
   TBranch        *b__CentralCKFTruthSeededTrackUnfilteredAssociations_rec_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrackUnfilteredAssociations_rec_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrackUnfilteredAssociations_sim_;   //!
   TBranch        *b__CentralCKFTruthSeededTrackUnfilteredAssociations_sim_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrackUnfilteredAssociations_sim_collectionID;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_type;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_nStates;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_nMeasurements;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_nOutliers;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_nHoles;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_nSharedHits;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_measurementChi2_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_measurementChi2_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_outlierChi2_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_outlierChi2_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_trackParameters_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_trackParameters_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_measurements_deprecated_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_measurements_deprecated_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_outliers_deprecated_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectories_outliers_deprecated_end;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_trackParameters_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_trackParameters_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_trackParameters_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_measurements_deprecated_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_measurements_deprecated_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_measurements_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_outliers_deprecated_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_outliers_deprecated_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_outliers_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_seed_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_seed_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_seed_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_measurementChi2;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectories_outlierChi2;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_type;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_nStates;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_nMeasurements;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_nOutliers;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_nHoles;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_nSharedHits;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_end;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_begin;   //!
   TBranch        *b_CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_end;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_trackParameters_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurements_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_outliers_deprecated_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_seed_;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_seed_index;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_seed_collectionID;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_measurementChi2;   //!
   TBranch        *b__CentralCKFTruthSeededTrajectoriesUnfiltered_outlierChi2;   //!
   TBranch        *b_CentralTrackerMeasurements_;   //!
   TBranch        *b_CentralTrackerMeasurements_surface;   //!
   TBranch        *b_CentralTrackerMeasurements_loc_a;   //!
   TBranch        *b_CentralTrackerMeasurements_loc_b;   //!
   TBranch        *b_CentralTrackerMeasurements_time;   //!
   TBranch        *b_CentralTrackerMeasurements_covariance_xx;   //!
   TBranch        *b_CentralTrackerMeasurements_covariance_yy;   //!
   TBranch        *b_CentralTrackerMeasurements_covariance_zz;   //!
   TBranch        *b_CentralTrackerMeasurements_covariance_xy;   //!
   TBranch        *b_CentralTrackerMeasurements_covariance_xz;   //!
   TBranch        *b_CentralTrackerMeasurements_covariance_yz;   //!
   TBranch        *b_CentralTrackerMeasurements_weights_begin;   //!
   TBranch        *b_CentralTrackerMeasurements_weights_end;   //!
   TBranch        *b_CentralTrackerMeasurements_hits_begin;   //!
   TBranch        *b_CentralTrackerMeasurements_hits_end;   //!
   TBranch        *b__CentralTrackerMeasurements_hits_;   //!
   TBranch        *b__CentralTrackerMeasurements_hits_index;   //!
   TBranch        *b__CentralTrackerMeasurements_hits_collectionID;   //!
   TBranch        *b__CentralTrackerMeasurements_weights;   //!
   TBranch        *b_CentralTrackerTruthSeeds_objIdx_;   //!
   TBranch        *b_CentralTrackerTruthSeeds_objIdx_index;   //!
   TBranch        *b_CentralTrackerTruthSeeds_objIdx_collectionID;   //!
   TBranch        *b_CentralTrackingRawHitAssociations_objIdx_;   //!
   TBranch        *b_CentralTrackingRawHitAssociations_objIdx_index;   //!
   TBranch        *b_CentralTrackingRawHitAssociations_objIdx_collectionID;   //!
   TBranch        *b_CentralTrackingRecHits_objIdx_;   //!
   TBranch        *b_CentralTrackingRecHits_objIdx_index;   //!
   TBranch        *b_CentralTrackingRecHits_objIdx_collectionID;   //!
   TBranch        *b_CentralTrackSeedingResults_;   //!
   TBranch        *b_CentralTrackSeedingResults_type;   //!
   TBranch        *b_CentralTrackSeedingResults_surface;   //!
   TBranch        *b_CentralTrackSeedingResults_loc_a;   //!
   TBranch        *b_CentralTrackSeedingResults_loc_b;   //!
   TBranch        *b_CentralTrackSeedingResults_theta;   //!
   TBranch        *b_CentralTrackSeedingResults_phi;   //!
   TBranch        *b_CentralTrackSeedingResults_qOverP;   //!
   TBranch        *b_CentralTrackSeedingResults_time;   //!
   TBranch        *b_CentralTrackSeedingResults_pdg;   //!
   TBranch        *b_CentralTrackSeedingResults_covariance_covariance;   //!
   TBranch        *b_CentralTrackSegments_;   //!
   TBranch        *b_CentralTrackSegments_length;   //!
   TBranch        *b_CentralTrackSegments_lengthError;   //!
   TBranch        *b_CentralTrackSegments_points_begin;   //!
   TBranch        *b_CentralTrackSegments_points_end;   //!
   TBranch        *b__CentralTrackSegments_track_;   //!
   TBranch        *b__CentralTrackSegments_track_index;   //!
   TBranch        *b__CentralTrackSegments_track_collectionID;   //!
   TBranch        *b__CentralTrackSegments_points_;   //!
   TBranch        *b__CentralTrackSegments_points_surface;   //!
   TBranch        *b__CentralTrackSegments_points_system;   //!
   TBranch        *b__CentralTrackSegments_points_position_x;   //!
   TBranch        *b__CentralTrackSegments_points_position_y;   //!
   TBranch        *b__CentralTrackSegments_points_position_z;   //!
   TBranch        *b__CentralTrackSegments_points_positionError_xx;   //!
   TBranch        *b__CentralTrackSegments_points_positionError_yy;   //!
   TBranch        *b__CentralTrackSegments_points_positionError_zz;   //!
   TBranch        *b__CentralTrackSegments_points_positionError_xy;   //!
   TBranch        *b__CentralTrackSegments_points_positionError_xz;   //!
   TBranch        *b__CentralTrackSegments_points_positionError_yz;   //!
   TBranch        *b__CentralTrackSegments_points_momentum_x;   //!
   TBranch        *b__CentralTrackSegments_points_momentum_y;   //!
   TBranch        *b__CentralTrackSegments_points_momentum_z;   //!
   TBranch        *b__CentralTrackSegments_points_momentumError_xx;   //!
   TBranch        *b__CentralTrackSegments_points_momentumError_yy;   //!
   TBranch        *b__CentralTrackSegments_points_momentumError_zz;   //!
   TBranch        *b__CentralTrackSegments_points_momentumError_xy;   //!
   TBranch        *b__CentralTrackSegments_points_momentumError_xz;   //!
   TBranch        *b__CentralTrackSegments_points_momentumError_yz;   //!
   TBranch        *b__CentralTrackSegments_points_time;   //!
   TBranch        *b__CentralTrackSegments_points_timeError;   //!
   TBranch        *b__CentralTrackSegments_points_theta;   //!
   TBranch        *b__CentralTrackSegments_points_phi;   //!
   TBranch        *b__CentralTrackSegments_points_directionError_xx;   //!
   TBranch        *b__CentralTrackSegments_points_directionError_yy;   //!
   TBranch        *b__CentralTrackSegments_points_directionError_xy;   //!
   TBranch        *b__CentralTrackSegments_points_pathlength;   //!
   TBranch        *b__CentralTrackSegments_points_pathlengthError;   //!
   TBranch        *b_CentralTrackVertices_;   //!
   TBranch        *b_CentralTrackVertices_type;   //!
   TBranch        *b_CentralTrackVertices_chi2;   //!
   TBranch        *b_CentralTrackVertices_ndf;   //!
   TBranch        *b_CentralTrackVertices_position_x;   //!
   TBranch        *b_CentralTrackVertices_position_y;   //!
   TBranch        *b_CentralTrackVertices_position_z;   //!
   TBranch        *b_CentralTrackVertices_position_t;   //!
   TBranch        *b_CentralTrackVertices_positionError_xx;   //!
   TBranch        *b_CentralTrackVertices_positionError_yy;   //!
   TBranch        *b_CentralTrackVertices_positionError_zz;   //!
   TBranch        *b_CentralTrackVertices_positionError_tt;   //!
   TBranch        *b_CentralTrackVertices_positionError_xy;   //!
   TBranch        *b_CentralTrackVertices_positionError_xz;   //!
   TBranch        *b_CentralTrackVertices_positionError_xt;   //!
   TBranch        *b_CentralTrackVertices_positionError_yz;   //!
   TBranch        *b_CentralTrackVertices_positionError_yt;   //!
   TBranch        *b_CentralTrackVertices_positionError_zt;   //!
   TBranch        *b_CentralTrackVertices_associatedParticles_begin;   //!
   TBranch        *b_CentralTrackVertices_associatedParticles_end;   //!
   TBranch        *b__CentralTrackVertices_associatedParticles_;   //!
   TBranch        *b__CentralTrackVertices_associatedParticles_index;   //!
   TBranch        *b__CentralTrackVertices_associatedParticles_collectionID;   //!

      TBranch        *b_ReconstructedChargedParticleAssociations_;   //!
   TBranch        *b_ReconstructedChargedParticleAssociations_simID;   //!
   TBranch        *b_ReconstructedChargedParticleAssociations_recID;   //!
   TBranch        *b_ReconstructedChargedParticleAssociations_weight;   //!
   TBranch        *b__ReconstructedChargedParticleAssociations_rec_;   //!
   TBranch        *b__ReconstructedChargedParticleAssociations_rec_index;   //!
   TBranch        *b__ReconstructedChargedParticleAssociations_rec_collectionID;   //!
   TBranch        *b__ReconstructedChargedParticleAssociations_sim_;   //!
   TBranch        *b__ReconstructedChargedParticleAssociations_sim_index;   //!
   TBranch        *b__ReconstructedChargedParticleAssociations_sim_collectionID;   //!
   TBranch        *b_ReconstructedChargedParticles_;   //!
   TBranch        *b_ReconstructedChargedParticles_type;   //!
   TBranch        *b_ReconstructedChargedParticles_energy;   //!
   TBranch        *b_ReconstructedChargedParticles_momentum_x;   //!
   TBranch        *b_ReconstructedChargedParticles_momentum_y;   //!
   TBranch        *b_ReconstructedChargedParticles_momentum_z;   //!
   TBranch        *b_ReconstructedChargedParticles_referencePoint_x;   //!
   TBranch        *b_ReconstructedChargedParticles_referencePoint_y;   //!
   TBranch        *b_ReconstructedChargedParticles_referencePoint_z;   //!
   TBranch        *b_ReconstructedChargedParticles_charge;   //!
   TBranch        *b_ReconstructedChargedParticles_mass;   //!
   TBranch        *b_ReconstructedChargedParticles_goodnessOfPID;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_xx;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_yy;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_zz;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_tt;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_xy;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_xz;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_xt;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_yz;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_yt;   //!
   TBranch        *b_ReconstructedChargedParticles_covMatrix_zt;   //!
   TBranch        *b_ReconstructedChargedParticles_PDG;   //!
   TBranch        *b_ReconstructedChargedParticles_clusters_begin;   //!
   TBranch        *b_ReconstructedChargedParticles_clusters_end;   //!
   TBranch        *b_ReconstructedChargedParticles_tracks_begin;   //!
   TBranch        *b_ReconstructedChargedParticles_tracks_end;   //!
   TBranch        *b_ReconstructedChargedParticles_particles_begin;   //!
   TBranch        *b_ReconstructedChargedParticles_particles_end;   //!
   TBranch        *b_ReconstructedChargedParticles_particleIDs_begin;   //!
   TBranch        *b_ReconstructedChargedParticles_particleIDs_end;   //!
   TBranch        *b__ReconstructedChargedParticles_clusters_;   //!
   TBranch        *b__ReconstructedChargedParticles_clusters_index;   //!
   TBranch        *b__ReconstructedChargedParticles_clusters_collectionID;   //!
   TBranch        *b__ReconstructedChargedParticles_tracks_;   //!
   TBranch        *b__ReconstructedChargedParticles_tracks_index;   //!
   TBranch        *b__ReconstructedChargedParticles_tracks_collectionID;   //!
   TBranch        *b__ReconstructedChargedParticles_particles_;   //!
   TBranch        *b__ReconstructedChargedParticles_particles_index;   //!
   TBranch        *b__ReconstructedChargedParticles_particles_collectionID;   //!
   TBranch        *b__ReconstructedChargedParticles_particleIDs_;   //!
   TBranch        *b__ReconstructedChargedParticles_particleIDs_index;   //!
   TBranch        *b__ReconstructedChargedParticles_particleIDs_collectionID;   //!
   TBranch        *b__ReconstructedChargedParticles_startVertex_;   //!
   TBranch        *b__ReconstructedChargedParticles_startVertex_index;   //!
   TBranch        *b__ReconstructedChargedParticles_startVertex_collectionID;   //!
   TBranch        *b__ReconstructedChargedParticles_particleIDUsed_;   //!
   TBranch        *b__ReconstructedChargedParticles_particleIDUsed_index;   //!
   TBranch        *b__ReconstructedChargedParticles_particleIDUsed_collectionID;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_type;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_PDG;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_algorithmType;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_likelihood;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_parameters_begin;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticleIDs_parameters_end;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticleIDs_particle_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticleIDs_particle_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticleIDs_particle_collectionID;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticleIDs_parameters;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_type;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_energy;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_momentum_x;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_momentum_y;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_momentum_z;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_referencePoint_x;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_referencePoint_y;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_referencePoint_z;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_charge;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_mass;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_goodnessOfPID;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_xx;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_yy;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_zz;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_tt;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_xy;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_xz;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_xt;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_yz;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_yt;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_covMatrix_zt;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_PDG;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_clusters_begin;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_clusters_end;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_tracks_begin;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_tracks_end;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_particles_begin;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_particles_end;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_particleIDs_begin;   //!
   TBranch        *b_ReconstructedChargedRealPIDParticles_particleIDs_end;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_clusters_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_clusters_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_clusters_collectionID;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_tracks_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_tracks_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_tracks_collectionID;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particles_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particles_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particles_collectionID;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particleIDs_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particleIDs_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particleIDs_collectionID;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_startVertex_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_startVertex_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_startVertex_collectionID;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particleIDUsed_;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particleIDUsed_index;   //!
   TBranch        *b__ReconstructedChargedRealPIDParticles_particleIDUsed_collectionID;   //!
   TBranch        *b_ReconstructedElectrons_objIdx_;   //!
   TBranch        *b_ReconstructedElectrons_objIdx_index;   //!
   TBranch        *b_ReconstructedElectrons_objIdx_collectionID;   //!


   TBranch        *b_GPIntKeys;   //!
   TBranch        *b_GPIntValues;   //!
   TBranch        *b_GPFloatKeys;   //!
   TBranch        *b_GPFloatValues;   //!
   TBranch        *b_GPDoubleKeys;   //!
   TBranch        *b_GPDoubleValues;   //!
   TBranch        *b_GPStringKeys;   //!
   TBranch        *b_GPStringValues;   //!

   // public member valuables
   std::vector<Int_t> m_vTargetEvents;
   Int_t m_pubEvNum = 0;



   // black, blue, red, green, violet, orange, light blue, light green, dark violet, brown, very light blue, 
   // yellow green, week red, dark blue, week green, dark cyan, dark orange, 
   Int_t m_myHistColors[18] = {4, 600, 632, 419, 880, 807, 867, 909, 814, 874, 635, 870, 824, 625, 602, 417, 434, 802}; // colors for histograms
   
   

   // histograms as output
   TH1D* m_hTrackChi2;
   TH1D* m_hVertexChi2;
   TH1D* m_hVertexPosiZ;


   TH1D* m_hPtDist_MC;
   TH1D* m_hPtDist_Reco;

   TH2D* m_hPtCompMCVsReco;
   TH1D* m_hPtReso;

   TH1D* m_hTrackPurity;
   TH1D* m_hTotalTrackPurity;
   TH1D* m_hTrkEfficiency;

   // == member functions == // own function
   void HistInit();
   void ResetValuesForEachEvent();
   void WriteHists();
   
   bool bInitialLoop = true;
   std::vector<std::vector<unsigned int > > m_vOrigHitId;

   std::vector<std::vector<unsigned int > > m_vSameTSHitId;
   std::vector<std::vector<unsigned int > > m_vOutputHitContainer;


   
   int checkCount = 0;
   
};


#endif

// #ifndef recoQA_cxx
// #define recoQA_cxx


// #endif // #ifdef recoQA_cxx
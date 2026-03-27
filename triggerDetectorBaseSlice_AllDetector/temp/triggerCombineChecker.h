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

#ifndef triggerCombineChecker_h
#define triggerCombineChecker_h

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

#include "SimTrackerHitKuma.h"


class triggerCombineChecker {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any. 
   triggerCombineChecker(TTree *tree=0, std::string iFileName="", std::string oFileName="");
   virtual ~triggerCombineChecker();
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
   static constexpr Int_t kMaxEventHeader = 9999999;

   static constexpr Int_t kMaxBackwardMPGDEndcapRecHits = 9999999;
   static constexpr Int_t kMaxForwardMPGDEndcapRecHits = 9999999;

   static constexpr Int_t kMaxMCParticles = 9999999;
   static constexpr Int_t kMax_MCParticles_parents = 9999999;
   static constexpr Int_t kMax_MCParticles_daughters = 9999999;

   static constexpr Int_t kMaxMPGDBarrelRecHits = 9999999;
   static constexpr Int_t kMaxOuterMPGDBarrelRecHits = 9999999;
   static constexpr Int_t kMaxSiBarrelTrackerRecHits = 9999999;
   static constexpr Int_t kMaxSiBarrelVertexRecHits = 9999999;
   static constexpr Int_t kMaxSiEndcapTrackerRecHits = 9999999;
   static constexpr Int_t kMaxTOFBarrelRecHits = 9999999;
   static constexpr Int_t kMaxTOFEndcapRecHits = 9999999;


      static constexpr Int_t kMaxB0ECalClusters = 99999;
   static constexpr Int_t kMax_B0ECalClusters_clusters = 99999;
   static constexpr Int_t kMax_B0ECalClusters_hits = 99999;
   static constexpr Int_t kMax_B0ECalClusters_particleIDs = 99999;
   static constexpr Int_t kMaxB0ECalRecHits = 99999;
   static constexpr Int_t kMax_B0ECalRecHits_rawHit = 99999;

   static constexpr Int_t kMaxB0TrackerRecHits = 99999;

   static constexpr Int_t kMaxDIRCRawHits = 99999;

   static constexpr Int_t kMaxDRICHRawHits = 99999;

   static constexpr Int_t kMaxEcalBarrelClusters = 99999;
   static constexpr Int_t kMax_EcalBarrelClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalBarrelClusters_hits = 99999;

   static constexpr Int_t kMaxEcalBarrelImagingClusters = 99999;
   static constexpr Int_t kMax_EcalBarrelImagingClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalBarrelImagingClusters_hits = 99999;

   static constexpr Int_t kMaxEcalBarrelImagingRecHits = 99999;
   static constexpr Int_t kMax_EcalBarrelImagingRecHits_rawHit = 99999;

   static constexpr Int_t kMaxEcalBarrelScFiClusters = 99999;
   static constexpr Int_t kMax_EcalBarrelScFiClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalBarrelScFiClusters_hits = 99999;
   static constexpr Int_t kMaxEcalBarrelScFiRecHits = 99999;
   static constexpr Int_t kMax_EcalBarrelScFiRecHits_rawHit = 99999;

   static constexpr Int_t kMaxEcalEndcapNClusters = 99999;
   static constexpr Int_t kMax_EcalEndcapNClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalEndcapNClusters_hits = 99999;
   static constexpr Int_t kMaxEcalEndcapNRecHits = 99999;
   static constexpr Int_t kMax_EcalEndcapNRecHits_rawHit = 99999;

   static constexpr Int_t kMaxEcalEndcapPClusters = 99999;
   static constexpr Int_t kMax_EcalEndcapPClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalEndcapPClusters_hits = 99999;
   static constexpr Int_t kMaxEcalEndcapPRecHits = 99999;
   static constexpr Int_t kMax_EcalEndcapPRecHits_rawHit = 99999;

   static constexpr Int_t kMaxEcalFarForwardZDCClusters = 99999;
   static constexpr Int_t kMax_EcalFarForwardZDCClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalFarForwardZDCClusters_hits = 99999;
   static constexpr Int_t kMaxEcalFarForwardZDCRecHits = 99999;
   static constexpr Int_t kMax_EcalFarForwardZDCRecHits_rawHit = 99999;

   static constexpr Int_t kMaxEcalLumiSpecClusters = 99999;
   static constexpr Int_t kMax_EcalLumiSpecClusters_clusters = 99999;
   static constexpr Int_t kMax_EcalLumiSpecClusters_hits = 99999;
   static constexpr Int_t kMaxEcalLumiSpecRecHits = 99999;
   static constexpr Int_t kMax_EcalLumiSpecRecHits_rawHit = 99999;

   static constexpr Int_t kMaxForwardOffMRecParticles = 99999;
   static constexpr Int_t kMax_ForwardOffMRecParticles_clusters = 99999;
   static constexpr Int_t kMaxForwardOffMTrackerRecHits = 99999;
   static constexpr Int_t kMax_ForwardOffMTrackerRecHits_rawHit = 99999;

   static constexpr Int_t kMaxForwardRomanPotRecHits = 99999;
   static constexpr Int_t kMax_ForwardRomanPotRecHits_rawHit = 99999;


   static constexpr Int_t kMaxLFHCALClusters = 99999;
   static constexpr Int_t kMax_LFHCALClusters_clusters = 99999;
   static constexpr Int_t kMax_LFHCALClusters_hits = 99999;
   static constexpr Int_t kMaxLFHCALRecHits = 99999;
   static constexpr Int_t kMax_LFHCALRecHits_rawHit = 99999;


   // Declaration of leaf types
   Int_t           EventHeader_;
   Int_t           EventHeader_eventNumber[kMaxEventHeader];   //[EventHeader_]
   Int_t           EventHeader_runNumber[kMaxEventHeader];   //[EventHeader_]
   ULong_t         EventHeader_timeStamp[kMaxEventHeader];   //[EventHeader_]
   Double_t        EventHeader_weight[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_begin[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_end[kMaxEventHeader];   //[EventHeader_]
   
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

   
   Int_t           BackwardMPGDEndcapRecHits_;
   ULong_t         BackwardMPGDEndcapRecHits_cellID[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_position_x[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_position_y[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_position_z[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_positionError_xx[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_positionError_yy[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_positionError_zz[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_time[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_timeError[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_edep[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_edepError[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]

   Int_t           ForwardMPGDEndcapRecHits_;
   ULong_t         ForwardMPGDEndcapRecHits_cellID[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_position_x[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_position_y[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_position_z[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_positionError_xx[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_positionError_yy[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_positionError_zz[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_time[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_timeError[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_edep[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_edepError[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   
   
   Int_t           MPGDBarrelRecHits_;
   ULong_t         MPGDBarrelRecHits_cellID[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_position_x[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_position_y[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_position_z[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_positionError_xx[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_positionError_yy[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_positionError_zz[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_time[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_timeError[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_edep[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_edepError[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   
   Int_t           OuterMPGDBarrelRecHits_;
   ULong_t         OuterMPGDBarrelRecHits_cellID[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_position_x[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_position_y[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_position_z[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_positionError_xx[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_positionError_yy[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_positionError_zz[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_time[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_timeError[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_edep[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_edepError[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]

   Int_t           SiBarrelTrackerRecHits_;
   ULong_t         SiBarrelTrackerRecHits_cellID[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_position_x[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_position_y[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_position_z[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_positionError_xx[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_positionError_yy[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_positionError_zz[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_time[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_timeError[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_edep[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_edepError[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   
   Int_t           SiBarrelVertexRecHits_;
   ULong_t         SiBarrelVertexRecHits_cellID[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_position_x[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_position_y[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_position_z[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_positionError_xx[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_positionError_yy[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_positionError_zz[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_time[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_timeError[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_edep[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_edepError[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   
   Int_t           SiEndcapTrackerRecHits_;
   ULong_t         SiEndcapTrackerRecHits_cellID[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_position_x[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_position_y[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_position_z[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_positionError_xx[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_positionError_yy[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_positionError_zz[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_time[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_timeError[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_edep[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_edepError[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   
   Int_t           TOFBarrelRecHits_;
   ULong_t         TOFBarrelRecHits_cellID[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_position_x[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_position_y[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_position_z[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_positionError_xx[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_positionError_yy[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_positionError_zz[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_time[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_timeError[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_edep[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_edepError[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   
   Int_t           TOFEndcapRecHits_;
   ULong_t         TOFEndcapRecHits_cellID[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_position_x[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_position_y[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_position_z[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_positionError_xx[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_positionError_yy[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_positionError_zz[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_time[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_timeError[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_edep[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_edepError[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   

   Int_t           B0TrackerRecHits_;
   ULong_t         B0TrackerRecHits_cellID[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_position_x[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_position_y[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_position_z[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_positionError_xx[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_positionError_yy[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_positionError_zz[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_time[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_timeError[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_edep[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_edepError[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   
   Int_t           B0ECalClusters_;
   Int_t           B0ECalClusters_type[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_energy[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_energyError[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_time[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_timeError[kMaxB0ECalClusters];   //[B0ECalClusters_]
   UInt_t          B0ECalClusters_nhits[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_position_x[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_position_y[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_position_z[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_xx[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_yy[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_zz[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_xy[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_xz[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_yz[kMaxB0ECalClusters];   //[B0ECalClusters_]

   Int_t           B0ECalRecHits_;
   ULong_t         B0ECalRecHits_cellID[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_energy[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_energyError[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_time[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_timeError[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_x[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_y[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_z[kMaxB0ECalRecHits];   //[B0ECalRecHits_]

   Int_t           DIRCRawHits_;
   ULong_t         DIRCRawHits_cellID[kMaxDIRCRawHits];   //[DIRCRawHits_]
   Int_t           DIRCRawHits_charge[kMaxDIRCRawHits];   //[DIRCRawHits_]
   Int_t           DIRCRawHits_timeStamp[kMaxDIRCRawHits];   //[DIRCRawHits_]

   Int_t           DRICHRawHits_;
   ULong_t         DRICHRawHits_cellID[kMaxDRICHRawHits];   //[DRICHRawHits_]
   Int_t           DRICHRawHits_charge[kMaxDRICHRawHits];   //[DRICHRawHits_]
   Int_t           DRICHRawHits_timeStamp[kMaxDRICHRawHits];   //[DRICHRawHits_]


   Int_t           EcalBarrelClusters_;
   Int_t           EcalBarrelClusters_type[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_energy[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_energyError[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_time[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_timeError[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   UInt_t          EcalBarrelClusters_nhits[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_position_x[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_position_y[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_position_z[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_xx[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_yy[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_zz[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_xy[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_xz[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_yz[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]

   Int_t           EcalBarrelImagingClusters_;
   Int_t           EcalBarrelImagingClusters_type[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_energy[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_energyError[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_time[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_timeError[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   UInt_t          EcalBarrelImagingClusters_nhits[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_position_x[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_position_y[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_position_z[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_xx[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_yy[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_zz[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_xy[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_xz[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_yz[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   
   Int_t           EcalBarrelImagingRecHits_;
   ULong_t         EcalBarrelImagingRecHits_cellID[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_energy[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_energyError[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_time[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_timeError[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_x[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_y[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_z[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]

   Int_t           EcalBarrelScFiClusters_;
   Int_t           EcalBarrelScFiClusters_type[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_energy[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_energyError[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_time[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_timeError[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   UInt_t          EcalBarrelScFiClusters_nhits[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_position_x[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_position_y[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_position_z[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_xx[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_yy[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_zz[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_xy[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_xz[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_yz[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]

   Int_t           EcalBarrelScFiRecHits_;
   ULong_t         EcalBarrelScFiRecHits_cellID[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_energy[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_energyError[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_time[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_timeError[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_x[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_y[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_z[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]


   Int_t           EcalEndcapNClusters_;
   Int_t           EcalEndcapNClusters_type[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_energy[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_energyError[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_time[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_timeError[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   UInt_t          EcalEndcapNClusters_nhits[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_position_x[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_position_y[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_position_z[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_xx[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_yy[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_zz[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_xy[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_xz[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_yz[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]

   Int_t           EcalEndcapNRecHits_;
   ULong_t         EcalEndcapNRecHits_cellID[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_energy[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_energyError[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_time[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_timeError[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_x[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_y[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_z[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]

   Int_t           EcalEndcapPClusters_;
   Int_t           EcalEndcapPClusters_type[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_energy[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_energyError[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_time[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_timeError[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   UInt_t          EcalEndcapPClusters_nhits[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_position_x[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_position_y[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_position_z[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_xx[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_yy[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_zz[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_xy[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_xz[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_yz[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]

   Int_t           EcalEndcapPRecHits_;
   ULong_t         EcalEndcapPRecHits_cellID[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_energy[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_energyError[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_time[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_timeError[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_x[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_y[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_z[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]


   Int_t           EcalFarForwardZDCClusters_;
   Int_t           EcalFarForwardZDCClusters_type[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_energy[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_energyError[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_time[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_timeError[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   UInt_t          EcalFarForwardZDCClusters_nhits[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_position_x[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_position_y[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_position_z[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_xx[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_yy[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_zz[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_xy[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_xz[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_yz[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]

   Int_t           EcalFarForwardZDCRecHits_;
   ULong_t         EcalFarForwardZDCRecHits_cellID[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_energy[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_energyError[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_time[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_timeError[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_x[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_y[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_z[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]

   Int_t           EcalLumiSpecClusters_;
   Int_t           EcalLumiSpecClusters_type[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_energy[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_energyError[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_time[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_timeError[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   UInt_t          EcalLumiSpecClusters_nhits[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_position_x[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_position_y[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_position_z[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_xx[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_yy[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_zz[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_xy[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_xz[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_yz[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]

   Int_t           EcalLumiSpecRecHits_;
   ULong_t         EcalLumiSpecRecHits_cellID[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_energy[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_energyError[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_time[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_timeError[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_x[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_y[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_z[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]

   Int_t           ForwardOffMTrackerRecHits_;
   ULong_t         ForwardOffMTrackerRecHits_cellID[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_position_x[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_position_y[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_position_z[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_positionError_xx[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_positionError_yy[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_positionError_zz[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_time[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_timeError[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_edep[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_edepError[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]


   Int_t           ForwardRomanPotRecHits_;
   ULong_t         ForwardRomanPotRecHits_cellID[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_position_x[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_position_y[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_position_z[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_positionError_xx[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_positionError_yy[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_positionError_zz[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_time[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_timeError[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_edep[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_edepError[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]

   Int_t           LFHCALClusters_;
   Int_t           LFHCALClusters_type[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_energy[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_energyError[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_time[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_timeError[kMaxLFHCALClusters];   //[LFHCALClusters_]
   UInt_t          LFHCALClusters_nhits[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_position_x[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_position_y[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_position_z[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_xx[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_yy[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_zz[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_xy[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_xz[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_yz[kMaxLFHCALClusters];   //[LFHCALClusters_]

   Int_t           LFHCALRecHits_;
   ULong_t         LFHCALRecHits_cellID[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_energy[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_energyError[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_time[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_timeError[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_x[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_y[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_z[kMaxLFHCALRecHits];   //[LFHCALRecHits_]




   std::vector<std::string>  *GPIntKeys;
   std::vector<std::vector<int> > *GPIntValues;
   std::vector<std::string>  *GPFloatKeys;
   std::vector<std::vector<float> > *GPFloatValues;
   std::vector<std::string>  *GPDoubleKeys;
   std::vector<std::vector<double> > *GPDoubleValues;
   std::vector<std::string>  *GPStringKeys;
   std::vector<std::vector<std::string> > *GPStringValues;


   // List of branches
   TBranch        *b_EventHeader_;   //!
   TBranch        *b_EventHeader_eventNumber;   //!
   TBranch        *b_EventHeader_runNumber;   //!
   TBranch        *b_EventHeader_timeStamp;   //!
   TBranch        *b_EventHeader_weight;   //!
   TBranch        *b_EventHeader_weights_begin;   //!
   TBranch        *b_EventHeader_weights_end;   //!

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


   TBranch        *b_BackwardMPGDEndcapRecHits_;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_cellID;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_position_x;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_position_y;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_position_z;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_positionError_xx;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_positionError_yy;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_positionError_zz;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_time;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_timeError;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_edep;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_edepError;   //!
   
   TBranch        *b_ForwardMPGDEndcapRecHits_;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_cellID;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_position_x;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_position_y;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_position_z;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_positionError_xx;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_positionError_yy;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_positionError_zz;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_time;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_timeError;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_edep;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_edepError;   //!
   
   TBranch        *b_MPGDBarrelRecHits_;   //!
   TBranch        *b_MPGDBarrelRecHits_cellID;   //!
   TBranch        *b_MPGDBarrelRecHits_position_x;   //!
   TBranch        *b_MPGDBarrelRecHits_position_y;   //!
   TBranch        *b_MPGDBarrelRecHits_position_z;   //!
   TBranch        *b_MPGDBarrelRecHits_positionError_xx;   //!
   TBranch        *b_MPGDBarrelRecHits_positionError_yy;   //!
   TBranch        *b_MPGDBarrelRecHits_positionError_zz;   //!
   TBranch        *b_MPGDBarrelRecHits_time;   //!
   TBranch        *b_MPGDBarrelRecHits_timeError;   //!
   TBranch        *b_MPGDBarrelRecHits_edep;   //!
   TBranch        *b_MPGDBarrelRecHits_edepError;   //!
   
   TBranch        *b_OuterMPGDBarrelRecHits_;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_cellID;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_position_x;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_position_y;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_position_z;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_positionError_xx;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_positionError_yy;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_positionError_zz;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_time;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_timeError;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_edep;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_edepError;   //!

   TBranch        *b_SiBarrelTrackerRecHits_;   //!
   TBranch        *b_SiBarrelTrackerRecHits_cellID;   //!
   TBranch        *b_SiBarrelTrackerRecHits_position_x;   //!
   TBranch        *b_SiBarrelTrackerRecHits_position_y;   //!
   TBranch        *b_SiBarrelTrackerRecHits_position_z;   //!
   TBranch        *b_SiBarrelTrackerRecHits_positionError_xx;   //!
   TBranch        *b_SiBarrelTrackerRecHits_positionError_yy;   //!
   TBranch        *b_SiBarrelTrackerRecHits_positionError_zz;   //!
   TBranch        *b_SiBarrelTrackerRecHits_time;   //!
   TBranch        *b_SiBarrelTrackerRecHits_timeError;   //!
   TBranch        *b_SiBarrelTrackerRecHits_edep;   //!
   TBranch        *b_SiBarrelTrackerRecHits_edepError;   //!
   
   TBranch        *b_SiBarrelVertexRecHits_;   //!
   TBranch        *b_SiBarrelVertexRecHits_cellID;   //!
   TBranch        *b_SiBarrelVertexRecHits_position_x;   //!
   TBranch        *b_SiBarrelVertexRecHits_position_y;   //!
   TBranch        *b_SiBarrelVertexRecHits_position_z;   //!
   TBranch        *b_SiBarrelVertexRecHits_positionError_xx;   //!
   TBranch        *b_SiBarrelVertexRecHits_positionError_yy;   //!
   TBranch        *b_SiBarrelVertexRecHits_positionError_zz;   //!
   TBranch        *b_SiBarrelVertexRecHits_time;   //!
   TBranch        *b_SiBarrelVertexRecHits_timeError;   //!
   TBranch        *b_SiBarrelVertexRecHits_edep;   //!
   TBranch        *b_SiBarrelVertexRecHits_edepError;   //!
   
   TBranch        *b_SiEndcapTrackerRecHits_;   //!
   TBranch        *b_SiEndcapTrackerRecHits_cellID;   //!
   TBranch        *b_SiEndcapTrackerRecHits_position_x;   //!
   TBranch        *b_SiEndcapTrackerRecHits_position_y;   //!
   TBranch        *b_SiEndcapTrackerRecHits_position_z;   //!
   TBranch        *b_SiEndcapTrackerRecHits_positionError_xx;   //!
   TBranch        *b_SiEndcapTrackerRecHits_positionError_yy;   //!
   TBranch        *b_SiEndcapTrackerRecHits_positionError_zz;   //!
   TBranch        *b_SiEndcapTrackerRecHits_time;   //!
   TBranch        *b_SiEndcapTrackerRecHits_timeError;   //!
   TBranch        *b_SiEndcapTrackerRecHits_edep;   //!
   TBranch        *b_SiEndcapTrackerRecHits_edepError;   //!

   TBranch        *b_TOFBarrelRecHits_;   //!
   TBranch        *b_TOFBarrelRecHits_cellID;   //!
   TBranch        *b_TOFBarrelRecHits_position_x;   //!
   TBranch        *b_TOFBarrelRecHits_position_y;   //!
   TBranch        *b_TOFBarrelRecHits_position_z;   //!
   TBranch        *b_TOFBarrelRecHits_positionError_xx;   //!
   TBranch        *b_TOFBarrelRecHits_positionError_yy;   //!
   TBranch        *b_TOFBarrelRecHits_positionError_zz;   //!
   TBranch        *b_TOFBarrelRecHits_time;   //!
   TBranch        *b_TOFBarrelRecHits_timeError;   //!
   TBranch        *b_TOFBarrelRecHits_edep;   //!
   TBranch        *b_TOFBarrelRecHits_edepError;   //!
   
   TBranch        *b_TOFEndcapRecHits_;   //!
   TBranch        *b_TOFEndcapRecHits_cellID;   //!
   TBranch        *b_TOFEndcapRecHits_position_x;   //!
   TBranch        *b_TOFEndcapRecHits_position_y;   //!
   TBranch        *b_TOFEndcapRecHits_position_z;   //!
   TBranch        *b_TOFEndcapRecHits_positionError_xx;   //!
   TBranch        *b_TOFEndcapRecHits_positionError_yy;   //!
   TBranch        *b_TOFEndcapRecHits_positionError_zz;   //!
   TBranch        *b_TOFEndcapRecHits_time;   //!
   TBranch        *b_TOFEndcapRecHits_timeError;   //!
   TBranch        *b_TOFEndcapRecHits_edep;   //!
   TBranch        *b_TOFEndcapRecHits_edepError;   //!


   TBranch        *b_B0TrackerRecHits_;   //!
   TBranch        *b_B0TrackerRecHits_cellID;   //!
   TBranch        *b_B0TrackerRecHits_position_x;   //!
   TBranch        *b_B0TrackerRecHits_position_y;   //!
   TBranch        *b_B0TrackerRecHits_position_z;   //!
   TBranch        *b_B0TrackerRecHits_positionError_xx;   //!
   TBranch        *b_B0TrackerRecHits_positionError_yy;   //!
   TBranch        *b_B0TrackerRecHits_positionError_zz;   //!
   TBranch        *b_B0TrackerRecHits_time;   //!
   TBranch        *b_B0TrackerRecHits_timeError;   //!
   TBranch        *b_B0TrackerRecHits_edep;   //!
   TBranch        *b_B0TrackerRecHits_edepError;   //!


   TBranch        *b_B0ECalClusters_;   //!
   TBranch        *b_B0ECalClusters_type;   //!
   TBranch        *b_B0ECalClusters_energy;   //!
   TBranch        *b_B0ECalClusters_energyError;   //!
   TBranch        *b_B0ECalClusters_time;   //!
   TBranch        *b_B0ECalClusters_timeError;   //!
   TBranch        *b_B0ECalClusters_nhits;   //!
   TBranch        *b_B0ECalClusters_position_x;   //!
   TBranch        *b_B0ECalClusters_position_y;   //!
   TBranch        *b_B0ECalClusters_position_z;   //!
   TBranch        *b_B0ECalClusters_positionError_xx;   //!
   TBranch        *b_B0ECalClusters_positionError_yy;   //!
   TBranch        *b_B0ECalClusters_positionError_zz;   //!
   TBranch        *b_B0ECalClusters_positionError_xy;   //!
   TBranch        *b_B0ECalClusters_positionError_xz;   //!
   TBranch        *b_B0ECalClusters_positionError_yz;   //!

   TBranch        *b_B0ECalRawHits_;   //!
   TBranch        *b_B0ECalRawHits_cellID;   //!
   TBranch        *b_B0ECalRawHits_amplitude;   //!
   TBranch        *b_B0ECalRawHits_timeStamp;   //!
   TBranch        *b_B0ECalRecHits_;   //!
   TBranch        *b_B0ECalRecHits_cellID;   //!
   TBranch        *b_B0ECalRecHits_energy;   //!
   TBranch        *b_B0ECalRecHits_energyError;   //!
   TBranch        *b_B0ECalRecHits_time;   //!
   TBranch        *b_B0ECalRecHits_timeError;   //!
   TBranch        *b_B0ECalRecHits_position_x;   //!
   TBranch        *b_B0ECalRecHits_position_y;   //!
   TBranch        *b_B0ECalRecHits_position_z;   //!

   TBranch        *b_DIRCRawHits_;   //!
   TBranch        *b_DIRCRawHits_cellID;   //!
   TBranch        *b_DIRCRawHits_charge;   //!
   TBranch        *b_DIRCRawHits_timeStamp;   //!

   TBranch        *b_DRICHRawHits_;   //!
   TBranch        *b_DRICHRawHits_cellID;   //!
   TBranch        *b_DRICHRawHits_charge;   //!
   TBranch        *b_DRICHRawHits_timeStamp;   //!


   TBranch        *b_EcalBarrelClusters_;   //!
   TBranch        *b_EcalBarrelClusters_type;   //!
   TBranch        *b_EcalBarrelClusters_energy;   //!
   TBranch        *b_EcalBarrelClusters_energyError;   //!
   TBranch        *b_EcalBarrelClusters_time;   //!
   TBranch        *b_EcalBarrelClusters_timeError;   //!
   TBranch        *b_EcalBarrelClusters_nhits;   //!
   TBranch        *b_EcalBarrelClusters_position_x;   //!
   TBranch        *b_EcalBarrelClusters_position_y;   //!
   TBranch        *b_EcalBarrelClusters_position_z;   //!
   TBranch        *b_EcalBarrelClusters_positionError_xx;   //!
   TBranch        *b_EcalBarrelClusters_positionError_yy;   //!
   TBranch        *b_EcalBarrelClusters_positionError_zz;   //!
   TBranch        *b_EcalBarrelClusters_positionError_xy;   //!
   TBranch        *b_EcalBarrelClusters_positionError_xz;   //!
   TBranch        *b_EcalBarrelClusters_positionError_yz;   //!

   TBranch        *b_EcalBarrelImagingClusters_;   //!
   TBranch        *b_EcalBarrelImagingClusters_type;   //!
   TBranch        *b_EcalBarrelImagingClusters_energy;   //!
   TBranch        *b_EcalBarrelImagingClusters_energyError;   //!
   TBranch        *b_EcalBarrelImagingClusters_time;   //!
   TBranch        *b_EcalBarrelImagingClusters_timeError;   //!
   TBranch        *b_EcalBarrelImagingClusters_nhits;   //!
   TBranch        *b_EcalBarrelImagingClusters_position_x;   //!
   TBranch        *b_EcalBarrelImagingClusters_position_y;   //!
   TBranch        *b_EcalBarrelImagingClusters_position_z;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_xx;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_yy;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_zz;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_xy;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_xz;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_yz;   //!

   TBranch        *b_EcalBarrelImagingRecHits_;   //!
   TBranch        *b_EcalBarrelImagingRecHits_cellID;   //!
   TBranch        *b_EcalBarrelImagingRecHits_energy;   //!
   TBranch        *b_EcalBarrelImagingRecHits_energyError;   //!
   TBranch        *b_EcalBarrelImagingRecHits_time;   //!
   TBranch        *b_EcalBarrelImagingRecHits_timeError;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_x;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_y;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_z;   //!

   TBranch        *b_EcalBarrelScFiClusters_;   //!
   TBranch        *b_EcalBarrelScFiClusters_type;   //!
   TBranch        *b_EcalBarrelScFiClusters_energy;   //!
   TBranch        *b_EcalBarrelScFiClusters_energyError;   //!
   TBranch        *b_EcalBarrelScFiClusters_time;   //!
   TBranch        *b_EcalBarrelScFiClusters_timeError;   //!
   TBranch        *b_EcalBarrelScFiClusters_nhits;   //!
   TBranch        *b_EcalBarrelScFiClusters_position_x;   //!
   TBranch        *b_EcalBarrelScFiClusters_position_y;   //!
   TBranch        *b_EcalBarrelScFiClusters_position_z;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_xx;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_yy;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_zz;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_xy;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_xz;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_yz;   //!

   TBranch        *b_EcalBarrelScFiRecHits_;   //!
   TBranch        *b_EcalBarrelScFiRecHits_cellID;   //!
   TBranch        *b_EcalBarrelScFiRecHits_energy;   //!
   TBranch        *b_EcalBarrelScFiRecHits_energyError;   //!
   TBranch        *b_EcalBarrelScFiRecHits_time;   //!
   TBranch        *b_EcalBarrelScFiRecHits_timeError;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_x;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_y;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_z;   //!

   TBranch        *b_EcalEndcapNClusters_;   //!
   TBranch        *b_EcalEndcapNClusters_type;   //!
   TBranch        *b_EcalEndcapNClusters_energy;   //!
   TBranch        *b_EcalEndcapNClusters_energyError;   //!
   TBranch        *b_EcalEndcapNClusters_time;   //!
   TBranch        *b_EcalEndcapNClusters_timeError;   //!
   TBranch        *b_EcalEndcapNClusters_nhits;   //!
   TBranch        *b_EcalEndcapNClusters_position_x;   //!
   TBranch        *b_EcalEndcapNClusters_position_y;   //!
   TBranch        *b_EcalEndcapNClusters_position_z;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_xx;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_yy;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_zz;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_xy;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_xz;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_yz;   //!

   TBranch        *b_EcalEndcapNRecHits_;   //!
   TBranch        *b_EcalEndcapNRecHits_cellID;   //!
   TBranch        *b_EcalEndcapNRecHits_energy;   //!
   TBranch        *b_EcalEndcapNRecHits_energyError;   //!
   TBranch        *b_EcalEndcapNRecHits_time;   //!
   TBranch        *b_EcalEndcapNRecHits_timeError;   //!
   TBranch        *b_EcalEndcapNRecHits_position_x;   //!
   TBranch        *b_EcalEndcapNRecHits_position_y;   //!
   TBranch        *b_EcalEndcapNRecHits_position_z;   //!

   TBranch        *b_EcalEndcapPClusters_;   //!
   TBranch        *b_EcalEndcapPClusters_type;   //!
   TBranch        *b_EcalEndcapPClusters_energy;   //!
   TBranch        *b_EcalEndcapPClusters_energyError;   //!
   TBranch        *b_EcalEndcapPClusters_time;   //!
   TBranch        *b_EcalEndcapPClusters_timeError;   //!
   TBranch        *b_EcalEndcapPClusters_nhits;   //!
   TBranch        *b_EcalEndcapPClusters_position_x;   //!
   TBranch        *b_EcalEndcapPClusters_position_y;   //!
   TBranch        *b_EcalEndcapPClusters_position_z;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_xx;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_yy;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_zz;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_xy;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_xz;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_yz;   //!

   TBranch        *b_EcalEndcapPRecHits_;   //!
   TBranch        *b_EcalEndcapPRecHits_cellID;   //!
   TBranch        *b_EcalEndcapPRecHits_energy;   //!
   TBranch        *b_EcalEndcapPRecHits_energyError;   //!
   TBranch        *b_EcalEndcapPRecHits_time;   //!
   TBranch        *b_EcalEndcapPRecHits_timeError;   //!
   TBranch        *b_EcalEndcapPRecHits_position_x;   //!
   TBranch        *b_EcalEndcapPRecHits_position_y;   //!
   TBranch        *b_EcalEndcapPRecHits_position_z;   //!

   TBranch        *b_EcalFarForwardZDCClusters_;   //!
   TBranch        *b_EcalFarForwardZDCClusters_type;   //!
   TBranch        *b_EcalFarForwardZDCClusters_energy;   //!
   TBranch        *b_EcalFarForwardZDCClusters_energyError;   //!
   TBranch        *b_EcalFarForwardZDCClusters_time;   //!
   TBranch        *b_EcalFarForwardZDCClusters_timeError;   //!
   TBranch        *b_EcalFarForwardZDCClusters_nhits;   //!
   TBranch        *b_EcalFarForwardZDCClusters_position_x;   //!
   TBranch        *b_EcalFarForwardZDCClusters_position_y;   //!
   TBranch        *b_EcalFarForwardZDCClusters_position_z;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_xx;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_yy;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_zz;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_xy;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_xz;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_yz;   //!

   TBranch        *b_EcalFarForwardZDCRecHits_;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_cellID;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_energy;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_energyError;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_time;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_timeError;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_x;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_y;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_z;   //!

   TBranch        *b_EcalLumiSpecClusters_;   //!
   TBranch        *b_EcalLumiSpecClusters_type;   //!
   TBranch        *b_EcalLumiSpecClusters_energy;   //!
   TBranch        *b_EcalLumiSpecClusters_energyError;   //!
   TBranch        *b_EcalLumiSpecClusters_time;   //!
   TBranch        *b_EcalLumiSpecClusters_timeError;   //!
   TBranch        *b_EcalLumiSpecClusters_nhits;   //!
   TBranch        *b_EcalLumiSpecClusters_position_x;   //!
   TBranch        *b_EcalLumiSpecClusters_position_y;   //!
   TBranch        *b_EcalLumiSpecClusters_position_z;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_xx;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_yy;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_zz;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_xy;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_xz;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_yz;   //!

   TBranch        *b_EcalLumiSpecRecHits_;   //!
   TBranch        *b_EcalLumiSpecRecHits_cellID;   //!
   TBranch        *b_EcalLumiSpecRecHits_energy;   //!
   TBranch        *b_EcalLumiSpecRecHits_energyError;   //!
   TBranch        *b_EcalLumiSpecRecHits_time;   //!
   TBranch        *b_EcalLumiSpecRecHits_timeError;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_x;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_y;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_z;   //!

   TBranch        *b_ForwardOffMTrackerRecHits_;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_cellID;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_position_x;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_position_y;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_position_z;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_positionError_xx;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_positionError_yy;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_positionError_zz;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_time;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_timeError;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_edep;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_edepError;   //!

   TBranch        *b_ForwardRomanPotRecHits_;   //!
   TBranch        *b_ForwardRomanPotRecHits_cellID;   //!
   TBranch        *b_ForwardRomanPotRecHits_position_x;   //!
   TBranch        *b_ForwardRomanPotRecHits_position_y;   //!
   TBranch        *b_ForwardRomanPotRecHits_position_z;   //!
   TBranch        *b_ForwardRomanPotRecHits_positionError_xx;   //!
   TBranch        *b_ForwardRomanPotRecHits_positionError_yy;   //!
   TBranch        *b_ForwardRomanPotRecHits_positionError_zz;   //!
   TBranch        *b_ForwardRomanPotRecHits_time;   //!
   TBranch        *b_ForwardRomanPotRecHits_timeError;   //!
   TBranch        *b_ForwardRomanPotRecHits_edep;   //!
   TBranch        *b_ForwardRomanPotRecHits_edepError;   //!

   TBranch        *b_LFHCALClusters_;   //!
   TBranch        *b_LFHCALClusters_type;   //!
   TBranch        *b_LFHCALClusters_energy;   //!
   TBranch        *b_LFHCALClusters_energyError;   //!
   TBranch        *b_LFHCALClusters_time;   //!
   TBranch        *b_LFHCALClusters_timeError;   //!
   TBranch        *b_LFHCALClusters_nhits;   //!
   TBranch        *b_LFHCALClusters_position_x;   //!
   TBranch        *b_LFHCALClusters_position_y;   //!
   TBranch        *b_LFHCALClusters_position_z;   //!
   TBranch        *b_LFHCALClusters_positionError_xx;   //!
   TBranch        *b_LFHCALClusters_positionError_yy;   //!
   TBranch        *b_LFHCALClusters_positionError_zz;   //!
   TBranch        *b_LFHCALClusters_positionError_xy;   //!
   TBranch        *b_LFHCALClusters_positionError_xz;   //!
   TBranch        *b_LFHCALClusters_positionError_yz;   //!

   TBranch        *b_LFHCALRecHits_;   //!
   TBranch        *b_LFHCALRecHits_cellID;   //!
   TBranch        *b_LFHCALRecHits_energy;   //!
   TBranch        *b_LFHCALRecHits_energyError;   //!
   TBranch        *b_LFHCALRecHits_time;   //!
   TBranch        *b_LFHCALRecHits_timeError;   //!
   TBranch        *b_LFHCALRecHits_position_x;   //!
   TBranch        *b_LFHCALRecHits_position_y;   //!
   TBranch        *b_LFHCALRecHits_position_z;   //!



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

   // TString m_simTrackHitNames[17] = \
   // {
   //    "B0TrackerHits",       "BackwardMPGDEndcapHits", "DIRCBarHits",\
   //    "DRICHHits",           "ForwardMPGDEndcapHits",  "ForwardOffMTrackerHits",\
   //    "ForwardRomanPotHits", "LumiSpecTrackerHits",    "MPGDBarrelHits",\
   //    "OuterMPGDBarrelHits", "RICHEndcapNHits",        "SiBarrelHits",\
   //    "TOFBarrelHits",       "TOFEndcapHits",          "TaggerTrackerHits",\
   //    "TrackerEndcapHits",   "VertexBarrelHits"
   // };

   TString m_simTrackHitNames[17] = \
   {
      "TOFBarrelRecHits", "TOFEndcapRecHits",
      "MPGDBarrelRecHits", "OuterMPGDBarrelRecHits",
      "BackwardMPGDEndcapRecHits", "ForwardMPGDEndcapRecHits",
      "SiBarrelVertexRecHits", "SiBarrelTrackerRecHits",
      "SiEndcapTrackerRecHits", "TaggerTrackerRecHits",
      "B0TrackerRecHits", "DIRCBarRecHits",
      "DRICHRecHits", "ForwardOffMTrackerRecHits",
      "ForwardRomanPotRecHits", "LumiSpecTrackerRecHits",
      "RICHEndcapNRecHits"
   };


   std::vector<SimTrackerHitKuma > m_SimTrackerHitsKuma; // a "kuma example" of a member valuable
   // black, blue, red, green, violet, orange, light blue, light green, dark violet, brown, very light blue, 
   // yellow green, week red, dark blue, week green, dark cyan, dark orange, 
   Int_t m_myHistColors[18] = {4, 600, 632, 419, 880, 807, 867, 909, 814, 874, 635, 870, 824, 625, 602, 417, 434, 802}; // colors for histograms
   
   

   // histograms as output
   TH2D* m_hEventDisplayZR_Det;
   TH2D* m_hEventDisplayZR_Det_TF;

   TH1D* m_hTriggerCounts; // histogram for trigger types

   TH1D* m_hMCEtaDist; // 
   TH1D* m_hMCThetaDist; // 


   // == member functions == // own function
   void HistInit();
   void ResetValuesForEachEvent();
   void WriteHists();
   
   float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   float m_timeslice_width = 20.0; // width of time split for a time frame [ns]

   size_t m_triggerDetSize = 9;
   // Int_t detId[10] = {12, 13, 1, 4, 8, 9, 11, 14, 15, 16}; // TOF and MPGD, Silicon excluded
   Int_t detId[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // TOF and MPGD, Silicon excluded

   float m_timeResolution_Silicon = 2000.0; // time resolution [ns]
   float m_timeResolution_MPGD = 10.0; // time resolution [ns]
   // float m_timeResolution_TOF = 0.030; // time resolution [ns]
   float m_timeResolution_TOF = 1.0; // time resolution [ns]

   bool bInitialLoop = true;
   std::vector<std::vector<unsigned int > > m_vOrigHitId;

   std::vector<std::vector<unsigned int > > m_vSameTSHitId;
   std::vector<std::vector<unsigned int > > m_vOutputHitContainer;


   bool m_bDetLastHits[9] = {false, false, false, false, false, false, false, false, false};

   bool m_bOnceTriggered = false;
   bool m_bScanedAllTimeWindows = false;

   bool m_bOncePhysicsTriggered = false;
   int checkCount = 0;

   void HitTimeCalibration(Double_t timeOffSet);
   Double_t MakeRandomTimeOffset(Int_t randomSeed);
   Double_t FindFirstPhysParticle();

   Double_t HistCriticalValueEstimation(Double_t confidence, TH1D* hist);
   
   void FillEventDisplay(Double_t sTime, Double_t eTime, bool bTF);

   inline Double_t HitTimeCalibrationByR(Double_t hitTime, Double_t hitR){
      // return hitTime - 0.003*hitR;

      Double_t calibTime = (hitR - 91.7)/279;
      return hitTime - calibTime;
   };

   // == inherited functions == //
   std::vector<SimTrackerHitKuma> LoadInputHits();

   void thetaPhiBinCalc(SimTrackerHitKuma& simHitsKuma, Int_t hitId,\
      Int_t& thetaID1, Int_t& phiID1, Int_t& thetaID2, Int_t& phiID2);
};


#endif

// #ifndef triggerCombineChecker_cxx
// #define triggerCombineChecker_cxx


// #endif // #ifdef triggerCombineChecker_cxx
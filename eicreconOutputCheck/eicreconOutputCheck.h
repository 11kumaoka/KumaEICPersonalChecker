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

#ifndef eicreconOutputCheck_h
#define eicreconOutputCheck_h

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
#include <TPolyMarker3D.h>

#include "SimTrackerHitKuma.h"


#include <TApplication.h>
#include <TCanvas.h>
#include <TView.h>
#include <TAxis3D.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLatex.h>


class eicreconOutputCheck {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any. 
   eicreconOutputCheck(TTree *tree=0, std::string iFileName="", std::string oFileName="");
   virtual ~eicreconOutputCheck();
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

   static constexpr Int_t kMaxMCParticles = 9999999;
   static constexpr Int_t kMax_MCParticles_parents = 9999999;
   static constexpr Int_t kMax_MCParticles_daughters = 9999999;

   static constexpr Int_t kMaxSiBarrelVertexRecHits = 999999;
   static constexpr Int_t kMax_SiBarrelVertexRecHits_rawHit = 999999;
   static constexpr Int_t kMaxSiBarrelTrackerRecHits = 999999;
   static constexpr Int_t kMax_SiBarrelTrackerRecHits_rawHit = 999999;
   static constexpr Int_t kMaxSiEndcapTrackerRecHits = 999999;
   static constexpr Int_t kMax_SiEndcapTrackerRecHits_rawHit = 999999;

   static constexpr Int_t kMaxMPGDBarrelRecHits = 99999;
   static constexpr Int_t kMax_MPGDBarrelRecHits_rawHit = 99999;
   static constexpr Int_t kMaxOuterMPGDBarrelRecHits = 99999;
   static constexpr Int_t kMax_OuterMPGDBarrelRecHits_rawHit = 99999;
   static constexpr Int_t kMaxForwardMPGDEndcapRecHits = 99999;
   static constexpr Int_t kMax_ForwardMPGDEndcapRecHits_rawHit = 99999;
   static constexpr Int_t kMaxBackwardMPGDEndcapRecHits = 99999;
   static constexpr Int_t kMax_BackwardMPGDEndcapRecHits_rawHit = 99999;

   static constexpr Int_t kMaxTOFBarrelRecHits = 99999;
   static constexpr Int_t kMax_TOFBarrelRecHits_rawHit = 99999;
   static constexpr Int_t kMaxTOFEndcapRecHits = 99999;
   static constexpr Int_t kMax_TOFEndcapRecHits_rawHit = 99999;

   static constexpr Int_t kMaxB0TrackerRecHits = 999999;
   static constexpr Int_t kMax_B0TrackerRecHits_rawHit = 999999;

   static constexpr Int_t kMaxB0ECalRecHits = 999999;
   static constexpr Int_t kMax_B0ECalRecHits_rawHit = 999999;

   static constexpr Int_t kMaxEcalBarrelImagingRecHits = 99999;
   static constexpr Int_t kMax_EcalBarrelImagingRecHits_rawHit = 99999;

   static constexpr Int_t kMaxEcalBarrelScFiRecHits = 9999;
   static constexpr Int_t kMax_EcalBarrelScFiRecHits_rawHit = 9999;
   static constexpr Int_t kMaxEcalEndcapNRecHits = 99999;
   static constexpr Int_t kMax_EcalEndcapNRecHits_rawHit = 99999;
   static constexpr Int_t kMaxEcalEndcapPRecHits = 999999;
   static constexpr Int_t kMax_EcalEndcapPRecHits_rawHit = 999999;
   static constexpr Int_t kMaxEcalFarForwardZDCRecHits = 99999;
   static constexpr Int_t kMax_EcalFarForwardZDCRecHits_rawHit = 99999;
   static constexpr Int_t kMaxEcalLumiSpecRecHits = 9999999;
   static constexpr Int_t kMax_EcalLumiSpecRecHits_rawHit = 9999999;

   static constexpr Int_t kMaxForwardOffMTrackerRecHits = 9999999;
   static constexpr Int_t kMax_ForwardOffMTrackerRecHits_rawHit = 9999999;
   static constexpr Int_t kMaxForwardRomanPotRecHits = 9999999;
   static constexpr Int_t kMax_ForwardRomanPotRecHits_rawHit = 9999999;
   static constexpr Int_t kMaxHcalBarrelRecHits = 9999999;
   static constexpr Int_t kMax_HcalBarrelRecHits_rawHit = 9999999;
   static constexpr Int_t kMaxHcalEndcapNRecHits = 9999999;
   static constexpr Int_t kMax_HcalEndcapNRecHits_rawHit = 9999999;
   static constexpr Int_t kMaxHcalEndcapPInsertRecHits = 9999999;
   static constexpr Int_t kMax_HcalEndcapPInsertRecHits_rawHit = 9999999;
   static constexpr Int_t kMaxHcalFarForwardZDCRecHits = 9999999;
   static constexpr Int_t kMax_HcalFarForwardZDCRecHits_rawHit = 9999999;

   static constexpr Int_t kMaxLFHCALRecHits = 999999;
   static constexpr Int_t kMax_LFHCALRecHits_rawHit = 999999;



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
   Int_t           _SiBarrelVertexRecHits_rawHit_;
   Int_t           _SiBarrelVertexRecHits_rawHit_index[kMax_SiBarrelVertexRecHits_rawHit];   //[_SiBarrelVertexRecHits_rawHit_]
   UInt_t          _SiBarrelVertexRecHits_rawHit_collectionID[kMax_SiBarrelVertexRecHits_rawHit];   //[_SiBarrelVertexRecHits_rawHit_]

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
   Int_t           _SiBarrelTrackerRecHits_rawHit_;
   Int_t           _SiBarrelTrackerRecHits_rawHit_index[kMax_SiBarrelTrackerRecHits_rawHit];   //[_SiBarrelTrackerRecHits_rawHit_]
   UInt_t          _SiBarrelTrackerRecHits_rawHit_collectionID[kMax_SiBarrelTrackerRecHits_rawHit];   //[_SiBarrelTrackerRecHits_rawHit_]

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
   Int_t           _SiEndcapTrackerRecHits_rawHit_;
   Int_t           _SiEndcapTrackerRecHits_rawHit_index[kMax_SiEndcapTrackerRecHits_rawHit];   //[_SiEndcapTrackerRecHits_rawHit_]
   UInt_t          _SiEndcapTrackerRecHits_rawHit_collectionID[kMax_SiEndcapTrackerRecHits_rawHit];   //[_SiEndcapTrackerRecHits_rawHit_]

   
   
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
   Int_t           _MPGDBarrelRecHits_rawHit_;
   Int_t           _MPGDBarrelRecHits_rawHit_index[kMax_MPGDBarrelRecHits_rawHit];   //[_MPGDBarrelRecHits_rawHit_]
   UInt_t          _MPGDBarrelRecHits_rawHit_collectionID[kMax_MPGDBarrelRecHits_rawHit];   //[_MPGDBarrelRecHits_rawHit_]

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
   Int_t           _OuterMPGDBarrelRecHits_rawHit_;
   Int_t           _OuterMPGDBarrelRecHits_rawHit_index[kMax_OuterMPGDBarrelRecHits_rawHit];   //[_OuterMPGDBarrelRecHits_rawHit_]
   UInt_t          _OuterMPGDBarrelRecHits_rawHit_collectionID[kMax_OuterMPGDBarrelRecHits_rawHit];   //[_OuterMPGDBarrelRecHits_rawHit_]

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
   Int_t           _BackwardMPGDEndcapRecHits_rawHit_;
   Int_t           _BackwardMPGDEndcapRecHits_rawHit_index[kMax_BackwardMPGDEndcapRecHits_rawHit];   //[_BackwardMPGDEndcapRecHits_rawHit_]
   UInt_t          _BackwardMPGDEndcapRecHits_rawHit_collectionID[kMax_BackwardMPGDEndcapRecHits_rawHit];   //[_BackwardMPGDEndcapRecHits_rawHit_]


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
   Int_t           _TOFBarrelRecHits_rawHit_;
   Int_t           _TOFBarrelRecHits_rawHit_index[kMax_TOFBarrelRecHits_rawHit];   //[_TOFBarrelRecHits_rawHit_]
   UInt_t          _TOFBarrelRecHits_rawHit_collectionID[kMax_TOFBarrelRecHits_rawHit];   //[_TOFBarrelRecHits_rawHit_]

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
   Int_t           _TOFEndcapRecHits_rawHit_;
   Int_t           _TOFEndcapRecHits_rawHit_index[kMax_TOFEndcapRecHits_rawHit];   //[_TOFEndcapRecHits_rawHit_]
   UInt_t          _TOFEndcapRecHits_rawHit_collectionID[kMax_TOFEndcapRecHits_rawHit];   //[_TOFEndcapRecHits_rawHit_]

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
   Int_t           _B0TrackerRecHits_rawHit_;
   Int_t           _B0TrackerRecHits_rawHit_index[kMax_B0TrackerRecHits_rawHit];   //[_B0TrackerRecHits_rawHit_]
   UInt_t          _B0TrackerRecHits_rawHit_collectionID[kMax_B0TrackerRecHits_rawHit];   //[_B0TrackerRecHits_rawHit_]







   Int_t           B0ECalRecHits_;
   ULong_t         B0ECalRecHits_cellID[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_energy[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_energyError[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_time[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_timeError[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_x[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_y[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_z[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_dimension_x[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_dimension_y[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_dimension_z[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Int_t           B0ECalRecHits_sector[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Int_t           B0ECalRecHits_layer[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_local_x[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_local_y[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_local_z[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Int_t           _B0ECalRecHits_rawHit_;
   Int_t           _B0ECalRecHits_rawHit_index[kMax_B0ECalRecHits_rawHit];   //[_B0ECalRecHits_rawHit_]
   UInt_t          _B0ECalRecHits_rawHit_collectionID[kMax_B0ECalRecHits_rawHit];   //[_B0ECalRecHits_rawHit_]

   Int_t           EcalBarrelImagingRecHits_;
   ULong_t         EcalBarrelImagingRecHits_cellID[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_energy[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_energyError[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_time[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_timeError[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_x[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_y[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_z[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_dimension_x[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_dimension_y[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_dimension_z[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Int_t           EcalBarrelImagingRecHits_sector[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Int_t           EcalBarrelImagingRecHits_layer[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_local_x[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_local_y[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_local_z[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Int_t           _EcalBarrelImagingRecHits_rawHit_;
   Int_t           _EcalBarrelImagingRecHits_rawHit_index[kMax_EcalBarrelImagingRecHits_rawHit];   //[_EcalBarrelImagingRecHits_rawHit_]
   UInt_t          _EcalBarrelImagingRecHits_rawHit_collectionID[kMax_EcalBarrelImagingRecHits_rawHit];   //[_EcalBarrelImagingRecHits_rawHit_]

   Int_t           EcalBarrelScFiRecHits_;
   ULong_t         EcalBarrelScFiRecHits_cellID[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_energy[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_energyError[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_time[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_timeError[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_x[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_y[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_z[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_dimension_x[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_dimension_y[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_dimension_z[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Int_t           EcalBarrelScFiRecHits_sector[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Int_t           EcalBarrelScFiRecHits_layer[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_local_x[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_local_y[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_local_z[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Int_t           _EcalBarrelScFiRecHits_rawHit_;
   Int_t           _EcalBarrelScFiRecHits_rawHit_index[kMax_EcalBarrelScFiRecHits_rawHit];   //[_EcalBarrelScFiRecHits_rawHit_]
   UInt_t          _EcalBarrelScFiRecHits_rawHit_collectionID[kMax_EcalBarrelScFiRecHits_rawHit];   //[_EcalBarrelScFiRecHits_rawHit_]


   Int_t           EcalEndcapNRecHits_;
   ULong_t         EcalEndcapNRecHits_cellID[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_energy[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_energyError[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_time[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_timeError[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_x[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_y[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_z[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_dimension_x[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_dimension_y[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_dimension_z[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Int_t           EcalEndcapNRecHits_sector[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Int_t           EcalEndcapNRecHits_layer[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_local_x[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_local_y[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_local_z[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Int_t           _EcalEndcapNRecHits_rawHit_;
   Int_t           _EcalEndcapNRecHits_rawHit_index[kMax_EcalEndcapNRecHits_rawHit];   //[_EcalEndcapNRecHits_rawHit_]
   UInt_t          _EcalEndcapNRecHits_rawHit_collectionID[kMax_EcalEndcapNRecHits_rawHit];   //[_EcalEndcapNRecHits_rawHit_]

      Int_t           EcalEndcapPRecHits_;
   ULong_t         EcalEndcapPRecHits_cellID[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_energy[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_energyError[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_time[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_timeError[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_x[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_y[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_z[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_dimension_x[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_dimension_y[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_dimension_z[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Int_t           EcalEndcapPRecHits_sector[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Int_t           EcalEndcapPRecHits_layer[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_local_x[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_local_y[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_local_z[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Int_t           _EcalEndcapPRecHits_rawHit_;
   Int_t           _EcalEndcapPRecHits_rawHit_index[kMax_EcalEndcapPRecHits_rawHit];   //[_EcalEndcapPRecHits_rawHit_]
   UInt_t          _EcalEndcapPRecHits_rawHit_collectionID[kMax_EcalEndcapPRecHits_rawHit];   //[_EcalEndcapPRecHits_rawHit_]

   Int_t           EcalFarForwardZDCRecHits_;
   ULong_t         EcalFarForwardZDCRecHits_cellID[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_energy[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_energyError[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_time[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_timeError[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_x[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_y[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_z[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_dimension_x[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_dimension_y[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_dimension_z[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Int_t           EcalFarForwardZDCRecHits_sector[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Int_t           EcalFarForwardZDCRecHits_layer[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_local_x[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_local_y[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_local_z[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Int_t           _EcalFarForwardZDCRecHits_rawHit_;
   Int_t           _EcalFarForwardZDCRecHits_rawHit_index[kMax_EcalFarForwardZDCRecHits_rawHit];   //[_EcalFarForwardZDCRecHits_rawHit_]
   UInt_t          _EcalFarForwardZDCRecHits_rawHit_collectionID[kMax_EcalFarForwardZDCRecHits_rawHit];   //[_EcalFarForwardZDCRecHits_rawHit_]

   Int_t           EcalLumiSpecRecHits_;
   ULong_t         EcalLumiSpecRecHits_cellID[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_energy[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_energyError[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_time[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_timeError[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_x[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_y[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_z[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_dimension_x[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_dimension_y[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_dimension_z[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Int_t           EcalLumiSpecRecHits_sector[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Int_t           EcalLumiSpecRecHits_layer[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_local_x[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_local_y[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_local_z[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Int_t           _EcalLumiSpecRecHits_rawHit_;
   Int_t           _EcalLumiSpecRecHits_rawHit_index[kMax_EcalLumiSpecRecHits_rawHit];   //[_EcalLumiSpecRecHits_rawHit_]
   UInt_t          _EcalLumiSpecRecHits_rawHit_collectionID[kMax_EcalLumiSpecRecHits_rawHit];   //[_EcalLumiSpecRecHits_rawHit_]

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
   Int_t           _ForwardMPGDEndcapRecHits_rawHit_;
   Int_t           _ForwardMPGDEndcapRecHits_rawHit_index[kMax_ForwardMPGDEndcapRecHits_rawHit];   //[_ForwardMPGDEndcapRecHits_rawHit_]
   UInt_t          _ForwardMPGDEndcapRecHits_rawHit_collectionID[kMax_ForwardMPGDEndcapRecHits_rawHit];   //[_ForwardMPGDEndcapRecHits_rawHit_]

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
   Int_t           _ForwardOffMTrackerRecHits_rawHit_;
   Int_t           _ForwardOffMTrackerRecHits_rawHit_index[kMax_ForwardOffMTrackerRecHits_rawHit];   //[_ForwardOffMTrackerRecHits_rawHit_]
   UInt_t          _ForwardOffMTrackerRecHits_rawHit_collectionID[kMax_ForwardOffMTrackerRecHits_rawHit];   //[_ForwardOffMTrackerRecHits_rawHit_]

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
   Int_t           _ForwardRomanPotRecHits_rawHit_;
   Int_t           _ForwardRomanPotRecHits_rawHit_index[kMax_ForwardRomanPotRecHits_rawHit];   //[_ForwardRomanPotRecHits_rawHit_]
   UInt_t          _ForwardRomanPotRecHits_rawHit_collectionID[kMax_ForwardRomanPotRecHits_rawHit];   //[_ForwardRomanPotRecHits_rawHit_]

   Int_t           HcalBarrelRecHits_;
   ULong_t         HcalBarrelRecHits_cellID[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_energy[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_energyError[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_time[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_timeError[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_position_x[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_position_y[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_position_z[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_dimension_x[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_dimension_y[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_dimension_z[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Int_t           HcalBarrelRecHits_sector[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Int_t           HcalBarrelRecHits_layer[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_local_x[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_local_y[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Float_t         HcalBarrelRecHits_local_z[kMaxHcalBarrelRecHits];   //[HcalBarrelRecHits_]
   Int_t           _HcalBarrelRecHits_rawHit_;
   Int_t           _HcalBarrelRecHits_rawHit_index[kMax_HcalBarrelRecHits_rawHit];   //[_HcalBarrelRecHits_rawHit_]
   UInt_t          _HcalBarrelRecHits_rawHit_collectionID[kMax_HcalBarrelRecHits_rawHit];   //[_HcalBarrelRecHits_rawHit_]

      Int_t           HcalEndcapNRecHits_;
   ULong_t         HcalEndcapNRecHits_cellID[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_energy[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_energyError[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_time[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_timeError[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_position_x[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_position_y[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_position_z[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_dimension_x[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_dimension_y[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_dimension_z[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Int_t           HcalEndcapNRecHits_sector[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Int_t           HcalEndcapNRecHits_layer[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_local_x[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_local_y[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Float_t         HcalEndcapNRecHits_local_z[kMaxHcalEndcapNRecHits];   //[HcalEndcapNRecHits_]
   Int_t           _HcalEndcapNRecHits_rawHit_;
   Int_t           _HcalEndcapNRecHits_rawHit_index[kMax_HcalEndcapNRecHits_rawHit];   //[_HcalEndcapNRecHits_rawHit_]
   UInt_t          _HcalEndcapNRecHits_rawHit_collectionID[kMax_HcalEndcapNRecHits_rawHit];   //[_HcalEndcapNRecHits_rawHit_]

      Int_t           HcalEndcapPInsertRecHits_;
   ULong_t         HcalEndcapPInsertRecHits_cellID[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_energy[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_energyError[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_time[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_timeError[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_position_x[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_position_y[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_position_z[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_dimension_x[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_dimension_y[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_dimension_z[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Int_t           HcalEndcapPInsertRecHits_sector[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Int_t           HcalEndcapPInsertRecHits_layer[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_local_x[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_local_y[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Float_t         HcalEndcapPInsertRecHits_local_z[kMaxHcalEndcapPInsertRecHits];   //[HcalEndcapPInsertRecHits_]
   Int_t           _HcalEndcapPInsertRecHits_rawHit_;
   Int_t           _HcalEndcapPInsertRecHits_rawHit_index[kMax_HcalEndcapPInsertRecHits_rawHit];   //[_HcalEndcapPInsertRecHits_rawHit_]
   UInt_t          _HcalEndcapPInsertRecHits_rawHit_collectionID[kMax_HcalEndcapPInsertRecHits_rawHit];   //[_HcalEndcapPInsertRecHits_rawHit_]

      Int_t           HcalFarForwardZDCRecHits_;
   ULong_t         HcalFarForwardZDCRecHits_cellID[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_energy[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_energyError[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_time[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_timeError[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_position_x[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_position_y[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_position_z[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_dimension_x[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_dimension_y[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_dimension_z[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Int_t           HcalFarForwardZDCRecHits_sector[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Int_t           HcalFarForwardZDCRecHits_layer[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_local_x[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_local_y[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Float_t         HcalFarForwardZDCRecHits_local_z[kMaxHcalFarForwardZDCRecHits];   //[HcalFarForwardZDCRecHits_]
   Int_t           _HcalFarForwardZDCRecHits_rawHit_;
   Int_t           _HcalFarForwardZDCRecHits_rawHit_index[kMax_HcalFarForwardZDCRecHits_rawHit];   //[_HcalFarForwardZDCRecHits_rawHit_]
   UInt_t          _HcalFarForwardZDCRecHits_rawHit_collectionID[kMax_HcalFarForwardZDCRecHits_rawHit];   //[_HcalFarForwardZDCRecHits_rawHit_]

      Int_t           LFHCALRecHits_;
   ULong_t         LFHCALRecHits_cellID[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_energy[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_energyError[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_time[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_timeError[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_x[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_y[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_z[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_dimension_x[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_dimension_y[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_dimension_z[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Int_t           LFHCALRecHits_sector[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Int_t           LFHCALRecHits_layer[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_local_x[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_local_y[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_local_z[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Int_t           _LFHCALRecHits_rawHit_;
   Int_t           _LFHCALRecHits_rawHit_index[kMax_LFHCALRecHits_rawHit];   //[_LFHCALRecHits_rawHit_]
   UInt_t          _LFHCALRecHits_rawHit_collectionID[kMax_LFHCALRecHits_rawHit];   //[_LFHCALRecHits_rawHit_]




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
   TBranch        *b__SiBarrelVertexRecHits_rawHit_;   //!
   TBranch        *b__SiBarrelVertexRecHits_rawHit_index;   //!
   TBranch        *b__SiBarrelVertexRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__SiBarrelTrackerRecHits_rawHit_;   //!
   TBranch        *b__SiBarrelTrackerRecHits_rawHit_index;   //!
   TBranch        *b__SiBarrelTrackerRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__SiEndcapTrackerRecHits_rawHit_;   //!
   TBranch        *b__SiEndcapTrackerRecHits_rawHit_index;   //!
   TBranch        *b__SiEndcapTrackerRecHits_rawHit_collectionID;   //!


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
   TBranch        *b__MPGDBarrelRecHits_rawHit_;   //!
   TBranch        *b__MPGDBarrelRecHits_rawHit_index;   //!
   TBranch        *b__MPGDBarrelRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__OuterMPGDBarrelRecHits_rawHit_;   //!
   TBranch        *b__OuterMPGDBarrelRecHits_rawHit_index;   //!
   TBranch        *b__OuterMPGDBarrelRecHits_rawHit_collectionID;   //!


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
   TBranch        *b__BackwardMPGDEndcapRecHits_rawHit_;   //!
   TBranch        *b__BackwardMPGDEndcapRecHits_rawHit_index;   //!
   TBranch        *b__BackwardMPGDEndcapRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__ForwardMPGDEndcapRecHits_rawHit_;   //!
   TBranch        *b__ForwardMPGDEndcapRecHits_rawHit_index;   //!
   TBranch        *b__ForwardMPGDEndcapRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__TOFBarrelRecHits_rawHit_;   //!
   TBranch        *b__TOFBarrelRecHits_rawHit_index;   //!
   TBranch        *b__TOFBarrelRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__TOFEndcapRecHits_rawHit_;   //!
   TBranch        *b__TOFEndcapRecHits_rawHit_index;   //!
   TBranch        *b__TOFEndcapRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__B0TrackerRecHits_rawHit_;   //!
   TBranch        *b__B0TrackerRecHits_rawHit_index;   //!
   TBranch        *b__B0TrackerRecHits_rawHit_collectionID;   //!



      TBranch        *b_B0ECalRecHits_;   //!
   TBranch        *b_B0ECalRecHits_cellID;   //!
   TBranch        *b_B0ECalRecHits_energy;   //!
   TBranch        *b_B0ECalRecHits_energyError;   //!
   TBranch        *b_B0ECalRecHits_time;   //!
   TBranch        *b_B0ECalRecHits_timeError;   //!
   TBranch        *b_B0ECalRecHits_position_x;   //!
   TBranch        *b_B0ECalRecHits_position_y;   //!
   TBranch        *b_B0ECalRecHits_position_z;   //!
   TBranch        *b_B0ECalRecHits_dimension_x;   //!
   TBranch        *b_B0ECalRecHits_dimension_y;   //!
   TBranch        *b_B0ECalRecHits_dimension_z;   //!
   TBranch        *b_B0ECalRecHits_sector;   //!
   TBranch        *b_B0ECalRecHits_layer;   //!
   TBranch        *b_B0ECalRecHits_local_x;   //!
   TBranch        *b_B0ECalRecHits_local_y;   //!
   TBranch        *b_B0ECalRecHits_local_z;   //!
   TBranch        *b__B0ECalRecHits_rawHit_;   //!
   TBranch        *b__B0ECalRecHits_rawHit_index;   //!
   TBranch        *b__B0ECalRecHits_rawHit_collectionID;   //!

   TBranch        *b_EcalBarrelImagingRecHits_;   //!
   TBranch        *b_EcalBarrelImagingRecHits_cellID;   //!
   TBranch        *b_EcalBarrelImagingRecHits_energy;   //!
   TBranch        *b_EcalBarrelImagingRecHits_energyError;   //!
   TBranch        *b_EcalBarrelImagingRecHits_time;   //!
   TBranch        *b_EcalBarrelImagingRecHits_timeError;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_x;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_y;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_z;   //!
   TBranch        *b_EcalBarrelImagingRecHits_dimension_x;   //!
   TBranch        *b_EcalBarrelImagingRecHits_dimension_y;   //!
   TBranch        *b_EcalBarrelImagingRecHits_dimension_z;   //!
   TBranch        *b_EcalBarrelImagingRecHits_sector;   //!
   TBranch        *b_EcalBarrelImagingRecHits_layer;   //!
   TBranch        *b_EcalBarrelImagingRecHits_local_x;   //!
   TBranch        *b_EcalBarrelImagingRecHits_local_y;   //!
   TBranch        *b_EcalBarrelImagingRecHits_local_z;   //!
   TBranch        *b__EcalBarrelImagingRecHits_rawHit_;   //!
   TBranch        *b__EcalBarrelImagingRecHits_rawHit_index;   //!
   TBranch        *b__EcalBarrelImagingRecHits_rawHit_collectionID;   //!

      TBranch        *b_EcalBarrelScFiRecHits_;   //!
   TBranch        *b_EcalBarrelScFiRecHits_cellID;   //!
   TBranch        *b_EcalBarrelScFiRecHits_energy;   //!
   TBranch        *b_EcalBarrelScFiRecHits_energyError;   //!
   TBranch        *b_EcalBarrelScFiRecHits_time;   //!
   TBranch        *b_EcalBarrelScFiRecHits_timeError;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_x;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_y;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_z;   //!
   TBranch        *b_EcalBarrelScFiRecHits_dimension_x;   //!
   TBranch        *b_EcalBarrelScFiRecHits_dimension_y;   //!
   TBranch        *b_EcalBarrelScFiRecHits_dimension_z;   //!
   TBranch        *b_EcalBarrelScFiRecHits_sector;   //!
   TBranch        *b_EcalBarrelScFiRecHits_layer;   //!
   TBranch        *b_EcalBarrelScFiRecHits_local_x;   //!
   TBranch        *b_EcalBarrelScFiRecHits_local_y;   //!
   TBranch        *b_EcalBarrelScFiRecHits_local_z;   //!
   TBranch        *b__EcalBarrelScFiRecHits_rawHit_;   //!
   TBranch        *b__EcalBarrelScFiRecHits_rawHit_index;   //!
   TBranch        *b__EcalBarrelScFiRecHits_rawHit_collectionID;   //!

      TBranch        *b_EcalEndcapNRecHits_;   //!
   TBranch        *b_EcalEndcapNRecHits_cellID;   //!
   TBranch        *b_EcalEndcapNRecHits_energy;   //!
   TBranch        *b_EcalEndcapNRecHits_energyError;   //!
   TBranch        *b_EcalEndcapNRecHits_time;   //!
   TBranch        *b_EcalEndcapNRecHits_timeError;   //!
   TBranch        *b_EcalEndcapNRecHits_position_x;   //!
   TBranch        *b_EcalEndcapNRecHits_position_y;   //!
   TBranch        *b_EcalEndcapNRecHits_position_z;   //!
   TBranch        *b_EcalEndcapNRecHits_dimension_x;   //!
   TBranch        *b_EcalEndcapNRecHits_dimension_y;   //!
   TBranch        *b_EcalEndcapNRecHits_dimension_z;   //!
   TBranch        *b_EcalEndcapNRecHits_sector;   //!
   TBranch        *b_EcalEndcapNRecHits_layer;   //!
   TBranch        *b_EcalEndcapNRecHits_local_x;   //!
   TBranch        *b_EcalEndcapNRecHits_local_y;   //!
   TBranch        *b_EcalEndcapNRecHits_local_z;   //!
   TBranch        *b__EcalEndcapNRecHits_rawHit_;   //!
   TBranch        *b__EcalEndcapNRecHits_rawHit_index;   //!
   TBranch        *b__EcalEndcapNRecHits_rawHit_collectionID;   //!
   
   TBranch        *b_EcalEndcapPRecHits_;   //!
   TBranch        *b_EcalEndcapPRecHits_cellID;   //!
   TBranch        *b_EcalEndcapPRecHits_energy;   //!
   TBranch        *b_EcalEndcapPRecHits_energyError;   //!
   TBranch        *b_EcalEndcapPRecHits_time;   //!
   TBranch        *b_EcalEndcapPRecHits_timeError;   //!
   TBranch        *b_EcalEndcapPRecHits_position_x;   //!
   TBranch        *b_EcalEndcapPRecHits_position_y;   //!
   TBranch        *b_EcalEndcapPRecHits_position_z;   //!
   TBranch        *b_EcalEndcapPRecHits_dimension_x;   //!
   TBranch        *b_EcalEndcapPRecHits_dimension_y;   //!
   TBranch        *b_EcalEndcapPRecHits_dimension_z;   //!
   TBranch        *b_EcalEndcapPRecHits_sector;   //!
   TBranch        *b_EcalEndcapPRecHits_layer;   //!
   TBranch        *b_EcalEndcapPRecHits_local_x;   //!
   TBranch        *b_EcalEndcapPRecHits_local_y;   //!
   TBranch        *b_EcalEndcapPRecHits_local_z;   //!
   TBranch        *b__EcalEndcapPRecHits_rawHit_;   //!
   TBranch        *b__EcalEndcapPRecHits_rawHit_index;   //!
   TBranch        *b__EcalEndcapPRecHits_rawHit_collectionID;   //!

   TBranch        *b_EcalFarForwardZDCRecHits_;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_cellID;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_energy;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_energyError;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_time;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_timeError;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_x;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_y;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_z;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_dimension_x;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_dimension_y;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_dimension_z;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_sector;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_layer;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_local_x;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_local_y;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_local_z;   //!
   TBranch        *b__EcalFarForwardZDCRecHits_rawHit_;   //!
   TBranch        *b__EcalFarForwardZDCRecHits_rawHit_index;   //!
   TBranch        *b__EcalFarForwardZDCRecHits_rawHit_collectionID;   //!

      TBranch        *b_EcalLumiSpecRecHits_;   //!
   TBranch        *b_EcalLumiSpecRecHits_cellID;   //!
   TBranch        *b_EcalLumiSpecRecHits_energy;   //!
   TBranch        *b_EcalLumiSpecRecHits_energyError;   //!
   TBranch        *b_EcalLumiSpecRecHits_time;   //!
   TBranch        *b_EcalLumiSpecRecHits_timeError;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_x;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_y;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_z;   //!
   TBranch        *b_EcalLumiSpecRecHits_dimension_x;   //!
   TBranch        *b_EcalLumiSpecRecHits_dimension_y;   //!
   TBranch        *b_EcalLumiSpecRecHits_dimension_z;   //!
   TBranch        *b_EcalLumiSpecRecHits_sector;   //!
   TBranch        *b_EcalLumiSpecRecHits_layer;   //!
   TBranch        *b_EcalLumiSpecRecHits_local_x;   //!
   TBranch        *b_EcalLumiSpecRecHits_local_y;   //!
   TBranch        *b_EcalLumiSpecRecHits_local_z;   //!
   TBranch        *b__EcalLumiSpecRecHits_rawHit_;   //!
   TBranch        *b__EcalLumiSpecRecHits_rawHit_index;   //!
   TBranch        *b__EcalLumiSpecRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__ForwardOffMTrackerRecHits_rawHit_;   //!
   TBranch        *b__ForwardOffMTrackerRecHits_rawHit_index;   //!
   TBranch        *b__ForwardOffMTrackerRecHits_rawHit_collectionID;   //!

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
   TBranch        *b__ForwardRomanPotRecHits_rawHit_;   //!
   TBranch        *b__ForwardRomanPotRecHits_rawHit_index;   //!
   TBranch        *b__ForwardRomanPotRecHits_rawHit_collectionID;   //!

   TBranch        *b_HcalBarrelRecHits_;   //!
   TBranch        *b_HcalBarrelRecHits_cellID;   //!
   TBranch        *b_HcalBarrelRecHits_energy;   //!
   TBranch        *b_HcalBarrelRecHits_energyError;   //!
   TBranch        *b_HcalBarrelRecHits_time;   //!
   TBranch        *b_HcalBarrelRecHits_timeError;   //!
   TBranch        *b_HcalBarrelRecHits_position_x;   //!
   TBranch        *b_HcalBarrelRecHits_position_y;   //!
   TBranch        *b_HcalBarrelRecHits_position_z;   //!
   TBranch        *b_HcalBarrelRecHits_dimension_x;   //!
   TBranch        *b_HcalBarrelRecHits_dimension_y;   //!
   TBranch        *b_HcalBarrelRecHits_dimension_z;   //!
   TBranch        *b_HcalBarrelRecHits_sector;   //!
   TBranch        *b_HcalBarrelRecHits_layer;   //!
   TBranch        *b_HcalBarrelRecHits_local_x;   //!
   TBranch        *b_HcalBarrelRecHits_local_y;   //!
   TBranch        *b_HcalBarrelRecHits_local_z;   //!
   TBranch        *b__HcalBarrelRecHits_rawHit_;   //!
   TBranch        *b__HcalBarrelRecHits_rawHit_index;   //!
   TBranch        *b__HcalBarrelRecHits_rawHit_collectionID;   //!

      TBranch        *b_HcalEndcapNRecHits_;   //!
   TBranch        *b_HcalEndcapNRecHits_cellID;   //!
   TBranch        *b_HcalEndcapNRecHits_energy;   //!
   TBranch        *b_HcalEndcapNRecHits_energyError;   //!
   TBranch        *b_HcalEndcapNRecHits_time;   //!
   TBranch        *b_HcalEndcapNRecHits_timeError;   //!
   TBranch        *b_HcalEndcapNRecHits_position_x;   //!
   TBranch        *b_HcalEndcapNRecHits_position_y;   //!
   TBranch        *b_HcalEndcapNRecHits_position_z;   //!
   TBranch        *b_HcalEndcapNRecHits_dimension_x;   //!
   TBranch        *b_HcalEndcapNRecHits_dimension_y;   //!
   TBranch        *b_HcalEndcapNRecHits_dimension_z;   //!
   TBranch        *b_HcalEndcapNRecHits_sector;   //!
   TBranch        *b_HcalEndcapNRecHits_layer;   //!
   TBranch        *b_HcalEndcapNRecHits_local_x;   //!
   TBranch        *b_HcalEndcapNRecHits_local_y;   //!
   TBranch        *b_HcalEndcapNRecHits_local_z;   //!
   TBranch        *b__HcalEndcapNRecHits_rawHit_;   //!
   TBranch        *b__HcalEndcapNRecHits_rawHit_index;   //!
   TBranch        *b__HcalEndcapNRecHits_rawHit_collectionID;   //!

      TBranch        *b_HcalEndcapPInsertRecHits_;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_cellID;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_energy;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_energyError;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_time;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_timeError;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_position_x;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_position_y;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_position_z;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_dimension_x;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_dimension_y;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_dimension_z;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_sector;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_layer;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_local_x;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_local_y;   //!
   TBranch        *b_HcalEndcapPInsertRecHits_local_z;   //!
   TBranch        *b__HcalEndcapPInsertRecHits_rawHit_;   //!
   TBranch        *b__HcalEndcapPInsertRecHits_rawHit_index;   //!
   TBranch        *b__HcalEndcapPInsertRecHits_rawHit_collectionID;   //!

      TBranch        *b_HcalFarForwardZDCRecHits_;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_cellID;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_energy;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_energyError;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_time;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_timeError;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_position_x;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_position_y;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_position_z;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_dimension_x;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_dimension_y;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_dimension_z;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_sector;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_layer;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_local_x;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_local_y;   //!
   TBranch        *b_HcalFarForwardZDCRecHits_local_z;   //!
   TBranch        *b__HcalFarForwardZDCRecHits_rawHit_;   //!
   TBranch        *b__HcalFarForwardZDCRecHits_rawHit_index;   //!
   TBranch        *b__HcalFarForwardZDCRecHits_rawHit_collectionID;   //!

   TBranch        *b_LFHCALRecHits_;   //!
   TBranch        *b_LFHCALRecHits_cellID;   //!
   TBranch        *b_LFHCALRecHits_energy;   //!
   TBranch        *b_LFHCALRecHits_energyError;   //!
   TBranch        *b_LFHCALRecHits_time;   //!
   TBranch        *b_LFHCALRecHits_timeError;   //!
   TBranch        *b_LFHCALRecHits_position_x;   //!
   TBranch        *b_LFHCALRecHits_position_y;   //!
   TBranch        *b_LFHCALRecHits_position_z;   //!
   TBranch        *b_LFHCALRecHits_dimension_x;   //!
   TBranch        *b_LFHCALRecHits_dimension_y;   //!
   TBranch        *b_LFHCALRecHits_dimension_z;   //!
   TBranch        *b_LFHCALRecHits_sector;   //!
   TBranch        *b_LFHCALRecHits_layer;   //!
   TBranch        *b_LFHCALRecHits_local_x;   //!
   TBranch        *b_LFHCALRecHits_local_y;   //!
   TBranch        *b_LFHCALRecHits_local_z;   //!
   TBranch        *b__LFHCALRecHits_rawHit_;   //!
   TBranch        *b__LFHCALRecHits_rawHit_index;   //!
   TBranch        *b__LFHCALRecHits_rawHit_collectionID;   //!


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

   TString m_simTrackDetNames[9] = \
   {
      "TOFBarrelRecHits", "TOFEndcapRecHits",
      "MPGDBarrelRecHits", "OuterMPGDBarrelRecHits",
      "BackwardMPGDEndcapRecHits", "ForwardMPGDEndcapRecHits",
      "SiBarrelVertexRecHits", "SiBarrelTrackerRecHits",
      "SiEndcapTrackerRecHits"
   };

   TString m_simCalDetNames[8] = \
   {
      "B0TrackerRecHits", "EcalBarrelScFiClusters",
      "EcalEndcapNClusters", "EcalEndcapPClusters",
      "EcalLumiSpecClusters", "ForwardOffMTrackerRecHits",
      "ForwardRomanPotRecHits", "LFHCALClusters"
   };

   std::vector<SimTrackerHitKuma > m_SimTrackerHitsKuma; // a "kuma example" of a member valuable
   std::vector<SimTrackerHitKuma > m_SimCalHitsKuma; // a "kuma example" of a member valuable

   // black, blue, red, green, violet, orange, light blue, light green, dark violet, brown, very light blue, 
   // yellow green, week red, dark blue, week green, dark cyan, dark orange, 
   Int_t m_myHistColors[18] = {4, 600, 632, 419, 880, 807, 867, 909, 814, 874, 635, 870, 824, 625, 602, 417, 434, 802}; // colors for histograms
   
   // TOFBarrelRecHits, TOFEndcapRecHits, BackwardMPGDEndcapRecHits, ForwardMPGDEndcapRecHits, MPGDBarrelRecHits, OuterMPGDBarrelRecHits, SiBarrelVertexRecHits, SiBarrelTrackerRecHits, SiEndcapTrackerRecHits
   Int_t m_TrackDetColors[9] = {880+10, 880+10, 880-2, 880-2, 880-2, 880-2, 880+4, 880+2, 880+2};
   // B0TrackerRecHits, ,  EcalBarrelScFiClusters, EcalEndcapNClusters, EcalEndcapPClusters, EcalFarForwardZDCClusters, EcalLumiSpecClusters, ForwardRomanPotRecHits, LFHCALClusters
   Int_t m_CalDetColors[8] = {860-3, 840-3, 600-9, 600-9, 880+1, 860+10, 880-6, 600-3};
   // B0ECalClusters:  860+7, ,EcalBarrelClusters: 880-4, EcalBarrelImagingClusters: 600-7
   // DIRCRawHits, DRICHRawHits, 
   Int_t m_PIDDetColors[2] = {860-6, 860};
   


   // histograms as output
   TH1D* m_hEDep_BTOF; // histogram for trigger types

   TH1D* m_hTriggerCounts_MAPS; // histogram for trigger types



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
   float m_timeResolution_MPGD = 50.0; // time resolution [ns]
   // float m_timeResolution_TOF = 0.030; // time resolution [ns]
   float m_timeResolution_TOF = 10.0; // time resolution [ns]
   
   float looseFixTimeWidth = 30.0; // [ns], a time width for a loose time cut to find the first physics particle in an event

   bool bInitialLoop = true;
   std::vector<std::vector<unsigned int > > m_vOrigHitId;

   std::vector<std::vector<unsigned int > > m_vSameTSHitId;
   std::vector<std::vector<unsigned int > > m_vOutputHitContainer;


   bool m_bDetLastHits[9] = {false, false, false, false, false, false, false, false, false};

   bool m_bOnceTriggered = false;
   bool m_bScanedAllTimeWindows = false;

   bool m_bOncePhysicsTriggered = false;
   int checkCount = 0;


   // == inherited functions == //
   std::vector<SimTrackerHitKuma> LoadInputTrkHits();
   std::vector<SimTrackerHitKuma> LoadInputCalHits();


};


#endif

// #ifndef eicreconOutputCheck_cxx
// #define eicreconOutputCheck_cxx


// #endif // #ifdef eicreconOutputCheck_cxx





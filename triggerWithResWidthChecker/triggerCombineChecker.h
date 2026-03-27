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

   // Declaration of leaf types
   // "kuma example": you need to write valuables in your input root file.
   // std::vector<int>     *x; //example x
   
   // List of branches
   // "kuma example": you need to write branch in your input root file.
   // TBranch        *b_x;   //! example x


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
   static constexpr Int_t kMaxB0ECalHits = 112;
   static constexpr Int_t kMax_B0ECalHits_contributions = 463403;
   static constexpr Int_t kMaxB0ECalHitsContributions = 463403;
   static constexpr Int_t kMax_B0ECalHitsContributions_particle = 463403;
   static constexpr Int_t kMaxB0TrackerHits = 159;
   static constexpr Int_t kMax_B0TrackerHits_particle = 159;
   static constexpr Int_t kMaxBackwardMPGDEndcapHits = 22;
   static constexpr Int_t kMax_BackwardMPGDEndcapHits_particle = 22;
   static constexpr Int_t kMaxDIRCBarHits = 19710;
   static constexpr Int_t kMax_DIRCBarHits_particle = 19710;
   static constexpr Int_t kMaxDRICHHits = 5875;
   static constexpr Int_t kMax_DRICHHits_particle = 5875;
   static constexpr Int_t kMaxEcalBarrelImagingHits = 710;
   static constexpr Int_t kMax_EcalBarrelImagingHits_contributions = 1966;
   static constexpr Int_t kMaxEcalBarrelImagingHitsContributions = 1966;
   static constexpr Int_t kMax_EcalBarrelImagingHitsContributions_particle = 1966;
   static constexpr Int_t kMaxEcalBarrelScFiHits = 8542;
   static constexpr Int_t kMax_EcalBarrelScFiHits_contributions = 36686;
   static constexpr Int_t kMaxEcalBarrelScFiHitsContributions = 36686;
   static constexpr Int_t kMax_EcalBarrelScFiHitsContributions_particle = 36686;
   static constexpr Int_t kMaxEcalEndcapNHits = 826;
   static constexpr Int_t kMax_EcalEndcapNHits_contributions = 52285;
   static constexpr Int_t kMaxEcalEndcapNHitsContributions = 52285;
   static constexpr Int_t kMax_EcalEndcapNHitsContributions_particle = 52285;
   static constexpr Int_t kMaxEcalEndcapPHits = 2849;
   static constexpr Int_t kMax_EcalEndcapPHits_contributions = 79211;
   static constexpr Int_t kMaxEcalEndcapPHitsContributions = 79211;
   static constexpr Int_t kMax_EcalEndcapPHitsContributions_particle = 79211;
   static constexpr Int_t kMaxEcalEndcapPInsertHits = 478;
   static constexpr Int_t kMax_EcalEndcapPInsertHits_contributions = 110181;
   static constexpr Int_t kMaxEcalEndcapPInsertHitsContributions = 110181;
   static constexpr Int_t kMax_EcalEndcapPInsertHitsContributions_particle = 110181;
   static constexpr Int_t kMaxEcalFarForwardZDCHits = 362;
   static constexpr Int_t kMax_EcalFarForwardZDCHits_contributions = 78485;
   static constexpr Int_t kMaxEcalFarForwardZDCHitsContributions = 78485;
   static constexpr Int_t kMax_EcalFarForwardZDCHitsContributions_particle = 78485;
   static constexpr Int_t kMaxEcalLumiSpecHits = 1;
   static constexpr Int_t kMax_EcalLumiSpecHits_contributions = 1;
   static constexpr Int_t kMaxEcalLumiSpecHitsContributions = 1;
   static constexpr Int_t kMax_EcalLumiSpecHitsContributions_particle = 1;
   static constexpr Int_t kMaxEventHeader = 1;
   static constexpr Int_t kMaxForwardMPGDEndcapHits = 131;
   static constexpr Int_t kMax_ForwardMPGDEndcapHits_particle = 131;
   static constexpr Int_t kMaxForwardOffMTrackerHits = 29;
   static constexpr Int_t kMax_ForwardOffMTrackerHits_particle = 29;
   static constexpr Int_t kMaxForwardRomanPotHits = 157;
   static constexpr Int_t kMax_ForwardRomanPotHits_particle = 157;
   static constexpr Int_t kMaxHcalBarrelHits = 264;
   static constexpr Int_t kMax_HcalBarrelHits_contributions = 1602;
   static constexpr Int_t kMaxHcalBarrelHitsContributions = 1602;
   static constexpr Int_t kMax_HcalBarrelHitsContributions_particle = 1602;
   static constexpr Int_t kMaxHcalEndcapNHits = 261;
   static constexpr Int_t kMax_HcalEndcapNHits_contributions = 990;
   static constexpr Int_t kMaxHcalEndcapNHitsContributions = 990;
   static constexpr Int_t kMax_HcalEndcapNHitsContributions_particle = 990;
   static constexpr Int_t kMaxHcalEndcapPInsertHits = 1758;
   static constexpr Int_t kMax_HcalEndcapPInsertHits_contributions = 7357;
   static constexpr Int_t kMaxHcalEndcapPInsertHitsContributions = 7357;
   static constexpr Int_t kMax_HcalEndcapPInsertHitsContributions_particle = 7357;
   static constexpr Int_t kMaxHcalFarForwardZDCHits = 3755;
   static constexpr Int_t kMax_HcalFarForwardZDCHits_contributions = 30635;
   static constexpr Int_t kMaxHcalFarForwardZDCHitsContributions = 30635;
   static constexpr Int_t kMax_HcalFarForwardZDCHitsContributions_particle = 30635;
   static constexpr Int_t kMaxLFHCALHits = 2401;
   static constexpr Int_t kMax_LFHCALHits_contributions = 6344;
   static constexpr Int_t kMaxLFHCALHitsContributions = 6344;
   static constexpr Int_t kMax_LFHCALHitsContributions_particle = 6344;
   static constexpr Int_t kMaxLumiDirectPCALHits = 1;
   static constexpr Int_t kMax_LumiDirectPCALHits_contributions = 1;
   static constexpr Int_t kMaxLumiDirectPCALHitsContributions = 1;
   static constexpr Int_t kMax_LumiDirectPCALHitsContributions_particle = 1;
   static constexpr Int_t kMaxLumiSpecTrackerHits = 1;
   static constexpr Int_t kMax_LumiSpecTrackerHits_particle = 1;
   static constexpr Int_t kMaxMCParticles = 7979;
   static constexpr Int_t kMax_MCParticles_parents = 7983;
   static constexpr Int_t kMax_MCParticles_daughters = 7983;
   static constexpr Int_t kMaxMPGDBarrelHits = 49;
   static constexpr Int_t kMax_MPGDBarrelHits_particle = 49;
   static constexpr Int_t kMaxOuterMPGDBarrelHits = 46;
   static constexpr Int_t kMax_OuterMPGDBarrelHits_particle = 46;
   static constexpr Int_t kMaxRICHEndcapNHits = 1;
   static constexpr Int_t kMax_RICHEndcapNHits_particle = 1;
   static constexpr Int_t kMaxSiBarrelHits = 26;
   static constexpr Int_t kMax_SiBarrelHits_particle = 26;
   static constexpr Int_t kMaxTaggerTrackerHits = 1;
   static constexpr Int_t kMax_TaggerTrackerHits_particle = 1;
   static constexpr Int_t kMaxTOFBarrelHits = 97;
   static constexpr Int_t kMax_TOFBarrelHits_particle = 97;
   static constexpr Int_t kMaxTOFEndcapHits = 96;
   static constexpr Int_t kMax_TOFEndcapHits_particle = 96;
   static constexpr Int_t kMaxTrackerEndcapHits = 238;
   static constexpr Int_t kMax_TrackerEndcapHits_particle = 238;
   static constexpr Int_t kMaxVertexBarrelHits = 96;
   static constexpr Int_t kMax_VertexBarrelHits_particle = 96;

   // Declaration of leaf types
   Int_t           B0ECalHits_;
   ULong_t         B0ECalHits_cellID[kMaxB0ECalHits];   //[B0ECalHits_]
   Float_t         B0ECalHits_energy[kMaxB0ECalHits];   //[B0ECalHits_]
   Float_t         B0ECalHits_position_x[kMaxB0ECalHits];   //[B0ECalHits_]
   Float_t         B0ECalHits_position_y[kMaxB0ECalHits];   //[B0ECalHits_]
   Float_t         B0ECalHits_position_z[kMaxB0ECalHits];   //[B0ECalHits_]
   UInt_t          B0ECalHits_contributions_begin[kMaxB0ECalHits];   //[B0ECalHits_]
   UInt_t          B0ECalHits_contributions_end[kMaxB0ECalHits];   //[B0ECalHits_]
   Int_t           _B0ECalHits_contributions_;
   Int_t           _B0ECalHits_contributions_index[kMax_B0ECalHits_contributions];   //[_B0ECalHits_contributions_]
   UInt_t          _B0ECalHits_contributions_collectionID[kMax_B0ECalHits_contributions];   //[_B0ECalHits_contributions_]
   Int_t           B0ECalHitsContributions_;
   Int_t           B0ECalHitsContributions_PDG[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
   Float_t         B0ECalHitsContributions_energy[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
   Float_t         B0ECalHitsContributions_time[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
   Float_t         B0ECalHitsContributions_stepPosition_x[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
   Float_t         B0ECalHitsContributions_stepPosition_y[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
   Float_t         B0ECalHitsContributions_stepPosition_z[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
   Int_t           _B0ECalHitsContributions_particle_;
   Int_t           _B0ECalHitsContributions_particle_index[kMax_B0ECalHitsContributions_particle];   //[_B0ECalHitsContributions_particle_]
   UInt_t          _B0ECalHitsContributions_particle_collectionID[kMax_B0ECalHitsContributions_particle];   //[_B0ECalHitsContributions_particle_]
   Int_t           B0TrackerHits_;
   ULong_t         B0TrackerHits_cellID[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Float_t         B0TrackerHits_eDep[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Float_t         B0TrackerHits_time[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Float_t         B0TrackerHits_pathLength[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Int_t           B0TrackerHits_quality[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Double_t        B0TrackerHits_position_x[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Double_t        B0TrackerHits_position_y[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Double_t        B0TrackerHits_position_z[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Float_t         B0TrackerHits_momentum_x[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Float_t         B0TrackerHits_momentum_y[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Float_t         B0TrackerHits_momentum_z[kMaxB0TrackerHits];   //[B0TrackerHits_]
   Int_t           _B0TrackerHits_particle_;
   Int_t           _B0TrackerHits_particle_index[kMax_B0TrackerHits_particle];   //[_B0TrackerHits_particle_]
   UInt_t          _B0TrackerHits_particle_collectionID[kMax_B0TrackerHits_particle];   //[_B0TrackerHits_particle_]
   Int_t           BackwardMPGDEndcapHits_;
   ULong_t         BackwardMPGDEndcapHits_cellID[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Float_t         BackwardMPGDEndcapHits_eDep[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Float_t         BackwardMPGDEndcapHits_time[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Float_t         BackwardMPGDEndcapHits_pathLength[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Int_t           BackwardMPGDEndcapHits_quality[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Double_t        BackwardMPGDEndcapHits_position_x[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Double_t        BackwardMPGDEndcapHits_position_y[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Double_t        BackwardMPGDEndcapHits_position_z[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Float_t         BackwardMPGDEndcapHits_momentum_x[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Float_t         BackwardMPGDEndcapHits_momentum_y[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Float_t         BackwardMPGDEndcapHits_momentum_z[kMaxBackwardMPGDEndcapHits];   //[BackwardMPGDEndcapHits_]
   Int_t           _BackwardMPGDEndcapHits_particle_;
   Int_t           _BackwardMPGDEndcapHits_particle_index[kMax_BackwardMPGDEndcapHits_particle];   //[_BackwardMPGDEndcapHits_particle_]
   UInt_t          _BackwardMPGDEndcapHits_particle_collectionID[kMax_BackwardMPGDEndcapHits_particle];   //[_BackwardMPGDEndcapHits_particle_]
   Int_t           DIRCBarHits_;
   ULong_t         DIRCBarHits_cellID[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Float_t         DIRCBarHits_eDep[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Float_t         DIRCBarHits_time[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Float_t         DIRCBarHits_pathLength[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Int_t           DIRCBarHits_quality[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Double_t        DIRCBarHits_position_x[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Double_t        DIRCBarHits_position_y[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Double_t        DIRCBarHits_position_z[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Float_t         DIRCBarHits_momentum_x[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Float_t         DIRCBarHits_momentum_y[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Float_t         DIRCBarHits_momentum_z[kMaxDIRCBarHits];   //[DIRCBarHits_]
   Int_t           _DIRCBarHits_particle_;
   Int_t           _DIRCBarHits_particle_index[kMax_DIRCBarHits_particle];   //[_DIRCBarHits_particle_]
   UInt_t          _DIRCBarHits_particle_collectionID[kMax_DIRCBarHits_particle];   //[_DIRCBarHits_particle_]
   Int_t           DRICHHits_;
   ULong_t         DRICHHits_cellID[kMaxDRICHHits];   //[DRICHHits_]
   Float_t         DRICHHits_eDep[kMaxDRICHHits];   //[DRICHHits_]
   Float_t         DRICHHits_time[kMaxDRICHHits];   //[DRICHHits_]
   Float_t         DRICHHits_pathLength[kMaxDRICHHits];   //[DRICHHits_]
   Int_t           DRICHHits_quality[kMaxDRICHHits];   //[DRICHHits_]
   Double_t        DRICHHits_position_x[kMaxDRICHHits];   //[DRICHHits_]
   Double_t        DRICHHits_position_y[kMaxDRICHHits];   //[DRICHHits_]
   Double_t        DRICHHits_position_z[kMaxDRICHHits];   //[DRICHHits_]
   Float_t         DRICHHits_momentum_x[kMaxDRICHHits];   //[DRICHHits_]
   Float_t         DRICHHits_momentum_y[kMaxDRICHHits];   //[DRICHHits_]
   Float_t         DRICHHits_momentum_z[kMaxDRICHHits];   //[DRICHHits_]
   Int_t           _DRICHHits_particle_;
   Int_t           _DRICHHits_particle_index[kMax_DRICHHits_particle];   //[_DRICHHits_particle_]
   UInt_t          _DRICHHits_particle_collectionID[kMax_DRICHHits_particle];   //[_DRICHHits_particle_]
   Int_t           EcalBarrelImagingHits_;
   ULong_t         EcalBarrelImagingHits_cellID[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   Float_t         EcalBarrelImagingHits_energy[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   Float_t         EcalBarrelImagingHits_position_x[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   Float_t         EcalBarrelImagingHits_position_y[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   Float_t         EcalBarrelImagingHits_position_z[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   UInt_t          EcalBarrelImagingHits_contributions_begin[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   UInt_t          EcalBarrelImagingHits_contributions_end[kMaxEcalBarrelImagingHits];   //[EcalBarrelImagingHits_]
   Int_t           _EcalBarrelImagingHits_contributions_;
   Int_t           _EcalBarrelImagingHits_contributions_index[kMax_EcalBarrelImagingHits_contributions];   //[_EcalBarrelImagingHits_contributions_]
   UInt_t          _EcalBarrelImagingHits_contributions_collectionID[kMax_EcalBarrelImagingHits_contributions];   //[_EcalBarrelImagingHits_contributions_]
   Int_t           EcalBarrelImagingHitsContributions_;
   Int_t           EcalBarrelImagingHitsContributions_PDG[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
   Float_t         EcalBarrelImagingHitsContributions_energy[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
   Float_t         EcalBarrelImagingHitsContributions_time[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
   Float_t         EcalBarrelImagingHitsContributions_stepPosition_x[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
   Float_t         EcalBarrelImagingHitsContributions_stepPosition_y[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
   Float_t         EcalBarrelImagingHitsContributions_stepPosition_z[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
   Int_t           _EcalBarrelImagingHitsContributions_particle_;
   Int_t           _EcalBarrelImagingHitsContributions_particle_index[kMax_EcalBarrelImagingHitsContributions_particle];   //[_EcalBarrelImagingHitsContributions_particle_]
   UInt_t          _EcalBarrelImagingHitsContributions_particle_collectionID[kMax_EcalBarrelImagingHitsContributions_particle];   //[_EcalBarrelImagingHitsContributions_particle_]
   Int_t           EcalBarrelScFiHits_;
   ULong_t         EcalBarrelScFiHits_cellID[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   Float_t         EcalBarrelScFiHits_energy[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   Float_t         EcalBarrelScFiHits_position_x[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   Float_t         EcalBarrelScFiHits_position_y[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   Float_t         EcalBarrelScFiHits_position_z[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   UInt_t          EcalBarrelScFiHits_contributions_begin[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   UInt_t          EcalBarrelScFiHits_contributions_end[kMaxEcalBarrelScFiHits];   //[EcalBarrelScFiHits_]
   Int_t           _EcalBarrelScFiHits_contributions_;
   Int_t           _EcalBarrelScFiHits_contributions_index[kMax_EcalBarrelScFiHits_contributions];   //[_EcalBarrelScFiHits_contributions_]
   UInt_t          _EcalBarrelScFiHits_contributions_collectionID[kMax_EcalBarrelScFiHits_contributions];   //[_EcalBarrelScFiHits_contributions_]
   Int_t           EcalBarrelScFiHitsContributions_;
   Int_t           EcalBarrelScFiHitsContributions_PDG[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
   Float_t         EcalBarrelScFiHitsContributions_energy[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
   Float_t         EcalBarrelScFiHitsContributions_time[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
   Float_t         EcalBarrelScFiHitsContributions_stepPosition_x[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
   Float_t         EcalBarrelScFiHitsContributions_stepPosition_y[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
   Float_t         EcalBarrelScFiHitsContributions_stepPosition_z[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
   Int_t           _EcalBarrelScFiHitsContributions_particle_;
   Int_t           _EcalBarrelScFiHitsContributions_particle_index[kMax_EcalBarrelScFiHitsContributions_particle];   //[_EcalBarrelScFiHitsContributions_particle_]
   UInt_t          _EcalBarrelScFiHitsContributions_particle_collectionID[kMax_EcalBarrelScFiHitsContributions_particle];   //[_EcalBarrelScFiHitsContributions_particle_]
   Int_t           EcalEndcapNHits_;
   ULong_t         EcalEndcapNHits_cellID[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   Float_t         EcalEndcapNHits_energy[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   Float_t         EcalEndcapNHits_position_x[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   Float_t         EcalEndcapNHits_position_y[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   Float_t         EcalEndcapNHits_position_z[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   UInt_t          EcalEndcapNHits_contributions_begin[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   UInt_t          EcalEndcapNHits_contributions_end[kMaxEcalEndcapNHits];   //[EcalEndcapNHits_]
   Int_t           _EcalEndcapNHits_contributions_;
   Int_t           _EcalEndcapNHits_contributions_index[kMax_EcalEndcapNHits_contributions];   //[_EcalEndcapNHits_contributions_]
   UInt_t          _EcalEndcapNHits_contributions_collectionID[kMax_EcalEndcapNHits_contributions];   //[_EcalEndcapNHits_contributions_]
   Int_t           EcalEndcapNHitsContributions_;
   Int_t           EcalEndcapNHitsContributions_PDG[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
   Float_t         EcalEndcapNHitsContributions_energy[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
   Float_t         EcalEndcapNHitsContributions_time[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
   Float_t         EcalEndcapNHitsContributions_stepPosition_x[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
   Float_t         EcalEndcapNHitsContributions_stepPosition_y[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
   Float_t         EcalEndcapNHitsContributions_stepPosition_z[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
   Int_t           _EcalEndcapNHitsContributions_particle_;
   Int_t           _EcalEndcapNHitsContributions_particle_index[kMax_EcalEndcapNHitsContributions_particle];   //[_EcalEndcapNHitsContributions_particle_]
   UInt_t          _EcalEndcapNHitsContributions_particle_collectionID[kMax_EcalEndcapNHitsContributions_particle];   //[_EcalEndcapNHitsContributions_particle_]
   Int_t           EcalEndcapPHits_;
   ULong_t         EcalEndcapPHits_cellID[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   Float_t         EcalEndcapPHits_energy[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   Float_t         EcalEndcapPHits_position_x[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   Float_t         EcalEndcapPHits_position_y[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   Float_t         EcalEndcapPHits_position_z[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   UInt_t          EcalEndcapPHits_contributions_begin[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   UInt_t          EcalEndcapPHits_contributions_end[kMaxEcalEndcapPHits];   //[EcalEndcapPHits_]
   Int_t           _EcalEndcapPHits_contributions_;
   Int_t           _EcalEndcapPHits_contributions_index[kMax_EcalEndcapPHits_contributions];   //[_EcalEndcapPHits_contributions_]
   UInt_t          _EcalEndcapPHits_contributions_collectionID[kMax_EcalEndcapPHits_contributions];   //[_EcalEndcapPHits_contributions_]
   Int_t           EcalEndcapPHitsContributions_;
   Int_t           EcalEndcapPHitsContributions_PDG[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Float_t         EcalEndcapPHitsContributions_energy[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Float_t         EcalEndcapPHitsContributions_time[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Float_t         EcalEndcapPHitsContributions_stepPosition_x[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Float_t         EcalEndcapPHitsContributions_stepPosition_y[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Float_t         EcalEndcapPHitsContributions_stepPosition_z[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Int_t           _EcalEndcapPHitsContributions_particle_;
   Int_t           _EcalEndcapPHitsContributions_particle_index[kMax_EcalEndcapPHitsContributions_particle];   //[_EcalEndcapPHitsContributions_particle_]
   UInt_t          _EcalEndcapPHitsContributions_particle_collectionID[kMax_EcalEndcapPHitsContributions_particle];   //[_EcalEndcapPHitsContributions_particle_]
   Int_t           EcalEndcapPInsertHits_;
   ULong_t         EcalEndcapPInsertHits_cellID[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   Float_t         EcalEndcapPInsertHits_energy[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   Float_t         EcalEndcapPInsertHits_position_x[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   Float_t         EcalEndcapPInsertHits_position_y[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   Float_t         EcalEndcapPInsertHits_position_z[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   UInt_t          EcalEndcapPInsertHits_contributions_begin[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   UInt_t          EcalEndcapPInsertHits_contributions_end[kMaxEcalEndcapPInsertHits];   //[EcalEndcapPInsertHits_]
   Int_t           _EcalEndcapPInsertHits_contributions_;
   Int_t           _EcalEndcapPInsertHits_contributions_index[kMax_EcalEndcapPInsertHits_contributions];   //[_EcalEndcapPInsertHits_contributions_]
   UInt_t          _EcalEndcapPInsertHits_contributions_collectionID[kMax_EcalEndcapPInsertHits_contributions];   //[_EcalEndcapPInsertHits_contributions_]
   Int_t           EcalEndcapPInsertHitsContributions_;
   Int_t           EcalEndcapPInsertHitsContributions_PDG[kMaxEcalEndcapPInsertHitsContributions];   //[EcalEndcapPInsertHitsContributions_]
   Float_t         EcalEndcapPInsertHitsContributions_energy[kMaxEcalEndcapPInsertHitsContributions];   //[EcalEndcapPInsertHitsContributions_]
   Float_t         EcalEndcapPInsertHitsContributions_time[kMaxEcalEndcapPInsertHitsContributions];   //[EcalEndcapPInsertHitsContributions_]
   Float_t         EcalEndcapPInsertHitsContributions_stepPosition_x[kMaxEcalEndcapPInsertHitsContributions];   //[EcalEndcapPInsertHitsContributions_]
   Float_t         EcalEndcapPInsertHitsContributions_stepPosition_y[kMaxEcalEndcapPInsertHitsContributions];   //[EcalEndcapPInsertHitsContributions_]
   Float_t         EcalEndcapPInsertHitsContributions_stepPosition_z[kMaxEcalEndcapPInsertHitsContributions];   //[EcalEndcapPInsertHitsContributions_]
   Int_t           _EcalEndcapPInsertHitsContributions_particle_;
   Int_t           _EcalEndcapPInsertHitsContributions_particle_index[kMax_EcalEndcapPInsertHitsContributions_particle];   //[_EcalEndcapPInsertHitsContributions_particle_]
   UInt_t          _EcalEndcapPInsertHitsContributions_particle_collectionID[kMax_EcalEndcapPInsertHitsContributions_particle];   //[_EcalEndcapPInsertHitsContributions_particle_]
   Int_t           EcalFarForwardZDCHits_;
   ULong_t         EcalFarForwardZDCHits_cellID[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   Float_t         EcalFarForwardZDCHits_energy[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   Float_t         EcalFarForwardZDCHits_position_x[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   Float_t         EcalFarForwardZDCHits_position_y[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   Float_t         EcalFarForwardZDCHits_position_z[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   UInt_t          EcalFarForwardZDCHits_contributions_begin[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   UInt_t          EcalFarForwardZDCHits_contributions_end[kMaxEcalFarForwardZDCHits];   //[EcalFarForwardZDCHits_]
   Int_t           _EcalFarForwardZDCHits_contributions_;
   Int_t           _EcalFarForwardZDCHits_contributions_index[kMax_EcalFarForwardZDCHits_contributions];   //[_EcalFarForwardZDCHits_contributions_]
   UInt_t          _EcalFarForwardZDCHits_contributions_collectionID[kMax_EcalFarForwardZDCHits_contributions];   //[_EcalFarForwardZDCHits_contributions_]
   Int_t           EcalFarForwardZDCHitsContributions_;
   Int_t           EcalFarForwardZDCHitsContributions_PDG[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
   Float_t         EcalFarForwardZDCHitsContributions_energy[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
   Float_t         EcalFarForwardZDCHitsContributions_time[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
   Float_t         EcalFarForwardZDCHitsContributions_stepPosition_x[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
   Float_t         EcalFarForwardZDCHitsContributions_stepPosition_y[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
   Float_t         EcalFarForwardZDCHitsContributions_stepPosition_z[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
   Int_t           _EcalFarForwardZDCHitsContributions_particle_;
   Int_t           _EcalFarForwardZDCHitsContributions_particle_index[kMax_EcalFarForwardZDCHitsContributions_particle];   //[_EcalFarForwardZDCHitsContributions_particle_]
   UInt_t          _EcalFarForwardZDCHitsContributions_particle_collectionID[kMax_EcalFarForwardZDCHitsContributions_particle];   //[_EcalFarForwardZDCHitsContributions_particle_]
   Int_t           EcalLumiSpecHits_;
   ULong_t         EcalLumiSpecHits_cellID[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   Float_t         EcalLumiSpecHits_energy[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   Float_t         EcalLumiSpecHits_position_x[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   Float_t         EcalLumiSpecHits_position_y[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   Float_t         EcalLumiSpecHits_position_z[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   UInt_t          EcalLumiSpecHits_contributions_begin[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   UInt_t          EcalLumiSpecHits_contributions_end[kMaxEcalLumiSpecHits];   //[EcalLumiSpecHits_]
   Int_t           _EcalLumiSpecHits_contributions_;
   Int_t           _EcalLumiSpecHits_contributions_index[kMax_EcalLumiSpecHits_contributions];   //[_EcalLumiSpecHits_contributions_]
   UInt_t          _EcalLumiSpecHits_contributions_collectionID[kMax_EcalLumiSpecHits_contributions];   //[_EcalLumiSpecHits_contributions_]
   Int_t           EcalLumiSpecHitsContributions_;
   Int_t           EcalLumiSpecHitsContributions_PDG[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Float_t         EcalLumiSpecHitsContributions_energy[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Float_t         EcalLumiSpecHitsContributions_time[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Float_t         EcalLumiSpecHitsContributions_stepPosition_x[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Float_t         EcalLumiSpecHitsContributions_stepPosition_y[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Float_t         EcalLumiSpecHitsContributions_stepPosition_z[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Int_t           _EcalLumiSpecHitsContributions_particle_;
   Int_t           _EcalLumiSpecHitsContributions_particle_index[kMax_EcalLumiSpecHitsContributions_particle];   //[_EcalLumiSpecHitsContributions_particle_]
   UInt_t          _EcalLumiSpecHitsContributions_particle_collectionID[kMax_EcalLumiSpecHitsContributions_particle];   //[_EcalLumiSpecHitsContributions_particle_]
   Int_t           EventHeader_;
   Int_t           EventHeader_eventNumber[kMaxEventHeader];   //[EventHeader_]
   Int_t           EventHeader_runNumber[kMaxEventHeader];   //[EventHeader_]
   ULong_t         EventHeader_timeStamp[kMaxEventHeader];   //[EventHeader_]
   Double_t        EventHeader_weight[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_begin[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_end[kMaxEventHeader];   //[EventHeader_]
   std::vector<double>  *_EventHeader_weights;
   Int_t           ForwardMPGDEndcapHits_;
   ULong_t         ForwardMPGDEndcapHits_cellID[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Float_t         ForwardMPGDEndcapHits_eDep[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Float_t         ForwardMPGDEndcapHits_time[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Float_t         ForwardMPGDEndcapHits_pathLength[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Int_t           ForwardMPGDEndcapHits_quality[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Double_t        ForwardMPGDEndcapHits_position_x[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Double_t        ForwardMPGDEndcapHits_position_y[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Double_t        ForwardMPGDEndcapHits_position_z[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Float_t         ForwardMPGDEndcapHits_momentum_x[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Float_t         ForwardMPGDEndcapHits_momentum_y[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Float_t         ForwardMPGDEndcapHits_momentum_z[kMaxForwardMPGDEndcapHits];   //[ForwardMPGDEndcapHits_]
   Int_t           _ForwardMPGDEndcapHits_particle_;
   Int_t           _ForwardMPGDEndcapHits_particle_index[kMax_ForwardMPGDEndcapHits_particle];   //[_ForwardMPGDEndcapHits_particle_]
   UInt_t          _ForwardMPGDEndcapHits_particle_collectionID[kMax_ForwardMPGDEndcapHits_particle];   //[_ForwardMPGDEndcapHits_particle_]
   Int_t           ForwardOffMTrackerHits_;
   ULong_t         ForwardOffMTrackerHits_cellID[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Float_t         ForwardOffMTrackerHits_eDep[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Float_t         ForwardOffMTrackerHits_time[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Float_t         ForwardOffMTrackerHits_pathLength[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Int_t           ForwardOffMTrackerHits_quality[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Double_t        ForwardOffMTrackerHits_position_x[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Double_t        ForwardOffMTrackerHits_position_y[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Double_t        ForwardOffMTrackerHits_position_z[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Float_t         ForwardOffMTrackerHits_momentum_x[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Float_t         ForwardOffMTrackerHits_momentum_y[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Float_t         ForwardOffMTrackerHits_momentum_z[kMaxForwardOffMTrackerHits];   //[ForwardOffMTrackerHits_]
   Int_t           _ForwardOffMTrackerHits_particle_;
   Int_t           _ForwardOffMTrackerHits_particle_index[kMax_ForwardOffMTrackerHits_particle];   //[_ForwardOffMTrackerHits_particle_]
   UInt_t          _ForwardOffMTrackerHits_particle_collectionID[kMax_ForwardOffMTrackerHits_particle];   //[_ForwardOffMTrackerHits_particle_]
   Int_t           ForwardRomanPotHits_;
   ULong_t         ForwardRomanPotHits_cellID[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Float_t         ForwardRomanPotHits_eDep[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Float_t         ForwardRomanPotHits_time[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Float_t         ForwardRomanPotHits_pathLength[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Int_t           ForwardRomanPotHits_quality[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Double_t        ForwardRomanPotHits_position_x[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Double_t        ForwardRomanPotHits_position_y[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Double_t        ForwardRomanPotHits_position_z[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Float_t         ForwardRomanPotHits_momentum_x[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Float_t         ForwardRomanPotHits_momentum_y[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Float_t         ForwardRomanPotHits_momentum_z[kMaxForwardRomanPotHits];   //[ForwardRomanPotHits_]
   Int_t           _ForwardRomanPotHits_particle_;
   Int_t           _ForwardRomanPotHits_particle_index[kMax_ForwardRomanPotHits_particle];   //[_ForwardRomanPotHits_particle_]
   UInt_t          _ForwardRomanPotHits_particle_collectionID[kMax_ForwardRomanPotHits_particle];   //[_ForwardRomanPotHits_particle_]
   Int_t           HcalBarrelHits_;
   ULong_t         HcalBarrelHits_cellID[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   Float_t         HcalBarrelHits_energy[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   Float_t         HcalBarrelHits_position_x[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   Float_t         HcalBarrelHits_position_y[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   Float_t         HcalBarrelHits_position_z[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   UInt_t          HcalBarrelHits_contributions_begin[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   UInt_t          HcalBarrelHits_contributions_end[kMaxHcalBarrelHits];   //[HcalBarrelHits_]
   Int_t           _HcalBarrelHits_contributions_;
   Int_t           _HcalBarrelHits_contributions_index[kMax_HcalBarrelHits_contributions];   //[_HcalBarrelHits_contributions_]
   UInt_t          _HcalBarrelHits_contributions_collectionID[kMax_HcalBarrelHits_contributions];   //[_HcalBarrelHits_contributions_]
   Int_t           HcalBarrelHitsContributions_;
   Int_t           HcalBarrelHitsContributions_PDG[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
   Float_t         HcalBarrelHitsContributions_energy[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
   Float_t         HcalBarrelHitsContributions_time[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
   Float_t         HcalBarrelHitsContributions_stepPosition_x[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
   Float_t         HcalBarrelHitsContributions_stepPosition_y[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
   Float_t         HcalBarrelHitsContributions_stepPosition_z[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
   Int_t           _HcalBarrelHitsContributions_particle_;
   Int_t           _HcalBarrelHitsContributions_particle_index[kMax_HcalBarrelHitsContributions_particle];   //[_HcalBarrelHitsContributions_particle_]
   UInt_t          _HcalBarrelHitsContributions_particle_collectionID[kMax_HcalBarrelHitsContributions_particle];   //[_HcalBarrelHitsContributions_particle_]
   Int_t           HcalEndcapNHits_;
   ULong_t         HcalEndcapNHits_cellID[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   Float_t         HcalEndcapNHits_energy[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   Float_t         HcalEndcapNHits_position_x[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   Float_t         HcalEndcapNHits_position_y[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   Float_t         HcalEndcapNHits_position_z[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   UInt_t          HcalEndcapNHits_contributions_begin[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   UInt_t          HcalEndcapNHits_contributions_end[kMaxHcalEndcapNHits];   //[HcalEndcapNHits_]
   Int_t           _HcalEndcapNHits_contributions_;
   Int_t           _HcalEndcapNHits_contributions_index[kMax_HcalEndcapNHits_contributions];   //[_HcalEndcapNHits_contributions_]
   UInt_t          _HcalEndcapNHits_contributions_collectionID[kMax_HcalEndcapNHits_contributions];   //[_HcalEndcapNHits_contributions_]
   Int_t           HcalEndcapNHitsContributions_;
   Int_t           HcalEndcapNHitsContributions_PDG[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
   Float_t         HcalEndcapNHitsContributions_energy[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
   Float_t         HcalEndcapNHitsContributions_time[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
   Float_t         HcalEndcapNHitsContributions_stepPosition_x[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
   Float_t         HcalEndcapNHitsContributions_stepPosition_y[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
   Float_t         HcalEndcapNHitsContributions_stepPosition_z[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
   Int_t           _HcalEndcapNHitsContributions_particle_;
   Int_t           _HcalEndcapNHitsContributions_particle_index[kMax_HcalEndcapNHitsContributions_particle];   //[_HcalEndcapNHitsContributions_particle_]
   UInt_t          _HcalEndcapNHitsContributions_particle_collectionID[kMax_HcalEndcapNHitsContributions_particle];   //[_HcalEndcapNHitsContributions_particle_]
   Int_t           HcalEndcapPInsertHits_;
   ULong_t         HcalEndcapPInsertHits_cellID[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   Float_t         HcalEndcapPInsertHits_energy[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   Float_t         HcalEndcapPInsertHits_position_x[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   Float_t         HcalEndcapPInsertHits_position_y[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   Float_t         HcalEndcapPInsertHits_position_z[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   UInt_t          HcalEndcapPInsertHits_contributions_begin[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   UInt_t          HcalEndcapPInsertHits_contributions_end[kMaxHcalEndcapPInsertHits];   //[HcalEndcapPInsertHits_]
   Int_t           _HcalEndcapPInsertHits_contributions_;
   Int_t           _HcalEndcapPInsertHits_contributions_index[kMax_HcalEndcapPInsertHits_contributions];   //[_HcalEndcapPInsertHits_contributions_]
   UInt_t          _HcalEndcapPInsertHits_contributions_collectionID[kMax_HcalEndcapPInsertHits_contributions];   //[_HcalEndcapPInsertHits_contributions_]
   Int_t           HcalEndcapPInsertHitsContributions_;
   Int_t           HcalEndcapPInsertHitsContributions_PDG[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
   Float_t         HcalEndcapPInsertHitsContributions_energy[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
   Float_t         HcalEndcapPInsertHitsContributions_time[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
   Float_t         HcalEndcapPInsertHitsContributions_stepPosition_x[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
   Float_t         HcalEndcapPInsertHitsContributions_stepPosition_y[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
   Float_t         HcalEndcapPInsertHitsContributions_stepPosition_z[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
   Int_t           _HcalEndcapPInsertHitsContributions_particle_;
   Int_t           _HcalEndcapPInsertHitsContributions_particle_index[kMax_HcalEndcapPInsertHitsContributions_particle];   //[_HcalEndcapPInsertHitsContributions_particle_]
   UInt_t          _HcalEndcapPInsertHitsContributions_particle_collectionID[kMax_HcalEndcapPInsertHitsContributions_particle];   //[_HcalEndcapPInsertHitsContributions_particle_]
   Int_t           HcalFarForwardZDCHits_;
   ULong_t         HcalFarForwardZDCHits_cellID[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   Float_t         HcalFarForwardZDCHits_energy[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   Float_t         HcalFarForwardZDCHits_position_x[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   Float_t         HcalFarForwardZDCHits_position_y[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   Float_t         HcalFarForwardZDCHits_position_z[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   UInt_t          HcalFarForwardZDCHits_contributions_begin[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   UInt_t          HcalFarForwardZDCHits_contributions_end[kMaxHcalFarForwardZDCHits];   //[HcalFarForwardZDCHits_]
   Int_t           _HcalFarForwardZDCHits_contributions_;
   Int_t           _HcalFarForwardZDCHits_contributions_index[kMax_HcalFarForwardZDCHits_contributions];   //[_HcalFarForwardZDCHits_contributions_]
   UInt_t          _HcalFarForwardZDCHits_contributions_collectionID[kMax_HcalFarForwardZDCHits_contributions];   //[_HcalFarForwardZDCHits_contributions_]
   Int_t           HcalFarForwardZDCHitsContributions_;
   Int_t           HcalFarForwardZDCHitsContributions_PDG[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
   Float_t         HcalFarForwardZDCHitsContributions_energy[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
   Float_t         HcalFarForwardZDCHitsContributions_time[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
   Float_t         HcalFarForwardZDCHitsContributions_stepPosition_x[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
   Float_t         HcalFarForwardZDCHitsContributions_stepPosition_y[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
   Float_t         HcalFarForwardZDCHitsContributions_stepPosition_z[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
   Int_t           _HcalFarForwardZDCHitsContributions_particle_;
   Int_t           _HcalFarForwardZDCHitsContributions_particle_index[kMax_HcalFarForwardZDCHitsContributions_particle];   //[_HcalFarForwardZDCHitsContributions_particle_]
   UInt_t          _HcalFarForwardZDCHitsContributions_particle_collectionID[kMax_HcalFarForwardZDCHitsContributions_particle];   //[_HcalFarForwardZDCHitsContributions_particle_]
   Int_t           LFHCALHits_;
   ULong_t         LFHCALHits_cellID[kMaxLFHCALHits];   //[LFHCALHits_]
   Float_t         LFHCALHits_energy[kMaxLFHCALHits];   //[LFHCALHits_]
   Float_t         LFHCALHits_position_x[kMaxLFHCALHits];   //[LFHCALHits_]
   Float_t         LFHCALHits_position_y[kMaxLFHCALHits];   //[LFHCALHits_]
   Float_t         LFHCALHits_position_z[kMaxLFHCALHits];   //[LFHCALHits_]
   UInt_t          LFHCALHits_contributions_begin[kMaxLFHCALHits];   //[LFHCALHits_]
   UInt_t          LFHCALHits_contributions_end[kMaxLFHCALHits];   //[LFHCALHits_]
   Int_t           _LFHCALHits_contributions_;
   Int_t           _LFHCALHits_contributions_index[kMax_LFHCALHits_contributions];   //[_LFHCALHits_contributions_]
   UInt_t          _LFHCALHits_contributions_collectionID[kMax_LFHCALHits_contributions];   //[_LFHCALHits_contributions_]
   Int_t           LFHCALHitsContributions_;
   Int_t           LFHCALHitsContributions_PDG[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
   Float_t         LFHCALHitsContributions_energy[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
   Float_t         LFHCALHitsContributions_time[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
   Float_t         LFHCALHitsContributions_stepPosition_x[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
   Float_t         LFHCALHitsContributions_stepPosition_y[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
   Float_t         LFHCALHitsContributions_stepPosition_z[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
   Int_t           _LFHCALHitsContributions_particle_;
   Int_t           _LFHCALHitsContributions_particle_index[kMax_LFHCALHitsContributions_particle];   //[_LFHCALHitsContributions_particle_]
   UInt_t          _LFHCALHitsContributions_particle_collectionID[kMax_LFHCALHitsContributions_particle];   //[_LFHCALHitsContributions_particle_]
   Int_t           LumiDirectPCALHits_;
   ULong_t         LumiDirectPCALHits_cellID[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   Float_t         LumiDirectPCALHits_energy[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   Float_t         LumiDirectPCALHits_position_x[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   Float_t         LumiDirectPCALHits_position_y[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   Float_t         LumiDirectPCALHits_position_z[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   UInt_t          LumiDirectPCALHits_contributions_begin[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   UInt_t          LumiDirectPCALHits_contributions_end[kMaxLumiDirectPCALHits];   //[LumiDirectPCALHits_]
   Int_t           _LumiDirectPCALHits_contributions_;
   Int_t           _LumiDirectPCALHits_contributions_index[kMax_LumiDirectPCALHits_contributions];   //[_LumiDirectPCALHits_contributions_]
   UInt_t          _LumiDirectPCALHits_contributions_collectionID[kMax_LumiDirectPCALHits_contributions];   //[_LumiDirectPCALHits_contributions_]
   Int_t           LumiDirectPCALHitsContributions_;
   Int_t           LumiDirectPCALHitsContributions_PDG[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
   Float_t         LumiDirectPCALHitsContributions_energy[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
   Float_t         LumiDirectPCALHitsContributions_time[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
   Float_t         LumiDirectPCALHitsContributions_stepPosition_x[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
   Float_t         LumiDirectPCALHitsContributions_stepPosition_y[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
   Float_t         LumiDirectPCALHitsContributions_stepPosition_z[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
   Int_t           _LumiDirectPCALHitsContributions_particle_;
   Int_t           _LumiDirectPCALHitsContributions_particle_index[kMax_LumiDirectPCALHitsContributions_particle];   //[_LumiDirectPCALHitsContributions_particle_]
   UInt_t          _LumiDirectPCALHitsContributions_particle_collectionID[kMax_LumiDirectPCALHitsContributions_particle];   //[_LumiDirectPCALHitsContributions_particle_]
   Int_t           LumiSpecTrackerHits_;
   ULong_t         LumiSpecTrackerHits_cellID[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Float_t         LumiSpecTrackerHits_eDep[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Float_t         LumiSpecTrackerHits_time[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Float_t         LumiSpecTrackerHits_pathLength[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Int_t           LumiSpecTrackerHits_quality[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Double_t        LumiSpecTrackerHits_position_x[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Double_t        LumiSpecTrackerHits_position_y[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Double_t        LumiSpecTrackerHits_position_z[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Float_t         LumiSpecTrackerHits_momentum_x[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Float_t         LumiSpecTrackerHits_momentum_y[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Float_t         LumiSpecTrackerHits_momentum_z[kMaxLumiSpecTrackerHits];   //[LumiSpecTrackerHits_]
   Int_t           _LumiSpecTrackerHits_particle_;
   Int_t           _LumiSpecTrackerHits_particle_index[kMax_LumiSpecTrackerHits_particle];   //[_LumiSpecTrackerHits_particle_]
   UInt_t          _LumiSpecTrackerHits_particle_collectionID[kMax_LumiSpecTrackerHits_particle];   //[_LumiSpecTrackerHits_particle_]
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
   Int_t           MPGDBarrelHits_;
   ULong_t         MPGDBarrelHits_cellID[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Float_t         MPGDBarrelHits_eDep[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Float_t         MPGDBarrelHits_time[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Float_t         MPGDBarrelHits_pathLength[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Int_t           MPGDBarrelHits_quality[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Double_t        MPGDBarrelHits_position_x[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Double_t        MPGDBarrelHits_position_y[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Double_t        MPGDBarrelHits_position_z[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Float_t         MPGDBarrelHits_momentum_x[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Float_t         MPGDBarrelHits_momentum_y[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Float_t         MPGDBarrelHits_momentum_z[kMaxMPGDBarrelHits];   //[MPGDBarrelHits_]
   Int_t           _MPGDBarrelHits_particle_;
   Int_t           _MPGDBarrelHits_particle_index[kMax_MPGDBarrelHits_particle];   //[_MPGDBarrelHits_particle_]
   UInt_t          _MPGDBarrelHits_particle_collectionID[kMax_MPGDBarrelHits_particle];   //[_MPGDBarrelHits_particle_]
   Int_t           OuterMPGDBarrelHits_;
   ULong_t         OuterMPGDBarrelHits_cellID[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Float_t         OuterMPGDBarrelHits_eDep[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Float_t         OuterMPGDBarrelHits_time[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Float_t         OuterMPGDBarrelHits_pathLength[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Int_t           OuterMPGDBarrelHits_quality[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Double_t        OuterMPGDBarrelHits_position_x[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Double_t        OuterMPGDBarrelHits_position_y[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Double_t        OuterMPGDBarrelHits_position_z[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Float_t         OuterMPGDBarrelHits_momentum_x[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Float_t         OuterMPGDBarrelHits_momentum_y[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Float_t         OuterMPGDBarrelHits_momentum_z[kMaxOuterMPGDBarrelHits];   //[OuterMPGDBarrelHits_]
   Int_t           _OuterMPGDBarrelHits_particle_;
   Int_t           _OuterMPGDBarrelHits_particle_index[kMax_OuterMPGDBarrelHits_particle];   //[_OuterMPGDBarrelHits_particle_]
   UInt_t          _OuterMPGDBarrelHits_particle_collectionID[kMax_OuterMPGDBarrelHits_particle];   //[_OuterMPGDBarrelHits_particle_]
   Int_t           RICHEndcapNHits_;
   ULong_t         RICHEndcapNHits_cellID[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Float_t         RICHEndcapNHits_eDep[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Float_t         RICHEndcapNHits_time[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Float_t         RICHEndcapNHits_pathLength[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Int_t           RICHEndcapNHits_quality[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Double_t        RICHEndcapNHits_position_x[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Double_t        RICHEndcapNHits_position_y[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Double_t        RICHEndcapNHits_position_z[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Float_t         RICHEndcapNHits_momentum_x[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Float_t         RICHEndcapNHits_momentum_y[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Float_t         RICHEndcapNHits_momentum_z[kMaxRICHEndcapNHits];   //[RICHEndcapNHits_]
   Int_t           _RICHEndcapNHits_particle_;
   Int_t           _RICHEndcapNHits_particle_index[kMax_RICHEndcapNHits_particle];   //[_RICHEndcapNHits_particle_]
   UInt_t          _RICHEndcapNHits_particle_collectionID[kMax_RICHEndcapNHits_particle];   //[_RICHEndcapNHits_particle_]
   Int_t           SiBarrelHits_;
   ULong_t         SiBarrelHits_cellID[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Float_t         SiBarrelHits_eDep[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Float_t         SiBarrelHits_time[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Float_t         SiBarrelHits_pathLength[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Int_t           SiBarrelHits_quality[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Double_t        SiBarrelHits_position_x[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Double_t        SiBarrelHits_position_y[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Double_t        SiBarrelHits_position_z[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Float_t         SiBarrelHits_momentum_x[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Float_t         SiBarrelHits_momentum_y[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Float_t         SiBarrelHits_momentum_z[kMaxSiBarrelHits];   //[SiBarrelHits_]
   Int_t           _SiBarrelHits_particle_;
   Int_t           _SiBarrelHits_particle_index[kMax_SiBarrelHits_particle];   //[_SiBarrelHits_particle_]
   UInt_t          _SiBarrelHits_particle_collectionID[kMax_SiBarrelHits_particle];   //[_SiBarrelHits_particle_]
   Int_t           TaggerTrackerHits_;
   ULong_t         TaggerTrackerHits_cellID[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Float_t         TaggerTrackerHits_eDep[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Float_t         TaggerTrackerHits_time[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Float_t         TaggerTrackerHits_pathLength[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Int_t           TaggerTrackerHits_quality[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Double_t        TaggerTrackerHits_position_x[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Double_t        TaggerTrackerHits_position_y[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Double_t        TaggerTrackerHits_position_z[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Float_t         TaggerTrackerHits_momentum_x[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Float_t         TaggerTrackerHits_momentum_y[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Float_t         TaggerTrackerHits_momentum_z[kMaxTaggerTrackerHits];   //[TaggerTrackerHits_]
   Int_t           _TaggerTrackerHits_particle_;
   Int_t           _TaggerTrackerHits_particle_index[kMax_TaggerTrackerHits_particle];   //[_TaggerTrackerHits_particle_]
   UInt_t          _TaggerTrackerHits_particle_collectionID[kMax_TaggerTrackerHits_particle];   //[_TaggerTrackerHits_particle_]
   Int_t           TOFBarrelHits_;
   ULong_t         TOFBarrelHits_cellID[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Float_t         TOFBarrelHits_eDep[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Float_t         TOFBarrelHits_time[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Float_t         TOFBarrelHits_pathLength[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Int_t           TOFBarrelHits_quality[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Double_t        TOFBarrelHits_position_x[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Double_t        TOFBarrelHits_position_y[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Double_t        TOFBarrelHits_position_z[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Float_t         TOFBarrelHits_momentum_x[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Float_t         TOFBarrelHits_momentum_y[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Float_t         TOFBarrelHits_momentum_z[kMaxTOFBarrelHits];   //[TOFBarrelHits_]
   Int_t           _TOFBarrelHits_particle_;
   Int_t           _TOFBarrelHits_particle_index[kMax_TOFBarrelHits_particle];   //[_TOFBarrelHits_particle_]
   UInt_t          _TOFBarrelHits_particle_collectionID[kMax_TOFBarrelHits_particle];   //[_TOFBarrelHits_particle_]
   Int_t           TOFEndcapHits_;
   ULong_t         TOFEndcapHits_cellID[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Float_t         TOFEndcapHits_eDep[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Float_t         TOFEndcapHits_time[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Float_t         TOFEndcapHits_pathLength[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Int_t           TOFEndcapHits_quality[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Double_t        TOFEndcapHits_position_x[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Double_t        TOFEndcapHits_position_y[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Double_t        TOFEndcapHits_position_z[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Float_t         TOFEndcapHits_momentum_x[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Float_t         TOFEndcapHits_momentum_y[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Float_t         TOFEndcapHits_momentum_z[kMaxTOFEndcapHits];   //[TOFEndcapHits_]
   Int_t           _TOFEndcapHits_particle_;
   Int_t           _TOFEndcapHits_particle_index[kMax_TOFEndcapHits_particle];   //[_TOFEndcapHits_particle_]
   UInt_t          _TOFEndcapHits_particle_collectionID[kMax_TOFEndcapHits_particle];   //[_TOFEndcapHits_particle_]
   Int_t           TrackerEndcapHits_;
   ULong_t         TrackerEndcapHits_cellID[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Float_t         TrackerEndcapHits_eDep[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Float_t         TrackerEndcapHits_time[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Float_t         TrackerEndcapHits_pathLength[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Int_t           TrackerEndcapHits_quality[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Double_t        TrackerEndcapHits_position_x[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Double_t        TrackerEndcapHits_position_y[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Double_t        TrackerEndcapHits_position_z[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Float_t         TrackerEndcapHits_momentum_x[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Float_t         TrackerEndcapHits_momentum_y[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Float_t         TrackerEndcapHits_momentum_z[kMaxTrackerEndcapHits];   //[TrackerEndcapHits_]
   Int_t           _TrackerEndcapHits_particle_;
   Int_t           _TrackerEndcapHits_particle_index[kMax_TrackerEndcapHits_particle];   //[_TrackerEndcapHits_particle_]
   UInt_t          _TrackerEndcapHits_particle_collectionID[kMax_TrackerEndcapHits_particle];   //[_TrackerEndcapHits_particle_]
   Int_t           VertexBarrelHits_;
   ULong_t         VertexBarrelHits_cellID[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Float_t         VertexBarrelHits_eDep[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Float_t         VertexBarrelHits_time[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Float_t         VertexBarrelHits_pathLength[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Int_t           VertexBarrelHits_quality[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Double_t        VertexBarrelHits_position_x[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Double_t        VertexBarrelHits_position_y[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Double_t        VertexBarrelHits_position_z[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Float_t         VertexBarrelHits_momentum_x[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Float_t         VertexBarrelHits_momentum_y[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Float_t         VertexBarrelHits_momentum_z[kMaxVertexBarrelHits];   //[VertexBarrelHits_]
   Int_t           _VertexBarrelHits_particle_;
   Int_t           _VertexBarrelHits_particle_index[kMax_VertexBarrelHits_particle];   //[_VertexBarrelHits_particle_]
   UInt_t          _VertexBarrelHits_particle_collectionID[kMax_VertexBarrelHits_particle];   //[_VertexBarrelHits_particle_]
   std::vector<std::string>  *GPIntKeys;
   std::vector<std::vector<int> > *GPIntValues;
   std::vector<std::string>  *GPFloatKeys;
   std::vector<std::vector<float> > *GPFloatValues;
   std::vector<std::string>  *GPDoubleKeys;
   std::vector<std::vector<double> > *GPDoubleValues;
   std::vector<std::string>  *GPStringKeys;
   std::vector<std::vector<std::string> > *GPStringValues;

   // List of branches
   TBranch        *b_B0ECalHits_;   //!
   TBranch        *b_B0ECalHits_cellID;   //!
   TBranch        *b_B0ECalHits_energy;   //!
   TBranch        *b_B0ECalHits_position_x;   //!
   TBranch        *b_B0ECalHits_position_y;   //!
   TBranch        *b_B0ECalHits_position_z;   //!
   TBranch        *b_B0ECalHits_contributions_begin;   //!
   TBranch        *b_B0ECalHits_contributions_end;   //!
   TBranch        *b__B0ECalHits_contributions_;   //!
   TBranch        *b__B0ECalHits_contributions_index;   //!
   TBranch        *b__B0ECalHits_contributions_collectionID;   //!
   TBranch        *b_B0ECalHitsContributions_;   //!
   TBranch        *b_B0ECalHitsContributions_PDG;   //!
   TBranch        *b_B0ECalHitsContributions_energy;   //!
   TBranch        *b_B0ECalHitsContributions_time;   //!
   TBranch        *b_B0ECalHitsContributions_stepPosition_x;   //!
   TBranch        *b_B0ECalHitsContributions_stepPosition_y;   //!
   TBranch        *b_B0ECalHitsContributions_stepPosition_z;   //!
   TBranch        *b__B0ECalHitsContributions_particle_;   //!
   TBranch        *b__B0ECalHitsContributions_particle_index;   //!
   TBranch        *b__B0ECalHitsContributions_particle_collectionID;   //!
   TBranch        *b_B0TrackerHits_;   //!
   TBranch        *b_B0TrackerHits_cellID;   //!
   TBranch        *b_B0TrackerHits_eDep;   //!
   TBranch        *b_B0TrackerHits_time;   //!
   TBranch        *b_B0TrackerHits_pathLength;   //!
   TBranch        *b_B0TrackerHits_quality;   //!
   TBranch        *b_B0TrackerHits_position_x;   //!
   TBranch        *b_B0TrackerHits_position_y;   //!
   TBranch        *b_B0TrackerHits_position_z;   //!
   TBranch        *b_B0TrackerHits_momentum_x;   //!
   TBranch        *b_B0TrackerHits_momentum_y;   //!
   TBranch        *b_B0TrackerHits_momentum_z;   //!
   TBranch        *b__B0TrackerHits_particle_;   //!
   TBranch        *b__B0TrackerHits_particle_index;   //!
   TBranch        *b__B0TrackerHits_particle_collectionID;   //!
   TBranch        *b_BackwardMPGDEndcapHits_;   //!
   TBranch        *b_BackwardMPGDEndcapHits_cellID;   //!
   TBranch        *b_BackwardMPGDEndcapHits_eDep;   //!
   TBranch        *b_BackwardMPGDEndcapHits_time;   //!
   TBranch        *b_BackwardMPGDEndcapHits_pathLength;   //!
   TBranch        *b_BackwardMPGDEndcapHits_quality;   //!
   TBranch        *b_BackwardMPGDEndcapHits_position_x;   //!
   TBranch        *b_BackwardMPGDEndcapHits_position_y;   //!
   TBranch        *b_BackwardMPGDEndcapHits_position_z;   //!
   TBranch        *b_BackwardMPGDEndcapHits_momentum_x;   //!
   TBranch        *b_BackwardMPGDEndcapHits_momentum_y;   //!
   TBranch        *b_BackwardMPGDEndcapHits_momentum_z;   //!
   TBranch        *b__BackwardMPGDEndcapHits_particle_;   //!
   TBranch        *b__BackwardMPGDEndcapHits_particle_index;   //!
   TBranch        *b__BackwardMPGDEndcapHits_particle_collectionID;   //!
   TBranch        *b_DIRCBarHits_;   //!
   TBranch        *b_DIRCBarHits_cellID;   //!
   TBranch        *b_DIRCBarHits_eDep;   //!
   TBranch        *b_DIRCBarHits_time;   //!
   TBranch        *b_DIRCBarHits_pathLength;   //!
   TBranch        *b_DIRCBarHits_quality;   //!
   TBranch        *b_DIRCBarHits_position_x;   //!
   TBranch        *b_DIRCBarHits_position_y;   //!
   TBranch        *b_DIRCBarHits_position_z;   //!
   TBranch        *b_DIRCBarHits_momentum_x;   //!
   TBranch        *b_DIRCBarHits_momentum_y;   //!
   TBranch        *b_DIRCBarHits_momentum_z;   //!
   TBranch        *b__DIRCBarHits_particle_;   //!
   TBranch        *b__DIRCBarHits_particle_index;   //!
   TBranch        *b__DIRCBarHits_particle_collectionID;   //!
   TBranch        *b_DRICHHits_;   //!
   TBranch        *b_DRICHHits_cellID;   //!
   TBranch        *b_DRICHHits_eDep;   //!
   TBranch        *b_DRICHHits_time;   //!
   TBranch        *b_DRICHHits_pathLength;   //!
   TBranch        *b_DRICHHits_quality;   //!
   TBranch        *b_DRICHHits_position_x;   //!
   TBranch        *b_DRICHHits_position_y;   //!
   TBranch        *b_DRICHHits_position_z;   //!
   TBranch        *b_DRICHHits_momentum_x;   //!
   TBranch        *b_DRICHHits_momentum_y;   //!
   TBranch        *b_DRICHHits_momentum_z;   //!
   TBranch        *b__DRICHHits_particle_;   //!
   TBranch        *b__DRICHHits_particle_index;   //!
   TBranch        *b__DRICHHits_particle_collectionID;   //!
   TBranch        *b_EcalBarrelImagingHits_;   //!
   TBranch        *b_EcalBarrelImagingHits_cellID;   //!
   TBranch        *b_EcalBarrelImagingHits_energy;   //!
   TBranch        *b_EcalBarrelImagingHits_position_x;   //!
   TBranch        *b_EcalBarrelImagingHits_position_y;   //!
   TBranch        *b_EcalBarrelImagingHits_position_z;   //!
   TBranch        *b_EcalBarrelImagingHits_contributions_begin;   //!
   TBranch        *b_EcalBarrelImagingHits_contributions_end;   //!
   TBranch        *b__EcalBarrelImagingHits_contributions_;   //!
   TBranch        *b__EcalBarrelImagingHits_contributions_index;   //!
   TBranch        *b__EcalBarrelImagingHits_contributions_collectionID;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_PDG;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_energy;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_time;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalBarrelImagingHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalBarrelImagingHitsContributions_particle_;   //!
   TBranch        *b__EcalBarrelImagingHitsContributions_particle_index;   //!
   TBranch        *b__EcalBarrelImagingHitsContributions_particle_collectionID;   //!
   TBranch        *b_EcalBarrelScFiHits_;   //!
   TBranch        *b_EcalBarrelScFiHits_cellID;   //!
   TBranch        *b_EcalBarrelScFiHits_energy;   //!
   TBranch        *b_EcalBarrelScFiHits_position_x;   //!
   TBranch        *b_EcalBarrelScFiHits_position_y;   //!
   TBranch        *b_EcalBarrelScFiHits_position_z;   //!
   TBranch        *b_EcalBarrelScFiHits_contributions_begin;   //!
   TBranch        *b_EcalBarrelScFiHits_contributions_end;   //!
   TBranch        *b__EcalBarrelScFiHits_contributions_;   //!
   TBranch        *b__EcalBarrelScFiHits_contributions_index;   //!
   TBranch        *b__EcalBarrelScFiHits_contributions_collectionID;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_PDG;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_energy;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_time;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalBarrelScFiHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalBarrelScFiHitsContributions_particle_;   //!
   TBranch        *b__EcalBarrelScFiHitsContributions_particle_index;   //!
   TBranch        *b__EcalBarrelScFiHitsContributions_particle_collectionID;   //!
   TBranch        *b_EcalEndcapNHits_;   //!
   TBranch        *b_EcalEndcapNHits_cellID;   //!
   TBranch        *b_EcalEndcapNHits_energy;   //!
   TBranch        *b_EcalEndcapNHits_position_x;   //!
   TBranch        *b_EcalEndcapNHits_position_y;   //!
   TBranch        *b_EcalEndcapNHits_position_z;   //!
   TBranch        *b_EcalEndcapNHits_contributions_begin;   //!
   TBranch        *b_EcalEndcapNHits_contributions_end;   //!
   TBranch        *b__EcalEndcapNHits_contributions_;   //!
   TBranch        *b__EcalEndcapNHits_contributions_index;   //!
   TBranch        *b__EcalEndcapNHits_contributions_collectionID;   //!
   TBranch        *b_EcalEndcapNHitsContributions_;   //!
   TBranch        *b_EcalEndcapNHitsContributions_PDG;   //!
   TBranch        *b_EcalEndcapNHitsContributions_energy;   //!
   TBranch        *b_EcalEndcapNHitsContributions_time;   //!
   TBranch        *b_EcalEndcapNHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalEndcapNHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalEndcapNHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalEndcapNHitsContributions_particle_;   //!
   TBranch        *b__EcalEndcapNHitsContributions_particle_index;   //!
   TBranch        *b__EcalEndcapNHitsContributions_particle_collectionID;   //!
   TBranch        *b_EcalEndcapPHits_;   //!
   TBranch        *b_EcalEndcapPHits_cellID;   //!
   TBranch        *b_EcalEndcapPHits_energy;   //!
   TBranch        *b_EcalEndcapPHits_position_x;   //!
   TBranch        *b_EcalEndcapPHits_position_y;   //!
   TBranch        *b_EcalEndcapPHits_position_z;   //!
   TBranch        *b_EcalEndcapPHits_contributions_begin;   //!
   TBranch        *b_EcalEndcapPHits_contributions_end;   //!
   TBranch        *b__EcalEndcapPHits_contributions_;   //!
   TBranch        *b__EcalEndcapPHits_contributions_index;   //!
   TBranch        *b__EcalEndcapPHits_contributions_collectionID;   //!
   TBranch        *b_EcalEndcapPHitsContributions_;   //!
   TBranch        *b_EcalEndcapPHitsContributions_PDG;   //!
   TBranch        *b_EcalEndcapPHitsContributions_energy;   //!
   TBranch        *b_EcalEndcapPHitsContributions_time;   //!
   TBranch        *b_EcalEndcapPHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalEndcapPHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalEndcapPHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalEndcapPHitsContributions_particle_;   //!
   TBranch        *b__EcalEndcapPHitsContributions_particle_index;   //!
   TBranch        *b__EcalEndcapPHitsContributions_particle_collectionID;   //!
   TBranch        *b_EcalEndcapPInsertHits_;   //!
   TBranch        *b_EcalEndcapPInsertHits_cellID;   //!
   TBranch        *b_EcalEndcapPInsertHits_energy;   //!
   TBranch        *b_EcalEndcapPInsertHits_position_x;   //!
   TBranch        *b_EcalEndcapPInsertHits_position_y;   //!
   TBranch        *b_EcalEndcapPInsertHits_position_z;   //!
   TBranch        *b_EcalEndcapPInsertHits_contributions_begin;   //!
   TBranch        *b_EcalEndcapPInsertHits_contributions_end;   //!
   TBranch        *b__EcalEndcapPInsertHits_contributions_;   //!
   TBranch        *b__EcalEndcapPInsertHits_contributions_index;   //!
   TBranch        *b__EcalEndcapPInsertHits_contributions_collectionID;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_PDG;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_energy;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_time;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalEndcapPInsertHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalEndcapPInsertHitsContributions_particle_;   //!
   TBranch        *b__EcalEndcapPInsertHitsContributions_particle_index;   //!
   TBranch        *b__EcalEndcapPInsertHitsContributions_particle_collectionID;   //!
   TBranch        *b_EcalFarForwardZDCHits_;   //!
   TBranch        *b_EcalFarForwardZDCHits_cellID;   //!
   TBranch        *b_EcalFarForwardZDCHits_energy;   //!
   TBranch        *b_EcalFarForwardZDCHits_position_x;   //!
   TBranch        *b_EcalFarForwardZDCHits_position_y;   //!
   TBranch        *b_EcalFarForwardZDCHits_position_z;   //!
   TBranch        *b_EcalFarForwardZDCHits_contributions_begin;   //!
   TBranch        *b_EcalFarForwardZDCHits_contributions_end;   //!
   TBranch        *b__EcalFarForwardZDCHits_contributions_;   //!
   TBranch        *b__EcalFarForwardZDCHits_contributions_index;   //!
   TBranch        *b__EcalFarForwardZDCHits_contributions_collectionID;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_PDG;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_energy;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_time;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalFarForwardZDCHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalFarForwardZDCHitsContributions_particle_;   //!
   TBranch        *b__EcalFarForwardZDCHitsContributions_particle_index;   //!
   TBranch        *b__EcalFarForwardZDCHitsContributions_particle_collectionID;   //!
   TBranch        *b_EcalLumiSpecHits_;   //!
   TBranch        *b_EcalLumiSpecHits_cellID;   //!
   TBranch        *b_EcalLumiSpecHits_energy;   //!
   TBranch        *b_EcalLumiSpecHits_position_x;   //!
   TBranch        *b_EcalLumiSpecHits_position_y;   //!
   TBranch        *b_EcalLumiSpecHits_position_z;   //!
   TBranch        *b_EcalLumiSpecHits_contributions_begin;   //!
   TBranch        *b_EcalLumiSpecHits_contributions_end;   //!
   TBranch        *b__EcalLumiSpecHits_contributions_;   //!
   TBranch        *b__EcalLumiSpecHits_contributions_index;   //!
   TBranch        *b__EcalLumiSpecHits_contributions_collectionID;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_PDG;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_energy;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_time;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_stepPosition_x;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_stepPosition_y;   //!
   TBranch        *b_EcalLumiSpecHitsContributions_stepPosition_z;   //!
   TBranch        *b__EcalLumiSpecHitsContributions_particle_;   //!
   TBranch        *b__EcalLumiSpecHitsContributions_particle_index;   //!
   TBranch        *b__EcalLumiSpecHitsContributions_particle_collectionID;   //!
   TBranch        *b_EventHeader_;   //!
   TBranch        *b_EventHeader_eventNumber;   //!
   TBranch        *b_EventHeader_runNumber;   //!
   TBranch        *b_EventHeader_timeStamp;   //!
   TBranch        *b_EventHeader_weight;   //!
   TBranch        *b_EventHeader_weights_begin;   //!
   TBranch        *b_EventHeader_weights_end;   //!
   TBranch        *b__EventHeader_weights;   //!
   TBranch        *b_ForwardMPGDEndcapHits_;   //!
   TBranch        *b_ForwardMPGDEndcapHits_cellID;   //!
   TBranch        *b_ForwardMPGDEndcapHits_eDep;   //!
   TBranch        *b_ForwardMPGDEndcapHits_time;   //!
   TBranch        *b_ForwardMPGDEndcapHits_pathLength;   //!
   TBranch        *b_ForwardMPGDEndcapHits_quality;   //!
   TBranch        *b_ForwardMPGDEndcapHits_position_x;   //!
   TBranch        *b_ForwardMPGDEndcapHits_position_y;   //!
   TBranch        *b_ForwardMPGDEndcapHits_position_z;   //!
   TBranch        *b_ForwardMPGDEndcapHits_momentum_x;   //!
   TBranch        *b_ForwardMPGDEndcapHits_momentum_y;   //!
   TBranch        *b_ForwardMPGDEndcapHits_momentum_z;   //!
   TBranch        *b__ForwardMPGDEndcapHits_particle_;   //!
   TBranch        *b__ForwardMPGDEndcapHits_particle_index;   //!
   TBranch        *b__ForwardMPGDEndcapHits_particle_collectionID;   //!
   TBranch        *b_ForwardOffMTrackerHits_;   //!
   TBranch        *b_ForwardOffMTrackerHits_cellID;   //!
   TBranch        *b_ForwardOffMTrackerHits_eDep;   //!
   TBranch        *b_ForwardOffMTrackerHits_time;   //!
   TBranch        *b_ForwardOffMTrackerHits_pathLength;   //!
   TBranch        *b_ForwardOffMTrackerHits_quality;   //!
   TBranch        *b_ForwardOffMTrackerHits_position_x;   //!
   TBranch        *b_ForwardOffMTrackerHits_position_y;   //!
   TBranch        *b_ForwardOffMTrackerHits_position_z;   //!
   TBranch        *b_ForwardOffMTrackerHits_momentum_x;   //!
   TBranch        *b_ForwardOffMTrackerHits_momentum_y;   //!
   TBranch        *b_ForwardOffMTrackerHits_momentum_z;   //!
   TBranch        *b__ForwardOffMTrackerHits_particle_;   //!
   TBranch        *b__ForwardOffMTrackerHits_particle_index;   //!
   TBranch        *b__ForwardOffMTrackerHits_particle_collectionID;   //!
   TBranch        *b_ForwardRomanPotHits_;   //!
   TBranch        *b_ForwardRomanPotHits_cellID;   //!
   TBranch        *b_ForwardRomanPotHits_eDep;   //!
   TBranch        *b_ForwardRomanPotHits_time;   //!
   TBranch        *b_ForwardRomanPotHits_pathLength;   //!
   TBranch        *b_ForwardRomanPotHits_quality;   //!
   TBranch        *b_ForwardRomanPotHits_position_x;   //!
   TBranch        *b_ForwardRomanPotHits_position_y;   //!
   TBranch        *b_ForwardRomanPotHits_position_z;   //!
   TBranch        *b_ForwardRomanPotHits_momentum_x;   //!
   TBranch        *b_ForwardRomanPotHits_momentum_y;   //!
   TBranch        *b_ForwardRomanPotHits_momentum_z;   //!
   TBranch        *b__ForwardRomanPotHits_particle_;   //!
   TBranch        *b__ForwardRomanPotHits_particle_index;   //!
   TBranch        *b__ForwardRomanPotHits_particle_collectionID;   //!
   TBranch        *b_HcalBarrelHits_;   //!
   TBranch        *b_HcalBarrelHits_cellID;   //!
   TBranch        *b_HcalBarrelHits_energy;   //!
   TBranch        *b_HcalBarrelHits_position_x;   //!
   TBranch        *b_HcalBarrelHits_position_y;   //!
   TBranch        *b_HcalBarrelHits_position_z;   //!
   TBranch        *b_HcalBarrelHits_contributions_begin;   //!
   TBranch        *b_HcalBarrelHits_contributions_end;   //!
   TBranch        *b__HcalBarrelHits_contributions_;   //!
   TBranch        *b__HcalBarrelHits_contributions_index;   //!
   TBranch        *b__HcalBarrelHits_contributions_collectionID;   //!
   TBranch        *b_HcalBarrelHitsContributions_;   //!
   TBranch        *b_HcalBarrelHitsContributions_PDG;   //!
   TBranch        *b_HcalBarrelHitsContributions_energy;   //!
   TBranch        *b_HcalBarrelHitsContributions_time;   //!
   TBranch        *b_HcalBarrelHitsContributions_stepPosition_x;   //!
   TBranch        *b_HcalBarrelHitsContributions_stepPosition_y;   //!
   TBranch        *b_HcalBarrelHitsContributions_stepPosition_z;   //!
   TBranch        *b__HcalBarrelHitsContributions_particle_;   //!
   TBranch        *b__HcalBarrelHitsContributions_particle_index;   //!
   TBranch        *b__HcalBarrelHitsContributions_particle_collectionID;   //!
   TBranch        *b_HcalEndcapNHits_;   //!
   TBranch        *b_HcalEndcapNHits_cellID;   //!
   TBranch        *b_HcalEndcapNHits_energy;   //!
   TBranch        *b_HcalEndcapNHits_position_x;   //!
   TBranch        *b_HcalEndcapNHits_position_y;   //!
   TBranch        *b_HcalEndcapNHits_position_z;   //!
   TBranch        *b_HcalEndcapNHits_contributions_begin;   //!
   TBranch        *b_HcalEndcapNHits_contributions_end;   //!
   TBranch        *b__HcalEndcapNHits_contributions_;   //!
   TBranch        *b__HcalEndcapNHits_contributions_index;   //!
   TBranch        *b__HcalEndcapNHits_contributions_collectionID;   //!
   TBranch        *b_HcalEndcapNHitsContributions_;   //!
   TBranch        *b_HcalEndcapNHitsContributions_PDG;   //!
   TBranch        *b_HcalEndcapNHitsContributions_energy;   //!
   TBranch        *b_HcalEndcapNHitsContributions_time;   //!
   TBranch        *b_HcalEndcapNHitsContributions_stepPosition_x;   //!
   TBranch        *b_HcalEndcapNHitsContributions_stepPosition_y;   //!
   TBranch        *b_HcalEndcapNHitsContributions_stepPosition_z;   //!
   TBranch        *b__HcalEndcapNHitsContributions_particle_;   //!
   TBranch        *b__HcalEndcapNHitsContributions_particle_index;   //!
   TBranch        *b__HcalEndcapNHitsContributions_particle_collectionID;   //!
   TBranch        *b_HcalEndcapPInsertHits_;   //!
   TBranch        *b_HcalEndcapPInsertHits_cellID;   //!
   TBranch        *b_HcalEndcapPInsertHits_energy;   //!
   TBranch        *b_HcalEndcapPInsertHits_position_x;   //!
   TBranch        *b_HcalEndcapPInsertHits_position_y;   //!
   TBranch        *b_HcalEndcapPInsertHits_position_z;   //!
   TBranch        *b_HcalEndcapPInsertHits_contributions_begin;   //!
   TBranch        *b_HcalEndcapPInsertHits_contributions_end;   //!
   TBranch        *b__HcalEndcapPInsertHits_contributions_;   //!
   TBranch        *b__HcalEndcapPInsertHits_contributions_index;   //!
   TBranch        *b__HcalEndcapPInsertHits_contributions_collectionID;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_PDG;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_energy;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_time;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_stepPosition_x;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_stepPosition_y;   //!
   TBranch        *b_HcalEndcapPInsertHitsContributions_stepPosition_z;   //!
   TBranch        *b__HcalEndcapPInsertHitsContributions_particle_;   //!
   TBranch        *b__HcalEndcapPInsertHitsContributions_particle_index;   //!
   TBranch        *b__HcalEndcapPInsertHitsContributions_particle_collectionID;   //!
   TBranch        *b_HcalFarForwardZDCHits_;   //!
   TBranch        *b_HcalFarForwardZDCHits_cellID;   //!
   TBranch        *b_HcalFarForwardZDCHits_energy;   //!
   TBranch        *b_HcalFarForwardZDCHits_position_x;   //!
   TBranch        *b_HcalFarForwardZDCHits_position_y;   //!
   TBranch        *b_HcalFarForwardZDCHits_position_z;   //!
   TBranch        *b_HcalFarForwardZDCHits_contributions_begin;   //!
   TBranch        *b_HcalFarForwardZDCHits_contributions_end;   //!
   TBranch        *b__HcalFarForwardZDCHits_contributions_;   //!
   TBranch        *b__HcalFarForwardZDCHits_contributions_index;   //!
   TBranch        *b__HcalFarForwardZDCHits_contributions_collectionID;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_PDG;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_energy;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_time;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_stepPosition_x;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_stepPosition_y;   //!
   TBranch        *b_HcalFarForwardZDCHitsContributions_stepPosition_z;   //!
   TBranch        *b__HcalFarForwardZDCHitsContributions_particle_;   //!
   TBranch        *b__HcalFarForwardZDCHitsContributions_particle_index;   //!
   TBranch        *b__HcalFarForwardZDCHitsContributions_particle_collectionID;   //!
   TBranch        *b_LFHCALHits_;   //!
   TBranch        *b_LFHCALHits_cellID;   //!
   TBranch        *b_LFHCALHits_energy;   //!
   TBranch        *b_LFHCALHits_position_x;   //!
   TBranch        *b_LFHCALHits_position_y;   //!
   TBranch        *b_LFHCALHits_position_z;   //!
   TBranch        *b_LFHCALHits_contributions_begin;   //!
   TBranch        *b_LFHCALHits_contributions_end;   //!
   TBranch        *b__LFHCALHits_contributions_;   //!
   TBranch        *b__LFHCALHits_contributions_index;   //!
   TBranch        *b__LFHCALHits_contributions_collectionID;   //!
   TBranch        *b_LFHCALHitsContributions_;   //!
   TBranch        *b_LFHCALHitsContributions_PDG;   //!
   TBranch        *b_LFHCALHitsContributions_energy;   //!
   TBranch        *b_LFHCALHitsContributions_time;   //!
   TBranch        *b_LFHCALHitsContributions_stepPosition_x;   //!
   TBranch        *b_LFHCALHitsContributions_stepPosition_y;   //!
   TBranch        *b_LFHCALHitsContributions_stepPosition_z;   //!
   TBranch        *b__LFHCALHitsContributions_particle_;   //!
   TBranch        *b__LFHCALHitsContributions_particle_index;   //!
   TBranch        *b__LFHCALHitsContributions_particle_collectionID;   //!
   TBranch        *b_LumiDirectPCALHits_;   //!
   TBranch        *b_LumiDirectPCALHits_cellID;   //!
   TBranch        *b_LumiDirectPCALHits_energy;   //!
   TBranch        *b_LumiDirectPCALHits_position_x;   //!
   TBranch        *b_LumiDirectPCALHits_position_y;   //!
   TBranch        *b_LumiDirectPCALHits_position_z;   //!
   TBranch        *b_LumiDirectPCALHits_contributions_begin;   //!
   TBranch        *b_LumiDirectPCALHits_contributions_end;   //!
   TBranch        *b__LumiDirectPCALHits_contributions_;   //!
   TBranch        *b__LumiDirectPCALHits_contributions_index;   //!
   TBranch        *b__LumiDirectPCALHits_contributions_collectionID;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_PDG;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_energy;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_time;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_stepPosition_x;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_stepPosition_y;   //!
   TBranch        *b_LumiDirectPCALHitsContributions_stepPosition_z;   //!
   TBranch        *b__LumiDirectPCALHitsContributions_particle_;   //!
   TBranch        *b__LumiDirectPCALHitsContributions_particle_index;   //!
   TBranch        *b__LumiDirectPCALHitsContributions_particle_collectionID;   //!
   TBranch        *b_LumiSpecTrackerHits_;   //!
   TBranch        *b_LumiSpecTrackerHits_cellID;   //!
   TBranch        *b_LumiSpecTrackerHits_eDep;   //!
   TBranch        *b_LumiSpecTrackerHits_time;   //!
   TBranch        *b_LumiSpecTrackerHits_pathLength;   //!
   TBranch        *b_LumiSpecTrackerHits_quality;   //!
   TBranch        *b_LumiSpecTrackerHits_position_x;   //!
   TBranch        *b_LumiSpecTrackerHits_position_y;   //!
   TBranch        *b_LumiSpecTrackerHits_position_z;   //!
   TBranch        *b_LumiSpecTrackerHits_momentum_x;   //!
   TBranch        *b_LumiSpecTrackerHits_momentum_y;   //!
   TBranch        *b_LumiSpecTrackerHits_momentum_z;   //!
   TBranch        *b__LumiSpecTrackerHits_particle_;   //!
   TBranch        *b__LumiSpecTrackerHits_particle_index;   //!
   TBranch        *b__LumiSpecTrackerHits_particle_collectionID;   //!
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
   TBranch        *b_MPGDBarrelHits_;   //!
   TBranch        *b_MPGDBarrelHits_cellID;   //!
   TBranch        *b_MPGDBarrelHits_eDep;   //!
   TBranch        *b_MPGDBarrelHits_time;   //!
   TBranch        *b_MPGDBarrelHits_pathLength;   //!
   TBranch        *b_MPGDBarrelHits_quality;   //!
   TBranch        *b_MPGDBarrelHits_position_x;   //!
   TBranch        *b_MPGDBarrelHits_position_y;   //!
   TBranch        *b_MPGDBarrelHits_position_z;   //!
   TBranch        *b_MPGDBarrelHits_momentum_x;   //!
   TBranch        *b_MPGDBarrelHits_momentum_y;   //!
   TBranch        *b_MPGDBarrelHits_momentum_z;   //!
   TBranch        *b__MPGDBarrelHits_particle_;   //!
   TBranch        *b__MPGDBarrelHits_particle_index;   //!
   TBranch        *b__MPGDBarrelHits_particle_collectionID;   //!
   TBranch        *b_OuterMPGDBarrelHits_;   //!
   TBranch        *b_OuterMPGDBarrelHits_cellID;   //!
   TBranch        *b_OuterMPGDBarrelHits_eDep;   //!
   TBranch        *b_OuterMPGDBarrelHits_time;   //!
   TBranch        *b_OuterMPGDBarrelHits_pathLength;   //!
   TBranch        *b_OuterMPGDBarrelHits_quality;   //!
   TBranch        *b_OuterMPGDBarrelHits_position_x;   //!
   TBranch        *b_OuterMPGDBarrelHits_position_y;   //!
   TBranch        *b_OuterMPGDBarrelHits_position_z;   //!
   TBranch        *b_OuterMPGDBarrelHits_momentum_x;   //!
   TBranch        *b_OuterMPGDBarrelHits_momentum_y;   //!
   TBranch        *b_OuterMPGDBarrelHits_momentum_z;   //!
   TBranch        *b__OuterMPGDBarrelHits_particle_;   //!
   TBranch        *b__OuterMPGDBarrelHits_particle_index;   //!
   TBranch        *b__OuterMPGDBarrelHits_particle_collectionID;   //!
   TBranch        *b_RICHEndcapNHits_;   //!
   TBranch        *b_RICHEndcapNHits_cellID;   //!
   TBranch        *b_RICHEndcapNHits_eDep;   //!
   TBranch        *b_RICHEndcapNHits_time;   //!
   TBranch        *b_RICHEndcapNHits_pathLength;   //!
   TBranch        *b_RICHEndcapNHits_quality;   //!
   TBranch        *b_RICHEndcapNHits_position_x;   //!
   TBranch        *b_RICHEndcapNHits_position_y;   //!
   TBranch        *b_RICHEndcapNHits_position_z;   //!
   TBranch        *b_RICHEndcapNHits_momentum_x;   //!
   TBranch        *b_RICHEndcapNHits_momentum_y;   //!
   TBranch        *b_RICHEndcapNHits_momentum_z;   //!
   TBranch        *b__RICHEndcapNHits_particle_;   //!
   TBranch        *b__RICHEndcapNHits_particle_index;   //!
   TBranch        *b__RICHEndcapNHits_particle_collectionID;   //!
   TBranch        *b_SiBarrelHits_;   //!
   TBranch        *b_SiBarrelHits_cellID;   //!
   TBranch        *b_SiBarrelHits_eDep;   //!
   TBranch        *b_SiBarrelHits_time;   //!
   TBranch        *b_SiBarrelHits_pathLength;   //!
   TBranch        *b_SiBarrelHits_quality;   //!
   TBranch        *b_SiBarrelHits_position_x;   //!
   TBranch        *b_SiBarrelHits_position_y;   //!
   TBranch        *b_SiBarrelHits_position_z;   //!
   TBranch        *b_SiBarrelHits_momentum_x;   //!
   TBranch        *b_SiBarrelHits_momentum_y;   //!
   TBranch        *b_SiBarrelHits_momentum_z;   //!
   TBranch        *b__SiBarrelHits_particle_;   //!
   TBranch        *b__SiBarrelHits_particle_index;   //!
   TBranch        *b__SiBarrelHits_particle_collectionID;   //!
   TBranch        *b_TaggerTrackerHits_;   //!
   TBranch        *b_TaggerTrackerHits_cellID;   //!
   TBranch        *b_TaggerTrackerHits_eDep;   //!
   TBranch        *b_TaggerTrackerHits_time;   //!
   TBranch        *b_TaggerTrackerHits_pathLength;   //!
   TBranch        *b_TaggerTrackerHits_quality;   //!
   TBranch        *b_TaggerTrackerHits_position_x;   //!
   TBranch        *b_TaggerTrackerHits_position_y;   //!
   TBranch        *b_TaggerTrackerHits_position_z;   //!
   TBranch        *b_TaggerTrackerHits_momentum_x;   //!
   TBranch        *b_TaggerTrackerHits_momentum_y;   //!
   TBranch        *b_TaggerTrackerHits_momentum_z;   //!
   TBranch        *b__TaggerTrackerHits_particle_;   //!
   TBranch        *b__TaggerTrackerHits_particle_index;   //!
   TBranch        *b__TaggerTrackerHits_particle_collectionID;   //!
   TBranch        *b_TOFBarrelHits_;   //!
   TBranch        *b_TOFBarrelHits_cellID;   //!
   TBranch        *b_TOFBarrelHits_eDep;   //!
   TBranch        *b_TOFBarrelHits_time;   //!
   TBranch        *b_TOFBarrelHits_pathLength;   //!
   TBranch        *b_TOFBarrelHits_quality;   //!
   TBranch        *b_TOFBarrelHits_position_x;   //!
   TBranch        *b_TOFBarrelHits_position_y;   //!
   TBranch        *b_TOFBarrelHits_position_z;   //!
   TBranch        *b_TOFBarrelHits_momentum_x;   //!
   TBranch        *b_TOFBarrelHits_momentum_y;   //!
   TBranch        *b_TOFBarrelHits_momentum_z;   //!
   TBranch        *b__TOFBarrelHits_particle_;   //!
   TBranch        *b__TOFBarrelHits_particle_index;   //!
   TBranch        *b__TOFBarrelHits_particle_collectionID;   //!
   TBranch        *b_TOFEndcapHits_;   //!
   TBranch        *b_TOFEndcapHits_cellID;   //!
   TBranch        *b_TOFEndcapHits_eDep;   //!
   TBranch        *b_TOFEndcapHits_time;   //!
   TBranch        *b_TOFEndcapHits_pathLength;   //!
   TBranch        *b_TOFEndcapHits_quality;   //!
   TBranch        *b_TOFEndcapHits_position_x;   //!
   TBranch        *b_TOFEndcapHits_position_y;   //!
   TBranch        *b_TOFEndcapHits_position_z;   //!
   TBranch        *b_TOFEndcapHits_momentum_x;   //!
   TBranch        *b_TOFEndcapHits_momentum_y;   //!
   TBranch        *b_TOFEndcapHits_momentum_z;   //!
   TBranch        *b__TOFEndcapHits_particle_;   //!
   TBranch        *b__TOFEndcapHits_particle_index;   //!
   TBranch        *b__TOFEndcapHits_particle_collectionID;   //!
   TBranch        *b_TrackerEndcapHits_;   //!
   TBranch        *b_TrackerEndcapHits_cellID;   //!
   TBranch        *b_TrackerEndcapHits_eDep;   //!
   TBranch        *b_TrackerEndcapHits_time;   //!
   TBranch        *b_TrackerEndcapHits_pathLength;   //!
   TBranch        *b_TrackerEndcapHits_quality;   //!
   TBranch        *b_TrackerEndcapHits_position_x;   //!
   TBranch        *b_TrackerEndcapHits_position_y;   //!
   TBranch        *b_TrackerEndcapHits_position_z;   //!
   TBranch        *b_TrackerEndcapHits_momentum_x;   //!
   TBranch        *b_TrackerEndcapHits_momentum_y;   //!
   TBranch        *b_TrackerEndcapHits_momentum_z;   //!
   TBranch        *b__TrackerEndcapHits_particle_;   //!
   TBranch        *b__TrackerEndcapHits_particle_index;   //!
   TBranch        *b__TrackerEndcapHits_particle_collectionID;   //!
   TBranch        *b_VertexBarrelHits_;   //!
   TBranch        *b_VertexBarrelHits_cellID;   //!
   TBranch        *b_VertexBarrelHits_eDep;   //!
   TBranch        *b_VertexBarrelHits_time;   //!
   TBranch        *b_VertexBarrelHits_pathLength;   //!
   TBranch        *b_VertexBarrelHits_quality;   //!
   TBranch        *b_VertexBarrelHits_position_x;   //!
   TBranch        *b_VertexBarrelHits_position_y;   //!
   TBranch        *b_VertexBarrelHits_position_z;   //!
   TBranch        *b_VertexBarrelHits_momentum_x;   //!
   TBranch        *b_VertexBarrelHits_momentum_y;   //!
   TBranch        *b_VertexBarrelHits_momentum_z;   //!
   TBranch        *b__VertexBarrelHits_particle_;   //!
   TBranch        *b__VertexBarrelHits_particle_index;   //!
   TBranch        *b__VertexBarrelHits_particle_collectionID;   //!
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
      "B0TrackerHits",       "BackwardMPGDEndcapHits", "DIRCBarHits",\
      "DRICHHits",           "ForwardMPGDEndcapHits",  "ForwardOffMTrackerHits",\
      "ForwardRomanPotHits", "LumiSpecTrackerHits",    "MPGDBarrelHits",\
      "OuterMPGDBarrelHits", "RICHEndcapNHits",        "SiBarrelHits",\
      "TOFBarrelHits",       "TOFEndcapHits",          "TaggerTrackerHits",\
      "TrackerEndcapHits",   "VertexBarrelHits"
   };


   std::vector<SimTrackerHitKuma > m_SimTrackerHitsKuma; // a "kuma example" of a member valuable
   // black, blue, red, green, violet, orange, light blue, light green, dark violet, brown, very light blue, 
   // yellow green, week red, dark blue, week green, dark cyan, dark orange, 
   Int_t m_myHistColors[18] = {4, 600, 632, 419, 880, 807, 867, 909, 814, 874, 635, 870, 824, 625, 602, 417, 434, 802}; // colors for histograms

   // "BackwardMPGDEndcapHits - TrackerEndcapHits", "TOFBarrelHits - SiBarrelHits", "ForwardMPGDEndcapHits - TrackerEndcapHits"
   std::vector<std::vector<Int_t> > m_TriggerSets = {{1, 15}, {11, 12}, {5, 15}};
   Int_t m_bDetMinHitsRequire[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   bool m_bDetTriggerLists[17] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
   bool m_bCombinTriggerLists[3] = {false, false, false};
   bool m_bTrigger = false;

   // histograms as output
   TH2D* m_hEventDisplayZR_Det;
   TH2D* m_hEventDisplayZR_Det_TF;

   TH1D* m_hTriggerCounts; // histogram for trigger types
   
   // == member functions == // own function
   void HistInit();
   void ResetValuesForEachEvent();
   void WriteHists();
   
   float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   float m_timeslice_width = 20.0; // width of time split for a time frame [ns]

   float m_timeResolution_Silicon = 2000.0; // time resolution [ns]
   float m_timeResolution_MPGD = 10.0; // time resolution [ns]
   float m_timeResolution_TOF = 0.030; // time resolution [ns]

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
};

#endif

// #ifndef triggerCombineChecker_cxx
// #define triggerCombineChecker_cxx


// #endif // #ifdef triggerCombineChecker_cxx
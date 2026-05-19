//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 27 09:52:40 2026 by ROOT version 6.30/05
// from TTree events/events data tree
// found on file: synrad_test.edm4hep.root
//////////////////////////////////////////////////////////

#ifndef McPsCheck_h
#define McPsCheck_h

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



#include <TApplication.h>
#include <TCanvas.h>
#include <TView.h>
#include <TAxis3D.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLatex.h>
#include <TMarker.h>
#include <TLine.h>


class McPsCheck {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any. 
   McPsCheck(TTree *tree=0, std::string iFileName="", std::string oFileName="");
   virtual ~McPsCheck();
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
   static constexpr Int_t kMaxB0ECalHits = 999999;
   static constexpr Int_t kMax_B0ECalHits_contributions = 999999;
   static constexpr Int_t kMaxB0ECalHitsContributions = 999999;
   static constexpr Int_t kMax_B0ECalHitsContributions_particle = 999999;
   static constexpr Int_t kMaxB0TrackerHits = 999999;
   static constexpr Int_t kMax_B0TrackerHits_particle = 999999;
   static constexpr Int_t kMaxBackwardMPGDEndcapHits = 999999;
   static constexpr Int_t kMax_BackwardMPGDEndcapHits_particle = 999999;
   static constexpr Int_t kMaxDIRCBarHits = 999999;
   static constexpr Int_t kMax_DIRCBarHits_particle = 999999;
   static constexpr Int_t kMaxDRICHHits = 999999;
   static constexpr Int_t kMax_DRICHHits_particle = 999999;
   static constexpr Int_t kMaxEcalBarrelImagingHits = 999999;
   static constexpr Int_t kMax_EcalBarrelImagingHits_contributions = 999999;
   static constexpr Int_t kMaxEcalBarrelImagingHitsContributions = 999999;
   static constexpr Int_t kMax_EcalBarrelImagingHitsContributions_particle = 999999;
   static constexpr Int_t kMaxEcalBarrelScFiHits = 999999;
   static constexpr Int_t kMax_EcalBarrelScFiHits_contributions = 999999;
   static constexpr Int_t kMaxEcalBarrelScFiHitsContributions = 999999;
   static constexpr Int_t kMax_EcalBarrelScFiHitsContributions_particle = 999999;
   static constexpr Int_t kMaxEcalEndcapNHits = 999999;
   static constexpr Int_t kMax_EcalEndcapNHits_contributions = 999999;
   static constexpr Int_t kMaxEcalEndcapNHitsContributions = 999999;
   static constexpr Int_t kMax_EcalEndcapNHitsContributions_particle = 999999;
   static constexpr Int_t kMaxEcalEndcapPHits = 999999;
   static constexpr Int_t kMax_EcalEndcapPHits_contributions = 999999;
   static constexpr Int_t kMaxEcalEndcapPHitsContributions = 999999;
   static constexpr Int_t kMax_EcalEndcapPHitsContributions_particle = 999999;
   static constexpr Int_t kMaxEcalFarForwardZDCHits = 999999;
   static constexpr Int_t kMax_EcalFarForwardZDCHits_contributions = 999999;
   static constexpr Int_t kMaxEcalFarForwardZDCHitsContributions = 999999;
   static constexpr Int_t kMax_EcalFarForwardZDCHitsContributions_particle = 999999;
   static constexpr Int_t kMaxEcalLumiSpecHits = 999999;
   static constexpr Int_t kMax_EcalLumiSpecHits_contributions = 999999;
   static constexpr Int_t kMaxEcalLumiSpecHitsContributions = 999999;
   static constexpr Int_t kMax_EcalLumiSpecHitsContributions_particle = 999999;
   static constexpr Int_t kMaxEventHeader = 999999;
   static constexpr Int_t kMaxForwardMPGDEndcapHits = 999999;
   static constexpr Int_t kMax_ForwardMPGDEndcapHits_particle = 999999;
   static constexpr Int_t kMaxForwardOffMTrackerHits = 999999;
   static constexpr Int_t kMax_ForwardOffMTrackerHits_particle = 999999;
   static constexpr Int_t kMaxForwardRomanPotHits = 999999;
   static constexpr Int_t kMax_ForwardRomanPotHits_particle = 999999;
   static constexpr Int_t kMaxHcalBarrelHits = 999999;
   static constexpr Int_t kMax_HcalBarrelHits_contributions = 999999;
   static constexpr Int_t kMaxHcalBarrelHitsContributions = 999999;
   static constexpr Int_t kMax_HcalBarrelHitsContributions_particle = 999999;
   static constexpr Int_t kMaxHcalEndcapNHits = 999999;
   static constexpr Int_t kMax_HcalEndcapNHits_contributions = 999999;
   static constexpr Int_t kMaxHcalEndcapNHitsContributions = 999999;
   static constexpr Int_t kMax_HcalEndcapNHitsContributions_particle = 999999;
   static constexpr Int_t kMaxHcalEndcapPInsertHits = 999999;
   static constexpr Int_t kMax_HcalEndcapPInsertHits_contributions = 999999;
   static constexpr Int_t kMaxHcalEndcapPInsertHitsContributions = 999999;
   static constexpr Int_t kMax_HcalEndcapPInsertHitsContributions_particle = 999999;
   static constexpr Int_t kMaxHcalFarForwardZDCHits = 999999;
   static constexpr Int_t kMax_HcalFarForwardZDCHits_contributions = 999999;
   static constexpr Int_t kMaxHcalFarForwardZDCHitsContributions = 999999;
   static constexpr Int_t kMax_HcalFarForwardZDCHitsContributions_particle = 999999;
   static constexpr Int_t kMaxLFHCALHits = 999999;
   static constexpr Int_t kMax_LFHCALHits_contributions = 999999;
   static constexpr Int_t kMaxLFHCALHitsContributions = 999999;
   static constexpr Int_t kMax_LFHCALHitsContributions_particle = 999999;
   static constexpr Int_t kMaxLumiDirectPCALHits = 999999;
   static constexpr Int_t kMax_LumiDirectPCALHits_contributions = 999999;
   static constexpr Int_t kMaxLumiDirectPCALHitsContributions = 999999;
   static constexpr Int_t kMax_LumiDirectPCALHitsContributions_particle = 999999;
   static constexpr Int_t kMaxLumiSpecTrackerHits = 999999;
   static constexpr Int_t kMax_LumiSpecTrackerHits_particle = 999999;
   static constexpr Int_t kMaxMCParticles = 999999;
   static constexpr Int_t kMax_MCParticles_parents = 999999;
   static constexpr Int_t kMax_MCParticles_daughters = 999999;
   static constexpr Int_t kMaxMPGDBarrelHits = 999999;
   static constexpr Int_t kMax_MPGDBarrelHits_particle = 999999;
   static constexpr Int_t kMaxOuterMPGDBarrelHits = 999999;
   static constexpr Int_t kMax_OuterMPGDBarrelHits_particle = 999999;
   static constexpr Int_t kMaxPFRICHHits = 999999;
   static constexpr Int_t kMax_PFRICHHits_particle = 999999;
   static constexpr Int_t kMaxSiBarrelHits = 999999;
   static constexpr Int_t kMax_SiBarrelHits_particle = 999999;
   static constexpr Int_t kMaxTaggerTrackerHits = 999999;
   static constexpr Int_t kMax_TaggerTrackerHits_particle = 999999;
   static constexpr Int_t kMaxTOFBarrelHits = 999999;
   static constexpr Int_t kMax_TOFBarrelHits_particle = 999999;
   static constexpr Int_t kMaxTOFEndcapHits = 999999;
   static constexpr Int_t kMax_TOFEndcapHits_particle = 999999;
   static constexpr Int_t kMaxTrackerEndcapHits = 999999;
   static constexpr Int_t kMax_TrackerEndcapHits_particle = 999999;
   static constexpr Int_t kMaxVertexBarrelHits = 999999;
   static constexpr Int_t kMax_VertexBarrelHits_particle = 999999;

   // Declaration of leaf types
   Int_t           EventHeader_;
   ULong_t         EventHeader_eventNumber[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_runNumber[kMaxEventHeader];   //[EventHeader_]
   ULong_t         EventHeader_timeStamp[kMaxEventHeader];   //[EventHeader_]
   Double_t        EventHeader_weight[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_begin[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_end[kMaxEventHeader];   //[EventHeader_]
   std::vector<double>  *_EventHeader_weights;

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
   Int_t           MCParticles_helicity[kMaxMCParticles];   //[MCParticles_]
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
   Float_t         B0ECalHitsContributions_stepLength[kMaxB0ECalHitsContributions];   //[B0ECalHitsContributions_]
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
   Float_t         EcalBarrelImagingHitsContributions_stepLength[kMaxEcalBarrelImagingHitsContributions];   //[EcalBarrelImagingHitsContributions_]
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
   Float_t         EcalBarrelScFiHitsContributions_stepLength[kMaxEcalBarrelScFiHitsContributions];   //[EcalBarrelScFiHitsContributions_]
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
   Float_t         EcalEndcapNHitsContributions_stepLength[kMaxEcalEndcapNHitsContributions];   //[EcalEndcapNHitsContributions_]
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
   Float_t         EcalEndcapPHitsContributions_stepLength[kMaxEcalEndcapPHitsContributions];   //[EcalEndcapPHitsContributions_]
   Int_t           _EcalEndcapPHitsContributions_particle_;
   Int_t           _EcalEndcapPHitsContributions_particle_index[kMax_EcalEndcapPHitsContributions_particle];   //[_EcalEndcapPHitsContributions_particle_]
   UInt_t          _EcalEndcapPHitsContributions_particle_collectionID[kMax_EcalEndcapPHitsContributions_particle];   //[_EcalEndcapPHitsContributions_particle_]
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
   Float_t         EcalFarForwardZDCHitsContributions_stepLength[kMaxEcalFarForwardZDCHitsContributions];   //[EcalFarForwardZDCHitsContributions_]
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
   Float_t         EcalLumiSpecHitsContributions_stepLength[kMaxEcalLumiSpecHitsContributions];   //[EcalLumiSpecHitsContributions_]
   Int_t           _EcalLumiSpecHitsContributions_particle_;
   Int_t           _EcalLumiSpecHitsContributions_particle_index[kMax_EcalLumiSpecHitsContributions_particle];   //[_EcalLumiSpecHitsContributions_particle_]
   UInt_t          _EcalLumiSpecHitsContributions_particle_collectionID[kMax_EcalLumiSpecHitsContributions_particle];   //[_EcalLumiSpecHitsContributions_particle_]

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
   Float_t         HcalBarrelHitsContributions_stepLength[kMaxHcalBarrelHitsContributions];   //[HcalBarrelHitsContributions_]
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
   Float_t         HcalEndcapNHitsContributions_stepLength[kMaxHcalEndcapNHitsContributions];   //[HcalEndcapNHitsContributions_]
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
   Float_t         HcalEndcapPInsertHitsContributions_stepLength[kMaxHcalEndcapPInsertHitsContributions];   //[HcalEndcapPInsertHitsContributions_]
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
   Float_t         HcalFarForwardZDCHitsContributions_stepLength[kMaxHcalFarForwardZDCHitsContributions];   //[HcalFarForwardZDCHitsContributions_]
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
   Float_t         LFHCALHitsContributions_stepLength[kMaxLFHCALHitsContributions];   //[LFHCALHitsContributions_]
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
   Float_t         LumiDirectPCALHitsContributions_stepLength[kMaxLumiDirectPCALHitsContributions];   //[LumiDirectPCALHitsContributions_]
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
   Int_t           PFRICHHits_;
   ULong_t         PFRICHHits_cellID[kMaxPFRICHHits];   //[PFRICHHits_]
   Float_t         PFRICHHits_eDep[kMaxPFRICHHits];   //[PFRICHHits_]
   Float_t         PFRICHHits_time[kMaxPFRICHHits];   //[PFRICHHits_]
   Float_t         PFRICHHits_pathLength[kMaxPFRICHHits];   //[PFRICHHits_]
   Int_t           PFRICHHits_quality[kMaxPFRICHHits];   //[PFRICHHits_]
   Double_t        PFRICHHits_position_x[kMaxPFRICHHits];   //[PFRICHHits_]
   Double_t        PFRICHHits_position_y[kMaxPFRICHHits];   //[PFRICHHits_]
   Double_t        PFRICHHits_position_z[kMaxPFRICHHits];   //[PFRICHHits_]
   Float_t         PFRICHHits_momentum_x[kMaxPFRICHHits];   //[PFRICHHits_]
   Float_t         PFRICHHits_momentum_y[kMaxPFRICHHits];   //[PFRICHHits_]
   Float_t         PFRICHHits_momentum_z[kMaxPFRICHHits];   //[PFRICHHits_]
   Int_t           _PFRICHHits_particle_;
   Int_t           _PFRICHHits_particle_index[kMax_PFRICHHits_particle];   //[_PFRICHHits_particle_]
   UInt_t          _PFRICHHits_particle_collectionID[kMax_PFRICHHits_particle];   //[_PFRICHHits_particle_]
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
   TBranch        *b_B0ECalHitsContributions_stepLength;   //!
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
   TBranch        *b_EcalBarrelImagingHitsContributions_stepLength;   //!
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
   TBranch        *b_EcalBarrelScFiHitsContributions_stepLength;   //!
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
   TBranch        *b_EcalEndcapNHitsContributions_stepLength;   //!
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
   TBranch        *b_EcalEndcapPHitsContributions_stepLength;   //!
   TBranch        *b__EcalEndcapPHitsContributions_particle_;   //!
   TBranch        *b__EcalEndcapPHitsContributions_particle_index;   //!
   TBranch        *b__EcalEndcapPHitsContributions_particle_collectionID;   //!
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
   TBranch        *b_EcalFarForwardZDCHitsContributions_stepLength;   //!
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
   TBranch        *b_EcalLumiSpecHitsContributions_stepLength;   //!
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
   TBranch        *b_HcalBarrelHitsContributions_stepLength;   //!
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
   TBranch        *b_HcalEndcapNHitsContributions_stepLength;   //!
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
   TBranch        *b_HcalEndcapPInsertHitsContributions_stepLength;   //!
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
   TBranch        *b_HcalFarForwardZDCHitsContributions_stepLength;   //!
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
   TBranch        *b_LFHCALHitsContributions_stepLength;   //!
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
   TBranch        *b_LumiDirectPCALHitsContributions_stepLength;   //!
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
   TBranch        *b_MCParticles_helicity;   //!
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
   TBranch        *b_PFRICHHits_;   //!
   TBranch        *b_PFRICHHits_cellID;   //!
   TBranch        *b_PFRICHHits_eDep;   //!
   TBranch        *b_PFRICHHits_time;   //!
   TBranch        *b_PFRICHHits_pathLength;   //!
   TBranch        *b_PFRICHHits_quality;   //!
   TBranch        *b_PFRICHHits_position_x;   //!
   TBranch        *b_PFRICHHits_position_y;   //!
   TBranch        *b_PFRICHHits_position_z;   //!
   TBranch        *b_PFRICHHits_momentum_x;   //!
   TBranch        *b_PFRICHHits_momentum_y;   //!
   TBranch        *b_PFRICHHits_momentum_z;   //!
   TBranch        *b__PFRICHHits_particle_;   //!
   TBranch        *b__PFRICHHits_particle_index;   //!
   TBranch        *b__PFRICHHits_particle_collectionID;   //!
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

   Int_t tempCount = 1;

   TString m_TrkDetNames[17] = \
   {
      "VertexBarrel", "SiBarrel", "TrackerEndcap", "MPGDBarrel", "OuterMPGDBarrel", "ForwardMPGDEndcap", "BackwardMPGDEndcap",\
       "TOFBarrel",  "TOFEndcap", "B0Tracker",  "DIRCBarHits", "DRICHHits", "ForwardOffMTracker",\
      "ForwardRomanPot", "LumiSpecTracker", "RICHEndcapN", "TaggerTracker"
   };
   Int_t numOfEventsForEachTrkDet[17] = {0};

   TString m_CalDetNames[12] = \
   {
      "B0ECal", "EcalBarrelImaging", "EcalBarrelScFi", "EcalEndcapN", "EcalEndcapP", \
      "EcalFarForwardZDC", "EcalLumiSpec", "HcalBarrel", "HcalEndcapN",\
      "HcalEndcapPInsert", "HcalFarForwardZDC", "LFHCAL"
   };
   Int_t numOfEventsForEachCalDet[12] = {0};

   // black, blue, red, green, violet, orange, light blue, light green, dark violet, brown, very light blue, 
   // yellow green, week red, dark blue, week green, dark cyan, dark orange, 
   Int_t m_myHistColors[18] = {4, 600, 632, 419, 880, 807, 867, 909, 814, 874, 635, 870, 824, 625, 602, 417, 434, 802}; // colors for histograms
   
// enum EColor { kWhite =0, kBlack =1, kGray=920, kRed =632, kGreen =416, kBlue=600, kYellow=400, kMagenta=616, kCyan=432, kOrange=800, kSpring=820, kTeal=840, kAzure =860kViolet =880, kPink=900 };
   const Int_t m_kDetColors[9] = {
      860 + 2, // kAzure：MAPS
      880 + 1, // kPurple：MPGD
      860 + 8, //840 + 2, // kTeal： AC-LGAD
      800 + 1, // kOrange：ECal
      860 - 2, // kAzure：HCal
      800 - 4, // kOrange：RICH
      860 - 7, // kAzure：DIRC
      632 - 6, // kRed：Far Forward
      600- 2  // kBlue：Far Backward
   };

   // "VertexBarrel", "SiBarrel", "TrackerEndcap", "MPGDBarrel", "OuterMPGDBarrel", "ForwardMPGDEndcap", "BackwardMPGDEndcap",\
   // "TOFBarrel",  "TOFEndcap", "B0Tracker",  "DIRCBarHits", "DRICHHits", "ForwardOffMTracker",\
   // "ForwardRomanPot", "LumiSpecTracker", "RICHEndcapN", "TaggerTracker"
   Int_t m_TrkDetColors[17] = {m_kDetColors[0], m_kDetColors[0], m_kDetColors[0],\
      m_kDetColors[1], m_kDetColors[1],  m_kDetColors[1], m_kDetColors[1],\
      m_kDetColors[2], m_kDetColors[2], \
      m_kDetColors[0],\
      m_kDetColors[6], m_kDetColors[5], m_kDetColors[7], m_kDetColors[7],
      m_kDetColors[7], m_kDetColors[5], m_kDetColors[0]
   };

   // "B0ECal", "EcalBarrelImaging", "EcalBarrelScFi", "EcalEndcapN", "EcalEndcapP", \
   // "EcalFarForwardZDC", "EcalLumiSpec", "HcalBarrel", "HcalEndcapN",\
   // "HcalEndcapPInsert", "HcalFarForwardZDC", "LFHCAL"
   Int_t m_CalDetColors[12] = {
      m_kDetColors[3], m_kDetColors[3], m_kDetColors[3], m_kDetColors[3], m_kDetColors[3],\
      m_kDetColors[3], m_kDetColors[3],
      m_kDetColors[4], m_kDetColors[4], m_kDetColors[4], m_kDetColors[4], m_kDetColors[4]
   };

   const Int_t m_kMcPColor[7] = {
      820 - 8, // kSpring：gamma
      860 + 1, // kAzure：electron
      632 - 7, // kRed : proton
      880 + 2, // kPurple : neutron
      860 + 10, // kAzure: other lepton
      2, // kGray: other neutral
      632 - 2  // kRed: other charged
   };


   TH1D* m_hMCEtaDist; // 
   TH1D* m_hMCThetaDist; // 

   TH2D* m_HitRTimeDispersion; // 
   TH2D* m_CalibHitRTimeDispersion; // 
   TH1D* m_HitTCalcT0Dispersion; // 

   TH2D* m_hEtaPt_All; // 
   TH2D* m_hEtaPt_ChMcP; // 
   TH2D* m_hEtaPt_NMcP; // 

   TH2D* m_hEtaKinE_All; // 
   TH2D* m_hEtaKinE_ChMcP; // 
   TH2D* m_hEtaKinE_NMcP; // 

   TH2D* m_hEtaAllE_All; // 
   TH2D* m_hEtaAllE_ChMcP; // 
   TH2D* m_hEtaAllE_NMcP; //

   TString m_BkgNames[5] = {"SR", "Brems", "Coul", "Tous", "ProtonGas"};
   TH2D* m_hZRHitRatio_All_BKG[5]; // [SR, Brems, Coul, Tous, ProtonGas]
   TH2D* m_hZRHitRatio_ChMcP_BKG[5]; // [SR, Brems, Coul, Tous, ProtonGas]
   TH2D* m_hZRHitRatio_NMcP_BKG[5]; // [SR, Brems, Coul, Tous, ProtonGas]

   TH1D* m_EveCountWithDetHits_Trk_BKG[5]; // 
   TH1D* m_EveCountWithDetHits_Cal_BKG[5]; // 

   TH1D* m_HitsPerEveWithDetHits_Trk_BKG[5]; // 
   TH1D* m_HitsPerEveWithDetHits_Cal_BKG[5]; // 

   TH2D* m_CollSourcePosiZR; // 

   TH1D* m_EveCountWithDetHits_Trk; // 
   TH1D* m_EveCountWithDetHits_Cal; // 

   TH1D* m_HitsPerEveWithDetHits_Trk; // 
   TH1D* m_HitsPerEveWithDetHits_Cal; // 
   

   TH1D* m_NumOfEventsOfBKG; // 

   TH1D* m_hEta_All; //
   TH1D* m_hEta_BTOF; // 
   TH1D* m_hEta_ETOF; // 

   TH1D* m_HitTCalcT0Dispersion_Phys; // 
   TH1D* m_HitTCalcT0Dispersion_BKG; // 
   TH1D* m_HitTCalcT0Dispersion_Phys_BTOF; // 
   TH1D* m_HitTCalcT0Dispersion_BKG_BTOF; // 

   TH1D* m_HitDepE_Phys; // 
   TH1D* m_HitDepE_BKG[5]; // 
   
   TH1D* m_HitDepE_Phys_BSVT; // 
   TH1D* m_HitDepE_BKG_BSVT[5]; // 
   TH1D* m_HitDepE_Phys_ESVT; // 
   TH1D* m_HitDepE_BKG_ESVT[5]; // 

   TH1D* m_HitDepE_Phys_BMPGD; // 
   TH1D* m_HitDepE_BKG_BMPGD[5]; // 
   TH1D* m_HitDepE_Phys_EMPGD; // 
   TH1D* m_HitDepE_BKG_EMPGD[5]; 

   TH1D* m_HitDepE_Phys_BTOF; // 
   TH1D* m_HitDepE_BKG_BTOF[5]; // 
   TH1D* m_HitDepE_Phys_ETOF; // 
   TH1D* m_HitDepE_BKG_ETOF[5]; // 

   // == member functions == // own function
   void HistInit();
   void ResetValuesForEachEvent();
   void WriteHists();
   
   float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   float m_timeslice_width = 20.0; // width of time split for a time frame [ns]

   void CountMcParticles();

   void FillZRHitMaps();

   void FillEtaPtMaps();

   void recordMCPsForED();
   void recordTrkHitsForED();
   void recordCalHitsForED();

   // void mcPChecks();
   void countTrkDetHits();
   void countCalDetHits();

   void FillHitTimeDispersion();
   void FillHitTimeDispersionForMixBKG();

   // === s === For Event Display ===========

   struct Vec3 {
      double x{};
      double y{};
      double z{};
   };

   struct Particle {
      Vec3 vertex;
      Vec3 momentum;
      Vec3 endpoint;
      int pdg{};
      double charge{};
      bool hasEndpoint{false};

      std::vector<int> parents;
      std::vector<int> daughters;
   };

   struct Event {
      std::vector<Particle> particles;
   };

   double mag(const Vec3& v) {
      return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
   }

   Vec3 normalize(const Vec3& v) {
      const double m = mag(v);
      if (m < 1e-12) return {0.0, 0.0, 0.0};
      return {v.x / m, v.y / m, v.z / m};
   }

   Vec3 add(const Vec3& a, const Vec3& b) {
      return {a.x + b.x, a.y + b.y, a.z + b.z};
   }

   Vec3 sub(const Vec3& a, const Vec3& b) {
      return {a.x - b.x, a.y - b.y, a.z - b.z};
   }

   Vec3 scale(const Vec3& v, double s) {
      return {v.x * s, v.y * s, v.z * s};
   }

   
   int colorFromPDG(int pdg, Float_t ch) {
      const int apdg = std::abs(pdg);
      if (apdg == 22)   return m_kMcPColor[0];    // gamma
      if (apdg == 11)   return m_kMcPColor[1];    // e
      if (apdg == 2212) return m_kMcPColor[2];    // proton
      if (apdg == 2112) return m_kMcPColor[3];    // neutron
      if (apdg == 13)   return m_kMcPColor[4];    // mu
      if (apdg == 211)  return m_kMcPColor[5];    // pi
      if (ch == 0)  return m_kMcPColor[6];    // other neutral
      if (ch != 0)  return m_kMcPColor[7];    // other charged
      return kBlack;
      // if (apdg == 321)  return m_kMcPColor[3];    // K
   }

   Vec3 getTrackEnd(const Particle& p, double fallbackLength = 9000.0) {
      if (p.hasEndpoint) {
         return p.endpoint;
      }

      const Vec3 dir = normalize(p.momentum);
      if (mag(dir) < 1e-12) {
         return p.vertex;
      }
      // return add(p.vertex, scale(dir, fallbackLength));
      return add(p.vertex, scale(dir, 1.));
   }

   void computeEventBounds(
      const Event& ev,
      double& xmin, double& xmax,
      double& ymin, double& ymax,
      double& zmin, double& zmax,
      double fallbackLength = 300.0
   ) {
      bool first = true;

      for (const auto& p : ev.particles) {
         const Vec3 a = p.vertex;
         const Vec3 b = getTrackEnd(p, fallbackLength);

         const Vec3 pts[2] = {a, b};
         for (const auto& q : pts) {
            if (first) {
               xmin = xmax = q.x;
               ymin = ymax = q.y;
               zmin = zmax = q.z;
               first = false;
            } else {
               xmin = std::min(xmin, q.x);
               xmax = std::max(xmax, q.x);
               ymin = std::min(ymin, q.y);
               ymax = std::max(ymax, q.y);
               zmin = std::min(zmin, q.z);
               zmax = std::max(zmax, q.z);
            }
         }
      }

      if (first) {
         xmin = ymin = zmin = -1.0;
         xmax = ymax = zmax =  1.0;
         return;
      }

      const double dx = xmax - xmin;
      const double dy = ymax - ymin;
      const double dz = zmax - zmin;
      const double margin = 0.15;

      xmin -= std::max(dx * margin, 1.0);
      xmax += std::max(dx * margin, 1.0);
      ymin -= std::max(dy * margin, 1.0);
      ymax += std::max(dy * margin, 1.0);
      zmin -= std::max(dz * margin, 1.0);
      zmax += std::max(dz * margin, 1.0);
   }

   std::vector<Event> m_eventsForED;


   Int_t numOfED = 8;
   TH3D* m_hEventDisplays[8];
   Int_t m_iDisplayCount = 0;

   std::vector<std::vector<std::vector<Vec3> > > m_vRecordedTrkDetHits;
   std::vector<std::vector<std::vector<Vec3> > > m_vRecordedCalDetHits;

   void drawOnlyOneEvent(const Event& ev);
   
   void drawOneEvent(const Event& ev, int eventIndex, double fallbackLength = 300.0);
   void drawEightEvents(double fallbackLength = 300.0);

   TH2D* m_hEventDisplays2D[8];
   void drawOneEvent2D_ZX(const Event& ev, int eventIndex, double fallbackLength = 300.0);
   void drawEightEvents2D_ZX(double fallbackLength = 300.0);

   TH3D* m_hCheckEventDisplays; // 
   std::vector<Event> m_CheckEventsForED;
   std::vector<std::vector<std::vector<Vec3> > > m_vCheckRecordedTrkDetHits;
   // === e === For Event Display ===========


};

#endif

// #ifndef McPsCheck_cxx
// #define McPsCheck_cxx


// #endif // #ifdef McPsCheck_cxx


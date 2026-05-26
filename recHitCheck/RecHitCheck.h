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

#ifndef RecHitCheck_h
#define RecHitCheck_h

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


class RecHitCheck {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any. 
   RecHitCheck(TTree *tree=0, std::string iFileName="", std::string oFileName="");
   virtual ~RecHitCheck();
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

   #include "defRootVariables.h"
   #include "defRootBranches.h"

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

   
   Double_t MakeRandomTimeOffset(Int_t randomSeed);
   // Double_t FindFirstPhysParticle();


   // == inherited functions == //
   std::vector<SimTrackerHitKuma> LoadInputTrkHits();
   std::vector<SimTrackerHitKuma> LoadInputCalHits();


};


#endif
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


#include <TApplication.h>

#include <TLatex.h>
#include <TMarker.h>
#include <TLine.h>

#include "podio/ROOTReader.h"
#include "podio/Frame.h"

#include "edm4hep/MCParticleCollection.h"

#include <edm4hep/SimTrackerHitCollection.h>
#include <edm4eic/RawTrackerHitCollection.h>
#include <edm4eic/MCRecoTrackerHitAssociationCollection.h>
#include "edm4eic/TrackerHitCollection.h"
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/MCRecoClusterParticleAssociationCollection.h>

#include "InputDataConfig.h"
#include "SimTrackerHitKuma.h"


class EventAna {

public:
    EventAna(const std::string& inputFile, const std::string& outputFile = "test.root");
    void EventLoop();

private:

    void OFileInit();
    void EditHists();
    void OFileWrite();
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

    double m_timeWindow = 2000.0;
    double m_timeSliceWidth = 20.0;


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
    // "TOFBarrel",  "TOFEndcap", "B0Tracker",  "ForwardOffMTracker","ForwardRomanPot", \
    // 
    // "DIRCBarHits", "DRICHHits", "LumiSpecTracker", "RICHEndcapN", "TaggerTracker"
    Int_t m_TrkDetColors[12] = {m_kDetColors[0], m_kDetColors[0], m_kDetColors[0],\
        m_kDetColors[1], m_kDetColors[1],  m_kDetColors[1], m_kDetColors[1],\
        m_kDetColors[2], m_kDetColors[2], \
        m_kDetColors[0],\
        m_kDetColors[7], m_kDetColors[7]
    };
    //    m_kDetColors[6], m_kDetColors[5], m_kDetColors[7], m_kDetColors[5], m_kDetColors[0]


   // "B0ECal", "EcalBarrel", "EcalEndcapN", "EcalEndcapP", \
   // "EcalFarForwardZDC", "EcalLumiSpec", "HcalBarrel", "HcalEndcapN",\
   // "HcalEndcapPInsert", "HcalFarForwardZDC", "LFHCAL"
   Int_t m_CalDetColors[11] = {
      m_kDetColors[3], m_kDetColors[3],  m_kDetColors[3], m_kDetColors[3],\
      m_kDetColors[3], m_kDetColors[3],
      m_kDetColors[4], m_kDetColors[4], m_kDetColors[4], m_kDetColors[4], m_kDetColors[4]
   };
    //    "EcalBarrelScFi", m_kDetColors[3],

   const Int_t m_kMcPColor[8] = {
      820 - 8, // kSpring：gamma
      860 + 1, // kAzure：electron
      632 - 7, // kRed : proton
      880 + 2, // kPurple : neutron
      860 + 10, // kAzure: other lepton
      860 - 7, // kGray: other neutral
      632 - 2, // kRed: other charged
      2 // kBlack: background
   };


   // === s === For Event Display ===========
   
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

   bool bWBKG = false;
   Int_t m_SpeEventID = 0;

   Int_t numOfED = 8;
   TH3D* m_hEventDisplays[8];
   Int_t m_iDisplayCount = 0;

   void drawOnlyOneEvent(const podio::Frame& frame);
   
   void drawOneEvent(const podio::Frame& frame, int eventIndex);
   void drawEightEvents(const podio::Frame& frame);

   TH2D* m_hEventDisplays2D_ZR[8];
   void drawOneEvent2D_ZR(const podio::Frame& frame, int eventIndex);
   void drawEightEvents2D_ZR();

   TH2D* m_hEventDisplays2D_XY[8];
   void drawOneEvent2D_XY(const podio::Frame& frame, int eventIndex);
   void drawEightEvents2D_XY();

   void drawSpecialEvents3D();

   TH3D* m_hEventDisplay3D; // 
   // === e === For Event Display ===========

};

#endif
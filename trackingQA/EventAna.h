#ifndef EVENT_ANA_H
#define EVENT_ANA_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include <utility>

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




#include <edm4hep/EventHeaderCollection.h>
#include <edm4hep/MCParticleCollection.h>
#include <edm4hep/ParticleIDCollection.h>
#include <edm4eic/TrackCollection.h>
#include <edm4eic/TrackParametersCollection.h>
#include <edm4eic/TrajectoryCollection.h>
#include <edm4eic/MCRecoTrackParticleAssociationCollection.h>
#include <edm4eic/Measurement2DCollection.h>
#include <edm4eic/TrackSeedCollection.h>
#include <edm4eic/TrackerHitCollection.h>
#include <edm4eic/MCRecoTrackerHitAssociationCollection.h>
#include <edm4eic/TrackSegmentCollection.h>
#include <edm4eic/VertexCollection.h>
#include <edm4eic/ReconstructedParticleCollection.h>
#include <edm4eic/MCRecoParticleAssociationCollection.h>

class EventAna {

public:
    EventAna(const std::string& inputFile, const std::string& outputFile = "test.root");
    void EventLoop();

private:
    void OFileInit();
    void EditHists();
    void OFileWrite();


    Double_t FindPhysCollTime(const podio::Frame& frame);

private:
    std::string m_iFileName;
    std::string m_oFileName;
    podio::ROOTReader m_reader;

    TFile* oFile;

    std::vector<Int_t> m_vTargetEvents;
    Int_t m_pubEvNum = 0;


    Double_t m_timeframe_width = 2000.0;
    Double_t m_timesplit_width = 20.0;

    const Double_t timeResolution_SiMaps = 2000.0; // ns [s]
    const Double_t timeResolution_MPGD = 30.0; // ns [s]
    const Double_t timeResolution_ACLGad = 0.03; // ns [s]
    const Double_t timeResolution_EMCal = 30.0; // ns [s]

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


    Int_t testCount = 0;
};

#endif

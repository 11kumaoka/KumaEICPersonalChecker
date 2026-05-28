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

#include "podio/ROOTReader.h"
#include "podio/Frame.h"

#include "edm4hep/MCParticleCollection.h"

#include <edm4hep/SimTrackerHitCollection.h>
#include <edm4eic/RawTrackerHitCollection.h>
#include <edm4eic/MCRecoTrackerHitAssociationCollection.h>
#include "edm4eic/TrackerHitCollection.h"

#include "InputDataConfig.h"
#include "SimTrackerHitKuma.h"


class EventAna {

public:
    EventAna(const std::string& inputFile, const std::string& outputFile = "test.root");
    void EventLoop();

private:
    SimTrackerHitKuma makeTrkHitsV(const edm4eic::TrackerHitCollection& podioHits);
    std::vector<SimTrackerHitKuma> LoadTrackerHitsFromFrame(const podio::Frame& frame);

    void OFileInit();
    void EditHists();
    void OFileWrite();
    void ResetValuesForEachEvent();

    void FillEachSubDetRecDepE(const podio::Frame& frame);

    void FillEachSubDetDepE();


private:
    std::string m_iFileName;
    std::string m_oFileName;
    podio::ROOTReader m_reader;

    TFile* oFile;

    std::vector<Int_t> m_vTargetEvents;
    Int_t m_pubEvNum = 0;

    std::vector<SimTrackerHitKuma> m_trkDetsHits;

    double m_timeWindow = 2000.0;
    double m_timeSliceWidth = 20.0;

    // TOFBarrelRecHits, TOFEndcapRecHits, BackwardMPGDEndcapRecHits, ForwardMPGDEndcapRecHits, MPGDBarrelRecHits, OuterMPGDBarrelRecHits, SiBarrelVertexRecHits, SiBarrelTrackerRecHits, SiEndcapTrackerRecHits, B0TrackerRecHits
    Int_t m_TrackDetColors[10] = {880+10, 880+10, 880-2, 880-2, 880-2, 880-2, 880+4, 880+2, 880+2, 880+10,};
    // , ,  EcalBarrelScFiClusters, EcalEndcapNClusters, EcalEndcapPClusters, EcalFarForwardZDCClusters, EcalLumiSpecClusters, ForwardRomanPotRecHits, LFHCALClusters
    Int_t m_CalDetColors[8] = {860-3, 840-3, 600-9, 600-9, 880+1, 860+10, 880-6, 600-3};
    // B0ECalClusters:  860+7, ,EcalBarrelClusters: 880-4, EcalBarrelImagingClusters: 600-7
    // DIRCRawHits, DRICHRawHits, 
    Int_t m_PIDDetColors[2] = {860-6, 860};

    Int_t m_BKGColors[6] = {820+4, 860+10, 860-3, 800-3, 840+9, 900+9};

    std::array<TString, 6> m_physKindShortName = {"Phys", "SR", "Brems", "Coulomb", "Touscheck", "PGas"};
    std::array<TString, 7> m_trkShortDetName = {"BSi", "ESi", "BMPGD", "EMPGD", "BTOF", "ETOF", "B0"};

    TH1D* m_hBSiRecDepE;
    TH1D* m_hESiRecDepE;
    TH1D* m_hBMPGDRecDepE;
    TH1D* m_hEMPGDRecDepE;
    TH1D* m_hBTOFRecDepE;
    TH1D* m_hETOFRecDepE;

    TH1D* m_hDetRecEDep[7][6];
};

#endif
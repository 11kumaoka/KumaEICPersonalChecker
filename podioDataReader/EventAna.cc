#include "EventAna.h"
#include <iostream>

EventAna::EventAna(const std::string& inputFile, const std::string& outputFile) : 
    m_iFileName(inputFile), m_oFileName(outputFile)
{
    m_reader.openFile(m_iFileName);
}


void EventAna::Loop() {
    OFileInit();
    const auto nEvents = m_reader.getEntries("events");
    std::cout << "Number of events = " << nEvents << std::endl;

    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        m_trkDetsHits = LoadTrackerHitsFromFrame(frame);

        ResetValuesForEachEvent();
        if (iEvent >= 4) break;

    }
    OFileWrite();

}



void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;
}

void EventAna::OFileWrite() {
    std::cout << "OFileWrite" << std::endl;
    oFile->cd();


    oFile->Close();
}

void EventAna::ResetValuesForEachEvent() {
    m_trkDetsHits.clear();
}

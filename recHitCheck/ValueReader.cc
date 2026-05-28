#include "EventAna.h"

#include "InputDataConfig.h"
#include <iostream>
#include <string>

SimTrackerHitKuma EventAna::makeTrkHitsV(const edm4eic::TrackerHitCollection& podioHits)
{
    SimTrackerHitKuma detHits;
    detHits.reserveHits(podioHits.size());
    for (const auto& hit : podioHits) {
        const auto pos = hit.getPosition();
        detHits.loadHits(hit.getCellID(), hit.getEdep(),hit.getTime(), pos.x, pos.y, pos.z);
    }
    return detHits;

}

std::vector<SimTrackerHitKuma> EventAna::LoadTrackerHitsFromFrame(const podio::Frame& frame)
{
    std::vector<SimTrackerHitKuma> trkDetsHits;
    trkDetsHits.reserve(InputDataConfig::kTrkRecCollections.size());

    for (const auto collectionName : InputDataConfig::kTrkRecCollections) {
        const auto& hits = frame.get<edm4eic::TrackerHitCollection>(std::string(collectionName));
        trkDetsHits.push_back(makeTrkHitsV(hits));
        // std::cout << "Loaded " << collectionName<< " : " << hits.size()<< " hits" << std::endl;
    }
    return trkDetsHits;

}
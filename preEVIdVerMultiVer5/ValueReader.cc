#include "EventAna.h"

#include "InputDataConfig.h"

#include <cmath>
#include <string>

namespace {

constexpr Double_t kTimeOfFlightPerMm = 0.0034;

Double_t calibratedHitTime(Double_t time, Double_t x, Double_t y, Double_t z)
{
    return time - std::hypot(x, y, z) * kTimeOfFlightPerMm;
}

template <typename Collection, typename CellIdGetter, typename EnergyGetter>
SimTrackerHitKuma makeHits(
    const Collection& podioHits,
    CellIdGetter getCellId,
    EnergyGetter getEnergy)
{
    SimTrackerHitKuma detHits;
    detHits.reserveHits(podioHits.size());

    for (const auto& hit : podioHits) {
        const auto position = hit.getPosition();
        detHits.loadHits(
            getCellId(hit),
            getEnergy(hit),
            calibratedHitTime(hit.getTime(), position.x, position.y, position.z),
            position.x,
            position.y,
            position.z);
    }

    detHits.sortByTime();
    return detHits;
}

template <typename Collection, std::size_t N, typename HitBuilder>
std::vector<SimTrackerHitKuma> loadHitCollections(
    const podio::Frame& frame,
    const std::array<std::string_view, N>& collectionNames,
    HitBuilder buildHits)
{
    std::vector<SimTrackerHitKuma> detectorHits;
    detectorHits.reserve(collectionNames.size());

    for (const std::string_view collectionName : collectionNames) {
        const auto& hits = frame.get<Collection>(std::string(collectionName));
        detectorHits.emplace_back(buildHits(hits));
    }

    return detectorHits;
}

} // namespace

SimTrackerHitKuma EventAna::makeTrkHitsV(const edm4eic::TrackerHitCollection& podioHits)
{
    return makeHits(
        podioHits,
        [](const auto& hit) { return hit.getCellID(); },
        [](const auto& hit) { return hit.getEdep(); });
}

std::vector<SimTrackerHitKuma> EventAna::LoadTrackerHitsFromFrame(const podio::Frame& frame)
{
    return loadHitCollections<edm4eic::TrackerHitCollection>(
        frame,
        InputDataConfig::kTrkRecCollections,
        [this](const auto& hits) { return makeTrkHitsV(hits); });
}

SimTrackerHitKuma EventAna::makeCalHitsV(const edm4eic::CalorimeterHitCollection& podioHits)
{
    return makeHits(
        podioHits,
        [](const auto& hit) { return hit.getCellID(); },
        [](const auto& hit) { return hit.getEnergy(); });
}

std::vector<SimTrackerHitKuma> EventAna::LoadCalHitsFromFrame(const podio::Frame& frame)
{
    return loadHitCollections<edm4eic::CalorimeterHitCollection>(
        frame,
        InputDataConfig::kCalRecCollections,
        [this](const auto& hits) { return makeCalHitsV(hits); });
}

#ifndef INPUT_DATA_CONFIG_H
#define INPUT_DATA_CONFIG_H

#include <array>
#include <string_view>

namespace InputDataConfig {

    inline constexpr std::array<std::string_view, 10> kTrkCollections = {
        "SiBarrelVertexRecHits",
        "SiBarrelTrackerRecHits",
        "SiEndcapTrackerRecHits",
        "MPGDBarrelRecHits",
        "OuterMPGDBarrelRecHits",
        "BackwardMPGDEndcapRecHits",
        "ForwardMPGDEndcapRecHits",
        "TOFBarrelRecHits",
        "TOFEndcapRecHits",
        "B0TrackerRecHits"
    };


} // namespace InputDataConfig

#endif
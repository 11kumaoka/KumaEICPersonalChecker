#ifndef INPUT_DATA_CONFIG_H
#define INPUT_DATA_CONFIG_H

#include <array>
#include <string_view>

namespace InputDataConfig {
    
    inline constexpr std::array<std::string_view, 10> kTrkSimCollections = {
        "VertexBarrelHits",
        "SiBarrelHits",
        "TrackerEndcapHits",
        "MPGDBarrelHits",
        "OuterMPGDBarrelHits",
        "BackwardMPGDEndcapHits",
        "ForwardMPGDEndcapHits",
        "TOFBarrelHits",
        "TOFEndcapHits",
        "B0TrackerHits"
    };

    inline constexpr std::array<std::string_view, 10> kTrkRawCollections = {
        "SiBarrelVertexRawHits",
        "SiBarrelTrackerRawHits",
        "SiEndcapTrackerRawHits",
        "MPGDBarrelRawHits",
        "OuterMPGDBarrelRawHits",
        "BackwardMPGDEndcapRawHits",
        "ForwardMPGDEndcapRawHits",
        "TOFBarrelRawHits",
        "TOFEndcapRawHits",
        "B0TrackerRawHits"
    };

    inline constexpr std::array<std::string_view, 10> kTrkRawAssociationCollections = {
        "SiBarrelVertexRawHitAssociations",
        "SiBarrelTrackerRawHitAssociations",
        "SiEndcapTrackerRawHitAssociations",
        "MPGDBarrelRawHitAssociations",
        "OuterMPGDBarrelRawHitAssociations",
        "BackwardMPGDEndcapRawHitAssociations",
        "ForwardMPGDEndcapRawHitAssociations",
        "TOFBarrelRawHitAssociations",
        "TOFEndcapRawHitAssociations",
        "B0TrackerRawHitAssociations"
    };

    inline constexpr std::array<std::string_view, 10> kTrkRecCollections = {
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
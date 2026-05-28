#ifndef INPUT_DATA_CONFIG_H
#define INPUT_DATA_CONFIG_H

#include <array>
#include <string_view>

namespace InputDataConfig {

    inline constexpr std::array<std::string_view, 10> kTrkCollections = {
        "VertexBarrelHits",
        "SiBarrelHits",
        "TrackerEndcapHits",
        "MPGDBarrelHits",
        "OuterMPGDBarrelHits",
        "BackwardMPGDEndcapHits ",
        "ForwardMPGDEndcapHits",
        "TOFBarrelHits",
        "TOFEndcapHits",
        "B0TrackerHits"
    };


} // namespace InputDataConfig

#endif
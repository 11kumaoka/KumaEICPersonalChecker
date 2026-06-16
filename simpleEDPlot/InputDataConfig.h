#ifndef INPUT_DATA_CONFIG_H
#define INPUT_DATA_CONFIG_H

#include <array>
#include <string_view>

namespace InputDataConfig {
    
    inline constexpr std::array<std::string_view, 12> kTrkSimCollections = {
        "VertexBarrelHits",
        "SiBarrelHits",
        "TrackerEndcapHits",
        "MPGDBarrelHits",
        "OuterMPGDBarrelHits",
        "BackwardMPGDEndcapHits",
        "ForwardMPGDEndcapHits",
        "TOFBarrelHits",
        "TOFEndcapHits",
        "B0TrackerHits",
        "ForwardOffMTrackerHits",
        "ForwardRomanPotHits"
    };



    inline constexpr std::array<std::string_view, 12> kTrkRawCollections = {
        "SiBarrelVertexRawHits",
        "SiBarrelRawHits",
        "SiEndcapTrackerRawHits",
        "MPGDBarrelRawHits",
        "OuterMPGDBarrelRawHits",
        "BackwardMPGDEndcapRawHits",
        "ForwardMPGDEndcapRawHits",
        "TOFBarrelRawHits",
        "TOFEndcapRawHits",
        "B0TrackerRawHits",
        "ForwardOffMTrackerRawHits",
        "ForwardRomanPotRawHits"
    };

    inline constexpr std::array<std::string_view, 12> kTrkRawAssociationCollections = {
        "SiBarrelVertexRawHitAssociations",
        "SiBarrelRawHitAssociations",
        "SiEndcapTrackerRawHitAssociations",
        "MPGDBarrelRawHitAssociations",
        "OuterMPGDBarrelRawHitAssociations",
        "BackwardMPGDEndcapRawHitAssociations",
        "ForwardMPGDEndcapRawHitAssociations",
        "TOFBarrelRawHitAssociations",
        "TOFEndcapRawHitAssociations",
        "B0TrackerRawHitAssociations",
        "ForwardOffMTrackerRawHitAssociations",
        "ForwardRomanPotRawHitAssociations"
    };

    inline constexpr std::array<std::string_view, 12> kTrkRecCollections = {
        "SiBarrelVertexRecHits",
        "SiBarrelTrackerRecHits",
        "SiEndcapTrackerRecHits",
        "MPGDBarrelRecHits",
        "OuterMPGDBarrelRecHits",
        "BackwardMPGDEndcapRecHits",
        "ForwardMPGDEndcapRecHits",
        "TOFBarrelRecHits",
        "TOFEndcapRecHits",
        "B0TrackerRecHits",
        "ForwardOffMTrackerRecHits",
        "ForwardRomanPotRecHits"
    };



    
    inline constexpr std::array<std::string_view, 11> kCalCluCollections = {
        "B0ECalClusters",
        "EcalBarrelClusters",
        "EcalEndcapNClusters",
        "EcalEndcapPClusters", 
        "EcalFarForwardZDCClusters",
        "EcalLumiSpecClusters",
        "HcalBarrelClusters",
        "HcalEndcapNClusters",
        "HcalEndcapPInsertClusters",
        "HcalFarForwardZDCClusters",
        "LFHCALClusters"
    };
        // "EcalBarrelImagingClusters",
        // "EcalBarrelScFiClusters"


    inline constexpr std::array<std::string_view, 11> kCalClusterAssociations = {
        "B0ECalClusterAssociations",
        "EcalBarrelClusterAssociations",
        "EcalEndcapNClusterAssociations",
        "EcalEndcapPClusterAssociations",
        "EcalFarForwardZDCClusterAssociations",
        "EcalLumiSpecClusterAssociations",
        "HcalBarrelClusterAssociations",
        "HcalEndcapNClusterAssociations",
        "HcalEndcapPInsertClusterAssociations",
        "HcalFarForwardZDCClusterAssociations",
        "LFHCALClusterAssociations"
    };


        // "EcalBarrelImagingClusterAssociations",
        // "EcalBarrelScFiClusterAssociations"

} // namespace InputDataConfig

#endif
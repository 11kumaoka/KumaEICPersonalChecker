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

    inline constexpr std::array<std::string_view, 7> kCalSimCollections = {
        "B0ECalHits",
        "EcalBarrelImagingHits",
        "EcalBarrelScFiHits",
        "EcalEndcapNHits",
        "EcalEndcapPHits",
        "EcalFarForwardZDCHits",
        "EcalLumiSpecHits"
    };

    inline constexpr std::array<std::string_view, 7> kCalSimAssociations = {
        "B0ECalHitAssociations",
        "EcalBarrelImagingHitAssociations",
        "EcalBarrelScFiHitAssociations",
        "EcalEndcapNHitAssociations",
        "EcalEndcapPHitAssociations",
        "EcalFarForwardZDCHitAssociations",
        "EcalLumiSpecHitAssociations"
    };

    inline constexpr std::array<std::string_view, 7> kCalRawCollections = {
        "B0ECalRawHits",
        "EcalBarrelImagingRawHits",
        "EcalBarrelScFiRawHits",
        "EcalEndcapNRawHits",
        "EcalEndcapPRawHits",
        "EcalFarForwardZDCRawHits",
        "EcalLumiSpecRawHits"
    };
        // "HcalBarrelRawHits",
        // "HcalEndcapNRawHits",
        // "HcalEndcapPInsertRawHits",
        // "HcalFarForwardZDCRawHits",
        // "LFHCALRawHits",
        // "EcalBarrelImagingRawHits",
        // "EcalBarrelScFiRawHits",

    inline constexpr std::array<std::string_view, 7> kCalRawAssociations = {
        "B0ECalRawHitAssociations",
        "EcalBarrelImagingRawHitAssociations",
        "EcalBarrelScFiRawHitAssociations",
        "EcalEndcapNRawHitAssociations",
        "EcalEndcapPRawHitAssociations",
        "EcalFarForwardZDCRawHitAssociations",
        "EcalLumiSpecRawHitAssociations"
    };


    inline constexpr std::array<std::string_view, 7> kCalRecCollections = {
        "B0ECalRecHits",
        "EcalBarrelImagingRecHits",
        "EcalBarrelScFiRecHits",
        "EcalEndcapNRecHits",
        "EcalEndcapPRecHits",
        "EcalFarForwardZDCRecHits",
        "EcalLumiSpecRecHits"
    };
        // "HcalBarrelRecHits",
        // "HcalEndcapNRecHits",
        // "HcalEndcapPInsertRecHits",
        // "HcalFarForwardZDCRecHits",
        // "LFHCALRecHits",
        // "EcalBarrelImagingRecHits",
        // "EcalBarrelScFiRecHits",


    inline constexpr std::array<std::string_view, 7> kCalRecAssociations = {
        "B0ECalRecHitsAssociations",
        "EcalBarrelImagingRecHitsAssociations",
        "EcalBarrelScFiRecHitsAssociations",
        "EcalEndcapNRecHitsAssociations",
        "EcalEndcapPRecHitsAssociations",
        "EcalFarForwardZDCRecHitsAssociations",
        "EcalLumiSpecRecHitsAssociations"
    };

        // "HcalBarrelClusterAssociations",
        // "HcalEndcapNClusterAssociations",
        // "HcalEndcapPInsertClusterAssociations",
        // "HcalFarForwardZDCClusterAssociations",
        // "LFHCALClusterAssociations",
        // "EcalBarrelImagingClusterAssociations",
        // "EcalBarrelScFiClusterAssociations"


    inline constexpr std::array<std::string_view, 6> kCalCluCollections = {
        "B0ECalClusters",
        "EcalBarrelClusters",
        "EcalEndcapNClusters",
        "EcalEndcapPClusters", 
        "EcalFarForwardZDCClusters",
        "EcalLumiSpecClusters"
    };
        // "HcalBarrelClusters",
        // "HcalEndcapNClusters",
        // "HcalEndcapPInsertClusters",
        // "HcalFarForwardZDCClusters",
        // "LFHCALClusters",
        // "EcalBarrelImagingClusters",
        // "EcalBarrelScFiClusters",


    inline constexpr std::array<std::string_view, 6> kCalCluAssociations = {
        "B0ECalClusterAssociations",
        "EcalBarrelClusterAssociations",
        "EcalEndcapNClusterAssociations",
        "EcalEndcapPClusterAssociations",
        "EcalFarForwardZDCClusterAssociations",
        "EcalLumiSpecClusterAssociations"
    };

        // "HcalBarrelClusterAssociations",
        // "HcalEndcapNClusterAssociations",
        // "HcalEndcapPInsertClusterAssociations",
        // "HcalFarForwardZDCClusterAssociations",
        // "LFHCALClusterAssociations",
        // "EcalBarrelImagingClusterAssociations",
        // "EcalBarrelScFiClusterAssociations"

} // namespace InputDataConfig

#endif
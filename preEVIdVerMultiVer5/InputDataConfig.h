#ifndef INPUT_DATA_CONFIG_H
#define INPUT_DATA_CONFIG_H

#include <array>
#include <string_view>

namespace InputDataConfig {
    
    inline constexpr std::array<std::string_view, 12> kTrkSimCollections = {
        "B0TrackerHits",
        "TOFBarrelHits",
        "TOFEndcapHits",
        "MPGDBarrelHits",
        "OuterMPGDBarrelHits",
        "BackwardMPGDEndcapHits",
        "ForwardMPGDEndcapHits",
        "VertexBarrelHits",
        "SiBarrelHits",
        "TrackerEndcapHits",
        "ForwardOffMTrackerHits",
        "ForwardRomanPotHits"
    };


    inline constexpr std::array<std::string_view, 12> kTrkRawCollections = {
        "B0TrackerRawHits",
        "MPGDBarrelRawHits",
        "OuterMPGDBarrelRawHits",
        "BackwardMPGDEndcapRawHits",
        "ForwardMPGDEndcapRawHits",
        "TOFBarrelRawHits",
        "TOFEndcapRawHits",
        "SiBarrelVertexRawHits",
        "SiBarrelRawHits",
        "SiEndcapTrackerRawHits",
        "ForwardOffMTrackerRawHits",
        "ForwardRomanPotRawHits"
    };

    inline constexpr std::array<std::string_view, 12> kTrkRawAssociationCollections = {
        "B0TrackerRawHitAssociations",
        "TOFBarrelRawHitAssociations",
        "TOFEndcapRawHitAssociations",
        "MPGDBarrelRawHitAssociations",
        "OuterMPGDBarrelRawHitAssociations",
        "BackwardMPGDEndcapRawHitAssociations",
        "ForwardMPGDEndcapRawHitAssociations",
        "SiBarrelVertexRawHitAssociations",
        "SiBarrelRawHitAssociations",
        "SiEndcapTrackerRawHitAssociations",
        "ForwardOffMTrackerRawHitAssociations",
        "ForwardRomanPotRawHitAssociations"
    };

    inline constexpr std::array<std::string_view, 12> kTrkRecCollections = {
        "B0TrackerRecHits",
        "TOFBarrelRecHits",
        "TOFEndcapRecHits",
        "MPGDBarrelRecHits",
        "OuterMPGDBarrelRecHits",
        "BackwardMPGDEndcapRecHits",
        "ForwardMPGDEndcapRecHits",
        "SiBarrelVertexRecHits",
        "SiBarrelTrackerRecHits",
        "SiEndcapTrackerRecHits",
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
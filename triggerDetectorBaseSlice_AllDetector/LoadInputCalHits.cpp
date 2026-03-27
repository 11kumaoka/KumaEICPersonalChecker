#include <iostream>
#include <vector>
#include <string>

#include "triggerCombineChecker.h"
#include "SimTrackerHitKuma.h"

// Function to load input hits from a file
std::vector<SimTrackerHitKuma> triggerCombineChecker::LoadInputCalHits() {
    std::cout << "Loading input cal hits..." << std::endl;
    std::vector<SimTrackerHitKuma> hits;

    SimTrackerHitKuma B0TrackerRecHits;
    for (size_t iHit = 0; iHit < B0TrackerRecHits_; iHit++)
    {
        B0TrackerRecHits.loadHits(
            B0TrackerRecHits_,
            B0TrackerRecHits_cellID[iHit],
            B0TrackerRecHits_edep[iHit],
            B0TrackerRecHits_time[iHit],
            B0TrackerRecHits_position_x[iHit],
            B0TrackerRecHits_position_y[iHit],
            B0TrackerRecHits_position_z[iHit]
        );
    }
    hits.push_back(B0TrackerRecHits);


std::cout << "Loading EcalBarrelScFiClusters hit " << EcalBarrelScFiClusters_ << std::endl;
    SimTrackerHitKuma EcalBarrelScFiClusters;
    for (size_t iHit = 0; iHit < EcalBarrelScFiClusters_; iHit++)
    {
        EcalBarrelScFiClusters.loadHits(
            EcalBarrelScFiClusters_,
            EcalBarrelScFiClusters_nhits[iHit],
            EcalBarrelScFiClusters_energy[iHit],
            EcalBarrelScFiClusters_time[iHit],
            EcalBarrelScFiClusters_position_x[iHit],
            EcalBarrelScFiClusters_position_y[iHit],
            EcalBarrelScFiClusters_position_z[iHit]
        );
    }
    hits.push_back(EcalBarrelScFiClusters);

    
std::cout << "Loading EcalEndcapNClusters hit " << EcalEndcapNClusters_ << std::endl;
    SimTrackerHitKuma EcalEndcapNClusters;
    for (size_t iHit = 0; iHit < EcalEndcapNClusters_; iHit++)
    {
        EcalEndcapNClusters.loadHits(
            EcalEndcapNClusters_,
            EcalEndcapNClusters_nhits[iHit],
            EcalEndcapNClusters_energy[iHit],
            EcalEndcapNClusters_time[iHit],
            EcalEndcapNClusters_position_x[iHit],
            EcalEndcapNClusters_position_y[iHit],
            EcalEndcapNClusters_position_z[iHit]
        );
    }
    hits.push_back(EcalEndcapNClusters);

    SimTrackerHitKuma EcalEndcapPClusters;
    for (size_t iHit = 0; iHit < EcalEndcapPClusters_; iHit++)
    {
        std::cout << "Loading EcalEndcapPClusters hit " << iHit + 1 << "/" << EcalEndcapPClusters_ << std::endl;
        EcalEndcapPClusters.loadHits(
            EcalEndcapPClusters_,
            EcalEndcapPClusters_nhits[iHit],
            EcalEndcapPClusters_energy[iHit],
            EcalEndcapPClusters_time[iHit],
            EcalEndcapPClusters_position_x[iHit],
            EcalEndcapPClusters_position_y[iHit],
            EcalEndcapPClusters_position_z[iHit]
        );
    }
    hits.push_back(EcalEndcapPClusters);


    SimTrackerHitKuma EcalLumiSpecClusters;
    for (size_t iHit = 0; iHit < EcalLumiSpecClusters_; iHit++)
    {
        std::cout << "Loading EcalLumiSpecClusters hit " << iHit + 1 << "/" << EcalLumiSpecClusters_ << std::endl;
        EcalLumiSpecClusters.loadHits(
            EcalLumiSpecClusters_,
            EcalLumiSpecClusters_nhits[iHit],
            EcalLumiSpecClusters_energy[iHit],
            EcalLumiSpecClusters_time[iHit],
            EcalLumiSpecClusters_position_x[iHit],
            EcalLumiSpecClusters_position_y[iHit],
            EcalLumiSpecClusters_position_z[iHit]
        );
    }
    hits.push_back(EcalLumiSpecClusters);


    SimTrackerHitKuma ForwardOffMTrackerRecHits;
    for (size_t iHit = 0; iHit < ForwardOffMTrackerRecHits_; iHit++)
    {
        std::cout << "Loading ForwardOffMTrackerRecHits hit " << iHit + 1 << "/" << ForwardOffMTrackerRecHits_ << std::endl;
        ForwardOffMTrackerRecHits.loadHits(
            ForwardOffMTrackerRecHits_,
            ForwardOffMTrackerRecHits_cellID[iHit],
            ForwardOffMTrackerRecHits_edep[iHit],
            ForwardOffMTrackerRecHits_time[iHit],
            ForwardOffMTrackerRecHits_position_x[iHit],
            ForwardOffMTrackerRecHits_position_y[iHit],
            ForwardOffMTrackerRecHits_position_z[iHit]
        );
    }
    hits.push_back(ForwardOffMTrackerRecHits);


    SimTrackerHitKuma ForwardRomanPotRecHits;
    for (size_t iHit = 0; iHit < ForwardRomanPotRecHits_; iHit++)
    {
        std::cout << "Loading ForwardRomanPotRecHits hit " << iHit + 1 << "/" << ForwardRomanPotRecHits_ << std::endl;
        ForwardRomanPotRecHits.loadHits(
            ForwardRomanPotRecHits_,
            ForwardRomanPotRecHits_cellID[iHit],
            ForwardRomanPotRecHits_edep[iHit],
            ForwardRomanPotRecHits_time[iHit],
            ForwardRomanPotRecHits_position_x[iHit],
            ForwardRomanPotRecHits_position_y[iHit],
            ForwardRomanPotRecHits_position_z[iHit]
        );
    }
    hits.push_back(ForwardRomanPotRecHits);


        SimTrackerHitKuma LFHCALClusters;
    for (size_t iHit = 0; iHit < LFHCALClusters_; iHit++)
    {
        LFHCALClusters.loadHits(
            LFHCALClusters_,
            LFHCALClusters_nhits[iHit],
            LFHCALClusters_energy[iHit],
            LFHCALClusters_time[iHit],
            LFHCALClusters_position_x[iHit],
            LFHCALClusters_position_y[iHit],
            LFHCALClusters_position_z[iHit]
        );
    }
    hits.push_back(LFHCALClusters);

    return hits;
}



#include <iostream>
#include <vector>
#include <string>

#include "triggerCombineChecker.h"
#include "SimTrackerHitKuma.h"

// Function to load input hits from a file
std::vector<SimTrackerHitKuma> triggerCombineChecker::LoadInputHits() {

    std::vector<SimTrackerHitKuma> hits;

    SimTrackerHitKuma TOFBarrelRecHits;
    for (size_t iHit = 0; iHit < TOFBarrelRecHits_; iHit++)
    {
        TOFBarrelRecHits.loadHits(
            TOFBarrelRecHits_,
            TOFBarrelRecHits_cellID[iHit],
            TOFBarrelRecHits_edep[iHit],
            TOFBarrelRecHits_time[iHit],
            TOFBarrelRecHits_position_x[iHit],
            TOFBarrelRecHits_position_y[iHit],
            TOFBarrelRecHits_position_z[iHit]
        );
    }
    hits.push_back(TOFBarrelRecHits);

    SimTrackerHitKuma TOFEndcapRecHits;
    for (size_t iHit = 0; iHit < TOFEndcapRecHits_; iHit++)
    {
        TOFEndcapRecHits.loadHits(
            TOFEndcapRecHits_,
            TOFEndcapRecHits_cellID[iHit],
            TOFEndcapRecHits_edep[iHit],
            TOFEndcapRecHits_time[iHit],
            TOFEndcapRecHits_position_x[iHit],
            TOFEndcapRecHits_position_y[iHit],
            TOFEndcapRecHits_position_z[iHit]
        );
    }
    hits.push_back(TOFEndcapRecHits);

    SimTrackerHitKuma MPGDBarrelRecHits;
    for (size_t iHit = 0; iHit < MPGDBarrelRecHits_; iHit++)
    {
        MPGDBarrelRecHits.loadHits(
            MPGDBarrelRecHits_,
            MPGDBarrelRecHits_cellID[iHit],
            MPGDBarrelRecHits_edep[iHit],
            MPGDBarrelRecHits_time[iHit],
            MPGDBarrelRecHits_position_x[iHit],
            MPGDBarrelRecHits_position_y[iHit],
            MPGDBarrelRecHits_position_z[iHit]
        );
    }
    hits.push_back(MPGDBarrelRecHits);

    SimTrackerHitKuma OuterMPGDBarrelRecHits;
    for (size_t iHit = 0; iHit < OuterMPGDBarrelRecHits_; iHit++)
    {
        OuterMPGDBarrelRecHits.loadHits(
            OuterMPGDBarrelRecHits_,
            OuterMPGDBarrelRecHits_cellID[iHit],
            OuterMPGDBarrelRecHits_edep[iHit],
            OuterMPGDBarrelRecHits_time[iHit],
            OuterMPGDBarrelRecHits_position_x[iHit],
            OuterMPGDBarrelRecHits_position_y[iHit],
            OuterMPGDBarrelRecHits_position_z[iHit]
        );
    }
    hits.push_back(OuterMPGDBarrelRecHits);

    SimTrackerHitKuma BackwardMPGDEndcapRecHits;
    for (size_t iHit = 0; iHit < BackwardMPGDEndcapRecHits_; iHit++)
    {
        BackwardMPGDEndcapRecHits.loadHits(
            BackwardMPGDEndcapRecHits_,
            BackwardMPGDEndcapRecHits_cellID[iHit],
            BackwardMPGDEndcapRecHits_edep[iHit],
            BackwardMPGDEndcapRecHits_time[iHit],
            BackwardMPGDEndcapRecHits_position_x[iHit],
            BackwardMPGDEndcapRecHits_position_y[iHit],
            BackwardMPGDEndcapRecHits_position_z[iHit]
        );

    }
    hits.push_back(BackwardMPGDEndcapRecHits);


    SimTrackerHitKuma ForwardMPGDEndcapRecHits;
    for (size_t iHit = 0; iHit < ForwardMPGDEndcapRecHits_; iHit++)
    {
        ForwardMPGDEndcapRecHits.loadHits(
            ForwardMPGDEndcapRecHits_,
            ForwardMPGDEndcapRecHits_cellID[iHit],
            ForwardMPGDEndcapRecHits_edep[iHit],
            ForwardMPGDEndcapRecHits_time[iHit],
            ForwardMPGDEndcapRecHits_position_x[iHit],
            ForwardMPGDEndcapRecHits_position_y[iHit],
            ForwardMPGDEndcapRecHits_position_z[iHit]
        );
    }
    hits.push_back(ForwardMPGDEndcapRecHits);

    SimTrackerHitKuma SiBarrelVertexRecHits;
    for (size_t iHit = 0; iHit < SiBarrelVertexRecHits_; iHit++)
    {
        SiBarrelVertexRecHits.loadHits(
            SiBarrelVertexRecHits_,
            SiBarrelVertexRecHits_cellID[iHit],
            SiBarrelVertexRecHits_edep[iHit],
            SiBarrelVertexRecHits_time[iHit],
            SiBarrelVertexRecHits_position_x[iHit],
            SiBarrelVertexRecHits_position_y[iHit],
            SiBarrelVertexRecHits_position_z[iHit]
        );
    }
    hits.push_back(SiBarrelVertexRecHits);

    SimTrackerHitKuma SiBarrelTrackerRecHits;
    for (size_t iHit = 0; iHit < SiBarrelTrackerRecHits_; iHit++)
    {
        SiBarrelTrackerRecHits.loadHits(
            SiBarrelTrackerRecHits_,
            SiBarrelTrackerRecHits_cellID[iHit],
            SiBarrelTrackerRecHits_edep[iHit],
            SiBarrelTrackerRecHits_time[iHit],
            SiBarrelTrackerRecHits_position_x[iHit],
            SiBarrelTrackerRecHits_position_y[iHit],
            SiBarrelTrackerRecHits_position_z[iHit]
        );
    }
    hits.push_back(SiBarrelTrackerRecHits);
    

    SimTrackerHitKuma SiEndcapTrackerRecHits;
    for (size_t iHit = 0; iHit < SiEndcapTrackerRecHits_; iHit++)
    {
        SiEndcapTrackerRecHits.loadHits(
            SiEndcapTrackerRecHits_,
            SiEndcapTrackerRecHits_cellID[iHit],
            SiEndcapTrackerRecHits_edep[iHit],
            SiEndcapTrackerRecHits_time[iHit],
            SiEndcapTrackerRecHits_position_x[iHit],
            SiEndcapTrackerRecHits_position_y[iHit],
            SiEndcapTrackerRecHits_position_z[iHit]
        );
    }
    hits.push_back(SiEndcapTrackerRecHits);
    

    return hits;
}



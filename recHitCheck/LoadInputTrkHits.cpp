#include <iostream>
#include <vector>
#include <string>

#include "RecHitCheck.h"
#include "SimTrackerHitKuma.h"

// Function to load input hits from a file
std::vector<SimTrackerHitKuma> RecHitCheck::LoadInputTrkHits() {

    std::vector<SimTrackerHitKuma> hits;
    hits.reserve(9);

    hits.emplace_back();
    SimTrackerHitKuma& TOFBarrelRecHits = hits.back();

    // SimTrackerHitKuma TOFBarrelRecHits;
    TOFBarrelRecHits.reserveHits(TOFBarrelRecHits_);
    for (size_t iHit = 0; iHit < TOFBarrelRecHits_; iHit++)
    {
         TOFBarrelRecHits.loadHits(
            TOFBarrelRecHits_cellID[iHit],
            TOFBarrelRecHits_edep[iHit],
            TOFBarrelRecHits_time[iHit],
            TOFBarrelRecHits_position_x[iHit],
            TOFBarrelRecHits_position_y[iHit],
            TOFBarrelRecHits_position_z[iHit]
        );
    }
    // hits.push_back(std::move(TOFBarrelRecHits));

    hits.emplace_back();
    SimTrackerHitKuma& TOFEndcapRecHits = hits.back();
    // SimTrackerHitKuma TOFEndcapRecHits;
    TOFEndcapRecHits.reserveHits(TOFEndcapRecHits_);
    for (size_t iHit = 0; iHit < TOFEndcapRecHits_; iHit++)
    {
        TOFEndcapRecHits.loadHits(
            TOFEndcapRecHits_cellID[iHit],
            TOFEndcapRecHits_edep[iHit],
            TOFEndcapRecHits_time[iHit],
            TOFEndcapRecHits_position_x[iHit],
            TOFEndcapRecHits_position_y[iHit],
            TOFEndcapRecHits_position_z[iHit]
        );
    }
    // hits.push_back(std::move(TOFEndcapRecHits));

    hits.emplace_back();

    SimTrackerHitKuma& MPGDBarrelRecHits = hits.back();
    // SimTrackerHitKuma MPGDBarrelRecHits;
    MPGDBarrelRecHits.reserveHits(MPGDBarrelRecHits_);
    for (size_t iHit = 0; iHit < MPGDBarrelRecHits_; iHit++)
    {
        MPGDBarrelRecHits.loadHits(
            MPGDBarrelRecHits_cellID[iHit],
            MPGDBarrelRecHits_edep[iHit],
            MPGDBarrelRecHits_time[iHit],
            MPGDBarrelRecHits_position_x[iHit],
            MPGDBarrelRecHits_position_y[iHit],
            MPGDBarrelRecHits_position_z[iHit]
        );
    }
    // hits.push_back(std::move(MPGDBarrelRecHits));
    
    SimTrackerHitKuma OuterMPGDBarrelRecHits;
    OuterMPGDBarrelRecHits.reserveHits(OuterMPGDBarrelRecHits_);
    for (size_t iHit = 0; iHit < OuterMPGDBarrelRecHits_; iHit++)
    {
        OuterMPGDBarrelRecHits.loadHits(
            OuterMPGDBarrelRecHits_cellID[iHit],
            OuterMPGDBarrelRecHits_edep[iHit],
            OuterMPGDBarrelRecHits_time[iHit],
            OuterMPGDBarrelRecHits_position_x[iHit],
            OuterMPGDBarrelRecHits_position_y[iHit],
            OuterMPGDBarrelRecHits_position_z[iHit]
        );
    }
    hits.push_back(std::move(OuterMPGDBarrelRecHits));

    
    SimTrackerHitKuma BackwardMPGDEndcapRecHits;
    BackwardMPGDEndcapRecHits.reserveHits(BackwardMPGDEndcapRecHits_);
    for (size_t iHit = 0; iHit < BackwardMPGDEndcapRecHits_; iHit++)
    {
        BackwardMPGDEndcapRecHits.loadHits(
            BackwardMPGDEndcapRecHits_cellID[iHit],
            BackwardMPGDEndcapRecHits_edep[iHit],
            BackwardMPGDEndcapRecHits_time[iHit],
            BackwardMPGDEndcapRecHits_position_x[iHit],
            BackwardMPGDEndcapRecHits_position_y[iHit],
            BackwardMPGDEndcapRecHits_position_z[iHit]
        );

    }
    hits.push_back(std::move(BackwardMPGDEndcapRecHits));

    
    SimTrackerHitKuma ForwardMPGDEndcapRecHits;
    ForwardMPGDEndcapRecHits.reserveHits(ForwardMPGDEndcapRecHits_);
    for (size_t iHit = 0; iHit < ForwardMPGDEndcapRecHits_; iHit++)
    {
        ForwardMPGDEndcapRecHits.loadHits(
            ForwardMPGDEndcapRecHits_cellID[iHit],
            ForwardMPGDEndcapRecHits_edep[iHit],
            ForwardMPGDEndcapRecHits_time[iHit],
            ForwardMPGDEndcapRecHits_position_x[iHit],
            ForwardMPGDEndcapRecHits_position_y[iHit],
            ForwardMPGDEndcapRecHits_position_z[iHit]
        );
    }
    hits.push_back(std::move(ForwardMPGDEndcapRecHits));

    SimTrackerHitKuma SiBarrelVertexRecHits;
    SiBarrelVertexRecHits.reserveHits(SiBarrelVertexRecHits_);
    for (size_t iHit = 0; iHit < SiBarrelVertexRecHits_; iHit++)
    {
        SiBarrelVertexRecHits.loadHits(
            SiBarrelVertexRecHits_cellID[iHit],
            SiBarrelVertexRecHits_edep[iHit],
            SiBarrelVertexRecHits_time[iHit],
            SiBarrelVertexRecHits_position_x[iHit],
            SiBarrelVertexRecHits_position_y[iHit],
            SiBarrelVertexRecHits_position_z[iHit]
        );
    }
    hits.push_back(std::move(SiBarrelVertexRecHits));

    SimTrackerHitKuma SiBarrelTrackerRecHits;
    SiBarrelTrackerRecHits.reserveHits(SiBarrelTrackerRecHits_);
    for (size_t iHit = 0; iHit < SiBarrelTrackerRecHits_; iHit++)
    {
        SiBarrelTrackerRecHits.loadHits(
            SiBarrelTrackerRecHits_cellID[iHit],
            SiBarrelTrackerRecHits_edep[iHit],
            SiBarrelTrackerRecHits_time[iHit],
            SiBarrelTrackerRecHits_position_x[iHit],
            SiBarrelTrackerRecHits_position_y[iHit],
            SiBarrelTrackerRecHits_position_z[iHit]
        );
    }
    hits.push_back(std::move(SiBarrelTrackerRecHits));
    
    
    SimTrackerHitKuma SiEndcapTrackerRecHits;
    SiEndcapTrackerRecHits.reserveHits(SiEndcapTrackerRecHits_);
    for (size_t iHit = 0; iHit < SiEndcapTrackerRecHits_; iHit++)
    {
        SiEndcapTrackerRecHits.loadHits(
            SiEndcapTrackerRecHits_cellID[iHit],
            SiEndcapTrackerRecHits_edep[iHit],
            SiEndcapTrackerRecHits_time[iHit],
            SiEndcapTrackerRecHits_position_x[iHit],
            SiEndcapTrackerRecHits_position_y[iHit],
            SiEndcapTrackerRecHits_position_z[iHit]
        );
    }
    hits.push_back(std::move(SiEndcapTrackerRecHits));
    

std::cout << "Before local clear test" << std::endl;
std::cout << "local hits size/capacity = "
          << hits.size() << " / " << hits.capacity() << std::endl;

for (size_t i = 0; i < hits.size(); ++i) {
    std::cout << "  local collection " << i
              << " hit size = " << hits[i].getSize()
              << std::endl;
}

std::cout << "Now local hits.clear()" << std::endl;
hits.clear();
std::cout << "local hits.clear() OK" << std::endl;

    return hits;
}



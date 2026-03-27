#include <iostream>
#include <vector>
#include <string>

#include "triggerCombineChecker.h"
#include "SimTrackerHitKuma.h"

// Function to load input hits from a file
std::vector<SimTrackerHitKuma> triggerCombineChecker::LoadInputHits() {

    std::vector<SimTrackerHitKuma> hits;


    SimTrackerHitKuma TOFBarrelHits;
    for (size_t iHit = 0; iHit < TOFBarrelHits_; iHit++)
    {
        TOFBarrelHits.loadHits(
            TOFBarrelHits_,
            TOFBarrelHits_cellID[iHit],
            TOFBarrelHits_eDep[iHit],
            TOFBarrelHits_time[iHit],
            TOFBarrelHits_pathLength[iHit],
            TOFBarrelHits_quality[iHit],
            TOFBarrelHits_position_x[iHit],
            TOFBarrelHits_position_y[iHit],
            TOFBarrelHits_position_z[iHit],
            TOFBarrelHits_momentum_x[iHit],
            TOFBarrelHits_momentum_y[iHit],
            TOFBarrelHits_momentum_z[iHit]
        );
    }
    hits.push_back(TOFBarrelHits);

    SimTrackerHitKuma TOFEndcapHits;
    for (size_t iHit = 0; iHit < TOFEndcapHits_; iHit++)
    {
        TOFEndcapHits.loadHits(
            TOFEndcapHits_,
            TOFEndcapHits_cellID[iHit],
            TOFEndcapHits_eDep[iHit],
            TOFEndcapHits_time[iHit],
            TOFEndcapHits_pathLength[iHit],
            TOFEndcapHits_quality[iHit],
            TOFEndcapHits_position_x[iHit],
            TOFEndcapHits_position_y[iHit],
            TOFEndcapHits_position_z[iHit],
            TOFEndcapHits_momentum_x[iHit],
            TOFEndcapHits_momentum_y[iHit],
            TOFEndcapHits_momentum_z[iHit]
        );
    }
    hits.push_back(TOFEndcapHits);

    SimTrackerHitKuma MPGDBarrelHits;
    for (size_t iHit = 0; iHit < MPGDBarrelHits_; iHit++)
    {
        MPGDBarrelHits.loadHits(
            MPGDBarrelHits_,
            MPGDBarrelHits_cellID[iHit],
            MPGDBarrelHits_eDep[iHit],
            MPGDBarrelHits_time[iHit],
            MPGDBarrelHits_pathLength[iHit],
            MPGDBarrelHits_quality[iHit],
            MPGDBarrelHits_position_x[iHit],
            MPGDBarrelHits_position_y[iHit],
            MPGDBarrelHits_position_z[iHit],
            MPGDBarrelHits_momentum_x[iHit],
            MPGDBarrelHits_momentum_y[iHit],
            MPGDBarrelHits_momentum_z[iHit]
        );
    }
    hits.push_back(MPGDBarrelHits);

    SimTrackerHitKuma OuterMPGDBarrelHits;
    for (size_t iHit = 0; iHit < OuterMPGDBarrelHits_; iHit++)
    {
        OuterMPGDBarrelHits.loadHits(
            OuterMPGDBarrelHits_,
            OuterMPGDBarrelHits_cellID[iHit],
            OuterMPGDBarrelHits_eDep[iHit],
            OuterMPGDBarrelHits_time[iHit],
            OuterMPGDBarrelHits_pathLength[iHit],
            OuterMPGDBarrelHits_quality[iHit],
            OuterMPGDBarrelHits_position_x[iHit],
            OuterMPGDBarrelHits_position_y[iHit],
            OuterMPGDBarrelHits_position_z[iHit],
            OuterMPGDBarrelHits_momentum_x[iHit],
            OuterMPGDBarrelHits_momentum_y[iHit],
            OuterMPGDBarrelHits_momentum_z[iHit]
        );
    }
    hits.push_back(OuterMPGDBarrelHits);

    SimTrackerHitKuma BackwardMPGDEndcapHits;
    for (size_t iHit = 0; iHit < BackwardMPGDEndcapHits_; iHit++)
    {
        BackwardMPGDEndcapHits.loadHits(
            BackwardMPGDEndcapHits_,
            BackwardMPGDEndcapHits_cellID[iHit],
            BackwardMPGDEndcapHits_eDep[iHit],
            BackwardMPGDEndcapHits_time[iHit],
            BackwardMPGDEndcapHits_pathLength[iHit],
            BackwardMPGDEndcapHits_quality[iHit],
            BackwardMPGDEndcapHits_position_x[iHit],
            BackwardMPGDEndcapHits_position_y[iHit],
            BackwardMPGDEndcapHits_position_z[iHit],
            BackwardMPGDEndcapHits_momentum_x[iHit],
            BackwardMPGDEndcapHits_momentum_y[iHit],
            BackwardMPGDEndcapHits_momentum_z[iHit]
        );

    }
    hits.push_back(BackwardMPGDEndcapHits);

    SimTrackerHitKuma ForwardMPGDEndcapHits;
    for (size_t iHit = 0; iHit < ForwardMPGDEndcapHits_; iHit++)
    {
        ForwardMPGDEndcapHits.loadHits(
            ForwardMPGDEndcapHits_,
            ForwardMPGDEndcapHits_cellID[iHit],
            ForwardMPGDEndcapHits_eDep[iHit],
            ForwardMPGDEndcapHits_time[iHit],
            ForwardMPGDEndcapHits_pathLength[iHit],
            ForwardMPGDEndcapHits_quality[iHit],
            ForwardMPGDEndcapHits_position_x[iHit],
            ForwardMPGDEndcapHits_position_y[iHit],
            ForwardMPGDEndcapHits_position_z[iHit],
            ForwardMPGDEndcapHits_momentum_x[iHit],
            ForwardMPGDEndcapHits_momentum_y[iHit],
            ForwardMPGDEndcapHits_momentum_z[iHit]
        );
    }
    hits.push_back(ForwardMPGDEndcapHits);

    SimTrackerHitKuma VertexBarrelHits;
    for (size_t iHit = 0; iHit < VertexBarrelHits_; iHit++)
    {
        VertexBarrelHits.loadHits(
            VertexBarrelHits_,
            VertexBarrelHits_cellID[iHit],
            VertexBarrelHits_eDep[iHit],
            VertexBarrelHits_time[iHit],
            VertexBarrelHits_pathLength[iHit],
            VertexBarrelHits_quality[iHit],
            VertexBarrelHits_position_x[iHit],
            VertexBarrelHits_position_y[iHit],
            VertexBarrelHits_position_z[iHit],
            VertexBarrelHits_momentum_x[iHit],
            VertexBarrelHits_momentum_y[iHit],
            VertexBarrelHits_momentum_z[iHit]
        );
    }
    hits.push_back(VertexBarrelHits);

    SimTrackerHitKuma SiBarrelHits;
    for (size_t iHit = 0; iHit < SiBarrelHits_; iHit++)
    {
        SiBarrelHits.loadHits(
            SiBarrelHits_,
            SiBarrelHits_cellID[iHit],
            SiBarrelHits_eDep[iHit],
            SiBarrelHits_time[iHit],
            SiBarrelHits_pathLength[iHit],
            SiBarrelHits_quality[iHit],
            SiBarrelHits_position_x[iHit],
            SiBarrelHits_position_y[iHit],
            SiBarrelHits_position_z[iHit],
            SiBarrelHits_momentum_x[iHit],
            SiBarrelHits_momentum_y[iHit],
            SiBarrelHits_momentum_z[iHit]
        );
    }
    hits.push_back(SiBarrelHits);

    SimTrackerHitKuma TrackerEndcapHits;
    for (size_t iHit = 0; iHit < TrackerEndcapHits_; iHit++)
    {
        TrackerEndcapHits.loadHits(
            TrackerEndcapHits_,
            TrackerEndcapHits_cellID[iHit],
            TrackerEndcapHits_eDep[iHit],
            TrackerEndcapHits_time[iHit],
            TrackerEndcapHits_pathLength[iHit],
            TrackerEndcapHits_quality[iHit],
            TrackerEndcapHits_position_x[iHit],
            TrackerEndcapHits_position_y[iHit],
            TrackerEndcapHits_position_z[iHit],
            TrackerEndcapHits_momentum_x[iHit],
            TrackerEndcapHits_momentum_y[iHit],
            TrackerEndcapHits_momentum_z[iHit]
        );
    }
    hits.push_back(TrackerEndcapHits);

    SimTrackerHitKuma TaggerTrackerHits;
    for (size_t iHit = 0; iHit < TaggerTrackerHits_; iHit++)
    {
        TaggerTrackerHits.loadHits(
            TaggerTrackerHits_,
            TaggerTrackerHits_cellID[iHit],
            TaggerTrackerHits_eDep[iHit],
            TaggerTrackerHits_time[iHit],
            TaggerTrackerHits_pathLength[iHit],
            TaggerTrackerHits_quality[iHit],
            TaggerTrackerHits_position_x[iHit],
            TaggerTrackerHits_position_y[iHit],
            TaggerTrackerHits_position_z[iHit],
            TaggerTrackerHits_momentum_x[iHit],
            TaggerTrackerHits_momentum_y[iHit],
            TaggerTrackerHits_momentum_z[iHit]
        );
    }
    hits.push_back(TaggerTrackerHits);


    SimTrackerHitKuma B0TrackerHits;
    for (size_t iHit = 0; iHit < B0TrackerHits_; iHit++)
    {        
        B0TrackerHits.loadHits(
            B0TrackerHits_,
            B0TrackerHits_cellID[iHit],
            B0TrackerHits_eDep[iHit],
            B0TrackerHits_time[iHit],
            B0TrackerHits_pathLength[iHit],
            B0TrackerHits_quality[iHit],
            B0TrackerHits_position_x[iHit],
            B0TrackerHits_position_y[iHit],
            B0TrackerHits_position_z[iHit],
            B0TrackerHits_momentum_x[iHit],
            B0TrackerHits_momentum_y[iHit],
            B0TrackerHits_momentum_z[iHit]
        );
    }
    hits.push_back(B0TrackerHits);

    SimTrackerHitKuma DIRCBarHits;
    for (size_t iHit = 0; iHit < DIRCBarHits_; iHit++)
    {
        DIRCBarHits.loadHits(
            DIRCBarHits_,
            DIRCBarHits_cellID[iHit],
            DIRCBarHits_eDep[iHit],
            DIRCBarHits_time[iHit],
            DIRCBarHits_pathLength[iHit],
            DIRCBarHits_quality[iHit],
            DIRCBarHits_position_x[iHit],
            DIRCBarHits_position_y[iHit],
            DIRCBarHits_position_z[iHit],
            DIRCBarHits_momentum_x[iHit],
            DIRCBarHits_momentum_y[iHit],
            DIRCBarHits_momentum_z[iHit]
        );
    }
    hits.push_back(DIRCBarHits);

    SimTrackerHitKuma DRICHHits;
    for (size_t iHit = 0; iHit < DRICHHits_; iHit++)
    {
        DRICHHits.loadHits(
            DRICHHits_,
            DRICHHits_cellID[iHit],
            DRICHHits_eDep[iHit],
            DRICHHits_time[iHit],
            DRICHHits_pathLength[iHit],
            DRICHHits_quality[iHit],
            DRICHHits_position_x[iHit],
            DRICHHits_position_y[iHit],
            DRICHHits_position_z[iHit],
            DRICHHits_momentum_x[iHit],
            DRICHHits_momentum_y[iHit],
            DRICHHits_momentum_z[iHit]
        );
    }
    hits.push_back(DRICHHits);

    SimTrackerHitKuma ForwardOffMTrackerHits;
    for (size_t iHit = 0; iHit < ForwardOffMTrackerHits_; iHit++)
    {
        ForwardOffMTrackerHits.loadHits(
            ForwardOffMTrackerHits_,
            ForwardOffMTrackerHits_cellID[iHit],
            ForwardOffMTrackerHits_eDep[iHit],
            ForwardOffMTrackerHits_time[iHit],
            ForwardOffMTrackerHits_pathLength[iHit],
            ForwardOffMTrackerHits_quality[iHit],
            ForwardOffMTrackerHits_position_x[iHit],
            ForwardOffMTrackerHits_position_y[iHit],
            ForwardOffMTrackerHits_position_z[iHit],
            ForwardOffMTrackerHits_momentum_x[iHit],
            ForwardOffMTrackerHits_momentum_y[iHit],
            ForwardOffMTrackerHits_momentum_z[iHit]
        );
    }
    hits.push_back(ForwardOffMTrackerHits);

    SimTrackerHitKuma ForwardRomanPotHits;
    for (size_t iHit = 0; iHit < ForwardRomanPotHits_; iHit++)
    {
        ForwardRomanPotHits.loadHits(
            ForwardRomanPotHits_,
            ForwardRomanPotHits_cellID[iHit],
            ForwardRomanPotHits_eDep[iHit],
            ForwardRomanPotHits_time[iHit],
            ForwardRomanPotHits_pathLength[iHit],
            ForwardRomanPotHits_quality[iHit],
            ForwardRomanPotHits_position_x[iHit],
            ForwardRomanPotHits_position_y[iHit],
            ForwardRomanPotHits_position_z[iHit],
            ForwardRomanPotHits_momentum_x[iHit],
            ForwardRomanPotHits_momentum_y[iHit],
            ForwardRomanPotHits_momentum_z[iHit]
        );
    }
    hits.push_back(ForwardRomanPotHits);
    
    SimTrackerHitKuma LumiSpecTrackerHits;
    for (size_t iHit = 0; iHit < LumiSpecTrackerHits_; iHit++)
    {
        LumiSpecTrackerHits.loadHits(
            LumiSpecTrackerHits_,
            LumiSpecTrackerHits_cellID[iHit],
            LumiSpecTrackerHits_eDep[iHit],
            LumiSpecTrackerHits_time[iHit],
            LumiSpecTrackerHits_pathLength[iHit],
            LumiSpecTrackerHits_quality[iHit],
            LumiSpecTrackerHits_position_x[iHit],
            LumiSpecTrackerHits_position_y[iHit],
            LumiSpecTrackerHits_position_z[iHit],
            LumiSpecTrackerHits_momentum_x[iHit],
            LumiSpecTrackerHits_momentum_y[iHit],
            LumiSpecTrackerHits_momentum_z[iHit]
        );
    }
    hits.push_back(LumiSpecTrackerHits);

    SimTrackerHitKuma RICHEndcapNHits;
    for (size_t iHit = 0; iHit < RICHEndcapNHits_; iHit++)
    {
        RICHEndcapNHits.loadHits(
            RICHEndcapNHits_,
            RICHEndcapNHits_cellID[iHit],
            RICHEndcapNHits_eDep[iHit],
            RICHEndcapNHits_time[iHit],
            RICHEndcapNHits_pathLength[iHit],
            RICHEndcapNHits_quality[iHit],
            RICHEndcapNHits_position_x[iHit],
            RICHEndcapNHits_position_y[iHit],
            RICHEndcapNHits_position_z[iHit],
            RICHEndcapNHits_momentum_x[iHit],
            RICHEndcapNHits_momentum_y[iHit],
            RICHEndcapNHits_momentum_z[iHit]
        );
    }
    hits.push_back(RICHEndcapNHits);



    return hits;
}



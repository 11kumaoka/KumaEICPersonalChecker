
#ifndef DEFROOTBRANCHES_H
#define DEFROOTBRANCHES_H
   
   // List of branches
   TBranch        *b_EventHeader_;   //!
   TBranch        *b_EventHeader_eventNumber;   //!
   TBranch        *b_EventHeader_runNumber;   //!
   TBranch        *b_EventHeader_timeStamp;   //!
   TBranch        *b_EventHeader_weight;   //!
   TBranch        *b_EventHeader_weights_begin;   //!
   TBranch        *b_EventHeader_weights_end;   //!

   TBranch        *b_MCParticles_;   //!
   TBranch        *b_MCParticles_PDG;   //!
   TBranch        *b_MCParticles_generatorStatus;   //!
   TBranch        *b_MCParticles_simulatorStatus;   //!
   TBranch        *b_MCParticles_charge;   //!
   TBranch        *b_MCParticles_time;   //!
   TBranch        *b_MCParticles_mass;   //!
   TBranch        *b_MCParticles_vertex_x;   //!
   TBranch        *b_MCParticles_vertex_y;   //!
   TBranch        *b_MCParticles_vertex_z;   //!
   TBranch        *b_MCParticles_endpoint_x;   //!
   TBranch        *b_MCParticles_endpoint_y;   //!
   TBranch        *b_MCParticles_endpoint_z;   //!
   TBranch        *b_MCParticles_momentum_x;   //!
   TBranch        *b_MCParticles_momentum_y;   //!
   TBranch        *b_MCParticles_momentum_z;   //!
   TBranch        *b_MCParticles_momentumAtEndpoint_x;   //!
   TBranch        *b_MCParticles_momentumAtEndpoint_y;   //!
   TBranch        *b_MCParticles_momentumAtEndpoint_z;   //!
   TBranch        *b_MCParticles_spin_x;   //!
   TBranch        *b_MCParticles_spin_y;   //!
   TBranch        *b_MCParticles_spin_z;   //!
   TBranch        *b_MCParticles_colorFlow_a;   //!
   TBranch        *b_MCParticles_colorFlow_b;   //!
   TBranch        *b_MCParticles_parents_begin;   //!
   TBranch        *b_MCParticles_parents_end;   //!
   TBranch        *b_MCParticles_daughters_begin;   //!
   TBranch        *b_MCParticles_daughters_end;   //!
   TBranch        *b__MCParticles_parents_;   //!
   TBranch        *b__MCParticles_parents_index;   //!
   TBranch        *b__MCParticles_parents_collectionID;   //!
   TBranch        *b__MCParticles_daughters_;   //!
   TBranch        *b__MCParticles_daughters_index;   //!
   TBranch        *b__MCParticles_daughters_collectionID;   //!


   TBranch        *b_BackwardMPGDEndcapRecHits_;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_cellID;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_position_x;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_position_y;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_position_z;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_positionError_xx;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_positionError_yy;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_positionError_zz;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_time;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_timeError;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_edep;   //!
   TBranch        *b_BackwardMPGDEndcapRecHits_edepError;   //!
   
   TBranch        *b_ForwardMPGDEndcapRecHits_;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_cellID;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_position_x;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_position_y;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_position_z;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_positionError_xx;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_positionError_yy;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_positionError_zz;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_time;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_timeError;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_edep;   //!
   TBranch        *b_ForwardMPGDEndcapRecHits_edepError;   //!
   
   TBranch        *b_MPGDBarrelRecHits_;   //!
   TBranch        *b_MPGDBarrelRecHits_cellID;   //!
   TBranch        *b_MPGDBarrelRecHits_position_x;   //!
   TBranch        *b_MPGDBarrelRecHits_position_y;   //!
   TBranch        *b_MPGDBarrelRecHits_position_z;   //!
   TBranch        *b_MPGDBarrelRecHits_positionError_xx;   //!
   TBranch        *b_MPGDBarrelRecHits_positionError_yy;   //!
   TBranch        *b_MPGDBarrelRecHits_positionError_zz;   //!
   TBranch        *b_MPGDBarrelRecHits_time;   //!
   TBranch        *b_MPGDBarrelRecHits_timeError;   //!
   TBranch        *b_MPGDBarrelRecHits_edep;   //!
   TBranch        *b_MPGDBarrelRecHits_edepError;   //!
   
   TBranch        *b_OuterMPGDBarrelRecHits_;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_cellID;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_position_x;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_position_y;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_position_z;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_positionError_xx;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_positionError_yy;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_positionError_zz;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_time;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_timeError;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_edep;   //!
   TBranch        *b_OuterMPGDBarrelRecHits_edepError;   //!

   TBranch        *b_SiBarrelTrackerRecHits_;   //!
   TBranch        *b_SiBarrelTrackerRecHits_cellID;   //!
   TBranch        *b_SiBarrelTrackerRecHits_position_x;   //!
   TBranch        *b_SiBarrelTrackerRecHits_position_y;   //!
   TBranch        *b_SiBarrelTrackerRecHits_position_z;   //!
   TBranch        *b_SiBarrelTrackerRecHits_positionError_xx;   //!
   TBranch        *b_SiBarrelTrackerRecHits_positionError_yy;   //!
   TBranch        *b_SiBarrelTrackerRecHits_positionError_zz;   //!
   TBranch        *b_SiBarrelTrackerRecHits_time;   //!
   TBranch        *b_SiBarrelTrackerRecHits_timeError;   //!
   TBranch        *b_SiBarrelTrackerRecHits_edep;   //!
   TBranch        *b_SiBarrelTrackerRecHits_edepError;   //!
   
   TBranch        *b_SiBarrelVertexRecHits_;   //!
   TBranch        *b_SiBarrelVertexRecHits_cellID;   //!
   TBranch        *b_SiBarrelVertexRecHits_position_x;   //!
   TBranch        *b_SiBarrelVertexRecHits_position_y;   //!
   TBranch        *b_SiBarrelVertexRecHits_position_z;   //!
   TBranch        *b_SiBarrelVertexRecHits_positionError_xx;   //!
   TBranch        *b_SiBarrelVertexRecHits_positionError_yy;   //!
   TBranch        *b_SiBarrelVertexRecHits_positionError_zz;   //!
   TBranch        *b_SiBarrelVertexRecHits_time;   //!
   TBranch        *b_SiBarrelVertexRecHits_timeError;   //!
   TBranch        *b_SiBarrelVertexRecHits_edep;   //!
   TBranch        *b_SiBarrelVertexRecHits_edepError;   //!
   
   TBranch        *b_SiEndcapTrackerRecHits_;   //!
   TBranch        *b_SiEndcapTrackerRecHits_cellID;   //!
   TBranch        *b_SiEndcapTrackerRecHits_position_x;   //!
   TBranch        *b_SiEndcapTrackerRecHits_position_y;   //!
   TBranch        *b_SiEndcapTrackerRecHits_position_z;   //!
   TBranch        *b_SiEndcapTrackerRecHits_positionError_xx;   //!
   TBranch        *b_SiEndcapTrackerRecHits_positionError_yy;   //!
   TBranch        *b_SiEndcapTrackerRecHits_positionError_zz;   //!
   TBranch        *b_SiEndcapTrackerRecHits_time;   //!
   TBranch        *b_SiEndcapTrackerRecHits_timeError;   //!
   TBranch        *b_SiEndcapTrackerRecHits_edep;   //!
   TBranch        *b_SiEndcapTrackerRecHits_edepError;   //!

   TBranch        *b_TOFBarrelRecHits_;   //!
   TBranch        *b_TOFBarrelRecHits_cellID;   //!
   TBranch        *b_TOFBarrelRecHits_position_x;   //!
   TBranch        *b_TOFBarrelRecHits_position_y;   //!
   TBranch        *b_TOFBarrelRecHits_position_z;   //!
   TBranch        *b_TOFBarrelRecHits_positionError_xx;   //!
   TBranch        *b_TOFBarrelRecHits_positionError_yy;   //!
   TBranch        *b_TOFBarrelRecHits_positionError_zz;   //!
   TBranch        *b_TOFBarrelRecHits_time;   //!
   TBranch        *b_TOFBarrelRecHits_timeError;   //!
   TBranch        *b_TOFBarrelRecHits_edep;   //!
   TBranch        *b_TOFBarrelRecHits_edepError;   //!
   
   TBranch        *b_TOFEndcapRecHits_;   //!
   TBranch        *b_TOFEndcapRecHits_cellID;   //!
   TBranch        *b_TOFEndcapRecHits_position_x;   //!
   TBranch        *b_TOFEndcapRecHits_position_y;   //!
   TBranch        *b_TOFEndcapRecHits_position_z;   //!
   TBranch        *b_TOFEndcapRecHits_positionError_xx;   //!
   TBranch        *b_TOFEndcapRecHits_positionError_yy;   //!
   TBranch        *b_TOFEndcapRecHits_positionError_zz;   //!
   TBranch        *b_TOFEndcapRecHits_time;   //!
   TBranch        *b_TOFEndcapRecHits_timeError;   //!
   TBranch        *b_TOFEndcapRecHits_edep;   //!
   TBranch        *b_TOFEndcapRecHits_edepError;   //!


   TBranch        *b_B0TrackerRecHits_;   //!
   TBranch        *b_B0TrackerRecHits_cellID;   //!
   TBranch        *b_B0TrackerRecHits_position_x;   //!
   TBranch        *b_B0TrackerRecHits_position_y;   //!
   TBranch        *b_B0TrackerRecHits_position_z;   //!
   TBranch        *b_B0TrackerRecHits_positionError_xx;   //!
   TBranch        *b_B0TrackerRecHits_positionError_yy;   //!
   TBranch        *b_B0TrackerRecHits_positionError_zz;   //!
   TBranch        *b_B0TrackerRecHits_time;   //!
   TBranch        *b_B0TrackerRecHits_timeError;   //!
   TBranch        *b_B0TrackerRecHits_edep;   //!
   TBranch        *b_B0TrackerRecHits_edepError;   //!


   TBranch        *b_B0ECalClusters_;   //!
   TBranch        *b_B0ECalClusters_type;   //!
   TBranch        *b_B0ECalClusters_energy;   //!
   TBranch        *b_B0ECalClusters_energyError;   //!
   TBranch        *b_B0ECalClusters_time;   //!
   TBranch        *b_B0ECalClusters_timeError;   //!
   TBranch        *b_B0ECalClusters_nhits;   //!
   TBranch        *b_B0ECalClusters_position_x;   //!
   TBranch        *b_B0ECalClusters_position_y;   //!
   TBranch        *b_B0ECalClusters_position_z;   //!
   TBranch        *b_B0ECalClusters_positionError_xx;   //!
   TBranch        *b_B0ECalClusters_positionError_yy;   //!
   TBranch        *b_B0ECalClusters_positionError_zz;   //!
   TBranch        *b_B0ECalClusters_positionError_xy;   //!
   TBranch        *b_B0ECalClusters_positionError_xz;   //!
   TBranch        *b_B0ECalClusters_positionError_yz;   //!

   TBranch        *b_B0ECalRawHits_;   //!
   TBranch        *b_B0ECalRawHits_cellID;   //!
   TBranch        *b_B0ECalRawHits_amplitude;   //!
   TBranch        *b_B0ECalRawHits_timeStamp;   //!
   TBranch        *b_B0ECalRecHits_;   //!
   TBranch        *b_B0ECalRecHits_cellID;   //!
   TBranch        *b_B0ECalRecHits_energy;   //!
   TBranch        *b_B0ECalRecHits_energyError;   //!
   TBranch        *b_B0ECalRecHits_time;   //!
   TBranch        *b_B0ECalRecHits_timeError;   //!
   TBranch        *b_B0ECalRecHits_position_x;   //!
   TBranch        *b_B0ECalRecHits_position_y;   //!
   TBranch        *b_B0ECalRecHits_position_z;   //!

   TBranch        *b_DIRCRawHits_;   //!
   TBranch        *b_DIRCRawHits_cellID;   //!
   TBranch        *b_DIRCRawHits_charge;   //!
   TBranch        *b_DIRCRawHits_timeStamp;   //!

   TBranch        *b_DRICHRawHits_;   //!
   TBranch        *b_DRICHRawHits_cellID;   //!
   TBranch        *b_DRICHRawHits_charge;   //!
   TBranch        *b_DRICHRawHits_timeStamp;   //!


   TBranch        *b_EcalBarrelClusters_;   //!
   TBranch        *b_EcalBarrelClusters_type;   //!
   TBranch        *b_EcalBarrelClusters_energy;   //!
   TBranch        *b_EcalBarrelClusters_energyError;   //!
   TBranch        *b_EcalBarrelClusters_time;   //!
   TBranch        *b_EcalBarrelClusters_timeError;   //!
   TBranch        *b_EcalBarrelClusters_nhits;   //!
   TBranch        *b_EcalBarrelClusters_position_x;   //!
   TBranch        *b_EcalBarrelClusters_position_y;   //!
   TBranch        *b_EcalBarrelClusters_position_z;   //!
   TBranch        *b_EcalBarrelClusters_positionError_xx;   //!
   TBranch        *b_EcalBarrelClusters_positionError_yy;   //!
   TBranch        *b_EcalBarrelClusters_positionError_zz;   //!
   TBranch        *b_EcalBarrelClusters_positionError_xy;   //!
   TBranch        *b_EcalBarrelClusters_positionError_xz;   //!
   TBranch        *b_EcalBarrelClusters_positionError_yz;   //!

   TBranch        *b_EcalBarrelImagingClusters_;   //!
   TBranch        *b_EcalBarrelImagingClusters_type;   //!
   TBranch        *b_EcalBarrelImagingClusters_energy;   //!
   TBranch        *b_EcalBarrelImagingClusters_energyError;   //!
   TBranch        *b_EcalBarrelImagingClusters_time;   //!
   TBranch        *b_EcalBarrelImagingClusters_timeError;   //!
   TBranch        *b_EcalBarrelImagingClusters_nhits;   //!
   TBranch        *b_EcalBarrelImagingClusters_position_x;   //!
   TBranch        *b_EcalBarrelImagingClusters_position_y;   //!
   TBranch        *b_EcalBarrelImagingClusters_position_z;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_xx;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_yy;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_zz;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_xy;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_xz;   //!
   TBranch        *b_EcalBarrelImagingClusters_positionError_yz;   //!

   TBranch        *b_EcalBarrelImagingRecHits_;   //!
   TBranch        *b_EcalBarrelImagingRecHits_cellID;   //!
   TBranch        *b_EcalBarrelImagingRecHits_energy;   //!
   TBranch        *b_EcalBarrelImagingRecHits_energyError;   //!
   TBranch        *b_EcalBarrelImagingRecHits_time;   //!
   TBranch        *b_EcalBarrelImagingRecHits_timeError;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_x;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_y;   //!
   TBranch        *b_EcalBarrelImagingRecHits_position_z;   //!

   TBranch        *b_EcalBarrelScFiClusters_;   //!
   TBranch        *b_EcalBarrelScFiClusters_type;   //!
   TBranch        *b_EcalBarrelScFiClusters_energy;   //!
   TBranch        *b_EcalBarrelScFiClusters_energyError;   //!
   TBranch        *b_EcalBarrelScFiClusters_time;   //!
   TBranch        *b_EcalBarrelScFiClusters_timeError;   //!
   TBranch        *b_EcalBarrelScFiClusters_nhits;   //!
   TBranch        *b_EcalBarrelScFiClusters_position_x;   //!
   TBranch        *b_EcalBarrelScFiClusters_position_y;   //!
   TBranch        *b_EcalBarrelScFiClusters_position_z;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_xx;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_yy;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_zz;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_xy;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_xz;   //!
   TBranch        *b_EcalBarrelScFiClusters_positionError_yz;   //!

   TBranch        *b_EcalBarrelScFiRecHits_;   //!
   TBranch        *b_EcalBarrelScFiRecHits_cellID;   //!
   TBranch        *b_EcalBarrelScFiRecHits_energy;   //!
   TBranch        *b_EcalBarrelScFiRecHits_energyError;   //!
   TBranch        *b_EcalBarrelScFiRecHits_time;   //!
   TBranch        *b_EcalBarrelScFiRecHits_timeError;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_x;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_y;   //!
   TBranch        *b_EcalBarrelScFiRecHits_position_z;   //!

   TBranch        *b_EcalEndcapNClusters_;   //!
   TBranch        *b_EcalEndcapNClusters_type;   //!
   TBranch        *b_EcalEndcapNClusters_energy;   //!
   TBranch        *b_EcalEndcapNClusters_energyError;   //!
   TBranch        *b_EcalEndcapNClusters_time;   //!
   TBranch        *b_EcalEndcapNClusters_timeError;   //!
   TBranch        *b_EcalEndcapNClusters_nhits;   //!
   TBranch        *b_EcalEndcapNClusters_position_x;   //!
   TBranch        *b_EcalEndcapNClusters_position_y;   //!
   TBranch        *b_EcalEndcapNClusters_position_z;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_xx;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_yy;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_zz;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_xy;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_xz;   //!
   TBranch        *b_EcalEndcapNClusters_positionError_yz;   //!

   TBranch        *b_EcalEndcapNRecHits_;   //!
   TBranch        *b_EcalEndcapNRecHits_cellID;   //!
   TBranch        *b_EcalEndcapNRecHits_energy;   //!
   TBranch        *b_EcalEndcapNRecHits_energyError;   //!
   TBranch        *b_EcalEndcapNRecHits_time;   //!
   TBranch        *b_EcalEndcapNRecHits_timeError;   //!
   TBranch        *b_EcalEndcapNRecHits_position_x;   //!
   TBranch        *b_EcalEndcapNRecHits_position_y;   //!
   TBranch        *b_EcalEndcapNRecHits_position_z;   //!

   TBranch        *b_EcalEndcapPClusters_;   //!
   TBranch        *b_EcalEndcapPClusters_type;   //!
   TBranch        *b_EcalEndcapPClusters_energy;   //!
   TBranch        *b_EcalEndcapPClusters_energyError;   //!
   TBranch        *b_EcalEndcapPClusters_time;   //!
   TBranch        *b_EcalEndcapPClusters_timeError;   //!
   TBranch        *b_EcalEndcapPClusters_nhits;   //!
   TBranch        *b_EcalEndcapPClusters_position_x;   //!
   TBranch        *b_EcalEndcapPClusters_position_y;   //!
   TBranch        *b_EcalEndcapPClusters_position_z;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_xx;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_yy;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_zz;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_xy;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_xz;   //!
   TBranch        *b_EcalEndcapPClusters_positionError_yz;   //!

   TBranch        *b_EcalEndcapPRecHits_;   //!
   TBranch        *b_EcalEndcapPRecHits_cellID;   //!
   TBranch        *b_EcalEndcapPRecHits_energy;   //!
   TBranch        *b_EcalEndcapPRecHits_energyError;   //!
   TBranch        *b_EcalEndcapPRecHits_time;   //!
   TBranch        *b_EcalEndcapPRecHits_timeError;   //!
   TBranch        *b_EcalEndcapPRecHits_position_x;   //!
   TBranch        *b_EcalEndcapPRecHits_position_y;   //!
   TBranch        *b_EcalEndcapPRecHits_position_z;   //!

   TBranch        *b_EcalFarForwardZDCClusters_;   //!
   TBranch        *b_EcalFarForwardZDCClusters_type;   //!
   TBranch        *b_EcalFarForwardZDCClusters_energy;   //!
   TBranch        *b_EcalFarForwardZDCClusters_energyError;   //!
   TBranch        *b_EcalFarForwardZDCClusters_time;   //!
   TBranch        *b_EcalFarForwardZDCClusters_timeError;   //!
   TBranch        *b_EcalFarForwardZDCClusters_nhits;   //!
   TBranch        *b_EcalFarForwardZDCClusters_position_x;   //!
   TBranch        *b_EcalFarForwardZDCClusters_position_y;   //!
   TBranch        *b_EcalFarForwardZDCClusters_position_z;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_xx;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_yy;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_zz;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_xy;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_xz;   //!
   TBranch        *b_EcalFarForwardZDCClusters_positionError_yz;   //!

   TBranch        *b_EcalFarForwardZDCRecHits_;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_cellID;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_energy;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_energyError;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_time;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_timeError;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_x;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_y;   //!
   TBranch        *b_EcalFarForwardZDCRecHits_position_z;   //!

   TBranch        *b_EcalLumiSpecClusters_;   //!
   TBranch        *b_EcalLumiSpecClusters_type;   //!
   TBranch        *b_EcalLumiSpecClusters_energy;   //!
   TBranch        *b_EcalLumiSpecClusters_energyError;   //!
   TBranch        *b_EcalLumiSpecClusters_time;   //!
   TBranch        *b_EcalLumiSpecClusters_timeError;   //!
   TBranch        *b_EcalLumiSpecClusters_nhits;   //!
   TBranch        *b_EcalLumiSpecClusters_position_x;   //!
   TBranch        *b_EcalLumiSpecClusters_position_y;   //!
   TBranch        *b_EcalLumiSpecClusters_position_z;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_xx;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_yy;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_zz;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_xy;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_xz;   //!
   TBranch        *b_EcalLumiSpecClusters_positionError_yz;   //!

   TBranch        *b_EcalLumiSpecRecHits_;   //!
   TBranch        *b_EcalLumiSpecRecHits_cellID;   //!
   TBranch        *b_EcalLumiSpecRecHits_energy;   //!
   TBranch        *b_EcalLumiSpecRecHits_energyError;   //!
   TBranch        *b_EcalLumiSpecRecHits_time;   //!
   TBranch        *b_EcalLumiSpecRecHits_timeError;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_x;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_y;   //!
   TBranch        *b_EcalLumiSpecRecHits_position_z;   //!

   TBranch        *b_ForwardOffMTrackerRecHits_;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_cellID;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_position_x;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_position_y;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_position_z;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_positionError_xx;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_positionError_yy;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_positionError_zz;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_time;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_timeError;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_edep;   //!
   TBranch        *b_ForwardOffMTrackerRecHits_edepError;   //!

   TBranch        *b_ForwardRomanPotRecHits_;   //!
   TBranch        *b_ForwardRomanPotRecHits_cellID;   //!
   TBranch        *b_ForwardRomanPotRecHits_position_x;   //!
   TBranch        *b_ForwardRomanPotRecHits_position_y;   //!
   TBranch        *b_ForwardRomanPotRecHits_position_z;   //!
   TBranch        *b_ForwardRomanPotRecHits_positionError_xx;   //!
   TBranch        *b_ForwardRomanPotRecHits_positionError_yy;   //!
   TBranch        *b_ForwardRomanPotRecHits_positionError_zz;   //!
   TBranch        *b_ForwardRomanPotRecHits_time;   //!
   TBranch        *b_ForwardRomanPotRecHits_timeError;   //!
   TBranch        *b_ForwardRomanPotRecHits_edep;   //!
   TBranch        *b_ForwardRomanPotRecHits_edepError;   //!

   TBranch        *b_LFHCALClusters_;   //!
   TBranch        *b_LFHCALClusters_type;   //!
   TBranch        *b_LFHCALClusters_energy;   //!
   TBranch        *b_LFHCALClusters_energyError;   //!
   TBranch        *b_LFHCALClusters_time;   //!
   TBranch        *b_LFHCALClusters_timeError;   //!
   TBranch        *b_LFHCALClusters_nhits;   //!
   TBranch        *b_LFHCALClusters_position_x;   //!
   TBranch        *b_LFHCALClusters_position_y;   //!
   TBranch        *b_LFHCALClusters_position_z;   //!
   TBranch        *b_LFHCALClusters_positionError_xx;   //!
   TBranch        *b_LFHCALClusters_positionError_yy;   //!
   TBranch        *b_LFHCALClusters_positionError_zz;   //!
   TBranch        *b_LFHCALClusters_positionError_xy;   //!
   TBranch        *b_LFHCALClusters_positionError_xz;   //!
   TBranch        *b_LFHCALClusters_positionError_yz;   //!

   TBranch        *b_LFHCALRecHits_;   //!
   TBranch        *b_LFHCALRecHits_cellID;   //!
   TBranch        *b_LFHCALRecHits_energy;   //!
   TBranch        *b_LFHCALRecHits_energyError;   //!
   TBranch        *b_LFHCALRecHits_time;   //!
   TBranch        *b_LFHCALRecHits_timeError;   //!
   TBranch        *b_LFHCALRecHits_position_x;   //!
   TBranch        *b_LFHCALRecHits_position_y;   //!
   TBranch        *b_LFHCALRecHits_position_z;   //!



   TBranch        *b_GPIntKeys;   //!
   TBranch        *b_GPIntValues;   //!
   TBranch        *b_GPFloatKeys;   //!
   TBranch        *b_GPFloatValues;   //!
   TBranch        *b_GPDoubleKeys;   //!
   TBranch        *b_GPDoubleValues;   //!
   TBranch        *b_GPStringKeys;   //!
   TBranch        *b_GPStringValues;   //!


#endif
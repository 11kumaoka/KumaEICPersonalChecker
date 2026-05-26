

#ifndef DEFROOTVARIABLES_H
#define DEFROOTVARIABLES_H
   

    static constexpr Int_t kMaxEventHeader = 100000;

   static constexpr Int_t kMaxBackwardMPGDEndcapRecHits = 100000;
   static constexpr Int_t kMaxForwardMPGDEndcapRecHits = 100000;

   static constexpr Int_t kMaxMCParticles = 100000;
   static constexpr Int_t kMax_MCParticles_parents = 100000;
   static constexpr Int_t kMax_MCParticles_daughters = 100000;

   static constexpr Int_t kMaxMPGDBarrelRecHits = 100000;
   static constexpr Int_t kMaxOuterMPGDBarrelRecHits = 100000;
   static constexpr Int_t kMaxSiBarrelTrackerRecHits = 100000;
   static constexpr Int_t kMaxSiBarrelVertexRecHits = 100000;
   static constexpr Int_t kMaxSiEndcapTrackerRecHits = 100000;
   static constexpr Int_t kMaxTOFBarrelRecHits = 100000;
   static constexpr Int_t kMaxTOFEndcapRecHits = 100000;


   static constexpr Int_t kMaxB0ECalClusters = 100000;
   static constexpr Int_t kMax_B0ECalClusters_clusters = 100000;
   static constexpr Int_t kMax_B0ECalClusters_hits = 100000;
   static constexpr Int_t kMax_B0ECalClusters_particleIDs = 100000;
   static constexpr Int_t kMaxB0ECalRecHits = 100000;
   static constexpr Int_t kMax_B0ECalRecHits_rawHit = 100000;

   static constexpr Int_t kMaxB0TrackerRecHits = 100000;

   static constexpr Int_t kMaxDIRCRawHits = 100000;

   static constexpr Int_t kMaxDRICHRawHits = 100000;

   static constexpr Int_t kMaxEcalBarrelClusters = 100000;
   static constexpr Int_t kMax_EcalBarrelClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalBarrelClusters_hits = 100000;

   static constexpr Int_t kMaxEcalBarrelImagingClusters = 100000;
   static constexpr Int_t kMax_EcalBarrelImagingClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalBarrelImagingClusters_hits = 100000;

   static constexpr Int_t kMaxEcalBarrelImagingRecHits = 100000;
   static constexpr Int_t kMax_EcalBarrelImagingRecHits_rawHit = 100000;

   static constexpr Int_t kMaxEcalBarrelScFiClusters = 100000;
   static constexpr Int_t kMax_EcalBarrelScFiClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalBarrelScFiClusters_hits = 100000;
   static constexpr Int_t kMaxEcalBarrelScFiRecHits = 100000;
   static constexpr Int_t kMax_EcalBarrelScFiRecHits_rawHit = 100000;

   static constexpr Int_t kMaxEcalEndcapNClusters = 100000;
   static constexpr Int_t kMax_EcalEndcapNClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalEndcapNClusters_hits = 100000;
   static constexpr Int_t kMaxEcalEndcapNRecHits = 100000;
   static constexpr Int_t kMax_EcalEndcapNRecHits_rawHit = 100000;

   static constexpr Int_t kMaxEcalEndcapPClusters = 100000;
   static constexpr Int_t kMax_EcalEndcapPClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalEndcapPClusters_hits = 100000;
   static constexpr Int_t kMaxEcalEndcapPRecHits = 100000;
   static constexpr Int_t kMax_EcalEndcapPRecHits_rawHit = 100000;

   static constexpr Int_t kMaxEcalFarForwardZDCClusters = 100000;
   static constexpr Int_t kMax_EcalFarForwardZDCClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalFarForwardZDCClusters_hits = 100000;
   static constexpr Int_t kMaxEcalFarForwardZDCRecHits = 100000;
   static constexpr Int_t kMax_EcalFarForwardZDCRecHits_rawHit = 100000;

   static constexpr Int_t kMaxEcalLumiSpecClusters = 100000;
   static constexpr Int_t kMax_EcalLumiSpecClusters_clusters = 100000;
   static constexpr Int_t kMax_EcalLumiSpecClusters_hits = 100000;
   static constexpr Int_t kMaxEcalLumiSpecRecHits = 100000;
   static constexpr Int_t kMax_EcalLumiSpecRecHits_rawHit = 100000;

   static constexpr Int_t kMaxForwardOffMRecParticles = 100000;
   static constexpr Int_t kMax_ForwardOffMRecParticles_clusters = 100000;
   static constexpr Int_t kMaxForwardOffMTrackerRecHits = 100000;
   static constexpr Int_t kMax_ForwardOffMTrackerRecHits_rawHit = 100000;

   static constexpr Int_t kMaxForwardRomanPotRecHits = 100000;
   static constexpr Int_t kMax_ForwardRomanPotRecHits_rawHit = 100000;


   static constexpr Int_t kMaxLFHCALClusters = 100000;
   static constexpr Int_t kMax_LFHCALClusters_clusters = 100000;
   static constexpr Int_t kMax_LFHCALClusters_hits = 100000;
   static constexpr Int_t kMaxLFHCALRecHits = 100000;
   static constexpr Int_t kMax_LFHCALRecHits_rawHit = 100000;


   // Declaration of leaf types
   Int_t           EventHeader_;
   Int_t           EventHeader_eventNumber[kMaxEventHeader];   //[EventHeader_]
   Int_t           EventHeader_runNumber[kMaxEventHeader];   //[EventHeader_]
   ULong_t         EventHeader_timeStamp[kMaxEventHeader];   //[EventHeader_]
   Double_t        EventHeader_weight[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_begin[kMaxEventHeader];   //[EventHeader_]
   UInt_t          EventHeader_weights_end[kMaxEventHeader];   //[EventHeader_]
   
   Int_t           MCParticles_;
   Int_t           MCParticles_PDG[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_generatorStatus[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_simulatorStatus[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_charge[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_time[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_mass[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_vertex_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_vertex_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_vertex_z[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_endpoint_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_endpoint_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_endpoint_z[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentum_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentum_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentum_z[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentumAtEndpoint_x[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentumAtEndpoint_y[kMaxMCParticles];   //[MCParticles_]
   Double_t        MCParticles_momentumAtEndpoint_z[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_spin_x[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_spin_y[kMaxMCParticles];   //[MCParticles_]
   Float_t         MCParticles_spin_z[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_colorFlow_a[kMaxMCParticles];   //[MCParticles_]
   Int_t           MCParticles_colorFlow_b[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_parents_begin[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_parents_end[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_daughters_begin[kMaxMCParticles];   //[MCParticles_]
   UInt_t          MCParticles_daughters_end[kMaxMCParticles];   //[MCParticles_]
   Int_t           _MCParticles_parents_;
   Int_t           _MCParticles_parents_index[kMax_MCParticles_parents];   //[_MCParticles_parents_]
   UInt_t          _MCParticles_parents_collectionID[kMax_MCParticles_parents];   //[_MCParticles_parents_]
   Int_t           _MCParticles_daughters_;
   Int_t           _MCParticles_daughters_index[kMax_MCParticles_daughters];   //[_MCParticles_daughters_]
   UInt_t          _MCParticles_daughters_collectionID[kMax_MCParticles_daughters];   //[_MCParticles_daughters_]

   
   Int_t           BackwardMPGDEndcapRecHits_;
   ULong_t         BackwardMPGDEndcapRecHits_cellID[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_position_x[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_position_y[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_position_z[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_positionError_xx[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_positionError_yy[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_positionError_zz[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_time[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_timeError[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_edep[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]
   Float_t         BackwardMPGDEndcapRecHits_edepError[kMaxBackwardMPGDEndcapRecHits];   //[BackwardMPGDEndcapRecHits_]

   Int_t           ForwardMPGDEndcapRecHits_;
   ULong_t         ForwardMPGDEndcapRecHits_cellID[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_position_x[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_position_y[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_position_z[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_positionError_xx[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_positionError_yy[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_positionError_zz[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_time[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_timeError[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_edep[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   Float_t         ForwardMPGDEndcapRecHits_edepError[kMaxForwardMPGDEndcapRecHits];   //[ForwardMPGDEndcapRecHits_]
   
   
   Int_t           MPGDBarrelRecHits_;
   ULong_t         MPGDBarrelRecHits_cellID[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_position_x[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_position_y[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_position_z[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_positionError_xx[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_positionError_yy[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_positionError_zz[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_time[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_timeError[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_edep[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   Float_t         MPGDBarrelRecHits_edepError[kMaxMPGDBarrelRecHits];   //[MPGDBarrelRecHits_]
   
   Int_t           OuterMPGDBarrelRecHits_;
   ULong_t         OuterMPGDBarrelRecHits_cellID[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_position_x[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_position_y[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_position_z[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_positionError_xx[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_positionError_yy[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_positionError_zz[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_time[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_timeError[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_edep[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]
   Float_t         OuterMPGDBarrelRecHits_edepError[kMaxOuterMPGDBarrelRecHits];   //[OuterMPGDBarrelRecHits_]

   Int_t           SiBarrelTrackerRecHits_;
   ULong_t         SiBarrelTrackerRecHits_cellID[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_position_x[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_position_y[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_position_z[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_positionError_xx[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_positionError_yy[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_positionError_zz[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_time[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_timeError[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_edep[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   Float_t         SiBarrelTrackerRecHits_edepError[kMaxSiBarrelTrackerRecHits];   //[SiBarrelTrackerRecHits_]
   
   Int_t           SiBarrelVertexRecHits_;
   ULong_t         SiBarrelVertexRecHits_cellID[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_position_x[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_position_y[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_position_z[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_positionError_xx[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_positionError_yy[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_positionError_zz[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_time[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_timeError[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_edep[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   Float_t         SiBarrelVertexRecHits_edepError[kMaxSiBarrelVertexRecHits];   //[SiBarrelVertexRecHits_]
   
   Int_t           SiEndcapTrackerRecHits_;
   ULong_t         SiEndcapTrackerRecHits_cellID[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_position_x[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_position_y[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_position_z[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_positionError_xx[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_positionError_yy[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_positionError_zz[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_time[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_timeError[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_edep[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   Float_t         SiEndcapTrackerRecHits_edepError[kMaxSiEndcapTrackerRecHits];   //[SiEndcapTrackerRecHits_]
   
   Int_t           TOFBarrelRecHits_;
   ULong_t         TOFBarrelRecHits_cellID[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_position_x[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_position_y[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_position_z[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_positionError_xx[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_positionError_yy[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_positionError_zz[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_time[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_timeError[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_edep[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   Float_t         TOFBarrelRecHits_edepError[kMaxTOFBarrelRecHits];   //[TOFBarrelRecHits_]
   
   Int_t           TOFEndcapRecHits_;
   ULong_t         TOFEndcapRecHits_cellID[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_position_x[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_position_y[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_position_z[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_positionError_xx[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_positionError_yy[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_positionError_zz[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_time[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_timeError[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_edep[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   Float_t         TOFEndcapRecHits_edepError[kMaxTOFEndcapRecHits];   //[TOFEndcapRecHits_]
   

   Int_t           B0TrackerRecHits_;
   ULong_t         B0TrackerRecHits_cellID[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_position_x[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_position_y[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_position_z[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_positionError_xx[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_positionError_yy[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_positionError_zz[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_time[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_timeError[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_edep[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   Float_t         B0TrackerRecHits_edepError[kMaxB0TrackerRecHits];   //[B0TrackerRecHits_]
   
   Int_t           B0ECalClusters_;
   Int_t           B0ECalClusters_type[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_energy[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_energyError[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_time[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_timeError[kMaxB0ECalClusters];   //[B0ECalClusters_]
   UInt_t          B0ECalClusters_nhits[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_position_x[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_position_y[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_position_z[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_xx[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_yy[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_zz[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_xy[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_xz[kMaxB0ECalClusters];   //[B0ECalClusters_]
   Float_t         B0ECalClusters_positionError_yz[kMaxB0ECalClusters];   //[B0ECalClusters_]

   Int_t           B0ECalRecHits_;
   ULong_t         B0ECalRecHits_cellID[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_energy[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_energyError[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_time[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_timeError[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_x[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_y[kMaxB0ECalRecHits];   //[B0ECalRecHits_]
   Float_t         B0ECalRecHits_position_z[kMaxB0ECalRecHits];   //[B0ECalRecHits_]

   Int_t           DIRCRawHits_;
   ULong_t         DIRCRawHits_cellID[kMaxDIRCRawHits];   //[DIRCRawHits_]
   Int_t           DIRCRawHits_charge[kMaxDIRCRawHits];   //[DIRCRawHits_]
   Int_t           DIRCRawHits_timeStamp[kMaxDIRCRawHits];   //[DIRCRawHits_]

   Int_t           DRICHRawHits_;
   ULong_t         DRICHRawHits_cellID[kMaxDRICHRawHits];   //[DRICHRawHits_]
   Int_t           DRICHRawHits_charge[kMaxDRICHRawHits];   //[DRICHRawHits_]
   Int_t           DRICHRawHits_timeStamp[kMaxDRICHRawHits];   //[DRICHRawHits_]


   Int_t           EcalBarrelClusters_;
   Int_t           EcalBarrelClusters_type[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_energy[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_energyError[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_time[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_timeError[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   UInt_t          EcalBarrelClusters_nhits[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_position_x[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_position_y[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_position_z[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_xx[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_yy[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_zz[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_xy[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_xz[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]
   Float_t         EcalBarrelClusters_positionError_yz[kMaxEcalBarrelClusters];   //[EcalBarrelClusters_]

   Int_t           EcalBarrelImagingClusters_;
   Int_t           EcalBarrelImagingClusters_type[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_energy[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_energyError[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_time[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_timeError[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   UInt_t          EcalBarrelImagingClusters_nhits[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_position_x[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_position_y[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_position_z[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_xx[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_yy[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_zz[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_xy[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_xz[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   Float_t         EcalBarrelImagingClusters_positionError_yz[kMaxEcalBarrelImagingClusters];   //[EcalBarrelImagingClusters_]
   
   Int_t           EcalBarrelImagingRecHits_;
   ULong_t         EcalBarrelImagingRecHits_cellID[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_energy[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_energyError[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_time[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_timeError[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_x[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_y[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]
   Float_t         EcalBarrelImagingRecHits_position_z[kMaxEcalBarrelImagingRecHits];   //[EcalBarrelImagingRecHits_]

   Int_t           EcalBarrelScFiClusters_;
   Int_t           EcalBarrelScFiClusters_type[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_energy[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_energyError[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_time[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_timeError[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   UInt_t          EcalBarrelScFiClusters_nhits[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_position_x[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_position_y[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_position_z[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_xx[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_yy[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_zz[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_xy[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_xz[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]
   Float_t         EcalBarrelScFiClusters_positionError_yz[kMaxEcalBarrelScFiClusters];   //[EcalBarrelScFiClusters_]

   Int_t           EcalBarrelScFiRecHits_;
   ULong_t         EcalBarrelScFiRecHits_cellID[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_energy[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_energyError[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_time[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_timeError[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_x[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_y[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]
   Float_t         EcalBarrelScFiRecHits_position_z[kMaxEcalBarrelScFiRecHits];   //[EcalBarrelScFiRecHits_]


   Int_t           EcalEndcapNClusters_;
   Int_t           EcalEndcapNClusters_type[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_energy[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_energyError[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_time[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_timeError[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   UInt_t          EcalEndcapNClusters_nhits[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_position_x[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_position_y[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_position_z[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_xx[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_yy[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_zz[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_xy[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_xz[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]
   Float_t         EcalEndcapNClusters_positionError_yz[kMaxEcalEndcapNClusters];   //[EcalEndcapNClusters_]

   Int_t           EcalEndcapNRecHits_;
   ULong_t         EcalEndcapNRecHits_cellID[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_energy[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_energyError[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_time[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_timeError[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_x[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_y[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]
   Float_t         EcalEndcapNRecHits_position_z[kMaxEcalEndcapNRecHits];   //[EcalEndcapNRecHits_]

   Int_t           EcalEndcapPClusters_;
   Int_t           EcalEndcapPClusters_type[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_energy[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_energyError[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_time[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_timeError[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   UInt_t          EcalEndcapPClusters_nhits[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_position_x[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_position_y[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_position_z[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_xx[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_yy[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_zz[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_xy[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_xz[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]
   Float_t         EcalEndcapPClusters_positionError_yz[kMaxEcalEndcapPClusters];   //[EcalEndcapPClusters_]

   Int_t           EcalEndcapPRecHits_;
   ULong_t         EcalEndcapPRecHits_cellID[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_energy[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_energyError[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_time[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_timeError[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_x[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_y[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]
   Float_t         EcalEndcapPRecHits_position_z[kMaxEcalEndcapPRecHits];   //[EcalEndcapPRecHits_]


   Int_t           EcalFarForwardZDCClusters_;
   Int_t           EcalFarForwardZDCClusters_type[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_energy[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_energyError[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_time[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_timeError[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   UInt_t          EcalFarForwardZDCClusters_nhits[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_position_x[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_position_y[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_position_z[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_xx[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_yy[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_zz[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_xy[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_xz[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]
   Float_t         EcalFarForwardZDCClusters_positionError_yz[kMaxEcalFarForwardZDCClusters];   //[EcalFarForwardZDCClusters_]

   Int_t           EcalFarForwardZDCRecHits_;
   ULong_t         EcalFarForwardZDCRecHits_cellID[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_energy[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_energyError[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_time[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_timeError[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_x[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_y[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]
   Float_t         EcalFarForwardZDCRecHits_position_z[kMaxEcalFarForwardZDCRecHits];   //[EcalFarForwardZDCRecHits_]

   Int_t           EcalLumiSpecClusters_;
   Int_t           EcalLumiSpecClusters_type[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_energy[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_energyError[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_time[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_timeError[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   UInt_t          EcalLumiSpecClusters_nhits[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_position_x[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_position_y[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_position_z[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_xx[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_yy[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_zz[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_xy[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_xz[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]
   Float_t         EcalLumiSpecClusters_positionError_yz[kMaxEcalLumiSpecClusters];   //[EcalLumiSpecClusters_]

   Int_t           EcalLumiSpecRecHits_;
   ULong_t         EcalLumiSpecRecHits_cellID[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_energy[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_energyError[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_time[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_timeError[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_x[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_y[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]
   Float_t         EcalLumiSpecRecHits_position_z[kMaxEcalLumiSpecRecHits];   //[EcalLumiSpecRecHits_]

   Int_t           ForwardOffMTrackerRecHits_;
   ULong_t         ForwardOffMTrackerRecHits_cellID[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_position_x[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_position_y[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_position_z[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_positionError_xx[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_positionError_yy[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_positionError_zz[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_time[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_timeError[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_edep[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]
   Float_t         ForwardOffMTrackerRecHits_edepError[kMaxForwardOffMTrackerRecHits];   //[ForwardOffMTrackerRecHits_]


   Int_t           ForwardRomanPotRecHits_;
   ULong_t         ForwardRomanPotRecHits_cellID[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_position_x[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_position_y[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_position_z[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_positionError_xx[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_positionError_yy[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_positionError_zz[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_time[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_timeError[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_edep[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]
   Float_t         ForwardRomanPotRecHits_edepError[kMaxForwardRomanPotRecHits];   //[ForwardRomanPotRecHits_]

   Int_t           LFHCALClusters_;
   Int_t           LFHCALClusters_type[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_energy[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_energyError[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_time[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_timeError[kMaxLFHCALClusters];   //[LFHCALClusters_]
   UInt_t          LFHCALClusters_nhits[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_position_x[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_position_y[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_position_z[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_xx[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_yy[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_zz[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_xy[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_xz[kMaxLFHCALClusters];   //[LFHCALClusters_]
   Float_t         LFHCALClusters_positionError_yz[kMaxLFHCALClusters];   //[LFHCALClusters_]

   Int_t           LFHCALRecHits_;
   ULong_t         LFHCALRecHits_cellID[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_energy[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_energyError[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_time[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_timeError[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_x[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_y[kMaxLFHCALRecHits];   //[LFHCALRecHits_]
   Float_t         LFHCALRecHits_position_z[kMaxLFHCALRecHits];   //[LFHCALRecHits_]




   std::vector<std::string>  *GPIntKeys;
   std::vector<std::vector<int> > *GPIntValues;
   std::vector<std::string>  *GPFloatKeys;
   std::vector<std::vector<float> > *GPFloatValues;
   std::vector<std::string>  *GPDoubleKeys;
   std::vector<std::vector<double> > *GPDoubleValues;
   std::vector<std::string>  *GPStringKeys;
   std::vector<std::vector<std::string> > *GPStringValues;




#endif

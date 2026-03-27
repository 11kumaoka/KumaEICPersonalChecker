#ifndef SIMTRACKERHITKUMA_H
#define SIMTRACKERHITKUMA_H

#include <vector>
#include <string>

// Forward declaration of SimTrackerHit and dd4hep::SimTrackerHit
class SimTrackerHitKuma {
public:
    // SimTrackerHitKuma();
    SimTrackerHitKuma() {}
    ~SimTrackerHitKuma() = default;


    struct Hit {
        ULong_t cellID;
        Double_t eDep;
        Double_t time;
        Double_t pathLength;
        Int_t quality;
        Double_t posiX;
        Double_t posiY;
        Double_t posiZ;
        Float_t momX;
        Float_t momY;
        Float_t momZ;
    };

    // Load hits from a collection (example: vector of SimTrackerHit pointers)
    void loadHits(size_t hitSize, ULong_t cellID,\
        Float_t eDep, Float_t time, Float_t pathLength, Int_t quality,\
        Double_t posiX, Double_t posiY, Double_t posiZ,\
        Float_t momX, Float_t momY, Float_t momZ){
        m_hitSize = hitSize;
        eDep = 1000 * eDep; // Convert energy deposit from GeV to MeV
        hits.push_back(Hit{cellID, eDep, time, pathLength, quality, posiX, posiY, posiZ, momX, momY, momZ});
    }

    void sortByTime() {
        std::sort(hits.begin(), hits.end(),
                  [](const Hit& a, const Hit& b) {
                      return a.time < b.time;
                  });
    }

    void setHitSize(size_t hitSize) {
        m_hitSize = hitSize;
    }
    void setCellID(size_t index, ULong_t cellID) {
        hits.at(index).cellID = cellID;
    }
    void setEDep(size_t index, Float_t eDep) {
        hits.at(index).eDep = eDep;
    }
    void setTime(size_t index, Float_t time) {
        hits.at(index).time = time;
    }
    void setPathLength(size_t index, Float_t pathLength) {
        hits.at(index).pathLength = pathLength;
    }
    void setQuality(size_t index, Int_t quality) {
        hits.at(index).quality = quality;
    }
    void setPosiX(size_t index, Double_t posiX) {
        hits.at(index).posiX = posiX;
    }
    void setPosiY(size_t index, Double_t posiY) {
        hits.at(index).posiY = posiY;
    }
    void setPosiZ(size_t index, Double_t posiZ) {
        hits.at(index).posiZ = posiZ;
    }
    void setMomX(size_t index, Float_t momX) {
        hits.at(index).momX = momX;
    }
    void setMomY(size_t index, Float_t momY) {
        hits.at(index).momY = momY;
    }
    void setMomZ(size_t index, Float_t momZ) {
        hits.at(index).momZ = momZ;
    }

    // Getters for hit properties
    Int_t getHitSize() const {
        return m_hitSize;
    }
    ULong_t getCellID(size_t index) const {
        return hits.at(index).cellID;
    }
    Float_t getEDep(size_t index) const {
        return hits.at(index).eDep;
    }
    Float_t getTime(size_t index) const {
        return hits.at(index).time;
    }
    Float_t getPathLength(size_t index) const {
        return hits.at(index).pathLength;
    }
    Int_t getQuality(size_t index) const {
        return hits.at(index).quality;
    }
    Double_t getPosiX(size_t index) const {
        return hits.at(index).posiX;
    }
    Double_t getPosiY(size_t index) const {
        return hits.at(index).posiY;
    }
    Double_t getPosiZ(size_t index) const {
        return hits.at(index).posiZ;
    }
    Float_t getMomX(size_t index) const {
        return hits.at(index).momX;
    }
    Float_t getMomY(size_t index) const {
        return hits.at(index).momY;
    }
    Float_t getMomZ(size_t index) const {
        return hits.at(index).momZ;
    }
    size_t getSize() const {
        return hits.size();
    }



private:
    size_t m_hitSize = 0;
    std::vector<Hit> hits;
};

#endif // SIMTRACKERHITKUMA_H







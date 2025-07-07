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

    // Load hits from a collection (example: vector of SimTrackerHit pointers)
    void loadHits(size_t hitSize, ULong_t cellID,\
        Float_t eDep, Float_t time, Float_t pathLength, Int_t quality,\
        Double_t posiX, Double_t posiY, Double_t posiZ,\
        Float_t momX, Float_t momY, Float_t momZ){
            this->m_hitSize = hitSize;
            this->m_cellID.push_back(cellID);
            eDep = 1000 * eDep; // Convert energy deposit from GeV to MeV
            this->m_eDep.push_back(eDep);
            this->m_time.push_back(time);
            this->m_pathLength.push_back(pathLength);
            this->m_quality.push_back(quality);
            this->m_posiX.push_back(posiX);
            this->m_posiY.push_back(posiY);
            this->m_posiZ.push_back(posiZ);
            this->m_momX.push_back(momX);
            this->m_momY.push_back(momY);
            this->m_momZ.push_back(momZ);
    }

    // Getters for hit properties
    Int_t getHitSize() const {
        return m_hitSize;
    }
    ULong_t getCellID(size_t index) const {
        return m_cellID.at(index);
    }
    Float_t getEDep(size_t index) const {
        return m_eDep.at(index);
    }
    Float_t getTime(size_t index) const {
        return m_time.at(index);
    }
    Float_t getPathLength(size_t index) const {
        return m_pathLength.at(index);
    }
    Int_t getQuality(size_t index) const {
        return m_quality.at(index);
    }
    Double_t getPosiX(size_t index) const {
        return m_posiX.at(index);
    }
    Double_t getPosiY(size_t index) const {
        return m_posiY.at(index);
    }
    Double_t getPosiZ(size_t index) const {
        return m_posiZ.at(index);
    }
    Float_t getMomX(size_t index) const {
        return m_momX.at(index);
    }
    Float_t getMomY(size_t index) const {
        return m_momY.at(index);
    }
    Float_t getMomZ(size_t index) const {
        return m_momZ.at(index);
    }
    size_t getSize() const {
        return m_cellID.size();
    }    



private:
    size_t m_hitSize = 0;
    std::vector<Int_t> m_cellID;
    std::vector<Double_t> m_eDep;
    std::vector<Double_t> m_time;
    std::vector<Double_t> m_pathLength;
    std::vector<Double_t> m_quality;
    std::vector<Double_t> m_posiX;
    std::vector<Double_t> m_posiY;
    std::vector<Double_t> m_posiZ;
    std::vector<Double_t> m_momX;
    std::vector<Double_t> m_momY;
    std::vector<Double_t> m_momZ;
};

#endif // SIMTRACKERHITKUMA_H







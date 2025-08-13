#ifndef CHEMOTHERAPY_REGIMEN_H
#define CHEMOTHERAPY_REGIMEN_H

#include "ClinicalConcepts.h"
#include "Patient.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

// Abstract base class for all chemotherapy regimens
class ChemotherapyRegimen {
protected:
    std::map<std::string, double> currentDosages; // Patient-specific dose in mg
    std::map<std::string, int> doseLevels;      // Dose level, e.g., 0, -1, -2

    // Calculates the initial dose based on BSA and other factors
    virtual void calculateInitialDosages(const Patient& patient) = 0;

public:
    ChemotherapyRegimen() = default;
    virtual ~ChemotherapyRegimen() = default;

    // Core Info
    virtual std::string getName() const = 0;
    virtual int getCycles() const = 0;
    
    // Dynamic Dose Management
    virtual void adjustDoses(const ClinicalFeedback& feedback, const Patient& patient) = 0;
    
    // Utility Methods
    bool isDrugActive(const std::string& drugName) const;
    double getDosage(const std::string& drugName) const;
    void printDosages() const;
    const std::map<std::string, double>& getAllDosages() const { return currentDosages; }
};

// Derived Regimen Classes
class ABVD final : public ChemotherapyRegimen {
private:
    void calculateInitialDosages(const Patient& patient) override;
public:
    ABVD(const Patient& patient);
    std::string getName() const override { return "ABVD"; }
    int getCycles() const override { return 6; }
    void adjustDoses(const ClinicalFeedback& feedback, const Patient& patient) override;
    void deEscalate() { currentDosages["Bleomycin"] = 0; }
};

class BEACOPP final : public ChemotherapyRegimen {
private:
    void calculateInitialDosages(const Patient& patient) override;
public:
    BEACOPP(const Patient& patient);
    std::string getName() const override { return "BEACOPP"; }
    int getCycles() const override { return 6; } // Simplified to 6
    void adjustDoses(const ClinicalFeedback& feedback, const Patient& patient) override;
};

#endif // CHEMOTHERAPY_REGIMEN_H
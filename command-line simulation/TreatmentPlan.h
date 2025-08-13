#ifndef TREATMENT_PLAN_H
#define TREATMENT_PLAN_H

#include "Patient.h"
#include "ChemotherapyRegimen.h"
#include <string>
#include <memory>

class TreatmentPlan {
private:
    Patient patient;
    std::unique_ptr<ChemotherapyRegimen> regimen;
    int currentCycle;
    bool cycleDelayed;
    std::string treatmentSummary;

    void escalateTreatment();

public:
    TreatmentPlan(const Patient& p);
    
    void chooseInitialRegimen();
    void runCycle();
    void assessFeedbackAndAdjust(const ClinicalFeedback& feedback);
    
    // Getters
    int getCurrentCycle() const { return currentCycle; }
    int getTotalCycles() const { return regimen ? regimen->getCycles() : 0; }
    bool isDelayed() const { return cycleDelayed; }
    const Patient& getPatient() const { return patient; }
    ChemotherapyRegimen* getRegimen() const { return regimen.get(); }
    const std::string& getSummary() const { return treatmentSummary; }
};

#endif // TREATMENT_PLAN_H
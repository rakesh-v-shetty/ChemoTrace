#include "TreatmentPlan.h"
#include "Constants.h"
#include <iostream>

TreatmentPlan::TreatmentPlan(const Patient& p) 
    : patient(p), currentCycle(0), cycleDelayed(false) {}

void TreatmentPlan::chooseInitialRegimen() {
    if (patient.isFavorableEarlyStage()) {
        treatmentSummary = "Patient is Early-Stage Favorable. Starting ABVD.\n";
        regimen = std::make_unique<ABVD>(patient);
    } else {
        int ips = patient.calculateIPS();
        if (ips >= IPS_HIGH_SCORE_THRESHOLD) {
            treatmentSummary = "Patient has a high IPS score ("+ std::to_string(ips) +"). Starting BEACOPP.\n";
            regimen = std::make_unique<BEACOPP>(patient);
        } else {
            treatmentSummary = "Patient is Unfavorable/Advanced-Stage with IPS < 4. Starting ABVD.\n";
            regimen = std::make_unique<ABVD>(patient);
        }
    }
    std::cout << treatmentSummary;
}

void TreatmentPlan::runCycle() {
    if (!regimen) return;
    currentCycle++;
    std::cout << "\n--- Starting Cycle " << currentCycle << " of " << regimen->getCycles() 
              << " (" << regimen->getName() << ") ---" << std::endl;

    // A single administration per cycle for this simulation
    if (regimen->isDrugActive("Doxorubicin")) {
        patient.cumulativeDoxorubicinDose += regimen->getDosage("Doxorubicin");
    }
    regimen->printDosages();
}

void TreatmentPlan::assessFeedbackAndAdjust(const ClinicalFeedback& feedback) {
    std::cout << "\n--- Analyzing Clinical Feedback ---" << std::endl;
    cycleDelayed = false;

    // 1. Check for cycle-delaying toxicities
    if (feedback.neutropeniaGrade >= (ToxicityGrade)NEUTROPENIA_GRADE_DELAY || feedback.thrombocytopeniaGrade >= (ToxicityGrade)THROMBOCYTOPENIA_GRADE_DELAY) {
        cycleDelayed = true;
        std::string reason = (feedback.neutropeniaGrade >= (ToxicityGrade)NEUTROPENIA_GRADE_DELAY) ? "Neutropenia" : "Thrombocytopenia";
        std::cout << "🚨 **Severe Myelosuppression (" << reason << "):** Next cycle will be delayed." << std::endl;
        treatmentSummary += "Cycle " + std::to_string(currentCycle+1) + " delayed due to " + reason + ".\n";
    }

    // 2. Adjust doses based on feedback
    regimen->adjustDoses(feedback, patient);

    // 3. Handle interim PET scan after 2 cycles
    if (currentCycle == 2 && feedback.petCTDeauvilleScore > 0) {
        std::cout << "🔎 **Interim PET-CT Scan Results:** Deauville score of " << feedback.petCTDeauvilleScore << "." << std::endl;
        if (regimen->getName() == "ABVD" && feedback.petCTDeauvilleScore <= DEAUVILLE_EXCELLENT_RESPONSE_MAX) {
            std::cout << "✅ **Excellent Response:** De-escalating treatment. Bleomycin will be discontinued." << std::endl;
            treatmentSummary += "Excellent PET response on cycle 2. Bleomycin discontinued.\n";
            if (auto abvd = dynamic_cast<ABVD*>(regimen.get())) {
                abvd->deEscalate();
            }
        } else if (regimen->getName() == "ABVD" && feedback.petCTDeauvilleScore >= DEAUVILLE_INADEQUATE_RESPONSE_MIN) {
            std::cout << "❗ **Inadequate Response:** Escalating treatment to a more intensive regimen." << std::endl;
            treatmentSummary += "Inadequate PET response on cycle 2. Escalating to BEACOPP.\n";
            escalateTreatment();
        }
    }
}

void TreatmentPlan::escalateTreatment() {
    currentCycle = 0; // Reset cycle count for the new regimen
    regimen = std::make_unique<BEACOPP>(patient);
    std::cout << "\n*** TREATMENT HAS BEEN ESCALATED TO " << regimen->getName() << " ***" << std::endl;
}
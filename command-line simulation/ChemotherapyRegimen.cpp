#include "ChemotherapyRegimen.h"
#include "Constants.h"
#include <iomanip>
#include <iostream>

// --- Base Class Implementation ---
bool ChemotherapyRegimen::isDrugActive(const std::string& drugName) const {
    return currentDosages.count(drugName) && currentDosages.at(drugName) > 0.0;
}
double ChemotherapyRegimen::getDosage(const std::string& drugName) const {
    return isDrugActive(drugName) ? currentDosages.at(drugName) : 0.0;
}
void ChemotherapyRegimen::printDosages() const {
    std::cout << "Current dosages (per administration):" << std::endl;
    for (const auto& pair : currentDosages) {
        if (pair.second > 0) {
            std::cout << " - " << std::left << std::setw(20) << pair.first 
                      << ": " << std::fixed << std::setprecision(2) << pair.second << " mg" << std::endl;
        } else {
            std::cout << " - " << std::left << std::setw(20) << pair.first 
                      << ": Discontinued" << std::endl;
        }
    }
}

// --- ABVD Implementation ---
ABVD::ABVD(const Patient& patient) {
    calculateInitialDosages(patient);
}

void ABVD::calculateInitialDosages(const Patient& patient) {
    double bsa = patient.metrics.bsa;
    doseLevels = {{"Doxorubicin", 0}, {"Bleomycin", 0}, {"Vinblastine", 0}, {"Dacarbazine", 0}};
    
    currentDosages["Doxorubicin"] = 25 * bsa;
    currentDosages["Bleomycin"]   = 10 * bsa;
    currentDosages["Vinblastine"] = 6 * bsa;
    currentDosages["Dacarbazine"] = 375 * bsa;

    // Renal dose adjustment for Bleomycin
    if (patient.creatinineClearance < MIN_CREATININE_CLEARANCE_FULL_DOSE) {
        std::cout << "⚠️ Kidney function below threshold. Reducing Bleomycin dose." << std::endl;
        currentDosages["Bleomycin"] *= 0.75; // 25% reduction
    }
}

void ABVD::adjustDoses(const ClinicalFeedback& feedback, const Patient& patient) {
    // Neuropathy check for Vinblastine
    if (feedback.neuropathyGrade >= (ToxicityGrade)NEUROPATHY_GRADE_DOSE_REDUCE && doseLevels["Vinblastine"] > -2) {
        doseLevels["Vinblastine"]--; // Reduce dose level
        double bsa = patient.metrics.bsa;
        double reductionFactor = 1.0 + (doseLevels["Vinblastine"] * 0.25); // -1 -> 0.75, -2 -> 0.5
        currentDosages["Vinblastine"] = (6 * bsa) * reductionFactor;
        std::cout << "⚠️ Grade " << static_cast<int>(feedback.neuropathyGrade) << " neuropathy detected. Vinblastine dose reduced." << std::endl;
    }
}

// --- BEACOPP Implementation ---
BEACOPP::BEACOPP(const Patient& patient) {
    calculateInitialDosages(patient);
}

void BEACOPP::calculateInitialDosages(const Patient& patient) {
    double bsa = patient.metrics.bsa;
    doseLevels = {{"Etoposide", 0}, {"Doxorubicin", 0}, {"Cyclophosphamide", 0}, {"Vincristine", 0}};
    
    currentDosages["Etoposide"] = 200 * bsa;
    currentDosages["Doxorubicin"] = 35 * bsa;
    currentDosages["Cyclophosphamide"] = 1250 * bsa;
    currentDosages["Vincristine"] = 1.4 * bsa;
    if(currentDosages["Vincristine"] > VINCRISTINE_DOSE_CAP_MG) {
        currentDosages["Vincristine"] = VINCRISTINE_DOSE_CAP_MG; // Apply dose cap
    }
}

void BEACOPP::adjustDoses(const ClinicalFeedback& feedback, const Patient& patient) {
    if (feedback.neutropeniaGrade >= (ToxicityGrade)NEUTROPENIA_GRADE_DELAY && doseLevels["Etoposide"] > -2) {
        doseLevels["Etoposide"]--;
        doseLevels["Doxorubicin"]--;
        doseLevels["Cyclophosphamide"]--;
        std::cout << "⚠️ Severe myelosuppression. Reducing doses of Etoposide, Doxorubicin, and Cyclophosphamide." << std::endl;
        
        double bsa = patient.metrics.bsa;
        double reductionFactor = 1.0 + (doseLevels["Etoposide"] * 0.20); // 20% reduction per level
        currentDosages["Etoposide"] = (200 * bsa) * reductionFactor;
        currentDosages["Doxorubicin"] = (35 * bsa) * reductionFactor;
        currentDosages["Cyclophosphamide"] = (1250 * bsa) * reductionFactor;
    }
}
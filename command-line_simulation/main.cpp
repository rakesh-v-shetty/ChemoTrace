#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
#include <limits>

#include "Patient.h"
#include "TreatmentPlan.h"
#include "ChemotherapyRegimen.h"
#include "Constants.h"

// Helper function to get graded input
void getGradedInput(const std::string& prompt, ToxicityGrade& grade) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good() && value >= 0 && value <= 4) {
            grade = static_cast<ToxicityGrade>(value);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Invalid input. Please enter a grade from 0 to 4." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Function to gather clinical feedback from the user
void getClinicalFeedbackFromUser(ClinicalFeedback& feedback, int currentCycle, const std::string& regimenName) {
    std::cout << "\n--- Enter Graded Clinical Feedback for Cycle " << currentCycle << " ---" << std::endl;
    getGradedInput("Enter Neutropenia grade (0-4): ", feedback.neutropeniaGrade);
    getGradedInput("Enter Thrombocytopenia (low platelet) grade (0-4): ", feedback.thrombocytopeniaGrade);
    getGradedInput("Enter Peripheral Neuropathy grade (0-4): ", feedback.neuropathyGrade);

    // Only ask for Deauville score on cycle 2 of ABVD
    if (currentCycle == 2 && regimenName == "ABVD") {
        int deauville;
        std::cout << "Enter interim PET-CT Deauville score (1-5): ";
        std::cin >> deauville;
        feedback.petCTDeauvilleScore = deauville;
    }
}

int main() {
    Patient patient;
    patient.getPatientData();

    TreatmentPlan plan(patient);
    plan.chooseInitialRegimen();

    while (plan.getCurrentCycle() < plan.getTotalCycles()) {
        plan.runCycle();
        
        ClinicalFeedback feedback;
        getClinicalFeedbackFromUser(feedback, plan.getCurrentCycle(), plan.getRegimen()->getName());

        plan.assessFeedbackAndAdjust(feedback);
        
        if (plan.isDelayed()) {
            std::cout << "\n--- Cycle Delayed ---" << std::endl;
            std::cout << "Simulating a 1-week delay for patient recovery..." << std::endl;
        }

        if (plan.getCurrentCycle() >= plan.getTotalCycles()) break;

        char continueResponse;
        std::cout << "\nContinue to the next cycle? (Y/N): ";
        std::cin >> continueResponse;
        if (continueResponse != 'Y' && continueResponse != 'y') {
            std::cout << "Treatment discontinued by user." << std::endl;
            break;
        }
    }
    
    std::cout << "\n\n--- End of Treatment ---" << std::endl;
    std::cout << "Final Summary:\n" << plan.getSummary() << std::endl;
    std::cout << "Total cycles completed on final regimen: " << plan.getCurrentCycle() << std::endl;
    std::cout << "Final Cumulative Doxorubicin Dose: " << std::fixed << std::setprecision(2) << plan.getPatient().cumulativeDoxorubicinDose << " mg" << std::endl;
    std::cout << "\nFinal Drug Dosages:" << std::endl;
    if (plan.getRegimen()) {
        plan.getRegimen()->printDosages();
    }
    
    return 0;
}
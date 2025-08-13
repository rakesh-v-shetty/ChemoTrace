#include "Patient.h"
#include "Constants.h"
#include <iostream>
#include <limits>
#include <string>

// Helper function for robust numeric input
template<typename T>
void getNumericInput(const std::string& prompt, T& value, T min, T max) {
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good() && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Helper function for boolean (1/0) input
void getBoolInput(const std::string& prompt, bool& value) {
    int intValue;
    getNumericInput(prompt, intValue, 0, 1);
    value = (intValue == 1);
}

Patient::Patient() 
    : age(0), stage(0), hasBSymptoms(false), hasBulkyTumors(false), 
      involvedLymphNodeSites(0), hemoglobin(0.0), creatinineClearance(0.0), 
      baselineNeuropathyGrade(ToxicityGrade::Grade0), cumulativeDoxorubicinDose(0.0) {}

void Patient::getPatientData() {
    std::cout << "--- Entering Patient Data ---" << std::endl;
    getNumericInput("Enter patient age: ", age, 10, 100);
    getNumericInput("Enter height in cm: ", metrics.heightCm, 100.0, 250.0);
    getNumericInput("Enter weight in kg: ", metrics.weightKg, 30.0, 200.0);
    metrics.calculateBSA();
    std::cout << " > Calculated BSA: " << std::fixed << std::setprecision(2) << metrics.bsa << " m^2" << std::endl;

    getNumericInput("Enter Hodgkin's Lymphoma stage (1-4): ", stage, 1, 4);
    getBoolInput("Does the patient have 'B symptoms' (1 for Yes, 0 for No): ", hasBSymptoms);
    getBoolInput("Is there bulky disease (1 for Yes, 0 for No): ", hasBulkyTumors);
    getNumericInput("Number of involved lymph node sites: ", involvedLymphNodeSites, 0, 20);
    
    getNumericInput("Enter patient's hemoglobin level (g/dL): ", hemoglobin, 5.0, 20.0);
    getNumericInput("Enter creatinine clearance (for kidney function, mL/min): ", creatinineClearance, 10.0, 200.0);
    
    int neuroGrade;
    getNumericInput("Enter baseline peripheral neuropathy grade (0-2): ", neuroGrade, 0, 2);
    baselineNeuropathyGrade = static_cast<ToxicityGrade>(neuroGrade);
}

bool Patient::isFavorableEarlyStage() const {
    return (stage <= FAVORABLE_STAGE_MAX && !hasBulkyTumors && !hasBSymptoms && involvedLymphNodeSites <= FAVORABLE_LYMPH_SITES_MAX);
}

int Patient::calculateIPS() const {
    int score = 0;
    if (age >= IPS_AGE_THRESHOLD) score++;
    if (stage == 4) score++;
    if (hemoglobin < LOW_HEMOGLOBIN_IPS) score++;
    return score;
}
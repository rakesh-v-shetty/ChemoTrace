#ifndef CLINICAL_CONCEPTS_H
#define CLINICAL_CONCEPTS_H

#include "Constants.h"
#include <cmath> // For std::pow, std::sqrt
#include <iostream>
#include <iomanip>

// Represents patient's physical metrics for BSA calculation
struct BodyMetrics {
    double heightCm = 0.0;
    double weightKg = 0.0;
    double bsa = 0.0; // Body Surface Area in m^2

    // Calculates BSA using the Du Bois formula
    void calculateBSA() {
        if (heightCm > 0 && weightKg > 0) {
            bsa = 0.007184 * std::pow(heightCm, 0.725) * std::pow(weightKg, 0.425);
            if (bsa > BSA_CAP) {
                bsa = BSA_CAP; // Cap BSA to avoid overdosing
            }
        } else {
            bsa = 0;
        }
    }
};

// Graded toxicity based on CTCAE (Common Terminology Criteria for Adverse Events)
enum class ToxicityGrade {
    Grade0 = 0, // None
    Grade1 = 1, // Mild
    Grade2 = 2, // Moderate
    Grade3 = 3, // Severe
    Grade4 = 4, // Life-threatening
};

// Struct to hold graded clinical feedback
struct ClinicalFeedback {
    ToxicityGrade neutropeniaGrade = ToxicityGrade::Grade0;
    ToxicityGrade thrombocytopeniaGrade = ToxicityGrade::Grade0; // Low platelets
    ToxicityGrade neuropathyGrade = ToxicityGrade::Grade0;
    
    int petCTDeauvilleScore = 0;
};

#endif // CLINICAL_CONCEPTS_H
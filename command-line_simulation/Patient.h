#ifndef PATIENT_H
#define PATIENT_H

#include "ClinicalConcepts.h"
#include <string>

class Patient {
public:
    // Core Demographics & Staging
    int age;
    int stage;
    bool hasBSymptoms;
    bool hasBulkyTumors;
    int involvedLymphNodeSites;
    double hemoglobin;
    
    // Body Metrics
    BodyMetrics metrics;

    // Comorbidities & Baseline Health
    double creatinineClearance; // For kidney function
    ToxicityGrade baselineNeuropathyGrade;

    // Treatment Tracking
    double cumulativeDoxorubicinDose;

    Patient();

    void getPatientData();
    bool isFavorableEarlyStage() const;
    int calculateIPS() const;
};

#endif // PATIENT_H
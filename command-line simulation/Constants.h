#ifndef CONSTANTS_H
#define CONSTANTS_H

// --- Patient & Clinical Thresholds ---
constexpr double LOW_HEMOGLOBIN_IPS = 10.5;
constexpr int IPS_AGE_THRESHOLD = 45;
constexpr int IPS_HIGH_SCORE_THRESHOLD = 4;
constexpr int FAVORABLE_STAGE_MAX = 2;
constexpr int FAVORABLE_LYMPH_SITES_MAX = 3;
constexpr double MIN_CREATININE_CLEARANCE_FULL_DOSE = 50.0; // in mL/min

// --- PET-CT Deauville Scores ---
constexpr int DEAUVILLE_EXCELLENT_RESPONSE_MAX = 2;
constexpr int DEAUVILLE_INADEQUATE_RESPONSE_MIN = 4;

// --- Toxicity Grade Thresholds for Action ---
constexpr int NEUTROPENIA_GRADE_DELAY = 3;
constexpr int THROMBOCYTOPENIA_GRADE_DELAY = 3;
constexpr int NEUROPATHY_GRADE_DOSE_REDUCE = 2;

// --- Dosing & Reduction Constants ---
// Body Surface Area (BSA) Capping
constexpr double BSA_CAP = 2.0; // Cap BSA at 2.0 m^2 for dose calculation
// Vinca Alkaloid Dose Capping
constexpr double VINCRISTINE_DOSE_CAP_MG = 2.0; // Max single dose for Vincristine

#endif // CONSTANTS_H
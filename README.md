# ChemoTrace: A Hodgkin's Lymphoma Chemotherapy Simulation Tool

A dynamic, command-line simulation tool that models the complex decision-making process in treating Hodgkin's Lymphoma with chemotherapy.

-----

## 📖 Overview

ChemoTrace is an educational C++ application designed to illustrate the real-world workflow of modern oncology. It allows users to simulate a patient's entire treatment journey, from initial diagnosis and risk stratification to dynamic adjustments based on treatment response and toxicities. The project showcases how clinical data directly influences chemotherapy dosing, regimen changes, and patient management.

-----

## ✨ Key Features

  * **Risk-Adapted Therapy**: The simulation automatically selects an appropriate initial chemotherapy regimen (`ABVD` or `BEACOPP`) based on the patient's specific disease stage and risk factors.
  * **BSA-Based Dosing**: Adhering to clinical standards, all chemotherapy doses are calculated based on the patient's Body Surface Area (BSA).
  * **Graded Toxicity System**: Users provide clinical feedback using a 0-4 graded scale for toxicities like neutropenia and neuropathy, mirroring the CTCAE standard used by oncologists.
  * **Dynamic Dose Adjustments**: The simulation intelligently reduces drug dosages in response to specific toxicities, such as lowering the Vinblastine dose for peripheral neuropathy.
  * **Response-Based Escalation**: Demonstrates a critical treatment pathway where an inadequate response on an interim PET-CT scan triggers an automatic escalation from the `ABVD` regimen to the more intensive `BEACOPP` regimen.
  * **Cycle Delays & Safety Caps**: The model incorporates safety protocols like delaying treatment cycles for severe myelosuppression and applying dose caps for high-risk drugs.

-----

## 🚀 Live Demo Walkthrough

Here is an example of the simulation in action, demonstrating the treatment escalation feature.

```bash
--- Entering Patient Data ---
Enter patient age: 35
Enter height in cm: 175
Enter weight in kg: 70
 > Calculated BSA: 1.84 m^2
Enter Hodgkin's Lymphoma stage (1-4): 2
Does the patient have 'B symptoms' (1 for Yes, 0 for No): 0
...

--- Starting Cycle 2 of 6 (ABVD) ---
...
--- Enter Graded Clinical Feedback for Cycle 2 ---
Enter Neutropenia grade (0-4): 2
Enter Thrombocytopenia (low platelet) grade (0-4): 1
Enter Peripheral Neuropathy grade (0-4): 2
Enter interim PET-CT Deauville score (1-5): 5

--- Analyzing Clinical Feedback ---
⚠️ Grade 2 neuropathy detected. Vinblastine dose reduced.
🔎 **Interim PET-CT Scan Results:** Deauville score of 5.
❗ **Inadequate Response:** Escalating treatment to a more intensive regimen.
Inadequate PET response on cycle 2. Escalating to BEACOPP.

*** TREATMENT HAS BEEN ESCALATED TO BEACOPP ***

--- Starting Cycle 1 of 6 (BEACOPP) ---
Current dosages (per administration):
 - Cyclophosphamide    : 2300.00 mg
 - Doxorubicin         : 64.40 mg
 - Etoposide           : 368.00 mg
 - Vincristine         : 2.00 mg
...
```

-----

## 🛠️ Technology Stack

  * **Language**: C++ (Standard: C++17)
  * **Compiler**: g++ / Clang / MSVC

-----

## 📂 Project File Structure

The project is organized with a clear separation of interface and implementation.

```
ChemoTrace/
├── main.cpp
├── Constants.h
├── ClinicalConcepts.h
├── Patient.h
├── Patient.cpp
├── ChemotherapyRegimen.h
├── ChemotherapyRegimen.cpp
├── TreatmentPlan.h
├── TreatmentPlan.cpp
└── .gitignore
```

-----

## ⚙️ Getting Started

Follow these instructions to compile and run the project on your local machine.

### Prerequisites

You will need a C++ compiler that supports the C++17 standard.

  * **Linux**: `sudo apt-get install build-essential g++`
  * **macOS**: `xcode-select --install`
  * **Windows**: Install MinGW-w64 (via MSYS2) or Visual Studio.

### Compilation

1.  Clone or download the repository and navigate to the project root directory.

2.  Run the following command in your terminal:

    ```bash
    g++ main.cpp Patient.cpp ChemotherapyRegimen.cpp TreatmentPlan.cpp -o chemotrace -std=c++17
    ```

    This command compiles all the source files and creates a single executable named `chemotrace`.

### Execution

1.  Run the compiled program from your terminal:

      * On Linux / macOS: `./chemotrace`
      * On Windows: `chemotrace.exe`

2.  The simulation will start, prompting you to enter patient data and subsequent clinical feedback for each cycle.

-----

## 🤝 Contributing

Contributions, issues, and feature requests are welcome\! Feel free to check the issues page or open a new one.
#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Create output ROOT file
    TFile *output = new TFile("mass_hist.root", "recreate");

    // Histogram for mass (GeV/c^2)
    TH1F *hist_mass = new TH1F("hist_mass", "Mass Distribution", 100, 0, 2);

    // Number of events
    int nevents = 50000;

    // Initialize Pythia
    Pythia8::Pythia pythia;
    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 13600.");
    pythia.readString("HardQCD:all = on");
    pythia.readString("PhaseSpace:pTHatMin = 100.");
    pythia.settings.readString("Tune:pp=18");

    pythia.init();

    // Event loop
    for (int i = 0; i < nevents; i++) {
        if (!pythia.next()) continue;

        // Loop over final charged particles
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                double mass = pythia.event[j].m();  // Rest mass
                hist_mass->Fill(mass);
            }
        }
    }

    // Write histogram to file
    output->Write();
    output->Close();

    cout << "Histogram of particle masses saved to mass_hist.root" << endl;

    return 0;
}


#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Output ROOT file
    TFile *output = new TFile("phi_hist.root", "recreate");

    // Histogram for phi (azimuthal angle in radians)
    TH1F *hist_phi = new TH1F("hist_phi", "phi Distribution", 100, -5, 5);

    // Number of events
    int nevents = 50000;

    // Initialize Pythia
    Pythia8::Pythia pythia;
    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 8000.");
    pythia.readString("HardQCD:all = on");
    pythia.readString("PhaseSpace:pTHatMin = 100.");
    pythia.settings.readString("Tune:pp=18");

    pythia.init();

    // Event loop
    for (int i = 0; i < nevents; i++) {
        if (!pythia.next()) continue;

        // Loop over final-state charged particles
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                double phi = pythia.event[j].phi();  // azimuthal angle
                hist_phi->Fill(phi);
            }
        }
    }

    // Save and close ROOT file
    output->Write();
    output->Close();

    cout << "Histogram of azimuthal angle (phi) saved to phi_hist.root" << endl;

    return 0;
}


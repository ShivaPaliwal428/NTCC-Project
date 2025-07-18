#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Create output ROOT file
    TFile *output = new TFile("eta_hist.root", "recreate");

    // Create histogram for eta
    TH1F *hist_eta = new TH1F("hist_eta", "eta Distribution", 100, -15.0, 15.0);

    // Number of events to simulate
    int nevents = 50000;

    // Set up Pythia
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

        // Loop over final charged particles
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                double eta = pythia.event[j].eta();  // pseudorapidity
                hist_eta->Fill(eta);
            }
        }
    }

    // Save histogram
    output->Write();
    output->Close();

    cout << "Histogram of pseudorapidity (eta) saved to eta_hist.root" << endl;

    return 0;
}


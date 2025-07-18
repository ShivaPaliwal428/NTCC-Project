#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Output ROOT file
    TFile *output = new TFile("py_hist.root", "recreate");

    // Create histogram for total py per event
    TH1F *hist_py = new TH1F("hist_py", "py Distribution", 100, -200, 200);

    // Number of events to simulate
    int nevents = 50000;

    // Set up Pythia
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

        double total_py = 0.0;

        // Loop over final charged particles
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                total_py += pythia.event[j].py();
            }
        }

        // Fill histogram with total py per event
        hist_py->Fill(total_py);
    }

    // Save and close
    output->Write();
    output->Close();

    cout << "Histogram of total py per event saved to py_hist.root" << endl;

    return 0;
}


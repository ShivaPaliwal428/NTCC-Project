#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Output ROOT file
    TFile *output = new TFile("pt_hist.root", "recreate");

    // Histogram for total pT per event
    TH1F *hist_pt = new TH1F("hist_pt", "pT Distribution", 100, 0, 250);

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

        double total_px = 0.0;
        double total_py = 0.0;

        // Loop over final charged particles
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                total_px += pythia.event[j].px();
                total_py += pythia.event[j].py();
            }
        }

        // Calculate total pT for the event
        double total_pt = sqrt(total_px * total_px + total_py * total_py);

        // Fill histogram with total pT per event
        hist_pt->Fill(total_pt);
    }

    // Save histogram
    output->Write();
    output->Close();

    cout << "Histogram of total pT per event saved to pt_hist.root" << endl;

    return 0;
}


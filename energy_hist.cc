#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Output ROOT file
    TFile *output = new TFile("energy_hist.root", "recreate");

    // Histogram for energy (GeV)
    TH1F *hist_energy = new TH1F("hist_energy", "Energy Distribution", 100, 0, 1000);

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
        
        if (i % 1000 == 0) cout << "Processed " << i << " events\r" << flush;


        // Loop over final charged particles
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                double energy = pythia.event[j].e();  // Energy in GeV
                hist_energy->Fill(energy);
            }
        }
    }

    // Save and close file
    output->Write();
    output->Close();

    cout << "Histogram of charged particle energy saved to energy_hist.root" << endl;

    return 0;
}


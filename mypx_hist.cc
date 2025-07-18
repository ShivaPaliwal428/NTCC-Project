#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    // Create output ROOT file
    TFile *output = new TFile("px_hist.root", "recreate");

    // Create histogram for total px per event
    TH1F *hist_px = new TH1F("hist_px", "Total px per event", 100, -200, 200);

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

    
    for (int i = 0; i < nevents; i++) {
        if (!pythia.next()) continue;

        double total_px = 0.0;

        
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                total_px += pythia.event[j].px();
            }
        }

      
        hist_px->Fill(total_px);
    }

    
    output->Write();
    output->Close();

    cout << "Histogram of total px per event saved to px_hist.root" << endl;

    return 0;
}


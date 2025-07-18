#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;

#include "TH1F.h"
#include "TFile.h"

int main() 
{
    
    TFile *output = new TFile("pz_hist.root", "recreate");

    
    TH1F *hist_pz = new TH1F("hist_pz", "pz Distribution", 100, -1200, 1200);

    
    int nevents = 50000;

    
    Pythia8::Pythia pythia;
    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 7000.");
    pythia.readString("HardQCD:all = on");
    pythia.readString("PhaseSpace:pTHatMin = 100.");
    pythia.settings.readString("Tune:pp=18");

    pythia.init();

    
    for (int i = 0; i < nevents; i++) {
        if (!pythia.next()) continue;

        double total_pz = 0.0;

        
        for (int j = 0; j < pythia.event.size(); j++) {
            if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
                total_pz += pythia.event[j].pz();
            }
        }

        
        hist_pz->Fill(total_pz);
    }

    
    output->Write();
    output->Close();

    cout << "Histogram of total pz per event saved to pz_hist.root" << endl;

    return 0;
}



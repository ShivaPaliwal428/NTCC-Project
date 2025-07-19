###1. myMultiplicity.cc
1. Headers and Setup:->
#include "Pythia8/Pythia.h"
#include <iostream>
#include "TH1F.h"
#include "TFile.h"
using namespace std; 
Explanation_>
Includes PYTHIA8 and ROOT libraries.
TH1F: 1D float histogram.
TFile: ROOT output file.
2. Create ROOT File and Histogram:->
TFile *output = new TFile("tutorial43.root", "recreate");
TH1F *hist_tune18 = new TH1F("hist_tune18", "Charged Multiplicity", 100, 0 , 400);
Explanation->
Creates a ROOT file to save output.
Defines a histogram hist_tune18 with 100 bins in the range [0, 400].
3. Set up Pythia Simulation->
Pythia8::Pythia pythia;
pythia.readString("Beams:idA = 2212");          // Proton beam A
pythia.readString("Beams:idB = 2212");          // Proton beam B
pythia.readString("Beams:eCM = 13600.");        // Energy = 13.6 TeV
pythia.readString("HardQCD:all = on");          // Simulate hard QCD processes
pythia.readString("PhaseSpace:pTHatMin = 100."); // Only consider high-pT collisions
pythia.settings.readString("Tune:pp=18");       // Use Tune 18 for settings
pythia.init();                                  // Initialize PYTHIA
4. Event Loop and Counting Charged Particles:
int nevents = 50000;
int ncharged = 0;

for(int i = 0; i < nevents; i++) {
    if (!pythia.next()) continue;

    int nch = 0; // number of charged particles in this event

    for(int j = 0; j < pythia.event.size(); j++) {
        if (pythia.event[j].isFinal() && pythia.event[j].isCharged()) {
            nch++;       // count per event
            ncharged++;  // total over all events
        }
    }

    hist_tune18->Fill(nch);
Explanation:
Loops over 50,000 events.
For each event, counts all final-state charged particles.
Fills the number nch into the histogram (one entry per event).
5.5. Print and Save Output:
cout << "Number of Charged particles:" << ncharged <<endl;

output->Write();  // save histogram to file
output->Close();  // close the ROOT file
explanation:
Prints total number of charged particles.

Saves the histogram to tutorial43.root.
 ### now in all the files the variables and the center of mass energy will be changed accordingly
 ##multiplicity.c
 Step-by-Step Explanation
1. Open File and Get Histogram
   TFile *f = TFile::Open("pz_hist.root");
   TH1F *h = (TH1F*)f->Get("hist_pz");
Opens the ROOT file that contains the histogram.
Retrieves the histogram named "hist_pz" and casts it to TH1F*.
2. Create a Canvas
   TCanvas *c1 = new TCanvas("c1", "Distribution", 800, 600);
3. Customize Y-Axis Appearance
   h->GetYaxis()->SetMoreLogLabels();
h->GetYaxis()->SetNoExponent(kFALSE);
h->GetYaxis()->SetLabelSize(0.035);
    SetMoreLogLabels(): Helps display more labels in logarithmic plots (even if unused here).

    SetNoExponent(kFALSE): Allows use of scientific notation on the axis.

    SetLabelSize(0.035): Adjusts label size for better visibility.

    🔸 These options are for styling and clarity.
4. Customize Histogram Line
   h->SetLineColor(kRed);
h->SetLineWidth(2);
5. Axis Titles
   h->GetXaxis()->SetTitle("(pz)");
h->GetYaxis()->SetTitle("Normalized Events");
7. Add Tick Marks on All Sides
   c1->SetTickx(1);
c1->SetTicky(1);
8. Add Text Annotations
   TLatex latex;
latex.SetNDC();  // Use normalized device coordinates (0–1)
latex.SetTextSize(0.035);
latex.SetTextColor(kBlack);

// Add simple text
latex.DrawLatex(0.12, 0.92, "Pythia8 Simulation");

// Add mathematical text
latex.DrawLatex(0.63, 0.92, "#sqrt{s} = 7 TeV");
9. Update and Save the Canvas
c1->Update();
c1->SaveAs("pzdistribution_ch1.png");

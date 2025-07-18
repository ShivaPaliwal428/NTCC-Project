#include "Pythia8/Pythia.h"
#include <iostream>
using namespace std;



#include "TH1F.h"
#include "TFile.h"

int main() 
{
    TFile *output = new TFile("tutorial43.root", "recreate");
    
    int nch;
    
    TH1F *hist_tune18 = new TH1F("hist_tune18", "Charged Multiplicity", 100, 0 , 400);
    
    int nevents = 50000;
    
    Pythia8::Pythia pythia;
    
    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 13600.");
    pythia.readString("HardQCD:all = on");
    pythia.readString("PhaseSpace:pTHatMin = 100.");
    pythia.settings.readString("Tune:pp=18");
    
    
    pythia.init();

   int ncharged = 0;
   
   for(int i = 0; i < nevents; i++)
   {
             if (!pythia.next()) continue;
             
             int entries = pythia.event.size();
             nch = 0;
             
             for(int j = 0; j < entries; j++)
             {
                     if(pythia.event[j].isFinal() && pythia.event[j].isCharged()){
                             nch++;
                             hist_tune18->Fill(nch);
                             ncharged++;
                             }
             }
   }
   
                             cout << "Number of Charged particles:" << ncharged <<endl;
                             
                             output->Write();
                             output->Close();
                             
                             return 0;
}



void multiplicity()


{

TFile *f = TFile::Open("pz_hist.root");
TH1F *h = (TH1F*)f->Get("hist_pz");
TCanvas *c1 = new TCanvas("c1", "Distribution", 800, 600);



 //c1->SetGridy();         // Optional: add horizontal grid lines
 h->GetYaxis()->SetMoreLogLabels();
h->GetYaxis()->SetNoExponent(kFALSE);
//wh->GetYaxis()->SetNdivisions(505, kTRUE);
h->GetYaxis()->SetLabelSize(0.035);
h->SetLineColor(kRed);
 h->SetLineWidth(2);
 h->GetXaxis()->SetTitle("(pz)");
 h->GetYaxis()->SetTitle("Normalized Events");
 h->DrawNormalized("HIST");
 c1->SetTickx(1);
 c1->SetTicky(1);
 
 TLatex latex;
    latex.SetNDC(); // Use normalized device coordinates (0 to 1)
    latex.SetTextSize(0.035);
    latex.SetTextColor(kBlack);
    
    // Example: simple annotation
    latex.DrawLatex(0.12, 0.92, "Pythia8 Simulation");

    // Optional: example with math (comment out if not needed)
    latex.DrawLatex(0.63, 0.92, "#sqrt{s} = 7 TeV");


 c1->Update();
 c1->SaveAs("pzdistribution_ch1.png");

}

void PlotSidebandFD(){
	// Run once you have saved the FD histos from the DrawBinningSB.cc macro
	// It produced the global comparison of the FD event numbers in each bin.
	TFile *fn = new TFile("NOM.root","READ");
	TFile *f1 = new TFile("FD1.root","READ");
	//TFile *f2 = new TFile("FD2.root","READ");
	//TFile *f3 = new TFile("FD3.root","READ");
	TFile *f4 = new TFile("FD4.root","READ");
	TFile *f5 = new TFile("FD5.root","READ");
	TFile *f6 = new TFile("FD6.root","READ");

	TH1D* h_n = (TH1D*)fn.Get("H_all");
	TH1D* h_1 = (TH1D*)f1.Get("H_all");
	//TH1D* h_2 = (TH1D*)f2.Get("H_all");
	//TH1D* h_3 = (TH1D*)f3.Get("H_all");
	TH1D* h_4 = (TH1D*)f4.Get("H_all");
	TH1D* h_5 = (TH1D*)f5.Get("H_all");
	TH1D* h_6 = (TH1D*)f6.Get("H_all");

	TCanvas *c3 = new TCanvas("c3","c3",900,600);
	TPad* pp3=new TPad("pp3","",0.0,0.0,1.0,1.0,0);
	SetStyle(pp3);
	h_n->SetLineColor(kBlack); 	h_n->SetLineStyle(1);
	h_1->SetLineColor(kOrange); h_1->SetLineStyle(1);
	//h_2->SetLineColor(kAzure+5);h_2->SetLineStyle(1);
	//h_3->SetLineColor(kRed+1); 	h_3->SetLineStyle(1);
	h_4->SetLineColor(kSpring+5); h_4->SetLineStyle(1);
	h_5->SetLineColor(kAzure+5); h_5->SetLineStyle(1);
	h_6->SetLineColor(kRed+1); h_6->SetLineStyle(1);

	h_n->GetYaxis()->SetRangeUser(0,300);
	h_1->GetYaxis()->SetRangeUser(0,300);
	//h_2->GetYaxis()->SetRangeUser(0,300);
	//h_3->GetYaxis()->SetRangeUser(0,300);
	h_4->GetYaxis()->SetRangeUser(0,300);
	h_5->GetYaxis()->SetRangeUser(0,300);
	h_6->GetYaxis()->SetRangeUser(0,300);

	h_n->Draw("hist");
	h_1->Draw("hist same");
	//h_2->Draw("hist same");
	//h_3->Draw("hist same");
	h_4->Draw("hist same");
 	h_5->Draw("hist same");
 	h_6->Draw("hist same");

	TLegend *legg = new TLegend(0.6,0.7,0.9,0.9);
	legg->AddEntry(h_n,"NEUT nominal","l");
	legg->AddEntry(h_1,"NEUT FD1","l");
	//legg->AddEntry(h_2,"NEUT FD2","l");
	//legg->AddEntry(h_3,"NEUT FD3","l");
	legg->AddEntry(h_4,"NEUT FD2","l");
	legg->AddEntry(h_5,"NEUT FD3","l"); // previous 2
	legg->AddEntry(h_6,"NEUT FD4","l"); // previous 3

	legg->SetFillColor(kWhite);
	legg->SetMargin(0.25);
	legg->SetBorderSize(0);
	legg->Draw("same");
	TLine *line = new TLine(12,0,12,300);
	line->SetLineStyle(2);
	line->SetLineColor(kGray);
	line->Draw("same");
}

// PLot with style !
void SetStyle(TPad * p){
	gStyle->SetLabelFont(42,"X");
	gStyle->SetLabelSize(0.05,"X");
	gStyle->SetTitleFont(62,"X");
	gStyle->SetTitleSize(0.05,"X");
	gStyle->SetTitleOffset(1.2,"X");
	gStyle->SetLabelFont(42,"Y");
	gStyle->SetLabelSize(0.05,"Y");
	gStyle->SetTitleFont(62,"Y");
	gStyle->SetTitleSize(0.05,"Y");

	gStyle->SetOptStat(0);
	p->SetTickx();
	p->SetTicky();
	p->SetBottomMargin(0.15);
  	p->SetLeftMargin(0.125);
  	p->SetRightMargin(0.05);
  	p->SetTopMargin(0.05);
  	p->Draw();
	p->cd();
}
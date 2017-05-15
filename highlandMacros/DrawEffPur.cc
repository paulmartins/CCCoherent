void DrawEffPur(){
	// Set to true in case plots need to be updated.
	bool useCohRW = false; // use the MC microTree where the coherent is reweighted from RS -> BS
	if (useCohRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTreesRW/";
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);

	// FGD1 
	TCanvas *c1 = new TCanvas("c1","c1",1300,500);

	TPad* p1=new TPad("p1","",0.0,0.0,0.5,1,0);
	SetStyle(p1);	
	draw.DrawEffVSCut(exp,0,0,"reaction==3","",-1,9,"z","","efficiency");
	TGraph* gr_eff1 = draw.GetLastGraph();
	TLegend * leg1 = draw.GetLastLegend();
	draw.DrawPurVSCut(exp,0,0,"reaction==3","",-1,9,"same z","","purity");
	TGraph* gr_pur1 = draw.GetLastGraph();
	DrawWithStyle(gr_eff1,gr_pur1,leg1);
	c1->cd();

	// FGD2
	TPad* p2=new TPad("p2","",0.5,0.0,1.0,1.0,0);
	SetStyle(p2);	
	draw.DrawEffVSCut(exp,1,0,"fgd2reaction==3","",-1,9,"z","","efficiency");
	TGraph* gr_eff2 = draw.GetLastGraph();
	TLegend * leg2 = draw.GetLastLegend();
	draw.DrawPurVSCut(exp,1,0,"fgd2reaction==3","",-1,9,"same z","","purity");
	TGraph* gr_pur2 = draw.GetLastGraph();
	DrawWithStyle(gr_eff2,gr_pur2,leg2);
	c1->cd();
}

void DrawWithStyle(TGraph* eff, TGraph* pur, TLegend *leg){
	eff->SetTitle("");
	eff->SetLineColor(kBlack);
	eff->SetLineWidth(2);
	eff->SetMarkerStyle(20);
	eff->SetMarkerColor(kBlack);
	TH1 *h = (TH1F*)eff->GetHistogram();
	TAxis * xaxis = h->GetXaxis();
	xaxis->SetLabelOffset(0.01);
	xaxis->SetLabelSize(0.055);
	pur->SetLineColor(kRed+1);
	pur->SetLineWidth(2);
	pur->SetMarkerStyle(20);
	pur->SetMarkerColor(kRed+1);
	eff->Draw("pl");
	pur->Draw("same pl");
	xaxis->Draw("same");
	leg->SetX1NDC(0.6);leg->SetX2NDC(0.85);leg->SetY1NDC(0.75);leg->SetY2NDC(0.9);
	leg->SetMargin(0.4);
	leg->SetBorderSize(0);
	leg->Draw();
}

Experiment SetUpExpt(std::string pathToMCMicroTree, std::string pathToDataMicroTree){
	Experiment exp("nd280");
	// Create MC samples 
	DataSample * mc2a = new DataSample(pathToMCMicroTree+"MicroTree_MC_R2a.root");
	DataSample * mc2w = new DataSample(pathToMCMicroTree+"MicroTree_MC_R2w.root");
	DataSample * mc3b = new DataSample(pathToMCMicroTree+"MicroTree_MC_R3b.root");
	DataSample * mc3c = new DataSample(pathToMCMicroTree+"MicroTree_MC_R3c.root");
	DataSample * mc4a = new DataSample(pathToMCMicroTree+"MicroTree_MC_R4a.root");
	DataSample * mc4w = new DataSample(pathToMCMicroTree+"MicroTree_MC_R4w.root");
	// Create data samples
	DataSample * data2a = new DataSample(pathToDataMicroTree+"MicroTree_Data_R2a.root");
	DataSample * data2w = new DataSample(pathToDataMicroTree+"MicroTree_Data_R2w.root");
	DataSample * data3b = new DataSample(pathToDataMicroTree+"MicroTree_Data_R3b.root");
	DataSample * data3c = new DataSample(pathToDataMicroTree+"MicroTree_Data_R3c.root");
	DataSample * data4a = new DataSample(pathToDataMicroTree+"MicroTree_Data_R4a.root");
	DataSample * data4w = new DataSample(pathToDataMicroTree+"MicroTree_Data_R4w.root");
	// Create samples group, run by run
	SampleGroup run2a("run2a");
	run2a.AddMCSample("magnet",mc2a);
	run2a.AddDataSample(data2a);
	SampleGroup run2w("run2w");
	run2w.AddMCSample("magnet",mc2w);
	run2w.AddDataSample(data2w);
	SampleGroup run3b("run3b");
	run3b.AddMCSample("magnet",mc3b);
	run3b.AddDataSample(data3b);
	SampleGroup run3c("run3c");
	run3c.AddMCSample("magnet",mc3c);
	run3c.AddDataSample(data3c);
	SampleGroup run4a("run4a");
	run4a.AddMCSample("magnet",mc4a);
	run4a.AddDataSample(data4a);
	SampleGroup run4w("run4w");
	run4w.AddMCSample("magnet",mc4w);
	run4w.AddDataSample(data4w);
	// Add the sample groups to the experiment class
	exp.AddSampleGroup("run2a",run2a);
	exp.AddSampleGroup("run2w",run2w);
	exp.AddSampleGroup("run3b",run3b);
	exp.AddSampleGroup("run3c",run3c);
	exp.AddSampleGroup("run4a",run4a);
	exp.AddSampleGroup("run4w",run4w);
	// because zero_var is now dead
	exp.SetCurrentTree("default"); 
	return exp;
}

// Plot with style !
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
	p->SetBottomMargin(0.175);
  	p->SetLeftMargin(0.1);
  	p->SetRightMargin(0.1);
  	p->SetTopMargin(0.05);
  	p->SetTickx();
  	p->SetTicky();
  	p->Draw();
	p->cd();
}
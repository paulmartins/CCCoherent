void DrawNuEReco(){
	bool useCohRW = false; // use the MC microTree where the coherent is reweighted from RS -> BS
	if (useCohRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/RW/";
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);

	// FGD1 
	TCanvas *c1 = new TCanvas("c1","FGD1",1400,500);

	TPad* p1=new TPad("p1","",0.0,0.0,0.5,1.0,0);
	SetStyle(p1);
	draw.SetTitleX("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.70,0.875,0.85);
	double xbins1[31]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0,3.5,4.0};
	draw.Draw(exp,"all","all","Emupi/1000.",30,xbins1,"reaccoh","accum_level[][0][0]>9 && reaction==3","","NODATA  NOSTAT WCORR");
	TLegend * leg1 = draw.GetLastLegend();
	leg1->SetMargin(0.45);
	leg1->SetBorderSize(0);
	draw.Draw(exp,"all","all","nu_trueE/1000",30,xbins1,"all","accum_level[][0][0]>9 && reaction==3","hist","NODATA NOSTAT WCORR NODRAW");
	TH1* hnu_trueE = draw.GetLastStackTotal();
	double integral = hnu_trueE->Integral("width");
	hnu_trueE->Scale(1/integral,"width");
	hnu_trueE->SetLineColor(kBlack); hnu_trueE->SetLineWidth(2); hnu_trueE->SetLineStyle(2); hnu_trueE->Draw("same  hist");
	leg1->AddEntry(hnu_trueE, "True E_{#nu}","l");
	leg1->Draw();
	c1->cd();

	TPad* p2=new TPad("p2","",0.5,0.0,1.0,1.0,0);
	SetStyle(p2);
	draw.SetRangeY(0,12);
	draw.SetTitleX("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.70,0.875,0.85);
	double xbins2[31]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0,3.5,4.0};
	draw.Draw(exp,"all","all","Emupi/1000.",30,xbins2,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaction==3","","NODATA  NOSTAT WCORR");
	TLegend * leg2 = draw.GetLastLegend();
	leg2->SetMargin(0.45);
	leg2->SetBorderSize(0);
	draw.Draw(exp,"all","all","nu_trueE/1000",30,xbins2,"all","accum_level[][1][0]>9 && fgd2reaction==3","hist","NODATA NOSTAT WCORR NODRAW");
	TH1* hnu_trueE2 = draw.GetLastStackTotal();
	double integral = hnu_trueE2->Integral("width");
	hnu_trueE2->Scale(1/integral,"width");
	hnu_trueE2->SetLineColor(kBlack); hnu_trueE2->SetLineWidth(2); hnu_trueE2->SetLineStyle(2); hnu_trueE2->Draw("same  hist");
	leg2->AddEntry(hnu_trueE2, "True E_{#nu}","l");
	leg2->Draw();
}

// Handy function to set up your experiment
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
	p->SetBottomMargin(0.15);
  	p->SetLeftMargin(0.125);
  	p->SetRightMargin(0.05);
  	p->SetTopMargin(0.05);
  	p->SetTickx();
  	p->SetTicky();
  	p->Draw();
	p->cd();
}
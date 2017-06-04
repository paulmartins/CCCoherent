void CheckEventsMigration(){
	// only put data sample to have correct POT normalisation
	// should not plot the data/MC comparison at the selection level, analysis is still blind !
	bool useCohRW = false; // use the MC microTree where the coherent is reweighted from RS -> BS
	if (useCohRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/RW/";
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);

// FGD1 
	TCanvas *c1 = new TCanvas("c1","FGD1",900,1000);

	TPad* p1=new TPad("p1","",0.0,0.67,0.5,1.0,0);
	SetStyle(p1);
	draw.SetTitleY("Reconstructed p_{#mu^{-}} [GeV]");
	draw.SetTitleX("True p_{#mu^{-}} [GeV]");
	double xbins[5]={0.01,0.2,0.7,5,100};
	draw.Draw(exp,"all","all","selmu_mom/1000 : truelepton_mom/1000",4,xbins,4,xbins,"all","accum_level[][1][0]>9","text COL"," NOVARBIN NODATA WCORR");
	gPad->SetLogx(1);
	gPad->SetLogy(1);
	c1->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);
	draw.SetTitleY("Reconstructed cos(#theta_{#mu^{-}})");
	draw.SetTitleX("True cos(#theta_{#mu^{-}})");
	double xbins2[4]={-1,0.7,0.95,1};
	draw.Draw(exp,"all","all","selmu_costheta : truelepton_costheta",3,xbins2,3,xbins2,"all","accum_level[][1][0]>9","text COL"," NOVARBIN NODATA WCORR");
	c1->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	draw.SetTitleY("Reconstructed p_{#pi^{+}} [GeV]");
	draw.SetTitleX("True p_{#pi^{+}} [GeV]");
	double xbins3[5]={0.01,0.15,0.4,1.5,100};
	draw.Draw(exp,"all","all","selpi_mom/1000 : truepi_mom/1000",4,xbins3,4,xbins3,"all","accum_level[][1][0]>9","text COL"," NOVARBIN NODATA WCORR");
	gPad->SetLogx(1);
	gPad->SetLogy(1);
	c1->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	draw.SetTitleY("Reconstructed cos(#theta_{#pi^{+}})");
	draw.SetTitleX("True cos(#theta_{#pi^{+}})");
	double xbins4[4]={-1,0.45,0.9,1};
	draw.Draw(exp,"all","all","selpi_costheta : truepi_costheta",3,xbins4,3,xbins4,"all","accum_level[][1][0]>9","text COL"," NOVARBIN NODATA WCORR");
	c1->cd();

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	draw.SetTitleY("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleX("True E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	double xbins5[5]={0.1,0.5,1.25,6.5,100};
	draw.Draw(exp,"all","all","Emupi/1000. : trueEmupi/1000",4,xbins5,4,xbins5,"all","accum_level[][1][0]>9","text COL"," NOVARBIN NODATA WCORR");
	gPad->SetLogx(1);
	gPad->SetLogy(1);
	c1->cd();

	TPad* p6=new TPad("p6","",0.5,0.0,1.0,0.32,0);
	SetStyle(p6);
	draw.SetTitleY("Reconstructed #theta_{#pi^{+}#mu^{-}} [deg]");
	draw.SetTitleX("True #theta_{#pi^{+}#mu^{-}} [deg]");
	double xbins6[4]={0.1,90,150,180};
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14 : trueThetaCoplanar*180/3.14 ",3,xbins6,3,xbins6,"all","accum_level[][1][0]>9","text COL"," NOVARBIN NODATA WCORR");
	c1->cd();

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
	const UInt_t Number = 5;
  	Double_t Red[Number]    = { 0.00, 0.00, 1.00, 1.00, 1.00 };
  	Double_t Green[Number]  = { 0.00, 1.00, 1.00, 1.00, 0.00 };
  	Double_t Blue[Number]   = { 1.00, 1.00, 1.00, 0.00, 0.00 };
  	Double_t Length[Number] = { 0.00, 0.40, 0.50, 0.60, 1.00 };
  	TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,50);

	gStyle->SetLabelFont(42,"X");
	gStyle->SetLabelSize(0.05,"X");
	gStyle->SetTitleFont(62,"X");
	gStyle->SetTitleSize(0.05,"X");
	gStyle->SetTitleOffset(1.2,"X");
	gStyle->SetLabelFont(42,"Y");
	gStyle->SetLabelSize(0.05,"Y");
	gStyle->SetTitleFont(62,"Y");
	gStyle->SetTitleSize(0.05,"Y");

	gStyle->SetOptStat(1000000);
	p->SetTickx();
	p->SetTicky();
	p->SetBottomMargin(0.15);
  	p->SetLeftMargin(0.125);
  	p->SetRightMargin(0.15);
  	p->SetTopMargin(0.1);
  	p->Draw();
	p->cd();
}
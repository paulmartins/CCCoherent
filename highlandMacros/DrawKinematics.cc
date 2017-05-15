void DrawKinematics(){
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
	draw.SetFillStyle(1001);
	draw.SetTitleX("Reconstructed p_{#mu^{-}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.75,0.875,0.85);
	double xbins[32]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,3.25,3.5,3.75,4.0,4.5,5.0};
	draw.Draw(exp,"all","all","selmu_mom/1000",31,xbins,"reaccoh","accum_level[][0][0]>9 ","","NODATA NOSTAT WCORR"); // Need to active WCORR to get the reweight 
	TLegend * leg1 = draw.GetLastLegend();
	leg1->SetMargin(0.45);
	leg1->SetBorderSize(0);
	leg1->Draw();
	c1->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);
	draw.SetTitleX("Reconstructed cos(#theta_{#mu^{-}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.75,0.475,0.85);
	double xbins2[18]={0.5,0.6,0.7,0.75,0.8,0.82,0.84,0.86,0.88,0.90,0.92,0.94,0.95,0.96,0.97,0.98,0.99,1};
	draw.Draw(exp,"all","all","selmu_costheta",17,xbins2,"reaccoh","accum_level[][0][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg2 = draw.GetLastLegend();
	leg2->SetMargin(0.45);
	leg2->SetBorderSize(0);
	leg2->Draw();
	c1->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	draw.SetTitleX("Reconstructed p_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.75,0.875,0.85);
	double xbins3[29]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0};
	draw.Draw(exp,"all","all","selpi_mom/1000",28,xbins3,"reaccoh","accum_level[][0][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg3 = draw.GetLastLegend();
	leg3->SetMargin(0.45);
	leg3->SetBorderSize(0);
	leg3->Draw();
	c1->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	draw.SetTitleX("Reconstructed cos(#theta_{#pi^{+}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.75,0.475,0.85);
	double xbins4[23]={0.2,0.3,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.725,0.75,0.775,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1};
	draw.Draw(exp,"all","all","selpi_costheta",22,xbins4,"reaccoh","accum_level[][0][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg4 = draw.GetLastLegend();
	leg4->SetMargin(0.45);
	leg4->SetBorderSize(0);
	leg4->Draw();
	c1->cd();

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	draw.SetTitleX("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.70,0.875,0.85);
	double xbins5[31]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0,3.5,4.0};
	draw.Draw(exp,"all","all","Emupi/1000.",30,xbins5,"reaccoh","accum_level[][0][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg5 = draw.GetLastLegend();
	leg5->SetMargin(0.45);
	leg5->SetBorderSize(0);
	leg5->Draw();
	c1->cd();

	TPad* p6=new TPad("p6","",0.5,0.0,1.0,0.32,0);
	SetStyle(p6);
	draw.SetTitleX("Reconstructed #theta_{#pi^{+}#mu^{-}} [deg]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.75,0.475,0.85);
	double xbins6[21]={0.0,20,40,60,80,90,100,110,120,125,130,135,140,145,150,155,160,165,170,175,180};
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",20,xbins6,"reaccoh","accum_level[][0][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg6 = draw.GetLastLegend();
	leg6->SetMargin(0.45);
	leg6->SetBorderSize(0);
	leg6->Draw();
	c1->cd();

	// FGD2
	TCanvas *c2 = new TCanvas("c2","FGD2",900,1000);

	TPad* p1=new TPad("p1","",0.0,0.67,0.5,1.0,0);
	SetStyle(p1);
	draw.SetTitleX("Reconstructed p_{#mu^{-}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.75,0.875,0.85);
	double xbins[32]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,3.25,3.5,3.75,4.0,4.5,5.0};
	draw.Draw(exp,"all","all","selmu_mom/1000",31,xbins,"fgd2reaccoh","accum_level[][1][0]>9","","NODATA  NOSTAT WCORR");
	TLegend * leg1 = draw.GetLastLegend();
	leg1->SetMargin(0.45);
	leg1->SetBorderSize(0);
	leg1->Draw();
	c2->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);
	draw.SetTitleX("Reconstructed cos(#theta_{#mu^{-}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.75,0.475,0.85);
	double xbins2[18]={0.5,0.6,0.7,0.75,0.8,0.82,0.84,0.86,0.88,0.90,0.92,0.94,0.95,0.96,0.97,0.98,0.99,1};
	draw.Draw(exp,"all","all","selmu_costheta",17,xbins2,"fgd2reaccoh","accum_level[][1][0]>9","","NODATA  NOSTAT WCORR");
	TLegend * leg2 = draw.GetLastLegend();
	leg2->SetMargin(0.45);
	leg2->SetBorderSize(0);
	leg2->Draw();
	c2->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	draw.SetTitleX("Reconstructed p_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.75,0.875,0.85);
	double xbins3[29]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0};
	draw.Draw(exp,"all","all","selpi_mom/1000",28,xbins3,"fgd2reaccoh","accum_level[][1][0]>9","","NODATA  NOSTAT WCORR");
	TLegend * leg3 = draw.GetLastLegend();
	leg3->SetMargin(0.45);
	leg3->SetBorderSize(0);
	leg3->Draw();
	c2->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	draw.SetTitleX("Reconstructed cos(#theta_{#pi^{+}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.75,0.475,0.85);
	double xbins4[23]={0.2,0.3,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.725,0.75,0.775,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1};
	draw.Draw(exp,"all","all","selpi_costheta",22,xbins4,"fgd2reaccoh","accum_level[][1][0]>9","","NODATA  NOSTAT WCORR");
	TLegend * leg4 = draw.GetLastLegend();
	leg4->SetMargin(0.45);
	leg4->SetBorderSize(0);
	leg4->Draw();
	c2->cd();

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	draw.SetTitleX("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.70,0.875,0.85);
	double xbins5[31]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0,3.5,4.0};
	draw.Draw(exp,"all","all","Emupi/1000.",30,xbins5,"fgd2reaccoh","accum_level[][1][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg5 = draw.GetLastLegend();
	leg5->SetMargin(0.45);
	leg5->SetBorderSize(0);
	leg5->Draw();
	c2->cd();

	TPad* p6=new TPad("p6","",0.5,0.0,1.0,0.32,0);
	SetStyle(p6);
	draw.SetTitleX("Reconstructed #theta_{#pi^{+}#mu^{-}} [deg]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.75,0.475,0.85);
	double xbins6[21]={0.0,20,40,60,80,90,100,110,120,125,130,135,140,145,150,155,160,165,170,175,180};
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",20,xbins6,"fgd2reaccoh","accum_level[][1][0]>9 ","","NODATA  NOSTAT WCORR");
	TLegend * leg6 = draw.GetLastLegend();
	leg6->SetMargin(0.45);
	leg6->SetBorderSize(0);
	leg6->Draw();
	c2->cd();
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
void DrawSelection(){
	// Define a so-called experiment
	Experiment exp("nd280");
	// Define a drawingTool engine
	std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	DrawingTools draw(pathToMCMicroTree+"MicroTree_MC_R2w.root");
	// Create MC samples 
	DataSample * mc2a = new DataSample(pathToMCMicroTree+"MicroTree_MC_R2a.root");
	DataSample * mc2w = new DataSample(pathToMCMicroTree+"MicroTree_MC_R2w.root");
	DataSample * mc3b = new DataSample(pathToMCMicroTree+"MicroTree_MC_R3b.root");
	DataSample * mc3c = new DataSample(pathToMCMicroTree+"MicroTree_MC_R3c.root");
	DataSample * mc4a = new DataSample(pathToMCMicroTree+"MicroTree_MC_R4a.root");
	DataSample * mc4w = new DataSample(pathToMCMicroTree+"MicroTree_MC_R4w.root");
	// Create data samples, just for POT normalisation. !! DO NOT PLOT THE DATA !!
	DataSample * data2a = new DataSample(pathToMCMicroTree+"MicroTree_Data_R2a.root");
	DataSample * data2w = new DataSample(pathToMCMicroTree+"MicroTree_Data_R2w.root");
	DataSample * data3b = new DataSample(pathToMCMicroTree+"MicroTree_Data_R3b.root");
	DataSample * data3c = new DataSample(pathToMCMicroTree+"MicroTree_Data_R3c.root");
	DataSample * data4a = new DataSample(pathToMCMicroTree+"MicroTree_Data_R4a.root");
	DataSample * data4w = new DataSample(pathToMCMicroTree+"MicroTree_Data_R4w.root");
	
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
	
	// Use the default tree (= reconstructed information)
	exp.SetCurrentTree("default");

	// FGD1 
	TCanvas *c1 = new TCanvas("c1","c1",900,1000);
	c1->SetFillStyle(4000);
	
	TPad* p1=new TPad("p1","",0.0,0.66,0.5,1,0);
	SetStyle(p1);
	draw.SetTitleX("Nbr FGD1 tracks");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.8,0.9,0.85);
	draw.Draw(exp,"all","all","NFGD1Tracks",8,0,8,"reaccoh","accum_level[][0][0]>6","","NODATA ");
	draw.DrawCutLineVertical(3,true,"l",0.95);
	// Customize the legend
	TLegend * leg1 = draw.GetLastLegend();
	leg1->SetMargin(0.4);
	leg1->SetBorderSize(0);
	leg1->Draw();
	c1->cd();

	TPad* p2=new TPad("p2","",0.0,0.33,0.5,0.65,0);
	SetStyle(p2);
	draw.SetTitleX("Vertex Activity 5#times5 [MeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.8,0.9,0.85);
	draw.Draw(exp,"all","all","selmu_fgd_V55/21.7",50,0,100,"reaccoh","accum_level[][0][0]>7","","NODATA ");
	draw.DrawCutLineVertical(14,true,"l",0.95);
	TLegend * leg2 = draw.GetLastLegend();
	leg2->SetMargin(0.4);
	leg2->SetBorderSize(0);
	leg2->Draw();
	c1->cd();

	TPad* p3=new TPad("p3","",0.0,0.0,0.5,0.32,0);
	SetStyle(p3);
	draw.SetTitleX("t [GeV^{2}]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.8,0.9,0.85);
	draw.Draw(exp,"all","all","sel_t",30,0,3,"reaccoh","accum_level[][0][0]>8","","NODATA  NOSTAT");
	draw.DrawCutLineVertical(0.4,true,"l",0.95);
	TLegend * leg3 = draw.GetLastLegend();
	leg3->SetMargin(0.4);
	leg3->SetBorderSize(0);
	leg3->Draw();
	c1->cd();

	// FGD2
	TPad* p4=new TPad("p4","",0.5,0.66,1.0,1,0);
	SetStyle(p4);
	draw.SetTitleX("Nbr FGD2 tracks");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.8,0.9,0.85);
	draw.Draw(exp,"all","all","NFGD2Tracks",8,0,8,"fgd2reaccoh","accum_level[][1][0]>6","","NODATA NOSTAT");
	draw.DrawCutLineVertical(3,true,"l",0.95);
	TLegend * leg4 = draw.GetLastLegend();
	leg4->SetMargin(0.4);
	leg4->SetBorderSize(0);
	leg4->Draw();
	c1->cd();

	TPad* p5=new TPad("p5","",0.5,0.33,1.0,0.65,0);
	SetStyle(p5);
	draw.SetTitleX("Vertex Activity 2#times7 [MeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.8,0.9,0.85);
	draw.Draw(exp,"all","all","selmu_fgd_V27/21.7",50,0,50,"fgd2reaccoh","accum_level[][1][0]>7","","NODATA  NOSTAT");
	draw.DrawCutLineVertical(7,true,"l",0.95);
	TLegend * leg5 = draw.GetLastLegend();
	leg5->SetMargin(0.4);
	leg5->SetBorderSize(0);
	leg5->Draw();
	c1->cd();

	TPad* p6=new TPad("p6","",0.5,0.0,1.0,0.32,0);
	SetStyle(p6);
	draw.SetTitleX("t [GeV^{2}]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.8,0.9,0.85);
	draw.Draw(exp,"all","all","sel_t",30,0,3,"fgd2reaccoh","accum_level[][1][0]>8","","NODATA  NOSTAT");
	draw.DrawCutLineVertical(0.3,true,"l",0.95);
	TLegend * leg6 = draw.GetLastLegend();
	leg6->SetMargin(0.4);
	leg6->SetBorderSize(0);
	leg6->Draw();
	c1->cd();
}

void SetStyle(TPad *p){
	gStyle->SetLabelFont(42,"X");
	gStyle->SetLabelSize(0.05,"X");
	gStyle->SetTitleFont(62,"X");
	gStyle->SetTitleSize(0.05,"X");
	gStyle->SetTitleOffset(1.2,"X");
	gStyle->SetLabelFont(42,"Y");
	gStyle->SetLabelSize(0.05,"Y");
	gStyle->SetTitleFont(62,"Y");
	gStyle->SetTitleSize(0.05,"Y");
	gStyle->SetTitleOffset(1.2,"Y");
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	gStyle->SetOptStat(00000000);

	p->SetBottomMargin(0.125);
  	p->SetLeftMargin(0.125);
  	p->SetRightMargin(0.05);
  	p->SetTopMargin(0.05);
  	p->SetFillStyle(4000);
  	p->Draw();
	p->cd();	
}
void DrawBinningsSB(){
	// Same as DrawBinnings but for the sideband samples
	// Used to draw the binning for different fake data samples (negative scale factor problem)
	bool useResDISRW = true; // use the MC microTree where the REs and DIS have been reweigthed to different fake data
	// In the case of sideband it okay to look at the data, so no need the NODATA argument in the drawing options

	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	if (useResDISRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTreesRW/SidebandRW/FD6/"; // choose which Fake data to use !
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);

	// Phase space cuts
	std::string true_cut = "&& truelepton_mom>200 && truelepton_mom < 5000 && truelepton_costheta >0.75 && truelepton_costheta < 1 && truepi_mom>150 && truepi_mom <1500 && truepi_costheta >0.45 && truepi_costheta < 1 && trueEmupi > 500 && trueEmupi < 6500 && trueThetaCoplanar *180/3.14 > 90";
	std::string reco_cut = "&& selmu_mom>200 && truelepton_mom < 5000 && selmu_costheta >0.75 && selmu_costheta < 1 && selpi_mom>150 && selpi_mom <1500 && selpi_costheta >0.45 && selpi_costheta < 1 && Emupi > 500 && Emupi < 6500 && ThetaCoplanar*180/3.14 > 90";
	
	// Save histos
	TH1* histos[12];
	TH1* data_histos[12];

	// FGD1 
	TCanvas *c1 = new TCanvas("c1","FGD1",900,1000);

	TPad* p1=new TPad("p1","",0.0,0.67,0.5,1.0,0);
	SetStyle(p1);
	draw.SetTitleX("Reconstructed p_{#mu^{-}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.55,0.85,0.65);
	double xbins[3]={0.2,0.7,5};
	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut,"text","   NOVARBIN  WCORR");
	histos[0] = draw.GetLastStackTotal();
	data_histos[0] = draw.GetLastHisto();
	TLegend * leg1 = draw.GetLastLegend();
	leg1->SetMargin(0.45);
	leg1->SetBorderSize(1);
	leg1->Draw();
	c1->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);
	draw.SetTitleX("Reconstructed cos(#theta_{#mu^{-}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.55,0.45,0.65);
	double xbins2[3]={0.7,0.95,1};
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"reaccoh","accum_level[][0][1]>7"+reco_cut,"text","   NOVARBIN  WCORR");
	histos[1] = draw.GetLastStackTotal();
	data_histos[1] = draw.GetLastHisto();
	TLegend * leg2 = draw.GetLastLegend();
	leg2->SetMargin(0.45);
	leg2->SetBorderSize(1);
	leg2->Draw();
	c1->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	draw.SetTitleX("Reconstructed p_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.55,0.85,0.65);
	double xbins3[3]={0.15,0.4,1.5};
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"reaccoh","accum_level[][0][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[2] = draw.GetLastStackTotal();
	data_histos[2] = draw.GetLastHisto();
	TLegend * leg3 = draw.GetLastLegend();
	leg3->SetMargin(0.45);
	leg3->SetBorderSize(1);
	leg3->Draw();
	c1->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	draw.SetTitleX("Reconstructed cos(#theta_{#pi^{+}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.55,0.45,0.65);
	double xbins4[3]={0.45,0.9,1};
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"reaccoh","accum_level[][0][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[3] = draw.GetLastStackTotal();
	data_histos[3] = draw.GetLastHisto();
	TLegend * leg4 = draw.GetLastLegend();
	leg4->SetMargin(0.45);
	leg4->SetBorderSize(1);
	leg4->Draw();
	c1->cd();

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	draw.SetTitleX("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.70,0.875,0.85);
	double xbins5[3]={0.5,1.25,6.5};
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"reaccoh","accum_level[][0][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[4] = draw.GetLastStackTotal();
	data_histos[4] = draw.GetLastHisto();
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
	double xbins6[21]={90,150,180};
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"reaccoh","accum_level[][0][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[5] = draw.GetLastStackTotal();
	data_histos[5] = draw.GetLastHisto();
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
	draw.SetLegendParam(0.6,0.55,0.85,0.65);
	double xbins[3]={0.2,0.7,5};
	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut,"text","   NOVARBIN  WCORR");
	histos[6] = draw.GetLastStackTotal();
	data_histos[6] = draw.GetLastHisto();
	TLegend * leg1 = draw.GetLastLegend();
	leg1->SetMargin(0.45);
	leg1->SetBorderSize(1);
	leg1->Draw();
	c2->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);
	draw.SetTitleX("Reconstructed cos(#theta_{#mu^{-}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.55,0.45,0.65);
	double xbins2[3]={0.7,0.95,1};
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut,"text","   NOVARBIN  WCORR");
	histos[7] = draw.GetLastStackTotal();
	data_histos[7] = draw.GetLastHisto();
	TLegend * leg2 = draw.GetLastLegend();
	leg2->SetMargin(0.45);
	leg2->SetBorderSize(1);
	leg2->Draw();
	c2->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	draw.SetTitleX("Reconstructed p_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.55,0.85,0.65);
	double xbins3[3]={0.15,0.4,1.5};
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"fgd2reaccoh","accum_level[][1][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[8] = draw.GetLastStackTotal();
	data_histos[8] = draw.GetLastHisto();
	TLegend * leg3 = draw.GetLastLegend();
	leg3->SetMargin(0.45);
	leg3->SetBorderSize(1);
	leg3->Draw();
	c2->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	draw.SetTitleX("Reconstructed cos(#theta_{#pi^{+}})");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.2,0.55,0.45,0.65);
	double xbins4[3]={0.45,0.9,1};
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"fgd2reaccoh","accum_level[][1][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[9] = draw.GetLastStackTotal();
	data_histos[9] = draw.GetLastHisto();	
	TLegend * leg4 = draw.GetLastLegend();
	leg4->SetMargin(0.45);
	leg4->SetBorderSize(1);
	leg4->Draw();
	c2->cd();

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	draw.SetTitleX("Reconstructed E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.70,0.875,0.85);
	double xbins5[3]={0.5,1.25,6.5};
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"fgd2reaccoh","accum_level[][1][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[10] = draw.GetLastStackTotal();
	data_histos[10] = draw.GetLastHisto();
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
	double xbins6[21]={90,150,180};
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"fgd2reaccoh","accum_level[][1][1]>7 "+reco_cut,"text","   NOVARBIN  WCORR");
	histos[11] = draw.GetLastStackTotal();
	data_histos[11] = draw.GetLastHisto();
	TLegend * leg6 = draw.GetLastLegend();
	leg6->SetMargin(0.45);
	leg6->SetBorderSize(0);
	leg6->Draw();
	c2->cd();

	// Comparison summary plot
	// Can save the Fake Data histos and used it later for the sideband FD global comparison !!
	TCanvas *c3 = new TCanvas("c3","c3",900,600);
	TPad* pp3=new TPad("pp3","",0.0,0.0,1.0,1.0,0);
	SetStyle(pp3);
	const char *label[24]  = {"p_{#mu, 1}","p_{#mu, 2}","cos#theta_{#mu, 1}","cos#theta_{#mu, 2}","p_{#pi, 1}","p_{#pi, 2}","cos#theta_{#pi, 1}","cos#theta_{#pi, 2}","E_{#nu}^{reco, 1}","E_{#nu}^{reco, 2}","#theta_{#pi #mu, 1}","#theta_{#pi #mu, 2}","p_{#mu, 1}","p_{#mu, 2}","cos#theta_{#mu, 1}","cos#theta_{#mu, 2}","p_{#pi, 1}","p_{#pi, 2}","cos#theta_{#pi, 1}","cos#theta_{#pi, 2}","E_{#nu}^{reco, 1}","E_{#nu}^{reco, 2}","#theta_{#pi #mu, 1}","#theta_{#pi #mu, 2}"};
	TH1D * H_all = new TH1D("H_all","",24,0,24);
	TH1D * H_data = new TH1D("H_data","",24,0,24);
	for(int j=0;j<12;j++){
		for(int i=1;i<3;i++){
			H_all->GetXaxis()->SetBinLabel(j*2+i,label[j*2+i-1]);
			H_all->Fill(j*2+i-1,histos[j]->GetBinContent(i) );
			H_data->Fill(j*2+i-1,data_histos[j]->GetBinContent(i) );
		}
	}
	H_all->SetLineColor(kRed+1);
	H_all->SetLineWidth(2);
	H_all->SetLineStyle(2);
	H_all->GetYaxis()->SetTitle("Events");
	H_all->GetYaxis()->SetRangeUser(0,500);
	H_all->GetXaxis()->LabelsOption("v");
	H_all->Draw("hist");
	H_data->SetLineColor(kBlack);
	H_data->SetLineWidth(2);
	H_data->SetMarkerStyle(20);
	H_data->Draw("same p e0");
	TLegend *legg = new TLegend(0.6,0.7,0.9,0.9);
	legg->AddEntry(H_all,"NEUT nominal","l p");
	legg->AddEntry(H_data,"NEUT FD (C_{A}^{5} + #delta_{DIS} reweight)","l f");
	legg->SetFillColor(kWhite);
	legg->SetMargin(0.25);
	legg->SetBorderSize(0);
	legg->Draw("same");
	TLine *line = new TLine(12,0,12,200);
	line->SetLineStyle(2);
	line->SetLineColor(kGray);
	line->Draw("same");
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
	p->SetTickx();
	p->SetTicky();
	p->SetBottomMargin(0.15);
  	p->SetLeftMargin(0.125);
  	p->SetRightMargin(0.05);
  	p->SetTopMargin(0.05);
  	p->Draw();
	p->cd();
}

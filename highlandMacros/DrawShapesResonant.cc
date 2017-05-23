void DrawShapesResonant(){
	// Macro to compare the shape of the Resonant component in sideband sample and signal sample

	bool useCohRW = false; // Doesn't matter which coherent model we use here: Bkg (Res or DIS) are the same anyway
	if (useCohRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTreesRW/";
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);

	// phase space cuts and bkg definition
	// set reaccoh==2 and fgd2reaccoh == 2 for DIS comparison
	std::string reco_cut = " && selmu_mom>200 && truelepton_mom < 5000 && selmu_costheta >0.75 && selmu_costheta < 1 && selpi_mom>150 && selpi_mom <1500 && selpi_costheta >0.45 && selpi_costheta < 1 && Emupi > 500 && Emupi < 6500 && ThetaCoplanar*180/3.14 > 90";
	std::string reac_cut1 = " && reaccoh==1";
	std::string reac_cut2 = " && fgd2reaccoh==1";

	// Draw all low-level plots and save the histo temporary
	TCanvas *c1 = new TCanvas("c1","c1",1000,1100);
	c1->Divide(4,6);
	c1->cd(1);
	draw.SetTitleX("Reconstructed p_{#mu^{-}} [GeV]");
	draw.SetTitleY("N_{evts}");
	draw.SetLegendParam(0.5,0.5,0.9,0.9);
	const int nbins = 7;
	double xbins[nbins+1]={0.2,0.4,0.6,0.8,1,1.5,2,5};	
	draw.Draw(exp,"all","all","selmu_mom/1000",nbins,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_mumom_sb1 = draw.GetLastStackTotal();
	c1->cd(2);
	draw.Draw(exp,"all","all","selmu_mom/1000",nbins,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_mumom_bg1 = draw.GetLastStackTotal();
	c1->cd(3);
	draw.Draw(exp,"all","all","selmu_mom/1000",nbins,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_mumom_sb2 = draw.GetLastStackTotal();	
	c1->cd(4);
	draw.Draw(exp,"all","all","selmu_mom/1000",nbins,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_mumom_bg2 = draw.GetLastStackTotal();
	
	c1->cd(5);
	draw.SetTitleX("Reconstructed cos(#theta_{#mu^{-}})");
	draw.SetTitleY("N_{evts}");
	draw.SetLegendParam(0.2,0.5,0.6,0.9);
	const int nbins = 6;
	double xbins[nbins+1]={0.75,0.85,0.9,0.925,0.95,0.975,1};
	draw.Draw(exp,"all","all","selmu_costheta",nbins,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_mutheta_sb1 = draw.GetLastStackTotal();
	c1->cd(6);
	draw.Draw(exp,"all","all","selmu_costheta",nbins,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_mutheta_bg1 = draw.GetLastStackTotal();
	c1->cd(7);
	draw.Draw(exp,"all","all","selmu_costheta",nbins,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_mutheta_sb2 = draw.GetLastStackTotal();	
	c1->cd(8);
	draw.Draw(exp,"all","all","selmu_costheta",nbins,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_mutheta_bg2 = draw.GetLastStackTotal();

	c1->cd(9);
	draw.SetTitleX("Reconstructed p_{#pi^{+}} [GeV]");
	draw.SetTitleY("N_{evts}");
	draw.SetLegendParam(0.5,0.5,0.9,0.9);
	const int nbins = 7;
	double xbins[nbins+1]={0.15,0.225,0.3,0.4,0.5,0.6,0.8,1.5};	
	draw.Draw(exp,"all","all","selpi_mom/1000",nbins,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_pimom_sb1 = draw.GetLastStackTotal();
	c1->cd(10);
	draw.Draw(exp,"all","all","selpi_mom/1000",nbins,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_pimom_bg1 = draw.GetLastStackTotal();
	c1->cd(11);
	draw.Draw(exp,"all","all","selpi_mom/1000",nbins,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_pimom_sb2 = draw.GetLastStackTotal();	
	c1->cd(12);
	draw.Draw(exp,"all","all","selpi_mom/1000",nbins,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_pimom_bg2 = draw.GetLastStackTotal();

	c1->cd(13);
	draw.SetTitleX("Reconstructed cos(#theta_{#pi^{+}})");
	draw.SetTitleY("N_{evts}");
	draw.SetLegendParam(0.2,0.5,0.6,0.9);
	const int nbins = 6;
	double xbins[nbins+1]={0.45,0.65,0.8,0.9,0.95,0.975,1};
	draw.Draw(exp,"all","all","selpi_costheta",nbins,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_pitheta_sb1 = draw.GetLastStackTotal();
	c1->cd(14);
	draw.Draw(exp,"all","all","selpi_costheta",nbins,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_pitheta_bg1 = draw.GetLastStackTotal();
	c1->cd(15);
	draw.Draw(exp,"all","all","selpi_costheta",nbins,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_pitheta_sb2 = draw.GetLastStackTotal();	
	c1->cd(16);
	draw.Draw(exp,"all","all","selpi_costheta",nbins,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_pitheta_bg2 = draw.GetLastStackTotal();

	c1->cd(17);
	draw.SetTitleX("Reconstructed E_{#pi^{+}} + E_{#mu^{-}} [GeV]");
	draw.SetTitleY("N_{evts}");
	draw.SetLegendParam(0.5,0.5,0.9,0.9);
	const int nbins = 6;
	double xbins[nbins+1]={0.5,0.7,0.9,1.1,1.5,2.5,6.5};
	draw.Draw(exp,"all","all","Emupi/1000.",nbins,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_emupi_sb1 = draw.GetLastStackTotal();
	c1->cd(18);
	draw.Draw(exp,"all","all","Emupi/1000.",nbins,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_emupi_bg1 = draw.GetLastStackTotal();
	c1->cd(19);
	draw.Draw(exp,"all","all","Emupi/1000.",nbins,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_emupi_sb2 = draw.GetLastStackTotal();	
	c1->cd(20);
	draw.Draw(exp,"all","all","Emupi/1000.",nbins,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_emupi_bg2 = draw.GetLastStackTotal();

	c1->cd(21);
	draw.SetTitleX("Reconstructed #theta_{#pi^{+}#mu^{-}} [deg]");
	draw.SetTitleY("N_{evts}");
	draw.SetLegendParam(0.2,0.5,0.6,0.9);
	const int nbins = 7;
	double xbins[nbins+1]={90,120,140,155,160,170,175,180};
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",nbins,xbins,"reaccoh","accum_level[][0][1]>7"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_copl_sb1 = draw.GetLastStackTotal();
	c1->cd(22);
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",nbins,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut+reac_cut1,"","NODATA NOLEG");
	TH1* h_copl_bg1 = draw.GetLastStackTotal();
	c1->cd(23);
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",nbins,xbins,"fgd2reaccoh","accum_level[][1][1]>7"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_copl_sb2 = draw.GetLastStackTotal();	
	c1->cd(24);
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",nbins,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut+reac_cut2,"","NODATA NOLEG");
	TH1* h_copl_bg2 = draw.GetLastStackTotal();
	
	// Rescale histo (same as doing area normalisation)
	// Usual procedure when we compare the shape
	h_mumom_sb1->Scale(1/(h_mumom_sb1->Integral()),"width");
	h_mumom_bg1->Scale(1/(h_mumom_bg1->Integral()),"width");
	h_mumom_sb2->Scale(1/(h_mumom_sb2->Integral()),"width");
	h_mumom_bg2->Scale(1/(h_mumom_bg2->Integral()),"width");

	h_mutheta_sb1->Scale(1/(h_mutheta_sb1->Integral()),"width");
	h_mutheta_bg1->Scale(1/(h_mutheta_bg1->Integral()),"width");
	h_mutheta_sb2->Scale(1/(h_mutheta_sb2->Integral()),"width");
	h_mutheta_bg2->Scale(1/(h_mutheta_bg2->Integral()),"width");

	h_pimom_sb1->Scale(1/(h_pimom_sb1->Integral()),"width");
	h_pimom_bg1->Scale(1/(h_pimom_bg1->Integral()),"width");
	h_pimom_sb2->Scale(1/(h_pimom_sb2->Integral()),"width");
	h_pimom_bg2->Scale(1/(h_pimom_bg2->Integral()),"width");

	h_pitheta_sb1->Scale(1/(h_pitheta_sb1->Integral()),"width");
	h_pitheta_bg1->Scale(1/(h_pitheta_bg1->Integral()),"width");
	h_pitheta_sb2->Scale(1/(h_pitheta_sb2->Integral()),"width");
	h_pitheta_bg2->Scale(1/(h_pitheta_bg2->Integral()),"width");

	h_emupi_sb1->Scale(1/(h_emupi_sb1->Integral()),"width");
	h_emupi_bg1->Scale(1/(h_emupi_bg1->Integral()),"width");
	h_emupi_sb2->Scale(1/(h_emupi_sb2->Integral()),"width");
	h_emupi_bg2->Scale(1/(h_emupi_bg2->Integral()),"width");

	h_copl_sb1->Scale(10/(h_copl_sb1->Integral()),"width");
	h_copl_bg1->Scale(10/(h_copl_bg1->Integral()),"width");
	h_copl_sb2->Scale(10/(h_copl_sb2->Integral()),"width");
	h_copl_bg2->Scale(10/(h_copl_bg2->Integral()),"width");

	// Do the final plot including the relative bias 
	TCanvas *c2 = new TCanvas("c2","FGD1",900,1000);
	c2->Divide(2,3);
	c2->cd(1);
	DrawRatio(h_mumom_sb1,h_mumom_bg1,c2,1);
	c2->cd(2);
	DrawRatio(h_mutheta_sb1,h_mutheta_bg1,c2,2);
	c2->cd(3);
	DrawRatio(h_pimom_sb1,h_pimom_bg1,c2,3);
	c2->cd(4);
	DrawRatio(h_pitheta_sb1,h_pitheta_bg1,c2,4);
	c2->cd(5);
	DrawRatio(h_emupi_sb1,h_emupi_bg1,c2,5);
	c2->cd(6);
	DrawRatio(h_copl_sb1,h_copl_bg1,c2,6);
}

// function that draws the relative bias under the shape comparison plot
void DrawRatio(TH1* h_sideband, TH1 * h_background, TCanvas *can,int canbr){
	gStyle->SetTitleFont(62,"X");

	// Upper plot with comparison
	TPad *pad1 = new TPad("pad1","pad1",0,0.35,1,1.0);
	pad1->SetTopMargin(0.05);
   	pad1->SetBottomMargin(0);
   	pad1->SetLeftMargin(0.15);
   	pad1->Draw();
   	pad1->cd();
   	gStyle->SetOptStat(0);
   	pad1->SetTickx();
   	pad1->SetTicky();
   	TH1 * h_sideband_clone = (TH1*)h_sideband->Clone("h_sideband_clone");
   	h_sideband_clone->SetLineWidth(2);
   	h_sideband_clone->SetLineColor(kRed+1);
   	h_sideband_clone->GetYaxis()->SetLabelSize(0.085);;
   	h_sideband_clone->GetYaxis()->SetTitle("Events [a.u.]");
   	h_sideband_clone->GetYaxis()->SetTitleFont(62);
   	h_sideband_clone->GetYaxis()->SetTitleSize(0.085);
   	h_sideband_clone->GetYaxis()->SetTitleOffset(0.7);
	h_sideband_clone->Draw("hist");
   	double maxi = TMath::Max(h_sideband_clone->GetMaximum(), h_background->GetMaximum());
   	h_sideband_clone->GetYaxis()->SetRangeUser(0.0001,1.2*maxi);
   	h_background->SetLineWidth(2);
   	h_background->SetLineColor(kAzure+5);
   	h_background->Draw("same hist");
   	if(canbr == 1 || canbr == 3 || canbr == 5) TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
   	else if(canbr == 2 || canbr == 4 ) TLegend *leg = new TLegend(0.2,0.6,0.5,0.8);
   	else TLegend *leg = new TLegend(0.2,0.3,0.5,0.5);
	leg->AddEntry(h_sideband_clone,"Sideband","l");
	leg->AddEntry(h_background,"Background","l");
	leg->SetMargin(0.4);
	leg->SetBorderSize(0);
	leg->SetFillColor(kWhite);
   	leg->Draw();
   	
   	// Ratio plot underneath
   	can->cd(canbr);
   	TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.35);
   	pad2->SetTickx();
   	pad2->SetTicky();
   	pad2->SetTopMargin(0);
   	pad2->SetBottomMargin(0.4);
   	pad2->SetLeftMargin(0.15);
   	pad2->Draw();
   	pad2->cd();
   	h_sideband->Sumw2();
   	h_sideband->SetStats(0);
   	TH1 * h_sideband_clone2 = (TH1*)h_sideband->Clone("h_sideband_clone2");
   	h_sideband->Add(h_background,-1);
   	h_sideband->Divide(h_sideband_clone2);
   	h_sideband->SetLineColor(kBlack);
   	h_sideband->SetLineWidth(2);
   	h_sideband->GetYaxis()->SetTitle("(S-B)/S");
   	h_sideband->GetYaxis()->SetTitleFont(62);
   	h_sideband->GetYaxis()->CenterTitle();
   	h_sideband->GetYaxis()->SetNdivisions(405);
   	h_sideband->GetYaxis()->SetTitleSize(0.16);
   	h_sideband->GetYaxis()->SetTitleOffset(0.4);
   	h_sideband->GetYaxis()->SetLabelSize(0.16);
   	h_sideband->GetXaxis()->SetLabelSize(0.16);
   	h_sideband->GetXaxis()->SetLabelOffset(0.015);
   	h_sideband->GetXaxis()->SetTitleSize(0.16);
   	h_sideband->GetXaxis()->SetTitleOffset(1.2);
   	h_sideband->GetXaxis()->SetTickLength(0.08);
   	h_sideband->GetXaxis()->SetTitleFont(62);
   	h_sideband->Draw("ep");
   	TLine *line = new TLine(h_sideband->GetXaxis()->GetXmin(),0,h_sideband->GetXaxis()->GetXmax(),0);
  	line->SetLineColor(kBlack);
  	line->SetLineStyle(3);
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

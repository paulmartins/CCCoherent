void DrawBinnings(){
	// only put data sample to have correct POT normalisation
	// should not plot the data/MC comparison at the selection level, analysis is still blind !
	bool useCohRW = false; // use the MC microTree where the coherent is reweighted from RS -> BS
	if (useCohRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/RW/";
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);

	// phase space cuts
	std::string true_cut = "&& truelepton_mom>200 && truelepton_mom < 5000 && truelepton_costheta >0.75 && truelepton_costheta < 1 && truepi_mom>150 && truepi_mom <1500 && truepi_costheta >0.45 && truepi_costheta < 1 && trueEmupi > 500 && trueEmupi < 6500 && trueThetaCoplanar *180/3.14 > 90";
	std::string reco_cut = "&& selmu_mom>200 && selmu_mom < 5000 && selmu_costheta >0.75 && selmu_costheta < 1 && selpi_mom>150 && selpi_mom <1500 && selpi_costheta >0.45 && selpi_costheta < 1 && Emupi > 500 && Emupi < 6500 && ThetaCoplanar*180/3.14 > 90";
	
	// vector to save histos
	TH1* histos[48];
	
	// FGD1 
	TCanvas *c1 = new TCanvas("c1","FGD1",900,1000);

	TPad* p1=new TPad("p1","",0.0,0.67,0.5,1.0,0);
	SetStyle(p1);
	draw.SetTitleX("Reconstructed p_{#mu^{-}} [GeV]");
	draw.SetTitleY("Events");
	draw.SetLegendParam(0.6,0.55,0.85,0.65);
	double xbins[3]={0.2,0.7,5};
	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"reaccoh","accum_level[][0][0]>9"+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[0] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"reaccoh","accum_level[][0][0]>9"+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[1] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"reaccoh","accum_level[][0][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[2] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"reaccoh","accum_level[][0][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[3] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"reaccoh","accum_level[][0][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[4] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"reaccoh","accum_level[][0][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[5] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[6] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"fgd2reaccoh","accum_level[][1][0]>9"+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[7] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"fgd2reaccoh","accum_level[][1][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[8] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"fgd2reaccoh","accum_level[][1][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[9] = draw.GetLastStackTotal();	
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
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"fgd2reaccoh","accum_level[][1][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[10] = draw.GetLastStackTotal();
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
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"fgd2reaccoh","accum_level[][1][0]>9 "+reco_cut,"text"," NOVARBIN NODATA  WCORR");
	histos[11] = draw.GetLastStackTotal();
	TLegend * leg6 = draw.GetLastLegend();
	leg6->SetMargin(0.45);
	leg6->SetBorderSize(0);
	leg6->Draw();
	c2->cd();

	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"reaction","accum_level[][0][0]>9 && reaction==3"+reco_cut,"text"," NOVARBIN NODATA  WCORR NODRAW");
	histos[12] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"reaction","accum_level[][0][0]>9 && reaction==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[13] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"reaction","accum_level[][0][0]>9 && reaction==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[14] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"reaction","accum_level[][0][0]>9 && reaction==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[15] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"reaction","accum_level[][0][0]>9 && reaction==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[16] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"reaction","accum_level[][0][0]>9 && reaction==3 "+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[17] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"fgd2reaction","accum_level[][1][0]>9 && fgd2reaction==3"+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[18] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"fgd2reaction","accum_level[][1][0]>9 && fgd2reaction==3 "+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[19] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"fgd2reaction","accum_level[][1][0]>9 && fgd2reaction==3 "+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[20] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"fgd2reaction","accum_level[][1][0]>9 && fgd2reaction==3"+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[21] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"fgd2reaction","accum_level[][1][0]>9 && fgd2reaction==3"+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[22] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"fgd2reaction","accum_level[][1][0]>9 && fgd2reaction==3 "+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[23] = draw.GetLastStackTotal();

	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"reaccoh","accum_level[][0][0]>9 && reaccoh==3"+reco_cut,"text"," NOVARBIN NODATA  WCORR NODRAW");
	histos[24] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"reaccoh","accum_level[][0][0]>9 && reaccoh==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[25] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"reaccoh","accum_level[][0][0]>9 && reaccoh==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[26] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"reaccoh","accum_level[][0][0]>9 && reaccoh==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[27] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"reaccoh","accum_level[][0][0]>9 && reaccoh==3"+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[28] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"reaccoh","accum_level[][0][0]>9 && reaccoh==3 "+reco_cut,"text"," NOVARBIN NODATA NODRAW WCORR");
	histos[29] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selmu_mom/1000",2,xbins,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaccoh==3"+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[30] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selmu_costheta",2,xbins2,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaccoh==3 "+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[31] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_mom/1000",2,xbins3,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaccoh==3 "+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[32] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","selpi_costheta",2,xbins4,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaccoh==3"+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[33] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","Emupi/1000.",2,xbins5,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaccoh==3"+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[34] = draw.GetLastStackTotal();
	draw.Draw(exp,"all","all","ThetaCoplanar*180/3.14",2,xbins6,"fgd2reaccoh","accum_level[][1][0]>9 && fgd2reaccoh==3 "+reco_cut,"text"," NODRAW NOVARBIN NODATA  WCORR");
	histos[35] = draw.GetLastStackTotal();

	TCanvas *c3 = new TCanvas("c3","c3",900,600);
	TPad* pp3=new TPad("pp3","",0.0,0.0,1.0,1.0,0);
	SetStyle(pp3);
	const char *label[24]  = {"p_{#mu, 1}","p_{#mu, 2}","cos#theta_{#mu, 1}","cos#theta_{#mu, 2}","p_{#pi, 1}","p_{#pi, 2}","cos#theta_{#pi, 1}","cos#theta_{#pi, 2}","E_{#nu}^{reco, 1}","E_{#nu}^{reco, 2}","#theta_{#pi #mu, 1}","#theta_{#pi #mu, 2}","p_{#mu, 1}","p_{#mu, 2}","cos#theta_{#mu, 1}","cos#theta_{#mu, 2}","p_{#pi, 1}","p_{#pi, 2}","cos#theta_{#pi, 1}","cos#theta_{#pi, 2}","E_{#nu}^{reco, 1}","E_{#nu}^{reco, 2}","#theta_{#pi #mu, 1}","#theta_{#pi #mu, 2}"};
	TH1D * H_all = new TH1D("H_all","",24,0,24);
	TH1D * H_coh = new TH1D("H_coh","",24,0,24);
	TH1D * H_coh_O = new TH1D("H_coh_O","",24,0,24);
	for(int j=0;j<12;j++){
		for(int i=1;i<3;i++){
			H_all->GetXaxis()->SetBinLabel(j*2+i,label[j*2+i-1]);
			H_all->Fill(j*2+i-1,histos[j]->GetBinContent(i) );
			H_coh->Fill(j*2+i-1,histos[j+12]->GetBinContent(i) );
			H_coh_O->Fill(j*2+i-1,histos[j+24]->GetBinContent(i) );
		}
	}
	H_all->SetLineColor(kBlack);
	H_all->SetLineWidth(2);
	H_all->GetYaxis()->SetTitle("Events");
	H_all->GetYaxis()->SetRangeUser(0,80);
	H_all->GetXaxis()->LabelsOption("v");
	H_all->Draw("hist e0");
	H_coh->SetLineColor(kAzure+5);
	H_coh->SetLineWidth(2);
	H_coh->Draw("same");
	H_coh_O->SetLineColor(kOrange+7);
	H_coh_O->SetLineWidth(2);
	H_coh_O->Draw("same");
	TLegend *legg = new TLegend(0.2,0.85,0.8,0.9);
	legg->AddEntry(H_all,"Total","l");
	legg->AddEntry(H_coh,"Coherent total","l");
	legg->AddEntry(H_coh_O,"Coherent on Oxygen","l");
	legg->SetFillColor(kWhite);
	legg->SetMargin(0.25);
	legg->SetBorderSize(0);
	legg->SetNColumns(3);
	legg->Draw("same");
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
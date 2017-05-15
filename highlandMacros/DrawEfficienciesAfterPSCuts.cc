void DrawEfficienciesAfterPSCuts(){
	// Save the efficiencies graph after Phase Space cuts in a root file to compare
	// with before the phase space cut
	TFile *saveEffAfterCuts = new TFile("EffAfterCuts.root","RECREATE");

	bool useCohRW = false; // use the MC microTree where the coherent is reweighted from RS -> BS
	if (useCohRW) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/RW/";
	else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
	std::string pathToDataMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

	// Set up the experiment & drawingtools
	DrawingTools draw( pathToMCMicroTree+"MicroTree_MC_R3b.root" );
	Experiment exp = SetUpExpt(pathToMCMicroTree,pathToDataMicroTree);
	double POTRatio = draw.GetPOTRatio(exp);

	// phase space cut (on true variable !)
	std::string true_cut = "&& truelepton_mom>200 && truelepton_mom < 5000 && truelepton_costheta >0.75 && truelepton_costheta < 1 && truepi_mom>150 && truepi_mom <1500 && truepi_costheta >0.45 && truepi_costheta < 1 && trueEmupi > 500 && trueEmupi < 6500 && trueThetaCoplanar *180/3.14 > 90";

	TCanvas *c1 = new TCanvas("c1","FGD1",900,1000);

	TPad* p1=new TPad("p1","",0.0,0.67,0.5,1.0,0);
	SetStyle(p1);
	double xeffmu[27]={0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.2,1.4,1.6,1.8,2,2.2,2.4,2.6,2.8,3,3.25,3.5,3.75,4,4.5,5};
	draw.Draw(exp,"all","all","truelepton_mom/1000.",26,xeffmu,"all","accum_level[0][0]>9"+true_cut,"","NODATA NODRAW");
	TH1* h_evt1 = draw.GetLastStackTotal();
	float rightmax1 = h_evt1->GetMaximum();
	h_evt1->SetTitle("");
	h_evt1->GetXaxis()->SetTitle("True p_{#mu^{-}} [GeV]");
	DrawEvents(h_evt1, rightmax1);
	draw.DrawEff(exp,false,"truelepton_mom/1000.",26,xeffmu,"accum_level[0][0]>9","reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff1 = draw.GetLastGraph();
	TLegend *leg1 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truelepton_mom/1000.",24,xeffmu,"reaction==3","accum_level[0][0]>9","same z","","purity");
	//TGraph* gr_pur1 = draw.GetLastGraph();
	DrawRightAxis(rightmax1, gr_eff1);
	leg1->SetX1NDC(0.5);leg1->SetX2NDC(0.8);leg1->SetY1NDC(0.775);leg1->SetY2NDC(0.9);
	leg1->SetMargin(0.25);
	leg1->SetBorderSize(0);
	leg1->Draw();
    saveEffAfterCuts->cd();
    gr_eff1->Write("Cut_eff_mumom_fgd1");
	c1->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);
	double cosxmu[27]={0,0.2,0.3,0.4,0.45,0.5,0.55,0.6,0.625,0.65,0.675,0.7,0.72,0.74,0.76,0.78,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1};
	draw.Draw(exp,"all","all","truelepton_costheta",26,cosxmu,"all","accum_level[0][0]>9"+true_cut,"","NODATA NODRAW");
	TH1* h_evt2 = draw.GetLastStackTotal();
	float rightmax2 = h_evt2->GetMaximum();
	h_evt2->SetTitle("");
	h_evt2->GetXaxis()->SetTitle("True cos(#theta_{#mu^{-}})");
	DrawEvents(h_evt2, rightmax2);
	draw.DrawEff(exp,false,"truelepton_costheta",26,cosxmu,"accum_level[0][0]>9 ","reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff2 = draw.GetLastGraph();
	TLegend * leg2 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truelepton_costheta",26,cosxmu,"reaction==3","accum_level[0][0]>9","same z","","purity");
	//TGraph* gr_pur2 = draw.GetLastGraph();
	DrawRightAxis(rightmax2, gr_eff2);
	leg2->SetX1NDC(0.2);leg2->SetX2NDC(0.5);leg2->SetY1NDC(0.775);leg2->SetY2NDC(0.9);
	leg2->SetMargin(0.25);
	leg2->SetBorderSize(0);
	leg2->Draw();
	saveEffAfterCuts->cd();
	gr_eff2->Write("Cut_eff_mutheta_fgd1");
	c1->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	double xeffpi[27]={0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.75,2,2.25,2.5,3};
	draw.Draw(exp,"all","all","truepi_mom/1000.",26,xeffpi,"all","accum_level[0][0]>9"+true_cut,"","NODATA NODRAW");
	TH1* h_evt3 = draw.GetLastStackTotal();
	float rightmax3 = h_evt3->GetMaximum();
	h_evt3->SetTitle("");
	h_evt3->GetXaxis()->SetTitle("True p_{#pi^{+}} [GeV]");
	DrawEvents(h_evt3, rightmax3);
	draw.DrawEff(exp,false,"truepi_mom/1000.",26,xeffpi,"accum_level[0][0]>9","reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff3 = draw.GetLastGraph();
	TLegend * leg3 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truepi_mom/1000.",19,xeffpi,"reaction==3","accum_level[0][0]>9","same z","","purity");
	//TGraph* gr_pur3 = draw.GetLastGraph();
	DrawRightAxis(rightmax3, gr_eff3);
	leg3->SetX1NDC(0.5);leg3->SetX2NDC(0.8);leg3->SetY1NDC(0.775);leg3->SetY2NDC(0.9);
	leg3->SetMargin(0.25);
	leg3->SetBorderSize(0);
	leg3->Draw();
    saveEffAfterCuts->cd();
	gr_eff3->Write("Cut_eff_pimom_fgd1");
	c1->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	double cosxpi[27]={0,0.2,0.3,0.4,0.45,0.5,0.55,0.6,0.625,0.65,0.675,0.7,0.72,0.74,0.76,0.78,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1};
	draw.Draw(exp,"all","all","truepi_costheta.",26,cosxpi,"all","accum_level[0][0]>9"+true_cut,"","NODATA NODRAW");
	TH1* h_evt4 = draw.GetLastStackTotal();
	float rightmax4 = h_evt4->GetMaximum();
	h_evt4->SetTitle("");
	h_evt4->GetXaxis()->SetTitle("True cos(#theta_{#pi^{+}})");
	DrawEvents(h_evt4, rightmax4);
	draw.DrawEff(exp,false,"truepi_costheta",26,cosxpi,"accum_level[0][0]>9","reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff4 = draw.GetLastGraph();
	TLegend * leg4 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truepi_costheta",26,cosxpi,"reaction==3","accum_level[0][0]>9","same z","","purity");
	//TGraph* gr_pur4 = draw.GetLastGraph();
	DrawRightAxis(rightmax4, gr_eff4);
	leg4->SetX1NDC(0.2);leg4->SetX2NDC(0.5);leg4->SetY1NDC(0.775);leg4->SetY2NDC(0.9);
	leg4->SetMargin(0.25);
	leg4->SetBorderSize(0);
	leg4->Draw();
	saveEffAfterCuts->cd();
	gr_eff4->Write("Cut_eff_pitheta_fgd1");
	c1->cd();

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	double xbins5[33]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0,3.5,4.0,5.0,6.5};
	draw.Draw(exp,"all","all","trueEmupi/1000.",32,xbins5,"all","accum_level[0][0]>9 "+true_cut,"","NODATA NODRAW");
	TH1* h_evt5 = draw.GetLastStackTotal();
	h_evt5->Scale(1/POTRatio,"width");
	float rightmax5 = h_evt5->GetMaximum();
	h_evt5->SetTitle("");
	h_evt5->GetXaxis()->SetTitle("True E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	DrawEvents(h_evt5, rightmax5);
	draw.DrawEff(exp,false,"trueEmupi/1000.",32,xbins5,"accum_level[0][0]>9 ","reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff5 = draw.GetLastGraph();
	TLegend * leg5 = draw.GetLastLegend();
	//draw.DrawPur(exp,"trueEmupi/1000.",30,xbins5,"reaction==3","accum_level[0][0]>9 ","same z","","purity");
	//TGraph* gr_pur5 = draw.GetLastGraph();
	DrawRightAxis(rightmax5, gr_eff5);
	leg5->SetX1NDC(0.5);leg5->SetX2NDC(0.8);leg5->SetY1NDC(0.775);leg5->SetY2NDC(0.9);
	leg5->SetMargin(0.25);
	leg5->SetBorderSize(0);
	leg5->Draw();
	saveEffAfterCuts->cd();
	gr_eff5->Write("Cut_eff_Emupi_fgd1");
	c1->cd();

	TPad* p6=new TPad("p6","",0.5,0.0,1.0,0.32,0);
	SetStyle(p6);
	double xbins6[31]={0.0,15,30,40,50,60,70,80,90,100,110,120,125,130,135,140,145,147.5,150,152.5,155,157.5,160,162.5,165,167.5,170,172.5,175,177.5,180};
	draw.Draw(exp,"all","all","trueThetaCoplanar *180/3.14",30,xbins6,"all","accum_level[0][0]>9 "+true_cut,"","NODATA  NODRAW NOVARBIN");
	TH1* h_evt6 = draw.GetLastStackTotal();
	for(int i=0;i<30;i++){h_evt6->SetBinContent(i,h_evt6->GetBinContent(i)/(h_evt6->GetBinWidth(i)/h_evt6->GetBinWidth(30)));}
	float rightmax6 = h_evt6->GetMaximum();
	h_evt6->SetTitle("");
	h_evt6->GetXaxis()->SetTitle("True #theta_{#pi^{+}#mu^{-}} [deg]");
	DrawEvents(h_evt6, rightmax6);
	draw.DrawEff(exp,false,"trueThetaCoplanar *180/3.14",30,xbins6,"accum_level[0][0]>9 ","reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff6 = draw.GetLastGraph();
	TLegend * leg6 = draw.GetLastLegend();
	//draw.DrawPur(exp,"acos((truelepton_dir[1]*truepi_dir[][1] + truelepton_dir[0]*truepi_dir[][0]) / (sqrt(pow(truelepton_dir[0],2)+pow(truelepton_dir[1],2)) *sqrt(pow(truepi_dir[][0],2)+pow(truepi_dir[][1],2)))) *180/3.14",20,xbins5,"reaction==3","accum_level[0][0]>9 ","same z","","purity");
	//TGraph* gr_pur6 = draw.GetLastGraph();
	DrawRightAxis(rightmax6, gr_eff6);
	leg6->SetX1NDC(0.2);leg6->SetX2NDC(0.5);leg6->SetY1NDC(0.775);leg6->SetY2NDC(0.9);
	leg6->SetMargin(0.25);
	leg6->SetBorderSize(0);
	leg6->Draw();
	saveEffAfterCuts->cd();
	gr_eff6->Write("Cut_eff_theta_mupi_fgd1");
	c1->cd();

	TCanvas *c2 = new TCanvas("c2","FGD2",900,1000);
	TPad* p1=new TPad("p1","",0.0,0.67,0.5,1.0,0);
	SetStyle(p1);
	double xeffmu[27]={0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.2,1.4,1.6,1.8,2,2.2,2.4,2.6,2.8,3,3.25,3.5,3.75,4,4.5,5};
	draw.Draw(exp,"all","all","truelepton_mom/1000.",26,xeffmu,"all","accum_level[1][0]>9"+true_cut,"","NODATA NODRAW ");
	TH1* h_evt1 = draw.GetLastStackTotal();
	float rightmax1 = h_evt1->GetMaximum();
	h_evt1->SetTitle("");
	h_evt1->GetXaxis()->SetTitle("True p_{#mu^{-}} [GeV]");
	DrawEvents(h_evt1, rightmax1);
	draw.DrawEff(exp,false,"truelepton_mom/1000.",26,xeffmu,"accum_level[1][0]>9","fgd2reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff1 = draw.GetLastGraph();
	TLegend *leg1 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truelepton_mom/1000.",24,xeffmu,"fgd2reaction==3","accum_level[1][0]>9","same z","","purity");
	//TGraph* gr_pur1 = draw.GetLastGraph();
	DrawRightAxis(rightmax1, gr_eff1);
	leg1->SetX1NDC(0.5);leg1->SetX2NDC(0.8);leg1->SetY1NDC(0.775);leg1->SetY2NDC(0.9);
	leg1->SetMargin(0.25);
	leg1->SetBorderSize(0);
    saveEffAfterCuts->cd();
    gr_eff1->Write("Cut_eff_mumom_fgd2");
	c2->cd();

	TPad* p2=new TPad("p2","",0.5,0.67,1.0,1.0,0);
	SetStyle(p2);	
	double cosxmu[27]={0,0.2,0.3,0.4,0.45,0.5,0.55,0.6,0.625,0.65,0.675,0.7,0.72,0.74,0.76,0.78,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1};
	draw.Draw(exp,"all","all","truelepton_costheta",26,cosxmu,"all","accum_level[1][0]>9"+true_cut,"","NODATA NODRAW ");
	TH1* h_evt2 = draw.GetLastStackTotal();
	float rightmax2 = h_evt2->GetMaximum();
	h_evt2->SetTitle("");
	h_evt2->GetXaxis()->SetTitle("True cos(#theta_{#mu^{-}})");
	DrawEvents(h_evt2, rightmax2);
	draw.DrawEff(exp,false,"truelepton_costheta",26,cosxmu,"accum_level[1][0]>9 ","fgd2reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff2 = draw.GetLastGraph();
	TLegend * leg2 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truelepton_costheta",26,cosxmu,"fgd2reaction==3","accum_level[1][0]>9","same z","","purity");
	//TGraph* gr_pur2 = draw.GetLastGraph();
	DrawRightAxis(rightmax2, gr_eff2);
	leg2->SetX1NDC(0.2);leg2->SetX2NDC(0.5);leg2->SetY1NDC(0.775);leg2->SetY2NDC(0.9);
	leg2->SetMargin(0.25);
	leg2->SetBorderSize(0);
	leg2->Draw();
	saveEffAfterCuts->cd();
	gr_eff2->Write("Cut_eff_mutheta_fgd2");
	c2->cd();

	TPad* p3=new TPad("p3","",0.0,0.33,0.5,0.66,0);
	SetStyle(p3);
	double xeffpi[27]={0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.75,2,2.25,2.5,3};
	draw.Draw(exp,"all","all","truepi_mom/1000.",26,xeffpi,"all","accum_level[1][0]>9"+true_cut,"","NODATA NODRAW ");
	TH1* h_evt3 = draw.GetLastStackTotal();
	float rightmax3 = h_evt3->GetMaximum();
	h_evt3->SetTitle("");
	h_evt3->GetXaxis()->SetTitle("True p_{#pi^{+}} [GeV]");
	DrawEvents(h_evt3, rightmax3);
	draw.DrawEff(exp,false,"truepi_mom/1000.",26,xeffpi,"accum_level[1][0]>9","fgd2reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff3 = draw.GetLastGraph();
	TLegend * leg3 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truepi_mom/1000.",19,xeffpi,"fgd2reaction==3","accum_level[1][0]>9","same z","","purity");
	//TGraph* gr_pur3 = draw.GetLastGraph();
	DrawRightAxis(rightmax3, gr_eff3);
	leg3->SetX1NDC(0.5);leg3->SetX2NDC(0.8);leg3->SetY1NDC(0.775);leg3->SetY2NDC(0.9);
	leg3->SetMargin(0.25);
	leg3->SetBorderSize(0);
	leg3->Draw();
    saveEffAfterCuts->cd();
    gr_eff3->Write("Cut_eff_pimom_fgd2");
	c2->cd();

	TPad* p4=new TPad("p4","",0.5,0.33,1.0,0.66,0);
	SetStyle(p4);
	double cosxpi[27]={0,0.2,0.3,0.4,0.45,0.5,0.55,0.6,0.625,0.65,0.675,0.7,0.72,0.74,0.76,0.78,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1};
	draw.Draw(exp,"all","all","truepi_costheta.",26,cosxpi,"all","accum_level[1][0]>9"+true_cut,"","NODATA NODRAW ");
	TH1* h_evt4 = draw.GetLastStackTotal();
	float rightmax4 = h_evt4->GetMaximum();
	h_evt4->SetTitle("");
	h_evt4->GetXaxis()->SetTitle("True cos(#theta_{#pi^{+}})");
	DrawEvents(h_evt4, rightmax4);
	draw.DrawEff(exp,false,"truepi_costheta",26,cosxpi,"accum_level[1][0]>9","fgd2reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff4 = draw.GetLastGraph();
	TLegend * leg4 = draw.GetLastLegend();
	//draw.DrawPur(exp,"truepi_costheta",26,cosxpi,"fgd2reaction==3","accum_level[1][0]>9","same z","","purity");
	//TGraph* gr_pur4 = draw.GetLastGraph();
	DrawRightAxis(rightmax4, gr_eff4);
	leg4->SetX1NDC(0.2);leg4->SetX2NDC(0.5);leg4->SetY1NDC(0.775);leg4->SetY2NDC(0.9);
	leg4->SetMargin(0.25);
	leg4->SetBorderSize(0);
	leg4->Draw();
	saveEffAfterCuts->cd();
	gr_eff4->Write("Cut_eff_pitheta_fgd2");
	c2->cd();	

	TPad* p5=new TPad("p5","",0.0,0.0,0.5,0.32,0);
	SetStyle(p5);
	double xbins5[33]={0.0,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.2,1.4,1.6,1.8,2.0,2.25,2.5,2.75,3.0,3.5,4.0,5.0,6.5};
	draw.Draw(exp,"all","all","trueEmupi/1000.",32,xbins5,"all","accum_level[1][0]>9 "+true_cut,"","NODATA NODRAW NOVARBIN NOVARBIN");
	TH1* h_evt5 = draw.GetLastStackTotal();
	h_evt5->Scale(1/POTRatio,"width");
	float rightmax5 = h_evt5->GetMaximum();
	h_evt5->SetTitle("");
	h_evt5->GetXaxis()->SetTitle("True E_{#mu^{-}}+E_{#pi^{+}} [GeV]");
	DrawEvents(h_evt5, rightmax5);
	draw.DrawEff(exp,false,"trueEmupi/1000.",32,xbins5,"accum_level[1][0]>9 ","fgd2reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff5 = draw.GetLastGraph();
	TLegend * leg5 = draw.GetLastLegend();
	//draw.DrawPur(exp,"trueEmupi/1000.",30,xbins5,"reaction==3","accum_level[1][0]>9 ","same z","","purity");
	//TGraph* gr_pur5 = draw.GetLastGraph();
	DrawRightAxis(rightmax5, gr_eff5);
	leg5->SetX1NDC(0.5);leg5->SetX2NDC(0.8);leg5->SetY1NDC(0.775);leg5->SetY2NDC(0.9);
	leg5->SetMargin(0.25);
	leg5->SetBorderSize(0);
	leg5->Draw();
	saveEffAfterCuts->cd();
	gr_eff5->Write("Cut_eff_Emupi_fgd2");
	c2->cd();	

	TPad* p6=new TPad("p6","",0.5,0.0,1.0,0.32,0);
	SetStyle(p6);
	double xbins6[31]={0.0,15,30,40,50,60,70,80,90,100,110,120,125,130,135,140,145,147.5,150,152.5,155,157.5,160,162.5,165,167.5,170,172.5,175,177.5,180};
	draw.Draw(exp,"all","all","trueThetaCoplanar *180/3.14",30,xbins6,"all","accum_level[1][0]>9 "+true_cut,"","NODATA  NODRAW NOVARBIN");
	TH1* h_evt6 = draw.GetLastStackTotal();
	for(int i=0;i<30;i++){h_evt6->SetBinContent(i,h_evt6->GetBinContent(i)/(h_evt6->GetBinWidth(i)/h_evt6->GetBinWidth(30)));}
	float rightmax6 = h_evt6->GetMaximum();
	h_evt6->SetTitle("");
	h_evt6->GetXaxis()->SetTitle("True #theta_{#pi^{+}#mu^{-}} [deg]");
	DrawEvents(h_evt6, rightmax6);
	draw.DrawEff(exp,false,"trueThetaCoplanar *180/3.14",30,xbins6,"accum_level[1][0]>9 ","fgd2reaction==3"+true_cut,"same z","","efficiency");
	TGraph* gr_eff6 = draw.GetLastGraph();
	TLegend * leg6 = draw.GetLastLegend();
	//draw.DrawPur(exp,"acos((truelepton_dir[1]*truepi_dir[][1] + truelepton_dir[0]*truepi_dir[][0]) / (sqrt(pow(truelepton_dir[0],2)+pow(truelepton_dir[1],2)) *sqrt(pow(truepi_dir[][0],2)+pow(truepi_dir[][1],2)))) *180/3.14",20,xbins5,"reaction==3","accum_level[1][0]>9 ","same z","","purity");
	//TGraph* gr_pur6 = draw.GetLastGraph();
	DrawRightAxis(rightmax6, gr_eff6);
	leg6->SetX1NDC(0.2);leg6->SetX2NDC(0.5);leg6->SetY1NDC(0.775);leg6->SetY2NDC(0.9);
	leg6->SetMargin(0.25);
	leg6->SetBorderSize(0);
	leg6->Draw();
	saveEffAfterCuts->cd();
	gr_eff6->Write("Cut_eff_theta_mupi_fgd2");
	c2->cd();
	saveEffAfterCuts->Close();

/* Efficiency vs |t| , optional 
	TCanvas *c3 = new TCanvas("c3","Eff q2",1200,450);
	TPad* p1=new TPad("p1","",0.0,0.0,0.5,1.0,0);
	SetStyle(p1);
	double xefft[21]={0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.8,0.9,1.0,1.1,1.25,1.5};
	draw.Draw(exp,"all","all","TMath::Abs(TMath::Power(TMath::Sqrt(truelepton_mom*truelepton_mom+105.6*105.6) - truelepton_mom*truelepton_costheta + TMath::Sqrt(truepi_mom*truepi_mom+139.57*139.57) - truepi_mom*truepi_costheta,2) + TMath::Power(truelepton_mom*TMath::Sqrt(1-TMath::Power(truelepton_costheta,2)) + truepi_mom*TMath::Sqrt(1-TMath::Power(truepi_costheta,2)),2))/1000000",20,xefft,"all","accum_level[0][0]>9","","NODATA NODRAW NOVARBIN");
	TH1* h_evt1 = draw.GetLastStackTotal();
	h_evt1->SetTitle("");
	h_evt1->GetXaxis()->SetTitle("True |t|_{rec} [GeV^{2}]");
	float rightmax1;
	DrawEvents(h_evt1, &rightmax1);
	draw.DrawEff(exp,false,"TMath::Abs(TMath::Power(TMath::Sqrt(truelepton_mom*truelepton_mom+105.6*105.6) - truelepton_mom*truelepton_costheta + TMath::Sqrt(truepi_mom*truepi_mom+139.57*139.57) - truepi_mom*truepi_costheta,2) + TMath::Power(truelepton_mom*TMath::Sqrt(1-TMath::Power(truelepton_costheta,2)) + truepi_mom*TMath::Sqrt(1-TMath::Power(truepi_costheta,2)),2))/1000000",20,xefft,"accum_level[0][0]>9","reaction==3","same z","","efficiency");
	TGraph* gr_eff1 = draw.GetLastGraph();
	TLegend *leg1 = draw.GetLastLegend();
	draw.DrawPur(exp,"TMath::Abs(TMath::Power(TMath::Sqrt(truelepton_mom*truelepton_mom+105.6*105.6) - truelepton_mom*truelepton_costheta + TMath::Sqrt(truepi_mom*truepi_mom+139.57*139.57) - truepi_mom*truepi_costheta,2) + TMath::Power(truelepton_mom*TMath::Sqrt(1-TMath::Power(truelepton_costheta,2)) + truepi_mom*TMath::Sqrt(1-TMath::Power(truepi_costheta,2)),2))/1000000",20,xefft,"reaction==3","accum_level[0][0]>9","same z","","purity");
	TGraph* gr_pur1 = draw.GetLastGraph();
	DrawRightAxis(&rightmax1, gr_eff1, gr_pur1);
	leg1->SetX1NDC(0.3);leg1->SetX2NDC(0.6);leg1->SetY1NDC(0.775);leg1->SetY2NDC(0.9);
	leg1->SetMargin(0.25);
	leg1->SetBorderSize(0);
	c3->cd();

	TPad* p2=new TPad("p2","",0.5,0.0,1.0,1.0,0);
	SetStyle(p2);
	double xefft[21]={0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.8,0.9,1.0,1.1,1.25,1.5};
	draw.Draw(exp,"all","all","TMath::Abs(TMath::Power(TMath::Sqrt(truelepton_mom*truelepton_mom+105.6*105.6) - truelepton_mom*truelepton_costheta + TMath::Sqrt(truepi_mom*truepi_mom+139.57*139.57) - truepi_mom*truepi_costheta,2) + TMath::Power(truelepton_mom*TMath::Sqrt(1-TMath::Power(truelepton_costheta,2)) + truepi_mom*TMath::Sqrt(1-TMath::Power(truepi_costheta,2)),2))/1000000",20,xefft,"all","accum_level[1][0]>9","","NODATA NODRAW NOVARBIN");
	TH1* h_evt2 = draw.GetLastStackTotal();
	h_evt2->SetTitle("");
	h_evt2->GetXaxis()->SetTitle("True |t|_{rec} [GeV^{2}]");
	float rightmax2;
	DrawEvents(h_evt2, &rightmax2);
	draw.DrawEff(exp,false,"TMath::Abs(TMath::Power(TMath::Sqrt(truelepton_mom*truelepton_mom+105.6*105.6) - truelepton_mom*truelepton_costheta + TMath::Sqrt(truepi_mom*truepi_mom+139.57*139.57) - truepi_mom*truepi_costheta,2) + TMath::Power(truelepton_mom*TMath::Sqrt(1-TMath::Power(truelepton_costheta,2)) + truepi_mom*TMath::Sqrt(1-TMath::Power(truepi_costheta,2)),2))/1000000",20,xefft,"accum_level[0][1]>9","fgd2reaction==3","same z","","efficiency");
	TGraph* gr_eff2 = draw.GetLastGraph();
	TLegend *leg2 = draw.GetLastLegend();
	draw.DrawPur(exp,"TMath::Abs(TMath::Power(TMath::Sqrt(truelepton_mom*truelepton_mom+105.6*105.6) - truelepton_mom*truelepton_costheta + TMath::Sqrt(truepi_mom*truepi_mom+139.57*139.57) - truepi_mom*truepi_costheta,2) + TMath::Power(truelepton_mom*TMath::Sqrt(1-TMath::Power(truelepton_costheta,2)) + truepi_mom*TMath::Sqrt(1-TMath::Power(truepi_costheta,2)),2))/1000000",20,xefft,"fgd2reaction==3","accum_level[1][0]>9","same z","","purity");
	TGraph* gr_pur2 = draw.GetLastGraph();
	DrawRightAxis(&rightmax2, gr_eff2, gr_pur2);
	leg2->SetX1NDC(0.3);leg2->SetX2NDC(0.6);leg2->SetY1NDC(0.775);leg2->SetY2NDC(0.9);
	leg2->SetMargin(0.25);
	leg2->SetBorderSize(0);
*/
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
	exp.SetCurrentTree("truth"); 
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
  	p->SetLeftMargin(0.1);
  	p->SetRightMargin(0.15);
  	p->SetTopMargin(0.05);
  	p->SetTickx();
  	p->Draw();
	p->cd();
}

// Draw the event number in dashed blue
void DrawEvents(TH1* h_evt,float rightmax){
	//rightmax = 1.1*h_evt->GetMaximum();
    Float_t scale = gPad->GetUymax()/(1.1*rightmax);
    h_evt->Scale(scale);
    h_evt->SetLineColor(kAzure+5);
    h_evt->SetFillColor(kAzure+5);
    h_evt->SetFillStyle(3002);
    h_evt->GetYaxis()->SetRangeUser(0,1);
	h_evt->GetYaxis()->SetNdivisions(510);
	h_evt->Draw("hist");
}

// Draw the right axis for the event nbr and set the style for
// efficiency and purity
void DrawRightAxis(float rightmax, TGraph* gr_eff){
	gr_eff->SetLineColor(kBlack);
	gr_eff->GetYaxis()->SetRangeUser(0,1);
	gr_eff->SetMarkerStyle(20);
	gr_eff->SetMarkerColor(kBlack);
	//gr_pur->SetLineColor(kGray+1);
	//gr_pur->GetYaxis()->SetRangeUser(0,1);
	//gr_pur->SetMarkerStyle(1);
	//gr_pur->SetMarkerColor(kBlack);
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(), gPad->GetUymax(),0,1.1*rightmax,510,"+L");
	axis->SetTitle("Events");
    axis->SetLineColor(kAzure+5);
    axis->SetTextColor(kAzure+5);
    axis->SetLabelColor(kAzure+5);
    axis->SetLabelFont(42);
	axis->SetTitleFont(62);
	axis->SetLabelSize(0.05);
	axis->SetTitleSize(0.06);
	axis->SetTitleOffset(0.9);
    axis->Draw();
}
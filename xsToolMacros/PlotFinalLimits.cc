void PlotFinalLimits(){
	int rebin_param = 2; // Rebin NEUT plots to get it smooth
	TFile *f_BS = new TFile("GeneratorFiles/1M_BS_ND280.root","READ");
	TFile *f_RS = new TFile("GeneratorFiles/1M_RS_ND280.root","READ");

	// Just to make sure the axis titles are set correctly on every plots
  	// p_{#mu^{-}} , cos#theta_{#mu^{-}}, p_{#pi^{+}} , cos#theta_{#pi^{+}}, (E_{#pi^{+}}+E_{#mu^{-}}), #theta_{#pi^{+}#mu^{-}}
  	const char* variable = "#theta_{#pi^{+}#mu^{-}}";
  	TCanvas * can_pmu = new TCanvas("can_pmu","can_pmu",650,500);
  	TPad * pad_pmu = new TPad("pad_pmu","pad_pmu",0,0,1,1);
	PlotVar(f_BS,f_RS,variable,rebin_param,pad_pmu);
	
}

void PlotVar(TFile *f_BS, TFile *f_RS, const char* var,int rebin_param,TPad* p){
	std::string var_unit, unit,th1f_neut;
	double y_throw[2];
	double y_bayes[2];
	double x[2];
	double x_err[2];
	bool left_legend = false;
	 switch (var){
        case "p_{#mu^{-}}":
			y_throw[0]=11.3;y_throw[1]=1.07;
			y_bayes[0]=8.58;y_bayes[1]=0.75;
			x[0]=0.45;		x[1]=2.85;
			x_err[0]=0.25;	x_err[1]=2.15;
			var_unit = "/GeV";
			unit="[GeV]";
			th1f_neut="NEUT_pmu_XS";
            break;
        case "cos#theta_{#mu^{-}}":
			y_throw[0]=23.9;y_throw[1]=88.8;
			y_bayes[0]=18.4;y_bayes[1]=59.7;
			x[0]=0.825;		x[1]=0.975;
			x_err[0]=0.125;	x_err[1]=0.025;
			var_unit = "";
			unit="";
			th1f_neut="NEUT_cosanglemu_XS";
			left_legend=true;
            break;
        case "p_{#pi^{+}}":
			y_throw[0]=23.6;y_throw[1]=4.77;
			y_bayes[0]=13.9;y_bayes[1]=3.71;
			x[0]=0.275;		x[1]=0.95;
			x_err[0]=0.125;	x_err[1]=0.55;
			var_unit = "/GeV";
			unit="[GeV]";
			th1f_neut="NEUT_ppi_XS";
            break;
        case "cos#theta_{#pi^{+}}":
			y_throw[0]=11.6;y_throw[1]=52.8;
			y_bayes[0]=7.89;y_bayes[1]=40.8;
			x[0]=0.675;		x[1]=0.95;
			x_err[0]=0.225;	x_err[1]=0.05;
			var_unit = "";
			unit="";
			th1f_neut="NEUT_cosanglepi_XS";
			left_legend=true;
            break;
        case "(E_{#pi^{+}}+E_{#mu^{-}})":
			y_throw[0]=11.3;y_throw[1]=1.07;
			y_bayes[0]=8.58;y_bayes[1]=0.75;
			x[0]=0.875;		x[1]=3.875;
			x_err[0]=0.375;	x_err[1]=2.625;
			var_unit = "/GeV";
			unit="[GeV]";
			th1f_neut="NEUT_emupi_XS";
            break;
        case "#theta_{#pi^{+}#mu^{-}}":
			y_throw[0]=7.70;y_throw[1]=20;
			y_bayes[0]=5.30;y_bayes[1]=16;
			x[0]=122.5;		x[1]=167.5;
			x_err[0]=32.5;	x_err[1]=12.5;
			var_unit = "/deg";
			unit="[deg]";
			th1f_neut="NEUT_copla_XS";
			left_legend=true;
            break;
        }
		SetStyle(p);

	std::string title = ";"+std::string(var)+" "+unit+";#frac{d#sigma}{d" + std::string(var) + "} [x10^{-40}cm^{2}" + var_unit + "/^{16}O]";	
	// Get NEUT plots from files in GeneratorFiles
	TH1F * f_bs_pmu = (TH1F*)f_BS->Get(th1f_neut.c_str());
	f_bs_pmu->RebinX(rebin_param,"f_bs_pmu_binned");
	f_bs_pmu_binned->Scale(100.0/rebin_param); // scale to nbr evts generated and adjust units | for thetamupi, times by 100 !
	f_bs_pmu_binned->SetLineColor(kRed+1);
	f_bs_pmu_binned->SetLineWidth(1);

	TH1F * f_rs_pmu = (TH1F*)f_RS->Get(th1f_neut.c_str());
	f_rs_pmu->RebinX(rebin_param,"f_rs_pmu_binned");
	f_rs_pmu_binned->Scale(100.0/rebin_param); // scale to nbr evts generated and adjust units | for thetamupi, times by 100 !
	f_rs_pmu_binned->SetLineColor(kRed+1);
	f_rs_pmu_binned->SetLineWidth(1);
	f_rs_pmu_binned->SetLineStyle(2);

	// Plot the limit graphs
	TGraphErrors *gr_pmu_throw = new TGraphErrors(2,x,y_throw,x_err);
	gr_pmu_throw->SetLineWidth(2);
	gr_pmu_throw->SetLineColor(kBlack);
	gr_pmu_throw->SetTitle(title.c_str());
	gr_pmu_throw->GetXaxis()->SetRangeUser(x[0]-x_err[0],x[1]+x_err[1]);
	gr_pmu_throw->GetYaxis()->SetRangeUser(0,1.2*f_rs_pmu_binned->GetMaximum());
	gr_pmu_throw->Draw("a p z ");

	TGraphErrors *gr_pmu_bayes = new TGraphErrors(2,x,y_bayes,x_err);
	gr_pmu_bayes->SetLineWidth(2);
	gr_pmu_bayes->SetLineStyle(2);
	gr_pmu_bayes->SetLineColor(kBlack);
	gr_pmu_bayes->Draw("p z same ");

	f_rs_pmu_binned->Draw("c same");
	f_bs_pmu_binned->Draw("c same");

	PlotArrows(x,y_bayes,y_throw);

 	if(left_legend) TLegend *leg = new TLegend(0.2,0.55,0.6,0.8);
 	else TLegend *leg = new TLegend(0.5,0.55,0.9,0.8);
    leg->AddEntry(f_rs_pmu_binned,"Rein-Sehgal (NEUT v5.3.4)","l");
    leg->AddEntry(f_bs_pmu_binned,"Berger-Sehgal (NEUT v5.3.4)","l");
    leg->AddEntry(gr_pmu_throw,"95% C.L. Upper Limit (Throw)","l");
    leg->AddEntry(gr_pmu_bayes,"95% C.L. Upper Limit (Bayes)","l");
    leg->SetFillColor(kWhite);
    leg->SetBorderSize(0);
    leg->SetMargin(0.25);
    leg->Draw("same");

 	if(left_legend) TPaveText * pt = new TPaveText(0.2,0.8,0.45,0.85,"brNDC");
 	else TPaveText * pt = new TPaveText(0.5,0.8,0.75,0.85,"brNDC");
 	pt->SetTextFont(72);
 	pt->SetFillColor(kWhite);
 	pt->SetBorderSize(0);
 	pt->AddText("T2K Preliminary");
 	pt->Draw();

	p->Update();
}

void PlotArrows(double *x, double *y_bayes, double *y_throw){
	TArrow* arr_bayes_1 = new TArrow(x[0],y_bayes[0],x[0],0.85*y_bayes[0],0.0075,"|>");
	arr_bayes_1->SetLineColor(kBlack);
	arr_bayes_1->SetLineStyle(2);
	arr_bayes_1->SetFillStyle(1001);
   	arr_bayes_1->SetFillColor(kBlack);
	arr_bayes_1->Draw();

	TArrow* arr_throw_1 = new TArrow(x[0],y_throw[0],x[0],0.85*y_throw[0],0.0075,"|>");
	arr_throw_1->SetLineColor(kBlack);
	arr_throw_1->SetFillStyle(1001);
	arr_throw_1->SetFillColor(kBlack);
	arr_throw_1->Draw();

	TArrow* arr_bayes_2 = new TArrow(x[1],y_bayes[1],x[1],0.85*y_bayes[1],0.01,"|>");
	arr_bayes_2->SetLineColor(kBlack);
	arr_bayes_2->SetLineStyle(2);
	arr_bayes_2->SetFillStyle(1001);
   	arr_bayes_2->SetFillColor(kBlack);
	arr_bayes_2->Draw();

	TArrow* arr_throw_2 = new TArrow(x[1],y_throw[1],x[1],0.85*y_throw[1],0.01,"|>");
	arr_throw_2->SetLineColor(kBlack);
	arr_throw_2->SetFillStyle(1001);
	arr_throw_2->SetFillColor(kBlack);
	arr_throw_2->Draw();
	
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
	gStyle->SetTitleOffset(1.25,"Y");
	gStyle->SetOptStat(0);

	p->SetBottomMargin(0.15);
  	p->SetLeftMargin(0.15);
  	p->SetRightMargin(0.05);
  	p->SetTopMargin(0.1);
  	p->SetTickx();
  	p->SetTicky();
  	p->Draw();
	p->cd();
}
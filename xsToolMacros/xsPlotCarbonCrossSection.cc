void xsPlotCarbonCrossSection(){
    // Get the Results Files obtained by xsMakeResultFiles.cc, change the name for another variable:
  // Mumom, Mutheta, Pimom, Pitheta, Emupi, Thetamupi
	TFile *f_grouped = new TFile("/data/pmartins/T2K/work/CCCoherent/xsToolMacros/xsFilesData/xsResults_Thetamupi_FGD1Grouped.root","READ");

  // Just to make sure the axis titles are set correctly on every plots
  // p_{#mu^{-}} , cos#theta_{#mu^{-}}, p_{#pi^{+}} , cos#theta_{#pi^{+}}, (E_{#pi^{+}}+E_{#mu^{-}}), #theta_{#pi^{+}#mu^{-}}
  const char* variable = "#theta_{#pi^{+}#mu^{-}}";

  DrawDifferential(f_grouped, variable);

  DrawCovariance(f_grouped, variable);
}

void DrawDifferential(TFile *file, const char* var){
  // Build the drawingTool
  xsDrawingTools *draw = new xsDrawingTools(file->GetName());
  xsErrorGroups::type group = xsErrorGroups::ALL;

  // Print out the total flux-integrated xsec
  double totalXS = draw->GetTotalXsec();
  double totalXStruth = draw->GetTruthTotalXsec();

  // calculate error on total cross section for each error source
  vector<double> totalErrorPerSource;
  double staterr = 0;
  double systerr = 0;
  // obtain list of error sources
  draw->SelectErrorSources(group);
  vector<string> sources = draw->GetSelectedErrorSources();
  int nsources = sources.size();
  for(int i=0; i<nsources; i++) {
    double err = draw->GetTotalXsecError(sources[i]);
    totalErrorPerSource.push_back(err);
    if(sources[i].substr(0,strlen("statistics_")) == "statistics_") {
      staterr += pow(err,2);
    }
    else {
      systerr += pow(err,2);
    }
  }
  staterr = sqrt(staterr);
  systerr = sqrt(systerr);

  cout << "************************************************************************" << endl;
  cout << "Total xsec = " << totalXS*100 << " +- " << staterr*100 << "(" << staterr/totalXS*100 << "% stat) +- " << systerr*100 << "(" << systerr/totalXS*100 << "% syst) x 10^-40 cm^2 / C12" << endl;
  cout << "Total xsec from truth = " << totalXStruth*100 << " x 10^-40 cm^2 / C12" << endl;

  // print error on total cross section for each error source
  for(int i=0; i<nsources; i++) {
    cout << sources[i] << setw(10) << "\t abs: " << totalErrorPerSource[i]*100 << setw(10) << "\t rel: " << totalErrorPerSource[i]/totalXS*100. << "%" << endl;
  }
  cout << "************************************************************************" << endl;

  // Canvas, draw unfolded differential cross section results
  TCanvas *can1 = new TCanvas("can1","can1",600,500);
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  SetStyle(p1,false);

  // Get the titles right, to know what is plotted
  std::string var_unit,unit;
  bool left_legend;
  if(var == "cos#theta_{#pi^{+}}" || var == "cos#theta_{#mu^{-}}" ) {var_unit = ""; unit = "";left_legend=true;}
  if(var == "p_{#pi^{+}}" || var == "p_{#mu^{-}}" || var == "(E_{#pi^{+}}+E_{#mu^{-}})"  ) {var_unit = "/GeV";unit = "[GeV]";left_legend=false;}
  if(var == "#theta_{#pi^{+}#mu^{-}}") {var_unit = "/deg";unit = "[deg]";left_legend=true;}
  
  std::string titleY, titleX;
  titleY="#frac{d#sigma}{d" + std::string(var) + "} [x10^{-40}cm^{2}" + var_unit + "/^{12}C]";

  // Get results with total error and set the axis titles
  TH1 *hresult_err = draw->GetResultWithErrors(sources);
  TH1 *hresult_err_binned = draw->GetBinning()->convertTH1(hresult_err);
  hresult_err_binned->SetTitle((" ;"+ std::string(var) + unit +";"+titleY).c_str());

  // Get results with stat error only
  vector<string> statonly = xsErrorsUtils::GetGroupErrorList(sources,xsErrorGroups::STATONLY);
  TH1 *hresult_stat = draw->GetResultWithErrors(statonly);
  TH1 *hresult_stat_binned = draw->GetBinning()->convertTH1(hresult_stat);

  // Get results with syst error only
  vector<string> systonly = xsErrorsUtils::GetGroupErrorList(sources,xsErrorGroups::NOSTAT);
  TH1 *hresult_syst = draw->GetResultWithErrors(systonly);
  TH1 *hresult_syst_binned = draw->GetBinning()->convertTH1(hresult_syst);

  // Get MC truth result
  TH1 *hmctruth = draw->GetTruthResult();
  TH1 *hmctruth_binned = draw->GetBinning()->convertTH1(hmctruth);

  PlotResults(hresult_err_binned, hresult_stat_binned,hmctruth_binned, left_legend);

  PlotTables(hresult_err_binned,hresult_stat_binned,hresult_syst_binned);
}

void PlotResults(TH1* h_total, TH1* h_stat, TH1* h_mc, bool left_legend){

  h_total->Scale(100); // Just changing the unit
  h_total->GetYaxis()->SetRangeUser(0,1.75*h_total->GetMaximum());
  h_total->SetLineColor(kBlack);
  h_total->SetMarkerStyle(kFullCircle);
  h_total->Draw("E1");

  h_stat->Scale(100); // Just change the unit
  h_stat->SetLineColor(kBlack);
  h_stat->SetMarkerStyle(kFullCircle);
  //h_stat->SetLineWidth(2);  
  h_stat->Draw("same E1");

  h_mc->Scale(100); // Just change the unit
  h_mc->SetLineColor(kRed+1);
  h_mc->SetLineWidth(2);
  h_mc->Draw("hist same");

  // draw legend
  if(left_legend) TLegend *leg = new TLegend(0.25,0.65,0.7,0.8); 
  else TLegend *leg = new TLegend(0.45,0.65,0.9,0.8); 
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg1 = new TLegend(*leg);
  //leg1->AddEntry(h_total,"T2K data (stat + syst)","l p");
  leg1->AddEntry(h_stat,"T2K data ","l p");
  leg1->AddEntry(h_mc,"NEUT (Berger-sehgal)","l");
  leg1->Draw();

  if(left_legend) TPaveText * pt = new TPaveText(0.25,0.83,0.55,0.9,"brNDC");
  else TPaveText * pt = new TPaveText(0.45,0.83,0.75,0.9,"brNDC");
  pt->SetTextFont(72);
  pt->SetFillColor(kWhite);
  pt->SetBorderSize(0);
  pt->AddText("T2K Preliminary");
  pt->Draw();
  
}

void PlotTables(TH1* h_total, TH1* h_stat, TH1* h_syst ){
  h_syst->Scale(100); // Like all the other, change the unit
  cout << "Results for each bin:" << endl;
  for(int i=1;i<=h_total->GetNbinsX();i++){
      cout <<i<<"| bin edges: "<< h_total->GetBinLowEdge(i)<<"->"<< h_total->GetBinLowEdge(i)+h_total->GetBinWidth(i)<< setw(20) << "\t | bin value = "<<h_total->GetBinContent(i) << setw(7) 
      << "\t stat: " << h_stat->GetBinError(i) <<" ("<<100*h_stat->GetBinError(i)/h_total->GetBinContent(i) <<" %) "<< setw(4)  
      << "\t syst: " << h_syst->GetBinError(i) <<" ("<<100*h_syst->GetBinError(i)/h_total->GetBinContent(i) <<" %) "<< setw(4)  
      << "\t stat+syst: " << h_total->GetBinError(i) << " ("<< 100*h_total->GetBinError(i)/h_total->GetBinContent(i) << " %)" << endl;
  }
  cout << "************************************************************************" << endl;
}

void DrawCovariance(TFile *file, const char* var){
  TCanvas *cancov = new TCanvas("cancov","cancov",600,500);
  TPad * p = new TPad("p","p",0,0,1,1);
  SetStyle(p,true);
  // Build the drawingTool
  xsDrawingTools *draw = new xsDrawingTools(file->GetName());
  //xsErrorGroups::type group = xsErrorGroups::ALL;
  // obtain list of error sources
  //draw->SelectErrorSources(group);
  vector<string> sources = draw->GetSelectedErrorSources();
  TMatrixD *cvm = draw->GetFractionalCovariance(sources);
  //TMatrixD *cvm = draw->GetCovariance(sources);
  TH2D *hcvm = new TH2D(*cvm);
  double m = TMath::Max(hcvm->GetMaximum(),-hcvm->GetMinimum());
  hcvm->GetZaxis()->SetRangeUser(-m,m);
  hcvm->SetTitle("");
  hcvm->SetContour(50);
  hcvm->GetXaxis()->SetRangeUser(1,3);
  hcvm->GetYaxis()->SetRangeUser(1,3);
  hcvm->GetXaxis()->SetNdivisions(202);
  hcvm->GetYaxis()->SetNdivisions(202);
  hcvm->GetXaxis()->CenterLabels();
  hcvm->GetYaxis()->CenterLabels();
  hcvm->GetXaxis()->SetTitle((std::string(var)+" bin number").c_str());
  hcvm->GetYaxis()->SetTitle((std::string(var)+" bin number").c_str());
  hcvm->SetMarkerSize(2.5);
  hcvm->Draw("COL Z TEXT");

}

// PLot with style !
void SetStyle(TPad * p, bool IsCovariance){
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
  gStyle->SetTitleOffset(1.25,"X");
  gStyle->SetLabelFont(42,"Y");
  gStyle->SetLabelSize(0.05,"Y");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetTitleSize(0.05,"Y");
  if (IsCovariance) 
    gStyle->SetTitleOffset(1.25,"Y");
  else 
    gStyle->SetTitleOffset(1.5,"Y");
  gStyle->SetOptStat(0);
  gStyle->SetNdivisions(510,"X");
  gStyle->SetNdivisions(510,"Y");
  gStyle->SetOptFit(1);
  gStyle->SetEndErrorSize(3);

  p->SetBottomMargin(0.15);
  if(IsCovariance) 
    p->SetLeftMargin(0.15);
  else 
    p->SetLeftMargin(0.2);
  if (IsCovariance) 
    p->SetRightMargin(0.15);
  else
  p->SetRightMargin(0.05);
  p->SetTopMargin(0.05);
  p->SetTickx();
  p->SetTicky();
  p->Draw();
  p->cd();
}
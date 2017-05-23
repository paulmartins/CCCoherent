void xsPlotLimit(){
  // Just the nbr of bins, to check the binning is correct and the fits are good enough.
  // Need to be adjusted for each variable/bin
  const int nbins_throw = 1000; 
  
  // Get the Results Files obtained by xsMakeResultFiles.cc, change the name for another variable:
  // Mumom, Mutheta, Pimom, Pitheta, Emupi, Thetamupi
	TFile *f_grouped = new TFile("/data/pmartins/T2K/work/CCCoherent/xsToolMacros/xsFilesData/xsResults_Mutheta_SubGrouped.root","READ");
  TFile *f_allcorr = new TFile("/data/pmartins/T2K/work/CCCoherent/xsToolMacros/xsFilesData/xsResults_Mutheta_SubAll.root","READ");

  // Just to make sure the axis titles are set correctly on every plots
  // p_{#mu^{-}} , cos#theta_{#mu^{-}}, p_{#pi^{+}} , cos#theta_{#pi^{+}}, (E_{#pi^{+}}+E_{#mu^{-}}), #theta_{#pi^{+}#mu^{-}}
  const char* variable = "cos#theta_{#pi^{+}}";

  // Choose what to plot between the first and second bin, or the integrated xs, easyyyyyyy
  // std::string DiffOrIntegrated = "throw_bin[1]";
  // std::string DiffOrIntegrated = "throw_bin[2]";
   std::string DiffOrIntegrated = "throw_total";

  // Plot the throw together with their fits (fit using gausskew to get assymetric errors)
  // And save the fit results in a vector of TF1 FitResults
  TF1 **FitResults = new TF1*[7];  
  PlotThrowAndFit(f_grouped,f_allcorr,nbins_throw,DiffOrIntegrated,variable,FitResults);

  // Normalise and re-plot the previous fits against each others, plus add the total Flux+FSI+XS with full correlations
  // Sum all the throws and integrate to get the limit
  PlotFitsAndGetLimit(FitResults,nbins_throw,DiffOrIntegrated,variable);
}

void PlotFitsAndGetLimit(TF1** FitResults, int nbins, std::string DiffOrIntegrated,const char* var){
  TCanvas *c3 = new TCanvas("c3","c3",600,500);
  //TPad *p2 = new TPad("p2","p2",0,0,0.49,1);
  //SetStyle(p2); 

  // Get the titles right, to know what is plotted
  std::string var_unit;
  if(var == "cos#theta_{#pi^{+}}" || var == "cos#theta_{#mu^{-}}" ) var_unit = "";
  if(var == "p_{#pi^{+}}" || var == "p_{#mu^{-}}" || var == "(E_{#pi^{+}}+E_{#mu^{-}})"  ) var_unit = "/GeV";
  if(var == "#theta_{#pi^{+}#mu^{-}}") var_unit = "/deg";
  
  std::string titleX;
  if(DiffOrIntegrated == "throw_bin[1]") titleX="#frac{d#sigma}{d" + std::string(var) + "} [x10^{-38}cm^{2}" + var_unit + "/^{16}O] (1^{st}bin)";
  if(DiffOrIntegrated == "throw_bin[2]") titleX="#frac{d#sigma}{d" + std::string(var) + "} [x10^{-38}cm^{2}" + var_unit + "/^{16}O] (2^{nd}bin)";
  if(DiffOrIntegrated == "throw_total")  titleX="#sigma [x10^{-38}cm^{2}/^{16}O] (with "+std::string(var)+")";
  /*
  // Normalise the throw fits
  // Acutally build histo based on the fits and then scale by the intagral of the fit
  // The integral is from 0 to 5 sigmas, sometimes integral fails, then reduce the range
  TH1F* hf_data=new TH1F("hf_data","Stats data",100*nbins,0,1);
  hf_data->Add(FitResults[0],1/FitResults[0]->Integral(0,FitResults[0]->GetParameter(1)+5*FitResults[0]->GetParameter(3))); 
  hf_data->SetLineColor(kAzure+5); hf_data->SetLineWidth(2);
  hf_data->SetTitle((" ;"+titleX+";Throws").c_str());
  hf_data->GetXaxis()->SetRangeUser(0,FitResults[0]->GetParameter(1)+4*FitResults[0]->GetParameter(3));
  hf_data->GetYaxis()->SetRangeUser(0,20*hf_data->GetMaximum());
  hf_data->Draw();

  TH1F* hf_mc=new TH1F("hf_mc","Stats mc",100*nbins,0,1);
  hf_mc->Add(FitResults[1],1/FitResults[1]->Integral(0,FitResults[1]->GetParameter(1)+5*FitResults[1]->GetParameter(3)));
  hf_mc->SetLineColor(kOrange); hf_mc->SetLineWidth(2);
  hf_mc->Draw("lc same");

  TH1F* hf_det=new TH1F("hf_det","Detector",100*nbins,0,1);
  hf_det->Add(FitResults[2],1/FitResults[2]->Integral(0,FitResults[2]->GetParameter(1)+5*FitResults[2]->GetParameter(3)));
  hf_det->SetLineColor(kRed+1); hf_det->SetLineWidth(2);
  hf_det->Draw("lc same");

  TH1F* hf_flux_fsi_xs=new TH1F("hf_flux_fsi_xs","Flux+FSI+Model",100*nbins,0,1);
  hf_flux_fsi_xs->Add(FitResults[6],1/FitResults[6]->Integral(0,FitResults[6]->GetParameter(1)+5*FitResults[6]->GetParameter(3)));
  hf_flux_fsi_xs->SetLineColor(kSpring+5); hf_flux_fsi_xs->SetLineWidth(2);
  hf_flux_fsi_xs->Draw("lc same");
*/
  // Get the average mean
  double AvgMean = (FitResults[0]->GetParameter(1) + FitResults[1]->GetParameter(1) +FitResults[2]->GetParameter(1) + FitResults[6]->GetParameter(1))/4;
  // Get the quadrature sum of the sigmas
  double SumSig1 = sqrt(pow(FitResults[0]->GetParameter(2),2) + pow(FitResults[1]->GetParameter(2),2) + pow(FitResults[2]->GetParameter(2),2) + pow(FitResults[6]->GetParameter(2),2));
  double SumSig2 = sqrt(pow(FitResults[0]->GetParameter(3),2) + pow(FitResults[1]->GetParameter(3),2) + pow(FitResults[2]->GetParameter(3),2) + pow(FitResults[6]->GetParameter(3),2));
  // Get the normalisation right
  double Norm = 1/(2*sqrt(2*3.14)*(SumSig1+SumSig2));

  TF1 *f_total = new TF1("f_total",gausskew,0,5,4); f_total->SetNpx(15000); 
  f_total->FixParameter(0,Norm);
  f_total->FixParameter(1,AvgMean);
  f_total->FixParameter(2,SumSig1);
  f_total->FixParameter(3,SumSig2);
  f_total->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");

  TH1F* h_sum_norm=new TH1F("h_sum_norm","Total",100*nbins,0,1);
  h_sum_norm->Add(f_total);
  
  //h_sum->Add(hf_mc);
  //h_sum->Add(hf_det);
  //h_sum->Add(hf_flux_fsi_xs);
  h_sum_norm->SetLineColor(kBlack); h_sum_norm->SetLineWidth(2);
  h_sum_norm->GetXaxis()->SetRangeUser(0,f_total->GetParameter(1)+4*f_total->GetParameter(3));
  //h_sum->Draw("lc same");
  //h_sum_norm->Draw();

  /*
  TLegend *leg = new TLegend(0.55,0.55,0.925,0.875);
  leg->AddEntry(hf_data,"Data stats","l");
  leg->AddEntry(hf_mc,"MC stats","l");
  leg->AddEntry(hf_det,"Detector","l");
  leg->AddEntry(hf_flux_fsi_xs,"Flux + FSI + Model","l");
  leg->AddEntry(h_sum,"Total","l");
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->SetMargin(0.3);
  leg->Draw();
  */
  c3->cd();
  TPad *p3 = new TPad("p3","p3",0,0,1,1);
  SetStyle(p3);

  // Normalise the total (divide by 4 as we added 4 histos that were already normalised)
  //TH1F* h_sum_norm = (TH1F*)h_sum->Clone("h_sum_norm");
  //h_sum_norm->Scale(0.25);

  // Calculate limit 
  h_sum_norm->Scale(1/h_sum_norm->ComputeIntegral());
  double integ = h_sum_norm->GetSumOfWeights(); // Should be 1, but safety first !
  double xs_lim = 0;   int i=0;
  while(xs_lim <= 0.95*integ){
    xs_lim = xs_lim + h_sum_norm->GetBinContent(i); // /(100*nbins);
    i++;
  }
  double limit = 100* h_sum_norm->GetXaxis()->GetBinCenter(i);
  std::cout<<"################################################"<<std::endl;
  std::cout<<"######   Limit = "<< limit <<" x10^{-40}cm^{2}  #######"<<std::endl;
  std::cout<<"################################################"<<std::endl;

  //p3->SetLogy();
  h_sum_norm->SetLineColor(kBlack);
  h_sum_norm->GetXaxis()->SetNdivisions(505);
  h_sum_norm->SetTitle((" ;"+titleX+";Throws").c_str());
  h_sum_norm->GetXaxis()->SetRangeUser(0,FitResults[0]->GetParameter(1)+5*FitResults[0]->GetParameter(3));
  h_sum_norm->GetYaxis()->SetRangeUser(0,1.1*h_sum_norm->GetMaximum());
  h_sum_norm->Draw("lc");

  //first fill area below a sub-range of h_sum_norm
  const Int_t np = i;
  Double_t xx[np+3], yy[np+3];
  Double_t xmin = 0; Double_t xmax = limit;
  Double_t dx = (xmax-xmin)/(np-1);
  for (Int_t j=0;j<i;j++) {
    xx[j] = h_sum_norm->GetXaxis()->GetBinCenter(j);
    yy[j] = h_sum_norm->GetBinContent(h_sum_norm->GetXaxis()->FindBin(xx[j]));
  }
  xx[np]   = xx[np-1]; yy[np]   = p3->GetUymin();
  xx[np+1] = xx[0];    yy[np+1] = yy[np];
  xx[np+2] = xx[0];    yy[np+2] = yy[0];
  TGraph *gr = new TGraph(np+3,xx,yy);
  gr->SetFillStyle(3004);
  gr->SetFillColor(kBlack);
  gr->SetLineColor(kBlack);
  gr->Draw("lf");
   
  TPaveText * pt = new TPaveText(0.525,0.675,0.9,0.85,"brNDC");
  std::stringstream sss;
  if(DiffOrIntegrated == "throw_bin[1]" || DiffOrIntegrated == "throw_bin[2]"){ 
    sss<<"#frac{d#sigma}{d"+std::string(var)+"} < " <<Form("%.2f", limit)<<"x10^{-40}cm^{2}" + var_unit + "/^{16}O";
  }
  else sss<<"#sigma < " <<Form("%.2f", limit)<<"x10^{-40}cm^{2}/^{16}O";
  pt->AddText("95% CL upper limit:");
  pt->AddText((sss.str()).c_str());
  pt->Draw();
  
} 

// define a function with 3 parameters
double gausskew(double *x,double *par) {
  double arg = 0;
  if (par[2]!=0 && x[0] < par[1]) {
    arg = (x[0] - par[1])/par[2];
    double fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  }
  else {
    arg = (x[0] - par[1])/par[3];
    double fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  }
  return fitval;
}

void PlotThrowAndFit(TFile* f_grouped,TFile* f_allcorr, int nbins, std::string DiffOrIntegrated,const char* var, TF1** Fits){
  // Get the Trees
  TTree *t_stat_data   = (TTree*)f_grouped->Get("statistics_data");
  TTree *t_stat_mc     = (TTree*)f_grouped->Get("statistics_mc");
  TTree *t_detector    = (TTree*)f_grouped->Get("highland_all_syst");
  TTree *t_rw_flux     = (TTree*)f_grouped->Get("T2KReWeight_Flux");
  TTree *t_rw_xs       = (TTree*)f_grouped->Get("T2KReWeight_XS");
  TTree *t_rw_fsi      = (TTree*)f_grouped->Get("T2KReWeight_FSI");
  TTree *t_nom         = (TTree*)f_grouped->Get("XSNominal");

  TTree *t_allcorr     = (TTree*)f_allcorr->Get("T2KReWeight_Total");

  // Get the nominal value (to later scale the detector throws)
  std::string nom_DiffOrIntegrated;
  if(DiffOrIntegrated == "throw_bin[1]") nom_DiffOrIntegrated="xsnominal_bin[1]";
  if(DiffOrIntegrated == "throw_bin[2]") nom_DiffOrIntegrated="xsnominal_bin[2]";
  if(DiffOrIntegrated == "throw_total")  nom_DiffOrIntegrated="xsnominal_total";
  double Nominal_value = GetNominal(t_nom,nbins,nom_DiffOrIntegrated);

  std::string var_unit;
  if(var == "cos#theta_{#pi^{+}}" || var == "cos#theta_{#mu^{-}}" ) var_unit = "";
  if(var == "p_{#pi^{+}}" || var == "p_{#mu^{-}}" || var == "(E_{#pi^{+}}+E_{#mu^{-}})"  ) var_unit = "/GeV";
  if(var == "#theta_{#pi^{+}#mu^{-}}") var_unit = "/deg";
  
  std::string titleX;
  if(DiffOrIntegrated == "throw_bin[1]") titleX="#frac{d#sigma}{d"+std::string(var)+"} [x10^{-38}cm^{2}"+var_unit+"/^{16}O] (1^{st}bin)";
  if(DiffOrIntegrated == "throw_bin[2]") titleX="#frac{d#sigma}{d" + std::string(var) + "} [x10^{-38}cm^{2}" + var_unit + "/^{16}O] (2^{nd}bin)";
  if(DiffOrIntegrated == "throw_total")  titleX="#sigma [x10^{-38}cm^{2}/^{16}O] (with "+std::string(var)+")";

  TCanvas *c1 = new TCanvas("c1","Fit Toy Experiments",1200,1000); 
  c1->Divide(3,2); // one sub_canvas per throw type
  
  // Statistics data
  c1->cd(1);
  SetStyle(gPad);
  TH1F *h_data = new TH1F("h_data","h_data",nbins/4,0,1);
  h_data->SetLineColor(kAzure-9);
  h_data->SetLineWidth(2);
  std::string assign_hdata = DiffOrIntegrated + ">>" + std::string(h_data->GetName());
  t_stat_data->Draw(assign_hdata.c_str());
  h_data->Scale(2000/h_data->GetEntries()); // scale so that nbr of entries is fixed to 2000 for all type of throws
  h_data->GetXaxis()->SetRangeUser(h_data->GetMean()-5*h_data->GetRMS(),h_data->GetMean()+6*h_data->GetRMS());
  h_data->SetTitle(("Stats data;"+titleX+";Throws").c_str());
  
  // Statistics mc
  c1->cd(2);
  SetStyle(gPad);
  TH1F *h_mc = new TH1F("h_mc","h_mc",nbins/2,0,1);
  h_mc->SetLineColor(kOrange-4);
  h_mc->SetLineWidth(2);
  std::string assign_hmc = DiffOrIntegrated + ">>" + std::string(h_mc->GetName());
  t_stat_mc->Draw(assign_hmc.c_str(),"","same");
  h_mc->Scale(2000/h_mc->GetEntries());
  h_mc->GetXaxis()->SetRangeUser(h_mc->GetMean()-5*h_mc->GetRMS(),h_mc->GetMean()+6*h_mc->GetRMS());
  h_mc->SetTitle(("Stats MC;"+titleX+";Throws").c_str());

  // Syst detector
  c1->cd(3);
  SetStyle(gPad);
  TH1F *h_det = new TH1F("h_det","h_det",2*nbins,0,1);
  h_det->SetLineColor(kRed-9);
  h_det->SetLineWidth(2);
  std::string assign_hdet = DiffOrIntegrated + ">>" + std::string(h_det->GetName());
  t_detector->Draw(assign_hdet.c_str(),"","same");
  h_det->Scale(2000/h_det->GetEntries());
  h_det->GetXaxis()->SetRangeUser(h_det->GetMean()-5*h_det->GetRMS(),h_det->GetMean()+7*h_det->GetRMS());
  h_det->SetTitle(("Detector;"+titleX+";Throws").c_str());

  // Syst flux
  c1->cd(4);
  SetStyle(gPad);
  TH1F *h_flux = new TH1F("h_flux","h_flux",nbins,0,1);
  h_flux->SetLineColor(kGreen-9);
  h_flux->SetLineWidth(2);
  std::string assign_hflux = DiffOrIntegrated + ">>" + std::string(h_flux->GetName());
  t_rw_flux->Draw(assign_hflux.c_str(),"","same");
  h_flux->Scale(2000/h_flux->GetEntries());
  h_flux->GetXaxis()->SetRangeUser(h_flux->GetMean()-5*h_flux->GetRMS(),h_flux->GetMean()+7*h_flux->GetRMS());
  h_flux->SetTitle(("Flux;"+titleX+";Throws").c_str());

  // Syst fsi
  c1->cd(5);
  SetStyle(gPad);
  TH1F *h_fsi = new TH1F("h_fsi","h_fsi",nbins,0,1);
  h_fsi->SetLineColor(kSpring+1);
  h_fsi->SetLineWidth(2);
  std::string assign_hfsi = DiffOrIntegrated + ">>" + std::string(h_fsi->GetName());
  t_rw_fsi->Draw(assign_hfsi.c_str(),"","same");
  h_fsi->Scale(2000/h_fsi->GetEntries());
  h_fsi->GetXaxis()->SetRangeUser(h_fsi->GetMean()-5*h_fsi->GetRMS(),h_fsi->GetMean()+7*h_fsi->GetRMS());
  h_fsi->SetTitle(("FSI;"+titleX+";Throws").c_str());

  // Syst xs
  c1->cd(6);
  SetStyle(gPad);
  TH1F *h_xs = new TH1F("h_xs","h_xs",nbins,0,1);
  h_xs->SetLineColor(kTeal-9);
  h_xs->SetLineWidth(2);
  std::string assign_hxs = DiffOrIntegrated + ">>" + std::string(h_xs->GetName());
  t_rw_xs->Draw(assign_hxs.c_str(),"","same");
  h_xs->Scale(2000/h_xs->GetEntries());
  h_xs->GetXaxis()->SetRangeUser(h_xs->GetMean()-2*h_xs->GetRMS(),h_xs->GetMean()+3*h_xs->GetRMS());
  h_xs->SetTitle(("Model;"+titleX+";Throws").c_str());

  // Define the function to fit with (skewgauss) and help by setting first value of parameters
  TF1 *f_stat_data        = new TF1("f_stat_data",gausskew,0,1,4);      f_stat_data->SetNpx(150000);      f_stat_data->SetParameters(100,h_data->GetMean(),h_data->GetRMS(),h_data->GetRMS());  f_stat_data->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");
  TF1 *f_stat_mc          = new TF1("f_stat_mc",gausskew,0,1,4);        f_stat_mc->SetNpx(150000);        f_stat_mc->SetParameters(100,h_mc->GetMean(),h_mc->GetRMS(),h_mc->GetRMS());          f_stat_mc->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");
  TF1 *f_detector         = new TF1("f_detector",gausskew,0,1,4);       f_detector->SetNpx(150000);       f_detector->SetParameters(100,h_det->GetMean(),h_det->GetRMS(),h_det->GetRMS());      f_detector->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");
  TF1 *f_rw_flux          = new TF1("f_rw_flux",gausskew,0,1,4);        f_rw_flux->SetNpx(150000);        f_rw_flux->SetParameters(100,h_flux->GetMean(),h_flux->GetRMS(),h_flux->GetRMS());    f_rw_flux->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");
  TF1 *f_rw_fsi           = new TF1("f_rw_fsi",gausskew,0,1,4);         f_rw_fsi->SetNpx(150000);         f_rw_fsi->SetParameters(100,h_fsi->GetMean(),h_fsi->GetRMS(),h_fsi->GetRMS());        f_rw_fsi->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");
  TF1 *f_rw_xs            = new TF1("f_rw_xs",gausskew,0,1,4);          f_rw_xs->SetNpx(150000);          f_rw_xs->SetParameters(100,h_xs->GetMean(),h_xs->GetRMS(),h_xs->GetRMS());            f_rw_xs->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");
  TF1 *f_detector_shift   = new TF1("f_detector_shift",gausskew,0,1,4); f_detector_shift->SetNpx(150000); f_detector_shift->SetParameters(100,h_det->GetMean(),h_det->GetRMS(),h_det->GetRMS());f_detector_shift->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}");

  // Do and plot the fits
  f_stat_data->SetLineColor(kAzure+5);
  h_data->Fit("f_stat_data");

  f_stat_mc->SetLineColor(kOrange);
  h_mc->Fit("f_stat_mc");

  f_detector->SetLineColor(kRed+1);   
  f_detector_shift->SetLineColor(kRed+1);
  h_det->Fit("f_detector");
  // Re-scale detector error around nominal value
  double sig1 = h_nom->GetMean()*f_detector->GetParameter(2)/f_detector->GetParameter(1);
  double sig2 = h_nom->GetMean()*f_detector->GetParameter(3)/f_detector->GetParameter(1);
  f_detector_shift->SetParameters(f_detector->GetParameter(0)*f_detector->GetParameter(2)/sig1,h_nom->GetMean(),sig1,sig2);

  f_rw_flux->SetLineColor(kGreen+2);
  h_flux->Fit("f_rw_flux");

  f_rw_fsi->SetLineColor(kSpring+5);
  h_fsi->Fit("f_rw_fsi");

  f_rw_xs->SetLineColor(kTeal-7);
  h_xs->Fit("f_rw_xs");

  // Save the fits
  Fits[0] = f_stat_data;
  Fits[1] = f_stat_mc;
  Fits[2] = f_detector_shift;
  Fits[3] = f_rw_flux;
  Fits[4] = f_rw_fsi;
  Fits[5] = f_rw_xs;

  // Do the same, for all reweight: Flux+FSI+XS correlation
  TCanvas *c2 = new TCanvas("c2","Quick check for Flux+FSI+XS",400,400); 
  SetStyle(gPad);
  TH1F *h_rw_corr = new TH1F("h_rw_corr","h_rw_corr",nbins/2,0,1);
  h_rw_corr->SetLineColor(kGray+1);
  h_rw_corr->SetLineWidth(2);
  std::string assign_hrwcorr = DiffOrIntegrated + ">>" + std::string(h_rw_corr->GetName());
  t_allcorr->Draw(assign_hrwcorr.c_str());
  h_rw_corr->Scale(2000/h_data->GetEntries()); // scale so that nbr of entries is fixed to 2000 for all type of throws
  h_rw_corr->GetXaxis()->SetRangeUser(h_rw_corr->GetMean()-5*h_rw_corr->GetRMS(),h_rw_corr->GetMean()+6*h_rw_corr->GetRMS());
  h_rw_corr->SetTitle(("Flux+FSI+Model correlated;"+titleX+";Throws").c_str());
  TF1 *f_rw_allcorr       = new TF1("f_rw_allcorr",gausskew,0,1,4);     f_rw_allcorr->SetNpx(150000);     f_rw_allcorr->SetParameters(30,h_rw_corr->GetMean(),h_rw_corr->GetRMS(),h_rw_corr->GetRMS());
  f_rw_allcorr->SetParNames("N","#mu","#sigma_{1}","#sigma_{2}"); 
  f_rw_allcorr->SetLineColor(kBlack);
  h_rw_corr->Fit("f_rw_allcorr");
  Fits[6] = f_rw_allcorr;
}

double GetNominal(TTree* t_nom,int nbins,std::string varToUse){
  // Return the nominal value for the variable (without plotting the canvas of the nominal histogram !)
  gROOT->SetBatch(kTRUE);
  TH1F *h_nom = new TH1F("h_nom","h_nom",nbins,0,1);
  std::string assign_hnom = varToUse+">>"+h_nom->GetName();
  t_nom->Draw(assign_hnom.c_str());
  gROOT->SetBatch(kFALSE);
  return h_nom->GetMean();
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
  gStyle->SetTitleOffset(1.5,"X");
  gStyle->SetLabelFont(42,"Y");
  gStyle->SetLabelSize(0.05,"Y");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetTitleSize(0.05,"Y");
  gStyle->SetTitleOffset(1.25,"Y");
  gStyle->SetFillColor(kWhite);
  gStyle->SetOptStat(0);
  gStyle->SetNdivisions(505,"X");
  gStyle->SetNdivisions(505,"Y");
  gStyle->SetOptFit(1);

  p->SetBottomMargin(0.2);
  p->SetLeftMargin(0.15);
  p->SetRightMargin(0.05);
  p->SetTopMargin(0.075);
  p->SetTickx();
  p->SetTicky();
  p->Draw();
  p->cd();
}
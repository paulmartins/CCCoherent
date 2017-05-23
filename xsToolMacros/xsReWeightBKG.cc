// Macro to test the bkg category fits with the sideband
// It takes one FGD selection and sideband samples, reweight the sideband categories and check the sideband fit results
// Then it applies the nkg scale factors to the selection and remove the bkg accordingly
// No unfolding is performed here, everything is done in the reconstructed space

void xsReWeightBKG(){
    const char *variable = "emupi";     // Select a variable: mumom, mutheta, pimom, pitheta, emupi, thetamupi
    bool BGsub = true;                  // set to false for purity correction (should use bkg subtraction anyway)
    int FGD = 1;                        // Set which FGD we look

    // Define the selection and sideband samples (more details in the function defintions below)
    xsInputdataMultipleRuns *inp = new xsInputdataMultipleRuns();
    ConfigInput(inp);
    xsBinning *binningTru = new xsBinning();
    xsBinning *binningRec = new xsBinning();
    ConfigBins(binningTru, binningRec, inp, variable);
    xsBinning *binningRecSB = new xsBinning();
    ConfigSBBins(binningRecSB);
    SetInputData(inp,FGD,binningRecSB);


    // It is possible to reweight a given category by a constant factor, as below
    // Note: it is important to multiply the categories NOT reweighted by 1 (event if it looks a bit useless) 
    
    if(FGD==1) inp->SetReweightFormulaData( " ( ( reaccoh==1 )*2 + ( reaccoh==2 )*3 ) + ( !(reaccoh==1 || reaccoh==2 ))*1");
    else if(FGD==2) inp->SetReweightFormulaData( " ( ( fgd2reaccoh==1 )*2 + ( fgd2reaccoh==2 )*3 ) + ( !(fgd2reaccoh==1 || fgd2reaccoh==2 ))*1");
    

    // Define the engine, here no unfolding is done, so just Noop -> No operation
    xsEngineNoop *engineWithSideband = new xsEngineNoop();
    engineWithSideband->EnableBackgroundSubtraction(BGsub);
    engineWithSideband->SetInput(inp);

    TH1 *hhh;
    // create canvas
    TCanvas *darfwas = new TCanvas("darfwas","Validate sideband fitting",1200,500);
    TPad* p1=new TPad("p1","",0.0,0.0,0.5,1,0);
    SetStyle(gStyle,p1); // (we all know ROOT default style is ugly...)
  
    // draw sideband data and MC comparison
    TLegend *leg_sideband = new TLegend(0.3,0.75,0.9,0.9);
    engineWithSideband->SetDataSource(xsNoopDataSource::DATASIDEBAND,0);
    hhh = engineWithSideband->GetResult();
    TH1 *hrecsb2 = binningRec->convertTH1(hhh);
    delete hhh;
    hrecsb2->SetLineColor(kAzure+5);
    hrecsb2->SetLineWidth(2);
    hrecsb2->SetTitle("");
    hrecsb2->GetXaxis()->SetTitle("Reconstructed E_{#nu} [GeV]");
    hrecsb2->GetYaxis()->SetTitle("Events");
    hrecsb2->GetYaxis()->SetRangeUser(0,700);
    hrecsb2->GetYaxis()->SetTitleOffset(1.5);
    hrecsb2->Draw("HIST ");
    leg_sideband->AddEntry(hrecsb2,"Fake data sb (RESx2 + DISx3)","l");
    inp->SetEnableSidebands(false);
    engineWithSideband->SetDataSource(xsNoopDataSource::MCSIDEBAND,0);
    hhh = engineWithSideband->GetResult();
    TH1 *hrecsb = binningRec->convertTH1(hhh);
    delete hhh;

    hrecsb->SetLineColor(kRed+1);
    hrecsb->SetLineWidth(2);
    hrecsb->Draw("HIST  same");
    leg_sideband->AddEntry(hrecsb,"MC sideband","l");
    leg_sideband->SetFillColor(0);
    leg_sideband->SetMargin(0.2);
    leg_sideband->SetBorderSize(0);
    leg_sideband->Draw();

    darfwas->cd();

    // draw the bkg after the categories have been constrained with the sideband scale factors
    TPad* p2=new TPad("p2","",0.5,0.0,1.0,1,0);
    SetStyle(gStyle, p2);

    TLegend *leg_sideband2 = new TLegend(0.3,0.75,0.9,0.9);
    engineWithSideband->SetDataSource(xsNoopDataSource::MCBACKGROUND,0);
    inp->SetEnableSidebands(true);
    hhh = engineWithSideband->GetResult();
    TH1 *hrec = binningRec->convertTH1(hhh);
    delete hhh;
    hrec->SetLineColor(kAzure+5);
    hrec->SetLineWidth(2);
    hrec->SetTitle("");
    hrec->GetXaxis()->SetTitle("Reconstructed E_{#nu} [GeV]");
    hrec->GetYaxis()->SetTitle("Events");
    hrec->GetYaxis()->SetRangeUser(0,100);
    hrec->GetYaxis()->SetTitleOffset(1.5);
    hrec->Draw("HIST ");
    
    // Save the results of 2000 statistical throws (Poissonian throws) in a root file 
    // For some reson this function must be called here and not later ?
    engineWithSideband->CreateResultsFile("/data/pmartins/T2K/work/CCCoherent/xsToolMacros/xsFiles/xsReWeightBKG_results.root", "statistics_data");
    
    inp->SetEnableSidebands(false);
    hhh = engineWithSideband->GetResult();
    TH1 *hrec0 = binningRec->convertTH1(hhh);
    delete hhh;
    hrec0->SetLineColor(kRed+1);
    hrec0->SetLineWidth(2);
    hrec0->Draw("HIST same ");   
    leg_sideband2->AddEntry(hrec,"Background after sideband fit","l");
    leg_sideband2->AddEntry(hrec0,"Background before sideband fit","l");
    leg_sideband2->SetFillColor(0);
    leg_sideband2->SetMargin(0.2);
    leg_sideband2->SetBorderSize(0);
    leg_sideband2->Draw();
    darfwas->cd();

    // Open the result file to plot the scale factors
    TFile *f1 = new TFile("/data/pmartins/T2K/work/CCCoherent/xsToolMacros/xsFiles/xsReWeightBKG_results.root","READ");
    DrawScaleFactors(f1);
}

// Setup phase space cut, signal, sidebands (ie which bkg to fit)
void SetInputData(xsInputdataMultipleRuns *inp, int nFGD, xsBinning *sbBins){
    // Phase space cut
    std::string true_cut = " && truelepton_mom>200 && truelepton_mom < 5000 && truelepton_costheta >0.75 && truelepton_costheta < 1 && truepi_mom>150 && truepi_mom <1500 && truepi_costheta >0.45 && truepi_costheta < 1 && trueEmupi > 500 && trueEmupi < 6500 && trueThetaCoplanar *180/3.14 > 90";
    std::string reco_cut = " && Sum$(selmu_mom[xstool_throw]) > 200 && Sum$(selmu_mom[xstool_throw]) < 5000 && Sum$(selpi_mom[xstool_throw])> 150 && Sum$(selpi_mom[xstool_throw])< 1500 && Sum$(selmu_costheta[xstool_throw]) > 0.7 && Sum$(selpi_costheta[xstool_throw]) > 0.45 && Sum$(Emupi[xstool_throw]) > 500 && Sum$(Emupi[xstool_throw]) < 6500 && Sum$(ThetaCoplanar[xstool_throw]*180/3.14) > 90";
    // FGD1 selection
    if(nFGD==1){
        inp->SetSignal("reaction==3"+true_cut); // signal is coherent in FGD1
        inp->SetCut("Sum$(accum_level[xstool_throw][0][0])> 9"+reco_cut); // signal selection branch and cut level
        inp->AddSideband("Sum$(accum_level[xstool_throw][0][1]) > 7"+reco_cut,"0",xsSidebandType::CATEGORYFIT,true,sbBins); // Add a FGD1 sideband sample
        vector<string> sideband_categs_fgd1;
        sideband_categs_fgd1.push_back("reaccoh==1 ");   std::cout<<" SidebandCat  reaccoh==1 : RES" <<std::endl; // Fit Resonant in FGD1 sideband
        sideband_categs_fgd1.push_back("reaccoh==2 ");   std::cout<<" SidebandCat  reaccoh==2 : DIS" <<std::endl; // Fit DIS in FGD1 sideband
        // IN CASE MORE BKG CATEGORIES NEED TO BE CONSTRAINED
        //sideband_categs_fgd1.push_back("reaction==4");   std::cout<<" SidebandCat  reaction==4 : NC" <<std::endl; // Fit NC in FGD1 sideband
        inp->AddCategories(sideband_categs_fgd1);
    }
    // FGD2 selection (in case FG2 is needed, in the measurement on Oxygen for exemple)
    else if(nFGD==2){
        inp->SetSignal("fgd2reaction==3"+true_cut); // signal is coherent in FGD2
        inp->SetCut("Sum$(accum_level[xstool_throw][1][0])> 9"+reco_cut); // signal selection branch and cut level
        inp->AddSideband("Sum$(accum_level[xstool_throw][1][1]) > 7"+reco_cut,"0",xsSidebandType::CATEGORYFIT,true,sbBins); // Add a FGD2 sideband sample
        vector<string> sideband_categs_fgd2;
        sideband_categs_fgd2.push_back("fgd2reaccoh==1 ");   std::cout<<" SidebandCat  fgd2reaccoh==1 : RES" <<std::endl; // Fit Resonant in FGD2 sideband
        sideband_categs_fgd2.push_back("fgd2reaccoh==2 ");   std::cout<<" SidebandCat  fgd2reaccoh==2 : DIS" <<std::endl; // Fit DIS in FGD2 sideband
        inp->AddCategories(sideband_categs_fgd2);
    }
}

void SetStyle(TStyle* g, TPad *p){
    g->SetLabelFont(42,"X");
    g->SetLabelSize(0.05,"X");
    g->SetTitleFont(62,"X");
    g->SetTitleSize(0.05,"X");
    g->SetTitleOffset(1.2,"X");
    g->SetLabelFont(42,"Y");
    g->SetLabelSize(0.05,"Y");
    g->SetTitleFont(62,"Y");
    g->SetTitleSize(0.05,"Y");
    g->SetTitleOffset(1.2,"Y");
    g->SetPadTickY(1);
    g->SetPadTickX(1);
    g->SetOptStat(00000000);

    p->SetBottomMargin(0.15);
    p->SetLeftMargin(0.15);
    p->SetRightMargin(0.05);
    p->SetTopMargin(0.05);
    p->Draw();
    p->cd(); 
}

// Setup the experiment class (which MC and Fake Data to use)
void ConfigInput(xsInputdataMultipleRuns *inp){
    std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
    std::string pathToFDMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";

    // if using real data (no fake data) then filename should be like "MicroTree_Data_R2w.root", and no need to have the POT weight, exemple:
    // inpRun2w_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R2w.root",pathToFDMicroTree+"MicroTree_Data_R2w.root");

    xsInputdataHighland2 *inpRun2w_fgd1 = new xsInputdataHighland2();
    inpRun2w_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R2w.root",pathToFDMicroTree+"MicroTree_MC_R2w.root",4.2858e19);
    inpRun2w_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run2/nd5_tuned13av1.1_13anom_run2_fine.root", "enu_nd5_tuned13a_numu");
    inp->AddRun(inpRun2w_fgd1);

    xsInputdataHighland2 *inpRun2a_fgd1 = new xsInputdataHighland2();
    inpRun2a_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R2a.root",pathToFDMicroTree+"MicroTree_MC_R2a.root",3.54457e19);
    inpRun2a_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run2/nd5_tuned13av1.1_13anom_run2_fine.root", "enu_nd5_tuned13a_numu");
    inp->AddRun(inpRun2a_fgd1);

    xsInputdataHighland2 *inpRun3b_fgd1 = new xsInputdataHighland2();
    inpRun3b_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R3b.root",pathToFDMicroTree+"MicroTree_MC_R3b.root",2.146e19);
    inpRun3b_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run3b/nd5_tuned13av1.1_13anom_run3b_fine.root", "enu_nd5_tuned13a_numu");
    inp->AddRun(inpRun3b_fgd1);

    xsInputdataHighland2 *inpRun3c_fgd1 = new xsInputdataHighland2();
    inpRun3c_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R3c.root",pathToFDMicroTree+"MicroTree_MC_R3c.root",1.34779e20);
    inpRun3c_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run3c/nd5_tuned13av1.1_13anom_run3c_fine.root", "enu_nd5_tuned13a_numu");
    inp->AddRun(inpRun3c_fgd1);

    xsInputdataHighland2 *inpRun4a_fgd1 = new xsInputdataHighland2();
    inpRun4a_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R4a.root",pathToFDMicroTree+"MicroTree_MC_R4a.root",1.76246e20);
    inpRun4a_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run4/nd5_tuned13av1.1_13anom_run4_fine.root", "enu_nd5_tuned13a_numu");
    inp->AddRun(inpRun4a_fgd1);

    xsInputdataHighland2 *inpRun4w_fgd1 = new xsInputdataHighland2();
    inpRun4w_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R4w.root",pathToFDMicroTree+"MicroTree_MC_R4w.root",1.62699e20);
    inpRun4w_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run4/nd5_tuned13av1.1_13anom_run4_fine.root", "enu_nd5_tuned13a_numu");
    inp->AddRun(inpRun4w_fgd1);
}

// Configure "signal" sample binning
void ConfigBins(xsBinning *Tru, xsBinning *Rec, xsInputdataMultipleRuns *inp, char* var){
    const int nTbins = 2;
    const int nRbins = 2;
    switch (var){
        case "mumom":
            const double Tbins[nTbins+1] ={0.2,0.7,5.0};
            Tru->addDimension("truelepton_mom/1000.",nTbins,Tbins);
            const double Rbins[nRbins+1] ={0.2,0.7,5.0};
            Rec->addDimension(string("Sum$(selmu_mom[xstool_throw]/1000.)"),nRbins,Rbins);
            std::cout<<"It works here"<<std::endl;
            break;
        case "mutheta":
            const double Tbins[nTbins+1] ={0.7,0.95,1.0};
            Tru->addDimension("truelepton_costheta",nTbins,Tbins);
            const double Rbins[nRbins+1] ={0.7,0.95,1.0};
            Rec->addDimension(string("Sum$(selmu_costheta[xstool_throw])"),nRbins,Rbins);
            break;
        case "pimom":
            const double Tbins[nTbins+1] ={0.15,0.35,1.5};
            Tru->addDimension("truepi_mom/1000.",nTbins,Tbins);
            const double Rbins[nRbins+1] ={0.15,0.4,1.5};
            Rec->addDimension(string("Sum$(selpi_mom[xstool_throw]/1000)"),nRbins,Rbins);
            break;
        case "pitheta":
            const double Tbins[nTbins+1] ={0.45,0.9,1};
            Tru->addDimension("truepi_costheta",nTbins,Tbins);
            const double Rbins[nRbins+1] ={0.45,0.9,1};
            Rec->addDimension(string("Sum$(selpi_costheta[xstool_throw])"),nRbins,Rbins);
            break;
        case "emupi":
            const double Tbins[nTbins+1] ={0.5,1.25,6.5};
            Tru->addDimension("trueEmupi/1000.",nTbins,Tbins);
            const double Rbins[nRbins+1] ={0.5,1.25,6.5};
            Rec->addDimension(string("Sum$(Emupi[xstool_throw]/1000)"),nRbins,Rbins);
            break;
        case "thetamupi":
            const double Tbins[nTbins+1] ={90,155,180};
            Tru->addDimension("trueThetaCoplanar*180/3.14",nTbins,Tbins);
            const double Rbins[nRbins+1] ={90,155,180};
            Rec->addDimension(string("Sum$(ThetaCoplanar[xstool_throw]*180/3.14)"),nRbins,Rbins);
            break;
    }
    // Save the binnings to the input data
    inp->SetTrueBinning(Tru);
    inp->SetReconstructedBinning(Rec);
}

// Configure sideband fit binning
void ConfigSBBins(xsBinning *Rec){
    const double Rbins[3] ={0.5,1.25,6.5};
    Rec->addDimension(string("Sum$(Emupi[xstool_throw]/1000)"),2,Rbins);
}

// Name is explicit enough
void DrawScaleFactors(TFile * f1){
    // Just a nice color palette
    const UInt_t Number = 5;
    Double_t Red[Number]    = { 0.00, 0.00, 1.00, 1.00, 1.00 };
    Double_t Green[Number]  = { 0.00, 1.00, 1.00, 1.00, 0.00 };
    Double_t Blue[Number]   = { 1.00, 1.00, 1.00, 0.00, 0.00 };
    Double_t Length[Number] = { 0.00, 0.40, 0.50, 0.60, 1.00 };
    TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,50);

    // Get the scale factor histograms from input file
    TTree * tree1 = (TTree*)f1.Get("statistics_data");
    double sf_throw1[4];
    double sf_nom1[4];
    tree1->SetBranchAddress("throw_sideband_scale_factor", &sf_throw1);
    tree1->SetBranchAddress("nominal_sideband_scale_factor", &sf_nom1);

    TH1F* h_sf_RES1 = new TH1F("h_sf_RES1",";Resonant scale factor ; Throws",100,0,4);
    TH1F* h_sf_DIS1 = new TH1F("h_sf_DIS1",";DIS scale factor ; Throws",100,0,6);
    TH2F* h_sf_RESDIS = new TH2F("h_sf_RESDIS", ";RES scale factor; DIS scale factor",100,0,4,100,0,6);

    // Calculate how often the fit fail to converge 
    double fitfail = 0;
    for (Int_t indx=0;indx<tree1->GetEntries();indx++){
        tree1->GetEntry(indx);
        h_sf_RES1->Fill(sf_throw1[0]);
        h_sf_DIS1->Fill(sf_throw1[1]);
        h_sf_RESDIS->Fill(sf_throw1[0],sf_throw1[1]);
        if(sf_throw1[1]<0.0001 || sf_throw1[0]<0.0001 ) fitfail ++;
    }
    std::cout<<"Fit fail: "<<fitfail *100/tree1->GetEntries()<<"%"<<std::endl;

    // Plot the scale factor result
    TCanvas *c11 = new TCanvas("c1","c1",1400,600);
    TPad* p11=new TPad("p11","",0.0,0.0,0.49,1,0);
    SetStyle(gStyle,p11);
    h_sf_RES1->SetLineColor(kAzure+3);
    h_sf_RES1->SetLineStyle(1);
    h_sf_RES1->SetLineWidth(2);
    h_sf_RES1->Draw();
    c11->cd();

    TPad* p22=new TPad("p22","",0.51,0.0,1.0,1.0,0);
    SetStyle(gStyle,p22);
    h_sf_DIS1->SetLineColor(kAzure+5);
    h_sf_DIS1->SetLineStyle(1);
    h_sf_DIS1->SetLineWidth(2);
    h_sf_DIS1->Draw();
    c11->cd();

    // Plot the correlation between the two scale factors
    TCanvas *c22 = new TCanvas("c22","c22",700,600);
    TPad* p9=new TPad("p9","",0,0.0,1,1,0);
    SetStyle(gStyle,p9);
    h_sf_RESDIS->Draw("COLZ");
}
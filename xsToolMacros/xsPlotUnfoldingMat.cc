// Macro to plot the unfolding (or unsmearing) matrices
// (Bayesian method with 1 iteration)
void xsPlotUnfoldingMat() {
    // Just the numbers of target in FV, as in the update of xsSubtraction.cxx
    const float nFGD1 = 3.567e+28;
    const float nFGD2 = 2.1998e+28;
    const float nTargetsFGD2waterlike = 1.864e+28;

    // Few handles to make life easier, see xsReWeightBKG.cc for more details
    bool useCohRW_MC = true;        // use the BS predictions in the MC
    bool useCohRW_FD = true;        // use the BS predictions in the Fake Data
    const char *variable = "mumom"; // choose your variable: mumom, mutheta, pimom, pitheta, emupi, thetamupi
    bool BGsub = true;              // set to false for purity correction
    int FGDnbr = 2;                 // set which FGD you want
    bool Subtraction = false;       // do you want to subtract FGD1 to FGD2 (ie xs on water ?)
    bool enableWeights = false;     // enables the T2KReWeight weigths for flux, theory and FSI systematics

    if(Subtraction) FGDnbr==1;

    // Setup everything before unfolding, see xsReWeightBKG.cc for detailed documentation
    xsInputdataMultipleRuns *inp1 = new xsInputdataMultipleRuns();
    ConfigInput(inp1,useCohRW_MC,useCohRW_FD, enableWeights);
    xsBinning *binningTru1 = new xsBinning();
    xsBinning *binningRec1 = new xsBinning();
    ConfigBins(binningTru1, binningRec1, inp1, variable);
    xsBinning *binningRecSB1 = new xsBinning();
    ConfigSBBins(binningRecSB1);
    SetInputData(inp1,FGDnbr,binningRecSB1);

    // if you want xs measurement on water, then you need 2 selections, one in each FGD !
    if(Subtraction){
        xsInputdataMultipleRuns *inp2 = new xsInputdataMultipleRuns();
        ConfigInput(inp2,useCohRW_MC,useCohRW_FD, enableWeights);
        xsBinning *binningTru2 = new xsBinning();
        xsBinning *binningRec2 = new xsBinning();
        ConfigBins(binningTru2, binningRec2, inp2, variable);
        xsBinning *binningRecSB2 = new xsBinning();
        ConfigSBBins(binningRecSB2);
        SetInputData(inp2,2,binningRecSB2);
    }

    xsEngineUnfolding *fgd1_engines;
    if(Subtraction){
        xsEngineUnfolding *fgd2_engines;
        xsSubtraction *engines;
    }

    string names;
    int colors[6] = {865 , 825 ,800, 1,2,3};
    int styles;

    TH2 *hunsmearing;
    TCanvas *canUnfoldingMat = new TCanvas("canUnfoldingMat","Unfolding matrices");

    fgd1_engines = new xsEngineUnfoldingBayes();
    if(Subtraction) fgd2_engines = new xsEngineUnfoldingBayes();

    ((xsEngineUnfoldingBayes*)fgd1_engines)->SetNumberOfIterations(1);
    if(Subtraction) ((xsEngineUnfoldingBayes*)fgd2_engines)->SetNumberOfIterations(1);

    fgd1_engines->EnableBackgroundSubtraction(BGsub);
    fgd1_engines->SetInput(inp1);
    if(FGDnbr==1) fgd1_engines->SetNTargets(nFGD1);
    if(FGDnbr==2) fgd1_engines->SetNTargets(nFGD2);
    if(Subtraction){
        fgd2_engines->EnableBackgroundSubtraction(BGsub);
        fgd2_engines->SetInput(inp2);
        fgd2_engines->SetNTargets(nTargetsFGD2waterlike);
        engines= new xsSubtraction(fgd2_engines,fgd1_engines);
        engines->UsexsReweightForXSNominal(true);
        engines->DoFGDsSubtraction(false);
    }

    canUnfoldingMat->cd();
    TPad *p = new TPad("p","p",0,0,1,1);
    SetStyle(p);
    hunsmearing = fgd1_engines->GetUnsmearingMatrix();
    // Just setup the axis titles (could be done in a specific function)
    std::string titleX, titleY;
    if(variable == "mumom") { titleX="p_{#mu^{-}} reco bin"; titleY="p_{#mu^{-}} true bin";}
    else if(variable == "mutheta") { titleX="cos#theta_{#mu^{-}} reco bin"; titleY="cos#theta_{#mu^{-}} true bin";}
    else if(variable == "pimom") { titleX="p_{#pi^{+}} reco bin"; titleY="p_{#pi^{+}} true bin";}
    else if(variable == "pitheta") { titleX="cos#theta_{#pi^{+}} reco bin"; titleY="cos#theta_{#pi^{+}} true bin";}
    else if(variable == "emupi") { titleX="E_{#pi^{+}}+E_{#mu^{-}} reco bin"; titleY="E_{#pi^{+}}+E_{#mu^{-}} true bin";}
    else if(variable == "thetamupi") { titleX="#theta_{#pi^{+}#mu^{-}} reco bin"; titleY="#theta_{#pi^{+}#mu^{-}} true bin";}

    hunsmearing->SetTitle((" ;"+titleX+" ;"+titleY).c_str());
    hunsmearing->GetXaxis()->CenterLabels();        hunsmearing->GetYaxis()->CenterLabels();
    hunsmearing->GetXaxis()->SetRangeUser(1,3);     hunsmearing->GetYaxis()->SetRangeUser(1,3);
    hunsmearing->GetXaxis()->SetNdivisions(202);    hunsmearing->GetYaxis()->SetNdivisions(202);
    hunsmearing->GetZaxis()->SetRangeUser(-0.7,2.0);
    hunsmearing->SetMarkerSize(2.5);
    hunsmearing->Draw("col text");
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

	gStyle->SetOptStat(0);
	p->SetBottomMargin(0.15);
  	p->SetLeftMargin(0.15);
  	p->SetRightMargin(0.1);
  	p->SetTopMargin(0.05);
  	p->SetTickx();
  	p->Draw();
	p->cd();
}

void ConfigInput(xsInputdataMultipleRuns *inp,bool useCohRW_MC,bool useCohRW_FD, bool weights){
    if (useCohRW_MC) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTreesRW/";
    else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
    if (useCohRW_FD) std::string pathToFDMicroTree = "/data/t2k/paul/MicroTreesRW/";
    else std::string pathToFDMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
    std::string pathToWeights = "/data/t2k/paul/Weights/";

    xsInputdataHighland2 *inpRun2w_fgd1 = new xsInputdataHighland2();
    inpRun2w_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R2w.root",pathToFDMicroTree+"MicroTree_MC_R2w.root",4.2858e19);
    inpRun2w_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run2/nd5_tuned13av1.1_13anom_run2_fine.root", "enu_nd5_tuned13a_numu");
    if(weights) xsReweightSystematics *reweightRun2w_fgd1 = new xsReweightSystematics(pathToWeights+"R2w/weights_unified.root","numu");
    if(weights) inpRun2w_fgd1->AddReweighting(reweightRun2w_fgd1);
    inp->AddRun(inpRun2w_fgd1);

    xsInputdataHighland2 *inpRun2a_fgd1 = new xsInputdataHighland2();
    inpRun2a_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R2a.root",pathToFDMicroTree+"MicroTree_MC_R2a.root",3.54457e19);
    inpRun2a_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run2/nd5_tuned13av1.1_13anom_run2_fine.root", "enu_nd5_tuned13a_numu");
    if(weights) xsReweightSystematics *reweightRun2a_fgd1 = new xsReweightSystematics(pathToWeights+"R2a/weights_unified.root","numu");
    if(weights) inpRun2a_fgd1->AddReweighting(reweightRun2a_fgd1);
    inp->AddRun(inpRun2a_fgd1);

    xsInputdataHighland2 *inpRun3b_fgd1 = new xsInputdataHighland2();
    inpRun3b_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R3b.root",pathToFDMicroTree+"MicroTree_MC_R3b.root",2.146e19);
    inpRun3b_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run3b/nd5_tuned13av1.1_13anom_run3b_fine.root", "enu_nd5_tuned13a_numu");
    if(weights) xsReweightSystematics *reweightRun3b_fgd1 = new xsReweightSystematics(pathToWeights+"R3b/weights_unified.root","numu");
    if(weights) inpRun3b_fgd1->AddReweighting(reweightRun3b_fgd1);
    inp->AddRun(inpRun3b_fgd1);

    xsInputdataHighland2 *inpRun3c_fgd1 = new xsInputdataHighland2();
    inpRun3c_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R3c.root",pathToFDMicroTree+"MicroTree_MC_R3c.root",1.34779e20);
    inpRun3c_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run3c/nd5_tuned13av1.1_13anom_run3c_fine.root", "enu_nd5_tuned13a_numu");
    if(weights) xsReweightSystematics *reweightRun3c_fgd1 = new xsReweightSystematics(pathToWeights+"R3c/weights_unified.root","numu");
    if(weights) inpRun3c_fgd1->AddReweighting(reweightRun3c_fgd1);
    inp->AddRun(inpRun3c_fgd1);

    xsInputdataHighland2 *inpRun4a_fgd1 = new xsInputdataHighland2();
    inpRun4a_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R4a.root",pathToFDMicroTree+"MicroTree_MC_R4a.root",1.76246e20);
    inpRun4a_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run4/nd5_tuned13av1.1_13anom_run4_fine.root", "enu_nd5_tuned13a_numu");
    if(weights) xsReweightSystematics *reweightRun4a_fgd1 = new xsReweightSystematics(pathToWeights+"R4a/weights_unified.root","numu");
    if(weights) inpRun4a_fgd1->AddReweighting(reweightRun4a_fgd1);
    inp->AddRun(inpRun4a_fgd1);

    xsInputdataHighland2 *inpRun4w_fgd1 = new xsInputdataHighland2();
    inpRun4w_fgd1->SetupFromHighland(pathToMCMicroTree+"MicroTree_MC_R4w.root",pathToFDMicroTree+"MicroTree_MC_R4w.root",1.62699e20);
    inpRun4w_fgd1->SetFlux("/data/pmartins/T2K/work/Highland2_v2/psyche/psycheUtils/v3r9/data/tuned13av1.1/run4/nd5_tuned13av1.1_13anom_run4_fine.root", "enu_nd5_tuned13a_numu");
    if(weights) xsReweightSystematics *reweightRun4w_fgd1 = new xsReweightSystematics(pathToWeights+"R4w/weights_unified.root","numu");
    if(weights) inpRun4w_fgd1->AddReweighting(reweightRun4w_fgd1);
    inp->AddRun(inpRun4w_fgd1);
    
}

void ConfigBins(xsBinning *Tru, xsBinning *Rec, xsInputdataMultipleRuns *inp, char* var){
    const int nTbins = 2;
    const int nRbins = 2;
    switch (var){
        case "mumom":
            const double Tbins[nTbins+1] ={0.2,0.7,5.0};
            Tru->addDimension("truelepton_mom/1000.",nTbins,Tbins);
            const double Rbins[nRbins+1] ={0.2,0.7,5.0};
            Rec->addDimension(string("Sum$(selmu_mom[xstool_throw]/1000.)"),nRbins,Rbins);
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

void ConfigSBBins(xsBinning *SBbin){
    const double Rbins[3] ={0.5,1.25,6.5};
    SBbin->addDimension(string("Sum$(Emupi[xstool_throw]/1000)"),2,Rbins);
}

void SetInputData(xsInputdataMultipleRuns *inp, int nFGD, xsBinning *sbbins){
    // Phase space cuts to improve efficiency
    std::string true_cut = " && truelepton_mom>200 && truelepton_mom < 5000 && truelepton_costheta >0.75 && truelepton_costheta < 1 && truepi_mom>150 && truepi_mom <1500 && truepi_costheta >0.45 && truepi_costheta < 1 && trueEmupi > 500 && trueEmupi < 6500 && trueThetaCoplanar *180/3.14 > 90";
    std::string reco_cut = " && Sum$(selmu_mom[xstool_throw]) > 200 && Sum$(selmu_mom[xstool_throw]) < 5000 && Sum$(selpi_mom[xstool_throw])> 150 && Sum$(selpi_mom[xstool_throw])< 1500 && Sum$(selmu_costheta[xstool_throw]) > 0.7 && Sum$(selpi_costheta[xstool_throw]) > 0.45 && Sum$(Emupi[xstool_throw]) > 500 && Sum$(Emupi[xstool_throw]) < 6500 && Sum$(ThetaCoplanar[xstool_throw]*180/3.14) > 90";

    if(nFGD==1){
        inp->SetSignal("reaction==3"+true_cut); // signal is cc-coherent
        inp->SetCut("Sum$(accum_level[xstool_throw][0][0])> 9"+reco_cut);
        inp->AddSideband("Sum$(accum_level[xstool_throw][0][1]) > 7"+reco_cut,"0",xsSidebandType::CATEGORYFIT,true,sbbins);
        vector<string> sideband_categs_fgd1;
        sideband_categs_fgd1.push_back("reaccoh==1 ");   std::cout<<" SidebandCat  reaccoh==1 : CC-RES" <<std::endl;
        sideband_categs_fgd1.push_back("reaccoh==2 ");   std::cout<<" SidebandCat  reaccoh==2 : CC-DIS" <<std::endl;
        inp->AddCategories(sideband_categs_fgd1);
    }
    else if(nFGD==2){
        inp->SetSignal("fgd2reaction==3"+true_cut);
        inp->SetCut("Sum$(accum_level[xstool_throw][1][0])> 9"+reco_cut);
        inp->AddSideband("Sum$(accum_level[xstool_throw][1][1]) > 7"+reco_cut,"0",xsSidebandType::CATEGORYFIT,true,sbbins);
        vector<string> sideband_categs_fgd2;
        sideband_categs_fgd2.push_back("fgd2reaccoh==1 ");   std::cout<<" SidebandCat  fgd2reaccoh==1 : RES" <<std::endl;
        sideband_categs_fgd2.push_back("fgd2reaccoh==2 ");   std::cout<<" SidebandCat  fgd2reaccoh==2 : DIS" <<std::endl;
        inp->AddCategories(sideband_categs_fgd2);
    }
}
// Macro that create results file
// Make sure the variable and the analyses (FGD1 measurement on Carbon or Subtraction, limit on Oxygen) are in the result filename
void xsMakeResultFiles() {
    // Just the numbers of target in FV, as in the update of xsSubtraction.cxx
    const float nFGD1 = 3.567e+28;
    const float nFGD2 = 2.1998e+28;
    const float nTargetsFGD2waterlike = 1.864e+28;
    
    // Few handles to make life easier
    // If it is not clear enoughm please have a look in xsReWeightBKG.cc
    // TODO:
    // passed these options as arguments and then compile
    bool useCohRW_MC = true;        // true=use the BS predictions in the MC | false=use RS predictions
    bool useCohRW_FD = true;        // true=use the BS predictions in the Fake Data | false=use the RS predictions
    const char *variable = "mumom"; // choose your variable between: mumom, mutheta, pimom, pitheta, emupi, thetamupi
    bool BGsub = true;              // set to false for purity correction, should always be true, purity correction is bad !
    int FGDnbr = 1;                 // set which FGD you want
    bool Subtraction = false;       // true=subtract FGD1 sample to FGD2 for xs on water (ie upper limit) | false=FGD1 only (xs on carbon)
    bool enableWeights = true;      // enables the T2KReWeight weigths for flux, theory and FSI systematics 
    if(Subtraction) FGDnbr==1;

    // Setup things
    // Load the selections files
    xsInputdataMultipleRuns *inp1 = new xsInputdataMultipleRuns();
    ConfigInput(inp1,useCohRW_MC,useCohRW_FD, enableWeights);
    // Define your binning (depends on the variable you choose !)
    xsBinning *binningTru1 = new xsBinning();
    xsBinning *binningRec1 = new xsBinning();
    ConfigBins(binningTru1, binningRec1, inp1, variable);
    // Define the sideband binning (it's always Emupi)
    xsBinning *binningRecSB1 = new xsBinning();
    ConfigSBBins(binningRecSB1);
    // Define what is the signal, the bkg to fit in the sidebands, the phase space ...
    SetInputData(inp1,FGDnbr,binningRecSB1);

    // If you want xs measurement on water, then you need 2 selections, one in each FGD, so that you can subtract one with another
    // So we do it again
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

    // Define your engines (how do we unfold -> Bayesian unfolding with 1 iteration)
    xsEngineUnfolding *fgd1_engines;
    if(Subtraction){
        xsEngineUnfolding *fgd2_engines;
        xsSubtraction* engines;
    }
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

    // Make the results files for all the error sources
    // It can take some time ...
    vector<string> sources = inp1->GetErrorSources();
    if(!Subtraction && FGDnbr==1) fgd1_engines->CreateResultsFile("xsFiles/xsResults_Mumom_FGD1Grouped.root",sources);
    if(!Subtraction && FGDnbr==2) fgd2_engines->CreateResultsFile("xsFiles/xsResults_Mumom_FGD2Grouped.root",sources); // Never used, but whatever
    if(Subtraction) engines->CreateResultsFile("xsFiles/xsResults_Mumom_SubGrouped.root",sources);
}

void ConfigInput(xsInputdataMultipleRuns *inp,bool useCohRW_MC,bool useCohRW_FD, bool weights){
    if (useCohRW_MC) std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/RW2/";
    else std::string pathToMCMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
    if (useCohRW_FD) std::string pathToFDMicroTree = "/data/t2k/paul/MicroTrees_allsyst/RW2/";
    else std::string pathToFDMicroTree = "/data/t2k/paul/MicroTrees_allsyst/";
    std::string pathToWeights = "/data/t2k/paul/WeightsGroupedCoh/";

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

void ConfigSBBins(xsBinning *Rec){
    const double Rbins[3] ={0.5,1.25,6.5};
    Rec->addDimension(string("Sum$(Emupi[xstool_throw]/1000)"),2,Rbins);
}

void SetInputData(xsInputdataMultipleRuns *inp, int nFGD, xsBinning *sbBins){
    // Phase space cuts to improve efficiency
    std::string true_cut = " && truelepton_mom>200 && truelepton_mom < 5000 && truelepton_costheta >0.75 && truelepton_costheta < 1 && truepi_mom>150 && truepi_mom <1500 && truepi_costheta >0.45 && truepi_costheta < 1 && trueEmupi > 500 && trueEmupi < 6500 && trueThetaCoplanar *180/3.14 > 90";
    std::string reco_cut = " && Sum$(selmu_mom[xstool_throw]) > 200 && Sum$(selmu_mom[xstool_throw]) < 5000 && Sum$(selpi_mom[xstool_throw])> 150 && Sum$(selpi_mom[xstool_throw])< 1500 && Sum$(selmu_costheta[xstool_throw]) > 0.7 && Sum$(selpi_costheta[xstool_throw]) > 0.45 && Sum$(Emupi[xstool_throw]) > 500 && Sum$(Emupi[xstool_throw]) < 6500 && Sum$(ThetaCoplanar[xstool_throw]*180/3.14) > 90";
    if(nFGD==1){
        inp->SetSignal("reaction==3"+true_cut); // signal is cc-coherent
        inp->SetCut("Sum$(accum_level[xstool_throw][0][0])> 9"+reco_cut); 
        inp->AddSideband("Sum$(accum_level[xstool_throw][0][1]) > 7"+reco_cut,"0",xsSidebandType::CATEGORYFIT,true,sbBins);
        vector<string> sideband_categs_fgd1;
        sideband_categs_fgd1.push_back("reaccoh==1 ");   std::cout<<" SidebandCat  reaccoh==1 : CC-RES has been added" <<std::endl;
        sideband_categs_fgd1.push_back("reaccoh==2 ");   std::cout<<" SidebandCat  reaccoh==2 : CC-DIS has been added" <<std::endl;
        inp->AddCategories(sideband_categs_fgd1);
    }
    else if(nFGD==2){
        inp->SetSignal("fgd2reaction==3"+true_cut);
        inp->SetCut("Sum$(accum_level[xstool_throw][1][0])> 9"+reco_cut);
        inp->AddSideband("Sum$(accum_level[xstool_throw][1][1]) > 7"+reco_cut,"0",xsSidebandType::CATEGORYFIT,true,sbBins);
        vector<string> sideband_categs_fgd2;
        sideband_categs_fgd2.push_back("fgd2reaccoh==1 ");   std::cout<<" SidebandCat  fgd2reaccoh==1 : RES has been added" <<std::endl;
        sideband_categs_fgd2.push_back("fgd2reaccoh==2 ");   std::cout<<" SidebandCat  fgd2reaccoh==2 : DIS has been added" <<std::endl;
        inp->AddCategories(sideband_categs_fgd2);
    }
}
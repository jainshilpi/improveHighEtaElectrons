# improveHighEtaElectrons

###Samples used: DoubleElectron gun from 1.7 GeV to 300 GeV in pT

######CMSSW version: CMSSW_11_0_1

1. The gen-sim-raw samples with nominal configuration (please use config.Data.inputDBS        = 'phys03'):
   *  /SingleEle_V0_GENSIMRAW/shilpi-SingleEle_V0_miniAOD_nominal-28ea11753f803e89e7fd3e375196acc9/USER
   * Ntuples are already made. Can be found here: /eos/cms/store/group/phys_egamma/shilpi/improveTrackingHighEleEta/ntuples/SingleEle_V0_GENSIMRAW/crab_nominal/210317_004029/0000/

2. For modified config, the gen-sim-raw samples can be used from here: /SingleEle_V0_GENSIMRAW/shilpi-crab_SingleEle_GENSIMRAW-2133ffc961f67f7c3fa0060c152fa455/USER
   * To modify the config, one needs to use aod_cfg_modified.py. 
   * For now, the parameter which was tried was: process.electronCkfTrackCandidates.TransientInitialStateEstimatorParameters.numberMeasurementsForFit = cms.int32(2)

3. Once the above aod config is finalised, generate the aod samples. 
4. Generate the miniAOD using the above aod samples
5. Then run the ggNtuplizer. Instructions: https://github.com/cmkuo/ggAnalysis/tree/110X
6. Once the modified config ntuples are there, go to analysis directory, update files.list and do:
   * root -l -b -q runAll.C+

#from CRABClient.UserUtilities import config, getUsernameFromSiteDB
#import sys

#config = config()

from CRABAPI.RawCommand import crabCommand
from httplib import HTTPException

from CRABClient.UserUtilities import config
config = config()

from multiprocessing import Process

def submit(config):
    try:
        crabCommand('submit', config = config)
    except HTTPException, hte:
        print hte.headers

#**************************submit function***********************
#from CRABAPI.RawCommand import crabCommand
#from CRABClient.ClientExceptions import ClientException
#from httplib import HTTPException
#def submit(config):
#        try:
#                crabCommand('submit', config = config)
#        except HTTPException as hte:
#                print "Failed submitting task: %s" % (hte.headers)
#        except ClientException as cle:
#                print "Failed submitting task: %s" % (cle)
#****************************************************************

#submitVersion = "V1_RAWSIM"
#submitVersion = "V0_AOD_modified"
submitVersion = "V1_AOD_modified"
mainOutputDir = "/store/group/phys_egamma/shilpi/improveTrackingHighEleEta/%s" %submitVersion



config.General.requestName = 'SingleEle_AOD'
config.General.transferLogs = True
config.General.workArea = 'crab_projects_%s' % submitVersion

config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ['T3_US_UCR','T3_US_FNALLPC','T2_US_Purdue','T3_US_Rice','T3_US_Rutgers','T3_US_FIT','T3_US_PSC','T3_US_OSU','T3_US_TAMU','T3_US_UMD','T3_US_VC3_NotreDame','T3_US_SDSC','T3_US_Colorado','T3_US_OSG','T3_US_Princeton_ICSE','T3_US_NERSC','T3_US_Baylor','T2_US_Nebraska','T2_US_UCSD','T2_US_Wisconsin','T2_US_MIT','T3_US_TACC','T3_US_TTU','T3_US_UMiss']
#config.Site.blacklist = ['T2_US_Florida','T2_US_Vanderbilt','T3_US_PuertoRico']
#config.Site.blacklist = ['T2_CH_CERN']
#config.JobType.numCores=4
config.JobType.allowUndistributedCMSSW = True 
#config.JobType.psetName  = 'beamhalo_gensim.py'
config.JobType.pluginName  = 'Analysis'
config.Data.inputDBS = 'phys03'
config.JobType.psetName  = 'aod_cfg_modified.py'
config.Data.inputDataset = '/SingleEle_V0_GENSIMRAW/shilpi-crab_SingleEle_GENSIMRAW-2133ffc961f67f7c3fa0060c152fa455/USER'
config.Data.publication = True
#config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % (mainOutputDir)
#config.Data.splitting     = 'EventBased'
#config.Data.splitting     = 'Automatic'
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 1
#config.Data.unitsPerJob   = 1000
#config.Data.totalUnits    = 10000000

#config.Data.outputPrimaryDataset='SinglePho_%s' %submitVersion
config.Data.outputDatasetTag ='SingleEle_%s' %submitVersion

submit(config)

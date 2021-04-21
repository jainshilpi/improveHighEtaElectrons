#define Analyse_cxx
#include "Analyse.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <map>
#include "TLorentzVector.h"
#include "TFile.h"
#include <iostream>
#include "TSystemFile.h"
#include "TSystemDirectory.h"

//bool debug = true;
bool debug = false;

void Analyse::Loop(string fname, string fnameout)
{

  using namespace std;
  
  cout<<"Now inside loop, fname : fout : "<<fname<<" "<<fnameout<<endl;
  
  TTree *tin = list_files(fname.c_str()); 

  Init(tin);

  TFile *fout = new TFile(fnameout.c_str(), "RECREATE");
  map<string,TH1F*> hmap;

  hmap["etaAll"] = new TH1F("etaAll","",90,-3,3);
  hmap["etaMatch"] = new TH1F("etaMatch","",90,-3,3);
  hmap["etaRatio"] = new TH1F("etaRatio","",90,-3,3);
  
  hmap["eleEta"] = new TH1F("eleEta","",90,-3,3);

  hmap["ptAll"] = new TH1F("ptAll","",140,2,300);
  hmap["ptMatch"] = new TH1F("ptMatch","",140,2,300);
  hmap["ptRatio"] = new TH1F("ptRatio","",140,2,300);

  hmap["elePt"] = new TH1F("elePt","",140,2,300);

  hmap["elePhi"] = new TH1F("elePhi","",140,-3.2,3.2);

  for(map<string,TH1F*>::iterator it = hmap.begin(); it != hmap.end(); ++it) {
    
    hmap[it->first]->Sumw2();
  }


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      for(int imc=0; imc<nMC; imc++){
	
	
	//pick only ele tracks --- these are single particle gun so no status needed
	if( abs(mcPID->at(imc)) != 11) continue;

	//if(mcPt->at(imc)<10) continue;
	
	if(debug) cout<<"found the mc ele"<<endl;
	
	int matchedEleInd = findRecoEle(imc);
	
       
	hmap["etaAll"]->Fill(mcEta->at(imc));
	hmap["ptAll"]->Fill(mcPt->at(imc));
	
	if(matchedEleInd>=0){

	  hmap["etaMatch"]->Fill(mcEta->at(imc));
	  hmap["ptMatch"]->Fill(mcPt->at(imc));

	  hmap["eleEta"]->Fill(eleEta->at(matchedEleInd));
	  hmap["elePt"]->Fill(elePt->at(matchedEleInd));
	  hmap["elePhi"]->Fill(elePhi->at(matchedEleInd));

	}

      }//for(int imc=0; imc<nMC; imc++)
      
   }//for (Long64_t jentry=0; jentry<nentries;jentry++)

   ///get the ratio ones
   hmap["etaRatio"]->Divide(hmap["etaMatch"],hmap["etaAll"]);
   hmap["ptRatio"]->Divide(hmap["ptMatch"],hmap["ptAll"]);

   fout->cd();
  for(map<string,TH1F*>::iterator it = hmap.begin(); it != hmap.end(); ++it) {
    
    hmap[it->first]->Write();
  }

  fout->Write();
}



int Analyse::findRecoEle(int imc){

  double tmpdR = 999;
  
  int matchInd = -99;
  TLorentzVector *ele1 = new TLorentzVector();
  ele1->SetPtEtaPhiM(mcPt->at(imc), mcEta->at(imc), mcPhi->at(imc), 0.511/1000);
  
  if(debug) cout<<"nEle "<<nEle<<endl;
  
  for(int iele=0; iele<nEle; iele++){

    TLorentzVector *ele2 = new TLorentzVector();
    ele2->SetPtEtaPhiM(elePt->at(iele), eleEta->at(iele), elePhi->at(iele), 0.511/1000);
    
  double dR = ele1->DeltaR(*ele2);
  if(dR>0.1) continue;
  
  if(tmpdR > dR){

    tmpdR = dR;
    matchInd = iele;
  }

  }
  
  return matchInd;
  
}


TChain* Analyse::list_files(const char *dirname, const char *ext){
  
  TChain *t = new TChain("ggNtuplizer/EventTree");
  TSystemDirectory dir(dirname, dirname); 
  TList *files = dir.GetListOfFiles(); 
  if (files) 
    { 
      TSystemFile *file; 
      TString fname; 
      TIter next(files); 
      while ((file=(TSystemFile*)next())) { 
	fname = file->GetName(); 
	if (!file->IsDirectory() && fname.EndsWith(ext)) 
	  { 
	    cout << fname.Data() << endl; 
	    t->Add(Form("%s/%s",dirname,fname.Data()));
	  } 
      } 
    } 
  return t;
}

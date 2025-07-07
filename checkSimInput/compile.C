// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
#include "checkSimInput.h"
#include "checkSimInput.C"

// #include "LoadInputHits.C"

#include <typeinfo>

int main(int argc, char* argv[]){
  TChain *tc = new TChain("events");
  
  // please replace directory and "fInput.root" the file name to yours
  std::string fDir = "./";
  // std::string fInputName = fDir + "fInput.root";
  std::string fInputName = argv[1];
  tc->Add(fInputName.c_str());
  // std::string fOutputName = fDir+"fOutput.root";
  std::string fOutputName = fDir + argv[2];

  TTree *tt = (TTree*)tc;

  checkSimInput *h = new checkSimInput(tt, fInputName, fOutputName);

  //h->Show(1);
  h->Loop();
  
}
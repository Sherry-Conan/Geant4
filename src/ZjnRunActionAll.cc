#include "ZjnRunActionAll.hh"

#include <G4Run.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4CsvAnalysisManager.hh>
#include <G4XmlAnalysisManager.hh>
#include <G4RootAnalysisManager.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ZjnRunActionAll::ZjnRunActionAll()
{


}

ZjnRunActionAll::~ZjnRunActionAll()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* ZjnRunActionAll::GenerateRun()
{
  return 0;
}

void ZjnRunActionAll::BeginOfRunAction(const G4Run* /*aRun*/)
{
  analysisManager = G4RootAnalysisManager::Instance(); 

  analysisManager->SetVerboseLevel(1); 

  analysisManager->CreateNtuple("tree", FileName); 

  analysisManager -> CreateNtupleIColumn("EventID"); 
  analysisManager -> CreateNtupleDColumn("GlobalTime"); 
  // analysisManager -> CreateNtupleDColumn("Edep"); 

  analysisManager -> FinishNtuple(); 
  analysisManager -> OpenFile(FileName);//输出文件名

    if (IsMaster()) {
    G4cout << G4endl << "--------------------Start of Global Run-----------------------" << G4endl;
  }
  else {
    G4cout << G4endl << "--------------------Start of Local Run------------------------" << G4endl;
  }
}

void ZjnRunActionAll::EndOfRunAction(const G4Run* /*aRun*/)
{
  analysisManager->Write();
  analysisManager->CloseFile(); 
  G4cout << "MeV = " << MeV << G4endl; 
}
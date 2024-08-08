#include "ZjnEventActionAll.hh"
#include "ZjnRunActionAll.hh"
#include"ZjnPrimaryGeneratorActionAll.hh"

#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4ParticleTable.hh>
#include <globals.hh>

#include <G4RunManager.hh>
#include <G4GeneralParticleSource.hh>
#include <G4RootAnalysisManager.hh>
#include <G4DigiManager.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

wuEventActionAll::wuEventActionAll()
{
}

wuEventActionAll::~wuEventActionAll()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void wuEventActionAll::BeginOfEventAction(const G4Event* /*anEvent*/)
{
  Edep = 0; 
}

void wuEventActionAll::EndOfEventAction(const G4Event* /*anEvent*/)
{
	int EventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID(); 
	if(EventID % 1000000 == 0)	G4cout << EventID << G4endl; 

  const ZjnPrimaryGeneratorActionAll* GeneratorAction = static_cast<const ZjnPrimaryGeneratorActionAll*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()); 

  G4VAnalysisManager* analysisManager = G4RootAnalysisManager::Instance(); 
	analysisManager->FillNtupleIColumn(0, EventID); 
	analysisManager->FillNtupleDColumn(1, Edep); 

	analysisManager->AddNtupleRow();	//相当于 Fill
}
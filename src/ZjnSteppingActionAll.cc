#include "ZjnSteppingActionAll.hh"
#include "ZjnRunActionAll.hh"

#include <G4Run.hh>
#include <G4TrackVector.hh>
#include <G4SteppingManager.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4CsvAnalysisManager.hh>
#include <G4XmlAnalysisManager.hh>
#include <G4RootAnalysisManager.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
wuSteppingActionAll::wuSteppingActionAll(wuEventActionAll* feventAction)
 : G4UserSteppingAction(), eventAction(feventAction)
{	
	analysisManager = G4RootAnalysisManager::Instance(); 
}

wuSteppingActionAll::~wuSteppingActionAll()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void wuSteppingActionAll::UserSteppingAction(const G4Step* step)
{
	G4StepPoint* preStepPoint = step->GetPreStepPoint();//获取数据接口
	G4StepPoint* postStepPoint = step->GetPostStepPoint();//获取数据接口

	if(postStepPoint->GetPhysicalVolume())//判断是否在world外
	{
		G4String ParticalName = step -> GetTrack() -> GetDefinition() -> GetParticleName(); 
		if(preStepPoint->GetPhysicalVolume()->GetName() == "LaBr3Scintillor")
		{
			if(ParticalName != "opticalphoton")
			{
				eventAction -> Edep += step -> GetTotalEnergyDeposit(); 
			}
		}
		if(ParticalName == "opticalphoton")
		{
			G4VAnalysisManager* analysisManager = G4RootAnalysisManager::Instance(); 
			analysisManager -> FillNtupleIColumn(0, G4EventManager::GetEventManager()->GetConstCurrentEvent() -> GetEventID()); 
			analysisManager -> FillNtupleDColumn(1, 0); 

			analysisManager -> AddNtupleRow();	//相当于 Fill
		}
		//else if(preStepPoint->GetPhysicalVolume()->GetName() == "SiDetector" && ParticalName == "opticalphoton")
		//// else if(ParticalName == "opticalphoton")
		//{
		//	G4VAnalysisManager* analysisManager = G4RootAnalysisManager::Instance(); 
		//	analysisManager -> FillNtupleIColumn(0, G4EventManager::GetEventManager()->GetConstCurrentEvent() -> GetEventID()); 
		//	// analysisManager -> FillNtupleDColumn(1, postStepPoint -> GetGlobalTime() / ns); 
		//	analysisManager -> FillNtupleDColumn(1, 0); 

		//	analysisManager -> AddNtupleRow();	//相当于 Fill
		//	step -> GetTrack() -> SetTrackStatus(fStopAndKill); 
		//}
	}
}
// wuSteppingActionAll.cc ends here
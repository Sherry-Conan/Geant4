#include "ZjnActionInitialization.hh"

#include "ZjnRunActionAll.hh"
#include "ZjnEventActionAll.hh"
#include "ZjnTrackingActionAll.hh"
#include "ZjnSteppingActionAll.hh"
#include "ZjnStackingActionAll.hh"
#include "ZjnPrimaryGeneratorActionAll.hh"


#include <G4Version.hh>

#include <G4MultiRunAction.hh>
#include <G4MultiEventAction.hh>
#include <G4MultiTrackingAction.hh>
#include <G4MultiSteppingAction.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

wuActionInitialization::wuActionInitialization()
 : G4VUserActionInitialization()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

wuActionInitialization::~wuActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void wuActionInitialization::BuildForMaster() const
{
  SetUserAction(new ZjnRunActionAll); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void wuActionInitialization::Build() const
{
  //源的设置
  SetUserAction(new ZjnPrimaryGeneratorActionAll);

  
#if G4VERSION_NUMBER >= 1030
  
  G4MultiRunAction* actsRun = new G4MultiRunAction;
  G4MultiEventAction* actsEvent = new G4MultiEventAction;
  G4MultiTrackingAction* actsTrack = new G4MultiTrackingAction;
  G4MultiSteppingAction* actsStep = new G4MultiSteppingAction;
  
  //...0123456789876543210...0123456789876543210...

  actsRun->push_back(G4UserRunActionUPtr(new ZjnRunActionAll));
  wuEventActionAll* eventAction = new wuEventActionAll(); 
  actsEvent->push_back(G4UserEventActionUPtr(eventAction));
  actsTrack->push_back(G4UserTrackingActionUPtr(new wuTrackingActionAll));
  actsStep->push_back(G4UserSteppingActionUPtr(new wuSteppingActionAll(eventAction))); 
  
  SetUserAction(new wuStackingActionAll);


  //...0123456789876543210...0123456789876543210...
  
  SetUserAction(actsRun);
  SetUserAction(actsTrack);
  SetUserAction(actsEvent);
  SetUserAction(actsStep);
  
#else

  G4cout<<"It need G4VERSION_NUMBER >= 1030"<<G4endl;
  
#endif 

}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 
// wuActionInitialization.cc ends here

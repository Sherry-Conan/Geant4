#include "ZjnStackingActionAll.hh"

#include <G4Track.hh>
#include <G4ios.hh>
#include <G4ParticleTable.hh>
#include <globals.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

wuStackingActionAll::wuStackingActionAll()
  : G4UserStackingAction()
{

}

wuStackingActionAll::~wuStackingActionAll()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack wuStackingActionAll::ClassifyNewTrack(const G4Track* /*aTrack*/)
{


  return fUrgent;
}

void wuStackingActionAll::NewStage()
{

}
  
void wuStackingActionAll::PrepareNewEvent()
{

}
  
// 
// wuStackingActionAll.cc ends here

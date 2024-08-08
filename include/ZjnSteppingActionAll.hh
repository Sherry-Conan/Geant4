#ifndef _ZJNSTEPPINGACTIONALL_H_
#define _ZJNSTEPPINGACTIONALL_H_

#include "G4UserSteppingAction.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include "ZjnEventActionAll.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4VAnalysisManager;

class wuSteppingActionAll : public G4UserSteppingAction
{
public:
  wuSteppingActionAll(wuEventActionAll* feventAction); 
  virtual ~wuSteppingActionAll();

public:
  virtual void UserSteppingAction(const G4Step* step);
  wuEventActionAll* eventAction = nullptr; 
private:
  G4VAnalysisManager* analysisManager; 
};

// enum G4StepStatus
// {
//   fWorldBoundary,// Step reached the world boundary
//   fGeomBoundary,// Step defined by a geometry boundary
//   fAtRestDoItProc,// Step defined by a PreStepDoItVector
//   fAlongStepDoItProc,// Step defined by a AlongStepDoItVector
//   fPostStepDoItProc,// Step defined by a PostStepDoItVector
//   fUserDefinedLimit,// Step defined by the user Step limit in the logical volume
//   fExclusivelyForcedProc,// Step defined by an exclusively forced PostStepDoIt process 
//   fUndefined// Step not defined yet
// };

// enum G4SteppingControl  
// {
//   NormalCondition,
//   AvoidHitInvocation,// Hit will NOT be called 
//   Debug
// };


#endif
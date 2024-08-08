#ifndef _WUEVENTACTIONALL_H_
#define _WUEVENTACTIONALL_H_

#include <G4UserEventAction.hh>
#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4ios.hh>
#include <G4VAnalysisManager.hh>

#include <G4HCofThisEvent.hh>
#include <G4VHitsCollection.hh>
#include <G4SDManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//  This is the base class of one of the user's optional action classes.
// The two methods BeginOfEventAction() and EndOfEventAction() are invoked
// at the beginning and the end of one event processing. These methods are
// invoked by G4EventManager.
//  Be aware that BeginOfEventAction() is invoked when a G4Event object is
// sent to G4EventManager. Thus the primary vertexes/particles have already
// been made by the primary generator. In case the user wants to do something
// before generating primaries (i.e., store random number status), do it in
// the G4VUserPrimaryGeneratorAction concrete class.

class wuEventActionAll : public G4UserEventAction
{
public:
  wuEventActionAll(); 
  virtual ~wuEventActionAll(); 

public: // with description
  virtual void BeginOfEventAction(const G4Event* anEvent); 
  virtual void EndOfEventAction(const G4Event* anEvent); 

  G4double Edep; 

private:
};

#endif
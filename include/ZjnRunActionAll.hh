#ifndef _ZjnRUNACTIONALL_H_
#define _ZjnRUNACTIONALL_H_

//  The user's concrete class derived from this class must be set to
// G4RunManager via G4RunManager::SetUserAction() method.

#include <G4UserRunAction.hh>
#include "globals.hh"
#include <cstring>
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4VAnalysisManager;
class G4Run;

class ZjnRunActionAll : public G4UserRunAction
{
public:
  ZjnRunActionAll();
  virtual ~ZjnRunActionAll();

public:
  // The user can override the following method to instanciate his/her own
  // concrete Run class. G4Run has a virtual method RecordEvent, so that
  // the user can store any information useful to him/her with event statistics.
  //    virtual G4Run* GenerateRun();  
  virtual G4Run* GenerateRun(); 

  //  This is the base class of a user's action class which defines the
  // user's action at the begining and the end of each run. The user can
  // override the following two methods but the user should not change 
  // any of the contents of G4Run object.  
  virtual void BeginOfRunAction(const G4Run* aRun);
  virtual void EndOfRunAction(const G4Run* aRun);

  G4String FileName = "WaveForm"; 

private:
  G4VAnalysisManager* analysisManager;
  
};

#endif /* _ZjnRUNACTIONALL_H_ */
// 
// ZjnRunActionAll.hh ends here

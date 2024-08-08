#ifndef _ZJNACTIONINITIALIZATION_H_
#define _ZJNACTIONINITIALIZATION_H_

#include <G4VUserActionInitialization.hh>

/// Action initialization class.
class wuActionInitialization : public G4VUserActionInitialization
{
public:
  wuActionInitialization();
  virtual ~wuActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

};

#endif

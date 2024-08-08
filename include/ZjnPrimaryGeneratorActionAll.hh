#ifndef _ZJNPRIMARYGENERATORACTIONALL_H_
#define _ZJNPRIMARYGENERATORACTIONALL_H_

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "Randomize.hh"//随机数这里产生
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleMomentum.hh"
#include "G4ThreeVector.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// This is the base class of the user's mandatory action class for primary vertex/particle generation.
// This class  GeneratePrimaries() which is invoked from G4RunManager during the event loop.
//  Note that this class is NOT intended for generating primary vertex/particle
// by itself. This class should 
//  - have one or more G4VPrimaryGenerator concrete classes such as G4ParticleGun 
//  - set/change properties of generator(s)
//  - pass G4Event object so that the generator(s) can generate primaries.

class ZjnPrimaryGeneratorActionAll : public G4VUserPrimaryGeneratorAction
{
public:
  ZjnPrimaryGeneratorActionAll();
  virtual ~ZjnPrimaryGeneratorActionAll();


public:

  // Creates a primary vertex at the given point and put primary particles to it.
  //   SetParticleDefinition should be called first.  
  //   By using SetParticleMomentum(), both particle_momentum_direction and
  //   particle_energy(Kinetic Energy) are set.
  virtual void GeneratePrimaries(G4Event* anEvent);//将G4PrimaryVertex压入G4Event

  // user define
private:
  G4ParticleGun* ParticleGun;//继承G4VPrimaryGenerator
  G4double Position = 0; 

public:
  G4double GetParticleEnergy() const{
    return ParticleGun -> GetParticleEnergy(); 
  }
  G4double GetParticlePosition() const{
    return Position; 
  }
};

#endif
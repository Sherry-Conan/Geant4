#include "ZjnG4Run.hh"

#include <G4ParticleDefinition.hh>
#include <G4UnitsTable.hh>

ZjnG4Run::ZjnG4Run()
  : G4Run()
{
  fParticle             = nullptr; 
  fEnergy               = -1.; 
  fScintillationCounter = 0.; 
  fScintillation2       = 0.; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ZjnG4Run::~ZjnG4Run() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ZjnG4Run::SetPrimary(G4ParticleDefinition* particle, G4double energy)
{
  fParticle = particle;
  fEnergy   = energy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ZjnG4Run::Merge(const G4Run* run)
{
  const ZjnG4Run* localRun = static_cast<const ZjnG4Run*>(run);

  fParticle = localRun->fParticle;
  fEnergy   = localRun->fEnergy;

  fScintillationCounter += localRun->fScintillationCounter; 
  fScintillation2 += localRun->fScintillation2; 

  G4Run::Merge(run); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ZjnG4Run::EndOfRun()
{

}

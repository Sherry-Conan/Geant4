#ifndef _ZjnG4RUN_H_
#define _ZjnG4RUN_H_

#include <G4Run.hh>

class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ZjnG4Run : public G4Run
{
 public:
  ZjnG4Run();
  ~ZjnG4Run();

  void SetPrimary(G4ParticleDefinition* particle, G4double energy);

  void AddScintillation(G4double n)
  {
    fScintillationCounter += n;
    fScintillation2 += n * n;
  };

  void Merge(const G4Run*) override;
  void EndOfRun();

 private:
  G4ParticleDefinition* fParticle;

  G4double fScintillationCounter;
  G4double fScintillation2;

  G4double fEnergy;
};
#endif
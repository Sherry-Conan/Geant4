#include "ZjnPrimaryGeneratorActionAll.hh"

#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ZjnPrimaryGeneratorActionAll::ZjnPrimaryGeneratorActionAll()
  : G4VUserPrimaryGeneratorAction(),ParticleGun(NULL)
{
  ParticleGun = new G4ParticleGun(G4Threading::G4GetNumberOfCores());///*G4int n_particle*/
}

ZjnPrimaryGeneratorActionAll::~ZjnPrimaryGeneratorActionAll()
{
  if(ParticleGun)
    {
      delete ParticleGun;
      ParticleGun =NULL;
    }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ZjnPrimaryGeneratorActionAll::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleTable* ParticleTable = G4ParticleTable::GetParticleTable();
  
  G4ParticleDefinition* pp = 0;

  // -------------------------
  
  //自定义带电粒子
  // G4int IonZ = 1;
  // G4int IonA = 1;
  // G4double IonEstar = 0.0; //exitition energy
  // G4double IonQ = 1;
  // G4cout<<"ion:Z-A-Q-E*"<<IonZ<<" "<<IonA<<" "<<IonQ<<" "<<IonEstar<<G4endl;
  // pp = particleTable->GetIonTable()->GetIon(IonZ, IonA, IonEstar);//4.10.01版本强制 G4IonTable.hh
  // particleGun->SetParticleCharge(IonQ);

  //Geant4已经定义的粒子
  pp = ParticleTable->FindParticle("gamma");

  // -------------------------
  
  if(pp)
    ParticleGun->SetParticleDefinition(pp);
  else
    G4cout<<"##Null pp in ZjnPrimaryGeneratorAction::SetParticleGun()"<<G4endl;

  
  //primary particle kinetic energy
  ParticleGun->SetParticleEnergy(0.662 * MeV); 
  ParticleGun->SetNumberOfParticles(1); //不设默认13个，也可能是线程数。


  // primary particle position
  G4double x = 0.; 
  G4double y = 0.; 
  G4double z = -5 * cm; 

  ParticleGun -> SetParticlePosition(G4ThreeVector(x, y, z)); 

  ParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1.)); 

  ParticleGun->GeneratePrimaryVertex(anEvent); 
}


// 
// wuPrimaryGeneratorActionAll.cc ends here



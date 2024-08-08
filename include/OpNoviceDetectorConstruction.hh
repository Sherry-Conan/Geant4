********************************************************************
//
/// \file OpNovice/include/OpNoviceDetectorConstruction.hh
/// \brief Definition of the OpNoviceDetectorConstruction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef OpNoviceDetectorConstruction_h
#define OpNoviceDetectorConstruction_h 1

#include "globals.hh"
#include <G4VUserDetectorConstruction.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class OpNoviceDetectorMessenger;

class OpNoviceDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  OpNoviceDetectorConstruction();
  ~OpNoviceDetectorConstruction();

  G4VPhysicalVolume* Construct() override;
  void SetDumpGdml(G4bool);
  G4bool IsDumpGdml() const;
  void SetVerbose(G4bool verbose);
  G4bool IsVerbose() const;
  void SetDumpGdmlFile(G4String);
  G4String GetDumpGdmlFile() const;

 private:
  void PrintError(G4String);

  OpNoviceDetectorMessenger* fDetectorMessenger;
  G4String fDumpGdmlFileName;

  G4double WorldRadius = 6 * cm, WorldHeight = 10 * cm; 
  G4double DetectorRadius = 4 * cm, DetectorHeight = 8 * cm; 
  // Al厚度
  G4double AlThick = 0.5 * cm; 
  // LaBr半径
  G4double LaBr3Radius = 1.5 * cm; 

  G4bool fVerbose;
  G4bool fDumpGdml;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*OpNoviceDetectorConstruction_h*/

#include "OpNoviceDetectorConstruction.hh"

#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Element.hh>
//#include <G4GDMLParser.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4OpticalSurface.hh>
#include <G4ThreeVector.hh>

#include <G4NistManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
  : G4VUserDetectorConstruction()
{
  fDumpGdmlFileName = "OpNovice_dump.gdml";
  fVerbose          = false;
  fDumpGdml         = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  // ------------- Materials -------------
  G4double a, z, density; 
  G4int nelements; 

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR"); 
  //
  // LaBr3
  G4Element* La = new G4Element("Lanthanum", "La", 57., 138.91*g/mole); 
	G4Element* Br = new G4Element("Bromine", "Br", 35., 79.904*g/mole); 
  G4Material* LaBr3 = new G4Material("LaBr3", density = 5.06 * g / cm3, nelements = 2);
	LaBr3 -> AddElement(La, 1); 
	LaBr3 -> AddElement(Br, 3); 

  //
  // CsI
  G4Element* Cs = new G4Element("Caesium", "Cs", 55., 126.9 * g / mole); 
	G4Element* I = new G4Element("Iodine", "I", 57., 132.9 * g / mole); 
  G4Material* CsI = new G4Material("CsI", density = 4.51 * g / cm3, nelements = 2); 
	CsI -> AddElement(Cs, 1); 
	CsI -> AddElement(I, 1); 

  G4Material* Al = nist->FindOrBuildMaterial("G4_Al"); 


  // ------------ Generate & Add Material Properties Table ------------
  //
  G4double photonEnergy[2] = {2.034 * eV, 7.0 * eV}; 
  G4double refractiveIndex1[2] = {1.9, 1.9}; 
  G4double absorption[2] = {50. * cm, 50. * cm}; 

  // Material properties can be added as arrays. However, in this case it is
  // up to the user to make sure both arrays have the same number of elements.
  // G4double scintilFastArray[]{ 1.0, 1.0 };
  // G4double energyArray[]{ 2.034 * eV, 4.136 * eV };
  // G4int lenArray = 2; 

  // std::vector<G4double> scintilSlow = {0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00, 3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 5.00, 4.00};

  G4MaterialPropertiesTable* LaBrMPT = new G4MaterialPropertiesTable();

  // Values can be added to the material property table individually.
  // With this method, spline interpolation cannot be set. Arguments
  // createNewKey and spline both take their default values of false.
  // Need to specify the number of entries (1) in the arrays, as an argument
  // to AddProperty.
  G4int numEntries = 2; 
  LaBrMPT->AddProperty("RINDEX", photonEnergy, refractiveIndex1,
                      numEntries); 

  LaBrMPT->AddProperty("ABSLENGTH", photonEnergy, absorption, numEntries); 

  LaBrMPT->AddConstProperty("SCINTILLATIONYIELD", 68. / keV); 
  LaBrMPT->AddConstProperty("RESOLUTIONSCALE", 1.0); 
  LaBrMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 19. * ns);
  LaBrMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 19. * ns);
  //LaBrMPT->AddConstProperty("SCINTILLATIONYIELD1", 0.8);
  //LaBrMPT->AddConstProperty("SCINTILLATIONYIELD2", 0.2); 

  LaBr3->SetMaterialPropertiesTable(LaBrMPT);

  // Check that group velocity is calculated from RINDEX
  if(LaBrMPT->GetProperty("RINDEX")->GetVectorLength() !=
     LaBrMPT->GetProperty("GROUPVEL")->GetVectorLength())
  {
    G4ExceptionDescription ed;
    ed << "Error calculating group velocities. Incorrect number of entries "
          "in group velocity material property vector.";
    G4Exception("OpNovice::OpNoviceDetectorConstruction", "OpNovice001",
                FatalException, ed);
  }

  // Set the Birks Constant for the LaBr3 scintillator
  LaBr3->GetIonisation()->SetBirksConstant(0.126 * mm / MeV); 

  //CsI
  G4double CsIRefractiveIndex[2] = {1.95, 1.95}; 
  G4double CsIAbsorption[2] = {150. * cm, 150. * cm}; 

  G4MaterialPropertiesTable* CsIMPT = new G4MaterialPropertiesTable();

  CsIMPT -> AddProperty("RINDEX", photonEnergy, CsIRefractiveIndex, numEntries); 

  CsIMPT -> AddProperty("ABSLENGTH", photonEnergy, CsIAbsorption, numEntries);

  CsIMPT -> AddConstProperty("SCINTILLATIONYIELD", 35 / keV); 
  CsIMPT -> AddConstProperty("RESOLUTIONSCALE", 1.0); 
  CsIMPT -> AddConstProperty("SCINTILLATIONTIMECONSTANT1", 30. * ns);
  CsIMPT -> AddConstProperty("SCINTILLATIONTIMECONSTANT2", 60. * ns);
  CsIMPT -> AddConstProperty("SCINTILLATIONYIELD1", 0.8);
  CsIMPT -> AddConstProperty("SCINTILLATIONYIELD2", 0.2); 

  CsI -> SetMaterialPropertiesTable(CsIMPT);

  // Set the Birks Constant for the LaBr3 scintillator
  CsI -> GetIonisation() -> SetBirksConstant(0.115 * mm / MeV); 

  // Air
  G4double refractiveIndex2[2] = {1.0, 1.0}; 

  G4MaterialPropertiesTable* AirMPT = new G4MaterialPropertiesTable();
  AirMPT->AddProperty("RINDEX", photonEnergy, refractiveIndex2, numEntries); 

  air->SetMaterialPropertiesTable(AirMPT); 


  // Al and Al2O3

	G4double AlPhotonEnergy[2] = {1.0 * eV, 7.0 * eV}; 
	
	G4double AlRefractionIndex[2] = {1.9,1.9}; 
	
	G4double AlAbsorptionLength[2] = {1.0E-9 * m, 1.0E-9 * m}; 
	
	G4MaterialPropertiesTable* AlMPT = new G4MaterialPropertiesTable(); 
	
	AlMPT->AddProperty("RINDEX", AlPhotonEnergy, AlRefractionIndex, numEntries); 
	AlMPT->AddProperty("ABSLENGTH", AlPhotonEnergy, AlAbsorptionLength, numEntries); 
	
	Al -> SetMaterialPropertiesTable(AlMPT); 



  
  // ------------- Volumes --------------
  //
  // The world
  G4Tubs* WorldTubs = new G4Tubs("World", 0, WorldRadius, WorldHeight / 2, 0., 360. * deg); 
  G4LogicalVolume* WorldLog = new G4LogicalVolume(WorldTubs, air, "World", 0, 0, 0);
  G4VPhysicalVolume* WorldPhys = new G4PVPlacement(
    0, G4ThreeVector(), WorldLog, "world", 0, false, 0, checkOverlaps);

  // The experimental Hall
  G4Tubs* Envelope = new G4Tubs("Envelope", 0, 0.9 * WorldRadius, 0.45 * WorldHeight, 0, 360. * deg);
  G4LogicalVolume* EnvelopeLog = new G4LogicalVolume(Envelope, air, "Envelope", 0, 0, 0);
  G4VPhysicalVolume* Envelope_phys = new G4PVPlacement(0, G4ThreeVector(), EnvelopeLog, "Envelope", WorldLog, false, 0);

	G4Tubs* AlTubs = new G4Tubs("Enclosure", 0., DetectorRadius, DetectorHeight / 2, 0., 360. * deg); 
  G4LogicalVolume* AlLog = new G4LogicalVolume(AlTubs, Al, "Enclosure", 0, 0, 0); 
  G4VPhysicalVolume* AlPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), AlLog, "Enclosure", EnvelopeLog, false, 0); 

  // The CsI
  G4Tubs* CsITubs = new G4Tubs("CsIScintillor", 0., DetectorRadius - AlThick, DetectorHeight / 2 - AlThick, 0., 360. * deg); 
  G4LogicalVolume* CsILog = new G4LogicalVolume(CsITubs, CsI, "CsIScintillor", 0, 0, 0); 
  G4VPhysicalVolume* CsIPhys = new G4PVPlacement(0, G4ThreeVector(), CsILog, "CsIScintillor", AlLog, false, 0); 

  // The LaBr3 
  G4Tubs* LaBr3Tubs = new G4Tubs("LaBr3Scintillor", 0., LaBr3Radius, DetectorHeight / 2 - AlThick, 0., 360. * deg); 
  G4LogicalVolume* LaBr3Log = new G4LogicalVolume(LaBr3Tubs, LaBr3, "LaBr3Scintillor", 0, 0, 0);
  G4VPhysicalVolume* LaBr3Phys = new G4PVPlacement(0, G4ThreeVector(), LaBr3Log, "LaBr3Scintillor", CsILog, false, 0); 

	G4Tubs* SiTubs = new G4Tubs("Si", 0., DetectorRadius - AlThick, AlThick / 2, 0., 360. * deg); 
	G4LogicalVolume* SiLog = new G4LogicalVolume(SiTubs, Al, "Si"); 
	G4VPhysicalVolume* SiPhys = new G4PVPlacement(nullptr, G4ThreeVector(0, 0., (DetectorHeight - AlThick) / 2), SiLog, "SiDetector", AlLog, false, 0, checkOverlaps); 



  // ------------- Surfaces --------------
  // LaBr3Scintillor
  G4OpticalSurface* opSurface = new G4OpticalSurface("Surface"); 
  opSurface -> SetType(dielectric_dielectric);
  opSurface -> SetFinish(polished);
  opSurface -> SetModel(glisur);

  new G4LogicalBorderSurface("LaBr3AndCsISurface", LaBr3Phys, CsIPhys, opSurface); 
  new G4LogicalBorderSurface("LaBr3AndSiSurface", LaBr3Phys, SiPhys, opSurface); 
  new G4LogicalBorderSurface("LaBr3AndAlSurface", LaBr3Phys, AlPhys, opSurface); 
  new G4LogicalBorderSurface("AlAndCsISurface", AlPhys, CsIPhys, opSurface); 

  return WorldPhys; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::SetDumpGdml(G4bool val) { fDumpGdml = val; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool OpNoviceDetectorConstruction::IsDumpGdml() const { return fDumpGdml; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::SetVerbose(G4bool val) { fVerbose = val; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool OpNoviceDetectorConstruction::IsVerbose() const { return fVerbose; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::SetDumpGdmlFile(G4String filename)
{
  fDumpGdmlFileName = filename;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String OpNoviceDetectorConstruction::GetDumpGdmlFile() const
{
  return fDumpGdmlFileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::PrintError(G4String ed)
{
  G4Exception("OpNoviceDetectorConstruction:MaterialProperty test", "op001",
              FatalException, ed);
}

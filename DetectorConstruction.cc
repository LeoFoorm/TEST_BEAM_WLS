//  DETECTOR CONSTRCTION SOURCE


#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include "G4UserLimits.hh"  
using namespace std;

DetectorConstruction::DetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
  fMessenger->DeclareProperty("Test_Beam", Test_Beam, "Construct Test Beam detector");
  fMessenger->DeclareProperty("distance_modules", distance_modules, "The distance between both modules");
  
  DefineMaterials();

  env_sizeX = 4*m;
  env_sizeY = 4*m;
  env_sizeZ = 4*m;

  distance_modules = 10*cm + 1.02*cm;

  Test_Beam = true; 
}


DetectorConstruction::~DetectorConstruction()
{}


void DetectorConstruction::DefineMaterials()
{
  //
  std::vector<G4double> wavelength = {499.83,496.62,491.92,487.22,482.51,477.81,473.10,468.40,463.69,458.99,454.28,449.58,445.30,441.45,438.03,434.18,429.69,425.20,417.03,415.36,414.08,413.22,412.53,411.60,410.66,409.80, 408.53,405.80,402.75,400.18,399.32,397.27,396.33,395.48,394.62,394.28,392.91,392.27,391.41,390.34,389.70,388.42,386.63,384.57,381.58,380.31};
  std::vector<G4double> lightOutput = {2.55,2.56,2.97,3.59,4.40,5.49,6.93,8.52,10.68,13.38,17.07,21.41,26.21,31.27,36.04,40.53,45.23,49.04,53.41,58.78,63.62,68.61,73.05,78.28,83.01,88.07,92.45,96.07,99.46,96.00,91.32,86.66,80.18,73.98,69.53,64.76,58.40,50.56,44.59,38.14,33.28,29.14,23.55,17.68,12.13,6.27,4.06};
  std::vector<G4double> energy;
  std::vector<G4double> RI;
  std::vector<G4double> fraction;
  std::vector<G4double> absSC;
  std::vector<G4double> rindexWorld;
  std::vector<G4double> reflectivity;
  std::vector<G4double> rindexmylar;

  G4double RefIndex=1.58;
  G4double AbsSC = 160.*cm;
  G4double RIWorld = 1.0;
  G4double Reflectivity = 0.9999;
  G4double Rindexmylar = 1.655;


  for (size_t i = 0; i < wavelength.size(); ++i) {

    G4double Energy = 1.239841939 * eV / (wavelength[i] / 1000);

    G4double normalizedLightOutput = lightOutput[i] / 100;

    energy.push_back(Energy);

    fraction.push_back(normalizedLightOutput);

    RI.push_back(RefIndex);

    absSC.push_back(AbsSC);

    rindexWorld.push_back(RIWorld);

    reflectivity.push_back(Reflectivity);

    rindexmylar.push_back(Rindexmylar);
    }
  
  G4int numberOfEntries = energy.size();


  //REQUIRED DATA FOR WLS

  vector<G4double> wavelength_wls = {550.02, 549.98, 548.49, 547.07, 546.86, 545.44, 544.51, 543.31, 542.32, 541.38, 540.26, 538.04, 537.59, 536.95, 535.00, 532.16, 530.67, 528.30, 527.21, 526.37, 525.08, 524.47, 523.50, 522.50, 521.56, 520.19, 518.93, 517.11, 516.07, 515.64, 513.88, 512.76, 511.53, 510.19, 508.43, 505.02, 503.76, 501.05, 500.01, 499.83, 496.62, 491.92, 487.22, 482.51, 476, 473.10, 468.40, 463.69, 458.99, 454.28, 449.58, 445.30, 441.45, 438.03, 434.18, 430, 429.69, 425.20, 417.03, 415.36, 414.08, 413.22, 412.53, 411.60, 410.66, 409.80, 408.53, 405.80, 402.75, 400.18, 399.32, 397.27, 396.33, 395.48, 394.62, 394.28, 392.91, 392.27, 391.41, 390.34, 389.70, 388.42, 386.63, 384.57, 381.58, 380.31};
    vector<G4double> PhotonEnergy;

  for(size_t j = 0; j< wavelength_wls.size(); ++j){
    //G4double energy_wls = 1.239841939 * eV / (wavelength[j] / 1000); // IS THIS RIGHT?
    G4double energy_wls = ( 1.2399728 )/ (wavelength_wls[j]/1000); 
    PhotonEnergy.push_back(energy_wls);
  }
  G4int numOfEnt2 = PhotonEnergy.size();

  vector<G4double> RIndexFiber(86, 1.59);
          
  vector<G4double> AbsFiber (86, 3.5*m);
   //AbsFiber.insert(AbsFiber.end(), 40, 3.5*m);
      
  vector<G4double> EmissionFiber(17, 2.0);
   EmissionFiber.insert(EmissionFiber.end(), 18, 5.0);
   EmissionFiber.insert(EmissionFiber.end(), 11, 10.0); //<--
   EmissionFiber.insert(EmissionFiber.end(), 40, 0.2); //<--

  /*vector<G4double> AbsFiber (40, 0.01*m);
   AbsFiber.insert(AbsFiber.end(), 45, 3.51*m);
      
  vector<G4double> EmissionFiber(40, 0.0);
   EmissionFiber.insert(EmissionFiber.end(), 11, 10.0);
   EmissionFiber.insert(EmissionFiber.end(), 17, 5.0); //<--
   EmissionFiber.insert(EmissionFiber.end(), 17, 2.0); //<--*/

  /*G4cout << "(SIZE) PhotonEnergy: " << PhotonEnergy.size() << G4endl;
  G4cout << "(SIZE) RIndex : " << RIndexFiber.size() << "\n";
  G4cout << "(SIZE) Absortion length: " << AbsFiber.size() << "\n";
  G4cout << "(SIZE) Emmision prob: " << EmissionFiber.size() << "\n";*/


  for(size_t k = 0; k<wavelength_wls.size(); ++k){
    G4cout << k << "(ELEMENTS) Photon Energy : " << PhotonEnergy[k] << " eV  \n";
  }

  /*for(size_t k = 0; k<wavelength_wls.size(); ++k){
    G4cout << k << "(ELEMENTS) Absortion length: " << AbsFiber[k]/m<< "\n";
  }

  for(size_t k = 0; k<wavelength_wls.size(); ++k){
    G4cout << k << "(ELEMENTS) Emmision prob: " << EmissionFiber[k]<< "\n";
  }*/

    
  

 G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true); 

 G4NistManager *nist = G4NistManager::Instance();
 worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
 plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 mylarMaterial = nist->FindOrBuildMaterial("G4_MYLAR");
 steel = nist->FindOrBuildMaterial("G4_Fe");

 //WLS CHARATERISTICS - CORE: (PS)
 fiber_core = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

 mirrorsurface = new G4OpticalSurface("mirrorsurface");

 mirrorsurface->SetType(dielectric_dielectric);
 mirrorsurface->SetFinish(polishedfrontpainted);
 mirrorsurface->SetModel(unified);

 G4MaterialPropertiesTable *mirror=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *prop=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propworld=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propmylar=new G4MaterialPropertiesTable();

G4MaterialPropertiesTable *propfiber=new G4MaterialPropertiesTable();
 

 propworld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
 prop->AddProperty("RINDEX",energy, RI,numberOfEntries);
 prop->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
 prop->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
 prop->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns);
 prop->AddConstProperty("SCINTILLATIONYIELD", 10.666666/keV);  //10.666666/keV
 prop->AddConstProperty("RESOLUTIONSCALE", 1.); 
 prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
 mirror->AddProperty("REFLECTIVITY", energy, reflectivity);
 propmylar->AddProperty("RINDEX",energy, rindexmylar,numberOfEntries);


propfiber->AddProperty("RINDEX", PhotonEnergy, RIndexFiber, numOfEnt2);
propfiber->AddProperty("WLSABSLENGTH", PhotonEnergy, AbsFiber, numOfEnt2);
propfiber->AddProperty("WLSCOMPONENT", PhotonEnergy, EmissionFiber, numOfEnt2);
propfiber->AddConstProperty("WLSTIMECONSTANT", 1.0*ns);

propfiber->AddConstProperty("WLSABSLENGTHMAX", 2.883657674*eV, true); // Absorption peak
propfiber->AddConstProperty("WLSCOMPONENTMAX", 2.604984874*eV, true); // Emission peak


 worldMaterial->SetMaterialPropertiesTable(propworld);
 plastic->SetMaterialPropertiesTable(prop);
 mirrorsurface->SetMaterialPropertiesTable(mirror);
 mylarMaterial->SetMaterialPropertiesTable(propmylar);

fiber_core->SetMaterialPropertiesTable(propfiber);

}


void DetectorConstruction::ConstructTESTBEAM()
{
  //                     BAR 
  G4double bar_X = 2.5*cm;
  G4double bar_Y = 0.5*cm;
  G4double bar_Z = 50*cm;
  
  Solidbar = new G4Box("Solidbar", bar_X, bar_Y, bar_Z );


//                        SiPM 
  G4double sipm_X = 0.3*cm;
  G4double sipm_Y = 0.3*cm;
  G4double sipm_Z = 0.005*cm;
  
  Solidsipm = new G4Box("Solidsipm", sipm_X, sipm_Y, sipm_Z );


//                      WINDOW
  G4double window_x = 0.05*cm;
  G4double window_y = 0.15*cm;
  G4double window_z = 0.0005*cm; 
  window = new G4Box("solid_Hole", window_x, window_y, window_z);

  //the position is relative to the first volume 
  G4double wind_pos_x = -2.496*cm; //<-- -2.5
  G4double wind_pos_y = 0*cm;
  G4double wind_pos_z = 50.0005*cm; //<--
  G4ThreeVector window_pos(wind_pos_x, wind_pos_y, wind_pos_z);



  //                     MYLAR
  G4double mylar_x = 2.551*cm;
  G4double mylar_y = 0.51*cm;
  G4double mylar_z = 50.001*cm;
 Solidmylar = new G4Box("Solidmylar", mylar_x, mylar_y, mylar_z);
 SolidInnermylar = new G4Box("SolidInnermylar", mylar_x - 0.001*cm, mylar_y - 0.001*cm, mylar_z - 0.001*cm); 

 G4SubtractionSolid* hollowMylarBox = new G4SubtractionSolid("HollowMylarBox", Solidmylar, SolidInnermylar);

G4SubtractionSolid* Mylar_With_Hole = new G4SubtractionSolid("Mylar_With_Hole", hollowMylarBox, window, 0, window_pos);

//Logicmylar = new G4LogicalVolume(hollowMylarBox, mylarMaterial, "Logicmylar");
 Logicmylar = new G4LogicalVolume(Mylar_With_Hole, mylarMaterial, "Logicmylar");
 G4LogicalSkinSurface *skin= new G4LogicalSkinSurface("skin", Logicmylar, mirrorsurface); 


//                      FIBER
  G4double innerRadius = 0.*cm;
  G4double outerRadius = 0.05*cm; // 1 mm diameter, 0.5 mm radius.
  G4double hz = 50.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

 Solid_fiber = new G4Tubs("FIBER", innerRadius, outerRadius, hz, startAngle, spanningAngle);



//----------------  2 SCINTILLATION BARS A  ---------------- 
  
  for (G4int i = 0; i < 2; i++)
  { 

  Logicbar_A = new G4LogicalVolume(Solidbar, plastic, "Logicbar_A_"+std::to_string(i));
  LogicBars_A.push_back(Logicbar_A);
  fScoringVolumes_A.push_back(Logicbar_A);


  Physical_MID_A = new  G4PVPlacement(0, G4ThreeVector(-2.5 * cm + (5.102*i) * cm, 0, 0),
                                   Logicbar_A, "Physical_MID_A", LogicWorld, false, i, true);
  }


//             2 SiPM A 

 for (G4int j = 0; j<2; j++)
 {
  Logicsipm_A= new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm_A_"+std::to_string(j));
  LogicSiPMs_A.push_back(Logicsipm_A);

  Physical_SiPM_MID_A = new  G4PVPlacement(0, G4ThreeVector(-4.8 * cm + (5.101*j) * cm, 0, 50.006*cm),
                                   Logicsipm_A, "Physical_SiPM_MID_A", LogicWorld, false, j, true);
 }


//            2 MYLAR A 
  for(G4int k = 0; k<2; k++)
  {
  Physical_Mylar_MID_A = new  G4PVPlacement(0, G4ThreeVector(-2.55 * cm + (5.102*k) * cm, 0, 0),
                                    Logicmylar, "Physical_Mylar_MID_A_with_hole", LogicWorld, false, k, true);
  }


//            6 FIBERS A 

for (G4int l = 0; l < 2; l++)
 {
  Logic_Fiber_A= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_A_"+std::to_string(l));
  Logic_Fibers_A.push_back(Logic_Fiber_A);

  Physical_Fiber_A = new  G4PVPlacement(0, G4ThreeVector(-5.05 * cm + (5.102*l) * cm, 0, 0),
                                   Logic_Fiber_A, "Physical_Fiber_A_middle", LogicWorld, false, l, true);
 }
 for (G4int l = 0; l < 2; l++)
 {
  Logic_Fiber_A= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_A_"+std::to_string(l));
  Logic_Fibers_A.push_back(Logic_Fiber_A);

  Physical_Fiber_A = new  G4PVPlacement(0, G4ThreeVector(-5.05 * cm + (5.102*l) * cm, 0.1 * cm, 0),
                                   Logic_Fiber_A, "Physical_Fiber_A_up", LogicWorld, false, l, true);
 }
 for (G4int l = 0; l < 2; l++)
 {
  Logic_Fiber_A= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_A_"+std::to_string(l));
  Logic_Fibers_A.push_back(Logic_Fiber_A);

  Physical_Fiber_A = new  G4PVPlacement(0, G4ThreeVector(-5.05 * cm + (5.102*l) * cm, - 0.1 * cm, 0),
                                   Logic_Fiber_A, "Physical_Fiber_A_down", LogicWorld, false, l, true);
 }

// ==== ADD STEP LIMITS FOR FIBERS A ====
G4double maxStep = 1.0 * mm;
G4UserLimits* fiberStepLimit = new G4UserLimits(maxStep);
for (auto& fiberLogic : Logic_Fibers_A) {
    fiberLogic->SetUserLimits(fiberStepLimit);
}




//---------------- 3 SCINTILLATION BARS B  -----------------------------
  G4RotationMatrix* rotationY = new G4RotationMatrix(); 
  rotationY->rotateY(90*deg);

  /*for (G4int l = 0; l < 3; l++)
  {
  Logicbar_B = new G4LogicalVolume(Solidbar, plastic, "Logicbar_B_"+std::to_string(l));
  LogicBars_B.push_back(Logicbar_B);
  fScoringVolumes_B.push_back(Logicbar_B);

  Physical_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector( 0, distance_modules, -5.052 * cm + (5.102*l) * cm),
                                   Logicbar_B, "Physical_MID_B", LogicWorld, false, l+2, true);
  }


//             3 SiPM B 
 for (G4int m = 0; m < 3; m++)
 {
  Logicsipm_B= new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm_B_"+std::to_string(m));
  LogicSiPMs_B.push_back(Logicsipm_B);
  
  Physical_SiPM_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(-50.006*cm, distance_modules,  -7.353 * cm + (5.102*m) * cm),
                                   Logicsipm_B, "Physical_SiPM_MID_B", LogicWorld, false, m+2, true);
 }


//             3 MYLAR B  
  for(G4int n = 0; n < 3; n++)
  {
  Physical_Mylar_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules, -5.102 * cm + (5.102*n) * cm),
                                   Logicmylar, "Physical_Mylar_MID_B", LogicWorld, false, n+2, true);
  }


//            9 FIBERS B 

for (G4int l = 0; l < 3; l++)
 {
  Logic_Fiber_B= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_B_"+std::to_string(l));
  Logic_Fibers_B.push_back(Logic_Fiber_B);

  Physical_Fiber_B = new  G4PVPlacement(rotationY, G4ThreeVector( 0, distance_modules,  -7.602 * cm + (5.102*l) * cm),
                                   Logic_Fiber_B, "Physical_Fiber_B_middle", LogicWorld, false, l+2, true);
 }

 for (G4int l = 0; l < 3; l++)
 {
  Logic_Fiber_B= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_B_"+std::to_string(l));
  Logic_Fibers_B.push_back(Logic_Fiber_B);

  Physical_Fiber_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules + 0.1 * cm,  -7.602 * cm + (5.102*l) * cm),
                                   Logic_Fiber_B, "Physical_Fiber_B_up", LogicWorld, false, l, true);
 }

 for (G4int l = 0; l < 3; l++)
 {
  Logic_Fiber_B= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_B_"+std::to_string(l));
  Logic_Fibers_B.push_back(Logic_Fiber_B);

  Physical_Fiber_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules - 0.1 * cm,  -7.602 * cm + (5.102*l) * cm),
                                   Logic_Fiber_B, "Physical_Fiber_B_down", LogicWorld, false, l, true);
 }*/

   

  //---------------  STEEL-ABSORBER  ---------------

  G4double SA_X = 50*cm;
  G4double SA_Y = 30*cm;
  G4double SA_Z = 50*cm;

  G4ThreeVector  positionSA = G4ThreeVector(0, 138.86*cm, 0);

  SolidSA = new G4Box("SolidSA", SA_X, SA_Y, SA_Z );
  LogicalSA = new G4LogicalVolume(SolidSA, steel, "LogicSA");
  PhysicalSA = new G4PVPlacement(0, positionSA, LogicalSA, "PhysicalSA", LogicWorld, false, 5, true);


  //---------------       TRIGGERS    --------------- 
   
   //                     SCINTILLATOR 1 & 2  
  /*G4double Finger_Trigger_X = 0.5*cm;
  G4double Finger_Trigger_Y = 0.5*cm;
  G4double Finger_Trigger_Z = 2.5*cm;
  
  SolidFingerTrigger = new G4Box("SolidFingerTrigger", Finger_Trigger_X, Finger_Trigger_Y, Finger_Trigger_Z );
  LogicFingerTrigger1 = new G4LogicalVolume(SolidFingerTrigger, plastic, "LogicFingerTrigger1");
  ScoringVolume_Trigger_1 = LogicFingerTrigger1;

  LogicFingerTrigger2 = new G4LogicalVolume(SolidFingerTrigger, plastic, "LogicFingerTrigger2");
  ScoringVolume_Trigger_2 = LogicFingerTrigger2;



//                        MYLAR 1 & 2 
 G4double mylarTrigger_x = 0.52*cm;
 G4double mylarTrigger_y = 0.52*cm;
 G4double mylarTrigger_z = 2.52*cm;
 SolidMylarTrigger1_2 = new G4Box("SolidMylarTrigger1_2", mylarTrigger_x, mylarTrigger_y, mylarTrigger_z);
 SolidMylarTrigger1_2_Inner = new G4Box("SolidMylarTrigger1_2_Inner", mylarTrigger_x-0.01*cm, mylarTrigger_y-0.01*cm, mylarTrigger_z-0.01*cm);
 G4SubtractionSolid* hollowMylarTrigger = new G4SubtractionSolid("HollowMylarTrigger", SolidMylarTrigger1_2, SolidMylarTrigger1_2_Inner);

 Logicmylar_Trigger_1_2 = new G4LogicalVolume(hollowMylarTrigger, mylarMaterial, "Logicmylar_Trigger_1_2");
 G4LogicalSkinSurface *skin2= new G4LogicalSkinSurface("skin2", Logicmylar_Trigger_1_2, mirrorsurface); 


//                        POSITION 1 & 2 

G4ThreeVector PosTrigger1 = G4ThreeVector(0, 280*cm, 0);
PhysicalTrigger1 = new G4PVPlacement(0, PosTrigger1, LogicFingerTrigger1, "PhysicalTrigger1", LogicWorld, false, 6, true);

G4ThreeVector PosTrigger2 = G4ThreeVector(0, 277*cm, 0);
PhysicalTrigger2 = new G4PVPlacement(rotationY, PosTrigger2, LogicFingerTrigger2, "PhysicalTrigger2", LogicWorld, false, 7, true);


Physical_Mylar_Trigger1 = new  G4PVPlacement(0, PosTrigger1,
                                    Logicmylar_Trigger_1_2, "Physical_Mylar_Trigger1", LogicWorld, false, 6, true);
                                    
Physical_Mylar_Trigger2 = new  G4PVPlacement(rotationY, PosTrigger2,
                                    Logicmylar_Trigger_1_2, "Physical_Mylar_Trigger2", LogicWorld, false, 7, true);


//                     SCINTILLATOR 3
  G4double Trigger_3_X = 3.5*cm;
  G4double Trigger_3_Y = 0.5*cm;
  G4double Trigger_3_Z = 2.5*cm;
  
  SolidTrigger_3 = new G4Box("SolidTrigger_3", Trigger_3_X, Trigger_3_Y, Trigger_3_Z );
  LogicTrigger_3 = new G4LogicalVolume(SolidTrigger_3, plastic, "LogicTrigger_3");
  ScoringVolume_Trigger_3 = LogicTrigger_3;

//                        MYLAR 3 
 G4double mylarTrigger_x3 = 3.52*cm;
 G4double mylarTrigger_y3 = 0.52*cm;
 G4double mylarTrigger_z3 = 2.52*cm;
 SolidMylarTrigger_3 = new G4Box("SolidMylarTrigger_3", mylarTrigger_x3, mylarTrigger_y3, mylarTrigger_z3);
 SolidMylarTrigger_3_Inner = new G4Box("SolidMylarTrigger_3_Inner", mylarTrigger_x3-0.01*cm, mylarTrigger_y3-0.01*cm, mylarTrigger_z3-0.01*cm);
 G4SubtractionSolid* hollowMylarTrigger_3 = new G4SubtractionSolid("HollowMylarTrigger_3", SolidMylarTrigger_3, SolidMylarTrigger_3_Inner);

 Logicmylar_Trigger_3 = new G4LogicalVolume(hollowMylarTrigger_3, mylarMaterial, "Logicmylar_Trigger_3");
 G4LogicalSkinSurface *skin3= new G4LogicalSkinSurface("skin3", Logicmylar_Trigger_3, mirrorsurface); 

//                        POSITION 3 

G4ThreeVector PosTrigger3 = G4ThreeVector(0, 274*cm, 0);
PhysicalTrigger3 = new G4PVPlacement(0, PosTrigger3, LogicTrigger_3, "PhysicalTrigger3", LogicWorld, false, 8, true);

Physical_Mylar_Trigger3 = new  G4PVPlacement(0, PosTrigger3,
                                    Logicmylar_Trigger_3, "Physical_Mylar_Trigger3", LogicWorld, false, 8, true);
                                    


//                     SCINTILLATOR 4
  G4double Trigger_4_X = 1*cm;
  G4double Trigger_4_Y = 1*cm;
  G4double Trigger_4_Z = 1*cm;
  
  SolidTrigger_4 = new G4Box("SolidTrigger_4", Trigger_4_X, Trigger_4_Y, Trigger_4_Z );
  LogicTrigger_4 = new G4LogicalVolume(SolidTrigger_4, plastic, "LogicTrigger_4");

   ScoringVolume_Trigger_4 = LogicTrigger_4;

//                        MYLAR 4 
 G4double mylarTrigger_x4 = 1.02*cm;
 G4double mylarTrigger_y4 = 1.02*cm;
 G4double mylarTrigger_z4 = 1.02*cm;
 SolidMylarTrigger_4 = new G4Box("SolidMylarTrigger_4", mylarTrigger_x4, mylarTrigger_y4, mylarTrigger_z4);
 SolidMylarTrigger_4_Inner = new G4Box("SolidMylarTrigger_4_Inner", mylarTrigger_x4-0.01*cm, mylarTrigger_y4-0.01*cm, mylarTrigger_z4-0.01*cm);
 G4SubtractionSolid* hollowMylarTrigger_4 = new G4SubtractionSolid("HollowMylarTrigger_4", SolidMylarTrigger_4, SolidMylarTrigger_4_Inner);

 Logicmylar_Trigger_4 = new G4LogicalVolume(hollowMylarTrigger_4, mylarMaterial, "Logicmylar_Trigger_4");
 G4LogicalSkinSurface *skin4= new G4LogicalSkinSurface("skin4", Logicmylar_Trigger_4, mirrorsurface); 

//                        POSITION 4 

G4ThreeVector PosTrigger4 = G4ThreeVector(0, 217.36*cm, 0);
PhysicalTrigger4 = new G4PVPlacement(0, PosTrigger4, LogicTrigger_4, "PhysicalTrigger4", LogicWorld, false, 9, true);

Physical_Mylar_Trigger4= new  G4PVPlacement(0, PosTrigger4,
                                    Logicmylar_Trigger_4, "Physical_Mylar_Trigger4", LogicWorld, false, 9, true);*/



//              CUBE TO B FIELD
  /*G4double BcubeX = 4.9 * m;
  G4double BcubeY = 1.9921 * m;
  G4double BcubeZ = 4.9 * m;

  G4ThreeVector positioncube = G4ThreeVector(0, 3.0077 * m, 0);
  SolidCube = new G4Box("SolidCube", BcubeX, BcubeY, BcubeZ);*/
  //LogicCube = new G4LogicalVolume(SolidCube, worldMaterial, "LogicCube");
 //PhysicalCube = new G4PVPlacement(0, positioncube, LogicCube, "PhysicalCube", LogicWorld, false, 0, true);

}



G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // Solid world
  SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);
  
  //logical
  LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);


  if (Test_Beam)
   ConstructTESTBEAM(); 

  return PhysicalWorld; 
}


void DetectorConstruction::ConstructSDandField()
{
 SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
 // Assign sensitive detector to all SiPMs in Set A
    for (auto& logicSiPM_aasignment_a : LogicSiPMs_A) {
        logicSiPM_aasignment_a->SetSensitiveDetector(sensDet);
    }

    // Assign sensitive detector to all SiPMs in Set B
    for (auto& logicSiPM_aasignment_b : LogicSiPMs_B) {
        logicSiPM_aasignment_b->SetSensitiveDetector(sensDet);
    }
  

  G4MagneticField *magField;
  G4ThreeVector BField = G4ThreeVector(0., 0., 5.0 *kilogauss);
  magField = new G4UniformMagField(BField);

  G4FieldManager* FieldMngr = new G4FieldManager(magField);
  //FieldMngr->SetDetectorField(magField);
  //FieldMngr->CreateChordFinder(magField);
  //LogicCube->SetFieldManager(FieldMngr,true); 
  
}


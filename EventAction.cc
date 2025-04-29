//   EVENT ACTION SOURCE

#include "EventAction.hh" 
#include <vector>
using namespace std;


EventAction::EventAction(RunAction*) : photonHits_event_A(2, 0), photonHits_event_B(3, 0)
{
fEdepA.resize(2, 0.0); // Initialize with 20 bars, all values set to 0
fEdepB.resize(3, 0.0); // Initialize with 20 bars, all values set to 0

fTotaldEdx_A.resize(2, 0.0);
fTotaldEdx_B.resize(3, 0.0);

fGenerated_photons_A.resize(2, 0.0);
fGenerated_photons_B.resize(3, 0.0);

muonCount = 0;

    traversed_Bars_A.clear();
    traversed_Bars_B.clear();

    Hit = false;
    Sumcopies = 0;

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;

    Trig_1 = 0;
    Trig_2 = 0;
    Trig_3 = 0;
    Trig_4 = 0;
    all_triggers_work = false;

    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();

    particles_names_A.clear();
    particles_names_B.clear();
    
}


EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event*) 
{
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 

    photonHits_event_A.assign(2, 0);
    photonHits_event_B.assign(3, 0);
    
    fEdepA.assign(2, 0.0); 
    fEdepB.assign(3, 0.0); 

    fTotaldEdx_A.assign(2, 0.0);
    fTotaldEdx_B.assign(3, 0.0);

    fGenerated_photons_A.assign(2, 0.0);
    fGenerated_photons_B.assign(3, 0.0);

 muonCount++;
 G4cout << "EVENT ID: "  << muonCount << G4endl;
 G4cout << "------------------------------------------------------------" << G4endl;


    traversed_Bars_A.clear();
    traversed_Bars_B.clear();  

    Hit = false;
    Sumcopies = 0;    

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;

    Trig_1 = 0;
    Trig_2 = 0;
    Trig_3 = 0;
    Trig_4 = 0;
    all_triggers_work = false;

    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();

    particles_names_A.clear();
    particles_names_B.clear();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
    man->FillNtupleIColumn(0,0,evt);
     man->AddNtupleRow(0); 
}



void EventAction::EndOfEventAction(const G4Event*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();  
//------------------------------------------------------------------------------------------
G4cout << "------------------------------------------------------------\n" << G4endl;
//G4cout << "PARTICLES DETECTED PER TRIGGER:"<<G4endl;

//G4cout << "TRIGGER 1: ";
    if(Trig_1 == 0){
        G4cout << "TRIGGER 1 DID NOT PASSED";
    } else { 
        //G4cout << "PASSED";
    }
//G4cout << G4endl;

//G4cout << "TRIGGER 2: ";
    if(Trig_2 == 0){
        G4cout << "TRIGGER 2 DID NOT PASSED";
    } else { 
       // G4cout << "PASSED";
    }
//G4cout << G4endl;

//G4cout << "TRIGGER 3: ";
    if(Trig_3 == 0){
        G4cout << "TRIGGER 3 DID NOT PASSED";
    } else { 
        //G4cout << "PASSED";
    }
//G4cout << G4endl;

//G4cout << "TRIGGER 4: ";
    if(Trig_4 == 0){
        G4cout << "TRIGGER 4 DID NOT PASSED";
    } else { 
        //G4cout << "PASSED";
    }
G4cout << "\n"<< G4endl;



        if(Trig_1 != 0){
            if(Trig_2 != 0){
                if(Trig_3 != 0){
                    if(Trig_4 != 0){
                        all_triggers_work = true;
                    }
                }   
            }
        } else {
          all_triggers_work = false;
        }  
    


    G4int ALL_TRIGGERS_INT = static_cast<G4int>(all_triggers_work );

    G4cout << "ALL TRIGGERS DETECTED: " << ALL_TRIGGERS_INT << G4endl;

    G4cout << G4endl;


    man->FillNtupleIColumn(1, 25, ALL_TRIGGERS_INT);


//------------------------------------------------------------------------------------------

G4cout << "------------------------------------------------------------\n" << G4endl;
G4cout << "ENERGY DEPOSITION ON BARS (MeV) :   \n" << G4endl;
for (size_t i = 0; i < fEdepA.size(); i++){
    if(fEdepA[i]>0){
        G4cout << "BAR A | " << "ID: "<< i << " |  Edep:  " << fEdepA[i] << "  MeV" << G4endl;
    } 
     man->FillNtupleDColumn(1, i, fEdepA[i]);  
}

for (size_t j = 0; j < fEdepB.size(); j++){
    if(fEdepB[j]>0){
       G4cout << "BAR B | " << "ID: "<< j + 2  << " |  Edep:  " << fEdepB[j] << "  MeV" << G4endl; 
    }
    man->FillNtupleDColumn(1, j + fEdepA.size(), fEdepB[j] );
    
}


G4cout << "" << G4endl;

for (size_t i = 0; i < fEdepB.size(); ++i) {
       TOTAL_Edep += fEdepA[i] + fEdepB[i];

    }

    G4cout << "TOTAL EDEP:  " << TOTAL_Edep << G4endl;

    man->FillNtupleDColumn(1, 33, TOTAL_Edep);
        
//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "dE/dx (MeV/):   " << G4endl;

for (size_t k = 0; k < fTotaldEdx_A.size(); k++){
    if(fTotaldEdx_A[k]>0){
       G4cout << "BAR A | " << "ID: "<< k  << " |  dE/dx:  " << fTotaldEdx_A[k] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, k + fEdepB.size() + fEdepA.size() , fTotaldEdx_A[k] );
}
   

for (size_t l = 0; l < fTotaldEdx_B.size(); l++){
    if(fTotaldEdx_B[l]>0){
       G4cout << "BAR B | " <<  "ID: "<< l + 2 << " |  dE/dx:  " << fTotaldEdx_B[l] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, l + fTotaldEdx_A.size() + fEdepA.size() + fEdepB.size(), fTotaldEdx_B[l] );
}


G4cout << "" << G4endl;

    for (size_t i = 0; i < fTotaldEdx_B.size(); ++i) {
        TOTAL_dEdx += fTotaldEdx_A[i] + fTotaldEdx_B[i];
    }
     G4cout << "total dE/dx:  " << TOTAL_dEdx <<"\n"<< G4endl;


    
    man->FillNtupleDColumn(1, 34, TOTAL_dEdx);

//------------------------------------------------------------------------------------------
G4cout << "\n------------------------------------------------------------" << G4endl;
G4cout << "" << G4endl;
G4cout << "DETECTED PHOTONS ON SiPM's:   " << G4endl;
for (size_t m = 0; m < photonHits_event_A.size(); m++){
    if(photonHits_event_A[m]>0){
        G4cout << "SiPM A | " <<"ID: "<<  m  << " |  Detected photons:  " << photonHits_event_A[m] << "  photons" << G4endl;   
    }
    man->FillNtupleDColumn(1, m + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_A[m] ); 
}

for (size_t n = 0; n < photonHits_event_B.size(); n++){
    if(photonHits_event_B[n]>0){
        G4cout << "SiPM B | " <<"ID: "<< n +2   << " |  Detected photons:  " << photonHits_event_B[n] << "  photons" << G4endl; 
        }
     man->FillNtupleDColumn(1, n + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_B[n] );
}

//             TO GET THE RIGHT NUMBER OF DETECTED PHOTONS 

G4int photons_detected_real_A = 0.0;

G4int photons_detected_real_B = 0.0;

    for (auto bar : traversed_Bars_A) {
        if(bar >=0 && bar <2){
            photons_detected_real_A += photonHits_event_A[bar];
        } else{
            G4cerr << " ERROR: índice inválido en traversed_Bars_A: " << bar << G4endl;
        }   
    }
    
    for (auto bar : traversed_Bars_B) {
        if(bar >=2 && bar <5){
            photons_detected_real_B += photonHits_event_B[bar-2];
        } else {
            G4cerr << "ERROR: índice inválido en traversed_Bars_B: " << bar << G4endl;
        }
    }

    if(photons_detected_real_A > 0 || photons_detected_real_B > 0){
    TOTAL_Detected_photons = photons_detected_real_A + photons_detected_real_B;
    }


    G4cout << "\n" << G4endl;
    G4cout <<"TOTAL DETECTED PHOTONS: "<< TOTAL_Detected_photons << " photons \n"<< G4endl;       
            
    man->FillNtupleIColumn(1, 36, TOTAL_Detected_photons);
  


//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "GENERATED PHOTONS:   " << G4endl;
for (size_t u = 0; u < fGenerated_photons_A.size(); ++u){
    if(fGenerated_photons_A[u]>0){
        G4cout << "BAR A | " <<"ID: "<<  u  << " |  Generated photons:  " << fGenerated_photons_A[u] << "  photons" << G4endl;   
        }
    man->FillNtupleDColumn(1, u + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_A[u] );   
}

for (size_t v = 0; v < fGenerated_photons_B.size(); v++){
    if(fGenerated_photons_B[v]>0){
        G4cout << "BAR B | " <<"ID: "<<  v + 2   << " |  Generated photons:  " << fGenerated_photons_B[v] << "  photons" << G4endl; 
        }
    man->FillNtupleDColumn(1, v + fGenerated_photons_A.size() + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_B[v] ); 
}


G4cout << "\n" << G4endl;
/*
G4cout << "**********************************" <<G4endl;
for(auto gen : fGenerated_photons_A) {
    G4cout << gen<< " ";
    G4cout << G4endl;
    }

    for(auto gen : fGenerated_photons_B) {
    G4cout << gen<< " ";
    G4cout << G4endl;
    }
G4cout << "**********************************" <<G4endl;
G4cout << "" <<G4endl;
*/

for (size_t i = 0; i < fGenerated_photons_B.size(); ++i) {
        TOTAL_Generated_photons += fGenerated_photons_A[i] + fGenerated_photons_B[i];
    }

    G4cout << "TOTAL GENERATED PHOTONS:  " << TOTAL_Generated_photons <<" photons "<< G4endl;

      man->FillNtupleDColumn(1, 35, TOTAL_Generated_photons);

G4cout << "\n------------------------------------------------------------" << G4endl;

 //-------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "LAYER A | ID: ";
if (traversed_Bars_A.empty()) {
    G4cout << "-1  (-1 means no particle has passed.)";
    man->FillNtupleIColumn(1, 23, -1);
} else {
    for (auto bar_a : traversed_Bars_A) {
        G4cout << bar_a << " ";
        man->FillNtupleIColumn(1,23,bar_a);
    }
}
 G4cout <<G4endl;


G4cout << "LAYER B | ID: ";
 if(traversed_Bars_B.empty()){
        G4cout<< "0  (O means no particle has passed.)";
        man->FillNtupleIColumn(1,24,0);
    }else{
    for (auto bar_b : traversed_Bars_B) {
        G4cout << bar_b << " ";
        man->FillNtupleIColumn(1,24,bar_b);
    }
    }


G4cout<<G4endl;
int Sumcopies = traversed_Bars_A.size() + traversed_Bars_B.size();
G4cout << "TOTAL AMOUNT OF PIERCED BARS:  " << Sumcopies << "  barras" << "\n" << G4endl; 

G4cout<<G4endl;
G4cout << "HIT: ";
if(Sumcopies >0){
    G4cout << "* YES * " <<G4endl;
    Hit = true;
}else{
    G4cout << "* NO * " <<G4endl;
    Hit = false;
}

G4int hit_int= static_cast<G4int>(Hit);

 man->FillNtupleIColumn(1, 38, hit_int);


//-------------------------------------------------------------------------------------------

G4cout << G4endl;
G4cout << "PARTICLES ON LAYER A: " <<  G4endl;

if (particles_names_A.empty()) {
    G4cout << "**No particles pierced Layer A in this event." << G4endl;
} else {
    for (auto p_name : particles_names_A) {
        G4cout << p_name << ", ";
        man->FillNtupleSColumn(1, 32, p_name);
    }}


G4cout <<"\n"<< G4endl;
G4cout << "PARTICLES ON LAYER B: " <<  G4endl;

if (particles_names_B.empty()) {
    G4cout << "**No particles pierced Layer B in this event." << G4endl;
} else {
    for (auto p_name : particles_names_B) {
        G4cout << p_name << ", ";
        man->FillNtupleSColumn(1, 37, p_name);
    }}



G4cout << G4endl;
G4cout << "------------------------------------------------------------" << G4endl;
G4cout << G4endl;

G4cout <<"A | POSITION X : " << G4endl;
for(const auto& pos_x_A :pos_layer_A_x){
        G4cout << pos_x_A << " cm, ";
        man->FillNtupleDColumn(1, 26, pos_x_A);

}

G4cout <<"A | POSITION Y: " << G4endl;
for(const auto& pos_y_A :pos_layer_A_y){
        G4cout << pos_y_A << " cm, ";
        man->FillNtupleDColumn(1, 27, pos_y_A);
}

G4cout <<"A | POSITION Z: " << G4endl;
for(const auto& pos_z_A :pos_layer_A_z){
        G4cout << pos_z_A << " cm, ";
        man->FillNtupleDColumn(1, 28, pos_z_A);
}

G4cout << "" << G4endl;

G4cout <<"B | POSITION X: "<< G4endl;
for(const auto& pos_x_B :pos_layer_B_x){
        G4cout << pos_x_B << " cm, ";
        man->FillNtupleDColumn(1, 29, pos_x_B);
}

G4cout <<"B | POSITION Y: " << G4endl;
for(const auto& pos_y_B :pos_layer_B_y){
        G4cout << pos_y_B << " cm, ";
        man->FillNtupleDColumn(1, 30, pos_y_B);
}

G4cout <<"B | POSITION Z: " << G4endl;
for(const auto& pos_z_B :pos_layer_B_z){
        G4cout << pos_z_B << " cm, ";
        man->FillNtupleDColumn(1, 31, pos_z_B);
}

G4cout << "\n" << G4endl;
G4cout <<"------------------------------------------------------------" << G4endl;
//-----------------  ANGLE  -----------------
//if the particle just pass layer A

   G4ThreeVector pos_vertex  (0., 305.56, 0.);
G4cout <<"Position of vertex: 305.56 cm on axis Y" << G4endl;
G4cout<< "" <<G4endl;


if (!pos_layer_A_x.empty() && !pos_layer_A_y.empty() && !pos_layer_A_z.empty()) {

        G4double first_pos_x_a = pos_layer_A_x.front();
        G4double first_pos_y_a = pos_layer_A_y.front();
        G4double first_pos_z_a = pos_layer_A_z.front();
     
        G4ThreeVector pos_on_A (first_pos_x_a, first_pos_y_a, first_pos_z_a);
        

        // Print the vector for debugging
        G4cout << "LAYER A | First position : ("
               << pos_on_A.x() << ", " << pos_on_A.y() << ", " << pos_on_A.z() << ") cm" << G4endl;
        
        G4cout <<""<<G4endl;
        

        G4ThreeVector sustraction_a =  pos_on_A - pos_vertex ;
        G4double Magnitude_sustraction_a = sustraction_a.mag();

        G4cout << "LAYER A | vector with the direction: ("
               << sustraction_a.x() << ", " << sustraction_a.y() << ", " << sustraction_a.z() << ") cm" << G4endl;
        
        G4cout <<""<<G4endl;


         G4ThreeVector unit_sust_a = sustraction_a.unit();
        G4cout << "LAYER A | UNIT direction : ("
               << unit_sust_a.x() << ", " << unit_sust_a.y() << ", " << unit_sust_a.z() << ") cm" << G4endl;
        
         G4cout <<""<<G4endl;


        G4ThreeVector unit_y(0., -1., 0.);
        

         G4double angle_a = std::acos(sustraction_a.unit().dot(unit_y));
        //G4double angle_a = std::acos(first_pos_y_a/Magnitude_sustraction_a);
        G4double angle_a_d = angle_a * (180.0/ CLHEP::pi);
        G4double angle_a_xz = 90 - angle_a_d;
        G4double angle_a_xz_rad = (CLHEP::pi/2) - angle_a;

         G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Magnitude: "<<Magnitude_sustraction_a <<G4endl;
        G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Dispersion angle (radians) respect to y:: " << angle_a << " rad"<< G4endl;
        G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Dispersion angle (degrees) respect to y: " << angle_a_d <<" °"<< G4endl;
        G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Dispersion angle (radians) respect to plane XZ: " << angle_a_xz_rad<<" rad"<< G4endl;
         G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Dispersion angle (degrees) respect to plane XZ: " << angle_a_xz<<" °"<< G4endl;


        man->FillNtupleDColumn(1,39,angle_a);
        man->FillNtupleDColumn(1,40,angle_a_d);
        man->FillNtupleDColumn(1,41,angle_a_xz_rad);
        man->FillNtupleDColumn(1,42,angle_a_xz);
    

    } else {
            G4cout << "No positions recorded in Layer A for this event." << G4endl;
   
    }
    G4cout << "\n" << G4endl;
   
//------------------------------------------------------------------------------------
G4cout <<"------------------------------------------------------------" << G4endl;

  if (!pos_layer_B_x.empty() && !pos_layer_B_y.empty() && !pos_layer_B_z.empty()) {

        G4double first_pos_x_b = pos_layer_B_x.front();
        G4double first_pos_y_b = pos_layer_B_y.front();
        G4double first_pos_z_b = pos_layer_B_z.front();
       
        G4ThreeVector pos_on_B (first_pos_x_b, first_pos_y_b, first_pos_z_b);


        // Print the vector for debugging
        G4cout << "LAYER B | First position : ("
               << pos_on_B.x() << ", " << pos_on_B.y() << ", " << pos_on_B.z() << ") cm" << G4endl;

        G4cout <<""<<G4endl;
        

        G4ThreeVector sustraction_b =  pos_on_B - pos_vertex ;
        G4double Magnitude_sustraction_b = sustraction_b.mag();

        G4cout << "LAYER B | vector with the direction: ("
               << sustraction_b.x() << ", " << sustraction_b.y() << ", " << sustraction_b.z() << ") cm" << G4endl;
        
        G4cout <<""<<G4endl;


        G4ThreeVector unit_sust_b = sustraction_b.unit();
        G4cout << "LAYER B | UNIT direction : ("
               << unit_sust_b.x() << ", " << unit_sust_b.y() << ", " << unit_sust_b.z() << ") cm" << G4endl;
        
         G4cout <<""<<G4endl;


        G4ThreeVector unit_y(0., -1., 0.);
        

         G4double angle_b = std::acos(sustraction_b.unit().dot(unit_y));
        //G4double angle_a = std::acos(first_pos_y_a/Magnitude_sustraction_a);
        G4double angle_b_d = angle_b * (180.0/ CLHEP::pi);
        G4double angle_b_xz = 90 - angle_b_d;
        G4double angle_b_xz_rad = (CLHEP::pi/2) - angle_b;

         G4cout <<""<<G4endl;
        G4cout <<"LAYER B | Magnitude: "<<Magnitude_sustraction_b <<G4endl;

        G4cout <<""<<G4endl;
        G4cout << "LAYER B | Dispersion angle (radians): " << angle_b <<" rad"<< G4endl;

        G4cout <<""<<G4endl;
        G4cout << "LAYER B | Dispersion angle (degrees) respect to y: " << angle_b_d <<" °"<< G4endl;

        G4cout <<""<<G4endl;
        G4cout << "LAYER B | Dispersion angle (rad) respect to plane XZ: " << angle_b_xz_rad<<" rad"<< G4endl;

        G4cout <<""<<G4endl;
        G4cout << "LAYER B | Dispersion angle (degrees) respect to plane XZ: " << angle_b_xz<<" °"<< G4endl;

        man->FillNtupleDColumn(1,43,angle_b);
        man->FillNtupleDColumn(1,44,angle_b_d);
        man->FillNtupleDColumn(1,45,angle_b_xz_rad);
        man->FillNtupleDColumn(1,46,angle_b_xz);

    } else {
            G4cout << "No positions recorded in Layer B for this event." << G4endl;
   
    }  

G4cout<<"\n"<<G4endl;

man->AddNtupleRow(1);


}




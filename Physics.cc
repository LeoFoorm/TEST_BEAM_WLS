//		PHYSICS LIST SOURCE

#include "Physics.hh"

#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"

#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4DecayPhysics.hh" 
#include "G4OpticalParameters.hh"


PhysicsList::PhysicsList()
{
	//NEW
	RegisterPhysics(new G4EmStandardPhysics());

    // Register hadronic physics (FTFP_BERT_HP components)
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());
    RegisterPhysics(new G4HadronElasticPhysicsHP());
    RegisterPhysics(new G4StoppingPhysics());
    RegisterPhysics(new G4IonPhysics());

    // Register decay physics
    RegisterPhysics(new G4DecayPhysics());

    // Register optical physics for scintillation
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    RegisterPhysics(opticalPhysics);

    // Configure optical processes using G4OpticalParameters
    G4OpticalParameters* opticalParams = G4OpticalParameters::Instance();
    opticalParams->SetProcessActivation("Scintillation", true);    // Enable scintillation
    opticalParams->SetProcessActivation("OpAbsorption", true);    // Enable absorption
    opticalParams->SetProcessActivation("OpBoundary", true);      // Enable boundary processes
	opticalParams->SetProcessActivation("OpWLS", true);			  // Enable WLS processes
	opticalParams->SetWLSTimeProfile("delta"); // o "exponential"


    // Disable tracking secondaries first for optical photons
    //opticalParams->SetTrackSecondariesFirst(kOpticalPhoton, false);
    
    // Limit number of optical photons generated per step
   // opticalParams->SetMaxNumPhotonsPerStep(100);


	// BEFORE

	/*RegisterPhysics (new G4EmStandardPhysics());

    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	RegisterPhysics(opticalPhysics);

	RegisterPhysics (new G4DecayPhysics());

	RegisterPhysics (new G4RadioactiveDecayPhysics());

	RegisterPhysics(new G4HadronPhysicsQGSP_BERT());


	RegisterPhysics( new G4EmExtraPhysics());

	RegisterPhysics( new G4HadronElasticPhysicsHP());


	RegisterPhysics( new G4StoppingPhysics());

	RegisterPhysics( new G4IonPhysics());*/

}

PhysicsList::~PhysicsList()
{}

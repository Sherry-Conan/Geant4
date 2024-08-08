//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4MTRunManager.hh"
#include "G4RunManager.hh"

//探测器构建
//madatory class - Detector Construction
#include "OpNoviceDetectorConstruction.hh"

//调用物理过程
//mandatory class - physics 
#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"

#include "G4GenericPhysicsList.hh"                    
#include "LBE.hh"// 这个比较复杂 -_-
#include "NuBeam.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysics G4HadronPhysicsNuBeam G4StoppingPhysics G4IonPhysics G4NeutronTrackingCut
#include "QBBC.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysicsXS G4StoppingPhysics G4IonPhysics G4HadronInelasticQBBC G4NeutronTrackingCut
#include "QGS_BIC.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysics G4HadronPhysicsQGS_BIC G4StoppingPhysics G4IonPhysics G4NeutronTrackingCut
#include "QGSP_BERT.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysics G4HadronPhysicsQGSP_BERT G4StoppingPhysics G4IonPhysics G4NeutronTrackingCut
#include "QGSP_BERT_HP.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysicsHP G4HadronPhysicsQGSP_BERT_HP G4StoppingPhysics G4IonPhysics
#include "QGSP_BIC_AllHP.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysicsPHP G4HadronPhysicsQGSP_BIC_AllHP G4StoppingPhysics G4IonPhysicsPHP
#include "QGSP_BIC.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysics G4HadronPhysicsQGSP_BIC G4StoppingPhysics G4IonPhysics G4NeutronTrackingCut
#include "QGSP_BIC_HP.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysicsHP G4HadronPhysicsQGSP_BIC_HP G4StoppingPhysics G4IonPhysics
#include "QGSP_FTFP_BERT.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysics G4HadronPhysicsQGSP_FTFP_BERT G4StoppingPhysics G4IonPhysics G4NeutronTrackingCut
#include "QGSP_INCLXX.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysics G4HadronPhysicsINCLXX G4StoppingPhysics G4IonINCLXXPhysics G4NeutronTrackingCut
#include "QGSP_INCLXX_HP.hh"// G4EmStandardPhysics G4EmExtraPhysics G4DecayPhysics G4HadronElasticPhysicsHP G4HadronPhysicsINCLXX G4StoppingPhysics G4IonINCLXXPhysics
#include "Shielding.hh"// 这个比较复杂,分好几种情况 -_-

#include "G4ParticleHPManager.hh"


//其它过程的管理
//not mandatory class - ActionInitialization
#include "ZjnActionInitialization.hh"

// 关于图形界面与交互接口
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"



#include "Randomize.hh"//随机数这里产生
#include <ctime>// initialize random seed
using namespace std;

int main(int argc,char** argv)
{

  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4int seconds =  time(NULL);
  G4Random::setTheSeed(seconds);



  // Construct the default run manager
  G4RunManager* mtrunManager = NULL;

  mtrunManager = new G4MTRunManager;
  // mtrunManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores()); 
  mtrunManager->SetNumberOfThreads(1); 

  // mtrunManager->SetUserInitialization(new wuWorkerInitialization);


  // Set mandatory initialization classes ，410版本的框架是这样的，ActionInitialization来管理。
  //
  // Detector construction
  mtrunManager->SetUserInitialization(new OpNoviceDetectorConstruction()); 

  // Physics list
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics); 
  mtrunManager->SetUserInitialization(physicsList); 

  // User action initialization
  mtrunManager->SetUserInitialization(new wuActionInitialization());


  // Initialize G4 kernel
  mtrunManager->Initialize();



  // Print   Data source of this Partile HP calculation
  // G4ParticleHPManager::GetInstance()->DumpDataSource();

  

  G4VisManager* visManager = 0; 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  G4String commandopt = argv[1];
  if(commandopt == "vis.mac")// 开启图形界面模式
    {
      visManager = new G4VisExecutive;
      visManager->Initialize();

      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
      UImanager->ApplyCommand("/control/execute vis.mac");
      ui->SessionStart();
      delete ui;
    }
  else
    {
      if(commandopt == "-l")// 开启命令行模式
	{  
	  G4UIsession* session = new G4UIterminal(new G4UItcsh);
	  session->SessionStart();
	  delete session;
	}
      else
	{// 无图形界面执行脚本模式
	  G4String command = "/control/execute ";
	  G4String fileName = argv[1];
	  UImanager->ApplyCommand(command + fileName);
	}
    }

  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  if(visManager != 0)
    delete visManager;

  delete mtrunManager;

  return 0;
}


// 
// main.cc ends here

// wuStackingActionAll.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 5月  8 22:50:33 2017 (+0800)
// Last-Updated: 一 5月  8 23:05:56 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#ifndef _WUSTACKINGACTIONALL_H_
#define _WUSTACKINGACTIONALL_H_

#include "G4UserStackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class wuStackingActionAll : public G4UserStackingAction
{
public:
  wuStackingActionAll();
  virtual ~wuStackingActionAll();

public:
  // Reply G4ClassificationOfNewTrack determined by the newly coming G4Track.
  // The parent_ID of the track indicates the origin of it.        
  //    G4int parent_ID = aTrack->get_parentID();
  //      parent_ID = 0 : primary particle
  //                > 0 : secondary particle
  //                < 0 : postponed from the previous event
  virtual G4ClassificationOfNewTrack  ClassifyNewTrack(const G4Track* aTrack);

  // This method is called by G4StackManager when the urgentStack becomes empty and contents in the waitingStack are transtered to the urgentStack.
  // Note that this method is not called at the begining of each event, but "PrepareNewEvent" is called.
  // In case re-classification of the stacked tracks is needed, use the following method to request to G4StackManager.
  //    stackManager->ReClassify();
  // All of the stacked tracks in the waitingStack will be re-classified by "ClassifyNewTrack" method.
  // To abort current event, use the following method.
  //    stackManager->clear();
  //  Note that this way is valid and safe only for the case it is called from this user class. The more global way of event abortion is
  //    G4UImanager * UImanager = G4UImanager::GetUIpointer();
  //    UImanager->ApplyCommand("/event/abort");  
  virtual void NewStage();

  // This method is called by G4StackManager at the begining of each event.
  // Be careful that the urgentStack and the waitingStack of G4StackManager are empty at this moment, because this method is called before accepting primary particles. Also, note that the postponeStack of G4StackManager may have some postponed tracks.
  virtual void PrepareNewEvent();
};

// enum G4ClassificationOfNewTrack
// { 
//   fUrgent=0,     // put into the urgent stack
//   fWaiting=1,    // put into the waiting stack
//   fPostpone=-1,  // postpone to the next event
//   fKill=-9,      // kill
//   //----------------------------------------------------------------
//   // following ENUM are available only if the user increases the number of waiting stacks
//   fWaiting_1=11, fWaiting_2=12, fWaiting_3=13, fWaiting_4=14, fWaiting_5=15,
//   fWaiting_6=16, fWaiting_7=17, fWaiting_8=18, fWaiting_9=19, fWaiting_10=20
// };

#endif /* _WUSTACKINGACTIONALL_H_ */
// 
// wuStackingActionAll.hh ends here


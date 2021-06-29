#ifndef __PEER_H_
#define __PEER_H_

#include "DiameterStateMachine.h"

class Peer : 
    public DiameterStActions<DiameterStateMachineArgsPtr&>,
    public DiameterStateMachineObserver,
{
  private:
    // the Diameter peer state machine
    DiameterStateMachine m_oStateMachine;
    
  public:
    CPeer() : m_oStateMachine(*this, *this)
    {
    }
 
    // DiameterStActions
    virtual void do_None            (DiameterStateMachineArgsPtr&);
    virtual void do_ISndConnReq     (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RAccept         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndCER         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndCER         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_Cleanup         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_Error           (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_IDisc           (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RDisc           (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndCEA         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndCEA         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_Process         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ProcessCER      (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ProcessCEA      (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ProcessDWA      (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ProcessDWR      (DiameterStateMachineArgsPtr& rptrArgs);
    //virtual void do_ISndDWR         (DiameterStateMachineArgsPtr& rptrArgs);
    //virtual void do_RSndDWR         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndDWA         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndDWA         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RWatchdogTimeout(DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_IWatchdogTimeout(DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndMessage     (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndMessage     (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RReject         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndDPR         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndDPA         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndDPR         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndDPA         (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_Elect           (DiameterStateMachineArgsPtr& rptrArgs);

    virtual void do_ProcessDPA      (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_ISndSecondCEA   (DiameterStateMachineArgsPtr& rptrArgs);
    virtual void do_RSndSecondCEA   (DiameterStateMachineArgsPtr& rptrArgs);

    // DiameterStateMachineObserver
    virtual void OnStopped();
    virtual void OnStopping();
    virtual void OnStarting();
    virtual void OnROpen();
    virtual void OnIOpen();
    virtual void OnStateChanged();
};
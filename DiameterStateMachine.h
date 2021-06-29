#ifndef _DIAMETERSTATEMACHINE_H
#define _DIAMETERSTATEMACHINE_H

#include <DiameterStateTable.h>

class DiameterStateMachineObserver
{
public:
	virtual void OnStopped() = 0;
	virtual void OnStopping() = 0;
	virtual void OnStarting() = 0;
	virtual void OnROpen() = 0;
  virtual void OnIOpen() = 0;
	virtual void OnStateChanged() = 0;
};

class DiameterStateMachineArgs;
typedef Pointer<DiameterStateMachineArgs> DiameterStateMachineArgsPtr;

class DiameterStateMachineArgs 
{
public:
    typedef DiameterStDefs<DiameterStateMachineArgsPtr&>::EVENT tEVENT;

    // Start
    DiameterStateMachineArgs(tEVENT eEvent);

    // Stop peer
    DiameterStateMachineArgs(tEVENT eEvent, int32 nData);

    // etc.

    void SetEvent (tEVENT eEvent)
    {
        m_eEvent = eEvent;
    }
    tEVENT Event()
    {
        return m_eEvent;
    }

protected:
    tEVENT  m_eEvent;
    // etc.
};

class DiameterStateMachine : public DiameterStDefs<DiameterStateMachineArgsPtr&>
{
protected:
	static DiameterStateTable<DiameterStateMachineArgsPtr&> theStateTable;

public:
	DiameterStateMachine(DiameterStActions<DiameterStateMachineArgsPtr&>& rActions, 
			                 DiameterStateMachineObserver& rObserver) :
		m_rActions(rActions),
		m_rObserver(rObserver),
		m_nState(STATE_CLOSED),
		m_nStatus(theStateTable.GetStatus(m_nState))
	{
	}
  
  STATUS Status()
  {
      return m_nStatus;
  }
  STATE State() const
  {
      return m_nState;
  }
  
protected:
	DiameterStActions<DiameterStateMachineArgsPtr&>&  m_rActions;
	DiameterStateMachineObserver&                     m_rObserver;
	STATE                                             m_nState;
	STATUS                                            m_nStatus;
};  

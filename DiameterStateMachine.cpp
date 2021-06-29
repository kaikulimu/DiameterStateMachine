#include "DiameterStateMachine.h"

// static state machine table
DiameterStateTable<DiameterStateMachineArgsPtr&> DiameterStateMachine::theStateTable;

void DiameterStateMachine::InnerEvent(EVENT nEvent, DiameterStateMachineArgsPtr& rptrArgs, LogClient& rLog)
{
    try
    {
        STATE nOld = m_nState;

        // transition state
	      PFN_ACTION pfnAction;
	      m_nState = (STATE)theStateTable.Transition(m_nState, nEvent, pfnAction);

        LOG(rLog) << "state machine event \'"<< EventString(nEvent) 
                  << "\', transition \'" << StateString(nOld) << "\' => \'" << StateString(m_nState) << '\'';

        // perform action
        (m_rActions.*pfnAction)(rptrArgs);
    }
    catch(Exception & ex)
    {
      _HANDLED(ex);
    }
}
void DiameterStateMachine::Event(EVENT nEvent, DiameterStateMachineArgsPtr& rptrArgs, LogClient& rLog)
{
	// get current status
	STATUS nStatus = m_nStatus;
  STATE  nOld    = m_nState;

  InnerEvent(nEvent, rptrArgs, rLog);

	// update status
	m_nStatus = theStateTable.GetStatus(m_nState);
  // if there was a change, notify the observer
	if( m_nStatus == nStatus ) {
      if (nOld != m_nState) {
          m_rObserver.OnStateChanged();
      }
  } else {
		switch( m_nStatus )
		{
		case STATUS_STOPPED:
			m_rObserver.OnStopped();
			break;

		case STATUS_STARTING:
			m_rObserver.OnStarting();
			break;

		case STATUS_STOPPING:
			m_rObserver.OnStopping();
			break;

		case STATUS_STARTED:
      switch (m_nState)
      {
      case STATE_R_OPEN:
          {
              m_rObserver.OnROpen();
              break;
          }
      case STATE_I_OPEN:
          {
              m_rObserver.OnIOpen();
              break;
          }
      default:
          {
          }
      }
			break;
		}
	}
}
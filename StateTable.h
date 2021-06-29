#ifndef _STATETABLE_H
#define _STATETABLE_H


template<size_t NUM_STATES, size_t NUM_EVENTS, typename ACTION>
class StateTable
{
public:

	// This constructor inits all elements to no state change, specified action
	StateTable(ACTION action = ACTION())
	{
		for( size_t i = 0; i < NUM_STATES; i++ )
		{
			for( size_t j = 0; j < NUM_EVENTS; j++ )
			{
				m_anNextState[i][j] = i;
				m_aAction[i][j] = action;
			}
		}
	}

	// This constructor inits all elements to specified state change, specified action
	StateTable(int nNextState, ACTION action = ACTION())
	{
		for( size_t i = 0; i < NUM_STATES; i++ )
		{
			for( size_t j = 0; j < NUM_EVENTS; j++ )
			{
				m_anNextState[i][j] = nNextState;
				m_aAction[i][j] = action;
			}
		}
	}

	void Configure(int nState, int nEvent, int nNextState, ACTION Action)
	{
		m_anNextState[nState][nEvent] = nNextState;
		m_aAction[nState][nEvent] = Action;
	}

	int Transition(int nState, int nEvent, ACTION& rAction) const
	{
		_ASSERT((size_t)nState < NUM_STATES);
		_ASSERT((size_t)nEvent < NUM_EVENTS);
		rAction = m_aAction[nState][nEvent];
		return m_anNextState[nState][nEvent];
	}

protected:
	int m_anNextState[NUM_STATES][NUM_EVENTS];
	ACTION m_aAction[NUM_STATES][NUM_EVENTS];
};


#endif

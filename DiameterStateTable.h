#ifndef _DIAMETERSTATETABLE_H
#define _DIAMETERSTATETABLE_H

#include <StateTable.h>

template<typename T>
class DiameterStActions
{
public:
    virtual void do_None(T x) = 0;
    virtual void do_ISndConnReq(T x) = 0;
    
    virtual void do_RAccept(T x) = 0;
    virtual void do_RReject(T x) = 0;
    
    virtual void do_RSndCER(T x) = 0;
    virtual void do_ISndCER(T x) = 0;

    virtual void do_ISndCEA(T x) = 0;
    virtual void do_RSndCEA(T x) = 0;

    virtual void do_ProcessCER(T x) = 0;
    virtual void do_ProcessCEA(T x) = 0;
    virtual void do_Process(T x) = 0;
    virtual void do_ProcessDWA(T x) = 0;
    virtual void do_ProcessDWR(T x) = 0;
    virtual void do_Cleanup(T x) = 0;
    virtual void do_Elect(T x) = 0;
    virtual void do_Error(T x) = 0;

    virtual void do_IDisc(T x) = 0;
    virtual void do_RDisc(T x) = 0;

    virtual void do_RSndMessage(T x) = 0;
    virtual void do_ISndMessage(T x) = 0;
    
    virtual void do_RSndDPR(T x) = 0;
    virtual void do_RSndDPA(T x) = 0;
    virtual void do_ISndDPR(T x) = 0;
    virtual void do_ISndDPA(T x) = 0;

    virtual void do_RWatchdogTimeout(T x) = 0;
    virtual void do_IWatchdogTimeout(T x) = 0;

    virtual void do_RSndDWA(T x) = 0;
    virtual void do_ISndDWA(T x) = 0;

    void do_RAccept_ProcessCER_RSndCEA(T x)
    {
        do_RAccept(x);
        do_ProcessCER(x);
        do_RSndCEA(x);
    }
    void do_RAccept_ProcessCER(T x)
    {
        do_RAccept(x);
        do_ProcessCER(x);
    }
    void do_RAccept_ProcessCER_Elect(T x)
    {
        do_RAccept(x);
        do_ProcessCER(x);
        do_Elect(x);
    }
    void do_ISndCER_Elect(T x)
    {
        do_ISndCER(x);
        do_Elect(x);
    }
    void do_IDisc_RSndCEA(T x)
    {
        do_IDisc(x);
        do_RSndCEA(x);
    }
    void do_ProcessDWR_RSndDWA(T x)
    {
        do_ProcessDWR(x);
        do_RSndDWA(x);
    }
    void do_RSndDPA_RDisc(T x)
    {
        do_RSndDPA(x);
        do_RDisc(x);
    }
    void do_ProcessDWR_ISndDWA(T x)
    {
        do_ProcessDWR(x);
        do_ISndDWA(x);
    }
    void do_ISndDPA_IDisc(T x)
    {
        do_ISndDPA(x);
        do_IDisc(x);
    }
};

template<typename T>
class DiameterStDefs
{
public:
    typedef void (DiameterStActions<T>::*PFN_ACTION)(T x);

    enum STATUS
    {
        STATUS_STOPPED = 0,
        STATUS_STOPPING,
        STATUS_STARTING,
        STATUS_STARTED
    };

    enum STATE
    {
        STATE_CLOSED = 0,
        STATE_WAIT_CONN_ACK,
        STATE_WAIT_I_CEA,
        STATE_WAIT_CONN_ACK_ELECT,
        STATE_WAIT_RETURNS,
        STATE_R_OPEN,
        STATE_I_OPEN,
        STATE_CLOSING,
        NUM_STATES          // this must be the last
    };

    enum EVENT
    {
        EVENT_START = 0,
        EVENT_R_CONN_CER,
        EVENT_I_RCV_CONN_ACK,
        EVENT_I_RCV_CONN_NACK,
        EVENT_TIMEOUT,
        EVENT_I_RCV_CER,
        EVENT_I_RCV_CEA,
        EVENT_R_RCV_CER,
        EVENT_R_RCV_CEA,
        EVENT_I_RCV_NON_CEA,

        EVENT_I_PEER_DISC,
        EVENT_R_PEER_DISC,

        EVENT_I_RCV_DPR,
        EVENT_R_RCV_DPR,
        EVENT_I_RCV_DPA,
        EVENT_R_RCV_DPA,

        EVENT_WIN_ELECTION,
        EVENT_SEND_MESSAGE,
        EVENT_R_RCV_MESSAGE,
        EVENT_I_RCV_MESSAGE,

        EVENT_WATCHDOG_TIMER,

        EVENT_R_RCV_DWA,
        
        EVENT_I_RCV_DWA,
        EVENT_R_RCV_DWR,
        EVENT_I_RCV_DWR,
        EVENT_STOP,
        // in addition to the draft.
        EVENT_ERROR,
        NUM_EVENTS              // this must be the last
    };
    static
    const char* StateString(STATE nState)
    {
        switch( nState )
        {
        case STATE_CLOSED:
            return "Closed";
        case STATE_WAIT_CONN_ACK:
            return "Wait-Conn-Ack";
        case STATE_WAIT_I_CEA:
            return "Wait-I-CEA";
        case STATE_WAIT_CONN_ACK_ELECT:
            return "Wait-Conn-Ack/Elect";
        case STATE_WAIT_RETURNS:
            return "Wait-Returns";
        case STATE_R_OPEN:
            return "R-Open";
        case STATE_I_OPEN:
            return "I-Open";
        case STATE_CLOSING:
            return "Closing";
        case NUM_STATES:
            break;
        }
        return "Unknown";
    }

    static
    const char* EventString(EVENT n)
    {
        switch( n )
        {
        case EVENT_START:
            return "Start";
        case EVENT_R_CONN_CER:
            return "R-Conn-CER";
        case EVENT_I_RCV_CONN_ACK:
            return "I-Rcv-Conn-Ack";
        case EVENT_I_RCV_CONN_NACK:
            return "I-Rcv-Conn-Nack";
        case EVENT_TIMEOUT:
            return "Timeout";
        case EVENT_I_RCV_CER:
            return "I-Rcv-CER";
        case EVENT_I_RCV_CEA:
            return "I-Rcv-CEA";
        case EVENT_R_RCV_CER:
            return "R-Rcv-CER";
        case EVENT_R_RCV_CEA:
            return "R-Rcv-CEA";
        case EVENT_I_RCV_NON_CEA:
            return "I-Rcv-Non-CEA";

        case EVENT_I_PEER_DISC:
            return "I-Peer-Disc";
        case EVENT_R_PEER_DISC:
            return "R-Peer-Disc";
        
        case EVENT_I_RCV_DPR:
            return "I-Rcv-DPR";
        case EVENT_R_RCV_DPR:
            return "R-Rcv-DPR";
        case EVENT_I_RCV_DPA:
            return "I-Rcv-DPA";
        case EVENT_R_RCV_DPA:
            return "R-Rcv-DPA";



        case EVENT_WIN_ELECTION:
            return "Win-Election";
        case EVENT_SEND_MESSAGE:
            return "Send-Message";
        case EVENT_R_RCV_MESSAGE:
            return "R-Rcv-Message";
        case EVENT_I_RCV_MESSAGE:
            return "I-Rcv-Message";
        case EVENT_WATCHDOG_TIMER:
            return "Watchdog-Timer";

        case EVENT_R_RCV_DWA:
            return "R-Rcv-DWA";
        case EVENT_R_RCV_DWR:
            return "R-Rcv-DWR";
        case EVENT_I_RCV_DWR:
            return "I-Rcv-DWR";
        case EVENT_I_RCV_DWA:
            return "I-Rcv-DWA";
        case EVENT_STOP:
            return "Stop";
        case EVENT_ERROR:
            return "Error";
        case NUM_EVENTS:
            break;
        }
        return "Unknown";
    }
};

template<typename T>
class DiameterStateTable : 
        public DiameterStDefs<T>,
        public StateTable<DiameterStDefs<T>::NUM_STATES, DiameterStDefs<T>::NUM_EVENTS, DiameterStDefs<T>::PFN_ACTION>
{

#define DST_CFG(s, e, a, n) Configure(STATE_##s, EVENT_##e, STATE_##n, &DiameterStActions<T>::do_##a)

public:

    DiameterStateTable() :
        StateTable<NUM_STATES, NUM_EVENTS, PFN_ACTION>(&DiameterStActions<T>::do_None)
    {
        //          state                   event               action                  next state
        DST_CFG(    CLOSED,                 START,              ISndConnReq,            WAIT_CONN_ACK       );
        DST_CFG(    CLOSED,                 R_CONN_CER,         RAccept_ProcessCER_RSndCEA, R_OPEN          );
        
        DST_CFG(    WAIT_CONN_ACK,          I_RCV_CONN_ACK,     ISndCER,                WAIT_I_CEA          );
        DST_CFG(    WAIT_CONN_ACK,          I_RCV_CONN_NACK,    Cleanup,                CLOSED              );
        DST_CFG(    WAIT_CONN_ACK,          R_CONN_CER,         RAccept_ProcessCER,     WAIT_CONN_ACK_ELECT );
        DST_CFG(    WAIT_CONN_ACK,          TIMEOUT,            Error,                  CLOSED              );
        // in addition to the RFC
        DST_CFG(    WAIT_CONN_ACK,          STOP,               Error,                  CLOSED              );
        
        DST_CFG(    WAIT_I_CEA,             I_RCV_CEA,          ProcessCEA,             I_OPEN              );
        DST_CFG(    WAIT_I_CEA,             R_CONN_CER,         RAccept_ProcessCER_Elect,   WAIT_RETURNS    );
        DST_CFG(    WAIT_I_CEA,             I_PEER_DISC,        IDisc,                  CLOSED              );
        DST_CFG(    WAIT_I_CEA,             I_RCV_NON_CEA,      Error,                  CLOSED              );
        DST_CFG(    WAIT_I_CEA,             TIMEOUT,            Error,                  CLOSED              );
        // in addition to the RFC
        DST_CFG(    WAIT_I_CEA,             STOP,               Error,                  CLOSED              );

        DST_CFG(    WAIT_CONN_ACK_ELECT,    I_RCV_CONN_ACK,     ISndCER_Elect,          WAIT_RETURNS        );
        DST_CFG(    WAIT_CONN_ACK_ELECT,    I_RCV_CONN_NACK,    RSndCEA,                R_OPEN              );
        DST_CFG(    WAIT_CONN_ACK_ELECT,    R_PEER_DISC,        RDisc,                  WAIT_CONN_ACK       );
        DST_CFG(    WAIT_CONN_ACK_ELECT,    R_CONN_CER,         RReject,                WAIT_CONN_ACK_ELECT );
        DST_CFG(    WAIT_CONN_ACK_ELECT,    TIMEOUT,            Error,                  CLOSED              );
        // in addition to the RFC
        DST_CFG(    WAIT_CONN_ACK_ELECT,    STOP,               Error,                  CLOSED              );

        DST_CFG(    WAIT_RETURNS,           WIN_ELECTION,       IDisc_RSndCEA,          R_OPEN              );
        DST_CFG(    WAIT_RETURNS,           I_PEER_DISC,        IDisc_RSndCEA,          R_OPEN              );
        DST_CFG(    WAIT_RETURNS,           I_RCV_CEA,          RDisc,                  I_OPEN              );
        DST_CFG(    WAIT_RETURNS,           R_PEER_DISC,        RDisc,                  WAIT_I_CEA          );
        DST_CFG(    WAIT_RETURNS,           R_CONN_CER,         RReject,                WAIT_RETURNS        );
        DST_CFG(    WAIT_RETURNS,           TIMEOUT,            Error,                  CLOSED              );
        // in addition to the RFC
        DST_CFG(    WAIT_RETURNS,           STOP,               Error,                  CLOSED              );

        DST_CFG(    R_OPEN,                 SEND_MESSAGE,       RSndMessage,            R_OPEN              );
        DST_CFG(    R_OPEN,                 R_RCV_MESSAGE,      Process,                R_OPEN              );
        DST_CFG(    R_OPEN,                 WATCHDOG_TIMER,     RWatchdogTimeout,       R_OPEN              );
        DST_CFG(    R_OPEN,                 R_RCV_DWR,          ProcessDWR_RSndDWA,     R_OPEN              );
        DST_CFG(    R_OPEN,                 R_RCV_DWA,          ProcessDWA,             R_OPEN              );
        DST_CFG(    R_OPEN,                 R_CONN_CER,         RReject,                R_OPEN              );
        DST_CFG(    R_OPEN,                 STOP,               RSndDPR,                CLOSING             );
        DST_CFG(    R_OPEN,                 R_RCV_DPR,          RSndDPA_RDisc,          CLOSED              );
        DST_CFG(    R_OPEN,                 R_PEER_DISC,        RDisc,                  CLOSED              );
        DST_CFG(    R_OPEN,                 R_RCV_CER,          RSndCEA,                R_OPEN              );
        DST_CFG(    R_OPEN,                 R_RCV_CEA,          ProcessCEA,             R_OPEN              );

        DST_CFG(    I_OPEN,                 SEND_MESSAGE,       ISndMessage,            I_OPEN              );
        DST_CFG(    I_OPEN,                 I_RCV_MESSAGE,      Process,                I_OPEN              );
        DST_CFG(    I_OPEN,                 WATCHDOG_TIMER,     IWatchdogTimeout,       I_OPEN              );
        DST_CFG(    I_OPEN,                 I_RCV_DWR,          ProcessDWR_ISndDWA,     I_OPEN              );
        DST_CFG(    I_OPEN,                 I_RCV_DWA,          ProcessDWA,             I_OPEN              );
        DST_CFG(    I_OPEN,                 R_CONN_CER,         RReject,                I_OPEN              );
        DST_CFG(    I_OPEN,                 STOP,               ISndDPR,                CLOSING             );
        DST_CFG(    I_OPEN,                 I_RCV_DPR,          ISndDPA_IDisc,          CLOSED              );
        DST_CFG(    I_OPEN,                 I_PEER_DISC,        IDisc,                  CLOSED              );
        DST_CFG(    I_OPEN,                 I_RCV_CER,          ISndCEA,                I_OPEN              );
        DST_CFG(    I_OPEN,                 I_RCV_CEA,          ProcessCEA,             I_OPEN              );


        DST_CFG(    CLOSING,                I_RCV_DPA,          IDisc,                  CLOSED              );
        DST_CFG(    CLOSING,                R_RCV_DPA,          RDisc,                  CLOSED              );
        DST_CFG(    CLOSING,                TIMEOUT,            Error,                  CLOSED              );
        DST_CFG(    CLOSING,                I_PEER_DISC,        IDisc,                  CLOSED              );
        DST_CFG(    CLOSING,                R_PEER_DISC,        RDisc,                  CLOSED              );
    }

    ~DiameterStateTable()
    {
    }

    STATUS GetStatus(STATE nState)
    {
        switch( nState )
        {
        case STATE_I_OPEN:
            return STATUS_STARTED;

        case STATE_R_OPEN:
            return STATUS_STARTED;

        case STATE_CLOSED:
            return STATUS_STOPPED;

        case STATE_CLOSING:
            return STATUS_STOPPING;

        default:
            return STATUS_STARTING;
        }
    }
};

#endif
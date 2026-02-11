#include "fsm.h"
#include "core/uprint.h"

// private variables
static state_t activeState = SS_IDLE;
static char pinBuffer[16];
static int retries = 0;

// Mock functions for hardware interaction
void displayMsg(const char* msg) { uprint("LCD: %s\r\n", msg); }
void lockDoor(void) { uprint("DOOR: Locked\r\n"); }
void unlockDoor(void) { uprint("DOOR: UNLOCKED\r\n"); }

void FSM_Init(void)
{
    activeState = SS_IDLE;
    pinBuffer[0] = '\0';
    retries = 0;
    displayMsg("System Ready");
}

void FSM_Dispatch(EventID_t id, EventParams_t *params)
{
    switch (activeState)
    {
        case SS_IDLE:
            if(id == EV_NULL)
            {
                if(retries >= 3)
                {
                    activeState = SS_ERROR;
                    displayMsg("MAX RETRIES EXCEED");
                }else
                {
                    retries++;
                    activeState = SS_ACCEPTING;
                    displayMsg("Enter PIN: ");
                }
            }
            break;
        
        case SS_ACCEPTING:
            if(id == EV_KEYPRESS)
            {
                if(params->key == 'C') // cancel
                {
                    retries = 0;
                    displayMsg("Cancelled");
                    activeState = SS_IDLE;
                    pinBuffer[0] = '\0';
                }else if(params->key >= '0' && params->key <= '9') // is digit
                {
                    strncat(pinBuffer, &params->key, 1);
                    activeState = SS_ACCEPTING;
                }else if(params->key == 'E') // enter
                {
                    activeState = SS_CHECKING_LENGTH;

                    // trigger a null event immediately for the next step
                    FSM_Dispatch(EV_NULL, NULL);
                }
            }
            break;
        
        case SS_CHECKING_LENGTH:
            if(id == EV_NULL)
            {
                if(strlen(pinBuffer) == 4)
                {
                    activeState = SS_VALIDATING_PIN;
                    FSM_Dispatch(EV_NULL, NULL);
                }else
                {
                    displayMsg("WRONG LENGTH");
                    activeState = SS_IDLE;
                    pinBuffer[0] = '\0';
                }
            }
            break;

        case SS_VALIDATING_PIN:
            if(id == EV_NULL)
            {
                if(strcmp(pinBuffer, "1234") == 0) // is valid
                {
                    unlockDoor();
                    activeState = SS_SECURITY_OPEN;
                }else
                {
                    displayMsg("INVALID PIN");
                    activeState = SS_IDLE;
                    pinBuffer[0] = '\0';
                }
            }
            break;

            case SS_SECURITY_OPEN:
                if(id == EV_KEYPRESS && params->key == 'R')
                {
                    lockDoor();
                    retries = 0;
                    activeState = SS_IDLE;
                    pinBuffer[0] = '\0';
                }
                break;



        default: break;
    }
}
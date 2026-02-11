#ifndef INC_FSM_H_
#define INC_FSM_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// States
typedef enum{
    SS_IDLE,
    SS_ACCEPTING,
    SS_CHECKING_LENGTH,
    SS_VALIDATING_PIN,
    SS_SECURITY_OPEN,
    SS_ERROR
}state_t;

// Events
typedef enum{
    EV_NULL,
    EV_KEYPRESS,
    EV_RESET
} EventID_t;

// Event Parameters
typedef struct
{
    char key;
}EventParams_t;

void FSM_Init(void);
void FSM_Dispatch(EventID_t id, EventParams_t *params);

#endif /* INC_FSM_H_ */
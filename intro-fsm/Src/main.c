#include "config.h"
#include "fsm.h"
#include "core/uprint.h"
#include "interface/interface.h"
#include "interface_defines.h"

int main(void)
{
    config_app();

    FSM_Init();

    Comm_Interface_t *serial = Comm_ProtocolGet(INTERFACE_PROTOCOL_UART2);

    FSM_Dispatch(EV_NULL, NULL); // enter accept mode

    while(1)
    {
        if(serial->data_available())
        {
            char c;
            serial->receive((uint8_t*)&c, 1);
            //uprint("%c", c);

            EventParams_t p = {.key = c};
            FSM_Dispatch(EV_KEYPRESS, &p);
        }

        /*
        if (some_condition) // enter accept mode
        {
            FSM_Dispatch(EV_NULL, NULL);
        }*/

    }
}

#include "config.h"
#include "core/uprint.h"
#include "sensor.h"
#include "queue.h"

int main(void)
{
    config_app();

    Sensor *p_Sensor;
    p_Sensor = Sensor_Create();
    p_Sensor->value = 47;
    uprint("The current value from sensor is %d\r\n", Sensor_getValue(p_Sensor));
    Sensor_Destroy(p_Sensor);


    int j, k, h, t;

    /* test normal queue */
    uprint("Queue test program\r\n");

    Queue *myQ;
    myQ = Queue_Create();
    k = 1000;
    for(j = 0; j < QUEUE_SIZE; j++)
    {
        h = myQ->head;
        myQ->insert(myQ, k);
        uprint("Inserting %d at position %d, size %d\r\n", k--, h, myQ->getSize(myQ));
    }

    uprint("Inserted %d elements\r\n", myQ->getSize(myQ));

    for(j = 0; j < QUEUE_SIZE; j++)
    {
        t = myQ->tail;
        k = myQ->remove(myQ);
        uprint("Removing %d at position %d, size %d\r\n", k, t, myQ->getSize(myQ));
    }

    uprint("Last item removed = %d\r\n", k);
    uprint("Current queue size = %d\r\n", myQ->getSize(myQ));


    while(1)
    {
    }
}

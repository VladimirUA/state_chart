#include "state_machine.h"

int main()
{ 
    state_machine fsm;
    fsm.initiate();

    fsm.process_event(watchdog { 0 }); //will be unconsumed
    fsm.process_event(turn_on {});
    fsm.process_event(watchdog { 1 });
    fsm.process_event(start {});
    fsm.process_event(watchdog { 2 });
    fsm.process_event(finish {});
    fsm.process_event(watchdog { 3 });
    fsm.process_event(turn_off {});
    fsm.process_event(watchdog { 4 }); //will be unconsumed

    return 0;
}
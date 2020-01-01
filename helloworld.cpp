#include "state_machine.h"

int main()
{ 
    state_machine fsm;
    fsm.initiate();

    fsm.process_event(turn_on {});
    fsm.process_event(start {});
    fsm.process_event(finish {});
    fsm.process_event(turn_off {});

    return 0;
}
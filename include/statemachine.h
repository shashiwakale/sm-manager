/* File Name: stateMachine.h
 *
 * Description: Auto Generated File for state machine app
 * Date:27-10-2022 17:12:41
 * Author: Microsoft Visual Basic Applications
 */


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_


/*Start of file*/
enum event{
    INV_EVENT = -1,
    START,
    PROCESS,
    STOP ,
    RETURN,
    MAX_EVENTS,
};

enum state{
    INV_STATE = -1,
    WAIT ,
    RUN ,
    EXECUTE,
    TERMINATE,
    MAX_STATES,
};


void wait (void* );
void pre_wait (void* );
void post_wait (void* );
void run (void* );
void pre_run (void* );
void post_run (void* );
void execute(void* );
void pre_execute(void* );
void post_execute(void* );
void terminate(void* );
void pre_terminate(void* );
void post_terminate(void* );




#endif /* STATEMACHINE_H_ */





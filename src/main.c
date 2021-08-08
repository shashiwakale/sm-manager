/*
 * main.c
 *
 *  Created on: 01-Aug-2021
 *      Author: Shashikant S. Wakale
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <stdint.h>

#include "StateMachine.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
/*State Machines States*/
enum state
{
    INV_STATE=-1,
    WAIT,
    RUN,
    EXECUTE,
    TERMINATE,
    MAX_STATES,
};

/*State Machines Events*/
enum event
{
    INV_EVENT=-1,
    START,
    PROCESS,
    STOP,
    RETURN,
    MAX_EVENTS,
};

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/
void wait(void);
void run(void);
void execute(void);
void terminate(void);

/*State Transition Table*/
int32_t StateTransitionTable[MAX_EVENTS][MAX_STATES] =
{               /*WAIT,     RUN,        EXECUTE,    TERMINATE*/
 /*START*/      {RUN,       INV_STATE,  INV_STATE, INV_STATE},
 /*PROCESS*/    {INV_STATE, EXECUTE,    INV_STATE, INV_STATE},
 /*STOP*/       {INV_STATE, INV_STATE,  TERMINATE, INV_STATE},
 /*RETURN*/     {WAIT,      WAIT,       WAIT,      WAIT},
};

/*State Functions*/
void (*FunctionPointer[MAX_STATES])() =
{
        &wait,
        &run,
        &execute,
        &terminate
};

/*
 * Function Name            : myThreadFun
 * Function ID              : SM_MAIN_FUNC_001
 * Description              : -
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : -
 * Arguments                : -
 * Return Value             : -
 * */
void *myThreadFun(void *vargp)
{
    while(1)
    {
        StateMachineRun();
        usleep(500);
    }

    return NULL;
}

/*
 * Function Name            : main
 * Function ID              : SM_MAIN_FUNC_002
 * Description              : Application Entry
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : -
 * Arguments                : -
 * Return Value             : -
 * */
int main()
{
    pthread_t thread_id;
    InitStateMachine(&StateTransitionTable[0][0], &FunctionPointer, WAIT);

    pthread_create(&thread_id, NULL, myThreadFun, NULL);

    while(1)
    {
        PostEvent(START);
        sleep(1);
        PostEvent(PROCESS);
        sleep(1);
        PostEvent(STOP);
        sleep(1);
        PostEvent(RETURN);
        sleep(1);
    }
    return 0;
}

/*
 * Function Name            : wait
 * Function ID              : SM_MAIN_FUNC_003
 * Description              : -
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : -
 * Arguments                : -
 * Return Value             : -
 * */
void wait(void)
{
    printf("waiting....!\n");
}

/*
 * Function Name            : run
 * Function ID              : SM_MAIN_FUNC_004
 * Description              : -
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : -
 * Arguments                : -
 * Return Value             : -
 * */
void run(void)
{
    printf("run....!\n");
}

/*
 * Function Name            : execute
 * Function ID              : SM_MAIN_FUNC_005
 * Description              : -
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : -
 * Arguments                : -
 * Return Value             : -
 * */
void execute(void)
{
    printf("execute....!\n");
}

/*
 * Function Name            : terminate
 * Function ID              : SM_MAIN_FUNC_006
 * Description              : -
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : -
 * Arguments                : -
 * Return Value             : -
 * */
void terminate(void)
{
    printf("terminate....!\n");
}

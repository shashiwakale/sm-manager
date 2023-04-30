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

#include "sm.h"
#include "statemachine.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
/* File Name: stateMachine.c
 *
 * Description: Auto Generated File for state machine app
 * Date:27-10-2022 17:22:13
 * Author: Microsoft Visual Basic Applications
 */


int32_t StateTransitionTable[MAX_EVENTS][MAX_STATES] =
{
    {RUN,             INV_STATE,       INV_STATE,       INV_STATE},
    {INV_STATE,       EXECUTE,         INV_STATE,       INV_STATE},
    {INV_STATE,       INV_STATE,       TERMINATE,       INV_STATE},
    {WAIT ,           WAIT,            WAIT,            WAIT}
};

void (*FunctionPointer[])(void* p_pvData) =
{
    &wait ,
    &pre_wait ,
    &post_wait ,
    &run ,
    &pre_run ,
    &post_run ,
    &execute,
    &pre_execute,
    &post_execute,
    &terminate,
    &pre_terminate,
    &post_terminate,
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
    InitStateMachine(&StateTransitionTable[0][0], &FunctionPointer, WAIT, MAX_STATES);

    pthread_create(&thread_id, NULL, myThreadFun, NULL);

    sleep(1);

    while(1)
    {
        PostEvent(START, "START Event");
        sleep(1);
        PostEvent(PROCESS, "Process Event");
        sleep(1);
        PostEvent(STOP, "Stop Event");
        sleep(1);
        PostEvent(RETURN, "Return Event");
        sleep(1);
    }
    return 0;
}

void pre_wait (void* p_pvData)
{
    /*Write your code here*/
    printf("pre_wait \n");
};

void wait (void* p_pvData)
{
    /*Write your code here*/
    char* data = (char*)p_pvData;
    printf("wait %s\n", data);
};

void post_wait (void* p_pvData)
{
    /*Write your code here*/
    printf("post_wait \n");
};

void pre_run (void* p_pvData)
{
    /*Write your code here*/
    printf("pre_run \n");
};

void run (void* p_pvData)
{
    /*Write your code here*/
    char* data = (char*)p_pvData;
    printf("run %s\n", data);
};

void post_run (void* p_pvData)
{
    /*Write your code here*/
    printf("post_run \n");
};

void pre_execute(void* p_pvData)
{
    /*Write your code here*/
    printf("pre_execute\n");
};

void execute(void* p_pvData)
{
    /*Write your code here*/
    char* data = (char*)p_pvData;
    printf("execute %s\n", data);
};

void post_execute(void* p_pvData)
{
    /*Write your code here*/
    printf("post_execute\n");
};

void pre_terminate(void* p_pvData)
{
    /*Write your code here*/
    printf("pre_terminate\n");
};

void terminate(void* p_pvData)
{
    /*Write your code here*/
    char* data = (char*)p_pvData;
    printf("terminate %s\n", data);
};

void post_terminate(void* p_pvData)
{
    /*Write your code here*/
    printf("post_terminate\n");
};



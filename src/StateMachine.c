/*
 * StateMachine.c
 *
 *  Created on: 01-Aug-2021
 *      Author: Shashikant S. Wakale
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "StateMachine.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
static uint32_t g_stat_u32CurrentState = INVAL_STATE;
static uint32_t g_stat_u32PreviousState = INVAL_STATE;
static uint32_t g_stat_u32PreviousEvent = INVAL_EVENT;
static const int32_t *g_stat_StateTransitionTable = NULL;
static void (* const *g_stat_FunctionPointer)();

/******************************************************************************
 * Static Functions
 *****************************************************************************/
/*
 * Function Name            : InitStateMachine
 * Function ID              : SM_FUNC_001
 * Description              : Initializes state machine
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: g_stat_StateTransitionTable, g_stat_FunctionPointer, g_stat_u32CurrentState
 * Global Arguments Refer   : -
 * Arguments                : p_cn_ps32SMTable: State Transition Table
 *                            p_cn_pvStateFunc: State Functions
 *                            p_cn_s32DefaultState: Default State
 * Return Value             : -
 * */
void InitStateMachine(const int32_t *p_cn_ps32SMTable, const void *p_cn_pvStateFunc, const int32_t p_cn_s32DefaultState)
{
    if(NULL != p_cn_ps32SMTable)
    {
        g_stat_StateTransitionTable = p_cn_ps32SMTable;

        if(NULL != p_cn_pvStateFunc)
        {
            g_stat_FunctionPointer = p_cn_pvStateFunc;
            g_stat_u32CurrentState = p_cn_s32DefaultState;
        }
        else
        {
            printf("[STATE MACHINE]: Function pointer empty!\n");
        }
    }
    else
    {
        printf("[STATE MACHINE]: State Transition Table is Empty!\n");
    }
}

/*
 * Function Name            : StateMachineRun
 * Function ID              : SM_FUNC_002
 * Description              : Executes state machine
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: -
 * Global Arguments Refer   : g_stat_u32CurrentState, g_stat_u32PreviousState, g_stat_FunctionPointer
 * Arguments                : -
 * Return Value             : -
 * */
void StateMachineRun()
{
    if(g_stat_u32CurrentState != g_stat_u32PreviousState)
    {
        if(g_stat_u32CurrentState != INVAL_STATE)
        {
            (g_stat_FunctionPointer[g_stat_u32CurrentState])();
        }
        g_stat_u32PreviousState = g_stat_u32CurrentState;
    }
}

/*
 * Function Name            : PostEvent
 * Function ID              : SM_FUNC_003
 * Description              : Triggers state machine event
 * Author                   : Shashi
 * Date                     : 01-Aug-21
 * Global Arguments Modified: g_stat_u32CurrentState
 * Global Arguments Refer   : g_stat_StateTransitionTable, g_stat_FunctionPointer,
 * Arguments                : p_cn_s32Event- Event ID
 * Return Value             : -
 * */
void PostEvent(const int32_t p_cn_s32Event)
{
    uint32_t l_u32EventID = INVAL_EVENT;

    if(g_stat_u32PreviousEvent != p_cn_s32Event)
    {
        g_stat_u32PreviousEvent = p_cn_s32Event;
        l_u32EventID = *(g_stat_StateTransitionTable + ((p_cn_s32Event + (g_stat_u32CurrentState*sizeof(int32_t)))));
        if(l_u32EventID != INVAL_EVENT)
        {
            g_stat_u32CurrentState = l_u32EventID;
        }
    }
}

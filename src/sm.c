/*
 * sm.c
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
#include "sm.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
static uint32_t g_stat_u32CurrentState = INVAL_STATE;
static uint32_t g_stat_u32PreviousState = INVAL_STATE;
static uint32_t g_stat_u32PreviousEvent = INVAL_EVENT;
static const int32_t *g_stat_StateTransitionTable = NULL;
static void (* const *g_stat_FunctionPointer)();
const int8_t PRE_EVENT = 1;
const int8_t POST_EVENT = 2;
static int32_t g_s32MaxStates = 0;
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
void InitStateMachine(const int32_t *p_cn_ps32SMTable, const void *p_cn_pvStateFunc,
        const int32_t p_cn_s32DefaultState, const int32_t p_cn_s32MaxState)
{
    if(NULL != p_cn_ps32SMTable)
    {
        g_s32MaxStates = p_cn_s32MaxState;
        g_stat_StateTransitionTable = p_cn_ps32SMTable;

        if(NULL != p_cn_pvStateFunc)
        {
            g_stat_FunctionPointer = p_cn_pvStateFunc;
            g_stat_u32CurrentState = p_cn_s32DefaultState;
        }
        else
        {
            printf("[SM]: Function pointer empty!\n");
        }
    }
    else
    {
        printf("[SM]: State Transition Table is Empty!\n");
    }
    printf("[SM]: Starting State Machine Manager...\n");
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
    uint32_t localState = g_stat_u32CurrentState;

    if(localState != g_stat_u32PreviousState)
    {
        if(localState != INVAL_STATE)
        {
            (g_stat_FunctionPointer[(localState * 3) + PRE_EVENT])(); //Execute before event function
            (g_stat_FunctionPointer[(localState * 3)])(); //Execute main event function
            (g_stat_FunctionPointer[(localState * 3) + POST_EVENT])(); //Execute after event function
        }
        g_stat_u32PreviousState = localState;
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
    g_stat_u32PreviousEvent = p_cn_s32Event;
//    Address of A[I][J] = B + W * ((I – LR) * N + (J – LC))
//    I = Row Subset of an element whose address to be found,
//    J = Column Subset of an element whose address to be found,
//    B = Base address,
//    W = Storage size of one element store in an array(in byte),
//    LR = Lower Limit of row/start row index of the matrix(If not given assume it as zero),
//    LC = Lower Limit of column/start column index of the matrix(If not given assume it as zero),
//    N = Number of column given in the matrix.
    l_u32EventID = *(g_stat_StateTransitionTable + (((p_cn_s32Event - 0)*g_s32MaxStates + (g_stat_u32CurrentState - 0))));

    if(l_u32EventID != INVAL_EVENT)
    {
        g_stat_u32CurrentState = l_u32EventID;
    }
    else
    {
        printf("Invalid event \n");
    }
}

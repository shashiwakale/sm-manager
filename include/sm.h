/*
 * StateMachine.h
 *
 *  Created on: 01-Aug-2021
 *      Author: Shashikant S. Wakale
 */

#ifndef INCLUDE_SM_H_
#define INCLUDE_SM_H_

/******************************************************************************
 * Includes
 *****************************************************************************/

/******************************************************************************
 * defines
 *****************************************************************************/
#define INVAL_STATE -1
#define INVAL_EVENT -1

/******************************************************************************
 * Public Functions
 *****************************************************************************/
void StateMachineRun();
void PostEvent(int32_t p_s32Event);
void InitStateMachine(const int32_t *p_cn_ps32SMTable, const void *p_cn_pvStateFunc,
        const int32_t p_cn_s32DefaultState, const int32_t p_cn_s32MaxState);

#endif /* INCLUDE_SM_H_ */

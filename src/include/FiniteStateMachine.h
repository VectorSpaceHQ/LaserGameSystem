/*
 * fsm.h
 * Finite State Machine
 *
 *  Created on: Mar 10, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_FINITESTATEMACHINE_H_
#define INCLUDE_FINITESTATEMACHINE_H_

#include <functional>
#include "GameSystemDefs.h"
#include "GameSystemEvents.h"


namespace GameSystem
{
   typedef std::function<void()> FsmTransition;
   typedef std::function<bool(Events e, void* data)> FsmHandler;

   struct FiniteState
   {
      char const*    name;
      FsmTransition  Enter;
      FsmHandler     Handle;
      FsmTransition  Exit;

      FiniteState(char const*    _name,
                  FsmTransition  _enter,
                  FsmHandler     _handler,
                  FsmTransition  _exit):
         name(_name),
         Enter(_enter),
         Handle(_handler),
         Exit(_exit)
      {
      }
   };


   class FiniteStateMachine
   {
   protected:
      FiniteState* currState;

   public:
      FiniteStateMachine(FiniteState* initialState):
         currState(initialState)
      {
      }

      ~FiniteStateMachine() {};

      void Start()
      {
         if(currState->Enter != nullptr)
         {
            currState->Enter();
         }
      }


      void Transition(FiniteState* newState)
      {
         if(currState->Exit != nullptr)
         {
            currState->Exit();
         }

         currState = newState;

         if(currState->Enter != nullptr)
         {
            currState->Enter();
         }
      }


      bool HandleEvent(Events e, void* data)
      {
         if(currState->Handle != nullptr)
         {
            return currState->Handle(e, data);
         }
         else
         {
            return false;
         }
      }

   };
}

#endif /* INCLUDE_FINITESTATEMACHINE_H_ */

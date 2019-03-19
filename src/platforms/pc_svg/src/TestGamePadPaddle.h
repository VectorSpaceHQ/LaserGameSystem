/*
 * GamePadPaddle.h
 *
 *  Created on: Mar 11, 2019
 *      Author: athiessen
 */

#ifndef __TEST_GAMEPAD_PADDLE_H__
#define __TEST_GAMEPAD_PADDLE_H__

#include "GamePad.h"
#include "GameSystemDefs.h"


class TestGamePadPaddle: public GameSystem::GamePad
{
private:
   GameSystem::GamePadId   gamePadId;
   uint32_t                axisLeftX;
   bool                    buttonA;
   uint32_t                frameCtr;

public:
   TestGamePadPaddle(GameSystem::GamePadId _id);
   ~TestGamePadPaddle();

   virtual GameSystem::GamePadId GetId();
   virtual int32_t GetAxis(GameSystem::AxisId axis);
   virtual bool GetButton(GameSystem::ButtonId button);
   virtual void Run();

};


#endif /* __TEST_GAMEPAD_PADDLE_H__ */

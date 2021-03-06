/*
 * GamePad.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_INCLUDE_GAMEPAD_H_
#define SRC_INCLUDE_GAMEPAD_H_

#include "GameSystemDefs.h"

namespace GameSystem
{
   class GamePad
   {
   public:
      virtual GamePadId GetId() = 0;
      virtual uint32_t  GetAxis(AxisId axis) = 0;
      virtual bool      GetButton(ButtonId button) = 0;
      virtual void      Run() = 0;

   protected:
      GamePad() {};
      virtual ~GamePad() {}

   };

}

#endif /* SRC_INCLUDE_GAMEPAD_H_ */

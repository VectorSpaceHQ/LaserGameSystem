/*
 * GameSystem.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEM_H_
#define INCLUDE_GAMESYSTEM_H_

#include <Canvas.h>
#include <DisplayIfc.h>
#include <hal.h>
#include <stdint.h>
#include "Program.h"
#include "Programs.h"


namespace GameSystem
{
   class System
   {
   private:
      HAL::Hal&   hal;
      Canvas      canvas;
      Programs    programs;
      Program&    currentProgram;
      uint32_t    runTime;

      static const uint32_t   GameWidth;
      static const uint32_t   GameHeight;

   public:
      System(HAL::Hal& _hal, DisplayIfc& _displayImpl);

      void Start(uint32_t _runTime);
      void Run();

      void StartCurrentProgram();
      void StopCurrentProgram();
};

}


#endif /* INCLUDE_GAMESYSTEM_H_ */

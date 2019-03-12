/*
 * Calibrate.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef PROGRAMS_CALIBRATE_CALIBRATE_H_
#define PROGRAMS_CALIBRATE_CALIBRATE_H_

#include "CommonShapes.h"
#include "CursorShape.h"
#include "GameSystemEvents.h"
#include "GamePad.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"


class Calibrate: public GameSystem::Program
{
private:
   CursorShape*            cursor;
   Shape*                  border;

public:
   Calibrate(Canvas&                _display,
             GameSystem::GamePad&   _gamePad1,
             GameSystem::GamePad&   _gamePad2);
   ~Calibrate() {};

   void Init();
   void Start();
   void Stop();
   void Run();
   void Draw();
   void HandleEvent(GameSystem::Events event, void* data);
};


#endif /* PROGRAMS_CALIBRATE_CALIBRATE_H_ */

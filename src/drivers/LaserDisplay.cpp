/*
 * LaserDisplay.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>
#include "Canvas.h"
#include "Hal.h"
#include "LaserDisplay.h"
#include "Shape.h"
#include "stm32f4xx.h"
#include "spi.h"

#define DAC_A     (0x00)
#define DAC_B     (0x80)
#define DAC_BUF   (0x40)
#define DAC_NGA   (0x20)
#define DAC_NSHDN (0x10)

LaserDisplay::LaserDisplay(HAL::Hal& _hal):
   hal(_hal),
   activeVerts(0, static_cast<int>(CoordMax)),
   backgroundVerts(0, static_cast<int>(CoordMax)),
   newVerts(false),
   vertIndex(0)
{
   spi_setup();
}

void LaserDisplay::Update()
{
   uint8_t dacCmd[2];

   if (vertIndex >= activeVerts.rows())
   {
      if (newVerts)
      {
         activeVerts = backgroundVerts;
         newVerts = false;
      }

      vertIndex = 0;
   }

   if (activeVerts.rows() > 0)
   {
      int16_t x = activeVerts(vertIndex, CoordX) + 2047;
      int16_t y = activeVerts(vertIndex, CoordY) + 2047;

      dacCmd[0] = DAC_A | DAC_NGA | DAC_NSHDN | (0x0F & (x >> 8));
      dacCmd[1] = 0xFF & x;
      spi_transfer(dacCmd, NULL, 2);

      dacCmd[0] = DAC_B | DAC_NGA | DAC_NSHDN | (0x0F & (y >> 8));
      dacCmd[1] = 0xFF & y;
      spi_transfer(dacCmd, NULL, 2);

      vertIndex++;
   }
}


void LaserDisplay::Render(Eigen::Ref<const VertexList_t> vertices)
{
   backgroundVerts = vertices;
   newVerts = true;
}

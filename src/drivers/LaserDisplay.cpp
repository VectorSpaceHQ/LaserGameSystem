/*
 * LaserDisplay.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>
#include <memory.h>
#include <stdlib.h>
#include "Canvas.h"
#include "CanvasObject.h"
#include "Hal.h"
#include "LaserDisplay.h"
#include "stm32f4xx.h"
#include "spi.h"

#define DAC_A     (0x00)
#define DAC_B     (0x80)
#define DAC_BUF   (0x40)
#define DAC_NGA   (0x20)
#define DAC_NSHDN (0x10)

LaserDisplay::LaserDisplay(HAL::Hal& _hal):
   hal(_hal),
   activeVerts(),
   backgroundVerts(),
   newVerts(false),
   vertIndex(0),
   numActivePts(0),
   numBackgroundPts(0)
{
   spi_setup();
}

void LaserDisplay::Update()
{
   uint8_t dacCmd[2];

   if (vertIndex >= numActivePts)
   {
      if (newVerts)
      {
         if(activeVerts)
         {
            // Free the previously-allocated set of points
            free(activeVerts);
         }

         activeVerts = backgroundVerts;

         if(activeVerts)
         {
            numActivePts = numBackgroundPts;
            numBackgroundPts = 0;
         }
         else
         {
            numActivePts = 0;
         }

         newVerts = false;
      }

      vertIndex = 0;
   }

   if (activeVerts && (numActivePts > 0))
   {
      uint16_t x = activeVerts[vertIndex].x;
      uint16_t y = activeVerts[vertIndex].y;

      if (activeVerts[vertIndex].c)
      {
         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
      }
      else
      {
         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
      }

      dacCmd[0] = DAC_A | DAC_NGA | DAC_NSHDN | (0x0F & (x >> 8));
      dacCmd[1] = 0xFF & x;
      spi_transfer(dacCmd, NULL, 2);

      dacCmd[0] = DAC_B | DAC_NGA | DAC_NSHDN | (0x0F & (y >> 8));
      dacCmd[1] = 0xFF & y;
      spi_transfer(dacCmd, NULL, 2);

      vertIndex++;
   }
}


void LaserDisplay::Render(VertexListRef vertices)
{
   numBackgroundPts = vertices.rows();

   // Convert from Cartesian -- Invert Y axis
   vertices.block(0, CoordY, numBackgroundPts, 1) *= -1;
   vertices.block(0, CoordX, numBackgroundPts, 1) += 2047;
   vertices.block(0, CoordY, numBackgroundPts, 1) += 2047;

   backgroundVerts = new LaserPoint[numBackgroundPts];

   if(backgroundVerts)
   {
      for(uint16_t cntr = 0; cntr < numBackgroundPts; cntr++)
      {
         backgroundVerts[cntr].x = static_cast<uint16_t>(vertices(cntr, CoordX));
         backgroundVerts[cntr].y = static_cast<uint16_t>(vertices(cntr, CoordY));
         backgroundVerts[cntr].c = static_cast<uint16_t>(vertices(cntr, CoordColor));
      }

      newVerts = true;
   }
   else
   {
      numBackgroundPts = 0;
      newVerts = false;
   }
}

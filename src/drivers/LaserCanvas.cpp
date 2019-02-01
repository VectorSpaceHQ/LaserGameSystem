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


LaserDisplay::LaserDisplay(HAL::Hal& _hal):
   hal(_hal)
{
}


void LaserDisplay::Update()
{
}


void LaserDisplay::Render(Eigen::Ref<const VertexList_t> vertices)
{
   int32_t  numVertices = vertices.rows();
   hal.GetOnOffSwitch(HAL::HAL_ID_MAIN_LIGHT)->Toggle();
}

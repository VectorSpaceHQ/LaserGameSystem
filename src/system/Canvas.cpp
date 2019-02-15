/*
 * Canvas.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>

#include "Canvas.h"
#include "CanvasObject.h"
#include "Shape.h"


Canvas::Canvas(uint32_t _width, uint32_t _height, DisplayIfc& _displayImpl):
   width(_width),
   height(_height),
   top(-(height / 2)),
   right(width / 2),
   bottom(height / 2),
   left(-(width / 2)),
   displayIfc(_displayImpl),
   objects(),
   allVertices(0, static_cast<int>(CoordMax))
{
}


void Canvas::Render()
{
   CollectVertices();

   // TODO: Perform transformations like skew here

   // After transformations, then render the updates on the implementation
   displayIfc.Render(allVertices);
}


void Canvas::Clear()
{
   // Another module is responsible for the allocation of memory for the shapes
   // thus, we just need to clear our list of pointers.
   objects.clear();
}


void Canvas::AddObject(CanvasObject* newObject)
{
   objects.push_back(newObject);
}


int32_t Canvas::TotalVertices()
{
   CanvasObjectList_t::iterator  it;
   int32_t                       vertexCnt = 0;

   for(it = objects.begin(); it != objects.end(); ++it )
   {
      vertexCnt += (*it)->NumPoints();
   }

   return vertexCnt;
}


/***
 * http://eigen.tuxfamily.org/dox/group__TutorialMapClass.html
 */
void Canvas::CollectVertices()
{
   CanvasObjectList_t::iterator  it;
   int32_t                       vertexCntr = 0;

   allVertices.resize(TotalVertices(), CoordMax);

   for(it = objects.begin(); it != objects.end(); ++it )
   {
      int32_t  objectVertices = (*it)->NumPoints();

      vertexCntr += (*it)->MapVertices(allVertices.block(vertexCntr, 0, objectVertices, CoordMax));
   }
}

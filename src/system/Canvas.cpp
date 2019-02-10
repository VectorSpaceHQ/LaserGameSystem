/*
 * Canvas.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>

#include "Canvas.h"
#include "Shape.h"


Canvas::Canvas(DisplayIfc& _displayImpl):
   displayIfc(_displayImpl),
   shapes(),
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
   shapes.clear();
}


void Canvas::AddShape(Shape* newShape)
{
   shapes.push_back(newShape);
}


int32_t Canvas::TotalVertices()
{
   ShapeList_t::iterator   it;
   int32_t                 vertexCnt = 0;

   for(it = shapes.begin(); it != shapes.end(); ++it )
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
   ShapeList_t::iterator   it;
   int32_t                 vertexCntr = 0;

   allVertices.resize(TotalVertices(), CoordMax);

   for(it = shapes.begin(); it != shapes.end(); ++it )
   {
      int32_t  shapeVertices = (*it)->NumPoints();

      vertexCntr += (*it)->MapVertices(allVertices.block(vertexCntr, 0, shapeVertices, CoordMax));
   }
}

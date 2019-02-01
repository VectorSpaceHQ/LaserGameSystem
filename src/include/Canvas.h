/*
 * Canvas.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <DisplayIfc.h>
#include <list>
#include "ScheduledInterval.h"
#include "Shape.h"


class Canvas: public ScheduledInterval
{
private:
   typedef std::list<Shape*>  ShapeList_t;

   DisplayIfc&    displayIfc;
   ShapeList_t    shapes;
   VertexList_t   allVertices;

public:
   Canvas(DisplayIfc& _displayImpl);
   ~Canvas() {};

   void Update();
   void Clear();
   void AddShape(Shape* newShape);

private:
   void Render();

   /***
    * Iterate over all the shapes and sum up the number of vertices
    */
   int32_t  TotalVertices();

   void CollectVertices();
};


#endif /* __CANVAS_H__ */

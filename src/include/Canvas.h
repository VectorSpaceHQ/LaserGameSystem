/*
 * Canvas.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <list>

#include "DisplayIfc.h"
#include "Shape.h"


class Canvas
{
private:
   typedef std::list<Shape*>  ShapeList_t;

   DisplayIfc&    displayIfc;
   ShapeList_t    shapes;
   VertexList_t   allVertices;

public:
   Canvas(DisplayIfc& _displayImpl);
   ~Canvas() {};

   void Clear();
   void AddShape(Shape* newShape);
   void Render();

private:
   /***
    * Iterate over all the shapes and sum up the number of vertices
    */
   int32_t  TotalVertices();

   void CollectVertices();
};


#endif /* __CANVAS_H__ */

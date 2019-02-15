/*
 * Canvas.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <list>

#include "CanvasObject.h"
#include "DisplayIfc.h"


class Canvas
{
private:
   typedef std::list<CanvasObject*>  ObjectList_t;

   DisplayIfc&    displayIfc;
   ObjectList_t   objects;
   VertexList_t   allVertices;

public:
   Canvas(DisplayIfc& _displayImpl);
   ~Canvas() {};

   void Clear();
   void AddObject(CanvasObject* newObject);
   void Render();

private:
   /***
    * Iterate over all the shapes and sum up the number of vertices
    */
   int32_t  TotalVertices();

   void CollectVertices();
};


#endif /* __CANVAS_H__ */

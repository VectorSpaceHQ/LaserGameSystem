
#include <DisplayIfc.h>
#include <hal.h>
#include <list>
#include <iostream>
#include <fstream>

#include "CanvasObject.h"
#include "SVGDisplay.h"


SVGDisplay::SVGDisplay(HAL::Hal& _hal):
   hal(_hal),
   numFrames(0),
   frames()
{
}


SVGDisplay::~SVGDisplay()
{
   // TODO: clean up memory used by our Frames list
   //       Not really necessary because we're exiting the program
}


void SVGDisplay::Render(VertexListRef vertices)
{
   Frame* newFrame = new Frame(hal.GetTime(), vertices);

   // Convert from Cartesian -- Invert Y axis
   newFrame->points.block(0, CoordY, newFrame->points.rows(), 1) *= -1;

   frames.push_back(newFrame);
   numFrames++;
}


void SVGDisplay::PrintFrames(char const * fileName)
{
   FrameList_t::iterator   it;
   int                     frameCntr = 0;
   uint32_t                prevTime = 0;
   std::ofstream           svgFile;

   svgFile.open(fileName);
   svgFile << "<svg viewBox=\"-2048 -2048 4096 4096\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
   svgFile << "<g>" << std::endl;
   svgFile << "   <path id=\"frame\" fill=\"none\" stroke=\"navy\" d=\"\">" << std::endl;

   for(it = frames.begin(); it != frames.end(); ++it )
   {
      uint32_t nextTime = (*it)->startTime;

      FrameList_t::iterator next = std::next(it, 1);

      if(next != frames.end())
      {
         nextTime = (*next)->startTime;
      }
      else
      {
         nextTime = hal.GetTime();
      }

      svgFile << "   <set"
              << " id=\"frame" << frameCntr << "\"";

      if(frameCntr == 0)
      {
         svgFile << " begin=\"0ms;frame" << (numFrames - 1) << ".end\"";
      }
      else
      {
         svgFile << " begin=\"frame" << frameCntr - 1 << ".end\"";
      }

      svgFile << " dur=\"" << nextTime - prevTime << "ms\""
              << " attributeName=\"d\""
              << " fill=\"remove\""
              << " to=\"";

      for(int pointCtr = 0; pointCtr < (*it)->points.rows(); pointCtr++)
      {
         CoordType x = (*it)->points(pointCtr, CoordX);
         CoordType y = (*it)->points(pointCtr, CoordY);
         CoordType d = (*it)->points(pointCtr, CoordColor);

         if(d == 0)
         {
            svgFile << " M " << x << "," << y;
         }
         else
         {
            svgFile << " L " << x << "," << y;
         }
      }

      svgFile << " z\" />" << std::endl;

      prevTime = nextTime;
      frameCntr++;
   }

   svgFile << "   </path>" << std::endl;
   svgFile << "</g>" << std::endl;
   svgFile << "</svg>" << std::endl;
   svgFile.close();
}



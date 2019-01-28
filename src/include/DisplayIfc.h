/*
 * DisplayIfc.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_DISPLAYIFC_H_
#define INCLUDE_DISPLAYIFC_H_


class DisplayIfc
{
public:
   virtual void Render() = 0;

protected:
   virtual ~DisplayIfc() {}
   DisplayIfc() {}
};



#endif /* INCLUDE_DISPLAYIFC_H_ */

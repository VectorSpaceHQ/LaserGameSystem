/*
 * DisplayImpl.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_DISPLAYIMPL_H_
#define INCLUDE_DISPLAYIMPL_H_


class DisplayImpl
{
public:
   virtual void Update() = 0;
   virtual void Render() = 0;

protected:
   virtual ~DisplayImpl() {}
   DisplayImpl() {}
};



#endif /* INCLUDE_DISPLAYIMPL_H_ */

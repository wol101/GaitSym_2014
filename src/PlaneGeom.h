/*
 *  PlaneGeom.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 13/09/2005.
 *  Copyright 2005 Bill Sellers. All rights reserved.
 *
 */

#ifndef PlaneGeom_h
#define PlaneGeom_h

#include "Geom.h"

class PlaneGeom: public Geom
{
public:
    
    PlaneGeom(dSpaceID space, double a, double b, double c, double d);
    
#ifdef USE_OPENGL
    virtual void Draw();
#endif
};


#endif

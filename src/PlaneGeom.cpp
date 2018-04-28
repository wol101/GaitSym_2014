/*
 *  PlaneGeom.cpp
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 13/09/2005.
 *  Copyright 2005 Bill Sellers. All rights reserved.
 *
 */

#include <ode/ode.h>

#include "PlaneGeom.h"

// The plane equation is:
// a * x + b * y + c * z = d
// The plane?s normal vector is (a, b, c), and it must have length 1.

// Note: planes are non placable so do not try and place them!

PlaneGeom::PlaneGeom(dSpaceID space, double a, double b, double c, double d)
{
    // create the geom
    m_GeomID = dCreatePlane(space, a, b, c, d);
    dGeomSetData(m_GeomID, this);
}

#ifdef USE_OPENGL
void PlaneGeom::Draw()
{
    if (m_Visible == false) return;
}
#endif

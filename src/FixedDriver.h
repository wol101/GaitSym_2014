/*
 *  FixedDriver.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on Sat Jun 21 2014.
 *  Copyright (c) 2014 Bill Sellers. All rights reserved.
 *
 *  Outputs a fixed value
 *
 */

#ifndef FIXEDDRIVER_H
#define FIXEDDRIVER_H

#include "Driver.h"

class FixedDriver : public Driver
{
public:
    FixedDriver();
    ~FixedDriver();

    double GetValue(double /* time */) { return mValue; }
    void SetValue(double value) { mValue = value; }
    void ModValue(double mod) { mValue *= mod; }

protected:
    double mValue;
};

#endif // FIXEDDRIVER_H

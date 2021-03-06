/*
 *  DataTarget.cpp
 *  GaitSymODE
 *
 *  Created by Bill Sellers on Sat May 22 2004.
 *  Copyright (c) 2004 Bill Sellers. All rights reserved.
 *
 */

#include <iostream>
#include <float.h>

#include <ode/ode.h>

#include "DataTarget.h"
#include "Util.h"

// Simulation global
#include "Simulation.h"
extern Simulation *gSimulation;


DataTarget::DataTarget()
{
    m_TargetTimeListLength = -1;
    m_TargetTimeList = 0;
    m_ValueList = 0;
    m_ValueListLength = -1;
    m_Intercept = 1;
    m_Slope = 1;
    m_MatchType = linear;
    m_AbortThreshold = -DBL_MAX;
    m_Target = 0;
    m_LastMatchIndex = -1;
}

DataTarget::~DataTarget()
{
    if (m_TargetTimeList) delete [] m_TargetTimeList;
}

void DataTarget::SetTargetTimes(int size, double *targetTimes)
{
    int i;
    if (size <= 0)
    {
        std::cerr << "DataTarget::SetTargetTimes error: size = " << size << "\n";
        return;
    }
    if (m_TargetTimeListLength != size)
    {
        if (m_TargetTimeList) delete [] m_TargetTimeList;
        m_TargetTimeListLength = size;
        m_TargetTimeList = new double[m_TargetTimeListLength];
    }
    for (i = 0 ; i < m_TargetTimeListLength; i++)
    {
        m_TargetTimeList[i] = targetTimes[i];
    }
}

void DataTarget::SetTargetValues(int size, double *values)
{
    int i;
    if (size <= 0)
    {
        std::cerr << "DataTarget::SetTargetValues error: size = " << size << "\n";
        return;
    }
    if (m_ValueListLength != size)
    {
        if (m_ValueList) delete [] m_ValueList;
        m_ValueListLength = size;
        m_ValueList = new double[m_ValueListLength];
    }
    for (i = 0; i < m_ValueListLength; i++)
    {
        m_ValueList[i] = values[i];
    }
}


// returns the index if a target match time is triggered
// the tolerance needs to be lower than the distance between target times
// returns -1 if no target is found within the tolerance
int DataTarget::TargetMatch(double time, double tolerance)
{
    m_LastMatchIndex = ProtectedTargetMatch(time, tolerance);
    return m_LastMatchIndex;
}

int DataTarget::ProtectedTargetMatch(double time, double tolerance)
{
    int index = Util::BinarySearchRange(m_TargetTimeList, m_TargetTimeListLength, time);
    if (index < 0)
    {
        if (fabs(m_TargetTimeList[0] - time) <= tolerance) return 0;
        return -1;
    }
    if (index >= m_TargetTimeListLength - 1)
    {
        if (fabs(m_TargetTimeList[m_TargetTimeListLength - 1] - time) <= tolerance) return m_TargetTimeListLength - 1;
        return -1;
    }
    if (fabs(m_TargetTimeList[index] - time) <= tolerance) return index;
    if (fabs(m_TargetTimeList[index + 1] - time) <= tolerance) return index + 1;
    return -1;
}

double DataTarget::PositiveFunction(double v)
{
    switch (m_MatchType)
    {
    case linear:
        if (v > 0) return v;
        else return -v;
        break;

    case square:
        return v * v;
        break;
    }
    return 0;
}

double DataTarget::GetMatchValue(double time)
{
    double matchScore = m_Intercept - m_Slope * PositiveFunction(GetError(time));
    if (matchScore < m_AbortThreshold)
    {
        //std::cerr << "matchScore " << matchScore << "\n";
        gSimulation->SetDataTargetAbort(true);
    }
    return matchScore;
}

double DataTarget::GetMatchValue(int index)
{
    double matchScore = m_Intercept - m_Slope * PositiveFunction(GetError(index));
    if (matchScore < m_AbortThreshold)
    {
        //std::cerr << "matchScore " << matchScore << "\n";
        gSimulation->SetDataTargetAbort(true);
    }
    return matchScore;
}




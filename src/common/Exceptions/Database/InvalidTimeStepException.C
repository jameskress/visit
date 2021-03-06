// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                          InvalidTimeStepException.C                       //
// ************************************************************************* //

#include <stdio.h>                     // for sprintf
#include <InvalidTimeStepException.h>


// ****************************************************************************
//  Method: InvalidTimeStepException constructor
//
//  Arguments:
//      timestep    The invalid time step.
//      nTimestep   The total number of timesteps.
//
//  Programmer: Hank Childs
//  Creation:   September 13, 2000
//
// ****************************************************************************

InvalidTimeStepException::InvalidTimeStepException(int timestep, int nTimestep)
{
    char str[1024];
    sprintf(str, "Tried to access invalid timestep %d (of %d).", 
                 timestep, nTimestep);
    msg = str;
}



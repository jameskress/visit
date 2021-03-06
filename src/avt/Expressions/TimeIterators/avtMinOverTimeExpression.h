// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                     avtMinOverTimeExpression.h                            //
// ************************************************************************* //

#ifndef AVT_MIN_OVER_TIME_EXPRESSION_H
#define AVT_MIN_OVER_TIME_EXPRESSION_H

#include <avtTimeIteratorDataTreeIteratorExpression.h>


// ****************************************************************************
//  Class: avtMinOverTimeExpression
//
//  Purpose:
//      A derived type of time iterator/data tree iterator that calculates the
//      minimum over time.
//
//  Programmer: Hank Childs
//  Creation:   February 16, 2009
//
// ****************************************************************************

class EXPRESSION_API avtMinOverTimeExpression 
    : public avtTimeIteratorDataTreeIteratorExpression
{
  public:
                              avtMinOverTimeExpression();
    virtual                  ~avtMinOverTimeExpression();

    virtual const char       *GetType(void)   
                                  { return "avtMinOverTimeExpression"; };
    virtual const char       *GetDescription(void)   
                                  { return "Calculating min over time"; };

  protected:
    virtual void              ExecuteDataset(std::vector<vtkDataArray *> &, 
                                             vtkDataArray *, int ts);
    virtual int               NumberOfVariables(void) { return 1; };
};


#endif



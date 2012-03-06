/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtGeqdskFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_Geqdsk_FILE_FORMAT_H
#define AVT_Geqdsk_FILE_FORMAT_H

#include <avtMTSDFileFormat.h>

#include <vector>

class DBOptionsAttributes;


// ****************************************************************************
//  Class: avtGeqdskFileFormat
//
//  Purpose:
//      Reads in Geqdsk files as a plugin to VisIt.
//
//  Programmer: allen -- generated by xml2avt
//  Creation:   Thu Aug 11 15:17:56 PST 2011
//
// ****************************************************************************

class avtGeqdskFileFormat : public avtMTSDFileFormat
{
  public:
                       avtGeqdskFileFormat(const char *, DBOptionsAttributes *);
    virtual           ~avtGeqdskFileFormat() {;};

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, int timestep, 
    //                                     const char *type, void *args, 
    //                                     DestructorFunction &);
    //

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    virtual void        GetCycles(std::vector<int> &);
    virtual void        GetTimes(std::vector<double> &);

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "Geqdsk"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

  protected:
    virtual void PopulateDatabaseMetaData(avtDatabaseMetaData *, int);

    virtual void ReadData( std::ifstream &f, float **var, int nVar );

    int nw;        // Number of horizontal R grid points
    int nh;        // Number of vertical   Z grid points

    float rdim;    // Horizontal dimension in meter of computational box
    float zdim;    // Vertical   dimension in meter of computational box

    float rleft;   // Minimum R in meter of rectangular computational box
    float zmid;    // Z in meter of center of computational box

    float rmaxis;  // R of magnetic axis in meter
    float zmaxis;  // Z of magnetic axis in meter

    float  simag;    // poloidal flux at magnetic axis in weber/rad
    float  sibry;    // poloidal flux at the plasma boundary in weber/rad
    float  rcentr;   // R in meter of vacuum toroidal magnetic field bcentr
    float  bcentr;   // Vacuum toroidal magnetic field in Tesla at rcentr
    float  current;  // Plasma current in Ampere

    float  *fpol;    // Poloidal current function in m-T, F = RBT on flux grid
    float  *pres;    // Plasma pressure in nt/m2 on uniform flux grid
    float  *ffprim;  // FF’(ψ) in (mT)^2 / (weber/rad) on uniform flux grid
    float  *pprime;  // P’(ψ) in (nt/m^2) / (weber/rad) on uniform flux grid
    float  *psirz;   // Poloidal flux in weber/rad on the rect grid points
    float  *qpsi;    // q values on uniform flux grid from axis to boundary

    int    nbbbs;    // Number of boundary points
    int    limitr;   // Number of limiter points

    float  *rzbbbs;   // RZ of boundary points in meter
    float  *rzlim;    // RZ of surrounding limiter contour in meter

    std::vector<int> cycles;
    std::vector<double> times;
};

#endif

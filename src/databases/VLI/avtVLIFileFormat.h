// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                            avtVLIFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_VLI_FILE_FORMAT_H
#define AVT_VLI_FILE_FORMAT_H

#include <vtkObject.h>
#include <avtDataSelection.h>
#include <avtMTMDFileFormat.h>
#include <VLIFileManager.h>

#include <vector>


// ****************************************************************************
//  Class: avtVLIFileFormat
//
//  Purpose:
//      Reads in VLI files as a plugin to VisIt.
//
//  Programmer: Markus Glatter <glatter@cs.utk.edu> -- generated by xml2avt
//  Creation:   Mon May 7 13:54:06 PST 2007
//
// ****************************************************************************

class avtVLIFileFormat : public avtMTMDFileFormat
{
  public:
                           avtVLIFileFormat(const char *);
    virtual               ~avtVLIFileFormat();

    virtual const char    *GetType(void)   { return "VLI"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual int            GetNTimesteps(void);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);
    virtual void           RegisterDataSelections(const std::vector<avtDataSelection_p>&, std::vector<bool> *);
    virtual void           RegisterVariableList(const char *, const std::vector<CharStrRef>&);
    virtual void          *threadCommServer(void *in);
    virtual void          *threadPacer(void *); 

   protected:

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
    virtual void           startServers(void);
    virtual int            startCommServer(std::string);
    virtual float          ConvertToFloat(unsigned short, int);
    virtual vtkObject     *Query(int, int, const char *);
    virtual void           ClearCache();
    virtual bool           CanCacheVariable(const char *v);

  private:

    int                             initialized;  
    int                             procNum;
    int                             procCount;
    VLIFileManager                 *config;
    volatile bool                   error;
    volatile bool                   loaded;
    volatile bool                   info;
    std::string                    *shostname;
    int                            *sport;
    std::string                    *ehostname;
    int                            *eport;
    void                           *ptid;
    volatile int                    socket;
    std::vector<avtDataSelection_p> selList;
    std::vector<bool>              *selsApplied;
    std::vector<int>                registeredVars;
    int                             queryTimestate;
    int                             queryDomain;
    std::vector<vtkObject *>        queryObjects;
    void                           *pacertid;
    int                             pport;
    volatile bool                   inQuery;
};

#endif

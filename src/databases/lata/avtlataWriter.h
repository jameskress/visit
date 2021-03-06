// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.
// ************************************************************************* //
//                             avtlataWriter.h                              //
// ************************************************************************* //

#ifndef AVT_lata_WRITER_H
#define AVT_lata_WRITER_H

#include <avtDatabaseWriter.h>

#include <string>


// ****************************************************************************
//  Class: avtlataWriter
//
//  Purpose:
//      A module that writes out lata files.
//
//  Programmer: fauchet -- generated by xml2avt
//
// ****************************************************************************

class
avtlataWriter : public avtDatabaseWriter
{
  public:
                   avtlataWriter();
    virtual       ~avtlataWriter() {;};

  protected:
    std::string    stem;
    vector<string> filenames_var;
    const avtDatabaseMetaData *md_;
    // deux methodes OpenFile (car changement d'interface entre 16 et 161
    double ftime;
    virtual void   OpenFile(const std::string &);
    virtual void   OpenFile(const std::string &, int nb);
    virtual void   WriteHeaders(const avtDatabaseMetaData *,
                                const std::vector<std::string> &, 
                                const std::vector<std::string> &,
                                const std::vector<std::string> &);
    virtual void   WriteChunk(vtkDataSet *, int);
    virtual void   CloseFile(void);
    
    void write_data(vtkDataArray *arr,const string& pos,string& filename);

};


#endif

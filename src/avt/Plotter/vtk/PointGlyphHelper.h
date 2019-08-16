// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef __PointGlyphHelper_h
#define __PointGlyphHelper_h

#include <visit_vtk_light_exports.h>
#include <GlyphTypes.h>
#include <vtkNew.h>

class vtkPolyData;

// *************************************************************************
//  PointGlyphHelper creates polydata 'glyphs' based on glyph type.
//
//  Modifications:
//
// *************************************************************************

class VISIT_VTK_LIGHT_API PointGlyphHelper
{
public:
  PointGlyphHelper();
 ~PointGlyphHelper();

  void SetGlyphType(GlyphType type);
  GlyphType  GetGlyphType(void) { return this->glyphType; }

  vtkPolyData *GetGlyphSource(int spatDim);

private:
  GlyphType glyphType;
  vtkNew<vtkPolyData> Glyph3D;
  vtkNew<vtkPolyData> Glyph2D;
  void SetUpGlyph(void);
};

#endif

// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                          vtkPointGlyphMapper.C                            //
// ************************************************************************* //

#include <vtkPointGlyphMapper.h>
#include <PointGlyphHelper.h>

#include <vtkCellData.h>
#include <vtkLookupTable.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkTrivialProducer.h>

#include <vtkPointMapper.h>
#include <vtkVisItGlyph3D.h>
#include <vtkVisItPolyDataNormals.h>

using std::string;



vtkStandardNewMacro( vtkPointGlyphMapper )

//----------------------------------------------------------------------------
vtkPointGlyphMapper::vtkPointGlyphMapper()
  : PointDataInitialized(false), SpatialDimension(3)
{
  this->Helper = new PointGlyphHelper();
  this->PointOutput->SetOutput(this->PointPolyData.GetPointer());

  this->GlyphFilter->SetVectorModeToVectorRotationOff();
  this->GlyphFilter->SetInputConnection(this->PointOutput->GetOutputPort());

  this->NormalsFilter->SetNormalTypeToCell();
  this->NormalsFilter->SetInputConnection(this->GlyphFilter->GetOutputPort());

  this->PointMapper->SetInputConnection(this->PointOutput->GetOutputPort());
  this->PointMapper->SetInterpolateScalarsBeforeMapping(0);
  this->PointMapper->SetImposterRadius(0.3f);
  this->PointMapper->UseImpostersOff();

  this->PointDataInitialized = false;
}

//----------------------------------------------------------------------------
vtkPointGlyphMapper::~vtkPointGlyphMapper()
{
}

//----------------------------------------------------------------------------
void vtkPointGlyphMapper::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}


//----------------------------------------------------------------------------
void vtkPointGlyphMapper::Render(vtkRenderer *ren, vtkActor *act)
{
  this->UpdatePointData();
  if (this->Helper->GetGlyphType() == Point ||
      this->Helper->GetGlyphType() == Sphere)
    {
    this->PointMapper->Render(ren,act);
    }
  else
    {
    this->GlyphMapper->Render(ren,act);
    }
}


//----------------------------------------------------------------------------
void vtkPointGlyphMapper::RenderPiece(vtkRenderer *ren, vtkActor *act)
{
  if (this->Helper->GetGlyphType() == Point ||
      this->Helper->GetGlyphType() == Sphere)
    {
    this->PointMapper->RenderPiece(ren,act);
    }
  else
    {
    this->GlyphMapper->RenderPiece(ren,act);
    }
}

//----------------------------------------------------------------------------
void vtkPointGlyphMapper::ReleaseGraphicsResources(vtkWindow *w)
{
  this->GlyphMapper->ReleaseGraphicsResources(w);
}


//----------------------------------------------------------------------------
// Modifications:
//
//    Kathleen Biagas, Fri Jun  7 11:06:14 PDT 2019
//    Tell superclass the scalar range, too. Needed by transparency actor.
//----------------------------------------------------------------------------

void vtkPointGlyphMapper::SetScalarRange(double min, double max)
{
  this->Superclass::SetScalarRange(min, max);
  this->GlyphMapper->SetScalarRange(min, max);
  this->PointMapper->SetScalarRange(min, max);
}


//----------------------------------------------------------------------------
// Modifications:
//
//    Kathleen Biagas, Fri Jun  7 11:06:14 PDT 2019
//    Tell superclass the lut, too. Needed by transparency actor.
//----------------------------------------------------------------------------
void vtkPointGlyphMapper::SetLookupTable(vtkLookupTable *lut)
{
  this->Superclass::SetLookupTable(lut);
  this->GlyphMapper->SetLookupTable(lut);
  this->PointMapper->SetLookupTable(lut);
}


//----------------------------------------------------------------------------
void vtkPointGlyphMapper::UpdatePointData()
{
  vtkPolyData *input = this->GetInput();

  if (!this->PointDataInitialized || (
        (input->GetMTime() > this->PointPolyData->GetMTime() ||
         this->GetMTime() > this->PointPolyData->GetMTime()) ))
    {
    this->PointPolyData->Initialize();
    this->PointPolyData->SetPoints(input->GetPoints());
    this->PointPolyData->SetVerts(input->GetVerts());
    this->PointPolyData->GetPointData()->PassData(input->GetPointData());
    this->PointPolyData->GetCellData()->PassData(input->GetCellData());

    this->GlyphFilter->SetSourceData(
      this->Helper->GetGlyphSource(this->SpatialDimension));

    if (this->SpatialDimension == 3)
      {
      this->GlyphMapper->SetInputConnection(this->NormalsFilter->GetOutputPort());
      }
    else
      {
      this->GlyphMapper->SetInputConnection(this->GlyphFilter->GetOutputPort());
      }
    this->GlyphFilter->SetInputConnection(this->PointOutput->GetOutputPort());
    this->PointDataInitialized = true;
    }
}

//----------------------------------------------------------------------------
void vtkPointGlyphMapper::SetGlyphType(GlyphType gt)
{
  if (this->Helper->GetGlyphType() != gt)
  {
    this->Helper->SetGlyphType(gt);
    this->Modified();
    if (gt == Sphere)
      this->PointMapper->UseImpostersOn();
    else
      this->PointMapper->UseImpostersOff();
  }
}

GlyphType vtkPointGlyphMapper::GetGlyphType()
{
  return this->Helper->GetGlyphType();
}

//----------------------------------------------------------------------------
void vtkPointGlyphMapper::SetScale(double s)
{
  this->GlyphFilter->SetScaleFactor(s);
  // Scale reduced by 1/2 for imposters, in attempt to duplicate size of
  // Sphere geometry when scaled by same amount.
  this->PointMapper->SetImposterRadius(s*0.5);
}

//----------------------------------------------------------------------------
void vtkPointGlyphMapper::DataScalingOff()
{
  this->GlyphFilter->SetScaleModeToDataScalingOff();
}

//----------------------------------------------------------------------------
void vtkPointGlyphMapper::DataScalingOn(const string &sname, int varDim)
{
  if (varDim < 3)
    {
    this->GlyphFilter->SetScaleModeToScaleByScalar();
    this->GlyphFilter->SelectScalarsForScaling(sname.c_str());
    }
  else if (varDim == 3)
    {
    this->GlyphFilter->SetScaleModeToScaleByVector();
    this->GlyphFilter->SelectVectorsForScaling(sname.c_str());
    }
  else if (varDim == 9)
    {
    this->GlyphFilter->SetScaleModeToScaleByTensor();
    this->GlyphFilter->SelectTensorsForScaling(sname.c_str());
    }
  else
    {
    this->GlyphFilter->SetScaleModeToScaleByVectorComponents();
    this->GlyphFilter->SelectVectorsForScaling(sname.c_str());
    }
}

//----------------------------------------------------------------------------
// Modifications:
//
//    Kathleen Biagas, Fri Jun  7 11:06:14 PDT 2019
//    Tell superclass too. Needed by transparency actor.
//----------------------------------------------------------------------------
void vtkPointGlyphMapper::ColorByScalarOn(const string &sn)
{
  this->Superclass::ScalarVisibilityOn();
  this->GlyphFilter->SetColorModeToColorByScalar();
  this->GlyphFilter->SelectScalarsForColoring(sn.c_str());
  this->GlyphMapper->ScalarVisibilityOn();
  this->PointMapper->ScalarVisibilityOn();
}

//----------------------------------------------------------------------------
// Modifications:
//
//    Kathleen Biagas, Fri Jun  7 11:06:14 PDT 2019
//    Tell superclass too. Needed by transparency actor.
//----------------------------------------------------------------------------
void vtkPointGlyphMapper::ColorByScalarOff()
{
  this->Superclass::ScalarVisibilityOff();
  this->GlyphFilter->SetColorMode(0);
  this->GlyphMapper->ScalarVisibilityOff();
  this->PointMapper->ScalarVisibilityOff();
}

//----------------------------------------------------------------------------
bool vtkPointGlyphMapper::SetFullFrameScaling(bool useScale, const double *s)
{
  if (this->GlyphFilter->SetFullFrameScaling(useScale?1:0, s))
    return true;
  return false;
}



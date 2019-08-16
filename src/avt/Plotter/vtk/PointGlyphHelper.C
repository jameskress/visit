// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PointGlyphHelper.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>

//----------------------------------------------------------------------------
PointGlyphHelper::PointGlyphHelper()
{
    this->glyphType = Point;
    this->SetUpGlyph();
}

//----------------------------------------------------------------------------
PointGlyphHelper::~PointGlyphHelper()
{
}

//----------------------------------------------------------------------------
vtkPolyData *
PointGlyphHelper::GetGlyphSource(int spatDim)
{
    if (spatDim == 3)
        return this->Glyph3D.GetPointer();
    else
        return this->Glyph2D.GetPointer();
}

//----------------------------------------------------------------------------
void PointGlyphHelper::SetGlyphType(GlyphType type)
{
    if (this->glyphType == type)
        return;
    this->glyphType = type;
    this->SetUpGlyph();
}

//----------------------------------------------------------------------------
void PointGlyphHelper::SetUpGlyph()
{
    this->Glyph3D->Initialize();
    this->Glyph2D->Initialize();

    if (this->glyphType == Box)
    {
        vtkNew<vtkPoints> pts;
        pts->SetNumberOfPoints(8);
        pts->SetPoint(0, -0.5, -0.5, -0.5);
        pts->SetPoint(1, +0.5, -0.5, -0.5);
        pts->SetPoint(2, +0.5, +0.5, -0.5);
        pts->SetPoint(3, -0.5, +0.5, -0.5);
        pts->SetPoint(4, -0.5, -0.5, +0.5);
        pts->SetPoint(5, +0.5, -0.5, +0.5);
        pts->SetPoint(6, +0.5, +0.5, +0.5);
        pts->SetPoint(7, -0.5, +0.5, +0.5);

        this->Glyph3D->SetPoints(pts.GetPointer());

        this->Glyph3D->Allocate(24);
        vtkIdType ids[6][4] = { { 0, 1, 2, 3 }, { 1, 5, 6, 2 },
                                { 2, 6, 7, 3 }, { 3, 7, 4, 0 },
                                { 0, 4, 5, 1 }, { 4, 7, 6, 5 } };
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[0]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[1]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[2]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[3]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[4]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[5]);

        vtkNew<vtkPoints> pts2D;
        pts2D->SetNumberOfPoints(4);
        pts2D->SetPoint(0, -0.5, -0.5, 0.);
        pts2D->SetPoint(1, +0.5, -0.5, 0.);
        pts2D->SetPoint(2, +0.5, +0.5, 0.);
        pts2D->SetPoint(3, -0.5, +0.5, 0.);

        this->Glyph2D->SetPoints(pts2D.GetPointer());

        this->Glyph2D->Allocate(4);
        vtkIdType ids2D[4] = { 0, 1, 2, 3};
        this->Glyph2D->InsertNextCell(VTK_QUAD, 4, ids2D);
    }
    else if (this->glyphType == Axis)
    {
        vtkNew<vtkPoints> pts;
        pts->SetNumberOfPoints(12);
        pts->SetPoint(0, 0., -0.5, -0.5);
        pts->SetPoint(1, 0., -0.5, +0.5);
        pts->SetPoint(2, 0., +0.5, +0.5);
        pts->SetPoint(3, 0., +0.5, -0.5);
        pts->SetPoint(4, -0.5, 0., -0.5);
        pts->SetPoint(5, -0.5, 0., +0.5);
        pts->SetPoint(6, +0.5, 0., +0.5);
        pts->SetPoint(7, +0.5, 0., -0.5);
        pts->SetPoint(8, -0.5, -0.5, 0.);
        pts->SetPoint(9, -0.5, +0.5, 0.);
        pts->SetPoint(10, +0.5, +0.5, 0.);
        pts->SetPoint(11, +0.5, -0.5, 0.);

        this->Glyph3D->SetPoints(pts.GetPointer());

        this->Glyph3D->Allocate(15);
        vtkIdType ids[3][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 },
                                { 8, 9, 10, 11 } };
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[0]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[1]);
        this->Glyph3D->InsertNextCell(VTK_QUAD, 4, ids[2]);

        vtkNew<vtkPoints> pts2D;
        pts2D->SetNumberOfPoints(4);
        pts2D->SetPoint(0, -0.5, 0., 0.);
        pts2D->SetPoint(1, +0.5, 0., 0.);
        pts2D->SetPoint(2, 0., -0.5, 0.);
        pts2D->SetPoint(3, 0., +0.5, 0.);

        this->Glyph2D->SetPoints(pts2D.GetPointer());

        this->Glyph2D->Allocate(6);
        vtkIdType line1[2] = { 0, 1 };
        vtkIdType line2[2] = { 2, 3 };
        this->Glyph2D->InsertNextCell(VTK_LINE, 2, line1);
        this->Glyph2D->InsertNextCell(VTK_LINE, 2, line2);
    }
    else if (this->glyphType == Icosahedron)
    {
        vtkNew<vtkPoints> pts;
        pts->SetNumberOfPoints(60);
        pts->SetPoint(0, 0, 0.5, 0);
        pts->SetPoint(1, -0.43787, 0.223375, 0.091508);
        pts->SetPoint(2, -0.0483832, 0.223697, 0.444543);
        pts->SetPoint(3, 0, 0.5, 0);
        pts->SetPoint(4, -0.0483832, 0.223697, 0.444543);
        pts->SetPoint(5, 0.407933, 0.223515, 0.183389);
        pts->SetPoint(6, 0, 0.5, 0);
        pts->SetPoint(7, 0.407933, 0.223515, 0.183389);
        pts->SetPoint(8, 0.300453, 0.223706, -0.331186);
        pts->SetPoint(9, 0, 0.5, 0);
        pts->SetPoint(10, 0.300453, 0.223706, -0.331186);
        pts->SetPoint(11, -0.222361, 0.223742, -0.387937);
        pts->SetPoint(12, 0, 0.5, 0);
        pts->SetPoint(13, -0.222361, 0.223742, -0.387937);
        pts->SetPoint(14, -0.43787, 0.223375, 0.091508);
        pts->SetPoint(15, 0, -0.5, 0);
        pts->SetPoint(16, 0.222411, -0.223548, 0.38802);
        pts->SetPoint(17, -0.300216, -0.223689, 0.331411);
        pts->SetPoint(18, 0, -0.5, 0);
        pts->SetPoint(19, -0.300216, -0.223689, 0.331411);
        pts->SetPoint(20, -0.407838, -0.223735, -0.183333);
        pts->SetPoint(21, 0, -0.5, 0);
        pts->SetPoint(22, -0.407838, -0.223735, -0.183333);
        pts->SetPoint(23, 0.0482061, -0.223357, -0.444733);
        pts->SetPoint(24, 0, -0.5, 0);
        pts->SetPoint(25, 0.0482061, -0.223357, -0.444733);
        pts->SetPoint(26, 0.437665, -0.223704, -0.091682);
        pts->SetPoint(27, 0, -0.5, 0);
        pts->SetPoint(28, 0.437665, -0.223704, -0.091682);
        pts->SetPoint(29, 0.222411, -0.223548, 0.38802);
        pts->SetPoint(30, -0.300216, -0.223689, 0.331411);
        pts->SetPoint(31, 0.222411, -0.223548, 0.38802);
        pts->SetPoint(32, -0.0483832, 0.223697, 0.444543);
        pts->SetPoint(33, -0.407838, -0.223735, -0.183333);
        pts->SetPoint(34, -0.300216, -0.223689, 0.331411);
        pts->SetPoint(35, -0.43787, 0.223375, 0.091508);
        pts->SetPoint(36, 0.0482061, -0.223357, -0.444733);
        pts->SetPoint(37, -0.407838, -0.223735, -0.183333);
        pts->SetPoint(38, -0.222361, 0.223742, -0.387937);
        pts->SetPoint(39, 0.437665, -0.223704, -0.091682);
        pts->SetPoint(40, 0.0482061, -0.223357, -0.444733);
        pts->SetPoint(41, 0.300453, 0.223706, -0.331186);
        pts->SetPoint(42, 0.222411, -0.223548, 0.38802);
        pts->SetPoint(43, 0.437665, -0.223704, -0.091682);
        pts->SetPoint(44, 0.407933, 0.223515, 0.183389);
        pts->SetPoint(45, -0.0483832, 0.223697, 0.444543);
        pts->SetPoint(46, -0.43787, 0.223375, 0.091508);
        pts->SetPoint(47, -0.300216, -0.223689, 0.331411);
        pts->SetPoint(48, -0.43787, 0.223375, 0.091508);
        pts->SetPoint(49, -0.222361, 0.223742, -0.387937);
        pts->SetPoint(50, -0.407838, -0.223735, -0.183333);
        pts->SetPoint(51, -0.222361, 0.223742, -0.387937);
        pts->SetPoint(52, 0.300453, 0.223706, -0.331186);
        pts->SetPoint(53, 0.0482061, -0.223357, -0.444733);
        pts->SetPoint(54, 0.300453, 0.223706, -0.331186);
        pts->SetPoint(55, 0.407933, 0.223515, 0.183389);
        pts->SetPoint(56, 0.437665, -0.223704, -0.091682);
        pts->SetPoint(57, 0.407933, 0.223515, 0.183389);
        pts->SetPoint(58, -0.0483832, 0.223697, 0.444543);
        pts->SetPoint(59, 0.222411, -0.223548, 0.38802);

        this->Glyph3D->SetPoints(pts.GetPointer());

        this->Glyph3D->Allocate(80);
        for (int i = 0 ; i < 20 ; ++i)
        {
            vtkIdType ids[3] = { 3*i, 3*i+1, 3*i+2 };
            this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids);
        }

        vtkNew<vtkPoints> pts2D;
        pts2D->SetNumberOfPoints(13);
        pts2D->SetPoint(0, 0., 0., 0.);
        for (int i = 0 ; i < 12 ; ++i)
        {
            double rad = ((double) i) / 12. * 2. * M_PI;
            pts2D->SetPoint(i+1, cos(rad)/2., sin(rad)/2., 0.);
        }

        this->Glyph2D->SetPoints(pts2D.GetPointer());

        this->Glyph2D->Allocate(48);
        for (int i = 0 ; i < 12 ; ++i)
        {
            int pt2 = (i+2 >= 13 ? 1 : i+2);
            vtkIdType tri[3] = { 0, i+1, pt2 };
            this->Glyph2D->InsertNextCell(VTK_TRIANGLE, 3, tri);
        }
    }
    else if (this->glyphType == Octahedron)
    {
        vtkNew<vtkPoints> pts;
        pts->SetNumberOfPoints(6);
        pts->SetPoint(0,  0.5,  0.0,  0.0);
        pts->SetPoint(1,  0.0,  0.0, -0.5);
        pts->SetPoint(2, -0.5,  0.0,  0.0);
        pts->SetPoint(3,  0.0,  0.0,  0.5);
        pts->SetPoint(4,  0.0,  0.5,  0.0);
        pts->SetPoint(5,  0.0, -0.5,  0.0);

        this->Glyph3D->SetPoints(pts.GetPointer());

        this->Glyph3D->Allocate(24);
        vtkIdType ids[8][3] = { {0,1,4}, {1,2,4}, {2,3,4}, {3,0,4},
                                {5,0,3}, {5,1,0}, {5,1,2}, {5,2,3} };
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[0]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[1]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[2]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[3]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[4]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[5]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[6]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[7]);

        vtkNew<vtkPoints> pts2D;
        pts2D->SetNumberOfPoints(4);
        pts2D->SetPoint(0,  0.5, 0.0, 0.);
        pts2D->SetPoint(1,  0.0, 0.5, 0.);
        pts2D->SetPoint(2, -0.5, 0.0, 0.);
        pts2D->SetPoint(3,  0.0, -0.5, 0.);

        this->Glyph2D->SetPoints(pts2D.GetPointer());

        this->Glyph2D->Allocate(4);
        vtkIdType ids2D[4] = { 0, 1, 2, 3};
        this->Glyph2D->InsertNextCell(VTK_QUAD, 4, ids2D);
    }
    else if (this->glyphType == Tetrahedron)
    {
        vtkNew<vtkPoints> pts;
        pts->SetNumberOfPoints(4);
        pts->SetPoint(0,  0.5, -0.42983,  -0.377355);
        pts->SetPoint(1,  0,    0.43479,  -0.42667);
        pts->SetPoint(2, -0.5, -0.42983,  -0.377355);
        pts->SetPoint(3,  0,   -0.0951297, 0.421379);

        this->Glyph3D->SetPoints(pts.GetPointer());

        this->Glyph3D->Allocate(12);
        vtkIdType ids[4][3] = { {0,1,3}, {1,2,3}, {2,0,3}, {1,0,2}};
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[0]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[1]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[2]);
        this->Glyph3D->InsertNextCell(VTK_TRIANGLE, 3, ids[3]);

        vtkNew<vtkPoints> pts2D;
        pts2D->SetNumberOfPoints(3);
        pts2D->SetPoint(0,  0.0,    0.5,  0.);
        pts2D->SetPoint(1, -0.433, -0.25, 0.);
        pts2D->SetPoint(2,  0.433, -0.25, 0.);

        this->Glyph2D->SetPoints(pts2D.GetPointer());

        this->Glyph2D->Allocate(3);
        vtkIdType ids2D[3] = { 0, 1, 2};
        this->Glyph2D->InsertNextCell(VTK_TRIANGLE, 3, ids2D);
    }
    else if (this->glyphType == SphereGeometry)
    {
        vtkNew<vtkSphereSource> sphere;
        sphere->SetRadius(0.5);
        sphere->SetCenter(0.,0.,0.);
        sphere->SetThetaResolution(16);
        sphere->SetPhiResolution(16);
        sphere->Update();

        this->Glyph3D->DeepCopy(sphere->GetOutput());

        vtkNew<vtkPoints> pts2D;
        pts2D->SetNumberOfPoints(13);
        pts2D->SetPoint(0, 0., 0., 0.);
        for (int i = 0 ; i < 12 ; ++i)
        {
            double rad = ((double) i) / 12. * 2. * M_PI;
            pts2D->SetPoint(i+1, cos(rad)/2., sin(rad)/2., 0.);
        }

        this->Glyph2D->SetPoints(pts2D.GetPointer());

        this->Glyph2D->Allocate(48);
        for (int i = 0 ; i < 12 ; ++i)
        {
            int pt2 = (i+2 >= 13 ? 1 : i+2);
            vtkIdType tri[3] = { 0, i+1, pt2 };
            this->Glyph2D->InsertNextCell(VTK_TRIANGLE, 3, tri);
        }
    }
    else if (this->glyphType == Point ||
             this->glyphType == Sphere)
    {
        vtkNew<vtkPoints> pts;
        pts->SetNumberOfPoints(1);
        pts->SetPoint(0, 0, 0, 0);
        vtkIdType ids[1] ={0};
        this->Glyph3D->SetPoints(pts.GetPointer());

        this->Glyph3D->Allocate(1);
        this->Glyph3D->InsertNextCell(VTK_VERTEX, 1, ids);

        this->Glyph2D->SetPoints(pts.GetPointer());

        this->Glyph2D->Allocate(1);
        this->Glyph2D->InsertNextCell(VTK_VERTEX, 1, ids);
    }
}



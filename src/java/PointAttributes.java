// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

package llnl.visit;


// ****************************************************************************
// Class: PointAttributes
//
// Purpose:
//    Attributes for a point
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

public class PointAttributes extends AttributeSubject
{
    private static int PointAttributes_numAdditionalAtts = 1;

    public PointAttributes()
    {
        super(PointAttributes_numAdditionalAtts);

        point = new double[3];
        point[0] = 0;
        point[1] = 0;
        point[2] = 0;
    }

    public PointAttributes(int nMoreFields)
    {
        super(PointAttributes_numAdditionalAtts + nMoreFields);

        point = new double[3];
        point[0] = 0;
        point[1] = 0;
        point[2] = 0;
    }

    public PointAttributes(PointAttributes obj)
    {
        super(obj);

        int i;

        point = new double[3];
        point[0] = obj.point[0];
        point[1] = obj.point[1];
        point[2] = obj.point[2];


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return PointAttributes_numAdditionalAtts;
    }

    public boolean equals(PointAttributes obj)
    {
        int i;

        // Compare the point arrays.
        boolean point_equal = true;
        for(i = 0; i < 3 && point_equal; ++i)
            point_equal = (point[i] == obj.point[i]);

        // Create the return value
        return (point_equal);
    }

    // Property setting methods
    public void SetPoint(double[] point_)
    {
        point[0] = point_[0];
        point[1] = point_[1];
        point[2] = point_[2];
        Select(0);
    }

    public void SetPoint(double e0, double e1, double e2)
    {
        point[0] = e0;
        point[1] = e1;
        point[2] = e2;
        Select(0);
    }

    // Property getting methods
    public double[] GetPoint() { return point; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteDoubleArray(point);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        SetPoint(buf.ReadDoubleArray());
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + doubleArrayToString("point", point, indent) + "\n";
        return str;
    }


    // Attributes
    private double[] point;
}


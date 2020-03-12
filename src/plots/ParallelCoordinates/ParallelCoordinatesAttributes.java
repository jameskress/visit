// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

package llnl.visit.plots;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;
import java.util.Vector;
import java.lang.Double;
import llnl.visit.ColorAttribute;

// ****************************************************************************
// Class: ParallelCoordinatesAttributes
//
// Purpose:
//    This class contains the plot attributes for the ParallelCoordinates plot.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

public class ParallelCoordinatesAttributes extends AttributeSubject implements Plugin
{
    private static int ParallelCoordinatesAttributes_numAdditionalAtts = 15;

    // Enum values
    public final static int FOCUSRENDERING_INDIVIDUALLINES = 0;
    public final static int FOCUSRENDERING_BINSOFCONSTANTCOLOR = 1;
    public final static int FOCUSRENDERING_BINSCOLOREDBYPOPULATION = 2;


    public ParallelCoordinatesAttributes()
    {
        super(ParallelCoordinatesAttributes_numAdditionalAtts);

        scalarAxisNames = new Vector();
        visualAxisNames = new Vector();
        extentMinima = new Vector();
        extentMaxima = new Vector();
        drawLines = true;
        linesColor = new ColorAttribute(128, 0, 0);
        drawContext = true;
        contextGamma = 2f;
        contextNumPartitions = 128;
        contextColor = new ColorAttribute(0, 220, 0);
        drawLinesOnlyIfExtentsOn = true;
        unifyAxisExtents = false;
        linesNumPartitions = 512;
        focusGamma = 4f;
        drawFocusAs = FOCUSRENDERING_BINSOFCONSTANTCOLOR;
    }

    public ParallelCoordinatesAttributes(int nMoreFields)
    {
        super(ParallelCoordinatesAttributes_numAdditionalAtts + nMoreFields);

        scalarAxisNames = new Vector();
        visualAxisNames = new Vector();
        extentMinima = new Vector();
        extentMaxima = new Vector();
        drawLines = true;
        linesColor = new ColorAttribute(128, 0, 0);
        drawContext = true;
        contextGamma = 2f;
        contextNumPartitions = 128;
        contextColor = new ColorAttribute(0, 220, 0);
        drawLinesOnlyIfExtentsOn = true;
        unifyAxisExtents = false;
        linesNumPartitions = 512;
        focusGamma = 4f;
        drawFocusAs = FOCUSRENDERING_BINSOFCONSTANTCOLOR;
    }

    public ParallelCoordinatesAttributes(ParallelCoordinatesAttributes obj)
    {
        super(obj);

        int i;

        scalarAxisNames = new Vector(obj.scalarAxisNames.size());
        for(i = 0; i < obj.scalarAxisNames.size(); ++i)
            scalarAxisNames.addElement(new String((String)obj.scalarAxisNames.elementAt(i)));

        visualAxisNames = new Vector(obj.visualAxisNames.size());
        for(i = 0; i < obj.visualAxisNames.size(); ++i)
            visualAxisNames.addElement(new String((String)obj.visualAxisNames.elementAt(i)));

        extentMinima = new Vector(obj.extentMinima.size());
        for(i = 0; i < obj.extentMinima.size(); ++i)
        {
            Double dv = (Double)obj.extentMinima.elementAt(i);
            extentMinima.addElement(new Double(dv.doubleValue()));
        }

        extentMaxima = new Vector(obj.extentMaxima.size());
        for(i = 0; i < obj.extentMaxima.size(); ++i)
        {
            Double dv = (Double)obj.extentMaxima.elementAt(i);
            extentMaxima.addElement(new Double(dv.doubleValue()));
        }

        drawLines = obj.drawLines;
        linesColor = new ColorAttribute(obj.linesColor);
        drawContext = obj.drawContext;
        contextGamma = obj.contextGamma;
        contextNumPartitions = obj.contextNumPartitions;
        contextColor = new ColorAttribute(obj.contextColor);
        drawLinesOnlyIfExtentsOn = obj.drawLinesOnlyIfExtentsOn;
        unifyAxisExtents = obj.unifyAxisExtents;
        linesNumPartitions = obj.linesNumPartitions;
        focusGamma = obj.focusGamma;
        drawFocusAs = obj.drawFocusAs;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return ParallelCoordinatesAttributes_numAdditionalAtts;
    }

    public boolean equals(ParallelCoordinatesAttributes obj)
    {
        int i;

        // Compare the elements in the scalarAxisNames vector.
        boolean scalarAxisNames_equal = (obj.scalarAxisNames.size() == scalarAxisNames.size());
        for(i = 0; (i < scalarAxisNames.size()) && scalarAxisNames_equal; ++i)
        {
            // Make references to String from Object.
            String scalarAxisNames1 = (String)scalarAxisNames.elementAt(i);
            String scalarAxisNames2 = (String)obj.scalarAxisNames.elementAt(i);
            scalarAxisNames_equal = scalarAxisNames1.equals(scalarAxisNames2);
        }
        // Compare the elements in the visualAxisNames vector.
        boolean visualAxisNames_equal = (obj.visualAxisNames.size() == visualAxisNames.size());
        for(i = 0; (i < visualAxisNames.size()) && visualAxisNames_equal; ++i)
        {
            // Make references to String from Object.
            String visualAxisNames1 = (String)visualAxisNames.elementAt(i);
            String visualAxisNames2 = (String)obj.visualAxisNames.elementAt(i);
            visualAxisNames_equal = visualAxisNames1.equals(visualAxisNames2);
        }
        // Compare the elements in the extentMinima vector.
        boolean extentMinima_equal = (obj.extentMinima.size() == extentMinima.size());
        for(i = 0; (i < extentMinima.size()) && extentMinima_equal; ++i)
        {
            // Make references to Double from Object.
            Double extentMinima1 = (Double)extentMinima.elementAt(i);
            Double extentMinima2 = (Double)obj.extentMinima.elementAt(i);
            extentMinima_equal = extentMinima1.equals(extentMinima2);
        }
        // Compare the elements in the extentMaxima vector.
        boolean extentMaxima_equal = (obj.extentMaxima.size() == extentMaxima.size());
        for(i = 0; (i < extentMaxima.size()) && extentMaxima_equal; ++i)
        {
            // Make references to Double from Object.
            Double extentMaxima1 = (Double)extentMaxima.elementAt(i);
            Double extentMaxima2 = (Double)obj.extentMaxima.elementAt(i);
            extentMaxima_equal = extentMaxima1.equals(extentMaxima2);
        }
        // Create the return value
        return (scalarAxisNames_equal &&
                visualAxisNames_equal &&
                extentMinima_equal &&
                extentMaxima_equal &&
                (drawLines == obj.drawLines) &&
                (linesColor == obj.linesColor) &&
                (drawContext == obj.drawContext) &&
                (contextGamma == obj.contextGamma) &&
                (contextNumPartitions == obj.contextNumPartitions) &&
                (contextColor == obj.contextColor) &&
                (drawLinesOnlyIfExtentsOn == obj.drawLinesOnlyIfExtentsOn) &&
                (unifyAxisExtents == obj.unifyAxisExtents) &&
                (linesNumPartitions == obj.linesNumPartitions) &&
                (focusGamma == obj.focusGamma) &&
                (drawFocusAs == obj.drawFocusAs));
    }

    public String GetName() { return "ParallelCoordinates"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetScalarAxisNames(Vector scalarAxisNames_)
    {
        scalarAxisNames = scalarAxisNames_;
        Select(0);
    }

    public void SetVisualAxisNames(Vector visualAxisNames_)
    {
        visualAxisNames = visualAxisNames_;
        Select(1);
    }

    public void SetExtentMinima(Vector extentMinima_)
    {
        extentMinima = extentMinima_;
        Select(2);
    }

    public void SetExtentMaxima(Vector extentMaxima_)
    {
        extentMaxima = extentMaxima_;
        Select(3);
    }

    public void SetDrawLines(boolean drawLines_)
    {
        drawLines = drawLines_;
        Select(4);
    }

    public void SetLinesColor(ColorAttribute linesColor_)
    {
        linesColor = linesColor_;
        Select(5);
    }

    public void SetDrawContext(boolean drawContext_)
    {
        drawContext = drawContext_;
        Select(6);
    }

    public void SetContextGamma(float contextGamma_)
    {
        contextGamma = contextGamma_;
        Select(7);
    }

    public void SetContextNumPartitions(int contextNumPartitions_)
    {
        contextNumPartitions = contextNumPartitions_;
        Select(8);
    }

    public void SetContextColor(ColorAttribute contextColor_)
    {
        contextColor = contextColor_;
        Select(9);
    }

    public void SetDrawLinesOnlyIfExtentsOn(boolean drawLinesOnlyIfExtentsOn_)
    {
        drawLinesOnlyIfExtentsOn = drawLinesOnlyIfExtentsOn_;
        Select(10);
    }

    public void SetUnifyAxisExtents(boolean unifyAxisExtents_)
    {
        unifyAxisExtents = unifyAxisExtents_;
        Select(11);
    }

    public void SetLinesNumPartitions(int linesNumPartitions_)
    {
        linesNumPartitions = linesNumPartitions_;
        Select(12);
    }

    public void SetFocusGamma(float focusGamma_)
    {
        focusGamma = focusGamma_;
        Select(13);
    }

    public void SetDrawFocusAs(int drawFocusAs_)
    {
        drawFocusAs = drawFocusAs_;
        Select(14);
    }

    // Property getting methods
    public Vector         GetScalarAxisNames() { return scalarAxisNames; }
    public Vector         GetVisualAxisNames() { return visualAxisNames; }
    public Vector         GetExtentMinima() { return extentMinima; }
    public Vector         GetExtentMaxima() { return extentMaxima; }
    public boolean        GetDrawLines() { return drawLines; }
    public ColorAttribute GetLinesColor() { return linesColor; }
    public boolean        GetDrawContext() { return drawContext; }
    public float          GetContextGamma() { return contextGamma; }
    public int            GetContextNumPartitions() { return contextNumPartitions; }
    public ColorAttribute GetContextColor() { return contextColor; }
    public boolean        GetDrawLinesOnlyIfExtentsOn() { return drawLinesOnlyIfExtentsOn; }
    public boolean        GetUnifyAxisExtents() { return unifyAxisExtents; }
    public int            GetLinesNumPartitions() { return linesNumPartitions; }
    public float          GetFocusGamma() { return focusGamma; }
    public int            GetDrawFocusAs() { return drawFocusAs; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteStringVector(scalarAxisNames);
        if(WriteSelect(1, buf))
            buf.WriteStringVector(visualAxisNames);
        if(WriteSelect(2, buf))
            buf.WriteDoubleVector(extentMinima);
        if(WriteSelect(3, buf))
            buf.WriteDoubleVector(extentMaxima);
        if(WriteSelect(4, buf))
            buf.WriteBool(drawLines);
        if(WriteSelect(5, buf))
            linesColor.Write(buf);
        if(WriteSelect(6, buf))
            buf.WriteBool(drawContext);
        if(WriteSelect(7, buf))
            buf.WriteFloat(contextGamma);
        if(WriteSelect(8, buf))
            buf.WriteInt(contextNumPartitions);
        if(WriteSelect(9, buf))
            contextColor.Write(buf);
        if(WriteSelect(10, buf))
            buf.WriteBool(drawLinesOnlyIfExtentsOn);
        if(WriteSelect(11, buf))
            buf.WriteBool(unifyAxisExtents);
        if(WriteSelect(12, buf))
            buf.WriteInt(linesNumPartitions);
        if(WriteSelect(13, buf))
            buf.WriteFloat(focusGamma);
        if(WriteSelect(14, buf))
            buf.WriteInt(drawFocusAs);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetScalarAxisNames(buf.ReadStringVector());
            break;
        case 1:
            SetVisualAxisNames(buf.ReadStringVector());
            break;
        case 2:
            SetExtentMinima(buf.ReadDoubleVector());
            break;
        case 3:
            SetExtentMaxima(buf.ReadDoubleVector());
            break;
        case 4:
            SetDrawLines(buf.ReadBool());
            break;
        case 5:
            linesColor.Read(buf);
            Select(5);
            break;
        case 6:
            SetDrawContext(buf.ReadBool());
            break;
        case 7:
            SetContextGamma(buf.ReadFloat());
            break;
        case 8:
            SetContextNumPartitions(buf.ReadInt());
            break;
        case 9:
            contextColor.Read(buf);
            Select(9);
            break;
        case 10:
            SetDrawLinesOnlyIfExtentsOn(buf.ReadBool());
            break;
        case 11:
            SetUnifyAxisExtents(buf.ReadBool());
            break;
        case 12:
            SetLinesNumPartitions(buf.ReadInt());
            break;
        case 13:
            SetFocusGamma(buf.ReadFloat());
            break;
        case 14:
            SetDrawFocusAs(buf.ReadInt());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringVectorToString("scalarAxisNames", scalarAxisNames, indent) + "\n";
        str = str + stringVectorToString("visualAxisNames", visualAxisNames, indent) + "\n";
        str = str + doubleVectorToString("extentMinima", extentMinima, indent) + "\n";
        str = str + doubleVectorToString("extentMaxima", extentMaxima, indent) + "\n";
        str = str + boolToString("drawLines", drawLines, indent) + "\n";
        str = str + indent + "linesColor = {" + linesColor.Red() + ", " + linesColor.Green() + ", " + linesColor.Blue() + ", " + linesColor.Alpha() + "}\n";
        str = str + boolToString("drawContext", drawContext, indent) + "\n";
        str = str + floatToString("contextGamma", contextGamma, indent) + "\n";
        str = str + intToString("contextNumPartitions", contextNumPartitions, indent) + "\n";
        str = str + indent + "contextColor = {" + contextColor.Red() + ", " + contextColor.Green() + ", " + contextColor.Blue() + ", " + contextColor.Alpha() + "}\n";
        str = str + boolToString("drawLinesOnlyIfExtentsOn", drawLinesOnlyIfExtentsOn, indent) + "\n";
        str = str + boolToString("unifyAxisExtents", unifyAxisExtents, indent) + "\n";
        str = str + intToString("linesNumPartitions", linesNumPartitions, indent) + "\n";
        str = str + floatToString("focusGamma", focusGamma, indent) + "\n";
        str = str + indent + "drawFocusAs = ";
        if(drawFocusAs == FOCUSRENDERING_INDIVIDUALLINES)
            str = str + "FOCUSRENDERING_INDIVIDUALLINES";
        if(drawFocusAs == FOCUSRENDERING_BINSOFCONSTANTCOLOR)
            str = str + "FOCUSRENDERING_BINSOFCONSTANTCOLOR";
        if(drawFocusAs == FOCUSRENDERING_BINSCOLOREDBYPOPULATION)
            str = str + "FOCUSRENDERING_BINSCOLOREDBYPOPULATION";
        str = str + "\n";
        return str;
    }


    // Attributes
    private Vector         scalarAxisNames; // vector of String objects
    private Vector         visualAxisNames; // vector of String objects
    private Vector         extentMinima; // vector of Double objects
    private Vector         extentMaxima; // vector of Double objects
    private boolean        drawLines;
    private ColorAttribute linesColor;
    private boolean        drawContext;
    private float          contextGamma;
    private int            contextNumPartitions;
    private ColorAttribute contextColor;
    private boolean        drawLinesOnlyIfExtentsOn;
    private boolean        unifyAxisExtents;
    private int            linesNumPartitions;
    private float          focusGamma;
    private int            drawFocusAs;
}


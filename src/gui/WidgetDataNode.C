// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
// Purpose:  This file is a set of routines that can set/get values from
//           QWidget/DataNode. This allows us to use custom UI components. We
//           could even use them to create DataNodes that AttributeSubjects
//           could use to initialize themselves, which would open the door to
//           plots with UI's created with Qt designer. It would also mean that
//           we might not need Qt to build new UI's at all, which would be a
//           plus on systems where you have to pay for QT.
//
//
// Notes:
//
// Programmer: Brad Whitlock
// Creation:   Fri Oct 6 17:35:57 PST 2006
//
// Modifications:
//
// ****************************************************************************


#include <DataNode.h>

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QObjectList>
#include <QSpinBox>
#include <QTextEdit>
#include <QvisColorButton.h>
#include <QvisDialogLineEdit.h>
#include <QvisVariableButton.h>

#include <DebugStream.h>

void
ConvertTextToDataNodeSettings(const QString &text, DataNode *node)
{
}

// ****************************************************************************
// Function: DataNodeToBool
//
// Purpose:
//   Converts a data node value into a bool
//
// Arguments:
//   node : The node to evaluate.
//
// Returns:    The converted bool value.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:37:19 PDT 2006
//
// Modifications:
//
// ****************************************************************************

static bool
DataNodeToBool(DataNode *node)
{
    bool ret = false;
    switch(node->GetNodeType())
    {
    case CHAR_NODE:
        ret = node->AsChar() > 0;
        break;
    case UNSIGNED_CHAR_NODE:
        ret = node->AsUnsignedChar() > 0;
        break;
    case INT_NODE:
        ret = node->AsInt() > 0;
        break;
    case LONG_NODE:
        ret = node->AsLong() > 0L;
        break;
    case FLOAT_NODE:
        ret = node->AsFloat() > 0.f;
        break;
    case DOUBLE_NODE:
        ret = node->AsDouble() > 0.;
        break;
    case STRING_NODE:
        ret = node->AsString() == "TRUE" || node->AsString() == "true";
        break;
    case BOOL_NODE:
        ret = node->AsBool();
        break;
    default:
        ret = false;
    }

    return ret;
}

// ****************************************************************************
// Function: DataNodeToInt
//
// Purpose:
//   Converts a data node into an int.
//
// Arguments:
//   node : The node to convert.
//
// Returns:    The int value of the data node.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:37:54 PDT 2006
//
// Modifications:
//
// ****************************************************************************

static int
DataNodeToInt(DataNode *node)
{
    int ret = 0;
    switch(node->GetNodeType())
    {
    case CHAR_NODE:
        ret = int(node->AsChar());
        break;
    case UNSIGNED_CHAR_NODE:
        ret = int(node->AsUnsignedChar());
        break;
    case INT_NODE:
        ret = node->AsInt();
        break;
    case LONG_NODE:
        ret = int(node->AsLong());
        break;
    case FLOAT_NODE:
        ret = int(node->AsFloat());
        break;
    case DOUBLE_NODE:
        ret = int(node->AsDouble());
        break;
    case STRING_NODE:
        {
            int tmp;
            if(sscanf(node->AsString().c_str(), "%d", &tmp) == 1)
                ret = tmp;
            else
                ret = 0;
        }
        break;
    case BOOL_NODE:
        ret = node->AsBool() ? 1 : 0;
        break;
    default:
        ret = 0;
    }

    return ret;
}

// ****************************************************************************
// Function: DataNodeToQString
//
// Purpose:
//   Converts the data node into a QString.
//
// Arguments:
//   node : The data node to convert.
//
// Returns:    The QString representation of the data node.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:38:27 PDT 2006
//
// Modifications:
//
//   Kathleen Biagas, Thu Jan 21, 2021
//   Replace QString.asprintf with QString.setNum where possible.
//
// ****************************************************************************

QString
DataNodeToQString(const DataNode *node)
{
    QString s, tmp;
    int i;

// These only handle numbers now, and call QString.setNum
#define ARRAY_TO_STRING(Type, Method)\
        {\
            const Type *ptr = node->Method();\
            for(i = 0; i < node->GetLength(); ++i)\
            {\
                tmp.setNum(ptr[i]);\
                if(i > 0)\
                    s += " ";\
                s += tmp;\
            }\
        }

#define VECTOR_TO_STRING(Type, Method)\
        {\
            const Type &vec = node->Method();\
            for(size_t i = 0; i < vec.size(); ++i)\
            {\
                tmp.setNum(vec[i]);\
                if(i > 0)\
                    s += " ";\
                s += tmp;\
            }\
        }
    switch(node->GetNodeType())
    {
    case INTERNAL_NODE:
        break;
    case CHAR_NODE:
        s.setNum((int)node->AsChar());
        break;
    case UNSIGNED_CHAR_NODE:
        s.setNum((int)node->AsUnsignedChar());
        break;
    case INT_NODE:
        s.setNum(node->AsInt());
        break;
    case LONG_NODE:
        s.setNum(node->AsLong());
        break;
    case FLOAT_NODE:
        s.setNum(node->AsFloat());
        break;
    case DOUBLE_NODE:
        s.setNum(node->AsDouble());
        break;
    case STRING_NODE:
        s = QString(node->AsString().c_str());
        break;
    case BOOL_NODE:
        if(node->AsBool()) s = "true"; else s = "false";
        break;
    case CHAR_ARRAY_NODE:
        {
            const char *cptr = node->AsCharArray();
            for(i = 0; i < node->GetLength(); ++i)
            {
                tmp.setNum((int)cptr[i]);
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    case UNSIGNED_CHAR_ARRAY_NODE:
        {
            const unsigned char *cptr = node->AsUnsignedCharArray();
            for(i = 0; i < node->GetLength(); ++i)
            {
                tmp.setNum((int)cptr[i]);
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    case INT_ARRAY_NODE:
        ARRAY_TO_STRING(int, AsIntArray);
        break;
    case LONG_ARRAY_NODE:
        ARRAY_TO_STRING(long, AsLongArray);
        break;
    case FLOAT_ARRAY_NODE:
        ARRAY_TO_STRING(float, AsFloatArray);
        break;
    case DOUBLE_ARRAY_NODE:
        ARRAY_TO_STRING(double, AsDoubleArray);
        break;
    case STRING_ARRAY_NODE:
        {
            const std::string *ptr = node->AsStringArray();
            for(i = 0; i < node->GetLength(); ++i)
            {
                tmp = QString(ptr[i].c_str());
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    case BOOL_ARRAY_NODE:
        {
            const bool *ptr = node->AsBoolArray();
            for(i = 0; i < node->GetLength(); ++i)
            {
                if(ptr[i])
                    tmp = "true";
                else
                    tmp = "false";
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    case CHAR_VECTOR_NODE:
        {
            const charVector &vec = node->AsCharVector();
            for(size_t i = 0; i < vec.size(); ++i)
            {
                tmp.setNum((int)vec[i]);
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    case UNSIGNED_CHAR_VECTOR_NODE:
        {
            const unsignedCharVector &vec = node->AsUnsignedCharVector();
            for(size_t i = 0; i < vec.size(); ++i)
            {
                tmp.setNum((int)vec[i]);
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    case INT_VECTOR_NODE:
        VECTOR_TO_STRING(intVector, AsIntVector);
        break;
    case LONG_VECTOR_NODE:
        VECTOR_TO_STRING(longVector, AsLongVector);
        break;
    case FLOAT_VECTOR_NODE:
        VECTOR_TO_STRING(floatVector, AsFloatVector);
        break;
    case DOUBLE_VECTOR_NODE:
        VECTOR_TO_STRING(doubleVector, AsDoubleVector);
        break;
    case STRING_VECTOR_NODE:
        {
            const stringVector &vec = node->AsStringVector();
            for(size_t i = 0; i < vec.size(); ++i)
            {
                tmp = QString(vec[i].c_str());
                if(i > 0)
                    s += " ";
                s += tmp;
            }
        }
        break;
    default:
        break;
    }

#undef ARRAY_TO_STRING
#undef VECTOR_TO_STRING

    return s;
}

// ****************************************************************************
// Function: DataNodeToQColor
//
// Purpose:
//   Converts a data node representation of color into a QColor.
//
// Arguments:
//   node : The data to convert to QColor.
//   color : The return QColor object.
//
// Returns:    True on success; False otherwise.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Thu Nov 16 13:34:12 PST 2006
//
// Modifications:
//
// ****************************************************************************

bool DataNodeToQColor(DataNode *node, QColor &color)
{
    bool  retval = true;
    int   i, rgb[3] = {0, 0, 0};
    float f_rgb[3] = {0., 0., 0.};
    bool  fp = false;

#define ARRAY_TO_RGB(Rgb, Type, Method, Cast) \
        if(node->GetLength() >= 3) \
        { \
            const Type *ptr = node->Method();\
            for(i = 0; i < 3; ++i) \
                Rgb[i] = Cast ptr[i]; \
        }

#define VECTOR_TO_RGB(Rgb, Type, Method, Cast) \
        { \
            const Type &vec = node->Method(); \
            if(vec.size() >= 3) \
            { \
                for(i = 0; i < 3; ++i) \
                    Rgb[i] = Cast vec[i]; \
            } \
        }

    switch(node->GetNodeType())
    {
    case CHAR_ARRAY_NODE:
        ARRAY_TO_RGB(rgb, char, AsCharArray, (int));
        break;
    case UNSIGNED_CHAR_ARRAY_NODE:
        ARRAY_TO_RGB(rgb, unsigned char, AsUnsignedCharArray, (int));
        break;
    case INT_ARRAY_NODE:
        ARRAY_TO_RGB(rgb, int, AsIntArray, (int));
        break;
    case LONG_ARRAY_NODE:
        ARRAY_TO_RGB(rgb, long, AsLongArray, (int));
        break;
    case FLOAT_ARRAY_NODE:
        ARRAY_TO_RGB(f_rgb, float, AsFloatArray, (float));
        fp = true;
        break;
    case DOUBLE_ARRAY_NODE:
        ARRAY_TO_RGB(f_rgb, double, AsDoubleArray, (float));
        fp = true;
        break;
    case CHAR_VECTOR_NODE:
        VECTOR_TO_RGB(rgb, charVector, AsCharVector, (int));
        break;
    case UNSIGNED_CHAR_VECTOR_NODE:
        VECTOR_TO_RGB(rgb, unsignedCharVector, AsUnsignedCharVector, (int));
        break;
    case INT_VECTOR_NODE:
        VECTOR_TO_RGB(rgb, intVector, AsIntVector, (int));
        break;
    case LONG_VECTOR_NODE:
        VECTOR_TO_RGB(rgb, longVector, AsLongVector, (int));
        break;
    case FLOAT_VECTOR_NODE:
        VECTOR_TO_RGB(f_rgb, floatVector, AsFloatVector, (float));
        fp = true;
        break;
    case DOUBLE_VECTOR_NODE:
        VECTOR_TO_RGB(f_rgb, doubleVector, AsDoubleVector, (float));
        fp = true;
        break;
    default:
        retval = false;
        break;
    }

#undef ARRAY_TO_RGB
#undef VECTOR_TO_RGB
#define COLOR_CLAMP(C) (((C < 0) ? 0 : C) > 255) ? 255 : ((C < 0) ? 0 : C);

    if(retval)
    {
        if(fp)
        {
            rgb[0] = int(f_rgb[0] * 255.);
            rgb[1] = int(f_rgb[1] * 255.);
            rgb[2] = int(f_rgb[2] * 255.);
        }
        rgb[0] = COLOR_CLAMP(rgb[0]);
        rgb[1] = COLOR_CLAMP(rgb[1]);
        rgb[2] = COLOR_CLAMP(rgb[2]);
        color = QColor(rgb[0], rgb[1], rgb[2]);
    }
#undef COLOR_CLAMP

    return retval;
}

// ****************************************************************************
// Method: QColorToDataNode
//
// Purpose:
//   This function inserts a color into a data node.
//
// Arguments:
//   node : The node into which we're inserting the color.
//   key  : The name of the new color node.
//   c    : The color to insert.
//
// Programmer: Brad Whitlock
// Creation:   Thu Nov 16 13:35:18 PST 2006
//
// Modifications:
//
// ****************************************************************************

void
QColorToDataNode(DataNode *node, const char *key, const QColor &c)
{
    int tmp[3];
    tmp[0] = c.red();
    tmp[1] = c.green();
    tmp[2] = c.blue();

    node->RemoveNode(key);
    node->AddNode(new DataNode(key, tmp, 3));
}

// ****************************************************************************
// Method: InitializeQComboBoxFromDataNode
//
// Purpose:
//   Initializes a QComboBox from a DataNode
//
// Arguments:
//   obj  : The QComboBox to initialize.
//   node : The DataNode to use for initialization.
//
// Programmer: Brad Whitlock
// Creation:   Thu Nov 16 14:07:48 PST 2006
//
// Modifications:
//   Brad Whitlock, Tue Oct  7 10:32:39 PDT 2008
//   Qt 4.
//
// ****************************************************************************

static void
InitializeQComboBoxFromDataNode(QComboBox *co, DataNode *node)
{
    if(node->GetNodeType() == INT_NODE)
    {
        int index = node->AsInt();
        if(index < 0 || index >= co->count())
        {
            debug1 << node->GetKey().c_str() << " is out of range [0,"
                   << co->count() << "]" << endl;
            index = 0;
        }

        co->setCurrentIndex(index);
    }
    else if(node->GetNodeType() == STRING_NODE)
    {
        for(int i = 0; i < co->count(); ++i)
        {
            if(co->itemText(i).toStdString() == node->AsString())
            {
                co->setCurrentIndex(i);
                return;
            }
        }

        debug1 << node->GetKey().c_str() << " value of " << node->AsString().c_str()
               << " does not match any of the items in the QComboBox." << endl;
    }
    else
    {
        debug1 << "InitializeQComboBoxFromDataNode: only supports INT_NODE, STRING_NODE"
               << endl;
    }
}

// ****************************************************************************
// Function: InitializeDataNodeFromQComboBox
//
// Purpose:
//   Initializes a data node from the active item in a QComboBox.
//
// Arguments:
//   co   : The combo box that we're considering.
//   node : The parent of the node that we'll create.
//
// Programmer: Brad Whitlock
// Creation:   Thu Nov 16 14:16:16 PST 2006
//
// Modifications:
//   Brad Whitlock, Tue Oct  7 10:38:19 PDT 2008
//   Qt 4.
//
// ****************************************************************************

static void
InitializeDataNodeFromQComboBox(QComboBox *co, DataNode *node)
{
    std::string objectName(co->objectName().toStdString());
    DataNode *currentNode = node->GetNode(objectName);
    if(currentNode != 0)
    {
        // Use int or string, depending on what the node was initially.
        NodeTypeEnum t = currentNode->GetNodeType();
        if(t != INT_NODE && t != STRING_NODE)
        {
            debug1 << "InitializeDataNodeFromQComboBox: only supports INT_NODE, STRING_NODE"
                   << endl;
            t = INT_NODE;
        }

        node->RemoveNode(objectName);

        if(t == INT_NODE)
            node->AddNode(new DataNode(objectName, co->currentIndex()));
        else if(t == STRING_NODE)
        {
            node->AddNode(new DataNode(objectName,
                co->currentText().toStdString()));
        }
    }
    else
    {
        // There's no preference on which type to use so use int.
        node->AddNode(new DataNode(objectName, co->currentIndex()));
    }
}

// ****************************************************************************
// Function: InitializeQCheckBoxFromDataNode
//
// Purpose:
//   Initializes a QCheckBox from a data node.
//
// Arguments:
//   co   : The check box to initialize.
//   node : The data node to use for values.
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:40:22 PDT 2006
//
// Modifications:
//
// ****************************************************************************

static void
InitializeQCheckBoxFromDataNode(QCheckBox *co, DataNode *node)
{
    co->setChecked(DataNodeToBool(node));
}

// ****************************************************************************
// Method: InitializeDataNodeFromQCheckBox
//
// Purpose:
//   Initialize a data node from a QCheckBox.
//
// Arguments:
//   co : The check box from which to get the bool.
//   node : The node that will get the new bool value.
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:41:00 PDT 2006
//
// Modifications:
//
// ****************************************************************************

static void
InitializeDataNodeFromQCheckBox(QCheckBox *co, DataNode *node)
{
    std::string objectName(co->objectName().toStdString());
    node->RemoveNode(objectName);
    node->AddNode(new DataNode(objectName, co->isChecked()));
}

// ****************************************************************************
// Function: InitializeQButtonGroupFromDataNode
//
// Purpose:
//   Initializes a QButtonGroup from a data node.
//
// Arguments:
//   co : The button group to initialize.
//   node : The data node to use for initialization.
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:41:50 PDT 2006
//
// Modifications:
//   Brad Whitlock, Tue Oct  7 10:37:40 PDT 2008
//   Qt 4.
//
// ****************************************************************************

static void
InitializeQButtonGroupFromDataNode(QButtonGroup *co, DataNode *node)
{
    int index = DataNodeToInt(node);
    if(co->button(index) != 0)
        co->button(index)->setChecked(true);
}

// ****************************************************************************
// Method: InitializeDataNodeFromQButtonGroup
//
// Purpose:
//   Initializes a data node from a QButtonGroup.
//
// Arguments:
//   co   : The button group widget.
//   node : The data node to populate.
//
// Programmer: Brad Whitlock
// Creation:   Fri Nov 17 10:39:23 PDT 2006
//
// Modifications:
//   Brad Whitlock, Tue Oct  7 10:36:30 PDT 2008
//   Qt 4.
//
// ****************************************************************************

static void
InitializeDataNodeFromQButtonGroup(QButtonGroup *co, DataNode *node)
{
    std::string objectName(co->objectName().toStdString());
    DataNode *currentNode = node->GetNode(objectName);
    QAbstractButton *sb = co->checkedButton();

    if(currentNode != 0)
    {
        // Use int or string, depending on what the node was initially.
        NodeTypeEnum t = currentNode->GetNodeType();
        node->RemoveNode(objectName);

        if(t == STRING_NODE)
        {
            if(sb != 0)
                node->AddNode(new DataNode(objectName, sb->text().toStdString()));
            else
                node->AddNode(new DataNode(objectName, int(0)));
        }
        else
        {
            int index = sb ? co->id(sb) : 0;
            node->AddNode(new DataNode(objectName, index));
        }
    }
    else
    {
        // There's no preference on which type to use so use int
        int index = sb ? co->id(sb) : 0;
        node->AddNode(new DataNode(objectName, index));
    }
}

// ****************************************************************************
// Function: InitializeWidgetFromDataNode
//
// Purpose:
//   This function initializes a Qt widget (and its children) using a data
//   node, allowing us to initialize our custom UI's from data node from
//   saved settings, session files, etc.
//
// Arguments:
//   ui   : The parent widget to initialize.
//   node : The node that contains the data.
//
// Programmer: Brad Whitlock
// Creation:   Thu Nov 16 13:36:10 PST 2006
//
// Modifications:
//   Brad Whitlock, Tue Oct  7 11:14:47 PDT 2008
//   Qt 4.
//
// ****************************************************************************

void
InitializeWidgetFromDataNode(QWidget *ui, DataNode *node)
{
    const char *mName = "InitializeWidgetFromDataNode";

    // Iterate over the objects in the custom page and try and find
    // a setting in the config file with the same name. If we find
    // a compatible value then set it.
    QList<QWidget*> widgets = ui->findChildren<QWidget*>();
    for(int i = 0; i < widgets.size(); ++i)
    {
        QWidget *obj = widgets[i];
        std::string objectName(obj->objectName().toStdString());

        DataNode *objValues = node->GetNode(objectName);
        if(objValues)
        {
            debug4 << "Found values for object "
                   << objectName << endl;
            if(obj->inherits("QButtonGroup"))
            {
                InitializeQButtonGroupFromDataNode((QButtonGroup*)obj, node);
            }
            else if(obj->inherits("QCheckBox"))
            {
                InitializeQCheckBoxFromDataNode((QCheckBox*)obj, node);
            }
            else if(obj->inherits("QComboBox"))
            {
                InitializeQComboBoxFromDataNode((QComboBox*)obj, node);
            }
            if(obj->inherits("QLineEdit"))
            {
                QLineEdit *co = (QLineEdit *)obj;
                co->setText(DataNodeToQString(objValues));
            }
            else if(obj->inherits("QSpinBox"))
            {
                QSpinBox *co = (QSpinBox *)obj;
                int ival = DataNodeToInt(objValues);
                co->setValue(ival);
            }
            else if(obj->inherits("QTextEdit"))
            {
                QTextEdit *co = (QTextEdit *)obj;
                co->setText(DataNodeToQString(objValues));
            }

            // Fill in the rest of these ...

            // Do some of VisIt's custom widgets.
            else if(obj->inherits("QvisColorButton"))
            {
                QvisColorButton *cb = (QvisColorButton *)obj;
                QColor color;
                if(DataNodeToQColor(objValues, color))
                {
                    debug4 << "Setting " << objectName
                           << " to color (" << color.red()
                           << ", " << color.green()
                           << ", " << color.blue() << ")" << endl;
                    cb->setButtonColor(color);
                }
                else
                {
                    debug4 << mName << "There was no acceptable "
                           << "conversion from the data node type "
                           << "to QColor for " << objectName
                           << ".\n";
                }
            }
            else if(obj->inherits("QvisDialogLineEdit"))
            {
                QvisDialogLineEdit *co = (QvisDialogLineEdit *)obj;
                co->setText(DataNodeToQString(objValues));
            }
            else if(obj->inherits("QvisBaseVariableButton"))
            {
                QvisBaseVariableButton *co = (QvisBaseVariableButton *)obj;
                co->setVariable(DataNodeToQString(objValues));
            }
            else
            {
                debug4 << "There is currently no support for "
                       << objectName << " widgets." << endl;
            }
        }
        else
        {
            debug4 << "Did not find values for object "
                   << objectName << endl;
        }
    }
}

// ****************************************************************************
// Function: InitializeDataNodeFromWidget
//
// Purpose:
//   This function adds the widget data values into the data node structure.
//
// Arguments:
//   ui   : The parent widget.
//   node : The node that will get the widget data.
//
// Programmer: Brad Whitlock
// Creation:   Thu Nov 16 13:38:15 PST 2006
//
// Modifications:
//   Brad Whitlock, Tue Oct  7 11:14:39 PDT 2008
//   Qt 4.
//
// ****************************************************************************

void
InitializeDataNodeFromWidget(QWidget *ui, DataNode *node)
{
    // Iterate over the objects in the custom page and try and find
    // a setting in the config file with the same name. If we find
    // a compatible value then set it.

    QList<QWidget*> widgets = ui->findChildren<QWidget*>();
    for(int i = 0; i < widgets.size(); ++i)
    {
        QWidget *obj = widgets[i];
        std::string objectName(obj->objectName().toStdString());

        DataNode *objValues = node->GetNode(objectName);
        if(objValues)
        {
            // objValues points to the node in the settings that
            // contains the settings for the named widget.
            if(obj->inherits("QButtonGroup"))
            {
                InitializeDataNodeFromQButtonGroup((QButtonGroup *)obj, node);
            }
            else if(obj->inherits("QCheckBox"))
            {
                InitializeDataNodeFromQCheckBox((QCheckBox *)obj, node);
            }
            else if(obj->inherits("QComboBox"))
            {
                InitializeDataNodeFromQComboBox((QComboBox *)obj, node);
            }
            else if(obj->inherits("QLineEdit"))
            {
                QLineEdit *co = (QLineEdit *)obj;
                QString text(co->text());

                // Change values by deleting and inserting a node.
                node->RemoveNode(objectName);
                node->AddNode(new DataNode(objectName, text.toStdString()));
            }
            else if(obj->inherits("QSpinBox"))
            {
                QSpinBox *co = (QSpinBox *)obj;

                // Change values by deleting and inserting a node.
                node->RemoveNode(objectName);
                node->AddNode(new DataNode(objectName, co->value()));
            }
            else if(obj->inherits("QTextEdit"))
            {
                QTextEdit *co = (QTextEdit *)obj;
                QString text(co->toPlainText());

                // Change values by deleting and inserting a node.
                node->RemoveNode(objectName);
                node->AddNode(new DataNode(objectName, text.toStdString()));
            }

            //
            // Do some of VisIt's custom widgets.
            //
            else if(obj->inherits("QvisColorButton"))
            {
                QvisColorButton *co = (QvisColorButton *)obj;

                // Delete the current data node values.
                node->RemoveNode(objectName);

                // Add in the new color data node.
                int rgb[3];
                rgb[0] = co->buttonColor().red();
                rgb[1] = co->buttonColor().green();
                rgb[2] = co->buttonColor().blue();
                node->AddNode(new DataNode(objectName, rgb, 3));
            }
            else if(obj->inherits("QvisDialogLineEdit"))
            {
                QvisDialogLineEdit *co = (QvisDialogLineEdit *)obj;
                QString text(co->text());

                // Change values by deleting and inserting a node.
                node->RemoveNode(objectName);
                node->AddNode(new DataNode(objectName, text.toStdString()));
            }
            else if(obj->inherits("QvisBaseVariableButton"))
            {
                QvisBaseVariableButton *co = (QvisBaseVariableButton *)obj;
                QString text(co->getVariable());

                // Change values by deleting and inserting a node.
                node->RemoveNode(objectName);
                node->AddNode(new DataNode(objectName, text.toStdString()));
            }
        }
    }
}

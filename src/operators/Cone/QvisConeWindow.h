// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef QVISCONEWINDOW_H
#define QVISCONEWINDOW_H

#include <QvisOperatorWindow.h>
#include <AttributeSubject.h>

class ConeAttributes;
class QLabel;
class QCheckBox;
class QLineEdit;
class QButtonGroup;

// ****************************************************************************
// Class: QvisConeWindow
//
// Purpose:
//    Defines QvisConeWindow class.
//
// Notes:      Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   Cyrus Harrison, Tue Aug 19 09:28:38 PDT 2008
//   Qt4 Port - Autogen and removed lengthLabel.
//
// ****************************************************************************

class QvisConeWindow : public QvisOperatorWindow
{
    Q_OBJECT
  public:
    QvisConeWindow(const int type,
                         ConeAttributes *subj,
                         const QString &caption = QString(),
                         const QString &shortName = QString(),
                         QvisNotepadArea *notepad = 0);
    virtual ~QvisConeWindow();
    virtual void CreateWindowContents();
  protected:
    void UpdateWindow(bool doAll);
    virtual void GetCurrentValues(int which_widget);
  private slots:
    void angleProcessText();
    void originProcessText();
    void normalProcessText();
    void representationChanged(int val);
    void upAxisProcessText();
    void cutByLengthChanged(bool val);
    void lengthProcessText();
  private:
    QLineEdit *angle;
    QLineEdit *origin;
    QLineEdit *normal;
    QButtonGroup *representation;
    QLineEdit *upAxis;
    QCheckBox *cutByLength;
    QLineEdit *length;
    QLabel *angleLabel;
    QLabel *originLabel;
    QLabel *normalLabel;
    QLabel *representationLabel;
    QLabel *upAxisLabel;

    ConeAttributes *atts;
};



#endif

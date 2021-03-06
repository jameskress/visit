// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include "Scanner.h"
#include "ExprParser.h"
#include "ParseException.h"

// ****************************************************************************
//  Function:  main
//
//  Programmer:  Jeremy Meredith
//  Creation:    April  5, 2002
//
//  Modifications:
//    Jeremy Meredith, Mon Jul 28 16:53:15 PDT 2003
//    Made the expression parser print error messages to the console.
//    (Another simultaneous change made the default be the viewer error
//    reporting mechanism.)
//
//    Jeremy Meredith, Wed Nov 24 12:13:20 PST 2004
//    Refactored the parser into generic and VisIt Expression specific pieces.
//
// ****************************************************************************
int
main(int argc, char *argv[])
{
    if (argc<2) {cerr<<"needs an argument\n"; exit(-1);} // HOOKS_IGNORE

    Parser *parser = new ExprParser(new ExprNodeFactory());
    ExprParser::SetErrorMessageTarget(ExprParser::EMT_CONSOLE);

    for (int i=1; i<argc; i++)
    {
        cout << "\n----\n";
        cout << "PARSING '"<<argv[i]<<"'"<<endl;
        cout << "----\n\n";

        ExprNode *node = (ExprNode*)parser->Parse(argv[i]);
        if (node)
            node->Print(cout);
        else
            cout << "ERROR\n";
    }

    return 0;
}

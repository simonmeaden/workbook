/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#ifndef WORKBOOKPARSERPRIVATE_H
#define WORKBOOKPARSERPRIVATE_H

#include <QVariant>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QStack>

#include "types.h"
#include "interface.h"
#include "reference.h"

class Worksheet;
class PluginStore;
class WorkbookParser;

class Token : public QObject {
public:
    Token() {}
    Token(int start, int end, QObject *parent) :
        QObject(parent) {

        mStart = start, mEnd = end;

    }

    int start() {
        return mStart;
    }
    int end() {
        return mEnd;
    }

protected:
    int mStart, mEnd;
};

class CommaToken : public Token {
public:
    CommaToken(int &start, QObject *parent=0) :
        Token(start, start, parent) {}
};

class  CloseParenthesisToken : public Token {
public:
    CloseParenthesisToken() {}
    CloseParenthesisToken(int &start, QObject *parent) :
        Token(start, start, parent) {

    }
};

class  OpenParenthesisToken : public Token {
public:
    OpenParenthesisToken(int &start, QObject *parent) :
        Token(start, start, parent) {
        mPartner = NULL;
    }

    CloseParenthesisToken* partner() {
        return mPartner;
    }
    void setPartner(CloseParenthesisToken *token) {
        mPartner = token;
    }

protected:
    CloseParenthesisToken *mPartner;
};

class CellReferenceToken : public Token, public Reference {
public:
    CellReferenceToken(QString &ref, int &start, int &end, QObject *parent);

    int column() { return mColumn; }
    int row() { return mRow; }

protected:
    int mColumn;
    int mRow;

};

class FunctionToken : public Token {
public:
    FunctionToken(QString function, int start, int end, QObject *parent) :
        Token(start, end, parent) {
        mFunction = function;
    }

    QString function() {
        return mFunction;
    }

protected:
    QString mFunction;
};

class OperatorToken : public Token {
public:
    OperatorToken(QString operation, int start, int end, QObject *parent) :
        Token(start, end, parent) {
        mOperator = operation;
    }

    QString getOperator() {
        return mOperator;
    }

protected:
    QString mOperator;
};

class ConstantToken : public Token {
public:
    ConstantToken(QString constant, int start, int end, QObject *parent) :
        Token(start, end, parent) {
        mConstant = constant;
    }

    QString value() {
        return mConstant;
    }

protected:
    QString mConstant;
};

class NumberToken : public Token {
public:
    NumberToken(QObject *parent) : Token(0, 0, parent) {}
    NumberToken(QString number, int start, int end, QObject *parent) :
        Token(start, end, parent) {
        bool ok;
        if (number.indexOf(".") != -1) {
            double n = number.toDouble(&ok);
            if (ok)
                mNumber = QVariant(n);
        } else {
            int n = number.toInt(&ok);
            if (ok)
                mNumber = QVariant(n);
        }
    }

    void setValue(QVariant value) { mNumber = value; }

    QVariant value() {
        return mNumber;
    }

protected:
    QVariant mNumber;
};

class WorkbookParserPrivate {
public:
    WorkbookParserPrivate(PluginStore *store, WorkbookParser *parent);

    QVariant parse(Worksheet *sheet, QString expression);
    ParserErrors error();

    void setFunctions(QStringList list);
    void setOperations(QStringList list);
    void setConstants(QStringList list);
    void clearErrors();


protected:
    QString mFunctionsRegex;
    QString mOperationsRegex;
    QString mConstantsRegex;
    ParserErrors mError;
    PluginStore *pPluginStore;

    QMap<QString, IFunction*> mFunctions;
    QMap<QString, IOperator*> mOperators;
    QMap<QString, IConstant*> mConstants;

    QStack<IOperator*> opStack;
    QStack<QVariant> valueStack;

    QMap<int, Token*> analyseExpression(QString expression);
    QVariant parseExpression(Worksheet *sheet, QList<Token*> tokens);
    QList<Token*> separateFunctionList(int index, QList<Token *> tokens);
    QVariant parseFunction(Worksheet *sheet, IFunction *iFunction, QList<Token*> tokens);

    QVariant nullVariant() { return QVariant(QVariant::Double); }

    const static QString CellReferenceRegex;
    const static QString HexNumberRegex;
//    const static QString MatchedParenthesisRegex;
    const static QString NumbersRegex;

    WorkbookParser *q_ptr;
};

#endif // WORKBOOKPARSERPRIVATE_H

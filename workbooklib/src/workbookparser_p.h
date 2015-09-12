/*
    Copyright © Simon Meaden 2015.

    This file is part of the QWorkbook spreadsheet library.

    QWorkbook is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QWorkbook is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QWorkbook.  If not, see <http://www.gnu.org/licenses/>.

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

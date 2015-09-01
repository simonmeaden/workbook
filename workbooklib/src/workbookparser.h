#ifndef WORKBOOKPARSER_H
#define WORKBOOKPARSER_H

#include <QObject>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QPair>
#include <QList>
#include <QMap>
#include <QStack>

#include "qquad.h"

#include "reference.h"
#include "workbook_global.h"
#include "worksheet.h"

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

class PluginStore;

class WORKBOOKSHARED_EXPORT WorkbookParser : public QObject {
    Q_OBJECT
    Q_ENUMS(Error)
    Q_FLAGS(Errors)
public:
    enum Error {
        NoError=0x0,
        UnbalancedParethesis=0x1,
        UnhandledPartialExpression=0x2,
        NotAFunction=0x4,
        FunctionNotFollowedByParenthesis=0x8,
        EmptyFunction=0x10,
        WrongNumberOfFunctionParameters = 0x20,
        WrongParameterType=0x40,
        BrokenExpression=0x80,
        NoFunctionAvailable=0x100,
    };
    Q_DECLARE_FLAGS(Errors, Error)

    WorkbookParser(PluginStore *store, QObject *parent=0);

    QVariant parse(Worksheet *sheet, QString expression);
    Errors error();

public slots:
    void setFunctions(QStringList list);
    void setOperations(QStringList list);
    void setConstants(QStringList list);
    void clearErrors();


protected:
    QString mFunctionsRegex;
    QString mOperationsRegex;
    QString mConstantsRegex;
    Errors mError;
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
};

Q_DECLARE_OPERATORS_FOR_FLAGS(WorkbookParser::Errors)
Q_DECLARE_METATYPE(WorkbookParser::Error)

#endif // WORKBOOKPARSER_H

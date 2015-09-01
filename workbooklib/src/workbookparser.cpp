#include "workbookparser.h"
#include "qstd.h"
#include "pluginstore.h"


WorkbookParser::WorkbookParser(PluginStore *store, QObject *parent) :
    QObject(parent),
    pPluginStore(store) {
    mError = NoError;
}

WorkbookParser::Errors WorkbookParser::error() {
    return mError;
}

void WorkbookParser::clearErrors() {
    mError = NoError;
}

QVariant WorkbookParser::parse(Worksheet *sheet, const QString expression) {

    clearErrors();

    QString exp = expression.toUpper();

    QMap<int, Token*> tokenMap = analyseExpression(exp);

    // convert the map of position/Token to an ordered list.
    QList<Token*> tokens;
    QList<int> positions = tokenMap.keys();

    if (positions.size() == 0) {

        mError |= NotAFunction;
        return QVariant(QVariant::Double);

    } else {

        QListIterator<int> posIt(positions);
        while (posIt.hasNext()) {
            int p = posIt.next();
            tokens.append(tokenMap.value(positions.at(p)));
        }

        QVariant value = parseExpression(sheet, tokens);
        return value;
    }

    return QVariant(QVariant::Double);

}

const QString WorkbookParser::CellReferenceRegex = "[^0-9a-zA-Z_$:](\\$?[a-zA-Z]{1,2}\\$?[1-9][0-9]*)(?![0-9a-zA-Z_:])";
//const QString WorkbookParser::ScientificNumberRegex = "((\\b[0-9]+)?\\.)?\\b[0-9]+([eE][-+]?[0-9]+)?\\b";
const QString WorkbookParser::HexNumberRegex = "\\b0[xX][0-9a-fA-F]+\\b";
//const QString WorkbookParser::MatchedParenthesisRegex = "((?>[^()]|(?R))*";
const QString WorkbookParser::NumbersRegex = "[+-]?([0-9]*\\.?[0-9]+|[0-9]+\\.?[0-9]*)([eE][+-]?[0-9]+)?";

QVariant WorkbookParser::parseExpression(Worksheet* sheet, QList<Token *> tokens) {

    int index = 0;
    Token *token;
    for (; index < tokens.size(); index++) {

        token = tokens.value(index);
        NumberToken *num = dynamic_cast<NumberToken*>(token);
        OperatorToken *op = dynamic_cast<OperatorToken*>(token);
        CellReferenceToken *cellRef = dynamic_cast<CellReferenceToken*>(token);
        ConstantToken *constant = dynamic_cast<ConstantToken*>(token);
        FunctionToken *func = dynamic_cast<FunctionToken*>(token);

        if (num) {
            valueStack.push(num->value());
            continue;
        }

        if (op) {
            IOperator *iop = pPluginStore->getOperator(op->getOperator());
            if (iop)
                opStack.push(iop);
            continue;
        }

        if (cellRef) {
            QVariant v = sheet->cell(cellRef->row(), cellRef->column());
            valueStack.push(v);
            continue;
        }

        if (constant) {
            IConstant *con = pPluginStore->getConstant(constant->value());
            if (con)
                valueStack.push(con->value());
        }

        if (func) {


            QList<Token*> functionList = separateFunctionList(index, tokens);

            IFunction *f = pPluginStore->getFunction(func->function());

            QVariant v = parseFunction(sheet, f, functionList);
            valueStack.push(v);

        }
    }
    // TODO parse valueList/ operatorList
    return QVariant();
}

QList<Token*> WorkbookParser::separateFunctionList(int index, QList<Token *> tokens) {

    Token *nextToken = tokens.at(index + 1);
    OpenParenthesisToken *openToken = dynamic_cast<OpenParenthesisToken*>(nextToken);
    QList<Token*> tokenList;

    if (openToken) {
        CloseParenthesisToken *closeToken = openToken->partner();
        if (closeToken != NULL) {

            int start = tokens.indexOf(openToken);
            int end = tokens.indexOf(closeToken);



            for (int i = start + 1; i < end; i++) {
                tokenList.append(tokens.at(i));
            }

        }
    }
    return tokenList;
}

QVariant WorkbookParser::parseFunction(Worksheet *sheet, IFunction *iFunction, QList<Token *> tokens) {

    /*
        A function can contain :
        - A value.
        - A function
        - An expression
        - a godawful mix of above, ie.
         A comma deliniated list of values, expressions and functions.
         Any of the first three can be condensed down into a single value list.
    */

    Token *t;
    QVariant value;
    OperatorToken *opToken;
    NumberToken *numToken;
    CommaToken *commaToken;
    FunctionToken *functionToken;
    QList<QVariant> valueList;
    QList<Token*> expressionList;

    for (int index = 0; index < tokens.size(); index++) {
        t = tokens.at(index);

        // an operator gets added to the expression list
        opToken = dynamic_cast<OperatorToken*>(t);
        if (opToken) {

            expressionList.append(opToken);

        }

        // a value gets added to the expression list.
        numToken = dynamic_cast<NumberToken*>(t);
        if (numToken) {

            expressionList.append(numToken);
            continue;

        }

        // a function gets separated out and recursed to get it's value
        functionToken = dynamic_cast<FunctionToken*>(t);
        if (functionToken) {

            QList<Token*> functionList = separateFunctionList(index, tokens);

            IFunction *f = pPluginStore->getFunction(functionToken->function());

            QVariant v = parseFunction(sheet, f, functionList);
            numToken = new NumberToken(this); // unfortunately the list needs tokens
            numToken->setValue(v);
            expressionList.append(numToken);

        }

        // end of current expression
        commaToken = dynamic_cast<CommaToken*>(t);
        if (commaToken) {

            numToken = dynamic_cast<NumberToken*>(expressionList.at(0));

            if (expressionList.size() == 1 && numToken) {
                // if it's a single value add it to the value list.

                valueList.append(numToken->value());
                expressionList.clear();

            } else {
                // otherwise it was an expression of some type so evaluate it.

                value = parseExpression(sheet, expressionList);

                // empty expression so return with whatever error was already set.
                if (value.isNull()) return value;

                valueList.append(value);

            }

        }


    }

    // add the last item to the value list after the last comma
    numToken = dynamic_cast<NumberToken*>(expressionList.at(0));
    if (expressionList.size() == 1 && numToken) {

        valueList.append(numToken->value());

    } else {

        value = parseExpression(sheet, expressionList);
        valueList.append(value);

    }

    // at this point we should just have a list of values

    bool ok;
    // should be either one value, two or more values separated by commas,
    if (valueList.size() == 1) {

        NumberToken *num= dynamic_cast<NumberToken*>(expressionList.at(0));
        if (!num)  {
            mError |= WrongParameterType;
            return nullVariant();
        }

        IOneValueFunction<qreal> *oneFunc1 = dynamic_cast<IOneValueFunction<qreal>*>(iFunction);
        if (oneFunc1) {
            qreal v = num->value().toDouble(&ok);
            if (!ok) {
                mError |= WrongParameterType;
                return nullVariant();
            }
            QVariant value = oneFunc1->calculate(v);
            return value;
        }

        IOneValueFunction<quint32> *oneFunc2 = dynamic_cast<IOneValueFunction<quint32>*>(iFunction);
        if (oneFunc1) {
            quint32 v = num->value().toUInt(&ok);
            if (!ok) {
                mError |= WrongParameterType;
                return nullVariant();
            }
            QVariant value = oneFunc2->calculate(v);
            return value;
        }

        mError |= NoFunctionAvailable;
        return nullVariant();

    } else if (valueList.size() == 2) {

        NumberToken *num1 = dynamic_cast<NumberToken*>(expressionList.at(0));
        if (!num1) {
            mError |= WrongParameterType;
            return nullVariant();
        }

        NumberToken *num2 = dynamic_cast<NumberToken*>(expressionList.at(1));
        if (!num2) {
            mError |= WrongParameterType;
            return nullVariant();
        }

        ITwoValueFunction<qreal, qreal> *twoFunc2a = dynamic_cast<ITwoValueFunction<qreal, qreal>*>(iFunction);
        if (twoFunc2a) {
            qreal v1 = num1->value().toDouble(&ok);
            if (!ok) {
                mError |= WrongParameterType;
                return nullVariant();
            }

            qreal v2 = num2->value().toDouble();
            if (!ok) {
                mError |= WrongParameterType;
                return nullVariant();
            }

            value = twoFunc2a->calculate(v1, v2);
            return value;
        }

        ITwoValueFunction<quint32, quint32> *twoFunc2b = dynamic_cast<ITwoValueFunction<quint32, quint32>*>(iFunction);
        if (twoFunc2b) {

            quint32 v1 = num1->value().toUInt(&ok);
            if (!ok) {
                mError |= WrongParameterType;
                return nullVariant();
            }

            quint32 v2 = num2->value().toUInt();
            if (!ok) {
                mError |= WrongParameterType;
                return nullVariant();
            }

            value = twoFunc2b->calculate(v1, v2);
            return value;
        }

        mError |= NoFunctionAvailable;
        return nullVariant();

    } else {
        IListFunction<qreal> *listFunca = dynamic_cast<IListFunction<qreal>*>(iFunction);
        if (listFunca) {

            QList<qreal> list;
            QListIterator<QVariant> it(valueList);
            while (it.hasNext()) {

                qreal v = it.next().toDouble(&ok);
                if (!ok)  {
                    mError |= WrongParameterType;
                    return nullVariant();
                }

                list.append(v);


                value = listFunca->calculate(list);
                return value;
            }
        }
        IListFunction<quint32> *listFuncb = dynamic_cast<IListFunction<quint32>*>(iFunction);
        if (listFuncb) {

            QList<quint32> list;
            QListIterator<QVariant> it(valueList);
            while (it.hasNext()) {

                quint32 v = it.next().toUInt(&ok);
                if (!ok)  {
                    mError |= WrongParameterType;
                    return nullVariant();
                }

                list.append(v);

                value = listFuncb->calculate(list);
                return value;
            }
        }

    }
    return QVariant();
}

QMap<int, Token*>  WorkbookParser::analyseExpression(QString exp) {

    QMap<int, Token*> tokens;

    // first analyse the expression
    if (exp.trimmed().startsWith("=")) {

        QRegularExpression re;
        QRegularExpressionMatch match;
        QRegularExpressionMatchIterator it;
        QString refString, s;
        Token *token;

        int start = 0, end, len;
        re.setPattern(CellReferenceRegex);
        it = re.globalMatch(exp);
        while (it.hasNext()) {
            match = it.next();

            refString = match.captured();
            start = match.capturedStart();
            end = match.capturedStart();
            len = end - start;
            token = new CellReferenceToken(refString, start, end, this);
            tokens.insert(start, token);

            s.fill(' ', len);
            exp.replace(start, len, s);

        }

        // Functions MUST be followed by an opening parenthesis
        re.setPattern(mFunctionsRegex);
        it = re.globalMatch(exp);
        while (it.hasNext()) {
            match = it.next();

            refString = match.captured();
            start = match.capturedStart();
            end = match.capturedStart();
            len = end - start;
            // only save the function, not the opening parenthesis
            token = new FunctionToken(refString.left(len - 1), start, end, this);
            tokens.insert(start, token);

            s.fill(' ', len - 1);
            exp.replace(start, len, s);
        }

        re.setPattern(mOperationsRegex);
        it = re.globalMatch(exp);
        while (it.hasNext()) {
            match = it.next();

            refString = match.captured();
            start = match.capturedStart();
            end = match.capturedStart();
            len = end - start;
            token = new OperatorToken(refString, start, end, this);
            tokens.insert(start, token);

            s.fill(' ', len);
            exp.replace(start, len, s);
        }

        re.setPattern(mConstantsRegex);
        it = re.globalMatch(exp);
        while (it.hasNext()) {
            match = it.next();

            refString = match.captured();
            start = match.capturedStart();
            end = match.capturedStart();
            len = end - start;
            token = new ConstantToken(refString, start, end, this);

            tokens.insert(start, token);

            s.fill(' ', len);
            exp.replace(start, len, s);
        }

        re.setPattern(NumbersRegex);
        it = re.globalMatch(exp);
        while (it.hasNext()) {
            match = it.next();

            refString = match.captured();
            start = match.capturedStart();
            end = match.capturedStart();
            len = end - start;
            token = new NumberToken(refString, start, end, this);
            tokens.insert(start, token);

            s.fill(' ', len);
            exp.replace(start, len, s);
        }

        // handle comma separated list.
        int pos;
        pos = exp.indexOf(",");
        while(pos != -1) {
            token = new CommaToken(pos, this);
            tokens.insert(pos, token);
            exp.replace(start, 1, " ");
        }

        // handle open parenthesis
        QList<Token*> parenthesis;
        int count = 0;
        pos = exp.indexOf("(");
        while (pos != -1) {
            token = new OpenParenthesisToken(pos, this);
            parenthesis.append(token);
            tokens.insert(pos, token);
            count++;
            pos = exp.indexOf("(", pos + 1);

            exp.replace(start, 1, " ");
        }

        // handle close parenthesis
        pos = exp.indexOf(")");
        while (pos != -1) {
            token = new CloseParenthesisToken(pos, this);
            parenthesis.append(token);
            count--;
            pos = exp.indexOf(")", pos + 1);

            exp.replace(start, 1, " ");
        }
        // count should == 0 at this point otherwise
        // parenthesis are unbalanced.

        if (count != 0) {
            // shit unbalanced parenthesis.
            // TODO some sort of error
            cout << "Unbalanced parenthesis - bugger" << flush;
            mError |= UnbalancedParethesis;
            tokens.clear();
            return tokens;
        }

        // partner up the parenthesis
        QStack<OpenParenthesisToken*> openers;
        for (int i = 0; i < parenthesis.size(); i++) {
            token = parenthesis.at(i);
            OpenParenthesisToken *openToken = dynamic_cast<OpenParenthesisToken*>(token);
            if (openToken)
                openers.push(openToken);
            else {
                CloseParenthesisToken *closeToken = dynamic_cast<CloseParenthesisToken*>(token);
                if (openers.size() > 0) {
                    openToken = openers.pop();
                    openToken->setPartner(closeToken);
                } else  {
                    mError |= UnbalancedParethesis;
                    tokens.clear();
                    return tokens;
                }
            }
        }


        if (exp.trimmed().length() > 0) {
            // shit forgot something.
            // TODO some sort of error
            cout << "Something was left over - bugger : " << exp << flush;
            mError |= UnhandledPartialExpression;
            tokens.clear();
            return tokens;
        }

        mError |= NotAFunction;
        return tokens;
    }

    return tokens;
}

void WorkbookParser::setFunctions(QStringList list) {
    mFunctionsRegex = "";
    QString funcName;
    IFunction* func;
    for (int i = 0; i < list.length(); i++) {
        funcName = list.at(i);
        func = pPluginStore->getFunction(funcName);

        mFunctionsRegex.append(funcName);
        mFunctionsRegex.append("\\(");
        if (i < list.length() - 1)
            mFunctionsRegex.append("|");

        mFunctions.insert(funcName, func);
    }
}

void WorkbookParser::setOperations(QStringList list) {
    mOperationsRegex = "";
    QString opName;
    IOperator* op;
    for (int i = 0; i < list.length(); i++) {
        opName = list.at(i);
        op = pPluginStore->getOperator(opName);

        mOperationsRegex.append(opName);
        mOperationsRegex.append("\\(");
        if (i < list.length() - 1)
            mOperationsRegex.append("|");

        mOperators.insert(opName, op);
    }
}

void WorkbookParser::setConstants(QStringList list) {
    mConstantsRegex = "";
    QString conName;
    IConstant* con;
    for (int i = 0; i < list.length(); i++) {
        conName = list.at(i);
        con = pPluginStore->getConstant(conName);

        mConstantsRegex.append(conName);
        mConstantsRegex.append("\\(");
        if (i < list.length() - 1)
            mConstantsRegex.append("|");

        mConstants.insert(conName, con);
    }
}

CellReferenceToken::CellReferenceToken(QString &ref, int &start, int &end, QObject *parent) :
    Token(start, end, parent) {

    QQuad<QString, QString, QString, QString> quad = init(ref);

    if (!quad.first.isEmpty() && !quad.second.isEmpty()) {
        mColumn = columnFromString(quad.first);
        mRow = rowFromString(quad.second);
    }

}


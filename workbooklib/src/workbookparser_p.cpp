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

#include "workbookparser_p.h"
#include "workbookparser.h"
#include "regex.h"
#include "workbook_global.h"
#include "pluginstore.h"
#include "qworkbookview.h"
#include "qworksheetview.h"
#include "worksheetmodel.h"

namespace QWorkbook {

const QString WorkbookParserPrivate::WithDelimiter = "((?<=%1)|(?=%1))";

WorkbookParserPrivate::WorkbookParserPrivate(QWorkbookView *book, WorkbookParser *parent) :
    pWorkbook(book),
    pWorksheet(NULL),
    pPluginStore(new PluginStore(parent)),
    mError(NoError),
    q_ptr(parent) {

    // bracket types.
    brackets << "(" << ")";
    specials << "," << ":";

}

WorkbookParserPrivate::WorkbookParserPrivate(QWorksheetView *sheet, WorkbookParser *parent) :
    pWorkbook(NULL),
    pWorksheet(sheet),
    pPluginStore(new PluginStore(parent)),
    mError(NoError),
    q_ptr(parent) {

    // bracket types.
    brackets << "(" << ")";
    specials << "," << ":";

}

ParserErrors WorkbookParserPrivate::error() {
    return mError;
}

void WorkbookParserPrivate::clearErrors() {
    mError = NoError;
}

void WorkbookParserPrivate::dataHasChanged(const QModelIndex &topLeft,
                                    const QModelIndex &bottomRight,
                                    const QVector<int> &roles) {
    mTopLeft = topLeft;
    mBottomRight = bottomRight;
    mChangedRoles = roles;

}

QVariant WorkbookParserPrivate::parse() {

    QString expression;
    QModelIndex index;

    // TODO possibly a range of data has changed.

    if (pWorkbook) {
        index = pWorkbook->currentWorksheetView()->currentIndex();
        expression = pWorkbook->currentWorksheetView()->model()->data(index).toString();
    } else if (pWorksheet) {
        index = pWorksheet->currentIndex();
        expression = pWorksheet->model()->data(index).toString();
    }

    clearErrors();

    // formulae must start with an = sign but it has no relevance later.
    if (expression.startsWith("=")) {
        QStringList tokenList = splitExpression(expression.mid(1));
        tokenise(tokenList);
    }

    return QVariant(QVariant::Double);

}

QPair<int, double> WorkbookParserPrivate::calculateInfix(int start, QStringList items) {
    int i = start;
    bool ok;
    qreal d, n1, n2;
    QStack<qreal> values;
    QStack<OperatorBase<qreal>*> operators;
    QPair<int, double> result;

    // TODO add in errors ie unbalanced brackets wrong number
    // of values or operators
    // TODO handle cell references and ranges.

    while(i < items.size()) {
        QString s = items.at(i);

        if (s == ")") {
            result.first = i + 1;
            result.second = values.pop();
            return result;
        }

        if (s == "(") {
            i++;
            result = calculateInfix(i, items); // Recurse.
            i = result.first;
            values.push(result.second);
            continue;
        }

        d = s.toDouble(&ok);
        if (ok) {
            values.insert(i++, d);
            continue;
        }
        // turns constants into their actual value in the list.
        ConstantBase *constant = dynamic_cast<ConstantBase*>(pPluginStore->getConstant(s));
        if (constant) {
            values.insert(i++, constant->value());
            continue;
        }

        IFunction *func = dynamic_cast<IFunction*>(pPluginStore->getFunction(s));
        if (func) {
            result = calculateInfixFunction(func, i, items); // functioss should return a value.
            i = result.first;
            values.push(result.second);
            continue;
        }

        OperatorBase<qreal> *op1 = dynamic_cast<OperatorBase<qreal>*>(pPluginStore->getOperator(s));
        if (op1) {
            if (operators.size() == 0 || operators.top()->level() < op1->level()) {
                OperatorBase<qreal> *op2 = operators.pop();
                n1 = values.pop();
                n2 = values.pop();
                d = op2->calculate(n2, n1);
                values.push(d);
            }
            operators.push(op1);

            i++;
            continue;
        }

        // TODO string handling
//        OperatorBase<QString> *ops1 = dynamic_cast<OperatorBase<QString>*>(pPluginStore->getOperator(s));
//        if (op1) {
//            // convert numbers to strings if necessary
//        }

    }

    return result;
}

QPair<int, double> WorkbookParserPrivate::calculateInfixFunction(IFunction *func, int start, QStringList items) {
    // TODO
}

void WorkbookParserPrivate::tokenise(QStringList items) {

    calculateInfix(0, items);

}

QStringList WorkbookParserPrivate::splitExpression(QString expression) {
    QStringList listIn;

    mLeftBrackets = 0;
    mRightBrackets = 0;

    if (mRightBrackets != mLeftBrackets) {
        mError = UnbalancedParethesis;
    }

    listIn = splitoutCellReference(expression);
    listIn = splitoutBrackets(listIn);

    listIn = splitoutItems(listIn, specials);
    listIn = splitoutItems(listIn, pPluginStore->operatorNames());
    listIn = splitoutItems(listIn, pPluginStore->functionNames());
    listIn = splitoutItems(listIn, pPluginStore->constantNames());

    return listIn;
}

QStringList WorkbookParserPrivate::splitoutCellReference(QString expression) {
    QStringList result;
    QRegularExpression re = QRegularExpression(REGEX_CELL_REFERENCE_2);
    QRegularExpressionMatch match;
    int start, end = 0;

    QRegularExpressionMatchIterator it = re.globalMatch(expression);
    while (it.hasNext()) {
        match = it.next();
        start = match.capturedStart(0);
        result.append(expression.mid(end, start - end));
        // TODO replace cell references with actual contents of cell
        result.append(match.captured(0));
        // TODO above
        end = match.capturedEnd(0);
    }

    if (end < expression.length())
        result.append(expression.mid(end));

    return result;
}

QStringList WorkbookParserPrivate::splitoutItems(QStringList listIn, QStringList items) {
    QStringList listOut, splits;

    foreach(QString item, items) {

        QString pattern = QString(WithDelimiter).arg(QRegularExpression::escape(item));
        QRegularExpression re = QRegularExpression(pattern);

        foreach(QString s, listIn) {

            splits = s.split(re);
            QListIterator<QString> it(splits);
            while (it.hasNext()) {
                QString s = it.next();
                if (!s.isEmpty())
                    listOut.append(s);
            }

        }

        listIn = listOut;
        listOut.clear();
    }

    return listIn;
}

QStringList WorkbookParserPrivate::splitoutBrackets(QStringList listIn) {
    QStringList listOut, splits;

    foreach(QString item, brackets) {

        QString pattern = QString(WithDelimiter).arg(QRegularExpression::escape(item));
        QRegularExpression re = QRegularExpression(pattern);

        foreach(QString s, listIn) {
            if (s == "(") mLeftBrackets++;
            else if (s == ")") mRightBrackets++;

            splits = s.split(re);
            QListIterator<QString> it(splits);
            while (it.hasNext()) {
                QString s = it.next();
                if (!s.isEmpty())
                    listOut.append(s);
            }

        }

        listIn = listOut;
        listOut.clear();
    }

    bBracketsMatch = (mLeftBrackets == mRightBrackets);

    return listIn;
}


}


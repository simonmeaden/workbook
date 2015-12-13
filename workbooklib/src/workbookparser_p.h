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
#include <QPair>
#include <QModelIndex>

#include "types.h"
#include "interface.h"
#include "reference.h"

#include "workbook_global.h"

namespace QWorkbook {

class PluginStore;
class WorkbookParser;
class QWorksheetView;
class QWorkbookView;

class WorkbookParserPrivate {
public:
    WorkbookParserPrivate(QWorkbookView *book, WorkbookParser *parent);
    WorkbookParserPrivate(QWorksheetView *sheet, WorkbookParser *parent);
    virtual ~WorkbookParserPrivate() {}

    void stopProcess();

    QVariant parse();
    QStringList splitExpression(QString);

    ParserErrors error();
    void clearErrors();
    void defineRules();

    QStringList specials, brackets;
    int mLeftBrackets, mRightBrackets;
    bool bBracketsMatch;

    void dataHasChanged(const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles);

//    QList<QPair<int, int> > bracketMatch;
//    QMap<int, double> values;
//    QMultiMap<int, IFunction*> funcMatch;
//    QMultiMap<int, IOperator*> opMatch5;
//    QMultiMap<int, IOperator*> opMatch6;

    QStringList splitoutCellReference(QString);
    QStringList splitoutItems(QStringList, QStringList items);
    QStringList splitoutBrackets(QStringList);
    void tokenise(QStringList);
    QPair<int, double> calculateInfix(int, QStringList);
    QPair<int, double> calculateInfixFunction(IFunction*, int, QStringList);

    QWorkbookView *pWorkbook;
    QWorksheetView *pWorksheet;
    QModelIndex mTopLeft, mBottomRight;
    QVector <int> mChangedRoles;
    const QSharedPointer<PluginStore> pPluginStore;
    ParserErrors mError;

    WorkbookParser *q_ptr;

    static const QString WithDelimiter;
};



}

#endif // WORKBOOKPARSERPRIVATE_H

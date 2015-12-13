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
#include <QScopedPointer>
#include <QThread>
#include <QMutex>

#include <assert.h>

#include "workbook_global.h"
#include "reference.h"
#include "workbook_global.h"
#include "workbookparser_p.h"
#include "types.h"


namespace QWorkbook {

class PluginStore;
class QWorksheetView;
class QWorkbookView;
//class WorkbookParserPrivate;

class WORKBOOKSHARED_EXPORT WorkbookParser : public QThread {
    Q_OBJECT
    Q_ENUMS(ParserError)
    Q_FLAGS(ParserErrors)
    Q_DECLARE_PRIVATE(WorkbookParser)
public:

    WorkbookParser();
    WorkbookParser(QWorkbookView *parent);
    WorkbookParser(QWorksheetView *parent);
    WorkbookParser(const WorkbookParser& other) : QThread(other.parent())  { Q_ASSERT(false); }

    virtual ~WorkbookParser();

    ParserErrors error();

public slots:
    void stopProcess();
    void dataHasChanged(const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles);


protected:
    QScopedPointer<WorkbookParserPrivate> d_ptr;

    QMutex mMutex;
    bool bAbort, bDataHasChanged;

    void run();

private:

};

} // end of namespace QWorkbook

Q_DECLARE_METATYPE(QWorkbook::WorkbookParser)
typedef QSharedPointer<QWorkbook::WorkbookParser> PWorkbookParser;

#endif // WORKBOOKPARSER_H

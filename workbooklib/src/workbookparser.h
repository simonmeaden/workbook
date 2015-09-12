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

#include "qquad.h"

#include "reference.h"
#include "workbook_global.h"
#include "worksheet.h"
#include "workbookparser_p.h"
#include <types.h>

class PluginStore;
//class WorkbookParserPrivate;

class WORKBOOKSHARED_EXPORT WorkbookParser : public QObject {
    Q_OBJECT
    Q_ENUMS(ParserError)
    Q_FLAGS(ParserErrors)
public:

    WorkbookParser(PluginStore *store, QObject *parent=0);

    QVariant parse(Worksheet *sheet, QString expression);
    ParserErrors error();

public slots:
    void setFunctions(QStringList list);
    void setOperations(QStringList list);
    void setConstants(QStringList list);
    void clearErrors();


protected:
    QScopedPointer<WorkbookParserPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(WorkbookParser)

};


#endif // WORKBOOKPARSER_H

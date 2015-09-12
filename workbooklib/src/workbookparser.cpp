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
#include "workbookparser.h"
#include "qstd.h"
#include "pluginstore.h"
#include "workbookparser_p.h"


WorkbookParser::WorkbookParser(PluginStore *store, QObject *parent) :
    QObject(parent),
    d_ptr(new WorkbookParserPrivate(store, this)) {
}

ParserErrors WorkbookParser::error() {
    return d_ptr->error();
}

void WorkbookParser::clearErrors() {
    d_ptr->clearErrors();
}

QVariant WorkbookParser::parse(Worksheet *sheet, const QString expression) {
    return d_ptr->parse(sheet, expression);
}

void WorkbookParser::setFunctions(QStringList list) {
    d_ptr->setFunctions(list);
}

void WorkbookParser::setOperations(QStringList list) {
    d_ptr->setOperations(list);
}

void WorkbookParser::setConstants(QStringList list) {
    d_ptr->setConstants(list);
}

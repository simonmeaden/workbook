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
#include "workbook.h"
#include "workbook_p.h"
#include "qworksheetview.h"

#include "workbook_global.h"

namespace QWorkbook {

const QString Workbook::SHEET = "Sheet ";
const QString Workbook::SHEETNAME = SHEET + " %1";

Workbook::Workbook(PWorkbookParser parser,
                   QWorkbookView *parent) :
    QObject(parent),
    d_ptr(new WorkbookPrivate(parser, parent, this)) {

}


void Workbook::saveWorkbook(QString filename, WorksheetType type) {
    d_ptr->saveWorkbook(filename, type);
}

QWorksheetView* Workbook::worksheetView(int index) {
    return d_ptr->worksheetView(index);
}

QStringList Workbook::names() {
    return d_ptr->names();
}

QWorksheetView* Workbook::worksheetView(QString name) {
    return d_ptr->worksheetView(name);
}

QWorksheetView* Workbook::currentWorksheetView() {
    return d_ptr->currentWorksheetView();
}

void Workbook::setCurrentWorksheetView(int index) {
    d_ptr->setCurrentWorksheetView(index);
}

void Workbook::setCurrentWorksheetView(QString name) {
    d_ptr->setCurrentWorksheetView(name);
}

int Workbook::indexOf(QWorksheetView* sheet) {
    return d_ptr->indexOf(sheet);
}

int Workbook::size() {
    return d_ptr->size();
}

QWorksheetView* Workbook::addWorksheet() {
    return d_ptr->addWorksheet();
}

void Workbook::moveSheet(int oldIndex, int newIndex) {
    d_ptr->moveSheet(oldIndex, newIndex);
}

QWorksheetView *Workbook::insertNewWorksheet(int index) {
    return d_ptr->insertNewWorksheet(index);
}

QWorksheetView *Workbook::insertWorksheet(int index, QWorksheetView* view) {
    return d_ptr->insertWorksheet(index, view);
}

int Workbook::removeWorksheet(int index) {
    return d_ptr->removeWorksheet(index);
}

int Workbook::removeWorksheet(QString name) {
    return d_ptr->removeWorksheet(name);
}

int Workbook::removeWorksheet(QWorksheetView *sheet) {
    return d_ptr->removeWorksheet(sheet);
}

int Workbook::renameSheet(QString oldname, QString newname) {
    return d_ptr->renameSheet(oldname, newname);
}

}


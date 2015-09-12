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
#include "worksheet.h"
#include "qworksheetview.h"

const QString Workbook::SHEET = "Sheet ";
const QString Workbook::SHEETNAME = SHEET + " %1";

Workbook::Workbook(QObject *parent) :
    QObject(parent),
    d_ptr(new WorkbookPrivate(this)) {

}

Workbook::~Workbook() {

}

void Workbook::saveWorkbook(QString filename) {
    d_ptr->saveWorkbook(filename);
}

void Workbook::saveWorkbook(QString filename, WorksheetType type) {
    d_ptr->saveWorkbook(filename, type);
}

Worksheet* Workbook::worksheet(int index) {
    return d_ptr->worksheet(index);
}

Worksheet* Workbook::worksheet(QString name) {
    return d_ptr->worksheet(name);
}

Worksheet* Workbook::currentWorksheet() {
    return d_ptr->currentWorksheet();
}

void Workbook::setCurrentWorksheet(int index) {
    d_ptr->setCurrentWorksheet(index);
}

void Workbook::setCurrentWorksheet(QString name) {
    d_ptr->setCurrentWorksheet(name);
}

int Workbook::indexOf(Worksheet* sheet) {
    return d_ptr->indexOf(sheet);
}

int Workbook::count() {
    return d_ptr->count();
}

Worksheet* Workbook::addWorksheet() {
    return d_ptr->addWorksheet();
}

Worksheet *Workbook::insertWorksheet(int index) {
    return d_ptr->insertWorksheet(index);
}

int Workbook::removeWorksheet(int index) {
    return d_ptr->removeWorksheet(index);
}

int Workbook::removeWorksheet(QString name) {
    return d_ptr->removeWorksheet(name);
}

int Workbook::removeWorksheet(Worksheet *sheet) {
    return d_ptr->removeWorksheet(sheet);
}

int Workbook::renameSheet(QString oldname, QString newname) {
    return d_ptr->renameSheet(oldname, newname);
}

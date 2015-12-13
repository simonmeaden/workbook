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

#include "pluginstore.h"
#include "workbookparser_p.h"
#include "qworkbookview.h"
#include "qworksheetview.h"

#include "workbook_global.h"

namespace QWorkbook {

/*!

    \internal
    \class WorkbookParser

    \brief The internal object that parses Cell formulae and returns a result.

    This class is entirely internal to QWorbookView and QWorksheetView and should never be
    utilsed by a user, only by a developer.

*/

/*!
    \internal

    \brief Constructs an empty WorkbookParser object.

    This is only included because I needed to use qRegisterMetaType() on WorkbookParser. You
    should never use this in real life, use either WorkbookParser(QWorkbookView) or
    QWorkbookParser(QWorksheetView).

*/
WorkbookParser::WorkbookParser() {

}

/*!
    \brief Constructs a WorkbookParser object with a QWorkbook parent.
*/
WorkbookParser::WorkbookParser(QWorkbookView *parent) :
    QThread(parent),
    d_ptr(new WorkbookParserPrivate(parent, this)) {

}

/*!
    \brief Constructs a WorkbookParser object with a QWorksheet parent.
*/
WorkbookParser::WorkbookParser(QWorksheetView *parent) :
    QThread(parent),
    d_ptr(new WorkbookParserPrivate(parent, this)) {

}

WorkbookParser::~WorkbookParser() {

    mMutex.lock();
    bAbort = true;
    mMutex.unlock();

    wait();
}


void WorkbookParser::run() {

    forever {
        mMutex.lock();
        bool abort = bAbort;
        if (abort) {
            return;
        }
        bool changed = bDataHasChanged;
        mMutex.unlock();

        if (changed) {
            // TODO actually do stuff.
            d_ptr->parse();

            mMutex.lock();
            bDataHasChanged = false;
            mMutex.unlock();

        }

    }
}

void WorkbookParser::stopProcess() {

    mMutex.lock();
    bAbort = true;
    mMutex.unlock();

}


ParserErrors WorkbookParser::error() {
    return d_ptr->error();
}

//void WorkbookParser::clearErrors() {
//    d_ptr->clearErrors();
//}

void WorkbookParser::dataHasChanged(const QModelIndex &/*topLeft*/,
                                    const QModelIndex &/*bottomRight*/,
                                    const QVector<int> &/*roles*/) {
    mMutex.lock();
    bDataHasChanged = true;
    // TODO might not actually use these as changes to cells are normally made one cell at a time.
    //    d_ptr->dataHasChanged(topLeft, bottomRight, changedRoles);
    // TODO unless loading file.
    mMutex.unlock();


}

//QVariant WorkbookParser::parse(const QString expression) {
//    return d_ptr->parse(expression);
//}

///*!
//    \internal
//    \brief Splits the string expression into separate tokens strings.

//    This is a protected method and is not normally
//    intended for use by external classes only
//    whilst testing the tokeniser.
//*/
//QStringList WorkbookParser::splitExpression(const QString expression) {
//    return d_ptr->splitExpression(expression);
//}

///*!
//    \internal
//    \brief Takes the QStringList from splitExpression(QString) and converts it to a Token list.

//    This is a protected method and is not normally
//    intended for use by external classes only
//    whilst testing the tokeniser.
//*/
//void WorkbookParser::tokenise(QStringList items) {
//    d_ptr->tokenise(items);
//}

}


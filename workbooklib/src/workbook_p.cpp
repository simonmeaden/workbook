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

#include <QDateTime>

#include "workbook_p.h"
#include "workbook.h"
#include "qworkbookview.h"
#include "toolbar/qworkbooktoolbar.h"
#include "qworkbookview.h"
#include "qworksheetview.h"
#include "workbookparser.h"
#include "workbook_global.h"

#include "xlsxdocument.h"
#include "xlsxworkbook.h"
#include "xlsxworksheet.h"


namespace QWorkbook {

WorkbookPrivate::WorkbookPrivate(PWorkbookParser parser,
                                 QWorkbookView *bookView,
                                 Workbook *parent) :
    pBookView(bookView),
    pCurrentWorksheet(NULL),
    pParser(parser),
    q_ptr(parent) {

}


void WorkbookPrivate::setToolbar(QWorkbookToolBar *toolbar) {
    pToolbar = toolbar;

}

void WorkbookPrivate::saveWorkbook(QString filename, WorksheetType type) {
    switch (type) {
    case ODS:
        break;
    case XLS:
        break;
    case XLSX:
        saveXlsx(filename);
        break;
    case CSV:
        saveCSV(filename);
        break;
    default:
        break;
    }
}

void WorkbookPrivate::saveOds(QString /*filename*/) {

}

void WorkbookPrivate::saveDif(QString /*filename*/) {

}

void WorkbookPrivate::saveCSV(QString /*filename*/) {

}

void WorkbookPrivate::saveXls(QString /*filename*/) {

}

void WorkbookPrivate::saveXlsx(QString filename) {

    QXlsx::Document document(filename, q_ptr);


    document.setDocumentProperty("title", q_ptr->property("title").toString());
    document.setDocumentProperty("subject", q_ptr->property("subject").toString());
    document.setDocumentProperty("creator", q_ptr->property("creator").toString());
    document.setDocumentProperty("company", q_ptr->property("company").toString());
    document.setDocumentProperty("category", q_ptr->property("category").toString());
    document.setDocumentProperty("keywords", q_ptr->property("keywords").toString());
    document.setDocumentProperty("description", q_ptr->property("description").toString());
    document.setDocumentProperty("comments", q_ptr->property("comments").toString());
    document.setDocumentProperty("created", q_ptr->property("created").toDateTime().toString("dd MMMM yyyy, hh:mm"));


    QListIterator<QWorksheetView*> it(mSheets);
    while (it.hasNext()) {
        QWorksheetView *source = it.next();
        QString name = source->sheetName();

        document.addSheet(name);
        source->writeWorksheet(document.currentWorksheet());

    }

    document.save();

}

void WorkbookPrivate::loadWorkbook(QString filename) {
    if (!filename.isEmpty()) {
        WorksheetType type;

        if (filename.toLower().endsWith(".ods"))
            type = ODS;
        else if (filename.endsWith(".xls"))
            type = XLS;
        else if (filename.endsWith(".xlsx"))
            type = XLSX;
        else
            type = NOT_A_SPREADSHEET;

        switch (type) {
        case ODS:
            // TODO save ODS
            break;
        case XLS:
            // TODO save XLS
            break;
        case XLSX: {
            QXlsx::Document *document = new QXlsx::Document(filename, q_ptr);

            QXlsx::Workbook *book = document->workbook();
            int count = book->sheetCount();

            for (int i = 0; i < count; i++) {
                // TODO read xlsx file

//                sheet->readXlsx(book, i);
            }

            break;
        }
        default:
            // TODO not standard file
            break;
        }
    }
}

QStringList WorkbookPrivate::names() {
    return mNames.keys();
}

int WorkbookPrivate::indexOf(QWorksheetView *sheet) {
    return mSheets.indexOf(sheet);
}

QWorksheetView *WorkbookPrivate::worksheetView(int index) {
    return mSheets.at(index);
}

QWorksheetView *WorkbookPrivate::worksheetView(QString name) {
    return mNames.value(name);
}

QWorksheetView *WorkbookPrivate::currentWorksheetView() {
    return pCurrentWorksheet;
}

void WorkbookPrivate::setCurrentWorksheetView(int index) {
    if (pCurrentWorksheet) {
        q_ptr->disconnect(pCurrentWorksheet, SIGNAL(cellContentsChanged(QString)),
                          pBookView, SIGNAL(cellContentsChanged(QString)));
        pCurrentWorksheet->disconnectSignalsFromParser();
    }

    pCurrentWorksheet = mSheets.at(index);
    pCurrentWorksheet->connectSignalsToParser();
    q_ptr->connect(pCurrentWorksheet, SIGNAL(cellContentsChanged(QString)),
                   pBookView, SIGNAL(cellContentsChanged(QString)));
//    pCurrentWorksheet->triggerCurrentSelection();
}

void WorkbookPrivate::setCurrentWorksheetView(QString name) {
    if (pCurrentWorksheet) {
        q_ptr->disconnect(pCurrentWorksheet, SIGNAL(cellContentsChanged(QString)),
                          pBookView, SIGNAL(cellContentsChanged(QString)));
    }

    pCurrentWorksheet = mNames.value(name);
    q_ptr->connect(pCurrentWorksheet, SIGNAL(cellContentsChanged(QString)),
                   pBookView, SIGNAL(cellContentsChanged(QString)));
//    pCurrentWorksheet->triggerCurrentSelection();
}

QWorksheetView *WorkbookPrivate::addWorksheet() {

    QWorkbookView *view = qobject_cast<QWorkbookView*>(q_ptr->parent());


    QWorksheetView *sheet = new QWorksheetView(pParser, view);

    QString name = Workbook::SHEETNAME;
    name = name.arg(mSheets.size());
    sheet->setSheetName(name);

    mSheets.append(sheet);
    mNames.insert(name, sheet);
    mRealnames.insert(sheet, false);
    setCurrentWorksheetView(mSheets.indexOf(sheet));

    Q_Q(Workbook);
    emit q->sheetAdded(mSheets.indexOf(sheet));

    return sheet;
}

QWorksheetView* WorkbookPrivate::insertWorksheet(int index, QWorksheetView *sheet) {
    int i = index;
    if (i >= mSheets.size())
        return addWorksheet();
    else if (i < 0)
        i = 0;

    mSheets.insert(i, sheet);
    mNames.insert(sheet->sheetName(), sheet);
    mRealnames.insert(sheet, true);
    setCurrentWorksheetView(i);

    renameSheets(i);

    Q_Q(Workbook);
    emit q->sheetAdded(mSheets.indexOf(sheet));

    return sheet;
}

QWorksheetView *WorkbookPrivate::insertNewWorksheet(int index) {
    int i = index;
    if (i >= mSheets.size())
        return addWorksheet();
    else if (i < 0)
        i = 0;

    QWorksheetView *sheet = new QWorksheetView(pParser, qobject_cast<QWorkbookView*>(q_ptr->parent()));

    QString name = Workbook::SHEETNAME;
    name = name.arg(mSheets.size());
    sheet->setSheetName(name);

    mSheets.insert(i, sheet);
    mNames.insert(name, sheet);
    mRealnames.insert(sheet, false);
    setCurrentWorksheetView(i);

    renameSheets(i);

    Q_Q(Workbook);
    emit q->sheetAdded(mSheets.indexOf(sheet));

    return sheet;
}

int WorkbookPrivate::renameSheet(QString oldname, QString newname) {
    QString o = oldname.trimmed();
    QString n = newname.trimmed();
    if (o == n || n.isEmpty()) return -1;

    QWorksheetView *sheet = mNames.value(o);
    if (!sheet) return -1;

    sheet->setSheetName(n);
    mNames.remove(o);
    mNames.insert(n, sheet);

    if (isRealName(n))
        mRealnames.insert(sheet, true);
    else
        mRealnames.insert(sheet, false);

    return mSheets.indexOf(sheet);
}

bool WorkbookPrivate::isRealName(QString str) {
    if (str.startsWith(Workbook::SHEET) &&
            areNumbers(str.mid(Workbook::SHEET.length())))
        return true;
    return false;
}

bool WorkbookPrivate::areNumbers(QString str) {
    if (str.length() == 0) return false;

    for (int i = 0; i < str.length(); i++) {
        if (!str.at(i).isNumber())
            return false;
    }

    return true;
}

void WorkbookPrivate::renameSheets(int index) {
    QWorksheetView *sheet;
    bool isReal;

    for (int i = index + 1; i < mSheets.size(); i++) {
        sheet = mSheets.at(i);
        isReal = mRealnames.value(sheet);
        if (!isReal) {
            QString name = Workbook::SHEETNAME;
            name = name.arg(i);
            sheet->setSheetName(name);
        }
    }

    Q_Q(Workbook);
    emit q->namesChanged(index);
}

int WorkbookPrivate::removeWorksheet(int index) {
    if (index < 0 || index < mSheets.size()) return -1;

    QWorksheetView * sheet = mSheets.at(index);
    if (!sheet) return -1;

    QString name = sheet->sheetName();
    if (sheet == pCurrentWorksheet) {
        if (index > 0)
            setCurrentWorksheetView(index - 1);
        else if (index == 0 && size() > 1)
            setCurrentWorksheetView(index + 1);
        else
            pCurrentWorksheet = NULL;
    }

    mSheets.removeAt(index);
    mNames.remove(name);
    mRealnames.remove(sheet);

    renameSheets(index);


    Q_Q(Workbook);
    emit q->sheetRemoved(index);

    return index;
}

int WorkbookPrivate::removeWorksheet(QString name) {
    QWorksheetView *sheet = mNames.value(name);
    if (!sheet) return -1;

    int index = mSheets.indexOf(sheet);

    if (sheet == pCurrentWorksheet) {
        if (index > 0)
            setCurrentWorksheetView(index - 1);
        else if (index == 0 && size() > 1)
            setCurrentWorksheetView(index + 1);
        else
            pCurrentWorksheet = NULL;
    }

    mSheets.removeAt(index);
    mNames.remove(name);
    mRealnames.remove(sheet);

    renameSheets(index);

    Q_Q(Workbook);
    emit q->sheetRemoved(index);

    return index;
}

int WorkbookPrivate::removeWorksheet(QWorksheetView *sheet) {
    if (!sheet) return -1;

    QString name = sheet->sheetName();
    int index = mSheets.indexOf(sheet);

    if (sheet == pCurrentWorksheet) {
        if (index > 0)
            setCurrentWorksheetView(index - 1);
        else if (index == 0 && size() > 1)
            setCurrentWorksheetView(index + 1);
        else
            pCurrentWorksheet = NULL;
    }

    mSheets.removeAt(index);
    mNames.remove(name);
    mRealnames.remove(sheet);

    renameSheets(index);

    Q_Q(Workbook);
    emit q->sheetRemoved(index);

    return index;
}

void WorkbookPrivate::moveSheet(int oldIndex, int newIndex) {

    mSheets.move(oldIndex, newIndex);

}

}


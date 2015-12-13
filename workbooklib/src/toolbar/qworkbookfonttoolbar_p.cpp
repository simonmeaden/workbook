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
#include "qworkbookfonttoolbar_p.h"
#include "qworkbookfonttoolbar.h"
#include "types.h"
#include "qworkbookview.h"
#include "qworksheetview.h"



#include "workbook_global.h"

namespace QWorkbook {

QWorkbookFontToolBarPrivate::QWorkbookFontToolBarPrivate(QWorkbookFontToolBar *q) :
    q_ptr(q),
    pView(NULL) {

}

void QWorkbookFontToolBarPrivate::setView(QObject *view) {

    Q_Q(QWorkbookFontToolBar);
    QWorkbookView *wb;
    QWorksheetView *ws;

    // remove old connections
    if (pView) {
        wb = qobject_cast<QWorkbookView*>(pView);
        ws = qobject_cast<QWorksheetView*>(pView);

        if (wb) {
            q->disconnect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(fontChanged(QFont)),
                       wb, SLOT(setSelectionFont(QFont)));
            q->disconnect(q, SIGNAL(fontSizeChanged(int)),
                       wb, SLOT(setSelectionFontSize(int)));
        } else if (ws) {
            q->disconnect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(fontChanged(QFont)),
                       ws, SLOT(setSelectionFont(QFont)));
            q->disconnect(q, SIGNAL(fontSizeChanged(int)),
                       ws, SLOT(setSelectionFontSize(int)));
        }
    }

    // make new ones.
    wb = qobject_cast<QWorkbookView*>(view);
    ws = qobject_cast<QWorksheetView*>(view);
    if (wb) {
        q->connect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(fontChanged(QFont)),
                   wb, SLOT(setSelectionFont(QFont)));
        q->connect(q, SIGNAL(fontSizeChanged(int)),
                   wb, SLOT(setSelectionFontSize(int)));
    } else if (ws) {
        q->connect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(fontChanged(QFont)),
                   ws, SLOT(setSelectionFont(QFont)));
        q->connect(q, SIGNAL(fontSizeChanged(int)),
                   ws, SLOT(setSelectionFontSize(int)));
    }

    pView = view;

}

void QWorkbookFontToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setFont(status->bAllSameFont, status->mFont, status->mFontSize);
}

void QWorkbookFontToolBarPrivate::init() {

    QFont font = QFont("Times", 10, QFont::Normal);

    pFontCombo = new QFontComboBox(q_ptr);
    pFontCombo->setToolTip(q_ptr->tr("Font Name"));
    pFontCombo->setFont(font);
    q_ptr->addWidget(pFontCombo);
    q_ptr->connect(pFontCombo, SIGNAL(currentFontChanged(QFont)), q_ptr, SLOT(fontHasChanged(QFont)));

    pSizeCombo = new QComboBox(q_ptr);
    pSizeCombo->setValidator(new QIntValidator(1, 1000, q_ptr));
    pSizeCombo->setToolTip(q_ptr->tr("Font Size"));
    q_ptr->addWidget(pSizeCombo);
    q_ptr->connect(pSizeCombo, SIGNAL(currentTextChanged(QString)), q_ptr, SLOT(sizeHasChanged(QString)));

    font = pFontCombo->currentFont();
    setFontSizes(font);

}

void QWorkbookFontToolBarPrivate::fontHasChanged(QFont font) {

    int size = pSizeCombo->currentText().toInt();

    setFontSizes(font);

    bool isItalic = mFontDatabase.italic(font.family(), font.styleName());

    emit q_ptr->italic(isItalic);

    bool isBold = mFontDatabase.bold(font.family(), font.styleName()) ;
    emit q_ptr->bold(isBold);

    pSizeCombo->setCurrentText(QString::number(size));

    emit q_ptr->fontChanged(font);
    emit q_ptr->fontSizeChanged(size);

}

void QWorkbookFontToolBarPrivate::sizeHasChanged(QString size) {

    emit q_ptr->fontSizeChanged(size.toInt());

}

void QWorkbookFontToolBarPrivate::setFont(QFont font) {
    pFontCombo->setCurrentFont(font);
}

void QWorkbookFontToolBarPrivate::setFont(bool selected, QFont font, int size) {
    if (selected) {
        pFontCombo->setCurrentFont(font);
        pSizeCombo->setCurrentText(QString::number(size));
    }
}

void QWorkbookFontToolBarPrivate::setFontSizes(QFont font) {
    QList<int> sizes = mFontDatabase.pointSizes(font.family(), font.styleName());
    pSizeCombo->clear();
    QListIterator<int> it(sizes);
    while (it.hasNext())
        pSizeCombo->addItem(QString::number(it.next()));
}

}


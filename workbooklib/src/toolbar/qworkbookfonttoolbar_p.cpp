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
#include "qstd.h"


QWorkbookFontToolBarPrivate::QWorkbookFontToolBarPrivate(QWorkbookFontToolBar *q) :
    q_ptr(q) {

}

void QWorkbookFontToolBarPrivate::setWorkbookView(QWorkbookView *view) {

    // view to bar
    q_ptr->connect(view, SIGNAL(selectionChanged(FormatStatus*)),
               q_ptr, SLOT(selectionChanged(FormatStatus*)));

    // bar to view (sets format in view)
    q_ptr->connect(q_ptr, SIGNAL(fontChanged(QFont)),
               view, SLOT(setSelectionFont(QFont)));
    q_ptr->connect(q_ptr, SIGNAL(fontSizeChanged(int)),
               view, SLOT(setSelectionFontSize(int)));

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

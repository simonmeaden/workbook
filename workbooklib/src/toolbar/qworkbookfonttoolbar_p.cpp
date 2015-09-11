/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#include "qworkbookfonttoolbar_p.h"
#include "qworkbookfonttoolbar.h"
#include "types.h"
#include "qworkbookview.h"
#include "qstd.h"


QWorkbookFontToolBarPrivate::QWorkbookFontToolBarPrivate(QWorkbookFontToolBar *q) :
    q_ptr(q) {

    cout << "QWorkbookFontToolBarPrivate" << endl << flush;

    init();

}

void QWorkbookFontToolBarPrivate::setWorkbookView(QWorkbookView *view) {

    Q_Q(QWorkbookFontToolBar);
    // view to bar
    q->connect(view, SIGNAL(selectionChanged(FormatStatus*)),
               q, SLOT(selectionChanged(FormatStatus*)));

    // bar to view (sets format in view)
    q->connect(q, SIGNAL(fontChanged(QFont)),
               view, SLOT(setSelectionFont(QFont)));
    q->connect(q, SIGNAL(fontSizeChanged(int)),
               view, SLOT(setSelectionFontSize(int)));

}

void QWorkbookFontToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setFont(status->bAllSameFont, status->mFont, status->mFontSize);
}

void QWorkbookFontToolBarPrivate::init() {

    QFont font = QFont("Times", 10, QFont::Normal);

    Q_Q(QWorkbookFontToolBar);
    pFontCombo = new QFontComboBox(q);
    pFontCombo->setToolTip(q->tr("Font Name"));
    pFontCombo->setFont(font);
    q->addWidget(pFontCombo);
    q->connect(pFontCombo, SIGNAL(currentFontChanged(QFont)), q, SLOT(fontHasChanged(QFont)));

    pSizeCombo = new QComboBox(q);
    pSizeCombo->setValidator(new QIntValidator(1, 1000, q));
    pSizeCombo->setToolTip(q->tr("Font Size"));
    q->addWidget(pSizeCombo);
    q->connect(pSizeCombo, SIGNAL(currentTextChanged(QString)), q, SLOT(sizeHasChanged(QString)));

    font = pFontCombo->currentFont();
    setFontSizes(font);

}

void QWorkbookFontToolBarPrivate::fontHasChanged(QFont font) {

    int size = pSizeCombo->currentText().toInt();

    setFontSizes(font);

    bool isItalic = mFontDatabase.italic(font.family(), font.styleName());
    Q_Q(QWorkbookFontToolBar);
    emit q->italic(isItalic);

    bool isBold = mFontDatabase.bold(font.family(), font.styleName()) ;
    emit q->bold(isBold);

    pSizeCombo->setCurrentText(QString::number(size));

    emit q->fontChanged(font);
    emit q->fontSizeChanged(size);

}

void QWorkbookFontToolBarPrivate::sizeHasChanged(QString size) {

    Q_Q(QWorkbookFontToolBar);
    emit q->fontSizeChanged(size.toInt());

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

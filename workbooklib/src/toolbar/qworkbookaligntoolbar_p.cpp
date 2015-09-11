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
#include "qworkbookaligntoolbar_p.h"
#include "qworkbookaligntoolbar.h"
#include "qworkbookview.h"
#include "types.h"

QWorkbookAlignToolBarPrivate::QWorkbookAlignToolBarPrivate(QWorkbookAlignToolBar *q) :
    q_ptr(q) {

    init();

}

void QWorkbookAlignToolBarPrivate::init()  {

    pLeftBtn = new QPushButton(QIcon("://justify-left"), "", q_ptr);
    pLeftBtn->setToolTip("Align Left");
    pLeftBtn->setStyleSheet(buttonStyle);
    pLeftBtn->setContentsMargins(0, 0, 0, 0);
    pLeftBtn->setCheckable(true);
    q_ptr->addWidget(pLeftBtn);
    q_ptr->connect(pLeftBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pHCentreBtn = new QPushButton(q_ptr);
    pHCentreBtn->setToolTip("Align Horizontal Centre");
    pHCentreBtn->setStyleSheet(buttonStyle);
    pHCentreBtn->setContentsMargins(0, 0, 0, 0);
    pHCentreBtn->setCheckable(true);
    pHCentreBtn->setIcon(QIcon("://justify-centre"));
    q_ptr->addWidget(pHCentreBtn);
    q_ptr->connect(pHCentreBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pRightBtn = new QPushButton(q_ptr);
    pRightBtn->setToolTip("Align Right");
    pRightBtn->setStyleSheet(buttonStyle);
    pRightBtn->setContentsMargins(0, 0, 0, 0);
    pRightBtn->setCheckable(true);
    pRightBtn->setIcon(QIcon("://justify-right"));
    q_ptr->addWidget(pRightBtn);
    q_ptr->connect(pRightBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pButtonGroup = new QButtonGroup(q_ptr);
    pButtonGroup->addButton(pLeftBtn);
    pButtonGroup->addButton(pHCentreBtn);
    pButtonGroup->addButton(pRightBtn);
    pLeftBtn->setChecked(true);

}

void QWorkbookAlignToolBarPrivate::setWorkbookView(QWorkbookView *view) {

    Q_Q(QWorkbookAlignToolBar);
    // view to bar
    q->connect(view, SIGNAL(selectionChanged(FormatStatus*)),
               q, SLOT(selectionChanged(FormatStatus*)));

    // bar to view (sets format in view)
    q->connect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
               view, SLOT(setSelectionAlignment(Qt::Alignment)));

}

void QWorkbookAlignToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setAlign(status->bAllSameAlignment, status->mAlignment);
}

void QWorkbookAlignToolBarPrivate::alignHasClicked() {
    Qt::Alignment valign = Qt::AlignVCenter;
    Qt::Alignment halign = Qt::AlignLeft;
    Qt::Alignment align;

    if (pLeftBtn->isChecked())
        halign = Qt::AlignLeft;
    else if (pHCentreBtn->isChecked())
        halign = Qt::AlignHCenter;
    else if (pRightBtn->isChecked())
        halign = Qt::AlignRight;

    align = halign | valign;

    Q_Q(QWorkbookAlignToolBar);
    emit q->alignmentChanged(align);
}

void QWorkbookAlignToolBarPrivate::setAlign(bool set, Qt::Alignment alignment) {
    if (set) {
        if (alignment.testFlag(Qt::AlignLeft))
            pLeftBtn->setChecked(true);
        else
            pLeftBtn->setChecked(false);

        if (alignment.testFlag(Qt::AlignCenter))
            pHCentreBtn->setChecked(true);
        else
            pHCentreBtn->setChecked(false);

        if (alignment.testFlag(Qt::AlignRight))
            pRightBtn->setChecked(true);
        else
            pRightBtn->setChecked(false);
    }
}

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
#include "qworkbookaligntoolbar.h"
#include "qworkbookaligntoolbar_p.h"
#include "qworkbookview.h"

/*!
 * \class QWorkbookAlignToolBar
 * \brief A OpenOffice style toolbar for the QWorkbook class.
 * \ingroup QWorkbookView
 *
 * The QWorkbookAlignToolBar class provides a align toolbar similar in form to OpenOffice
 * Calc, and supplying align left, centre and right buttons.
 * .
 * This is not normally intended to be used by itself, but is also included as part
 * of the QWorkbookToolBar class.
 *
 * If used as a standalone toolbar you will need to manually call the
 * QWorkbookAlignToolBar::setWorkbookView(QWorkbookView *) method to link the toolbar to
 * the QWorkbookView object.
 */
QWorkbookAlignToolBar::QWorkbookAlignToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookAlignToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

QWorkbookAlignToolBar::QWorkbookAlignToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookAlignToolBarPrivate(this)) {

    Q_D(QWorkbookAlignToolBar);
    d->init();

}

QWorkbookAlignToolBar::~QWorkbookAlignToolBar() {
}

/*!
 * \brief QWorkbookToolBar::setWorkbookView(QWorkbookView *view)
 *
 * \param view
 */
void QWorkbookAlignToolBar::setWorkbookView(QWorkbookView *view) {

    Q_D(QWorkbookAlignToolBar);
    d->setWorkbookView(view);

}

void QWorkbookAlignToolBar::selectionChanged(FormatStatus* status) {

    Q_D(QWorkbookAlignToolBar);
    d->selectionChanged(status);

}

void QWorkbookAlignToolBar::alignHasClicked() {

    Q_D(QWorkbookAlignToolBar);
    d->alignHasClicked();

}

void QWorkbookAlignToolBar::setAlign(bool set, Qt::Alignment alignment) {
    Q_D(QWorkbookAlignToolBar);
    d->setAlign(set, alignment);
}

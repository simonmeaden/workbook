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
#include "qworksheetview.h"

#include "workbook_global.h"

namespace QWorkbook {

/*!
 * \class QWorkbookAlignToolBar
 *
 * \brief A OpenOffice style horizontal align toolbar for the QWorkbook class.
 *
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

/*!
 * \fn QWorkbookAlignToolBar::alignmentChanged(Qt::Alignment);
 *
 * This signal is emitted when one of the align buttons has been clicked and the
 * horizontal alignment has been changed.
 */



/*!
 * /brief Constructs a QWorkbookAlignToolBar with the given parent.
 */
QWorkbookAlignToolBar::QWorkbookAlignToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookAlignToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

/*!
 * /brief Constructs a QWorkbookAlignToolBar with the given parent.
 *
 * The given window title identifies the toolbar and is shown
 * in the context menu provided by QMainWindow.
 */
QWorkbookAlignToolBar::QWorkbookAlignToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookAlignToolBarPrivate(this)) {

    Q_D(QWorkbookAlignToolBar);
    d->init();

}

/*!
 * \brief Sets the QWorkbookView that is attached to this toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown.
 */
void QWorkbookAlignToolBar::setWorkbookView(QWorkbookView *view) {

    Q_D(QWorkbookAlignToolBar);
    d->setView(view);

}

/*!
 * \brief Sets the QWorkbookView that is attached to this toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown.
 */
void QWorkbookAlignToolBar::setWorksheetView(QWorksheetView *view) {

    Q_D(QWorkbookAlignToolBar);
    d->setView(view);

}

/*!
 * \internal
 *
 * \brief Called when the current worksheet's selection has changed.
 *
 * Protected method called by friend class QWorkbookView when it's selected
 * cells are changed. The FormatStatus supplied holds information from which
 * enabled/disabled button states is deduced.
 */
void QWorkbookAlignToolBar::selectionChanged(FormatStatus* status) {

    Q_D(QWorkbookAlignToolBar);
    d->selectionChanged(status);

}

/*!
 * \internal
 *
 * \brief Called when the current worksheet's selection has changed.
 *
 * Internal method called when one of the align buttons has been clicked.
 */
void QWorkbookAlignToolBar::alignHasClicked() {

    Q_D(QWorkbookAlignToolBar);
    d->alignHasClicked();

}

/*!
 * \internal
 *
 * \brief Sets the various align button states.
 *
 * Internal method called to set the button condition.
 */
void QWorkbookAlignToolBar::setAlign(bool set, Qt::Alignment alignment) {
    Q_D(QWorkbookAlignToolBar);
    d->setAlign(set, alignment);
}

/*!
 * \class QWorkbookVerticalAlignToolBar
 *
 * \brief A OpenOffice style horizontal align toolbar for the QWorkbook class.
 *
 * \ingroup QWorkbookView
 *
 * The QWorkbookVerticalAlignToolBar class provides a vertical align toolbar similar in form to OpenOffice
 * Calc, and supplying align top, middle and bottom buttons.
 * .
 * This is not normally intended to be used by itself, but is also included as part
 * of the QWorkbookToolBar class.
 *
 * If used as a standalone toolbar you will need to manually call the
 * QWorkbookVerticalAlignToolBar::setWorkbookView(QWorkbookView *) method to link the toolbar to
 * the QWorkbookView object.
 */

/*!
 * \fn QWorkbookVerticalAlignToolBar::alignmentChanged(Qt::Alignment);
 *
 * This signal is emitted when one of the align buttons has been clicked and the
 * horizontal alignment has been changed.
 */



/*!
 * /brief Constructs a QWorkbookVerticalAlignToolBar with the given parent.
 */
QWorkbookVerticalAlignToolBar::QWorkbookVerticalAlignToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookVerticalAlignToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

/*!
 * /brief Constructs a QWorkbookVerticalAlignToolBar with the given parent.
 *
 * The given window title identifies the toolbar and is shown
 * in the context menu provided by QMainWindow.
 */
QWorkbookVerticalAlignToolBar::QWorkbookVerticalAlignToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookVerticalAlignToolBarPrivate(this)) {

    Q_D(QWorkbookVerticalAlignToolBar);
    d->init();

}

/*!
 * \brief Sets the QWorkbookView that is attached to this toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown.
 */
void QWorkbookVerticalAlignToolBar::setWorkbookView(QWorkbookView *view) {

    Q_D(QWorkbookVerticalAlignToolBar);
    d->setView(view);

}

/*!
 * \brief Sets the QWorksheetView that is attached to this toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown.
 */
void QWorkbookVerticalAlignToolBar::setWorksheetView(QWorksheetView *view) {

    Q_D(QWorkbookVerticalAlignToolBar);
    d->setView(view);

}

/*!
 * \internal
 *
 * \brief Called when the current worksheet's selection has changed.
 *
 * Protected method called by friend class QWorkbookView when it's selected
 * cells are changed. The FormatStatus supplied holds information from which
 * enabled/disabled button states is deduced.
 */
void QWorkbookVerticalAlignToolBar::selectionChanged(FormatStatus* status) {

    Q_D(QWorkbookVerticalAlignToolBar);
    d->selectionChanged(status);

}

/*!
 * \internal
 *
 * \brief Called when the current worksheet's selection has changed.
 *
 * Internal method called when one of the align buttons has been clicked.
 */
void QWorkbookVerticalAlignToolBar::alignHasClicked() {

    Q_D(QWorkbookVerticalAlignToolBar);
    d->alignHasClicked();

}

/*!
 * \internal
 *
 * \brief Sets the various align button states.
 *
 * Internal method called to set the button condition.
 */
void QWorkbookVerticalAlignToolBar::setAlign(bool set, Qt::Alignment alignment) {
    Q_D(QWorkbookVerticalAlignToolBar);
    d->setAlign(set, alignment);
}

}


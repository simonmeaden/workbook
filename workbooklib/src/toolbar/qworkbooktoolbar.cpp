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
#include "qworkbooktoolbar.h"
#include "qworkbookaligntoolbar.h"
#include "qworkbookfonteffectstoolbar.h"
#include "qworkbookfonttoolbar.h"
#include "qworkbookindenttoolbar.h"
#include "qworkbookmergetoolbar.h"
#include "qworkbooktoolbar_p.h"
#include "qworkbookview.h"
#include "qworksheetview.h"


#include "workbook_global.h"

namespace QWorkbook {

/*!
 * \class QWorkbookToolBar
 *
 * \brief A OpenOffice style toolbar for the QWorkbook class.
 *
 * \ingroup QWorkbookView
 *
 * The QWorkbookToolBar class provides a movable panel that contains a set of controls,
 * similar in form to OpenOffice Calc. This is bascically a wrapper toolbar for the
 * other toolbars.
 *
 * There are two ways to instanciate a QWorkbookToolBar object. Either manually using
 * \code
 *  QWorkbookView *view = new QWorkbookView(this);
 *  addWidget(view);
 *
 *  ...
 *
 *  QWorkbookToolBar *toolbar = new QWorkbookToolBar("maintoolbar", this);
 *  toolbar.setWorkbookView(view);
 * \endcode
 *
 * or by utilising the QWorkbookView::toolBar() method, which combines the actions of
 * both of these methods in one action.
 *
 * \code
 *  QWorkbookView *view = new QWorkbookView(this);
 *
 *  ...
 *
 *  QWorkbookToolBar *toolbar = view->toolbar();
 * \endcode

 */

/*!
 * \brief Constructs a QWorkbookToolBar with the given parent.
 */
QWorkbookToolBar::QWorkbookToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookToolBarPrivate(this) ) {

    d_ptr->init();

}

/*!
 * /brief Constructs a QWorkbookToolBar with the given parent.
 *
 * The given window title identifies the toolbar and is shown
 * in the context menu provided by QMainWindow.
 */
QWorkbookToolBar::QWorkbookToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookToolBarPrivate(this) ) {

    Q_D(QWorkbookToolBar);
    d->init();

}

/*!
 * \brief Sets the QWorkbookView that is attached to this toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown. You can either set the toolbar to
 * link to a QWorkbookView OR a QWorksheetView, but not both.
 *
 * \sa QWorkbookToolBar::setWorksheetView(QWorksheetView*)
 */
void QWorkbookToolBar::setWorkbookView(QWorkbookView *view) {
    d_ptr->setView(view);
}

/*!
 * \brief Sets the QWorksheetView that is attached to this toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown. You can either set the toolbar to
 * link to a QWorkbookView OR a QWorksheetView, but not both.
 *
 * \sa QWorkbookToolBar::setWorkbookView(QWorkbookView*)
 */
void QWorkbookToolBar::setWorksheetView(QWorksheetView *view) {
    d_ptr->setView(view);
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
void QWorkbookToolBar::selectionChanged(FormatStatus* status) {
    d_ptr->selectionChanged(status);
}

void QWorkbookToolBar::showContextMenu(const QPoint &pos) {
    d_ptr->showContextMenu(pos);
}

/*!
 * \brief Shows or hides the QFontToolBar.
 *
 * The supplied boolean value defines whether the toolbar shows, if true,
 * otherwise is hidden.
 */
void QWorkbookToolBar::showFontBar(bool show) {
    d_ptr->showFontBar(show);
}

/*!
 * \brief Shows or hides the QFontEffectsToolBar.
 *
 * The supplied boolean value defines whether the toolbar shows, if true,
 * otherwise is hidden.
 */
void QWorkbookToolBar::showFontEffectsBar(bool show) {
    d_ptr->showFontEffectsBar(show);
}

///*!
// * \brief Shows or hides the QIndentToolBar.
// *
// * The supplied boolean value defines whether the toolbar shows, if true,
// * otherwise is hidden.
// */
//void QWorkbookToolBar::showIndentBar(bool show) {
//    d_ptr->showIndentBar(show);
//}

/*!
 * \brief Shows or hides the QAlignToolBar.
 *
 * The supplied boolean value defines whether the toolbar shows, if true,
 * otherwise is hidden.
 */
void QWorkbookToolBar::showAlignBar(bool show) {
    d_ptr->showAlignBar(show);
}

/*!
 * \brief Shows or hides the QMergeToolBar.
 *
 * The supplied boolean value defines whether the toolbar shows, if true,
 * otherwise is hidden.
 */
void QWorkbookToolBar::showMergeBar(bool show) {
    d_ptr->showMergeBar(show);
}


}


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
#include <qstd.h>

/*!
 * \class QWorkbookToolBar
 * \brief A OpenOffice style toolbar for the QWorkbook class.
 * \ingroup QWorkbookView
 *
 * The QWorkbookToolBar class provides a movable panel that contains a set of controls,
 * similar in form to OpenOffice Calc.
 */

/*!
 * \brief Constructor for the QWorkbookToolBar class.
 *
 * Constructs a QWorkbookToolBar with the given parent.
 */
QWorkbookToolBar::QWorkbookToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookToolBarPrivate(this) ) {

    d_ptr->init();

}

/*!
 * \brief Constructor for the QWorkbookToolBar class.
 *
 * Constructs a QWorkbookToolBar with the given parent.
 *
 * The given window title identifies the toolbar and is shown in the context menu provided by QMainWindow.
 */
QWorkbookToolBar::QWorkbookToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookToolBarPrivate(this) ) {

    Q_D(QWorkbookToolBar);
    d->init();

}

/*!
 * \brief QWorkbookToolBar::~QWorkbookToolBar
 *
 * Destroys the toolbar.
 */
QWorkbookToolBar::~QWorkbookToolBar() {

}

/*!
 * \brief QWorkbookToolBar::setWorkbookView(QWorkbookView *view)
 *
 * \param view
 */
void QWorkbookToolBar::setWorkbookView(QWorkbookView *view) {
    d_ptr->setWorkbookView(view);
}

void QWorkbookToolBar::selectionChanged(FormatStatus* status) {
    d_ptr->selectionChanged(status);
}

void QWorkbookToolBar::showContextMenu(const QPoint &pos) {
    d_ptr->showContextMenu(pos);
}

void QWorkbookToolBar::showFontBar(bool show) {
    d_ptr->showFontBar(show);
}

void QWorkbookToolBar::showFontEffectsBar(bool show) {
    d_ptr->showFontEffectsBar(show);
}

void QWorkbookToolBar::showIndentBar(bool show) {
    d_ptr->showIndentBar(show);
}

void QWorkbookToolBar::showAlignBar(bool show) {
    d_ptr->showAlignBar(show);
}

void QWorkbookToolBar::setBold(bool bold) {
    d_ptr->setBold(bold);
}

void QWorkbookToolBar::setItalic(bool italic) {
    d_ptr->setItalic(italic);
}

void QWorkbookToolBar::setUnderline(bool underline) {
    d_ptr->setUnderline(underline);
}

void QWorkbookToolBar::setFont(QFont font) {
    d_ptr->setFont(font);
}

void QWorkbookToolBar::setAlign(Qt::Alignment alignment) {
    d_ptr->setAlign(alignment);
}

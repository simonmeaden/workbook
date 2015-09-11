/*
 * This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.
 *
 * This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
 * Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
 * under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
 * version 1.1.
 *
 * Qt5 library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License, version 2.1, as published by the
 * Free Software Foundation.
 *
 * Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
 * TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * As an additional permission to the GNU Lesser General Public License version 3.0, the
 * object code form of a “work that uses the Library” may incorporate material from a
 * header file that is part of the Library. You may distribute such object code under
 * terms of your choice, provided that: (i) the header files of the Library have not
 * been modified; and (ii) the incorporated material is limited to numerical parameters,
 * data structure layouts, accessors, macros, inline functions and templates; and (iii)
 * you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.
 *
 * Moreover, you may apply this exception to a modified version of the Library, provided
 * that such modification does not involve copying material from the Library into the
 * modified Library’s header files unless such material is limited to (i) numerical
 * parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
 * templates and inline functions of five lines or less in length.
 *
 * Furthermore, you are not required to apply this additional permission to a modified
 * version of the Library.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * The source code for Qt 5.4.X SDK is available from Nokia here:
 * http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.
 *
 * It is also available on request from Simon Meaden info@smelecomp.co.uk.
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

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
#include "qworkbookindenttoolbar.h"
#include "qworkbookindenttoolbar_p.h"
#include "qworkbooktoolbar.h"
#include "qworkbookview.h"

QWorkbookIndentToolBar::QWorkbookIndentToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookIndentToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

QWorkbookIndentToolBar::QWorkbookIndentToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookIndentToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

void QWorkbookIndentToolBar::indent() {
    Q_D(QWorkbookIndentToolBar);
    d->indent();
}

void QWorkbookIndentToolBar::undent() {
    Q_D(QWorkbookIndentToolBar);
    d->undent();
}

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
#include "qworkbookfonteffectstoolbar.h"
#include "qworkbookfonteffectstoolbar_p.h"
#include "qworkbookview.h"

QWorkbookFontEffectsToolBar::QWorkbookFontEffectsToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookFontEffectsToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

QWorkbookFontEffectsToolBar::QWorkbookFontEffectsToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookFontEffectsToolBarPrivate(this)) {

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

/*!
 * \brief QWorkbookToolBar::setWorkbookView(QWorkbookView *view)
 *
 * \param view
 */
void QWorkbookFontEffectsToolBar::setWorkbookView(QWorkbookView *view) {

    Q_D(QWorkbookFontEffectsToolBar);
    d->setWorkbookView(view);

}

void QWorkbookFontEffectsToolBar::selectionChanged(FormatStatus* status) {

    Q_D(QWorkbookFontEffectsToolBar);
    d->selectionChanged(status);

}

void QWorkbookFontEffectsToolBar::boldHasClicked() {
    Q_D(QWorkbookFontEffectsToolBar);
    d->boldHasClicked();
}

void QWorkbookFontEffectsToolBar::italicHasClicked() {
    Q_D(QWorkbookFontEffectsToolBar);
    d->italicHasClicked();
}

void QWorkbookFontEffectsToolBar::underlineHasClicked() {
    Q_D(QWorkbookFontEffectsToolBar);
    d->underlineHasClicked();
}

void QWorkbookFontEffectsToolBar::setBold(bool value) {
    Q_D(QWorkbookFontEffectsToolBar);
    d->setBold(value);
}

void QWorkbookFontEffectsToolBar::setItalic(bool value) {
    Q_D(QWorkbookFontEffectsToolBar);
    d->setItalic(value);
}

void QWorkbookFontEffectsToolBar::setUnderline(bool value) {
    Q_D(QWorkbookFontEffectsToolBar);
    d->setUnderline(value);
}


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
#ifndef WORKBOOKFONTEFFECTSTOOLBAR_H
#define WORKBOOKFONTEFFECTSTOOLBAR_H

#include <QObject>
#include <QPushButton>
#include <QShortcut>
#include <QScopedPointer>
#include <QToolBar>

#include "workbook_global.h"
#include "qworkbookfonteffectstoolbar_p.h"

class QWorkbookView;
class FormatStatus;
//class QWorkbookFontEffectsToolBarPrivate;

class WORKBOOKSHARED_EXPORT QWorkbookFontEffectsToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookFontEffectsToolBar)
public:
    QWorkbookFontEffectsToolBar(QWidget *parent);
    QWorkbookFontEffectsToolBar(QString title, QWidget *parent);
    virtual ~QWorkbookFontEffectsToolBar() {}

signals:
    void boldChanged(bool);
    void italicChanged(bool);
    void underlineChanged(bool);

public slots:
    void setBold(bool);
    void setItalic(bool);
    void setUnderline(bool);
    void setWorkbookView(QWorkbookView *);
    void selectionChanged(FormatStatus*);

protected slots:
    void boldHasClicked();
    void italicHasClicked();
    void underlineHasClicked();

protected:
    QWorkbookFontEffectsToolBar(QWorkbookFontEffectsToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
    QWorkbookFontEffectsToolBar(QWorkbookFontEffectsToolBarPrivate &d, QString title, QWidget *parent) :
        QToolBar(title, parent),
        d_ptr(&d) {}
    const QScopedPointer<QWorkbookFontEffectsToolBarPrivate> d_ptr;


    QPushButton *pBoldBtn, *pItalicBtn, *pUnderlineBtn;

private:

};
#endif // WORKBOOKFONTEFFECTSTOOLBAR_H

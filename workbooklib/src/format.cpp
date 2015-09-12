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
#include "format.h"
#include "format_p.h"
#include <workbook_global.h>
#include "worksheet.h"
#include "worksheetmodel.h"
#include "types.h"

#include <xlsxformat.h>

/*!
 * \enum DefaultNumberFormats::Types
 *
 * The enum type defines the types of NumberFormat strings.
 *
 * \value General General type.
 * \value Decimal Numeric types.
 * \value Currency Currency types.
 * \value Percent Percentage types.
 * \value Scientific Scientific types.
 * \value Fraction Fractional types.
 * \value Date Date types.
 * \value Time Time types.
 * \value DateTime DateTime types.
 * \value Account Accounting types.
 * \value Text String types.
 */

/*!
 * \brief A wrapper class for the various number formats.
 *
 * A wrapper class for the various number formats. By default only the common types for
 * all Locales are stored in this class although non-standard or Locale defined types can
 * be added manually. The format consists of an int id number, a \d DefaultNumberFormats::Types
 * value that defines the grouping for the format, for example \d Decimal or \d Date, and a
 * format string.
 *
 * Format/types values can be returned using the \d format(int id) method  which returns a
 * \d NumberFormat object from which a string can be recovered using \d format() and a
 * DefaultNumberFormats::Type using type().
 *
 * Id numbers can be recovered for a format string using the \d id(QString) method.
 */
DefaultNumberFormats::DefaultNumberFormats() {
    insertStyle(0,General, QStringLiteral("General"));
    insertStyle(1, Decimal, QStringLiteral("0"));
    insertStyle(2, Decimal, QStringLiteral("0.00"));
    insertStyle(3, Decimal, QStringLiteral("#,##0"));
    insertStyle(4, Decimal, QStringLiteral("#,##0.00"));
    insertStyle(9, Percent, QStringLiteral("0%"));
    insertStyle(10, Percent, QStringLiteral("0.00%"));
    insertStyle(11, Scientific, QStringLiteral("0.00E+00"));
    insertStyle(12, Fraction, QStringLiteral("#?/?"));
    insertStyle(13, Fraction, QStringLiteral("#\?\?/\?\?"));
    insertStyle(14, Date, QStringLiteral("mm-dd-yy"));
    insertStyle(15, Date, QStringLiteral("d-mmm-yy"));
    insertStyle(16, Date, QStringLiteral("d-mmm"));
    insertStyle(17, Date, QStringLiteral("mmm-yy"));
    insertStyle(18, Time, QStringLiteral("h:mm AM/PM"));
    insertStyle(19, Time, QStringLiteral("h:mm:ss AM/PM"));
    insertStyle(20, Time, QStringLiteral("h:mm"));
    insertStyle(21, Time, QStringLiteral("h:mm:ss"));
    insertStyle(22, DateTime, QStringLiteral("m/d/yy h:mm"));
    insertStyle(37, Decimal, QStringLiteral("#,##0;(#,##0)"));
    insertStyle(38, Decimal, QStringLiteral("#,##0;[Red](#,##0)"));
    insertStyle(39, Decimal, QStringLiteral("#,##0.00;(#,##0.00)"));
    insertStyle(40, Decimal, QStringLiteral("#,##0.00;[Red](#,##0.00)"));
    insertStyle(45, Time, QStringLiteral("mm:ss"));
    insertStyle(46, Time, QStringLiteral("[h]:mm:ss"));
    insertStyle(47, Time, QStringLiteral("mmss.0"));
    insertStyle(48, Scientific, QStringLiteral("##0.0E+0"));
    insertStyle(49, Text, QStringLiteral("@"));
}

/*!
 * \brief Insert a new format style.
 *
 * Define a new number format using an integer, id, a Type, type and a format string.
 */
void DefaultNumberFormats::insertStyle(int id, NumberFormatType type, QString format) {
    insertStyle(id, type, format);
    mIds.insert(format, id);
}


Format::Format(int row, int column, QObject *parent) :
    QObject(parent),
    d_ptr(new FormatPrivate(row, column, this)) {
}

Format::Format(Format &format) :
    QObject(format.parent()),
    d_ptr(new FormatPrivate(format.row(), format.column(), this)) {
    setBold(format.bold());
    setItalic(format.italic());
    setOverline(format.overline());
    setUnderline(format.underline());
    setStrikeout(format.strikeout());
    setUnderlineStyle(format.underlineStyle());
    setUnderlineColor(format.underlineColor());
}

Format::~Format() {

}

void Format::indent() {
    d_ptr->indent();
}

void Format::undent() {
    d_ptr->undent();
}

int Format::row() {
    Q_D(Format);
    return d->mRow;
}

int Format::column() {
    Q_D(Format);
    return d->mColumn;
}

QXlsx::Format Format::toXlsx() {
    return d_ptr->toXlsx();
}

void Format::fromXlsx(QXlsx::Format format) {
    d_ptr->fromXlsx(format);
}

void Format::setCell(int row, int column) {
    Q_D(Format);
    d->mRow = row;
    d->mColumn = column;
}

QFont Format::font() {
    return d_ptr->font();
}

int Format::pixelSize() {
    return d_ptr->pixelSize();
}

int Format::pointSize() {
    return d_ptr->pointSize();
}

int Format::pointSizeF() {
    return d_ptr->pointSizeF();
}

bool Format::bold() {
    return d_ptr->bold();
}

bool Format::italic() {
    return d_ptr->italic();
}

bool Format::underline() {
    return d_ptr->underline();
}

bool Format::overline() {
    return d_ptr->overline();
}

bool Format::strikeout() {
    return d_ptr->strikeout();
}

Qt::Alignment Format::alignment() {
    return d_ptr->alignment();
}

void Format::setAlignment(Qt::Alignment alignment) {
    d_ptr->setAlignment(alignment);
}

int Format::indentSize() {
    Q_D(Format);
    int count = d->mIndentCount;
    int size = d->xWidth;

    return (count * size);
}

void Format::setFont(QFont font) {
    d_ptr->setFont(font);
}

void Format::setPointSize(int size) {
    d_ptr->setPointSize(size);
}

void Format::setPointSizeF(float size) {
    d_ptr->setPointSizeF(size);
}

void Format::setPixelSize(int size) {
    d_ptr->setPixelSize(size);
}

void Format::setBold(bool bold) {
    d_ptr->setBold(bold);
}

void Format::setItalic(bool italic) {
    d_ptr->setItalic(italic);
}

void Format::setOverline(bool overline) {
    d_ptr->setOverline(overline);
}

void Format::setUnderline(bool underline) {
    d_ptr->setUnderline(underline);
}

void Format::setUnderlineStyle(UnderlineStyle style) {
    d_ptr->setUnderlineStyle(style);
}

UnderlineStyle Format::underlineStyle() {
    return d_ptr->underlineStyle();
}

void Format::setUnderlineColor(QColor color) {
    d_ptr->setUnderlineColor(color);
}

QColor Format::underlineColor() {
    return d_ptr->underlineColor();
}

void Format::setStrikeout(bool strikeout) {
    d_ptr->setStrikeout(strikeout);
}

void Format::setModel(WorksheetModel *model) {
    Q_D(Format);
    d->pModel = model;
}

void Format::setBackgroundColor(QColor background) {
    d_ptr->setBackgroundColor(background);
}

QBrush Format::backgroundColor() {
    return d_ptr->backgroundColor();
}

/*!
 * \brief Set all four borders with a common new style.
 * 
 * Sets the cell borders with a common style and color. The \d enabled flag 
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 *
 * Please note that although various border types are available, only SINGLE works well,
 * the others look a bit strange, especially where mixed. Also top/bottom and left/right
 * borders overwrite each other so mixed colors in adjacent borders will probably not get
 * what you expect as the last border to be set will be the one to appear.
 */
void Format::setBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->setBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the top border with a new style.
 * 
 * Sets the cell top border with a new style and color. The \d enabled flag 
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::setTopBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->setTopBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the bottom border with a new style.
 * 
 * Sets the cell bottom border with a new style and color. The \d enabled flag 
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::setBottomBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->setBottomBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the left border with a new style.
 * 
 * Sets the cell left border with a new style and color. The \d enabled flag 
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::setLeftBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->setLeftBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the right border with a new style.
 * 
 * Sets the cell right border with a new style and color. The \d enabled flag 
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::setRightBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->setRightBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the top border with a new style.
 *
 * Sets the cell top border with a new style and color. The \d enabled flag
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::updateTopBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->updateTopBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the bottom border with a new style.
 *
 * Sets the cell bottom border with a new style and color. The \d enabled flag
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::updateBottomBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->updateBottomBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the left border with a new style.
 *
 * Sets the cell left border with a new style and color. The \d enabled flag
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::updateLeftBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->updateLeftBorder(enabled, color, style, thickness);
}

/*!
 * \brief Set the right border with a new style.
 *
 * Sets the cell right border with a new style and color. The \d enabled flag
 * enables and disables the border and the \d color and \d style parameters
 * set the border color and \d BorderStyle.
 */
void Format::updateRightBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    d_ptr->updateRightBorder(enabled, color, style, thickness);
}


Border Format::topBorder() {
    return d_ptr->topBorder();
}

Border Format::bottomBorder() {
    return d_ptr->bottomBorder();
}

Border Format::leftborder() {
    return d_ptr->leftBorder();
}

Border Format::rightBorder() {
    return d_ptr->rightBorder();
}


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
#include <QPair>

#include "cellreference_p.h"
#include "cellreference.h"
#include "workbook.h"
#include "range.h"


CellReferencePrivate::CellReferencePrivate() :
    mRow(-1),
    mColumn(-1) {
}

CellReferencePrivate::CellReferencePrivate(CellReference *parent) :
    q_ptr(parent),
    mRow(-1),
    mColumn(-1) {
}

bool CellReferencePrivate::isValid() {

    if (mRow < 0 || mColumn < 0) return false;

    return true;

}

/*!
 * /brief Converts a row number to an spreadsheet row value.
 *
 * Note : Spreadsheet offsets start at 1 while most others start at 0. The
 * function increments to allow zero based offsets.
 *
 * Row is easy as it just a number a1 - n
 */
QString CellReferencePrivate::rowToString(int row) {
    QString result =  QString::number(row + 1);
    return result;
}

/*!
 * \brief Converts a column number to an spreadsheet column value A - Z, AA - ZZ.
 *
 * 0 = A
 * 1 = B
 * ...
 * 26 = AA
 * 27 = AB etc.
 *
 * I'm not going past two columns. If I need to have more than 702 (26 * 26) + 26
 * columns in a spreadsheet I will probably shoot myself to stop me
 * being a danger to society.
 */
QString CellReferencePrivate::columnToString(int column) {
    int divisor = 26;
    int mod = column % divisor;
    int div = column / divisor;
    // limit to one extra char

    char c = mod + 'A';
    QString result(c);
    if (div > 0 && div <= 26) {
        c = 'A' + (div - 1);
        result.prepend(c);
        c += div;
    }
    return result;
}

QString CellReferencePrivate::cellToString(int column, int row) {
    QString result =  columnToString(column) + rowToString(row);
    return result;
}



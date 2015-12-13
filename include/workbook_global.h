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
#ifndef WORKBOOK_GLOBAL_H
#define WORKBOOK_GLOBAL_H

#include <QtCore/qglobal.h>

#define QT_BEGIN_NAMESPACE_QWORKBOOK namespace QWorkbook {

#define QT_END_NAMESPACE_QWORKBOOK }

#define QWORKBOOK_USE_NAMESPACE using namespace QWorkbook;

#if defined NO_WORKBOOK_LIBRARY
#   define WORKBOOKSHARED_EXPORT
#else
#   if defined(WORKBOOK_LIBRARY)
#       define WORKBOOKSHARED_EXPORT Q_DECL_EXPORT
#   else
#       define WORKBOOKSHARED_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif // WORKBOOK_GLOBAL_H

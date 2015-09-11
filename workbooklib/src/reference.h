/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#ifndef REFERENCE_H
#define REFERENCE_H

#include <QString>
#include <QRegularExpression>

#include <qquad.h>
#include "types.h"

class Reference {
public:
    Reference() {}
    ~Reference() {}

protected:
    static int columnFromString(QString &columnRef) {

        char c;
        int mult = 1;
        int column = 0;
        for (int i = columnRef.length() - 1; i >= 0 ; i--) {
            c = columnRef[i].toLatin1();
            if (c < 'A' || c > 'Z') {
                return -1; // invalid character.
            }
            column += (c - 'A') * mult;
            mult *= 10;
        }

        return column;
    }

    static int rowFromString(QString &rowRef) {

        char c;
        int mult = 1;
        int row = 0;
        for (int i = rowRef.length() - 1; i >= 0 ; i--) {
            c = rowRef[i].toLatin1();
            if (c < '0' || c > '9') {
                return -1; // invalid character.
            }
            row += (c - '0') * mult;
            mult *= 10;
        }

        return row;
    }

    static QPair<int, int> cellFromString(QString &cellRef) {

        QQuad<QString, QString, QString, QString> m_quad = init(cellRef);

        QPair<int, int> result = qMakePair<int, int>(0, 0);
        if (!m_quad.first.isEmpty() && !m_quad.second.isEmpty()) {
            result.first = columnFromString(m_quad.first);
            result.second = rowFromString(m_quad.second);
        }

        return result;

    }

    static QQuad<QString, QString, QString, QString> init(QString& ref) {

        QQuad<QString, QString, QString, QString> m_quad;

        QRegularExpression m_re = QRegularExpression(REGEXSTRING_ROW);
        QRegularExpressionMatch match = m_re.match(ref);
        if (m_re.captureCount() == 1) {
            if (match.hasMatch()) {
                m_quad.second = match.captured(0);
                m_quad.fourth = QString();
            }
        } else if (m_re.captureCount() == 2) {
            if (match.hasMatch()) {
                m_quad.second = match.captured(0);
                m_quad.fourth = match.captured(2);
            }
        }

        m_re = QRegularExpression(REGEXSTRING_COLUMN);
        match = m_re.match(ref);
        if (m_re.captureCount() == 1) {
            if (match.hasMatch()) {
                m_quad.first = match.captured(0);
                m_quad.third = QString();
            }
        } else if (m_re.captureCount() == 2) {
            if (match.hasMatch()) {
                m_quad.first = match.captured(0);
                m_quad.third = match.captured(2);
            }
        }

        return m_quad;

    }



};

#endif // REFERENCE_H

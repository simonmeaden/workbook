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

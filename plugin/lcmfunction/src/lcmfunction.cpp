#include "lcmfunction.h"

/*!
    \class LcmFunction
    \brief Calculates the least common multiple of two or more unsigned integer values.

    Returns the least common multiple of two or more unsigned integer values. This is
    a plugin function for the QWorkbook simple workbook/spreadsheet classes.
*/

LcmFunction::LcmFunction(QObject *parent) : QObject(parent) {

    setName("LCM");

}

/*!
 * \brief Returns the function name.
 *
 * Returns the function name. This is used by the parser to locate the function.
 */
QString LcmFunction::name() {
    return sName;
}

void LcmFunction::setName(QString name) {
    sName = name;
}

QStringList LcmFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant LcmFunction::calculate(quint32 a, quint32 b) {
    return lcm(a, b);
}

QVariant LcmFunction::calculate(QList<quint32> list) {
    quint32 lastLcm;
    int i;

    if(list.size() < 2) return 0;

    lastLcm = lcm(list.at(0), list.at(1));

    for(i=2; i < list.size(); i++) {
        lastLcm = lcm(lastLcm, list.at(i));
    }
    return QVariant(lastLcm);
}

/*!
    \brief Find the greatest common divisor of 2 numbers

    Returns the greatest common divisor of 2 unsigned integer numbers, a and b.
    See http://en.wikipedia.org/wiki/Greatest_common_divisor
*/
quint32 LcmFunction::gcd(quint32 a, quint32 b ) {
    quint32 c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

/*!
    \brief Find the least common multiple of 2 numbers

    Returns the least common multiple of 2 unsigned integer numbers, \d a and \d b.
    See http://en.wikipedia.org/wiki/Least_common_multiple
*/
quint32 LcmFunction::lcm(quint32 a, quint32 b) {
    return (b / gcd(a, b) ) * a;
}


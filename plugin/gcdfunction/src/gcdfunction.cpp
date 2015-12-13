#include "gcdfunction.h"

namespace QWorkbook {

GcdFunction::GcdFunction(QObject *parent) : QObject(parent) {

    setName("GCD");

}

QString GcdFunction::name() {
    return sName;
}

void GcdFunction::setName(QString name) {
    sName = name;
}

QStringList GcdFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant GcdFunction::calculate(quint32 a, quint32 b) {
    return QVariant(gcd(a, b));
}

QVariant GcdFunction::calculate(QList<quint32> list) {
    quint32 lastGcd;
    int i;
    if(list.size() < 2) return 0;

    lastGcd = gcd(list.at(0), list.at(1));

    for(i=2; i < list.size(); i++) {
        lastGcd = gcd(lastGcd, list.at(i));
    }
    return QVariant(lastGcd);
}

/*!
    \brief Find the greatest common divisor of 2 numbers

    Returns the greatest common divisor of 2 unsigned integer numbers, a and b.
    See http://en.wikipedia.org/wiki/Greatest_common_divisor
*/
quint32 GcdFunction::gcd(quint32 a, quint32 b ) {
    quint32 c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

}

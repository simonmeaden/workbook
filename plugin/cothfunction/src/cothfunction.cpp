#include "cothfunction.h"

namespace QWorkbook {

CothFunction::CothFunction(QObject *parent) : QObject(parent) {

    setName("COTH");

}

QString CothFunction::name() {
    return sName;
}

void CothFunction::setName(QString name) {
    sName = name;
}

QStringList CothFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant CothFunction::calculate(qreal radians) {
    return (cosh(radians) / sinh(radians));
}

}

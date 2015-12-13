#include "atanhfunction.h"

namespace QWorkbook {

AtanhFunction::AtanhFunction(QObject *parent) : QObject(parent) {

    setName("ATANH");

}

QString AtanhFunction::name() {
    return sName;
}

void AtanhFunction::setName(QString name) {
    sName = name;
}

QStringList AtanhFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AtanhFunction::calculate(qreal radians) {
    return atanh(radians);
}

}

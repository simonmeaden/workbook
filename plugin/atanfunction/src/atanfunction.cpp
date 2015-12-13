#include "atanfunction.h"

namespace QWorkbook {

AtanFunction::AtanFunction(QObject *parent) :QObject(parent) {

    setName("ATAN");

}

QString AtanFunction::name() {
    return sName;
}

void AtanFunction::setName(QString name) {
    sName = name;
}

QStringList AtanFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AtanFunction::calculate(qreal radians) {
    return qAtan(radians);
}

}

#include "sinfunction.h"


namespace QWorkbook {

SinFunction::SinFunction(QObject *parent) : QObject(parent) {

    setName("SIN");

}

QString SinFunction::name() {
    return sName;
}

void SinFunction::setName(QString name) {
    sName = name;
}

QStringList SinFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant SinFunction::calculate(qreal radians) {
    return qSin(radians);
}

}

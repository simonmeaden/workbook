#include "cosecfunction.h"

CoSecFunction::CoSecFunction(QObject *parent) : QObject(parent) {

    setName("COSEC");

}

QString CoSecFunction::name() {
    return sName;
}

void CoSecFunction::setName(QString name) {
    sName = name;
}

QStringList CoSecFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant CoSecFunction::calculate(qreal radians) {
    return (1.0 / qSin(radians));
}

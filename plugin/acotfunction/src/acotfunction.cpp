#include "acotfunction.h"

AcotFunction::AcotFunction(QObject *parent) : QObject(parent) {

    setName("ACOT");

}

QString AcotFunction::name() {
    return sName;
}

void AcotFunction::setName(QString name) {
    sName = name;
}

QStringList AcotFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AcotFunction::calculate(qreal radians) {
    return atan(1.0 / radians);
}

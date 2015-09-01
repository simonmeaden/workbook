#include "acosecfunction.h"

AcosecFunction::AcosecFunction(QObject *parent) : QObject(parent) {

    setName("ACOSEC");

}

QString AcosecFunction::name() {
    return sName;
}

void AcosecFunction::setName(QString name) {
    sName = name;
}

QStringList AcosecFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AcosecFunction::calculate(qreal radians) {
    return asin(1.0 / radians);
}

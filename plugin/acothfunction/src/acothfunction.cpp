#include "acothfunction.h"

AcothFunction::AcothFunction(QObject *parent) : QObject(parent) {

    setName("ACOTH");

}

QString AcothFunction::name() {
    return sName;
}

void AcothFunction::setName(QString name) {
    sName = name;
}

QStringList AcothFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AcothFunction::calculate(qreal radians) {
    return atanh(1.0 / radians);
}

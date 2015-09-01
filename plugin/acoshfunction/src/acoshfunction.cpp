#include "acoshfunction.h"

AcoshFunction::AcoshFunction(QObject *parent) : QObject(parent) {

    setName("ACOSH");

}

QString AcoshFunction::name() {
    return sName;
}

void AcoshFunction::setName(QString name) {
    sName = name;
}

QStringList AcoshFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AcoshFunction::calculate(qreal radians) {
    return acosh(radians);
}

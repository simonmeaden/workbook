#include "acosfunction.h"

namespace QWorkbook {

AcosFunction::AcosFunction(QObject *parent) :QObject(parent) {

    setName("ACOS");

}

QString AcosFunction::name() {
    return sName;
}

void AcosFunction::setName(QString name) {
    sName = name;
}

QStringList AcosFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AcosFunction::calculate(qreal radians) {
    return qAcos(radians);
}

}

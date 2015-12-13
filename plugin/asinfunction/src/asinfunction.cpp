#include "asinfunction.h"

namespace QWorkbook {

AsinFunction::AsinFunction(QObject *parent) :QObject(parent) {

    setName("ASIN");

}

QString AsinFunction::name() {
    return sName;
}

void AsinFunction::setName(QString name) {
    sName = name;
}

QStringList AsinFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AsinFunction::calculate(qreal radians) {
    return qAsin(radians);
}

}

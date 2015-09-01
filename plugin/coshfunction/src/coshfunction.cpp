#include "coshfunction.h"

CoshFunction::CoshFunction(QObject *parent) : QObject(parent) {

    setName("COSH");

}

QString CoshFunction::name() {
    return sName;
}

void CoshFunction::setName(QString name) {
    sName = name;
}

QStringList CoshFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant CoshFunction::calculate(qreal radians) {
    return cosh(radians);
}

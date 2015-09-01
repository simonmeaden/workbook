#include "sechfunction.h"

SechFunction::SechFunction(QObject *parent) : QObject(parent) {

    setName("SECH");

}

QString SechFunction::name() {
    return sName;
}

void SechFunction::setName(QString name) {
    sName = name;
}

QStringList SechFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant SechFunction::calculate(qreal radians) {
    return qPow(cosh(radians), -1);
}

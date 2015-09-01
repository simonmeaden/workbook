#include "sinhfunction.h"

SinhFunction::SinhFunction(QObject *parent) : QObject(parent) {

    setName("SINH");

}

QString SinhFunction::name() {
    return sName;
}

void SinhFunction::setName(QString name) {
    sName = name;
}

QStringList SinhFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant SinhFunction::calculate(qreal radians) {
    return sinh(radians);
}

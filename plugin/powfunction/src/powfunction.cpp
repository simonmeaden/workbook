#include "powfunction.h"

PowFunction::PowFunction(QObject *parent) : QObject(parent) {

    setName("POW");

}

QString PowFunction::name() {
    return sName;
}

void PowFunction::setName(QString name) {
    sName = name;
}

QStringList PowFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant PowFunction::calculate(qreal x, qreal y) {
    return qPow(x, y);
}

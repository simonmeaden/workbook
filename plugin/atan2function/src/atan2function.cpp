#include "atan2function.h"

Atan2Function::Atan2Function(QObject *parent) : QObject(parent) {

    setName("ATAN2");

}

QString Atan2Function::name() {
    return sName;
}

void Atan2Function::setName(QString name) {
    sName = name;
}

QStringList Atan2Function::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant Atan2Function::calculate(qreal y, qreal x) {
    return qAtan2(y, x);
}


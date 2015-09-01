#include "expfunction.h"

ExpFunction::ExpFunction(QObject *parent) :QObject(parent) {

    setName("EXP");

}

QString ExpFunction::name() {
    return sName;
}

void ExpFunction::setName(QString name) {
    sName = name;
}

QStringList ExpFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant ExpFunction::calculate(qreal value) {
    return qExp(value);
}

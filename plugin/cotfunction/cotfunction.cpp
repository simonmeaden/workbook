#include "cotfunction.h"

CotFunction::CotFunction(QObject *parent) : QObject(parent) {

    setName("COT");

}

QString CotFunction::name() {
    return sName;
}

void CotFunction::setName(QString name) {
    sName = name;
}

QStringList CotFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant CotFunction::calculate(qreal radians) {
    return (1.0 / qTan(radians));
}

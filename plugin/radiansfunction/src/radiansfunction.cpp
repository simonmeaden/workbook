#include "radiansfunction.h"

RadiansFunction::RadiansFunction(QObject *parent) :QObject(parent) {

    setName("RADIANS");

}

QString RadiansFunction::name() {
    return sName;
}

void RadiansFunction::setName(QString name) {
    sName = name;
}

QStringList RadiansFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant RadiansFunction::calculate(qreal value) {
    return qDegreesToRadians(value);
}

#include "degreesfunction.h"

DegreesFunction::DegreesFunction(QObject *parent) : QObject(parent){

    setName("DEGREES");

}

QString DegreesFunction::name() {
    return sName;
}

void DegreesFunction::setName(QString name) {
    sName = name;
}

QStringList DegreesFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant DegreesFunction::calculate(qreal value) {
    return qRadiansToDegrees(value);
}

#include "absfunction.h"

AbsFunction::AbsFunction(QObject *parent) :QObject(parent) {

    setName("ABS");

}

QString AbsFunction::name() {
    return sName;
}

void AbsFunction::setName(QString name) {
    sName = name;
}

QStringList AbsFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AbsFunction::calculate(qreal value) {
    return fabs(value);
}

#include "piconstant.h"
#include <qmath.h>


PiConstant::PiConstant(QObject *parent) : QObject(parent) {
    setName("PI");
    setValue(M_PI);
}


void PiConstant::setName(QString name) {
    sName = name;
}

QString PiConstant::name() {
    return sName;
}

QVariant PiConstant::value() {
    return mValue;
}

void PiConstant::setValue(qreal value) {
    mValue = value;
}

QStringList PiConstant::importer() const {
    QStringList values;

    values << sName;

    return values;
}

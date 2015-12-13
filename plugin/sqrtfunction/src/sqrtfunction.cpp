#include "sqrtfunction.h"

namespace QWorkbook {

SqrtFunction::SqrtFunction(QObject *parent) :QObject(parent) {

    setName("QSRT");

}

QString SqrtFunction::name() {
    return sName;
}

void SqrtFunction::setName(QString name) {
    sName = name;
}

QStringList SqrtFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant SqrtFunction::calculate(qreal value) {
    return qSqrt(value);
}

}

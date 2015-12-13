#include "cosfunction.h"

namespace QWorkbook {

CosFunction::CosFunction(QObject *parent) : QObject(parent) {

    setName("COS");

}

QString CosFunction::name() {
    return sName;
}

void CosFunction::setName(QString name) {
    sName = name;
}

QStringList CosFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant CosFunction::calculate(qreal radians) {
    return qCos(radians);
}

}

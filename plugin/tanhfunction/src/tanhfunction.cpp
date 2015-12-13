#include "tanhfunction.h"

namespace QWorkbook {

TanhFunction::TanhFunction(QObject *parent) : QObject(parent) {

    setName("TANH");

}

QString TanhFunction::name() {
    return sName;
}

void TanhFunction::setName(QString name) {
    sName = name;
}

QStringList TanhFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant TanhFunction::calculate(qreal radians) {
    return tanh(radians);
}

}

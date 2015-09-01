#include "asinhfunction.h"

AsinhFunction::AsinhFunction(QObject *parent) : QObject(parent) {

    setName("ASINH");

}

QString AsinhFunction::name() {
    return sName;
}

void AsinhFunction::setName(QString name) {
    sName = name;
}

QStringList AsinhFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant AsinhFunction::calculate(qreal radians) {
    return asinh(radians);
}

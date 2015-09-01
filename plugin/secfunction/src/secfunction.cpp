#include "secfunction.h"

SecFunction::SecFunction() {

    setName("SEC");

}

QString SecFunction::name() {
    return sName;
}

void SecFunction::setName(QString name) {
    sName = name;
}

QStringList SecFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant SecFunction::calculate(qreal radians) {
    return (1.0 / qCos(radians));
}

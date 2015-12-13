#include "tanfunction.h"

namespace QWorkbook {

TanFunction::TanFunction(QObject *parent) : QObject(parent) {

    setName("TAN");

}

QString TanFunction::name() {
    return sName;
}

void TanFunction::setName(QString name) {
    sName = name;
}

QStringList TanFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant TanFunction::calculate(qreal radians) {
    return qTan(radians);
}


}

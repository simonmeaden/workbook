#include "lnfunction.h"

LnFunction::LnFunction(QObject *parent) :QObject(parent) {

    setName("LN");

}

QString LnFunction::name() {
    return sName;
}

void LnFunction::setName(QString name) {
    sName = name;
}

QStringList LnFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant LnFunction::calculate(qreal value) {
    return qLn(value);
}

#include "minfunction.h"

namespace QWorkbook {

MinFunction::MinFunction(QObject *parent) :QObject(parent) {

    setName("MIN");

}

QString MinFunction::name() {
    return sName;
}

void MinFunction::setName(QString name) {
    sName = name;
}

QStringList MinFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant MinFunction::calculate(qreal a, qreal b) {
    return qMin(a, b);
}

QVariant MinFunction::calculate(QList<qreal> list) {
    if (list.size() == 0) return 0.0;
    else if (list.size() == 1) return list.at(0);

    qreal min = list.at(0), next;

    for (int i = 1; i < list.size(); i++) {       // Loop until all numbers are added
        next = list.at(i++);
        min = qMin(min, next);
    }

    return min;
}

}

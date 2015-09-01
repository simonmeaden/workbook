#include "maxfunction.h"

MaxFunction::MaxFunction(QObject *parent) :QObject(parent) {

    setName("MAX");

}


QString MaxFunction::name() {
    return sName;
}

void MaxFunction::setName(QString name) {
    sName = name;
}

QStringList MaxFunction::importer() const {
    QStringList values;

    values << sName;

    return values;
}

QVariant MaxFunction::calculate(qreal a, qreal b) {
    return qMax(a, b);
}

QVariant MaxFunction::calculate(QList<qreal> list) {
    if (list.size() == 0) return 0.0;
    else if (list.size() == 1) return list.at(0);

    qreal max = list.at(0), next;

    for (int i = 1; i < list.size(); i++) {       // Loop until all numbers are added
        next = list.at(i++);
        max = qMax(max, next);
    }

    return max;
}

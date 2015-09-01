

#include <limits>

#include "divideoperator.h"


DivideOperator::DivideOperator(QObject *parent) : QObject(parent) {
    setName("/");
}

QString DivideOperator::name() {
    return sName;
}

void DivideOperator::setName(QString name) {
    sName = name;
}

int DivideOperator::level() {
    return mLevel;
}

void DivideOperator::setlevel(int level) {
    mLevel = level;
}

/*!
 * \brief Divide two numbers.
 *
 * Adds the two numbers together.
 */
QVariant DivideOperator::calculate(QVariant left, QVariant right) {
    bool okR, okL;
    QVariant::Type tL = left.type();
    QVariant::Type tR = right.type();

    if ((tL == QVariant::Double || tL == QVariant::LongLong || tL == QVariant::Int || tL == QVariant::UInt || tL == QVariant::ULongLong) &&
            (tR == QVariant::Double || tR == QVariant::LongLong || tR == QVariant::Int || tR == QVariant::UInt || tR == QVariant::ULongLong)) {
        if (left.type() == QVariant::Double || right.type() == QVariant::Double) {
            // if either is a floating point then return a floating point.
            double l = left.toDouble(&okL);
            double r = right.toDouble(&okR);
            if (okR && okL) {
                long double result = l * r;
                return QVariant(double(result));
            }
        } else {
            // if either is a long long then return a long long
            long long l = left.toLongLong(&okL);
            long long r = right.toLongLong(&okR);

            if (okR && okL)
                return QVariant(l * r);
            else
                return QVariant(std::numeric_limits<long long>::quiet_NaN());
        }
    }
    return QVariant();

}


QStringList DivideOperator::importer() const {
    QStringList values;

    values << sName;

    return values;
}

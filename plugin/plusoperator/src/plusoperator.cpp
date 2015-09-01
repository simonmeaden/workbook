
#include <limits>

#include "plusoperator.h"

PlusOperator::PlusOperator(QObject *parent) :
    QObject(parent) {

    setName("+");
    setlevel(4);

}

QString PlusOperator::name() {
    return sName;
}

void PlusOperator::setName(QString name) {
    sName = name;
}

int PlusOperator::level() {
    return mLevel;
}

void PlusOperator::setlevel(int level) {
    mLevel = level;
}

/*!
 * \brief Add two numbers together.
 *
 * Adds the two numbers together.
 */
QVariant PlusOperator::calculate(QVariant left, QVariant right) {
    bool okR, okL;
    QVariant::Type tL = left.type();
    QVariant::Type tR = right.type();

    if (tR == QVariant::String && tR == QVariant::String) {
        // if strings then concatenate them.
        return QVariant(left.toString() + right.toString());
    } else {
        if ((tL == QVariant::Double || tL == QVariant::LongLong || tL == QVariant::Int || tL == QVariant::UInt || tL == QVariant::ULongLong) &&
                (tR == QVariant::Double || tR == QVariant::LongLong || tR == QVariant::Int || tR == QVariant::UInt || tR == QVariant::ULongLong)) {
            if (left.type() == QVariant::Double || right.type() == QVariant::Double) {
                // if either is a floating point then return a floating point.
                double l = left.toDouble(&okL);
                double r = right.toDouble(&okR);
                if (okR && okL) {
                    long double result = l + r;
                    if (result < std::numeric_limits<double>::max())
                        return QVariant(double(result));
                    else
                        return QVariant(std::numeric_limits<double>::quiet_NaN());
                }
            } else {
                // if either is a long long then return a long long
                long long l = left.toLongLong(&okL);
                long long r = right.toLongLong(&okR);

                if (additionIsSafe(l, r)) {
                    if (okR && okL)
                        return QVariant(l + r);
                    else
                        return QVariant(std::numeric_limits<long long>::quiet_NaN());
                }
            }
        }
    }
    return QVariant();
}


QStringList PlusOperator::importer() const {
    QStringList values;

    values << sName;

    return values;
}

bool PlusOperator::additionIsSafe(long long a, long long b) {
    size_t a_bits = highestOneBitPosition(a), b_bits = highestOneBitPosition(b);
    return (a_bits < 32 && b_bits < 32);
}

size_t PlusOperator::highestOneBitPosition(long long a) {
    size_t bits = 0;
    while (a != 0) {
        ++bits;
        a >>= 1;
    };
    return bits;
}


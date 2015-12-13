
#include <limits>

#include "multiplyoperator.h"

namespace QWorkbook {


MultiplyOperator::MultiplyOperator(QObject *parent) :
    QObject(parent) {
    setName("*");
    setlevel(5);
}


/*!
    \brief Multiply two numbers together.

    Adds the two numbers together.
*/
qreal MultiplyOperator::calculate(qreal left, qreal right) {
    long double result = left * right;
    return double(result);
}



} // end of namespace

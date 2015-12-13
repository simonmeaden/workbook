
#include <limits>

#include "minusoperator.h"

namespace QWorkbook {


MinusOperator::MinusOperator(QObject *parent) : QObject(parent) {
    setName("-");
    setlevel(6);
}

/*!
    \brief Add two numbers together.

    Adds the two numbers together.
*/
qreal MinusOperator::calculate(qreal left, qreal right) {
    return left - right;
}


} // end of namespace

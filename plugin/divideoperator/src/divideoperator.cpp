

#include <limits>

#include "divideoperator.h"

namespace QWorkbook {

DivideOperator::DivideOperator(QObject *parent) : QObject(parent) {
    setName("/");
    setlevel(5);
}

/*!
 * \brief Divide two numbers.
 *
 * Adds the two numbers together.
 */
qreal DivideOperator::calculate(qreal left, qreal right) {

    return left / right;

}


} // end of namespace

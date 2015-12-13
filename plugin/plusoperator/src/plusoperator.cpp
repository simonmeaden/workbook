
#include <limits>

#include "plusoperator.h"


namespace QWorkbook {

ConcatenateOperator::ConcatenateOperator(QObject *parent) :
    QObject(parent) {

    setName("+");
    setlevel(6);

}

/*!
 * \brief Add two numbers together.
 *
 * Adds the two numbers together.
 */
qreal ConcatenateOperator::calculate(qreal left, qreal right) {
    return left + right;
}

} // end of namespace

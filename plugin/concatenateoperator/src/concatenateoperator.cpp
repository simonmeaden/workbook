
#include <limits>

#include "concatenateoperator.h"


namespace QWorkbook {

ConcatenateOperator::ConcatenateOperator(QObject *parent) :
    QObject(parent) {

    setName("&");
    setlevel(5);

}

/*!
 * \brief Add two numbers together.
 *
 * Adds the two numbers together.
 */
QString ConcatenateOperator::calculate(QString left, QString right) {
    return left + right;
}

} // end of namespace

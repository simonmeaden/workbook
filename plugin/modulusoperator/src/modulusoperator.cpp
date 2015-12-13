
#include <limits>

#include "modulusoperator.h"

namespace QWorkbook {


ModulusOperator::ModulusOperator(QObject *parent) :
    QObject(parent) {
    setName("%");
    setlevel(5);
}


/*!
    \brief return the reamainder of two numbers divided.

    Adds the two numbers together.
*/
int ModulusOperator::calculate(int left, int right) {
    long int result = left % right;
    return double(result);
}



} // end of namespace

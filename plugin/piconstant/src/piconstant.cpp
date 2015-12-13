#include "piconstant.h"
#include <qmath.h>


namespace QWorkbook {

PiConstant::PiConstant(QObject *parent) : QObject(parent) {
    setName("PI");
    setValue(M_PI);
}

} // end of namespace

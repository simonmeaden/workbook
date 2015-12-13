#ifndef MULTIPLYOPERATOR_H
#define MULTIPLYOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QtPlugin>

#include "interface.h"
#include "workbook_global.h"

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT  MultiplyOperator :
        public QObject, public OperatorBase<qreal> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(QWorkbook::IOperator)
public:
    MultiplyOperator(QObject *parent = 0);

    qreal calculate(qreal left, qreal right);

protected:

};

}

#endif // MULTIPLYOPERATOR_H

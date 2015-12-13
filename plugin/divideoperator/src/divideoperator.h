#ifndef DIVIDEOPERATOR_H
#define DIVIDEOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtPlugin>

#include <interface.h>
#include <workbook_global.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT  DivideOperator :
        public QObject,
        public OperatorBase<qreal> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(QWorkbook::IOperator)
public:
    DivideOperator(QObject *parent = 0);

    qreal calculate(qreal left, qreal right);

protected:

};

}

#endif // DIVIDEOPERATOR_H

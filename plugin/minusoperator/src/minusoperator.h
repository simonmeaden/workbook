#ifndef MINUSOPERATOR_H
#define MINUSOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtPlugin>

#include <interface.h>
#include <workbook_global.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT MinusOperator :
        public QObject, public OperatorBase<qreal> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(QWorkbook::IOperator)
public:
    MinusOperator(QObject *parent = 0);

    qreal calculate(qreal left, qreal right);

protected:

};

}

#endif // MINUSOPERATOR_H

#ifndef MULTIPLYOPERATOR_H
#define MULTIPLYOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QtPlugin>

#include "interface.h"
#include "workbook_global.h"

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT  ModulusOperator :
        public QObject, public OperatorBase<int> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(QWorkbook::IOperator)
public:
    ModulusOperator(QObject *parent = 0);

    int calculate(int left, int right);

protected:

};

}

#endif // MULTIPLYOPERATOR_H

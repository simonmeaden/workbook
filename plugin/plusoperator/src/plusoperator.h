#ifndef PLUSOPERATOR_H
#define PLUSOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtPlugin>

#include <interface.h>
#include <workbook_global.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT ConcatenateOperator :
        public QObject, public OperatorBase<qreal> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(QWorkbook::IOperator)
public:
    explicit ConcatenateOperator(QObject *parent = 0);

    qreal calculate(qreal left, qreal right);


signals:

public slots:

protected:
//    bool additionIsSafe(long long a, long long b);
//    size_t highestOneBitPosition(long long a);
};

}

#endif // PLUSOPERATOR_H

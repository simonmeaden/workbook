#ifndef LCMFUNCTION_H
#define LCMFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "interface.h"
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT LcmFunction :
        public QObject,
        public ITwoValueFunction<quint32, quint32>,
        public IListFunction<quint32>,
        public IFunction {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid )
    Q_INTERFACES(IFunction)
public:
    explicit LcmFunction(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(QList<quint32> list);
    QVariant calculate(quint32 a, quint32 b);

protected:
    QString sName;

    void setName(QString name);
    quint32 gcd ( quint32 a, quint32 b );
    quint32 lcm(quint32 a, quint32 b);

 };

#endif // LCMFUNCTION_H

#ifndef MINFUNCTION_H
#define MINFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QList>
#include <qmath.h>

#include <cstdarg>

#include "interface.h"
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT MinFunction:
        public QObject,
        public ITwoValueFunction<qreal, qreal>,
        public IListFunction<qreal>,
        public IFunction  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(IFunction)
public:
    MinFunction(QObject *parent=0);

    QStringList importer() const;

    QString name();
    QVariant calculate(QList<qreal> list);
    QVariant calculate(qreal a, qreal b);

protected:
    QString sName;

    void setName(QString name);
};

#endif // MINFUNCTION_H

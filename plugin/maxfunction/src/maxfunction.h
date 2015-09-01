#ifndef MAXFUNCTION_H
#define MAXFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include "interface.h"
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT MaxFunction  :
        public QObject,
        public ITwoValueFunction<qreal, qreal>,
        public IListFunction<qreal>,
        public IFunction  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid )
    Q_INTERFACES(IFunction)
public:
    MaxFunction(QObject *parent=0);

    QStringList importer() const;

    QString name();
    QVariant calculate(QList<qreal> list);
    QVariant calculate(qreal a, qreal b);

protected:
    QString sName;

    void setName(QString name);
};

#endif // MAXFUNCTION_H

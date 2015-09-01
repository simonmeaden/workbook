#ifndef ACOSFUNCTION_H
#define ACOSFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <workbook_global.h>
#include <interface.h>

class AcosFunction :
        public QObject,
        public IOneValueFunction<qreal>,
        public IFunction {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(IFunction)
public:
    AcosFunction(QObject *parent=0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal radians);

protected:
    QString sName;

    void setName(QString name);
};

#endif // ACOSFUNCTION_H

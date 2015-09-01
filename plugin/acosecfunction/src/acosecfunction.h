#ifndef ACOSECFUNCTION_H
#define ACOSECFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <interface.h>
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT AcosecFunction:
    public QObject,
    public IOneValueFunction<qreal>,
    public IFunction {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(IFunction)
public:
    explicit AcosecFunction(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal radians);

protected:
    QString sName;

    void setName(QString name);
};

#endif // ACOSECFUNCTION_H

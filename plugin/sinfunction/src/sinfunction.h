#ifndef SINFUNCTION_H
#define SINFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <interface.h>
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT SinFunction :
    public QObject,
    public IOneValueFunction<qreal>,
    public IFunction  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(IFunction)
public:
    SinFunction(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal radians);

protected:
    QString sName;

    void setName(QString name);

};

#endif // SINFUNCTION_H

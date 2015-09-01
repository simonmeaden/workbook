#ifndef COSHFUNCTION_H
#define COSHFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <interface.h>
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT CoshFunction :
        public QObject,
        public IOneValueFunction<qreal>,
        public IFunction {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IFunction_iid)
        Q_INTERFACES(IFunction)
public:
    explicit CoshFunction(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal radians);

protected:
    QString sName;

    void setName(QString name);
};

#endif // COSHFUNCTION_H

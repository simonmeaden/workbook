#ifndef ATANFUNCTION_H
#define ATANFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <workbook_global.h>
#include <interface.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT AtanFunction :
        public QObject,
        public IOneValueFunction<qreal>,
        public IFunction {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(QWorkbook::IFunction)
public:
    AtanFunction(QObject *parent=0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal radians);

protected:
    QString sName;

    void setName(QString name);
};

}

#endif // ATANFUNCTION_H

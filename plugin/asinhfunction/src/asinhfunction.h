#ifndef ASINHFUNCTION_H
#define ASINHFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <interface.h>
#include <workbook_global.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT AsinhFunction :
        public QObject,
        public IOneValueFunction<qreal>,
        public IFunction {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IFunction_iid)
        Q_INTERFACES(QWorkbook::IFunction)
public:
    explicit AsinhFunction(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal radians);

protected:
    QString sName;

    void setName(QString name);
};

}

#endif // ASINHFUNCTION_H

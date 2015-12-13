#ifndef POWFUNCTION_H
#define POWFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <interface.h>
#include <workbook_global.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT PowFunction :
        public QObject,
        public ITwoValueFunction<qreal, qreal>,
        public IFunction  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(QWorkbook::IFunction)
public:
    PowFunction(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal x, qreal y);

protected:
    QString sName;

    void setName(QString name);
};

}

#endif // POWFUNCTION_H

#ifndef RADIANSFUNCTION_H
#define RADIANSFUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <interface.h>
#include <workbook_global.h>

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT RadiansFunction :
        public QObject,
        public IOneValueFunction<qreal>,
        public IFunction {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IFunction_iid)
        Q_INTERFACES(QWorkbook::IFunction)
public:
    RadiansFunction(QObject *parent=0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal value);

protected:
    QString sName;

    void setName(QString name);
};

}

#endif // RADIANSFUNCTION_H

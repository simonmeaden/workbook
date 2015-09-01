#ifndef ATAN2FUNCTION_H
#define ATAN2FUNCTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <qmath.h>

#include <workbook_global.h>
#include <interface.h>

class WORKBOOKSHARED_EXPORT Atan2Function :
    public QObject,
    public ITwoValueFunction<qreal, qreal>,
    public IFunction {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IFunction_iid)
    Q_INTERFACES(IFunction)
public:
    Atan2Function(QObject *parent=0);

    QStringList importer() const;

    QString name();
    QVariant calculate(qreal y, qreal x);

protected:
    QString sName;

    void setName(QString name);
};

#endif // ATAN2FUNCTION_H

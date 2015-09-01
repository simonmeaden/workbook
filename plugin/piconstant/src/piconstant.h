#ifndef PICONSTANT_H
#define PICONSTANT_H

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QtPlugin>

#include <workbook_global.h>
#include <interface.h>

class WORKBOOKSHARED_EXPORT PiConstant :
        public QObject, public ConstantInterface<qreal> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IConstant_iid)
    Q_INTERFACES(IConstant)
public:
    PiConstant(QObject *parent = 0);

    QStringList importer() const;
    QVariant value();
    QString name();

protected:
    qreal mValue;
    QString sName;

    void setName(QString name);
    void setValue(qreal value);

};

#endif // PICONSTANT_H

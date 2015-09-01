#ifndef MINUSOPERATOR_H
#define MINUSOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtPlugin>

#include <interface.h>
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT MinusOperator :
        public QObject, public OperatorInterface<QVariant> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(IOperator)
public:
    MinusOperator(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(QVariant left, QVariant right);
    int level();

protected:
    QString sName;
    int mLevel;

    void setName(QString name);
    void setlevel(int level);
};

#endif // MINUSOPERATOR_H

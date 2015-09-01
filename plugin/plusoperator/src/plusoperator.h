#ifndef PLUSOPERATOR_H
#define PLUSOPERATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtPlugin>

#include <interface.h>
#include <workbook_global.h>

class WORKBOOKSHARED_EXPORT PlusOperator :
        public QObject, public OperatorInterface<QVariant> {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOperator_iid)
    Q_INTERFACES(IOperator)
public:
    explicit PlusOperator(QObject *parent = 0);

    QStringList importer() const;

    QString name();
    QVariant calculate(QVariant left, QVariant right);
    int level();


signals:

public slots:

protected:
    QString sName;
    int mLevel;

    void setName(QString name);
    void setlevel(int level);

    bool additionIsSafe(long long a, long long b);
    size_t highestOneBitPosition(long long a);
};


#endif // PLUSOPERATOR_H

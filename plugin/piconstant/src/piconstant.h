#ifndef PICONSTANT_H
#define PICONSTANT_H

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QtPlugin>

#include "workbook_global.h"
#include "interface.h"

namespace QWorkbook {

class WORKBOOKSHARED_EXPORT PiConstant :
        public QObject, public ConstantBase {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IConstant_iid)
    Q_INTERFACES(QWorkbook::IConstant)
public:
    PiConstant(QObject *parent = 0);

protected:

};

}

#endif // PICONSTANT_H

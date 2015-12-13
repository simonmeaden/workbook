#ifndef QCELLEDIT_H
#define QCELLEDIT_H

#include <QWidget>
#include <QToolBar>
#include <QScopedPointer>
#include <QLineEdit>

#include "workbook_global.h"
#include "qcelledittoolbar_p.h"

namespace QWorkbook {

class QWorkbookView;
class QWorksheetView;
class FormatStatus;

class WORKBOOKSHARED_EXPORT QCellEditToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QCellEditToolBar)
public:
    QCellEditToolBar(QWidget *);
    QCellEditToolBar(QString, QWidget *);
    virtual ~QCellEditToolBar() {}

signals:
    void contentsChanged(QString text);

public slots:
    void setWorkbookView(QWorkbookView *);
    void setWorksheetView(QWorksheetView *);
    void setText(QString);

protected slots:
    void setValueWithoutSignal(QVariant);
    void setTextWithoutSignal(QString);
//    void setCellEditor();
//    void setCellEditor(QString);
//    void drop();


protected:
    QCellEditToolBar(QCellEditToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
   QCellEditToolBar(QCellEditToolBarPrivate &d, QString title, QWidget *parent) :
       QToolBar(title, parent),
       d_ptr(&d) {}
    const QScopedPointer<QCellEditToolBarPrivate> d_ptr;

private:

    friend class QWorkbookView;
};


}

#endif // QCELLEDIT_H

#ifndef WORKBOOKALIGNTOOLBAR_H
#define WORKBOOKALIGNTOOLBAR_H

#include <QPushButton>
#include <QButtonGroup>

#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT QWorkbookAlignToolbar : public BaseToolbar {
    Q_OBJECT
public:
    QWorkbookAlignToolbar(QWidget *);
    QWorkbookAlignToolbar(QString, QWidget *);
    ~QWorkbookAlignToolbar();

signals:
    void alignmentChanged(Qt::Alignment);

public slots:
    void setAlign(bool, Qt::Alignment);

protected slots:
    void align();

protected:
    QPushButton *pLeftBtn, *pHCentreBtn, *pRightBtn;
    QButtonGroup *pButtonGroup;

    void init();

};

#endif // WORKBOOKALIGNTOOLBAR_H

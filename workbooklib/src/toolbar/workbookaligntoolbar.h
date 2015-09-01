#ifndef WORKBOOKALIGNTOOLBAR_H
#define WORKBOOKALIGNTOOLBAR_H

#include <QPushButton>
#include <QButtonGroup>

#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT WorkbookAlignToolbar : public BaseToolbar {
    Q_OBJECT
public:
    WorkbookAlignToolbar(QWidget *parent);
    WorkbookAlignToolbar(QString title, QWidget *parent);
    ~WorkbookAlignToolbar();

signals:

public slots:
    void setAlign(Qt::Alignment);

protected slots:
    void align();
    void merge();

protected:
    QPushButton *pLeftBtn, *pHCentreBtn, *pRightBtn, *pFillBtn, *pMergeBtn;
    QButtonGroup *pButtonGroup;

    void init();

};

#endif // WORKBOOKALIGNTOOLBAR_H

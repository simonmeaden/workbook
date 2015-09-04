#ifndef WORKBOOKMERGETOOLBAR_H
#define WORKBOOKMERGETOOLBAR_H

#include <QToolBar>
#include <QPushButton>

#include "basetoolbar.h"


class QWorkbookMergeToolbar : public BaseToolbar {
    Q_OBJECT
public:
    QWorkbookMergeToolbar(QWidget *);
    QWorkbookMergeToolbar(QString, QWidget *);
    ~QWorkbookMergeToolbar();

signals:
    void mergeSelection(bool);

public slots:
    void setMerge(bool);

protected slots:
    void merge();

protected:
    QPushButton *pMergeBtn;

    void init();
};

#endif // WORKBOOKMERGETOOLBAR_H

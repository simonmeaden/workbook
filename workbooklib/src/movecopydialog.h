#ifndef MOVECOPYDIALOG_H
#define MOVECOPYDIALOG_H

#include <QRadioButton>
#include <QListWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QDialog>

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookView;

class MoveCopyDialog : public QDialog {
    Q_OBJECT
public:
    enum Type {
        Move,
        Copy,
    };
    explicit MoveCopyDialog(QWorkbookView *parent);
    explicit MoveCopyDialog(QString, QWorkbookView *);
    virtual ~MoveCopyDialog() {}

    QString name();
    int tabIndex();
    Type type();

public slots:
    void setName(QString);

protected:
    QRadioButton *pMoveBtn, *pCopyBtn;
    QButtonGroup *pGroup;
    QListWidget *pListView;
    QLineEdit *pNameEdit;
    QPushButton *pOkBtn, *pCancelBtn;
    QWorkbookView *pView;

    void init();

private:

};


}

#endif // MOVECOPYDIALOG_H

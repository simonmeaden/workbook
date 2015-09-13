#ifndef QCELLEDITTOOLBARPRIVATE_H
#define QCELLEDITTOOLBARPRIVATE_H

#include <QLineEdit>
#include <QPlainTextEdit>
#include <QToolButton>

class QCellEditToolBar;
class QWorkbookView;
class FormatStatus;

class QCellEditToolBarPrivate {
    Q_DECLARE_PUBLIC(QCellEditToolBar)
public:
    QCellEditToolBarPrivate(QCellEditToolBar *q);
    virtual ~QCellEditToolBarPrivate() {}

    void setWorkbookView(QWorkbookView *);
    void setText(QString);
    void setValueWithoutSignal(QVariant);
    void setTextWithoutSignal(QString);

protected:
    QLineEdit *pCellEdit;
    QPlainTextEdit *pDropDownEdit;
    QToolButton *pDropBtn;
    QWidget *pEditor;
    QCellEditToolBar *q_ptr;
    QString mOldText;
    QWorkbookView *pView;

    void init();
    void setCellEditorValue(QObject*);
    void drop();

};

#endif // QCELLEDITTOOLBARPRIVATE_H

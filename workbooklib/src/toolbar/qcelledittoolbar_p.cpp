#include "qcelledittoolbar_p.h"
#include "qcelledittoolbar.h"
#include "qworkbookview.h"
#include "qworksheetview.h"
#include "types.h"

#include "workbook_global.h"

namespace QWorkbook {

QCellEditToolBarPrivate::QCellEditToolBarPrivate(QCellEditToolBar *q) :
    q_ptr(q),
    pView(NULL) {

}


void QCellEditToolBarPrivate::init() {

    pCellEdit = new QLineEdit(q_ptr);
    pCellEdit->setToolTip(q_ptr->tr("Input line"));
//    pDropDownEdit = new QPlainTextEdit(q_ptr);
//    pDropDownEdit->setToolTip(q_ptr->tr("Input line"));
//    pDropDownEdit->setVisible(false);
    pEditor = pCellEdit;
    q_ptr->addWidget(pEditor);

//    pDropBtn = new QToolButton(q_ptr);
//    pDropBtn->setStyleSheet(ButtonStyle);
//    pDropBtn->setCheckable(true);
//    pDropBtn->setArrowType(Qt::DownArrow);
//    q_ptr->addWidget(pDropBtn);
//    q_ptr->connect(pDropBtn, SIGNAL(clicked()), q_ptr, SLOT(drop()));

    q_ptr->connect(pCellEdit, SIGNAL(textChanged(QString)),
                   q_ptr, SLOT(setText(QString)));
//    q_ptr->connect(pDropDownEdit, SIGNAL(textChanged()),
//                   q_ptr, SLOT(setCellEditor()));

}

//void QCellEditToolBarPrivate::drop() {
//    if (pEditor == pCellEdit) {
//        pDropDownEdit->setVisible(true);
//        pCellEdit->setVisible(false);
//        pEditor = pDropDownEdit;
//    } else {
//        pDropDownEdit->setVisible(false);
//        pCellEdit->setVisible(true);
//        pEditor = pCellEdit;
//    }
//}


void QCellEditToolBarPrivate::setView(QObject *view) {

    Q_Q(QCellEditToolBar);
    QWorkbookView *wb;
    QWorksheetView *ws;

    // remove old connections
    if (pView) {
        wb = qobject_cast<QWorkbookView*>(pView);
        ws = qobject_cast<QWorksheetView*>(pView);

        if (wb) {
            q->disconnect(wb, SIGNAL(cellChanged(QVariant)),
                       q, SLOT(setValueWithoutSignal(QVariant)));
            q->disconnect(wb, SIGNAL(cellContentsChanged(QString)),
                       q, SLOT(setTextWithoutSignal(QString)));
            q->disconnect(q, SIGNAL(contentsChanged(QString)),
                       wb, SLOT(changeCellContents(QString)));
        } else if (ws) {
            q->disconnect((ws), SIGNAL(cellChanged(QVariant)),
                       q, SLOT(setValueWithoutSignal(QVariant)));
            q->disconnect(ws, SIGNAL(cellContentsChanged(QString)),
                       q, SLOT(setTextWithoutSignal(QString)));
            q->disconnect(q, SIGNAL(contentsChanged(QString)),
                       (ws), SLOT(changeCellContents(QString)));
        }
    }

    // make new ones.
    wb = qobject_cast<QWorkbookView*>(view);
    ws = qobject_cast<QWorksheetView*>(view);
    if (wb) {
        q->connect(wb, SIGNAL(cellChanged(QVariant)),
                   q, SLOT(setValueWithoutSignal(QVariant)));
        q->connect(wb, SIGNAL(cellContentsChanged(QString)),
                   q, SLOT(setTextWithoutSignal(QString)));
        q->connect(q, SIGNAL(contentsChanged(QString)),
                   wb, SLOT(changeCellContents(QString)));
    } else if (ws) {
        q->connect((ws), SIGNAL(cellChanged(QVariant)),
                   q, SLOT(setValueWithoutSignal(QVariant)));
        q->connect(ws, SIGNAL(cellContentsChanged(QString)),
                   q, SLOT(setTextWithoutSignal(QString)));
        q->connect(q, SIGNAL(contentsChanged(QString)),
                   ws, SLOT(changeCellContents(QString)));
    }

    pView = view;



}

void QCellEditToolBarPrivate::setValueWithoutSignal(QVariant value) {
    q_ptr->disconnect(q_ptr, SIGNAL(contentsChanged(QString)),
               pView, SLOT(changeCellContents(QString)));
    pCellEdit->setText(value.toString());
    q_ptr->connect(q_ptr, SIGNAL(contentsChanged(QString)),
               pView, SLOT(changeCellContents(QString)));
}

void QCellEditToolBarPrivate::setTextWithoutSignal(QString value) {
    q_ptr->disconnect(q_ptr, SIGNAL(contentsChanged(QString)),
               pView, SLOT(changeCellContents(QString)));
    pCellEdit->setText(value);
    q_ptr->connect(q_ptr, SIGNAL(contentsChanged(QString)),
               pView, SLOT(changeCellContents(QString)));
}

void QCellEditToolBarPrivate::setText(QString value) {
    pCellEdit->setText(value);
    emit q_ptr->contentsChanged(value);
}

//void QCellEditToolBarPrivate::setCellEditorValue(QObject* sender) {

//    if (sender == pCellEdit) {

        // as the plain edit changes the line edit only one of them need to trigger the signal.
//        text = pCellEdit->text();
//        pDropDownEdit->setPlainText(text);
//        emit q_ptr->contentsChanged(text);

//    }
    /* else if (sender == pDropDownEdit) {

        text = pDropDownEdit->toPlainText();
        pCellEdit->setText(text);

    }*/
//}


}


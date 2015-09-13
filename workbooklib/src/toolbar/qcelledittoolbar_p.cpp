#include "qcelledittoolbar_p.h"
#include "qcelledittoolbar.h"
#include "qworkbookview.h"
#include "types.h"

QCellEditToolBarPrivate::QCellEditToolBarPrivate(QCellEditToolBar *q) :
    q_ptr(q) {

}


void QCellEditToolBarPrivate::init() {

    pCellEdit = new QLineEdit(q_ptr);
    pCellEdit->setToolTip(q_ptr->tr("Input line"));
    pDropDownEdit = new QPlainTextEdit(q_ptr);
    pDropDownEdit->setToolTip(q_ptr->tr("Input line"));
    pDropDownEdit->setVisible(false);
    pEditor = pCellEdit;
    q_ptr->addWidget(pEditor);

    pDropBtn = new QToolButton(q_ptr);
    pDropBtn->setStyleSheet(ButtonStyle);
    pDropBtn->setCheckable(true);
    pDropBtn->setArrowType(Qt::DownArrow);
    q_ptr->addWidget(pDropBtn);
    q_ptr->connect(pDropBtn, SIGNAL(clicked()), q_ptr, SLOT(drop()));

    q_ptr->connect(pCellEdit, SIGNAL(textChanged(QString)),
                   q_ptr, SLOT(setCellEditor(QString)));
    q_ptr->connect(pDropDownEdit, SIGNAL(textChanged()),
                   q_ptr, SLOT(setCellEditor()));

}

void QCellEditToolBarPrivate::drop() {
    if (pEditor == pCellEdit) {
        pDropDownEdit->setVisible(true);
        pCellEdit->setVisible(false);
        pEditor = pDropDownEdit;
    } else {
        pDropDownEdit->setVisible(false);
        pCellEdit->setVisible(true);
        pEditor = pCellEdit;
    }
}


void QCellEditToolBarPrivate::setWorkbookView(QWorkbookView *view) {

    Q_Q(QCellEditToolBar);

    // view to bar
    q->connect(view, SIGNAL(cellChanged(QVariant)),
               q, SLOT(setValueWithoutSignal(QVariant)));
    q->connect(view, SIGNAL(cellContentsChanged(QString)),
               q, SLOT(setTextWithoutSignal(QString)));

    // bar to view (sets format in view)
    q->connect(q, SIGNAL(contentsChanged(QString)),
               view, SLOT(changeCellContents(QString)));

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
}

void QCellEditToolBarPrivate::setCellEditorValue(QObject *sender) {

    QString text;
    if (sender == pCellEdit) {

        // as the plain edit changes the line edit only one of them need to trigger the signal.
        text = pCellEdit->text();
        pDropDownEdit->setPlainText(text);
        emit q_ptr->contentsChanged(text);

    } else if (sender == pDropDownEdit) {

        text = pDropDownEdit->toPlainText();
        pCellEdit->setText(text);

    }
}


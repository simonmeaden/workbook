#include "qcelledittoolbar.h"

/*!
 * \class  QCellEditToolBar
 *
 * A toolbar that holds a spreadsheet style editing window that links to the selected cell
 * on the QWorkbook. Changes to the editor are followed by the cell and changes
 * made in the cell are followed by the editor..
 *\

/*!
 * \fn QCellEditToolBar::contentsChanged(QString text);
 *
 * This signal is emitted when the the contents of editor
 * are changed.
 */

/*!
 * /brief Constructs a QCellEditToolBar with the given parent.
 */
QCellEditToolBar::QCellEditToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QCellEditToolBarPrivate(this)){
    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

/*!
 * /brief Constructs a QCellEditToolBar with the given parent.
 *
 * The given window title identifies the toolbar and is shown
 * in the context menu provided by QMainWindow.
 */
QCellEditToolBar::QCellEditToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QCellEditToolBarPrivate(this)){
    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

/*!
 * \brief Attaches the supplied QWorkbookView to the toolbar.
 *
 * The toolbar signals/slots are set up correctly to enable changes to the
 * toolbar and view to be correctly shown.
 */
void QCellEditToolBar::setWorkbookView(QWorkbookView *view) {

    Q_D(QCellEditToolBar);
    d->setWorkbookView(view);

}

/*!
 * \internal
 *
 * \brief Sets the cell contents.
 *
 * Protected method called by friend class QWorkbookView when it's selected
 * cell is changed. No signal is sent back to the view.
 */
void QCellEditToolBar::setValueWithoutSignal(QVariant value) {

    Q_D(QCellEditToolBar);
    d->setValueWithoutSignal(value);

}

/*!
 * \internal
 *
 * \brief Sets the cell contents.
 *
 * Protected method called by friend class QWorkbookView when it's selected
 * cell's contents are changed.  No signal is sent back to the view.
 */
void QCellEditToolBar::setTextWithoutSignal(QString value) {

    Q_D(QCellEditToolBar);
    d->setTextWithoutSignal(value);

}

/*!
 * \brief Sets the contents of the cell editor to the supplied value.
 */
void QCellEditToolBar::setText(QString value) {

    Q_D(QCellEditToolBar);
    d->setText(value);

}

/*!
 * \internal
 *
 * Internal class that sets the value of the both editors to the same value
 * when there are changes but only sends one signal.
 */
void QCellEditToolBar::setCellEditor() {
    d_ptr->setCellEditorValue(sender());
}

/*!
 * \internal
 *
 * Internal class that sets the value of the both editors to the same value
 * when there are changes but only sends one signal.
 */
void QCellEditToolBar::setCellEditor(QString) {
    d_ptr->setCellEditorValue(sender());
}

/*!
 * \internal
 *
 * toggle button causes the cell editor to be exchanged with a multiline editor.
 */
void QCellEditToolBar::drop() {
    d_ptr->drop();
}

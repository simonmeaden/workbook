#include "workbookfonttoolbar.h"
#include "qworkbooktoolbar.h"

WorkbookFontToolbar::WorkbookFontToolbar(QWidget *parent) : BaseToolbar(parent) {
    initBuild();
}

WorkbookFontToolbar::WorkbookFontToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    initBuild();
}

WorkbookFontToolbar::~WorkbookFontToolbar() {

}

void WorkbookFontToolbar::initBuild() {
    QFont font = QFont("Times", 10, QFont::Normal);

    pFonts = new QFontComboBox(this);
    pFonts->setToolTip(tr("Font Name"));
    pFonts->setFont(font);
    addWidget(pFonts);
    connect(pFonts, SIGNAL(currentFontChanged(QFont)), this, SLOT(fontHasChanged(QFont)));

    pSizes = new QComboBox(this);
    pSizes->setToolTip(tr("Font Size"));
    addWidget(pSizes);

    font = pFonts->currentFont();
    setFontSizes(font);
}

void WorkbookFontToolbar::fontHasChanged(QFont font) {
    setFontSizes(font);

    bool isItalic = db.italic(font.family(), font.styleName());
    emit italic(isItalic);

    bool isBold = db.bold(font.family(), font.styleName()) ;
    emit bold(isBold);

    emit master->fontChanged(font);
}

void WorkbookFontToolbar::setFont(QFont font) {
    pFonts->setCurrentFont(font);
}

void WorkbookFontToolbar::setFontSizes(QFont font) {
    QList<int> sizes = db.pointSizes(font.family(), font.styleName());
    pSizes->clear();
    QListIterator<int> it(sizes);
    while (it.hasNext())
        pSizes->addItem(QString::number(it.next()));
}

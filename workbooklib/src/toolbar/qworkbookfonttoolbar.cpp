#include "qworkbookfonttoolbar.h"
#include "qworkbooktoolbar.h"

QWorkbookFontToolbar::QWorkbookFontToolbar(QWidget *parent) : BaseToolbar(parent) {
    initBuild();
}

QWorkbookFontToolbar::QWorkbookFontToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    initBuild();
}

QWorkbookFontToolbar::~QWorkbookFontToolbar() {

}

void QWorkbookFontToolbar::initBuild() {
    QFont font = QFont("Times", 10, QFont::Normal);

    pFonts = new QFontComboBox(this);
    pFonts->setToolTip(tr("Font Name"));
    pFonts->setFont(font);
    addWidget(pFonts);
    connect(pFonts, SIGNAL(currentFontChanged(QFont)), this, SLOT(fontHasChanged(QFont)));

    pSizes = new QComboBox(this);
    pSizes->setValidator(new QIntValidator(1, 1000, this));
    pSizes->setToolTip(tr("Font Size"));
    addWidget(pSizes);
    connect(pSizes, SIGNAL(currentTextChanged(QString)), this, SLOT(sizeHasChanged(QString)));

    font = pFonts->currentFont();
    setFontSizes(font);
}

void QWorkbookFontToolbar::fontHasChanged(QFont font) {
    int size = pSizes->currentText().toInt();

    setFontSizes(font);

    bool isItalic = mFontDatabase.italic(font.family(), font.styleName());
    emit italic(isItalic);

    bool isBold = mFontDatabase.bold(font.family(), font.styleName()) ;
    emit bold(isBold);

    pSizes->setCurrentText(QString::number(size));

    emit fontChanged(font);
    emit fontSizeChanged(size);
}

void QWorkbookFontToolbar::sizeHasChanged(QString size) {
    emit fontSizeChanged(size.toInt());
}

void QWorkbookFontToolbar::setFont(QFont font) {
    pFonts->setCurrentFont(font);
}

void QWorkbookFontToolbar::setFont(bool selected, QFont font, int size) {
    if (selected) {
        pFonts->setCurrentFont(font);
        pSizes->setCurrentText(QString::number(size));
    }
}

void QWorkbookFontToolbar::setFontSizes(QFont font) {
    QList<int> sizes = mFontDatabase.pointSizes(font.family(), font.styleName());
    pSizes->clear();
    QListIterator<int> it(sizes);
    while (it.hasNext())
        pSizes->addItem(QString::number(it.next()));
}

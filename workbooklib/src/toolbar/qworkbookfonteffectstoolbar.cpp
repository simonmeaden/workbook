#include "qworkbookfonteffectstoolbar.h"
#include "qworkbooktoolbar.h"

QWorkbookFontEffectsToolbar::QWorkbookFontEffectsToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

QWorkbookFontEffectsToolbar::QWorkbookFontEffectsToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

QWorkbookFontEffectsToolbar::~QWorkbookFontEffectsToolbar() {
}

void QWorkbookFontEffectsToolbar::init()  {
    pBoldBtn = new QPushButton(QIcon("://bold"), "", this);
    pBoldBtn->setShortcut(QKeySequence(QKeySequence::Bold));
    pBoldBtn->setToolTip(tr("Bold (Ctrl+B)"));
    pBoldBtn->setStyleSheet(buttonStyle);
    pBoldBtn->setContentsMargins(0, 0, 0, 0);
    pBoldBtn->setCheckable(true);
    addWidget(pBoldBtn);
    connect(pBoldBtn, SIGNAL(clicked()), this, SLOT(bold()));

    pItalicBtn = new QPushButton(QIcon("://italic"), "", this);
    pItalicBtn->setShortcut(QKeySequence(QKeySequence::Italic));
    pItalicBtn->setToolTip(tr("Italic (Ctrl+I)"));
    pItalicBtn->setStyleSheet(buttonStyle);
    pItalicBtn->setContentsMargins(0, 0, 0, 0);
    pItalicBtn->setCheckable(true);
    addWidget(pItalicBtn);
    connect(pItalicBtn, SIGNAL(clicked()), this, SLOT(italic()));

    pUnderlineBtn = new QPushButton(QIcon("://underline"), "", this);
    pUnderlineBtn->setShortcut(QKeySequence(QKeySequence::Underline));
    pUnderlineBtn->setToolTip(tr("Underline (Ctrl+U)"));
    pUnderlineBtn->setStyleSheet(buttonStyle);
    pUnderlineBtn->setContentsMargins(0, 0, 0, 0);
    pUnderlineBtn->setCheckable(true);
    addWidget(pUnderlineBtn);
    connect(pUnderlineBtn, SIGNAL(clicked()), this, SLOT(underline()));

}

void QWorkbookFontEffectsToolbar::bold() {
    emit boldChanged(pBoldBtn->isChecked());
}

void QWorkbookFontEffectsToolbar::italic() {
    emit italicChanged(pItalicBtn->isChecked());
}

void QWorkbookFontEffectsToolbar::underline() {
    emit underlineChanged(pUnderlineBtn->isChecked());
}

void QWorkbookFontEffectsToolbar::setBold(bool value) {
    pBoldBtn->setChecked(value);
}

void QWorkbookFontEffectsToolbar::setItalic(bool value) {
    pItalicBtn->setChecked(value);
}

void QWorkbookFontEffectsToolbar::setUnderline(bool value) {
    pUnderlineBtn->setChecked(value);
}


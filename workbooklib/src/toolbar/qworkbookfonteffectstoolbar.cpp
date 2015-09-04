#include "workbookfonteffectstoolbar.h"
#include "qworkbooktoolbar.h"

WorkbookFontEffectsToolbar::WorkbookFontEffectsToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

WorkbookFontEffectsToolbar::WorkbookFontEffectsToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

WorkbookFontEffectsToolbar::~WorkbookFontEffectsToolbar() {
}

void WorkbookFontEffectsToolbar::init()  {
    pBoldBtn = new QPushButton(QIcon("://bold"), "", this);
    pBoldBtn->setToolTip(tr("Bold"));
    pBoldBtn->setStyleSheet(buttonStyle);
    pBoldBtn->setContentsMargins(0, 0, 0, 0);
    pBoldBtn->setCheckable(true);
    addWidget(pBoldBtn);
    connect(pBoldBtn, SIGNAL(clicked()), this, SLOT(bold()));

    pItalicBtn = new QPushButton(QIcon("://italic"), "", this);
    pItalicBtn->setToolTip(tr("Italic"));
    pItalicBtn->setStyleSheet(buttonStyle);
    pItalicBtn->setContentsMargins(0, 0, 0, 0);
    pItalicBtn->setCheckable(true);
    addWidget(pItalicBtn);
    connect(pItalicBtn, SIGNAL(clicked()), this, SLOT(italic()));

    pUnderlineBtn = new QPushButton(QIcon("://underline"), "", this);
    pUnderlineBtn->setToolTip(tr("Underline"));
    pUnderlineBtn->setStyleSheet(buttonStyle);
    pUnderlineBtn->setContentsMargins(0, 0, 0, 0);
    pUnderlineBtn->setCheckable(true);
    addWidget(pUnderlineBtn);
    connect(pUnderlineBtn, SIGNAL(clicked()), this, SLOT(underline()));

}

void WorkbookFontEffectsToolbar::bold() {
    emit master->boldChanged(pBoldBtn->isChecked());
}

void WorkbookFontEffectsToolbar::italic() {
    emit master->italicChanged(pItalicBtn->isChecked());
}

void WorkbookFontEffectsToolbar::underline() {
    emit master->underlineChanged(pUnderlineBtn->isChecked());
}

void WorkbookFontEffectsToolbar::setBold(bool value) {
    pBoldBtn->setChecked(value);
}

void WorkbookFontEffectsToolbar::setItalic(bool value) {
    pItalicBtn->setChecked(value);
}

void WorkbookFontEffectsToolbar::setUnderline(bool value) {
    pUnderlineBtn->setChecked(value);
}


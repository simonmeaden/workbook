#ifndef WORKBOOKFONTEFFECTSTOOLBAR_H
#define WORKBOOKFONTEFFECTSTOOLBAR_H

#include <QPushButton>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT WorkbookFontEffectsToolbar : public BaseToolbar {
    Q_OBJECT
public:
    WorkbookFontEffectsToolbar(QWidget *parent);
    WorkbookFontEffectsToolbar(QString title, QWidget *parent);
    ~WorkbookFontEffectsToolbar();

signals:

public slots:
    void setBold(bool);
    void setItalic(bool);
    void setUnderline(bool);

protected slots:
    void bold();
    void italic();
    void underline();

protected:
    QPushButton *pBoldBtn, *pItalicBtn, *pUnderlineBtn;

    void init();

};
#endif // WORKBOOKFONTEFFECTSTOOLBAR_H

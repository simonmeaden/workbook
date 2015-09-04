#ifndef WORKBOOKFONTEFFECTSTOOLBAR_H
#define WORKBOOKFONTEFFECTSTOOLBAR_H

#include <QPushButton>
#include <QShortcut>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT QWorkbookFontEffectsToolbar : public BaseToolbar {
    Q_OBJECT
public:
    QWorkbookFontEffectsToolbar(QWidget *parent);
    QWorkbookFontEffectsToolbar(QString title, QWidget *parent);
    ~QWorkbookFontEffectsToolbar();

signals:
    void boldChanged(bool);
    void italicChanged(bool);
    void underlineChanged(bool);

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

#ifndef WORKBOOKFONTTOOLBAR_H
#define WORKBOOKFONTTOOLBAR_H

#include <QFontComboBox>
#include <QComboBox>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT WorkbookFontToolbar : public BaseToolbar {
    Q_OBJECT
public:
    WorkbookFontToolbar(QWidget *parent);
    WorkbookFontToolbar(QString title, QWidget *parent);
    ~WorkbookFontToolbar();

signals:
    void bold(bool);
    void italic(bool);

public slots:
    void setFont(QFont font);

protected slots:
    void fontHasChanged(QFont font);

protected:
    QFontComboBox *pFonts;
    QComboBox *pSizes;
    QFontDatabase db;

    void initBuild();
    void setFontSizes(QFont font);
};
#endif // WORKBOOKFONTTOOLBAR_H

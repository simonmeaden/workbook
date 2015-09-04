#ifndef WORKBOOKFONTTOOLBAR_H
#define WORKBOOKFONTTOOLBAR_H

#include <QFontComboBox>
#include <QComboBox>
#include <QIntValidator>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT QWorkbookFontToolbar : public BaseToolbar {
    Q_OBJECT
public:
    QWorkbookFontToolbar(QWidget *parent);
    QWorkbookFontToolbar(QString title, QWidget *parent);
    ~QWorkbookFontToolbar();

signals:
    void bold(bool);
    void italic(bool);
    void fontChanged(QFont);
    void fontSizeChanged(int);

public slots:
    void setFont(QFont);
    void setFont(bool, QFont, int);

protected slots:
    void fontHasChanged(QFont);
    void sizeHasChanged(QString);

protected:
    QFontComboBox *pFonts;
    QComboBox *pSizes;
    QFontDatabase mFontDatabase;

    void initBuild();
    void setFontSizes(QFont font);
};
#endif // WORKBOOKFONTTOOLBAR_H

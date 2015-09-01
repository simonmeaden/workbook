#ifndef WORKBOOKVIEWPRIVATE_H
#define WORKBOOKVIEWPRIVATE_H

#include <QObject>
#include <QTabBar>
#include <QStackedLayout>
#include <QFrame>
#include <QGridLayout>
#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QButtonGroup>
#include <QLineEdit>
#include <QVariant>
#include <QDateTime>
#include <QItemSelectionModel>

#include "cellreference.h"
#include "range.h"
#include "types.h"

class QWorkbookView;
class QWorksheetView;
class Workbook;
class Worksheet;
class WorkbookInsertSheetDialog;
class WorksheetModel;
class Format;
class PluginStore;
class WorkbookParser;

class WorkbookInsertSheetDialogPrivate {
public:
    WorkbookInsertSheetDialogPrivate(WorkbookInsertSheetDialog *parent);

    QCheckBox *beforeBox, *afterBox, *newSheetBox, *fromFileBox;
    QButtonGroup *tabPositionGroup, *tabTypeGroup;
    QLineEdit *tabFilenameEdit;
    QSpinBox *tabCountBox;
    QPushButton *okBtn, *cancelBtn, *helpBtn;


    WorkbookInsertSheetDialog *q_ptr;
    Q_DECLARE_PUBLIC(WorkbookInsertSheetDialog)
};

class QWorkbookViewPrivate {
public:
    QWorkbookViewPrivate(QWorkbookView *parent);
    ~QWorkbookViewPrivate();

    // document properties
    QString sTitle, sSubject, sDescription, sKeywords, sComments, sCreator, sCompany, sCategory;
    QDateTime mCreated;
    QString title() { return sTitle; }
    void setTitle(QString title) { sTitle = title; }
    QString subject() { return sSubject; }
    void setSubject(QString subject) { sSubject = subject; }
    QString description() { return sDescription; }
    void setDescription(QString description) { sDescription = description; }
    QString keywords() { return sKeywords; }
    void setKeywords(QString keywords) { sKeywords = keywords; }
    QString comments() { return sComments; }
    void setComments(QString comments) { sComments = comments; }
    QString category() { return sCategory; }
    void setCategory(QString category) { sCategory = category; }
    QString creator() { return sCreator; }
    void setCreator(QString creator) { sCreator = creator; }
    QString company() { return sCompany; }
    void setCompany(QString company) { sCompany = company; }
    QDateTime created() { return mCreated; }
    void setCreated(QDateTime created) { mCreated = created; }


    void createActions();

    bool showGrid();
    bool showGrid(int index);
    bool showGrid(QString name);
    void setShowGrid(bool showGrid);
    void setShowGrid(int index, bool showGrid);
    void setShowGrid(QString name, bool showGrid);

    QVariant read(int row, int column);
    QVariant read(int index, int row, int column);
    QVariant read(QString name, int row, int column);

    void write(int row, int column, QVariant item);
    void write(int index, int row, int column, QVariant item);
    void write(QString name, int row, int column, QVariant item);

    void writeImage(int row, int column, QString path);
    void writeImage(int index, int row, int column, QString path);
    void writeImage(QString name, int row, int column, QString path);

    void writeImage(int row, int column, QImage image);
    void writeImage(int index, int row, int column, QImage image);
    void writeImage(QString name, int row, int column, QImage image);

    QImage imageFromFilename(QString path);

    Format* format(int row, int column);
    Format* format(int index, int row, int column);
    Format* format(QString name, int row, int column);
    void setFormat(int row, int column, Format *item);
    void setFormat(int index, int row, int column, Format *item);
    void setFormat(QString name, int row, int column, Format *item);

    QMap<QModelIndex, Format*> selectedFormats();
    QMap<QModelIndex, Format*> selectedFormats(int index);
    QMap<QModelIndex, Format*> selectedFormats(QString name);
    void setSelectedFormat(Format *format);
    void setSelectedFormat(int index, Format *format);
    void setSelectedFormat(QString name, Format *format);

    void lockCell(int row, int column);
    void lockRow(int &row);
    void lockColumn(int &column);
    void lockRange(Range &range);
    void lockSheet();
    void unlockCell(int row, int column);
    void unlockRow(int &row);
    void unlockColumn(int &column);
    void unlockRange(Range &range);
    void unlockSheet();

    void lockCell(int index, int row, int column);
    void lockRow(int index, int &row);
    void lockColumn(int index, int &column);
    void lockRange(int index, Range &range);
    void lockSheet(int index);
    void unlockCell(int index, int row, int column);
    void unlockCell(int index, CellReference &ref);
    void unlockRow(int index, int &row);
    void unlockColumn(int index, int &column);
    void unlockRange(int index, Range &range);
    void unlockSheet(int index);

    void lockCell(QString name, int row, int column);
    void lockRow(QString name, int &row);
    void lockColumn(QString name, int &column);
    void lockRange(QString name, Range &range);
    void lockSheet(QString name);
    void unlockCell(QString name, int row, int column);
    void unlockCell(QString name, CellReference &ref);
    void unlockRow(QString name, int &row);
    void unlockColumn(QString name, int &column);
    void unlockRange(QString name, Range &range);
    void unlockSheet(QString name);

    int indexOf(Worksheet*sheet);
    QWorksheetView *addWorksheet();
    QWorksheetView *addWorksheet(QString name);
    QWorksheetView *insertWorksheet(int position);
    QWorksheetView* insertWorksheet(int position, QString name);
    QWorksheetView *initWorksheet(WorksheetModel *model);
    void removeWorksheet(int position);
    void removeWorksheet(Worksheet *sheet);
    void removeWorksheet(QString name);

    QWorksheetView* currentWorksheetView();
    Worksheet* currentWorksheet();
    void setCurrentWorksheet(int index);
    void setCurrentWorksheet(QString name);

    void saveWorkbook(QString filename);
    void saveWorkbook(QString filename, WorksheetType type);

    QWorksheetView* worksheetview(int index);
    QWorksheetView* worksheetview(QString name);

    void renameSheet(QString oldname, QString newname);
    void setTabText(int index, QString text);

    inline Workbook* book() {return pBook; }
    void setWorkbook(Workbook *book);

    WorkbookParser *pParser;
    PluginStore *pPluginStore;

//    void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint);
//    void keyPressEvent(QKeyEvent* event);

    // popup menu for tabs
    QAction *pInsertSheetAction, *pRenameSheetAction, *pMoveCopySheetAction;
    QAction *pProtectSheetAction, *pTabColorAction;
    bool bEnableContextMenu, pEnableTabMenu;
    int mCurrentIndex;
    QWorksheetView *pCurrentView;

    void enablePopup();
    void insertSheet();
    void renameSheet();
    void moveCopySheet();
    void protectSheet();
    void tabColor();
    void showContextMenu(const QPoint &point);
    void enableContextMenu(bool);
    void enableTabMenu(bool);

    // toolbar methods
    void alignmentHasChanged(Qt::Alignment);
    void setBold(bool);
    void setItalic(bool);
    void setUnderline(bool);
    void indentCells();
    void undentCells();

private:
    Workbook *pBook;
    QWorkbookView *q_ptr;
    Q_DECLARE_PUBLIC(QWorkbookView)
};

#endif // WORKBOOKVIEWPRIVATE_H

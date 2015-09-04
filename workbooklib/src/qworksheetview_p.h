#ifndef WORKSHEETVIEWPRIVATE_H
#define WORKSHEETVIEWPRIVATE_H

#include <QObject>
#include <QVariant>
#include <QItemSelection>

#include "cellreference.h"
#include "range.h"
#include "types.h"

class QWorksheetView;
class PluginStore;
class WorkbookParser;
class Format;
class Worksheet;


class QWorksheetViewPrivate {

public:
    QWorksheetViewPrivate(QWorksheetView *parent);
    QWorksheetViewPrivate(WorkbookParser *parser, PluginStore *store, QWorksheetView *parent);
    ~QWorksheetViewPrivate();

    WorkbookParser *pParser;
    PluginStore *pPluginStore;
    Worksheet *pSheet;

    QVariant read(int row, int column);
    QVariant read(const CellReference& reference);

    void write(int row, int column, QVariant item);
    void write(const CellReference& reference, QVariant item);
    void write(Range& range, QVariant item);

    Format* format(int row, int column);
    Format* format(const CellReference& reference);
    void setFormat(int row, int column, Format *format);
    void setSelectedFormat(Format *format);
    QMap<QModelIndex, Format*> selectedFormats();
    void setFormat(const CellReference& reference, Format *format);
    void setFormat(Range& range, Format *format);

    // toolbar interaction
    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge(bool);

    bool bContiguous;
    FormatStatus mFormatStatus;
    QModelIndexList mItems;
    void selectionHasChanged(QItemSelection, QItemSelection);

    void init();
    void setSheetName(QString);
    QString sheetName();
    Worksheet* worksheet();


    QWorksheetView*  const q_ptr;
    Q_DECLARE_PUBLIC(QWorksheetView)
};

#endif // WORKSHEETVIEWPRIVATE_H

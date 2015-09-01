#ifndef WORKSHEETVIEWPRIVATE_H
#define WORKSHEETVIEWPRIVATE_H

#include <QObject>
#include <QVariant>
#include <QItemSelection>

#include "cellreference.h"
#include "range.h"

class QWorksheetView;
class PluginStore;
class WorkbookParser;
class Format;

class QWorksheetViewPrivate {

public:
    QWorksheetViewPrivate(QWorksheetView *parent);
    QWorksheetViewPrivate(WorkbookParser *parser, PluginStore *store, QWorksheetView *parent);
    ~QWorksheetViewPrivate();

    WorkbookParser *pParser;
    PluginStore *pPluginStore;

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

    bool contiguous;
    void selectionHasChanged(QItemSelection, QItemSelection);

    QWorksheetView*  const q_ptr;
    Q_DECLARE_PUBLIC(QWorksheetView)
};

#endif // WORKSHEETVIEWPRIVATE_H

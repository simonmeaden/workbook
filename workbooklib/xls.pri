INCLUDEPATH += xlsx
DEPENDPATH += xlsx

QT -= core

HEADERS += HEADERS += \
    xlslib.h \
    xlslib/biffsection.h \
    xlslib/blank.h \
    xlslib/boolean.h \
    xlslib/cbridge.h \
    xlslib/cell.h \
    xlslib/colinfo.h \
    xlslib/colors.h \
    xlslib/common.h \
    xlslib/continue.h \
    xlslib/datast.h \
    xlslib/docsumminfo.h \
    xlslib/err.h \
    xlslib/extformat.h \
    xlslib/font.h \
    xlslib/format.h \
    xlslib/formtags.h \
    xlslib/formula.h \
    xlslib/formula_cell.h \
    xlslib/formula_const.h \
    xlslib/formula_estimate.h \
    xlslib/formula_expr.h \
    xlslib/globalrec.h \
    xlslib/HPSF.h \
    xlslib/index.h \
    xlslib/label.h \
    xlslib/merged.h \
    xlslib/note.h \
    xlslib/number.h \
    xlslib/range.h \
    xlslib/recdef.h \
    xlslib/record.h \
    xlslib/rectypes.h \
    xlslib/row.h \
    xlslib/sheetrec.h \
    xlslib/summinfo.h \
    xlslib/tostr.h \
    xlslib/unit.h \
    xlslib/workbook.h \
    oledoc/binfile.h \
    oledoc/oledoc.h \
    oledoc/olefs.h \
    oledoc/oleprop.h \
    common/overnew.h \
    common/stringtok.h \
    common/systype.h \
    common/timespan.h \
    common/xls_poppack.h \
    common/xls_pshpack1.h \
    common/xls_pshpack2.h \
    common/xls_pshpack4.h \
    common/xlstypes.h \
    common/xlsys.h \
    common/xlconfig.h

SOURCES +=  \
    xlslib/assert_assist.cpp \
    xlslib/blank.cpp \
    xlslib/boolean.cpp \
    xlslib/cbridge.cpp \
    xlslib/cell.cpp \
    xlslib/colinfo.cpp \
    xlslib/colors.cpp \
    xlslib/continue.cpp \
    xlslib/datast.cpp \
    xlslib/docsumminfo.cpp \
    xlslib/err.cpp \
    xlslib/extformat.cpp \
    xlslib/font.cpp \
    xlslib/format.cpp \
    xlslib/formula.cpp \
    xlslib/formula_cell.cpp \
    xlslib/formula_estimate.cpp \
    xlslib/formula_expr.cpp \
    xlslib/globalrec.cpp \
    xlslib/HPSF.cpp \
    xlslib/index.cpp \
    xlslib/label.cpp \
    xlslib/merged.cpp \
    xlslib/note.cpp \
    xlslib/number.cpp \
    xlslib/range.cpp \
    xlslib/recdef.cpp \
    xlslib/record.cpp \
    xlslib/row.cpp \
    xlslib/sheetrec.cpp \
    xlslib/summinfo.cpp \
    xlslib/unit.cpp \
    xlslib/workbook.cpp \
    oledoc/binfile.cpp \
    oledoc/oledoc.cpp \
    oledoc/olefs.cpp \
    oledoc/oleprop.cpp \
    common/overnew.cpp

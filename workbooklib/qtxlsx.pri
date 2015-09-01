INCLUDEPATH += xlsx
DEPENDPATH += xlsx

QT += core gui gui-private
!build_xlsx_lib:DEFINES += XLSX_NO_LIB

HEADERS += xlsx/xlsxdocpropscore_p.h \
    xlsx/xlsxdocpropsapp_p.h \
    xlsx/xlsxrelationships_p.h \
    xlsx/xlsxutility_p.h \
    xlsx/xlsxsharedstrings_p.h \
    xlsx/xlsxcontenttypes_p.h \
    xlsx/xlsxtheme_p.h \
    xlsx/xlsxformat.h \
    xlsx/xlsxworkbook.h \
    xlsx/xlsxstyles_p.h \
    xlsx/xlsxabstractsheet.h \
    xlsx/xlsxabstractsheet_p.h \
    xlsx/xlsxworksheet.h \
    xlsx/xlsxworksheet_p.h \
    xlsx/xlsxchartsheet.h \
    xlsx/xlsxchartsheet_p.h \
    xlsx/xlsxzipwriter_p.h \
    xlsx/xlsxworkbook_p.h \
    xlsx/xlsxformat_p.h \
    xlsx/xlsxglobal.h \
    xlsx/xlsxdrawing_p.h \
    xlsx/xlsxzipreader_p.h \
    xlsx/xlsxdocument.h \
    xlsx/xlsxdocument_p.h \
    xlsx/xlsxcell.h \
    xlsx/xlsxcell_p.h \
    xlsx/xlsxdatavalidation.h \
    xlsx/xlsxdatavalidation_p.h \
    xlsx/xlsxcellreference.h \
    xlsx/xlsxcellrange.h \
    xlsx/xlsxrichstring_p.h \
    xlsx/xlsxrichstring.h \
    xlsx/xlsxconditionalformatting.h \
    xlsx/xlsxconditionalformatting_p.h \
    xlsx/xlsxcolor_p.h \
    xlsx/xlsxnumformatparser_p.h \
    xlsx/xlsxdrawinganchor_p.h \
    xlsx/xlsxmediafile_p.h \
    xlsx/xlsxabstractooxmlfile.h \
    xlsx/xlsxabstractooxmlfile_p.h \
    xlsx/xlsxchart.h \
    xlsx/xlsxchart_p.h \
    xlsx/xlsxsimpleooxmlfile_p.h \
    xlsx/xlsxcellformula.h \
    xlsx/xlsxcellformula_p.h

SOURCES += xlsx/xlsxdocpropscore.cpp \
    xlsx/xlsxdocpropsapp.cpp \
    xlsx/xlsxrelationships.cpp \
    xlsx/xlsxutility.cpp \
    xlsx/xlsxsharedstrings.cpp \
    xlsx/xlsxcontenttypes.cpp \
    xlsx/xlsxtheme.cpp \
    xlsx/xlsxformat.cpp \
    xlsx/xlsxstyles.cpp \
    xlsx/xlsxworkbook.cpp \
    xlsx/xlsxabstractsheet.cpp \
    xlsx/xlsxworksheet.cpp \
    xlsx/xlsxchartsheet.cpp \
    xlsx/xlsxzipwriter.cpp \
    xlsx/xlsxdrawing.cpp \
    xlsx/xlsxzipreader.cpp \
    xlsx/xlsxdocument.cpp \
    xlsx/xlsxcell.cpp \
    xlsx/xlsxdatavalidation.cpp \
    xlsx/xlsxcellreference.cpp \
    xlsx/xlsxcellrange.cpp \
    xlsx/xlsxrichstring.cpp \
    xlsx/xlsxconditionalformatting.cpp \
    xlsx/xlsxcolor.cpp \
    xlsx/xlsxnumformatparser.cpp \
    xlsx/xlsxdrawinganchor.cpp \
    xlsx/xlsxmediafile.cpp \
    xlsx/xlsxabstractooxmlfile.cpp \
    xlsx/xlsxchart.cpp \
    xlsx/xlsxsimpleooxmlfile.cpp \
    xlsx/xlsxcellformula.cpp


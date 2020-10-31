include( $${PWD}/../examples.pri )

#DEFINES += PLOTFLNODE_LIB APP_HAS_DLL APP_BUILD_DLL QWT_DLL
INCLUDEPATH += $$PWD

HEADERS += \
    ActiveAxisDlg.h \
    CurveSettingDlg.h \
    QTextSignEdit.h \
    QTextToolBar.h \
    qwt_plot_my.h \
    QwtAxisSettingDlg.h \
    QwtBackgroundSettingDlg.h \
    QwtPlotActions.h \
    QwtPlotCurveSettingSheet.h \
    QwtPlotWidget.h \
    QwtPlotWidgetBase.h \
    QwtSignTextMarker.h \
    QwtSymbolSettingSheet.h \
    QwtTextSettingSheet.h \
    SelectCurveDlg.h \
    mainwindow.h \
    QBrushSettingSheet.h \
    QColorButton.h \
    QPenSettingSheet.h \
    QShareActionsMngr.h \
    qlinestylecombobox.h \
    qlinewidthcombobox.h

SOURCES += \
    ActiveAxisDlg.cpp \
    CurveSettingDlg.cpp \
    QTextSignEdit.cpp \
    QTextToolBar.cpp \
    QwtAxisSettingDlg.cpp \
    QwtBackgroundSettingDlg.cpp \
    QwtPlotActions.cpp \
    QwtPlotCurveSettingSheet.cpp \
    QwtPlotWidget.cpp \
    QwtPlotWidgetBase.cpp \
    QwtSignTextMarker.cpp \
    QwtSymbolSettingSheet.cpp \
    QwtTextSettingSheet.cpp \
    SelectCurveDlg.cpp \
    main.cpp \
    mainwindow.cpp \
    QPenSettingSheet.cpp \
    QShareActionsMngr.cpp \
    QBrushSettingSheet.cpp \
    qlinestylecombobox.cpp \
    qlinewidthcombobox.cpp

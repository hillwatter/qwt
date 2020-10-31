/****************************************************************************
** Last Modified: 2011-11-8-001
**
** File Name: CurveSettingDlg.h
** Created Time: 2011-11-8 9:33:44
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __CurveSettingDlg_h__
#define __CurveSettingDlg_h__

#include <QDialog>
#include <QVector>
#include <QListView>

class QPushButton;
class QwtPlotCurve;
class QwtPlotCurveSettingSheet;

class CurveSettingDlg : public QDialog
{
    Q_OBJECT
public:
    static const int LISTVIEW_WIDTH = 30;
    static const int SHEET_WIDTH = 40;

public:
    CurveSettingDlg(QVector<QwtPlotCurve*>& curves,
                    QWidget* parent=NULL,Qt::WindowFlags f=0);
public:

Q_SIGNALS:
    void changed(QwtPlotCurve*);

private Q_SLOTS:
    void onCurveSelectChanged(const QModelIndex&);
    void onOK();
    void onApply();

private:
    void initListView();

private:
    QVector<QwtPlotCurve*>& m_curves;

    QListView* m_listViewCurves;
    QwtPlotCurveSettingSheet* m_curveSettingSheet;
    QPushButton* m_okButton;
    QPushButton* m_applyButton;
    QPushButton* m_cancelButton;

};

#endif//__CurveSettingDlg_h__

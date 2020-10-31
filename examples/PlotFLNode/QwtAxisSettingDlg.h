/****************************************************************************
** Last Modified: 2011-11-9-001
**
** File Name: QwtAxisSettingDlg.h
** Created Time: 2011-11-9 14:50:30
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QwtAxisSettingDlg_h__
#define __QwtAxisSettingDlg_h__

#include <QMap>
#include <QDialog>
#include "QwtPlotWidgetBase.h"

class QCheckBox;
class QLineEdit;
class QAction;
class QwtTextSettingSheet;
class QPenSettingSheet;

class QwtAxisSettingDlg : public QDialog
{
	Q_OBJECT
public:
	explicit QwtAxisSettingDlg(QwtPlotWidgetBase* plot,
		QWidget* parent=NULL,Qt::WindowFlags f=0);

Q_SIGNALS:
	void changed();

private Q_SLOTS:
	void onAxisChanged(QAction* action);
	void onOK();
	void onApply();

private:
	bool validateSettings();
	//save: data from widgets to object settings.
	void updateSettings(bool save=true);
	void updateGridlineSettings(bool save=true);

private:
	QwtPlotWidgetBase* m_plot;
	QwtPlot::Axis m_current_axis;
	QMap<QAction*,QwtPlot::Axis> m_action2axis;

	QCheckBox* m_checkBoxShowAxis;
	QActionGroup* m_actionsAxis;
	QwtTextSettingSheet* m_sheetTitle;
	QLineEdit* m_lineEditLabelRotation;
	QwtTextSettingSheet* m_sheetLabel;
	QCheckBox* m_checkBoxMajGridline;
	QCheckBox* m_checkBoxMinGridline;
	QPenSettingSheet* m_sheetMajGridline;
	QPenSettingSheet* m_sheetMinGridline;

	QPushButton* m_buttonOk;
	QPushButton* m_buttonApply;
	QPushButton* m_buttonCancel;

};

#endif//__QwtAxisSettingDlg_h__

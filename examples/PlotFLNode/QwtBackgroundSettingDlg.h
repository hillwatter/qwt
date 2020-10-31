/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QwtBackgroundSettingDlg.h
** Created Time: 2011-11-14 9:24:18
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QwtBackgroundSettingDlg_h__
#define __QwtBackgroundSettingDlg_h__

#include <QDialog>
#include "QwtPlotWidgetBase.h"

class QwtTextSettingSheet;
class QBrushSettingSheet;

class QwtBackgroundSettingDlg : public QDialog
{
	Q_OBJECT
public:
	explicit QwtBackgroundSettingDlg(QwtPlotWidgetBase* plot,
		QWidget* parent=NULL,Qt::WindowFlags f=0);

private Q_SLOTS:
	void onOK();
	void onApply();

private:
	bool validateSettings();
	//save: data from widgets to object settings.
	void updateSettings(bool save=true);

private:
	QwtPlotWidgetBase* m_plot;
	QwtTextSettingSheet* m_sheetTitle;
	QBrushSettingSheet* m_brushSettingSheet;

	QPushButton* m_buttonOk;
	QPushButton* m_buttonApply;
	QPushButton* m_buttonCancel;
};
#endif//__QwtBackgroundSettingDlg_h__

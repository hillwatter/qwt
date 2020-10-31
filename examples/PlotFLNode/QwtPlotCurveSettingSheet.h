/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QwtPlotCurveSettingSheet.h
** Created Time: 2011-11-14 11:15:30
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QwtPlotCurveSettingSheet_h__
#define __QwtPlotCurveSettingSheet_h__

#include <QFrame>
#include <qwt_plot_curve.h>

class QLineEdit;
class QComboBox;
class QPenSettingSheet;
class QwtSymbolSettingSheet;

class QwtPlotCurveSettingSheet : public QFrame
{
public:
	QwtPlotCurveSettingSheet(QwtPlotCurve* curve=NULL,
		QWidget* parent=NULL,Qt::WindowFlags f=0);

	const QwtPlotCurve* curve() const;
	void setCurve(QwtPlotCurve* curve);

	void updateSettings(bool save=true);

private:
	void initSytleComboBox();

private:
	QwtPlotCurve* m_curve;

	QLineEdit* m_lineEditName;
	QComboBox* m_comboboxStyle;
	QPenSettingSheet* m_penSettingSheet;
	QwtSymbolSettingSheet* m_symbolSettingSheet;

};
#endif//__QwtPlotCurveSettingSheet_h__
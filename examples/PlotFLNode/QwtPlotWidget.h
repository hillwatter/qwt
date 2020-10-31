/**
* Copyright (C), 2010, Appsoft Tech. Co. Ltd.
* @file: QwtPlotWidget.h
* 
* @brief: XY曲线绘制窗口
* 
* @details: 所绘制的数据满足：
*           至少两列的数据，其中第一列为横轴坐标值，从第二列开始各代表一条曲线的纵轴坐标值，
*           第一行均表示各列的名称。
* 
* @version:  
* 
* @last modified: 2011-9-30 
* 
* @author: 曾先亮
* 
* @modify history:
*	2011-9-30 创建
* 
*/
#ifndef __SRC_COMPONENT_PLOTFLNODE_QWTPLOTWIDGET_H__
#define __SRC_COMPONENT_PLOTFLNODE_QWTPLOTWIDGET_H__

#include "QwtPlotWidgetBase.h"
#include <qwt_plot_curve.h>

class QwtPlotWidget : public QwtPlotWidgetBase
{
	Q_OBJECT
public:
	QwtPlotWidget(QWidget* parent=NULL);
	~QwtPlotWidget()
	{
		clearCurves();
	}

	void Plot(const vector<vector<double>>& data,
		const vector<QString>& col_names,const QString& data_name,bool clean_old=true);
	void clear();

	static bool IsValidData(const vector<vector<double>>& data,
		const vector<QString>& col_names);

public Q_SLOTS:
	virtual void onCurveSetting();
	virtual void onCurveChanged(QwtPlotCurve*);

	virtual void fit();
	virtual void switchToY2();

protected:
	int m_iColor;
	QVector<QwtPlotCurve*> m_curves;
	int m_iY2SelectedCurve;

private:
	inline void clearCurves();

private:
	QAction* curve_setting;
};

void QwtPlotWidget::clearCurves()
{
	for (size_t i = 0; i < m_curves.size(); ++i)
	{
		m_curves[i]->detach();
		delete m_curves[i];
	}

	m_curves.clear();
}

#endif//__SRC_COMPONENT_PLOTFLNODE_QWTPLOTWIDGET_H__


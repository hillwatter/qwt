#include <assert.h>
#include <qwt_symbol.h>
#include "QwtPlotWidget.h"
#include "CurveSettingDlg.h"
#include "SelectCurveDlg.h"
//#include <framework/AppManage.h>

#include <qwt_point_data.h>
#define _Q(s) QStringLiteral(s)

#include <algorithm>
using std::max_element;
using std::min_element;

QwtPlotWidget::QwtPlotWidget(QWidget* parent)
	: QwtPlotWidgetBase(parent)
	, m_iColor(0)
	, m_iY2SelectedCurve(-1)
{
    curve_setting = new QAction(_Q("曲线属性"),this);
	addAction(curve_setting);
	connect(curve_setting,SIGNAL(triggered()),SLOT(onCurveSetting()));
}

void QwtPlotWidget::Plot(const vector<vector<double>>& data,
						 const vector<QString>& col_names,const QString& data_name,
						 bool clean_old)
{
	assert(IsValidData(data,col_names));

	if (clean_old)
	{
		//use new data name
		setTitle(data_name);
		//reset color index
		m_iColor = 0;

		enableAxis(xBottom);
		setAxisTitle(xBottom, col_names[0]);
		setAxisAutoScale(xBottom);
		enableAxis(yLeft);
		setAxisAutoScale(yLeft);
	}

	size_t i = 0;
	QVector<double> x;
	if (data.size() > 1)
	{
		++i; //从第二列开始作为纵轴
		x = QVector<double>::fromStdVector(data[0]);
	}
	else     //针对一列数据
	{
		for (size_t i = 0; i < data[0].size(); ++i)
			x.append(i);
		setAxisTitle(xBottom, "index");
	}

	for (; i < data.size(); ++i)
	{
		QwtPlotCurve* curve = new QwtPlotCurve(col_names[i]);
		curve->setRenderHint( QwtPlotItem::RenderAntialiased );
		curve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
		curve->setPen( QPen((Qt::GlobalColor)(m_iColor%12 + 7)) ); //GlobalColor: red(7)至darkYellow(18)
		++m_iColor;
		curve->attach(this);

		curve->setData(new QwtPointArrayData(x,QVector<double>::fromStdVector(data[i])));
		m_curves.append(curve);
	}

	setZoomBase();
}

void QwtPlotWidget::clear()
{
	clearCurves();
	Init();

	m_iY2SelectedCurve = -1;
}

bool QwtPlotWidget::IsValidData(const vector<vector<double>>& data,
								const vector<QString>& col_names)
{
	if (data.size() != col_names.size())
		return false;

	//至少有一列数据
	if (data.size() < 1)
		return false;

	//每个至少有两个数据
	if (data[0].size() < 2)
		return false;

	//所有数据列的数据个数不多于第一个数据的个数
	for (size_t i = 1; i < data.size(); ++i)
	{
		if (data[i].size() > data[0].size())
			return false;
	}

	return true;
}

void QwtPlotWidget::onCurveSetting()
{
    CurveSettingDlg dlg(m_curves);
	connect(&dlg,SIGNAL(changed(QwtPlotCurve*)),SLOT(onCurveChanged(QwtPlotCurve*)));
	dlg.exec();
}

void QwtPlotWidget::onCurveChanged(QwtPlotCurve* curve)
{
	replot();
}

void QwtPlotWidget::fit()
{
	QwtPlotWidgetBase::fit();

	QwtInterval interval = axisInterval(yLeft);
	setAxisScale(yRight,
		interval.minValue(),interval.maxValue());
	replot();
}

void QwtPlotWidget::switchToY2()
{
    SelectCurveDlg dlg(m_curves,m_iY2SelectedCurve);
	dlg.exec();

	int iSelected = dlg.curveSelected();
	if (iSelected == m_iY2SelectedCurve)
		return;

	if (m_iY2SelectedCurve != -1)
	{
		m_curves[m_iY2SelectedCurve]->setYAxis(yLeft);
		enableAxis(yRight,false);
	}
	m_iY2SelectedCurve = iSelected;

	QwtInterval interval = axisInterval(yLeft);
	setAxisScale(yRight,
		interval.minValue(),interval.maxValue());
	if (m_iY2SelectedCurve != -1)
	{
		m_curves[m_iY2SelectedCurve]->setYAxis(yRight);
		enableAxis(yRight);
	}

	setAxisScale(yLeft,
		interval.minValue(),interval.maxValue());
	replot();
}

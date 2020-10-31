/**
* Copyright (C), 2010, Appsoft Tech. Co. Ltd.
* @file: XYChartWidget.h
* 
* @brief: XY���߻��ƴ���
* 
* @details: �����Ƶ��������㣺
*           �������е����ݣ����е�һ��Ϊ��������ֵ���ӵڶ��п�ʼ������һ�����ߵ���������ֵ��
*           ��һ�о���ʾ���е����ơ�
* 
* @version:  
* 
* @last modified: 2011-08-30 
* 
* @author: ������
* 
* @modify history:
*	2011-08-30 ����
* 
*/
#ifndef __SRC_COMPONENT_PLOTFLNODE_XYCHARTWIDGET_H__
#define __SRC_COMPONENT_PLOTFLNODE_XYCHARTWIDGET_H__

#include "QtGUI/QMouseEvent"
#include "vtkContextView.h"
#include "QVTKWidget.h"
#include <vector>
using std::vector;
using std::string;

class vtkContextView;
class vtkChartXY;

class CXYChartWidget : public QVTKWidget
{
	Q_OBJECT
public:
	CXYChartWidget(QWidget* parent=NULL,Qt::WFlags f=0);
	//virtual ~CXYChartWidget();

	bool Init();
	void Plot(vector<vector<double>> data,vector<string> names);
	bool IsPlotted()
	{
		return m_bPlotted;
	}

	static const double* GetColor(int i);
signals:
	void vtkUpdated();
	void focused(bool flag=true);

protected:
	CXYChartWidget(const CXYChartWidget& other);
	// overloaded mouse press handler
	virtual void mousePressEvent(QMouseEvent* event)
	{
		QVTKWidget::mousePressEvent(event);
		emit vtkUpdated();  //proxy->update();
		emit focused();
	}
	// overloaded mouse move handler
	virtual void mouseMoveEvent(QMouseEvent* event)
	{
		QVTKWidget::mouseMoveEvent(event);
		emit vtkUpdated();  //proxy->update();
	}
	// overloaded mouse release handler
	virtual void mouseReleaseEvent(QMouseEvent* event)
	{
		QVTKWidget::mouseReleaseEvent(event);
		if (event->button() == Qt::RightButton)
			m_view->ResetCamera();
		emit vtkUpdated();  //proxy->update();
	}
	// overload wheel mouse event
	virtual void wheelEvent(QWheelEvent* event)
	{
		QVTKWidget::wheelEvent(event);
		emit vtkUpdated();  //proxy->update();
	}

public slots:
	void selectControl();
	void paneControl();
	void zoomControl();

private:
	bool m_bPlotted;
	vtkContextView* m_view;
	vtkChartXY* m_chart;
};

#endif//__SRC_COMPONENT_PLOTFLNODE_XYCHARTWIDGET_H__
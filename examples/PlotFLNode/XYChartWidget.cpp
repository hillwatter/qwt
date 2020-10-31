#include "vtkDoubleArray.h"
#include "vtkMath.h"
#include "vtkAxis.h"
#include "vtkPlot.h"
#include "vtkChartXY.h"
#include "vtkTable.h"
#include "vtkQtTableView.h"
#include "vtkLookupTable.h"
#include "XYChartWidget.h"

CXYChartWidget::CXYChartWidget(QWidget* parent,Qt::WFlags f)
	: QVTKWidget(parent,f)
	, m_bPlotted(false)
	, m_chart(0x00)
{
}

bool CXYChartWidget::Init()
{
	// Set up my 2D world...
	m_view = vtkContextView::New(); // This contains a chart object
	m_view->SetInteractor(GetInteractor());
	SetRenderWindow(m_view->GetRenderWindow());

	// Add multiple line plots, setting the colors etc
	m_chart = vtkChartXY::New();
	m_view->GetScene()->AddItem(m_chart);

	return true;
}

void CXYChartWidget::Plot(vector<vector<double>> data,vector<string> names)
{
	// 数据列数与名字个数相同
	assert(data.size() == names.size());
	vtkTable* table = vtkTable::New();

	for (size_t i = 0; i != data.size(); ++i)
	{
		vtkDoubleArray* arr = vtkDoubleArray::New();
		if (names[i].size() > 0)
			arr->SetName(names[i].c_str());
		else
			arr->SetName("NONAME");
		table->AddColumn(arr);
	}

	assert(data.size() > 0);
	table->SetNumberOfRows(data[0].size());
	for (size_t i = 0; i != data.size(); ++i)
	{
		for (size_t j = 0; j != data[i].size(); ++j)
			table->SetValue(j,i,data[i][j]);
	}
	table->Update();

	int count = m_chart->GetNumberOfPlots();
	for (int i = 0; i < count; ++i)
		m_chart->RemovePlot(i);

	for (size_t i = 1; i < data.size(); ++i)
	{
		vtkPlot *line = m_chart->AddPlot(vtkChart::LINE);
		line->SetInput(table, 0, i);
		const double* color = GetColor(i-1);
		line->SetColor(color[0],color[1],color[2],255);
	}

	m_bPlotted = true;
	emit vtkUpdated();
}

const double* CXYChartWidget::GetColor(int i)
{
	static const int MAX_COLORS = 10;
	static const double COLORS[MAX_COLORS][3] = 
	{
		255,0,0,     //red
		0,255,0,     //green
		0,0,255,     //blue
		50,90,6,     //
		100,100,100, //
		92,18,240,   //
		240,92,18,   //
		50,90,100,   //
		200,50,50,   //
		0,0,0   //
	};

	if (i <= MAX_COLORS)
		return COLORS[i];
	else
		return COLORS[MAX_COLORS-1];
}

void CXYChartWidget::selectControl()
{
}

void CXYChartWidget::paneControl()
{
}

void CXYChartWidget::zoomControl()
{
	
}
#include <framework/FLNode/InputDataNode.h>
#include <framework/AppManage.h>
#include <framework/DataItem/RowColDataItem.h>
#include <framework/DataItem/TimeDataItem.h>
#include <framework/DataItem/FrequentlyDataItem.h>
#include <common/DataConvert/DataConvert.h>
#include <framework/NodeObject/CharPropElement.h>
#include <framework/NodeObject/IntPropElement.h>
#include <framework/NodeObject/FloatPropElement.h>
#include "QwtPlotActions.h"
#include "QwtPlotWidget.h"
#include "PlotFLNode.h"

PlotFLNode::PlotFLNode()
{
	m_pCenterWidget = NULL;

	SetInputPorts();
	
	QwtPlotActions::getInstance().setup(IAppManage::Instance().GetQMainWindow(),"XY-Chart");
	QwtPlotActions::getInstance().show(false);
}

PlotFLNode::PlotFLNode( PlotFLNode &src):IFLNodePaint( src)
{
	m_pCenterWidget = NULL;

	SetInputPorts();

	//MODIFIED BY Xianliang Zeng
	//From Qt::AutoConnection to Qt::BlockingQueuedConnection
	//For loop
	connect(this,SIGNAL(Run(CDataGroup*)),SLOT(Work(CDataGroup*)),
		Qt::BlockingQueuedConnection);
	/////////////////////////////////////////////////////////////
}

PlotFLNode::~PlotFLNode()
{
	//delete m_pCenterWidget;

	//if (m_pColumnInput != NULL)
	//	m_pColumnInput->Release();
	//if (m_pTimeInput != NULL)
	//	m_pTimeInput->Release();
	//if (m_pFrequentlyInput != NULL)
	//	m_pFrequentlyInput->Release();
}

IFLNode *PlotFLNode::Clone()
{
	return new PlotFLNode(*this);
}

bool PlotFLNode::IsReady( void )
{
	return m_pColumnInput->IsReady()
		&& m_pTimeInput->IsReady()
		&& m_pFrequentlyInput->IsReady();
}

bool PlotFLNode::IsParamValid() 
{
	return true;
}

ec::EC PlotFLNode::PictureToFile(const wstring &strPicFullPath, const QSize &picSize)
{
	if (m_pCenterWidget == NULL)
	{
		return ec::Fail(L"绘图窗口还没创建，没有图形数据");
	}

	::exportDocument(QString::fromStdWString(strPicFullPath),
		m_pCenterWidget,picSize.width(),picSize.height());

	return ec::Success();
}

void PlotFLNode::ClearCentralWidget()
{
	if (m_pCenterWidget != NULL)
		m_pCenterWidget->clear();
}

ec::EC PlotFLNode::RunWorker() 
{
	CDataGroup* pDataGroup = new CDataGroup;

	if (m_pColumnInput->GetData() != NULL)
	{
		CDataGroup* port_group = m_pColumnInput->GetData();
		int count = port_group->GetDataItemNum();
		for (int i = 0; i < count; ++i)
		{
			pDataGroup->AddDataItem(port_group->GetDataItem(i)->Clone());
		}
	}

	if (m_pTimeInput->GetData() != NULL)
	{
		CDataGroup* port_group = NULL;
		//转化为行列数据
		DataConvert::TimeDataToCol(m_pTimeInput->GetData(),&port_group);
		int count = port_group->GetDataItemNum();
		for (int i = 0; i < count; ++i)
		{
			pDataGroup->AddDataItem(port_group->GetDataItem(i)->Clone());
		}

		port_group->Release();
	}

	if (m_pFrequentlyInput->GetData() != NULL)
	{
		CDataGroup* port_group = NULL;
		//转化为行列数据
		DataConvert::FrequentlyDataToCol(m_pFrequentlyInput->GetData(),&port_group);
		int count = port_group->GetDataItemNum();
		for (int i = 0; i < count; ++i)
		{
			pDataGroup->AddDataItem(port_group->GetDataItem(i)->Clone());
		}

		port_group->Release();
	}

	if (pDataGroup->GetDataItemNum() == 0)
		return ec::Fail(L"没有得到数据");

	emit Run(pDataGroup);
	return ec::Success();
}

void PlotFLNode::DeleteFLNodeCentralWidget( void )
{
	QwtPlotActions::getInstance().unregisterWidget(m_pCenterWidget);
	//Deleted by QGraphicsProxyWidget object.
	//delete m_pCenterWidget;
	m_pCenterWidget = 0x00;
}

QWidget* PlotFLNode::GetFLNodeCentralWidget(void)
{
 	if (NULL == m_pCenterWidget)
	{
 		m_pCenterWidget = new QwtPlotWidget();
		m_pCenterWidget->Init();

		QwtPlotActions::getInstance().registerWidget(m_pCenterWidget);
		connect(GetRunOrderWidget(), SIGNAL(focused(bool)),this,SLOT(ShowActions(bool)));
	}

 	return m_pCenterWidget;
}

void PlotFLNode::Work(CDataGroup *pDataGroup)
{
	size_t count = pDataGroup->GetDataItemNum();
	if (count < 1)
	{
		IFLNode::NoticeEndRun(ec::Fail(L"空数据"));
		goto RETURN;
	}

	for (size_t i = 0; i < count; ++i)
	{
		CRowColDataItem<double>* pData = dynamic_cast< CRowColDataItem<double>* >(pDataGroup->GetDataItem(i));
		if (pData == NULL)
		{
			IFLNode::NoticeEndRun(ec::Fail(L"非数值数据"));
			goto RETURN;
		}

		vector< vector<double> > data;
		vector<QString> col_names;
		for (size_t j = 0; j < pData->GetColNum(); ++j)
		{
			CBaseDataItem<double>* col = pData->GetColData(j);
			if (NULL == col)
			{
				IFLNode::NoticeEndRun(ec::Fail(L"空列"));
				goto RETURN;
			}

			data.push_back(col->GetContain());
			if (col->GetDataName().size() > 0)
				col_names.push_back(QString::fromStdWString(col->GetDataName()));
			else
				col_names.push_back(QString::fromStdWString(col->GetDataDesc()));
		}

		if (!QwtPlotWidget::IsValidData(data,col_names))
		{
			IFLNode::NoticeEndRun(ec::Fail(L"数据不符合XYChart数据要求"));
			goto RETURN;
		}

		//第一组数据需要清理画布：i==0
		m_pCenterWidget->Plot(data,
			col_names,QString::fromStdWString(pData->GetDataItemDesc()),i==0);
	}

RETURN:
	pDataGroup->Release();
}

void PlotFLNode::SetInputPorts()
{
	m_pColumnInput = new IInputDataNode(this, DataNodeType::DT_COLUMN);
	AddInputDataNode(m_pColumnInput);	
	m_pTimeInput = new IInputDataNode(this, DataNodeType::DT_TIME);
	AddInputDataNode(m_pTimeInput);	
	m_pFrequentlyInput = new IInputDataNode(this, DataNodeType::DT_FREQUENTLY);
	AddInputDataNode(m_pFrequentlyInput);
}

void PlotFLNode::ShowActions(bool on)
{
	QwtPlotActions& actions = QwtPlotActions::getInstance();
	if (on)
		actions.connectWidget(m_pCenterWidget);

	actions.show(on);
}

extern "C" APP_Export PlotFLNode *plotFLNode()
{
	static PlotFLNode _obj;
	return &_obj;
}
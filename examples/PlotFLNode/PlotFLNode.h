/**
* Copyright (C), 2010, Appsoft Tech. Co. Ltd.
* @file: ProductInfo.h
* 
* @brief: ��ͼ�ڵ�
* 
* @details: 
* 
* @version:  
* 
* @last modified: 2011-08-02 
* 
* @author: ChiYaNan( CYN)
* 
* @modify history: �޸���ʷ�б�(����)
* 
*/

#ifndef __SRC_COMPONENT_PLOTFLNODE_PLOTFLNODE_H__
#define __SRC_COMPONENT_PLOTFLNODE_PLOTFLNODE_H__

#include <string>
using std::wstring;
#include <framework/FLNode/FLNodePaint.h>
#include <framework/DataItem/DataGroup.h>

class QToolBar;
class QLineEdit;
class QwtPlotWidget;

class PlotFLNode : public IFLNodePaint
{
	Q_OBJECT
public:
	PlotFLNode();
	PlotFLNode(PlotFLNode &src);
	~PlotFLNode();

	virtual IFLNode *Clone();
	virtual bool IsReady();
	virtual bool IsParamValid(); 

	virtual ec::EC PictureToFile(const wstring &strPicFullPath, const QSize &picSize);

protected:
	virtual void ClearCentralWidget();
	virtual ec::EC RunWorker();
	virtual void DeleteFLNodeCentralWidget(); 
	virtual QWidget *GetFLNodeCentralWidget();

private:
	void SetInputPorts();

signals:
	void Run(CDataGroup* pDataGroup);

private slots:
	void Work(CDataGroup *pDataGroup);
	void ShowActions(bool on);

private:
	QwtPlotWidget	    *m_pCenterWidget;		//���Ŀؼ�
	IInputDataNode		*m_pColumnInput;		//��������
	IInputDataNode		*m_pTimeInput;		    //ʱ������
	IInputDataNode		*m_pFrequentlyInput;    //Ƶ������
};

#endif // __SRC_COMPONENT_PLOTFLNODE_PLOTFLNODE_H__

/**
* Copyright (C), 2010, Appsoft Tech. Co. Ltd.
* @file: QwtPlotWidget.h
* 
* @brief: 
* 
* @details: 
* 
* @version:  
* 
* @last modified: 2011-10-10 
* 
* @author: 曾先亮
* 
* @modify history:
*	2011-10-10 创建
* 
*/
#ifndef __SRC_COMPONENT_PLOTFLNODE_QWTPLOTWIDGETBASE_H__
#define __SRC_COMPONENT_PLOTFLNODE_QWTPLOTWIDGETBASE_H__

#include <vector>
using std::vector;
#include <qwt_plot.h>
#include <qwt_plot_renderer.h>
#include "qwt_plot_my.h"

#include <QMenu>
#include <QAction>
#include <QActionGroup>



inline void exportDocument(const QString& fileName,
						   QwtPlot* plot,int width,int height)
{
    QwtPlotRenderer renderer;

    // flags to make the document look like the widget
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardBackground, false );
    renderer.setLayoutFlag( QwtPlotRenderer::FrameWithScales, true );
	
	//Add FACTOR, 2012-3-13
	//乘以FACTOR之后才得到要求的图像分辨率
#define FACTOR  3.0/10.04
    renderer.renderDocument(plot, fileName,
		QSizeF(width*FACTOR, height*FACTOR), 85);
#undef FACTOR
}

class QwtPlotCurve;
class QwtPlotGrid;
class QwtSignTextMarker;
class QTextSignEdit;
class QwtTextPosition;

class QwtPlotWidgetBase : public QwtPlot
{
	Q_OBJECT
friend class QwtAxisSettingDlg;
public:
	QwtPlotWidgetBase(QWidget* parent=NULL,bool showLegend=true);
	virtual ~QwtPlotWidgetBase();

	virtual bool Init();
	virtual void clear();
	void setZoomBase()
	{
		m_zoomer->setZoomBase();
	}

	void setAxisTitleColor(const QColor& c);
	void setAxisTitleFont(const QFont& f);

public Q_SLOTS:
	void enableSelectMode(bool);
	void enablePaneMode(bool);
	void enableZoomMode(bool);
	
	virtual void fit();
	virtual void switchToY2();
	virtual void setAxisActive();
	
	void showGrid(bool);

	void onSavePicture();
	void onBgSetting();
	void onAxisSetting();

	/**
	* @brief显示文本编辑框
	*
	* @param
	*
	* @return
	*/
	void ShowTextEdit();

	/**
	* @brief 添加文本标注
	*
	* @param
	*
	* @return
	*/
	void AddTextSign();

	/**
	* @brief 启用禁用添加文本标注状态
	*
	* @param
	*
	* @return
	*/
	void EnableTextSign(bool on);

protected:
	virtual void initContextMenu();
    //virtual void contextMenuEvent (QContextMenuEvent* event);

	virtual void mousePressEvent ( QMouseEvent * event );

private:
	QwtPlotWidgetBase(const QwtPlotWidgetBase& other);
	QwtPlotWidgetBase& operator=(const QwtPlotWidgetBase& other);

	/**
	* @brief 查找并选择文本注释
	*
	* @param pos 鼠标的光标所在的位置（基于curves()控件 的位置）
	*
	* @return
	*/
	void OnSelectText(const QPoint &pos);

protected:
	QwtPlotGrid* m_grid;
	MyPlotPanner* m_panner;
	MyPlotZoomer* m_zoomer;
	MyPlotMagnifier* m_magnifier;

	QAction* m_actionBgSetting;
	QAction* m_actionAxisSetting;

	QPoint m_curSignPos;	//当前光标的位置
	QTextSignEdit *m_textSignEdit;	 //标注添加类
	std::vector<QwtSignTextMarker *> m_signedTextVec;	//标注存储容器
	bool m_bTextSign;	//是否添加标注，
	Axis m_textXaxi;	//标注的x轴
	Axis m_textYaxi;	//标注的y轴

};

#endif//__SRC_COMPONENT_PLOTFLNODE_QWTPLOTWIDGETBASE_H__


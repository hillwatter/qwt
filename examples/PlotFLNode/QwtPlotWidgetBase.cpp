#include <assert.h>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_text.h>

#include "QwtBackgroundSettingDlg.h"
#include "QwtAxisSettingDlg.h"
#include "ActiveAxisDlg.h"
#include "QwtPlotWidgetBase.h"
//#include <framework/AppManage.h>

#include "QTextSignEdit.h"
#include "QwtSignTextMarker.h"
#include <QMouseEvent>
#define _Q(s) QStringLiteral(s)

QwtPlotWidgetBase::QwtPlotWidgetBase(QWidget* parent,bool showLegend)
	: QwtPlot(parent)
	, m_grid(NULL)
	, m_panner(NULL)
	, m_zoomer(NULL)
	, m_magnifier(NULL)
{
//    canvas()->setLineWidth(1);
//    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain);
    QPalette canvasPalette(Qt::white);
    canvasPalette.setColor(QPalette::Foreground, QColor(133, 190, 232));
    canvas()->setPalette(canvasPalette);

	m_panner = new MyPlotPanner(canvas());
	m_panner->setEnabled(false);
	m_zoomer = new MyPlotZoomer(canvas());	m_grid = new QwtPlotGrid;
	m_grid->enableX(true);
	m_grid->enableXMin(true);
	m_grid->enableY(true);
	m_grid->attach(this);
	m_grid->setVisible(false);
	m_zoomer->setEnabled(false);
    // zoom in/out with the wheel
    m_magnifier = new MyPlotMagnifier(canvas());
	if (showLegend)
		insertLegend(new QwtLegend(), QwtPlot::RightLegend);

	m_magnifier->setZoomInKey(Qt::Key_Plus,Qt::NoModifier);
	m_magnifier->setZoomOutKey(Qt::Key_Minus,Qt::NoModifier);

	m_textSignEdit = new QTextSignEdit(canvas());
	m_textSignEdit->hide();
	m_bTextSign = false;
	m_textXaxi = xBottom;
	m_textYaxi = yLeft;

	initContextMenu();


}

QwtPlotWidgetBase::~QwtPlotWidgetBase()
{
	delete m_grid;
	delete m_panner;
	delete m_zoomer;
	delete m_magnifier;

	m_signedTextVec.clear();
}

bool QwtPlotWidgetBase::Init()
{
	setTitle("");
	enableAxis(xBottom,false);
	enableAxis(yLeft,false);

    m_grid->setMajorPen(QPen(Qt::gray,0));
    m_grid->setMinorPen(QPen(Qt::black,0,Qt::DotLine));

	return true;
}

void QwtPlotWidgetBase::clear()
{
}

void QwtPlotWidgetBase::setAxisTitleColor(const QColor& c)
{
	QwtText t = axisTitle(xBottom);
	t.setColor(c);
	setAxisTitle(xBottom, t);
	
	t = axisTitle(yLeft);
	t.setColor(c);
	setAxisTitle(yLeft, t);
}

void QwtPlotWidgetBase::setAxisTitleFont(const QFont& f)
{
	QwtText t = axisTitle(xBottom);
	t.setFont(f);
	setAxisTitle(xBottom, t);
	
	t = axisTitle(yLeft);
	t.setFont(f);
	setAxisTitle(yLeft, t);
}

void QwtPlotWidgetBase::enableSelectMode(bool on)
{
	//if (m_panner)
	//	m_panner->setEnabled(false);
	//if (m_zoomer)
	//	m_zoomer->setEnabled(false);

	if (on)
		canvas()->setCursor(QCursor(Qt::PointingHandCursor));
}

void QwtPlotWidgetBase::enablePaneMode(bool on)
{
	if (m_panner)
		m_panner->setEnabled(on);

	if (on)
		canvas()->setCursor(QCursor(Qt::SizeAllCursor));
}

void QwtPlotWidgetBase::enableZoomMode(bool on)
{
	if (m_zoomer)
		m_zoomer->setEnabled(on);
}

void QwtPlotWidgetBase::fit()
{
	if (m_zoomer)
		m_zoomer->zoom(0);
}

void QwtPlotWidgetBase::switchToY2()
{
}

void QwtPlotWidgetBase::setAxisActive()
{
	bool x_active = m_panner->isAxisEnabled(xBottom);
	bool yLeft_active = m_panner->isAxisEnabled(yLeft);
	bool yRight_active = m_panner->isAxisEnabled(yRight);

	ActiveAxisDlg dlg(x_active,yLeft_active,yRight_active,
        0x00);
	dlg.exec();

	m_panner->setAxisEnabled(xTop,x_active);
	m_panner->setAxisEnabled(xBottom,x_active);
	m_panner->setAxisEnabled(yLeft,yLeft_active);
	m_panner->setAxisEnabled(yRight,yRight_active);

	m_magnifier->setAxisEnabled(xTop,x_active);
	m_magnifier->setAxisEnabled(xBottom,x_active);
	m_magnifier->setAxisEnabled(yLeft,yLeft_active);
	m_magnifier->setAxisEnabled(yRight,yRight_active);
}

void QwtPlotWidgetBase::showGrid(bool show)
{	
	m_grid->setVisible(show);
	replot();
}

void QwtPlotWidgetBase::onSavePicture()
{
	static QString recentDir = "D:\\";
	QString fileName = QFileDialog::getSaveFileName(
        0x00,
        _Q("图片另存为"),recentDir,_Q("Image Files (*.png *.jpg *.bmp)"));

	if (fileName.isEmpty())
		return;

	exportDocument(fileName,this,800,600);
	recentDir = fileName;
}

void QwtPlotWidgetBase::onBgSetting()
{
	QwtBackgroundSettingDlg dlg(this,
        NULL);
	dlg.exec();
}

void QwtPlotWidgetBase::onAxisSetting()
{
    QwtAxisSettingDlg dlg(this);
	dlg.exec();
}

void QwtPlotWidgetBase::initContextMenu()
{
	//添加字体工具栏显示 By JSL(Jia ShaoLing)
    QAction* actionFontTool = new QAction(_Q("字体工具栏"),this);
	addAction(actionFontTool);
	actionFontTool->setChecked(true);
	connect(actionFontTool,SIGNAL(triggered()),m_textSignEdit,SLOT(OnShowToolBar()));

	//ADDED 2012-3-13
    QAction* actionSaveAs = new QAction(_Q("图片另存"),this);
	addAction(actionSaveAs);
	connect(actionSaveAs,SIGNAL(triggered()),SLOT(onSavePicture()));
	///////////////////////////////////

    m_actionBgSetting = new QAction(_Q("背景设置"), this);
	addAction(m_actionBgSetting);
    m_actionAxisSetting = new QAction(_Q("坐标设置"), this);
	addAction(m_actionAxisSetting);

	QAction* sep = new QAction(this);
	sep->setSeparator(true);
	addAction(sep);

	setContextMenuPolicy(Qt::ActionsContextMenu);

	connect(m_actionBgSetting,SIGNAL(triggered()),SLOT(onBgSetting()));
	connect(m_actionAxisSetting,SIGNAL(triggered()),SLOT(onAxisSetting()));
}

//void QwtPlotWidgetBase::contextMenuEvent (QContextMenuEvent* event)
//{
//	QMenu* menu = new QMenu(this);
//	menu->addActions(actions());
//    menu->exec(event->pos());
//}


void QwtPlotWidgetBase::EnableTextSign(bool on)
{
	m_bTextSign = on;
}

void QwtPlotWidgetBase::mousePressEvent ( QMouseEvent * event )
{
	QwtPlot::mousePressEvent(event);

	QPoint eventPos = event->pos();

	if (false == canvas()->geometry().contains(eventPos))
	{
		return;
	}

	if (m_textSignEdit->isVisible())
	{
		AddTextSign();
		return;
	}

	if (false == m_bTextSign)
	{
		return;
	}

	m_curSignPos = canvas()->mapFromParent(eventPos);

	if (event->button() == Qt::LeftButton)
	{	
		m_textSignEdit->clear();
		OnSelectText(m_curSignPos);
	}

}

void QwtPlotWidgetBase::OnSelectText(const QPoint &pos)
{
	int desIndex = -1;


	QRect textRect;

	for (std::vector<QwtSignTextMarker* >::size_type i = 0;
		i < m_signedTextVec.size(); ++i)
	{
		QwtSignTextMarker *pTextMarker = m_signedTextVec[i];
		const QSizeF textSize = pTextMarker->text().textSize();


		double posX = transform(m_textXaxi, pTextMarker->xValue());
		double posY = transform(m_textYaxi,pTextMarker->yValue());

		QRect rect(posX, posY, textSize.width(),textSize.height());

		if (rect.contains(pos))
		{
			textRect = rect;
			desIndex = i;

			break;
		}
	}

	if ((-1 != desIndex )&& (desIndex < m_signedTextVec.size()))
	{
		QwtSignTextMarker *pTextMarker = m_signedTextVec[desIndex];
		pTextMarker->detach();

		QwtText qwtstrTex = pTextMarker->text();
		m_textSignEdit->SetFont(qwtstrTex.font());		
		m_textSignEdit->setText(qwtstrTex.text());
		m_curSignPos = textRect.topLeft();


		delete pTextMarker;
		pTextMarker = 0x00;

		m_signedTextVec.erase(m_signedTextVec.begin() + desIndex);

		replot();
	}

	ShowTextEdit();	

}

void QwtPlotWidgetBase::ShowTextEdit()
{
	if (0x00 == m_textSignEdit)
	{
		m_textSignEdit = new QTextSignEdit(this);
	}

	m_textSignEdit->move(m_curSignPos.x()-3, m_curSignPos.y() -2);
	m_textSignEdit->show();
	m_textSignEdit->setFocus();

}

void QwtPlotWidgetBase::AddTextSign()
{
	if (0x00 == m_textSignEdit)
	{
		return;
	}

	QString textstr = m_textSignEdit->toPlainText();
	if (textstr.isEmpty())
	{
		m_textSignEdit->close();
		return;
	}

	QPoint pos = m_curSignPos;

	//创建文本标记
	double realPosX = invTransform(m_textXaxi,pos.x());
	double realPosy = invTransform(m_textYaxi,pos.y());

	QwtSignTextMarker *pMarker = new QwtSignTextMarker();
	pMarker->setYAxis(m_textYaxi);
	QwtText qwtstr(textstr);
	qwtstr.setFont(m_textSignEdit->GetFont());
	pMarker->setText(qwtstr);
	pMarker->setValue(realPosX,realPosy);
	pMarker->attach(this);
	pMarker->SetRect(m_textSignEdit->frameGeometry());

	m_signedTextVec.push_back(pMarker);

	replot();

	m_textSignEdit->close();
}

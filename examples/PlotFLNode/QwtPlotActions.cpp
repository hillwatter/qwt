#include "QwtPlotWidgetBase.h"
#include "QwtPlotActions.h"
#define _Q(s) QStringLiteral(s)


bool QwtPlotActions::setup(QMainWindow* mw,const QString& name)
{
	static bool setupped = false;
	if (setupped)
		return false;
	else
		setupped = true;

	if (mw == NULL)
		return false;

	_ACTION_STATE init;
	QActionGroup* group = new QActionGroup(mw);
    QAction* select = new QAction(QIcon("./img/component/PlotIcon/control/select.png"),_Q("选择"),group);
	manageAction(select,init);
	addActionConnect(select, SIGNAL(toggled(bool)),SLOT(enableSelectMode(bool)));
	select->setCheckable(true);
    QAction* pane = new QAction(QIcon("./img/component/PlotIcon/control/pane.png"),_Q("平移"),group);
	manageAction(pane,init);
	addActionConnect(pane, SIGNAL(toggled(bool)),SLOT(enablePaneMode(bool)));
	pane->setCheckable(true);
    QAction* zoom = new QAction(QIcon("./img/component/PlotIcon/control/zoom.png"),_Q("缩放"),group);
	manageAction(zoom,init);
	addActionConnect(zoom, SIGNAL(toggled(bool)),SLOT(enableZoomMode(bool)));
	zoom->setCheckable(true);

	QAction* separator = new QAction(group);
	separator->setSeparator(true);

    QAction* fit = new QAction(QIcon("./img/component/PlotIcon/control/fit.png"),_Q("还原"),group);
	manageAction(fit,init);
	addActionConnect(fit,SIGNAL(triggered()),SLOT(fit()));

    QAction* y2 = new QAction(QIcon("./img/component/PlotIcon/control/y2.png"),_Q("y2"),group);
	manageAction(y2,init);
	addActionConnect(y2,SIGNAL(triggered()),SLOT(switchToY2()));

	QAction* active_axis = new QAction(QIcon("./img/component/PlotIcon/control/active_axis.png"),
        _Q("active_axis"),group);
	manageAction(active_axis,init);
	addActionConnect(active_axis,SIGNAL(triggered()),SLOT(setAxisActive()));

	separator = new QAction(group);
	separator->setSeparator(true);

    QAction* grid = new QAction(QIcon("./img/component/PlotIcon/view/grid.bmp"),_Q("网格"),mw);
	manageAction(grid,init);
	addActionConnect(grid, SIGNAL(toggled(bool)),SLOT(showGrid(bool)));
	grid->setCheckable(true);

	toolbar = mw->addToolBar(name);
	toolbar->addActions(group->actions());
	toolbar->addAction(grid);

	//添加文字标注按钮
	toolbar->addSeparator();
    QAction *pTextSign = toolbar->addAction(_Q("A"));
	QFont font;
	font.setPointSize(16);
	font.setBold(true);
	pTextSign->setFont(font);
	pTextSign->setCheckable(true);	

	addActionConnect(pTextSign ,SIGNAL(toggled(bool)), SLOT(EnableTextSign(bool)));

	return true;
}

void QwtPlotActions::show(bool on)
{
	toolbar->setVisible(on);
}

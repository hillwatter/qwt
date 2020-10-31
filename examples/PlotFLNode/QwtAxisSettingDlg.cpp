/****************************************************************************
** Last Modified: 2011-11-10-001
**
** File Name: QwtAxisSettingDlg.cpp
** Created Time: 2011-11-10 14:42:28
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPenSettingSheet.h>
#include "QwtTextSettingSheet.h"
#include "QwtAxisSettingDlg.h"

#include <qwt_scale_widget.h>
#include <qwt_plot_grid.h>
#define _Q(s) QStringLiteral(s)

QwtAxisSettingDlg::QwtAxisSettingDlg(QwtPlotWidgetBase* plot,
									 QWidget* parent,Qt::WindowFlags f)
	: QDialog(parent,f)
	, m_plot(plot)
{
	assert(m_plot != NULL);
    setWindowTitle(_Q("坐标设置"));

	QToolBar* bar = new QToolBar(this);
	m_actionsAxis = new QActionGroup(bar);
	QAction* sep = NULL;
	QAction* axis = NULL;

    axis = new QAction(_Q("xTop"),m_actionsAxis);
	axis->setCheckable(true);
	m_action2axis[axis] = QwtPlot::xTop;
	sep = new QAction(m_actionsAxis);
	sep->setSeparator(true);
    axis = new QAction(_Q("xBottom"),m_actionsAxis);
	axis->setCheckable(true);
	axis->setChecked(true);
	m_current_axis = QwtPlot::xBottom;
	m_action2axis[axis] = QwtPlot::xBottom;
	sep = new QAction(m_actionsAxis);
	sep->setSeparator(true);
    axis = new QAction(_Q("yLeft"),m_actionsAxis);
	axis->setCheckable(true);
	m_action2axis[axis] = QwtPlot::yLeft;
	sep = new QAction(m_actionsAxis);
	sep->setSeparator(true);
    axis = new QAction(_Q("yRight"),m_actionsAxis);
	axis->setCheckable(true);
	m_action2axis[axis] = QwtPlot::yRight;
	
	bar->addActions(m_actionsAxis->actions());

    m_checkBoxShowAxis = new QCheckBox(_Q("显示"));

	QHBoxLayout* checkbox_axisbar = new QHBoxLayout;
	checkbox_axisbar->addWidget(m_checkBoxShowAxis);
	checkbox_axisbar->addWidget(bar,false,Qt::AlignCenter);

	QFont font;
	font.setBold(true);

    QLabel* label = new QLabel(_Q("标题"));
	label->setFont(font);
	QFrame* line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	QHBoxLayout* label_line = new QHBoxLayout;
	label_line->addWidget(label);
	label_line->addWidget(line,true);
	m_sheetTitle = new QwtTextSettingSheet();
	QVBoxLayout* title_block = new QVBoxLayout;
	title_block->addLayout(label_line);
	title_block->addWidget(m_sheetTitle);

    label = new QLabel(_Q("标签"));
	label->setFont(font);
	line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	label_line = new QHBoxLayout;
	label_line->addWidget(label);
	label_line->addWidget(line,true);
	//label旋转度
	QHBoxLayout* label_edit = new QHBoxLayout;
    label_edit->addWidget(new QLabel(_Q("旋转：")));
	m_lineEditLabelRotation = new QLineEdit;
	label_edit->addWidget(m_lineEditLabelRotation);
	//label text setting sheet
	m_sheetLabel = new QwtTextSettingSheet(QwtText(),0,0,false);
	//label block
	QVBoxLayout* label_block = new QVBoxLayout;
	label_block->addLayout(label_line);
	label_block->addLayout(label_edit);
	label_block->addWidget(m_sheetLabel);

	//spacing between title block and label block
	int spacing = 20;
	//title and label blocks
	QHBoxLayout* title_label = new QHBoxLayout;
	title_label->addLayout(title_block);
	title_label->addSpacing(spacing);
	title_label->addLayout(label_block);

    label = new QLabel(_Q("网格"));
	label->setFont(font);
	line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	label_line = new QHBoxLayout;
	label_line->addWidget(label);
	label_line->addWidget(line,true);
    m_checkBoxMajGridline = new QCheckBox(_Q("显示主刻度网格线"));
	m_sheetMajGridline = new QPenSettingSheet;
	QVBoxLayout* check_pen_maj = new QVBoxLayout;
	check_pen_maj->addWidget(m_checkBoxMajGridline);
	check_pen_maj->addWidget(m_sheetMajGridline,0);
    m_checkBoxMinGridline = new QCheckBox(_Q("显示次刻度网格线"));
	m_sheetMinGridline = new QPenSettingSheet;
	QVBoxLayout* check_pen_min = new QVBoxLayout;
	check_pen_min->addWidget(m_checkBoxMinGridline);
	check_pen_min->addWidget(m_sheetMinGridline,0);
	QHBoxLayout* gridlines = new QHBoxLayout;
	gridlines->addLayout(check_pen_maj);
	gridlines->setSpacing(spacing);
	gridlines->addLayout(check_pen_min);
	//make up the wholoe gridlines setting block
	QVBoxLayout* gridline_block = new QVBoxLayout;
	gridline_block->addLayout(label_line);
	gridline_block->addLayout(gridlines);

    m_buttonOk = new QPushButton(_Q("确定"));
	m_buttonOk->setDefault(true);
    m_buttonApply = new QPushButton(_Q("应用"));
    m_buttonCancel = new QPushButton(_Q("取消"));
	QHBoxLayout* buttons = new QHBoxLayout;
	buttons->addWidget(m_buttonOk);
	buttons->addWidget(m_buttonApply);
	buttons->addWidget(m_buttonCancel);

	QVBoxLayout* whole = new QVBoxLayout;
	whole->addLayout(checkbox_axisbar);
	whole->addLayout(title_label);
	whole->addLayout(gridline_block);
	whole->addLayout(buttons);
	setLayout(whole);

	//connects
	connect(m_actionsAxis,SIGNAL(triggered(QAction*)),SLOT(onAxisChanged(QAction*)));
	connect(m_checkBoxMajGridline,SIGNAL(stateChanged(int)),m_sheetMajGridline,SLOT(setEnabled(bool)));
	connect(m_checkBoxMinGridline,SIGNAL(stateChanged(int)),m_sheetMinGridline,SLOT(setEnabled(bool)));
	connect(m_buttonOk,SIGNAL(clicked()),SLOT(onOK()));
	connect(m_buttonApply,SIGNAL(clicked()),SLOT(onApply()));
	connect(m_buttonCancel,SIGNAL(clicked()),SLOT(close()));

	updateSettings(false);
}

void QwtAxisSettingDlg::onAxisChanged(QAction* action)
{
	if (m_action2axis.count(action) < 1)
		return;

	m_current_axis = m_action2axis[action];
	updateSettings(false);
}

void QwtAxisSettingDlg::onOK()
{
	if (!validateSettings())
		return;

	updateSettings(true);
	close();
}

void QwtAxisSettingDlg::onApply()
{
	if (!validateSettings())
		return;

	updateSettings(true);
}

bool QwtAxisSettingDlg::validateSettings()
{
	//Check values in widgets
	bool ok = false;
	double rotation = m_lineEditLabelRotation->text().toDouble(&ok);
	if (!ok)
	{
		QMessageBox::information(m_lineEditLabelRotation,
            _Q("提示"),_Q("旋转是标签数字与其所依附的坐标轴夹角"));
		m_lineEditLabelRotation->setFocus();
		m_lineEditLabelRotation->setSelection(0,
			m_lineEditLabelRotation->text().length());
	}

	return ok;
}

void QwtAxisSettingDlg::updateSettings(bool save)
{
	QwtScaleWidget* axis_widget = m_plot->axisWidget(m_current_axis);
	if (axis_widget == NULL)
		return;

	if (save)
	{
		// show or not
		m_plot->enableAxis(m_current_axis,
			m_checkBoxShowAxis->checkState());
		// title
		axis_widget->setTitle(m_sheetTitle->text());
		// label
		bool ok = false;
		double rotation = m_lineEditLabelRotation->text().toDouble(&ok);
		axis_widget->setLabelRotation(rotation);
		QwtText text = m_sheetLabel->text();
		axis_widget->setFont(text.font());
		// gridlines
		updateGridlineSettings(save);

		//update to plot widget
		m_plot->replot();
	}
	else
	{
		if (m_plot->axisEnabled(m_current_axis))
			m_checkBoxShowAxis->setCheckState(Qt::Checked);
		else
			m_checkBoxShowAxis->setCheckState(Qt::Unchecked);
		m_sheetTitle->setText(axis_widget->title());
		m_lineEditLabelRotation->setText("0");
		//	axis_widget->
		QwtText text;
		text.setFont(axis_widget->font());
		m_sheetLabel->setText(text);
		updateGridlineSettings(save);
	}
}

void QwtAxisSettingDlg::updateGridlineSettings(bool save)
{
	if (m_plot->m_grid == NULL)
		return;

	if (save)
	{
		if (m_current_axis == QwtPlot::xTop || m_current_axis == QwtPlot::xBottom)
		{
			m_plot->m_grid->enableX(m_checkBoxMajGridline->checkState());
            m_plot->m_grid->setMajorPen(m_sheetMajGridline->pen());

			m_plot->m_grid->enableXMin(m_checkBoxMinGridline->checkState());
            m_plot->m_grid->setMinorPen(m_sheetMinGridline->pen());
		}
		else
		{
			m_plot->m_grid->enableY(m_checkBoxMajGridline->checkState());
            m_plot->m_grid->setMajorPen(m_sheetMajGridline->pen());

			m_plot->m_grid->enableYMin(m_checkBoxMinGridline->checkState());
            m_plot->m_grid->setMinorPen(m_sheetMinGridline->pen());
		}
	}
	else
	{
		if (m_current_axis == QwtPlot::xTop || m_current_axis == QwtPlot::xBottom)
		{
			if (m_plot->m_grid->xEnabled())
				m_checkBoxMajGridline->setCheckState(Qt::Checked);
			else
				m_checkBoxMajGridline->setCheckState(Qt::Unchecked);
            m_sheetMajGridline->setPen(m_plot->m_grid->majorPen());

			if (m_plot->m_grid->xMinEnabled())
				m_checkBoxMinGridline->setCheckState(Qt::Checked);
			else
				m_checkBoxMinGridline->setCheckState(Qt::Unchecked);
            m_sheetMinGridline->setPen(m_plot->m_grid->minorPen());
		}
		else
		{
			if (m_plot->m_grid->yEnabled())
				m_checkBoxMajGridline->setCheckState(Qt::Checked);
			else
				m_checkBoxMajGridline->setCheckState(Qt::Unchecked);
            m_sheetMajGridline->setPen(m_plot->m_grid->majorPen());

			if (m_plot->m_grid->yMinEnabled())
				m_checkBoxMinGridline->setCheckState(Qt::Checked);
			else
				m_checkBoxMinGridline->setCheckState(Qt::Unchecked);
            m_sheetMinGridline->setPen(m_plot->m_grid->minorPen());
		}
	}
}

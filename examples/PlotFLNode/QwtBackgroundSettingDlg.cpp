/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QwtBackgroundSettingDlg.cpp
** Created Time: 2011-11-14 9:25:41
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <assert.h>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBrushSettingSheet.h>
#include "QwtTextSettingSheet.h"
#include "QwtBackgroundSettingDlg.h"
#define _Q(s) QStringLiteral(s)

QwtBackgroundSettingDlg::QwtBackgroundSettingDlg(QwtPlotWidgetBase* plot,
												 QWidget* parent,
												 Qt::WindowFlags f)
	: QDialog(parent,f)
	, m_plot(plot)
{
	assert(m_plot != NULL);
    setWindowTitle(_Q("背景设置"));

	m_sheetTitle = new QwtTextSettingSheet;
	m_brushSettingSheet = new QBrushSettingSheet;

	QVBoxLayout* whole = new QVBoxLayout;

    QLabel* label = new QLabel(_Q("标题"));
	QFont font;
	font.setBold(true);
	label->setFont(font);
	QFrame* line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	QHBoxLayout* label_line = new QHBoxLayout;
	label_line->addWidget(label);
	label_line->addWidget(line,true);
	whole->addLayout(label_line);
	whole->addWidget(m_sheetTitle);

    label = new QLabel(_Q("画刷"));
	label->setFont(font);
	line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	label_line = new QHBoxLayout;
	label_line->addWidget(label);
	label_line->addWidget(line,true);
	whole->addLayout(label_line);
	whole->addWidget(m_brushSettingSheet);

    m_buttonOk = new QPushButton(_Q("确定"));
	m_buttonOk->setDefault(true);
    m_buttonApply = new QPushButton(_Q("应用"));
    m_buttonCancel = new QPushButton(_Q("取消"));
	QHBoxLayout* buttons = new QHBoxLayout;
	buttons->addWidget(m_buttonOk);
	buttons->addWidget(m_buttonApply);
	buttons->addWidget(m_buttonCancel);
	whole->addLayout(buttons);

	setLayout(whole);
	
	//connects
	connect(m_buttonOk,SIGNAL(clicked()),SLOT(onOK()));
	connect(m_buttonApply,SIGNAL(clicked()),SLOT(onApply()));
	connect(m_buttonCancel,SIGNAL(clicked()),SLOT(close()));
	
	updateSettings(false);
}

void QwtBackgroundSettingDlg::onOK()
{
	if (!validateSettings())
		return;

	updateSettings(true);
	close();
}

void QwtBackgroundSettingDlg::onApply()
{
	if (!validateSettings())
		return;

	updateSettings(true);
}

bool QwtBackgroundSettingDlg::validateSettings()
{
	//Check values in widgets
	bool ok = false;
	
	ok = true;
	if (!ok)
	{
		QMessageBox::information(this,
            _Q("提示"),_Q(""));
	}

	return ok;
}

void QwtBackgroundSettingDlg::updateSettings(bool save)
{
	assert(m_plot != NULL);
	if (save)
	{
		// title
		m_plot->setTitle(m_sheetTitle->text());
		// color
		m_plot->setCanvasBackground(m_brushSettingSheet->brush());

		//update to plot widget
		m_plot->replot();
	}
	else
	{
		m_sheetTitle->setText(m_plot->title());
		m_brushSettingSheet->setBrush(m_plot->canvasBackground());
	}
}

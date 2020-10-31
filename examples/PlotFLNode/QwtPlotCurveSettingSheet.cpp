/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QwtPlotCurveSettingSheet.cpp
** Created Time: 2011-11-14 11:16:05
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <assert.h>
#include <QTabWidget>
#include <QToolBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPenSettingSheet.h>
#include "QwtSymbolSettingSheet.h"
#include "QwtPlotCurveSettingSheet.h"
#define _Q(s) QStringLiteral(s)

QwtPlotCurveSettingSheet::QwtPlotCurveSettingSheet(QwtPlotCurve* curve,
												   QWidget* parent,Qt::WindowFlags f)
	: QFrame(parent,f)
{
	m_lineEditName = new QLineEdit;
	m_comboboxStyle = new QComboBox;
	initSytleComboBox();
	m_penSettingSheet = new QPenSettingSheet;
	m_symbolSettingSheet = new QwtSymbolSettingSheet;

	QVBoxLayout* vbox = new QVBoxLayout;
	QHBoxLayout* row_box = new QHBoxLayout;
    row_box->addWidget(new QLabel(_Q("名称：")));
	row_box->addWidget(m_lineEditName);
	vbox->addLayout(row_box);

	row_box = new QHBoxLayout;
    row_box->addWidget(new QLabel(_Q("类型：")));
	row_box->addWidget(m_comboboxStyle,true);
	vbox->addLayout(row_box);

	row_box = new QHBoxLayout;
    row_box->addWidget(new QLabel(_Q("画笔")));
	QFrame* line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	row_box->addWidget(line,true);
	vbox->addLayout(row_box);
	vbox->addWidget(m_penSettingSheet);

	QWidget* curveSettingSheet = new QWidget;
	curveSettingSheet->setLayout(vbox);

	QToolBox* tool_box = new QToolBox;
    tool_box->addItem(curveSettingSheet,_Q("曲线"));
    tool_box->addItem(m_symbolSettingSheet,_Q("符号"));
	//QTabWidget* tab = new QTabWidget;
    //tab->addTab(curveSettingSheet,_Q("曲线"));
    //tab->addTab(m_symbolSettingSheet,_Q("符号"));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(tool_box);
	setLayout(layout);

	//connects

	setCurve(curve);
}

const QwtPlotCurve* QwtPlotCurveSettingSheet::curve() const
{
	return m_curve;
}

void QwtPlotCurveSettingSheet::setCurve(QwtPlotCurve* curve)
{
	m_curve = curve;
	updateSettings(false);
}

void QwtPlotCurveSettingSheet::initSytleComboBox()
{
	assert(m_comboboxStyle != NULL);

    m_comboboxStyle->addItem(_Q("NoCurve"),QVariant(QwtPlotCurve::NoCurve));
    m_comboboxStyle->addItem(_Q("Lines"),QVariant(QwtPlotCurve::Lines));
    m_comboboxStyle->addItem(_Q("Sticks"),QVariant(QwtPlotCurve::Sticks));
    m_comboboxStyle->addItem(_Q("Steps"),QVariant(QwtPlotCurve::Steps));
    m_comboboxStyle->addItem(_Q("Dots"),QVariant(QwtPlotCurve::Dots));
}

void QwtPlotCurveSettingSheet::updateSettings(bool save)
{
	if (m_curve == NULL)
		return;

	if (save)
	{
		// name
		m_curve->setTitle(m_lineEditName->text());
		// style
		int i = m_comboboxStyle->currentIndex();
		m_curve->setStyle((QwtPlotCurve::CurveStyle)m_comboboxStyle->itemData(i).toInt());
		// pen
		m_curve->setPen(m_penSettingSheet->pen());
		// symbol
//		m_curve->setSymbol(new QwtSymbol(m_symbolSettingSheet->symbol()));
	}
	else
	{
		m_lineEditName->setText(m_curve->title().text());
		int i = m_comboboxStyle->findData(QVariant(m_curve->style()));
		m_comboboxStyle->setCurrentIndex(i);
		m_penSettingSheet->setPen(m_curve->pen());

		const QwtSymbol* symbol = m_curve->symbol();
		if (symbol != NULL)
			m_symbolSettingSheet->setSymbol(*symbol);
		else
			m_symbolSettingSheet->setSymbol(QwtSymbol());
	}
}

/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QwtSymbolSettingSheet.cpp
** Created Time: 2011-11-14 11:35:15
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QBrushSettingSheet.h>
#include <QPenSettingSheet.h>
#include "QwtSymbolSettingSheet.h"
#define _Q(s) QStringLiteral(s)

QwtSymbolSettingSheet::QwtSymbolSettingSheet(const QwtSymbol& symbol,
											 QWidget* parent,Qt::WindowFlags f)
 	: QFrame(parent,f)
{
	m_comboboxStyle = new QComboBox;
	initSytleComboBox();

	m_brushSettingSheet = new QBrushSettingSheet;
	m_penSettingSheet = new QPenSettingSheet;
	m_spinBoxWidth = new QSpinBox;
	m_spinBoxHeight = new QSpinBox;

	QVBoxLayout* whole = new QVBoxLayout;

	QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel(_Q("类型：")));
	hbox->addWidget(m_comboboxStyle,true);
	whole->addLayout(hbox);

	hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel(_Q("尺寸：")));
	hbox->addWidget(m_spinBoxWidth,true);
	hbox->addWidget(m_spinBoxHeight,true);
	whole->addLayout(hbox);

    QLabel* label = new QLabel(_Q("画刷"));
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
	whole->addWidget(m_brushSettingSheet);

    label = new QLabel(_Q("画笔"));
	label->setFont(font);
	line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	label_line = new QHBoxLayout;
	label_line->addWidget(label);
	label_line->addWidget(line,true);
	whole->addLayout(label_line);
	whole->addWidget(m_penSettingSheet);

	setLayout(whole);
	//connects

	setSymbol(symbol);
}

const QwtSymbol& QwtSymbolSettingSheet::symbol()
{
	updateSettings(true);
	return m_symbol;
}

void QwtSymbolSettingSheet::setSymbol(const QwtSymbol& symbol)
{
//	m_symbol = symbol;
	updateSettings(false);
}


void QwtSymbolSettingSheet::initSytleComboBox()
{
	assert(m_comboboxStyle != NULL);

    m_comboboxStyle->addItem(_Q("NoSymbol"),QVariant(QwtSymbol::NoSymbol));
    m_comboboxStyle->addItem(_Q("Ellipse"),QVariant(QwtSymbol::Ellipse));
    m_comboboxStyle->addItem(_Q("Rect"),QVariant(QwtSymbol::Rect));
    m_comboboxStyle->addItem(_Q("Diamond"),QVariant(QwtSymbol::Diamond));
    m_comboboxStyle->addItem(_Q("Triangle"),QVariant(QwtSymbol::Triangle));
    m_comboboxStyle->addItem(_Q("DTriangle"),QVariant(QwtSymbol::DTriangle));
    m_comboboxStyle->addItem(_Q("UTriangle"),QVariant(QwtSymbol::UTriangle));
    m_comboboxStyle->addItem(_Q("LTriangle"),QVariant(QwtSymbol::LTriangle));
    m_comboboxStyle->addItem(_Q("RTriangle"),QVariant(QwtSymbol::RTriangle));
    m_comboboxStyle->addItem(_Q("Cross"),QVariant(QwtSymbol::Cross));
    m_comboboxStyle->addItem(_Q("XCross"),QVariant(QwtSymbol::XCross));
    m_comboboxStyle->addItem(_Q("HLine"),QVariant(QwtSymbol::HLine));
    m_comboboxStyle->addItem(_Q("VLine"),QVariant(QwtSymbol::VLine));
    m_comboboxStyle->addItem(_Q("Star1"),QVariant(QwtSymbol::Star1));
    m_comboboxStyle->addItem(_Q("Star2"),QVariant(QwtSymbol::Star2));
    m_comboboxStyle->addItem(_Q("Hexagon"),QVariant(QwtSymbol::Hexagon));
}

void QwtSymbolSettingSheet::updateSettings(bool save)
{
	if (save)
	{
		// style
		int i = m_comboboxStyle->currentIndex();
		m_symbol.setStyle((QwtSymbol::Style)m_comboboxStyle->itemData(i).toInt());
		// size
		m_symbol.setSize(m_spinBoxWidth->value(),
			m_spinBoxHeight->value());
		// brush
		m_symbol.setBrush(m_brushSettingSheet->brush());
		// pen
		m_symbol.setPen(m_penSettingSheet->pen());
	}
	else
	{
		int i = m_comboboxStyle->findData(QVariant(m_symbol.style()));
		m_comboboxStyle->setCurrentIndex(i);
		m_spinBoxWidth->setValue(m_symbol.size().width());
		m_spinBoxHeight->setValue(m_symbol.size().height());
		m_brushSettingSheet->setBrush(m_symbol.brush());
		m_penSettingSheet->setPen(m_symbol.pen());
	}
}

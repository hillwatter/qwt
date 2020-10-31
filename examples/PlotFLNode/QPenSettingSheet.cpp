/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QPenSettingSheet.cpp
** Created Time: 2011-11-8 12:02:04
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QColorDialog>
#include "QLineStyleComboBox.h"
#include "QLineWidthComboBox.h"
#include "QColorButton.h"
#include "QPenSettingSheet.h"
#define _Q(s) QStringLiteral(s)

class QPenSettingSheet::PreviewFrame : public QFrame
{
public:
	const static int MIN_H = 50;
public:
	PreviewFrame(QWidget* parent=NULL,Qt::WindowFlags f=0)
		: QFrame(parent,f)
	{
		setFixedHeight(MIN_H);
		setFrameShape(QFrame::Panel);
		setFrameShadow(QFrame::Plain);
		setStyleSheet("background-color:#FFFFFF");
	}

	QPen pen;

protected:
	virtual void paintEvent(QPaintEvent* event)
	{
		QFrame::paintEvent(event);
		QPainter painter(this);

		painter.setPen(pen);
		//from 1 for the starting point not on border
		painter.drawLine(1,height()/2,width(),height()/2);
	}
};

QPenSettingSheet::QPenSettingSheet(const QPen& pen,
								   QWidget* parent,Qt::WindowFlags f)
	: QFrame(parent,f)
{
	m_styleComboBox = new QLineStyleComboBox;
	m_widthComboBox = new QLineWidthComboBox;
	m_colorButton = new QColorButton;
	m_previewFrame = new PreviewFrame;

	QGridLayout* gridLayout = new QGridLayout;
	int margin = 0;
	gridLayout->getContentsMargins(0,0,0,&margin);
	gridLayout->setContentsMargins(0,margin,0,margin);
	gridLayout->setColumnStretch(0,0);
	gridLayout->setColumnStretch(1,1);

    gridLayout->addWidget(new QLabel(_Q("线型：")),0,0);
    gridLayout->addWidget(new QLabel(_Q("线宽：")),1,0);
    gridLayout->addWidget(new QLabel(_Q("颜色：")),2,0);
    gridLayout->addWidget(new QLabel(_Q("预览：")),3,0);

	gridLayout->addWidget(m_styleComboBox,0,1);
	gridLayout->addWidget(m_widthComboBox,1,1);
	gridLayout->addWidget(m_colorButton,2,1);
	gridLayout->addWidget(m_previewFrame,3,1);
	setLayout(gridLayout);

	//connects
	connect(m_styleComboBox,SIGNAL(currentIndexChanged(int)),SLOT(onStyleChanged(int)));
	connect(m_widthComboBox,SIGNAL(currentIndexChanged(int)),SLOT(onWidthChanged(int)));
	connect(m_colorButton,SIGNAL(colorChanged(const QColor&)),
		SLOT(onColorChanged(const QColor&)));

	setPen(pen);
}

const QPen& QPenSettingSheet::pen() const
{
	return m_previewFrame->pen;
}

void QPenSettingSheet::setPen(const QPen& pen)
{	
	m_previewFrame->pen = pen;

	m_styleComboBox->setCurrentStyle(pen.style());
	m_widthComboBox->setCurrentWidth(pen.widthF());
	m_colorButton->setColor(pen.color());
	m_previewFrame->update();
}

void QPenSettingSheet::onStyleChanged(int)
{
	m_previewFrame->pen.setStyle(m_styleComboBox->currentStyle());
	m_previewFrame->update();

    Q_EMIT changed(m_previewFrame->pen);
}

void QPenSettingSheet::onWidthChanged(int)
{
	m_previewFrame->pen.setWidthF(m_widthComboBox->currentWidth());
	m_previewFrame->update();

    Q_EMIT changed(m_previewFrame->pen);
}

void QPenSettingSheet::onColorChanged(const QColor& c)
{
	m_previewFrame->pen.setColor(c);
	m_previewFrame->update();

    Q_EMIT changed(m_previewFrame->pen);
}

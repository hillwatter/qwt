/****************************************************************************
** Last Modified: 2011-11-9-001
**
** File Name: QwtTextSettingSheet.cpp
** Created Time: 2011-11-9 17:25:25
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QColorDialog>
#include <QFontDialog>
#include "QwtTextSettingSheet.h"
#define _Q(s) QStringLiteral(s)

//class QwtTextSettingSheet::PreviewFrame : public QFrame
//{
//public:
//	const static int MIN_H = 50;
//public:
//	PreviewFrame(QWidget* parent=NULL,Qt::WindowFlags f=0)
//		: QFrame(parent,f)
//	{
//		setMinimumSize(QPenSettingSheet::WIDTH-QLineStyleComboBox::FIXED_HEIGHT,
//			MIN_H);
//		setFrameShape(QFrame::Panel);
//		setFrameShadow(QFrame::Plain);
//		setStyleSheet("background-color:#FFFFFF");
//	}
//
//	QPen pen;
//
//protected:
//	virtual void paintEvent(QPaintEvent* event)
//	{
//		QFrame::paintEvent(event);
//		QPainter painter(this);
//
//		painter.setPen(pen);
//		//from 1 for the starting point not on border
//		painter.drawLine(1,height()/2,width(),height()/2);
//	}
//};

QwtTextSettingSheet::QwtTextSettingSheet(const QwtText& text,
										 QWidget* parent,Qt::WindowFlags f,
										 bool text_show)
	: QFrame(parent,f)
{
	m_lineEditText = new QLineEdit;
	m_colorButton = new QColorButton;
	m_buttonFont = new QPushButton;

	QGridLayout* gridLayout = new QGridLayout;
	int margin = 0;
	gridLayout->getContentsMargins(0,0,0,&margin);
	gridLayout->setContentsMargins(0,margin,0,margin);
	gridLayout->setColumnStretch(0,0);
	gridLayout->setColumnStretch(1,1);

	int row = -1;
	if (text_show)
	{
        gridLayout->addWidget(new QLabel(_Q("文本：")),++row,0);
		gridLayout->addWidget(m_lineEditText,row,1);
	}

    gridLayout->addWidget(new QLabel(_Q("颜色：")),++row,0);
	gridLayout->addWidget(m_colorButton,row,1);

    gridLayout->addWidget(new QLabel(_Q("字体：")),++row,0);
	gridLayout->addWidget(m_buttonFont,row,1);

	setLayout(gridLayout);

	//connects
	connect(m_lineEditText,SIGNAL(editingFinished()),SLOT(onTextChanged()));
	connect(m_colorButton,SIGNAL(colorChanged(const QColor&)),
		SLOT(onColorChanged(const QColor&)));
	connect(m_buttonFont,SIGNAL(clicked()),SLOT(onChangeFont()));
}

const QwtText& QwtTextSettingSheet::text() const
{
	return m_qwt_text;
}

void QwtTextSettingSheet::setText(const QwtText& text)
{	
	m_qwt_text = text;
	m_lineEditText->setText(m_qwt_text.text());
	m_colorButton->setColor(m_qwt_text.color());
	updateFontButton();
}

void QwtTextSettingSheet::onTextChanged()
{
	m_qwt_text.setText(m_lineEditText->text());
}

void QwtTextSettingSheet::onColorChanged(const QColor& c)
{
	m_qwt_text.setColor(c);
}

void QwtTextSettingSheet::onChangeFont()
{
	bool ok = false;
	QFont font = QFontDialog::getFont(&ok,m_qwt_text.font(),this);
	if (!ok) 
		return;
	m_qwt_text.setFont(font);
	updateFontButton();
}

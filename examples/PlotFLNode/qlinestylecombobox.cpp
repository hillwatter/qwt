/****************************************************************************
** Last Modified: 2011-11-8-001
**
** File Name: qlinestylecombobox.cpp
** Created Time: 2011-11-7 15:56:04
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include "qlinestylecombobox.h"

QLineStyleComboBox::QLineStyleComboBox(QWidget *parent,bool showName)
	: QComboBox(parent)
	, m_showName(showName)
{
	//setFixedHeight(FIXED_HEIGHT);
	//setFixedWidth(FIXED_WIDTH);
	setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
	drawItems();
}

Qt::PenStyle QLineStyleComboBox::currentStyle() const
{
	return getStyle(currentIndex());
}

void QLineStyleComboBox::setCurrentStyle(Qt::PenStyle style)
{
	const QVector<PEN_STYLE>& styles = getStyles();

	for (size_t i = 0; i < styles.size(); ++i)
	{
		if (styles[i].style == style)
		{
			setCurrentIndex(i);
			break;
		}
	}
}

void QLineStyleComboBox::resizeEvent(QResizeEvent* event)
{
	QComboBox::resizeEvent(event);
}


void QLineStyleComboBox::drawItems()
{
	clear();

	int p_w = ICON_WIDTH;
	int p_h = FIXED_HEIGHT;
	setIconSize(QSize(p_w,p_h));

	const QVector<PEN_STYLE>& styles = getStyles();
	for (int i = 0; i < styles.size(); ++i)
	{
		QPen pen;
		pen.setStyle(styles[i].style);
		QPixmap pixmap = linePixmap(pen,p_w,p_h);

		if (m_showName)
			addItem(pixmap,styles[i].name);
		else
			addItem(pixmap,QString::number(styles[i].style));
	}
}

//////////////////////////////////////////////////////////////////////////////
// static

Qt::PenStyle QLineStyleComboBox::getStyle(int index)
{
	const QVector<PEN_STYLE>& styles = getStyles();

	if (index > styles.size() || index < 0)
		return Qt::NoPen;
	else
		return styles[index].style;
}

const QVector<QLineStyleComboBox::PEN_STYLE>& QLineStyleComboBox::getStyles()
{
	static QVector<PEN_STYLE> styles = initStyles();
	return styles;
}

QVector<QLineStyleComboBox::PEN_STYLE> QLineStyleComboBox::initStyles()
{
	QVector<PEN_STYLE> styles;

	styles.append(PEN_STYLE(Qt::NoPen,"No Pen"));
	styles.append(PEN_STYLE(Qt::SolidLine,"Solid Line"));
	styles.append(PEN_STYLE(Qt::DashLine,"Dash Line"));
	styles.append(PEN_STYLE(Qt::DotLine,"Dot Line"));
	styles.append(PEN_STYLE(Qt::DashDotLine,"Dash Dot Line"));
	styles.append(PEN_STYLE(Qt::DashDotDotLine,"Dash Dot Dot Line"));
	styles.append(PEN_STYLE(Qt::CustomDashLine,"Custom Dash Line"));

	return styles;
}
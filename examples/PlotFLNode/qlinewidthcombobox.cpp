/****************************************************************************
** Last Modified: 2011-11-8-001
**
** File Name: qlinewidthcombobox.cpp
** Created Time: 2011-11-7 18:03:01
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include "qlinestylecombobox.h"
#include "qlinewidthcombobox.h"
#include <math.h>

QLineWidthComboBox::QLineWidthComboBox(QWidget* parent)
	: QComboBox(parent)
{
	//setFixedHeight(QLineStyleComboBox::FIXED_HEIGHT);
	//setFixedWidth(QLineStyleComboBox::FIXED_WIDTH);

	initItems();
}

qreal QLineWidthComboBox::currentWidth() const
{
	return m_widths[currentIndex()];
}

void QLineWidthComboBox::setCurrentWidth(qreal width)
{
	for (size_t i = 0; i < m_widths.size(); ++i)
	{
		if (fabs(m_widths[i] - width) < 0.001)
		{
			setCurrentIndex(i);
			break;
		}
	}
}

qreal QLineWidthComboBox::getWidth(int index) const
{
	if (index < 0 || index >= m_widths.size())
		return 0;
	else
		return m_widths[index];
}

void QLineWidthComboBox::initItems()
{
	const int MAX_LINE_WIDTH = 15;
	for (int i = 0; i < MAX_LINE_WIDTH; ++i)
		m_widths.append(i);

	int p_w = QLineStyleComboBox::ICON_WIDTH;
	int p_h = QLineStyleComboBox::FIXED_HEIGHT;
	setIconSize(QSize(p_w,p_h));

	for (int i = 0; i < m_widths.size(); ++i)
	{
		QPen pen(Qt::SolidLine);
		pen.setWidthF(m_widths[i]);
		QPixmap pixmap = linePixmap(pen,p_w,p_h);
		
		addItem(pixmap,QString::number(m_widths[i]));
	}
}

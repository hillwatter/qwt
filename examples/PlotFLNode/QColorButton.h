/****************************************************************************
** Last Modified: 2011-11-13-001
**
** File Name: QColorButton.h
** Created Time: 2011-11-13 14:33:51
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QColorButton_h__
#define __QColorButton_h__

#include <QPainter>
#include <QPushButton>
#include <QColorDialog>

class  QColorButton : public QPushButton
{
	Q_OBJECT
public:
	static const int ICON_WIDTH = 116;
	static const int ICON_HEIGHT = 16;
	static const int ICON_LMARGIN = 5;
	static const int TEXT_WIDTH = 45;
	static const int TEXT_HEIGHT = 10;

public:
	QColorButton(QWidget* parent=NULL)
		: QPushButton(parent)
	{
		setMinimumWidth(ICON_WIDTH + TEXT_WIDTH + 2*ICON_LMARGIN);
		connect(this,SIGNAL(clicked()),SLOT(showColorDialog()));
	}

	const QColor& color()
	{
		return m_color;
	}

	void setColor(const QColor& c)
	{
		m_color = c;
		update();
	}

Q_SIGNALS:
	void colorChanged(const QColor&);

protected Q_SLOTS:
	void showColorDialog()
	{
		QColor c = QColorDialog::getColor(m_color,this);
		setColor(c);
        Q_EMIT colorChanged(c);
	}

protected:
	virtual void paintEvent(QPaintEvent* event)
	{
		QPushButton::paintEvent(event);

		QPainter painter(this);
		painter.setPen(m_color);
		painter.setBrush(QBrush(m_color));
		painter.drawRoundedRect(ICON_LMARGIN,(height()-ICON_HEIGHT)/2,
			ICON_WIDTH,ICON_HEIGHT,ICON_LMARGIN,ICON_LMARGIN);

		QFont font;
		font.setBold(true);
		painter.drawText(2*ICON_LMARGIN+ICON_WIDTH,(height()+TEXT_HEIGHT)/2,
			m_color.name().toUpper());
	}

	QColor m_color;
};
#endif//__QColorButton_h__

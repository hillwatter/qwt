/****************************************************************************
** Last Modified: 2011-11-8-001
**
** File Name: qlinestylecombobox.h
** Created Time: 2011-11-7 15:46:54
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __qlinestylecombobox_h__
#define __qlinestylecombobox_h__

#include <QPainter>
#include <QComboBox>
#include <QVector>

//class LinePixmap : public QPixmap
//{
//public:
//	LinePixmap(int width, int height,int hMargin=1,int vMargin=3);
//
//private:
//	void paint();
//
//private:
//	int m_hMargin;
//	int m_vMargin;
//};
inline QPixmap linePixmap(const QPen& pen,
						  int width, int height,
						  int hMargin=1,int vMargin=3)
{
	QPixmap pixmap(width,height);
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	painter.drawRect(hMargin,vMargin,
		width - 2*hMargin, height - 2*vMargin);
	painter.setPen(pen);
	//hMargin+1 for starting point not on border
	painter.drawLine(hMargin+1, height/2,
		width-2*hMargin, height/2);

	return pixmap;
}

class QLineStyleComboBox : public QComboBox
{
	Q_OBJECT
public:
	static const int FIXED_HEIGHT = 22;
	static const int FIXED_WIDTH = 163;
	static const int ICON_WIDTH = 120;

public:
	struct PEN_STYLE
	{
		Qt::PenStyle style;
		QString name;

		PEN_STYLE(Qt::PenStyle s=Qt::NoPen,const QString& sn=QString())
			: style(s)
			, name(sn)
		{
		}
	};

public:
	explicit QLineStyleComboBox(QWidget *parent=NULL,
		bool showName=false);

	Qt::PenStyle currentStyle() const;
	void setCurrentStyle(Qt::PenStyle style);

	static Qt::PenStyle getStyle(int index);
	static const QVector<PEN_STYLE>& getStyles();
	
protected:
	virtual void drawItems();
	virtual void resizeEvent(QResizeEvent* event);

private:
	static QVector<PEN_STYLE> initStyles();
	//todo: put all non-const functions here to stop from editting.

private:
	bool m_showName;

};

#endif//__qlinestylecombobox_h__

/****************************************************************************
* @brief:
** Last Modified: 2012-3-22-001
**
** File Name: QwtSignTextMarker.h
** Created Time: 2012-3-22 11:34:50
** Created By: ShaoLing.Jia
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef QWTSIGNTEXTMARKER_H
#define QWTSIGNTEXTMARKER_H

#include <qpen.h>
#include <qfont.h>
#include <qstring.h>
#include <qbrush.h>
#include "qwt_global.h"
#include "qwt_plot_item.h"

class QRectF;
class QwtText;
class QwtSymbol;

class QwtSignTextMarker : public QwtPlotItem
{
public:
	explicit QwtSignTextMarker();
	virtual ~QwtSignTextMarker();

	virtual int rtti() const;

	double xValue() const;
	double yValue() const;
	QPointF value() const;

	void setXValue( double );
	void setYValue( double );
	void setValue( double, double );
	void setValue( const QPointF & );

	void setText( const QwtText& );
	QwtText text() const;

	void SetRect(const QRect &rect)
	{
		m_textRect = rect;
	}

	QRect GetTextRect()
	{
		return m_textRect;
	}


	void setLabelOrientation( Qt::Orientation );
	Qt::Orientation labelOrientation() const;

	virtual void draw( QPainter *p,
		const QwtScaleMap &xMap, const QwtScaleMap &yMap,
		const QRectF & ) const;

protected:

	virtual void drawLabel( QPainter *, 
		 const QPointF & ) const;

private:

	class PrivateData;
	PrivateData *d_data;

	QRect m_textRect;

	
};

#endif // QWTSIGNTEXTMARKER_H

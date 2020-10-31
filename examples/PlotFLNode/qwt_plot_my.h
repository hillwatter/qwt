#ifndef __SRC_COMPONENT_PLOTFLNODE_QWTPLOTMY_H__
#define __SRC_COMPONENT_PLOTFLNODE_QWTPLOTMY_H__

#include <QEvent>
#include <QMouseEvent>
#include <qwt_plot_canvas.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>

//改写了QwtPicker的eventFilter函数
//对Press消息特别处理，返回true
//这样QGraphicsScene就认为item Accept了该Press Event，
//才使得QGraphicsScent不会UngrabMouse从而将item从grabberItems中清除
//那么，在下一个Release Event到来的时候，它才会发给item

class MyPlotPanner : public QwtPlotPanner
{
public:
    MyPlotPanner( QWidget *canvas )
		: QwtPlotPanner( canvas )
	{
		//setCursor(QCursor(Qt::SizeAllCursor));
		disconnect(this,SIGNAL(panned(int,int)),this,SLOT(moveCanvas(int,int)));
	}

	void setEnabled(bool on)
	{
		QwtPlotPanner::setEnabled(on);
		if (on)
		{
			parentWidget()->setCursor(cursor());
		}
	}

	virtual bool eventFilter( QObject *object, QEvent *event )
	{
		QwtPlotPanner::eventFilter(object,event);
		if (event->type() == QEvent::MouseButtonPress)
		{
			const QMouseEvent *me = (const QMouseEvent *)event;
			if (me->button() == Qt::LeftButton)
				return true;
		}

		// filter MouseMove event
		return event->type() == QEvent::MouseMove;
	}

	virtual void paintEvent( QPaintEvent *pe )
	{
		int dx = m_pos.x() - m_initialPos.x();
		int dy = m_pos.y() - m_initialPos.y();
		moveCanvas(dx,dy);
		m_initialPos = m_pos;
	}

    virtual void widgetMousePressEvent( QMouseEvent *mouseEvent )
	{
		if ( mouseEvent->button() != Qt::LeftButton )
			return;

		QWidget *w = parentWidget();
		if ( w == NULL )
			return;

		m_initialPos = m_pos = mouseEvent->pos();
		QwtPlotPanner::widgetMousePressEvent(mouseEvent);
	}

    virtual void widgetMouseMoveEvent( QMouseEvent *mouseEvent )
	{
		if ( !isVisible() )
			return;

		QPoint cur_pos = mouseEvent->pos();
		if ( !isOrientationEnabled( Qt::Horizontal ) )
			cur_pos.setX( m_initialPos.x() );
		if ( !isOrientationEnabled( Qt::Vertical ) )
			cur_pos.setY( m_initialPos.y() );

		if (rect().contains( cur_pos ) )
		{
			m_pos = cur_pos;
		}

		QwtPlotPanner::widgetMouseMoveEvent(mouseEvent);
	}

	virtual void widgetMouseReleaseEvent( QMouseEvent *mouseEvent )
	{
		QwtPlotPanner::widgetMouseReleaseEvent(mouseEvent);
		//parentWidget()->setCursor(cursor());
	}

private:
	QPoint m_initialPos;
    QPoint m_pos;
};

class MyPlotZoomer : public QwtPlotZoomer
{
public:
    MyPlotZoomer( QWidget *canvas )
		: QwtPlotZoomer( canvas )
    {
        setTrackerMode( AlwaysOn );
    }

	void setEnabled(bool on)
	{
		QwtPlotZoomer::setEnabled(on);
		if (on)
			setCursor();
	}

	virtual bool end(bool ok = true)
	{
		setCursor();
		return QwtPlotZoomer::end(ok);
	}

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::gray );
        bg.setAlpha( 200 );

        QwtText text = QwtPlotZoomer::trackerTextF( pos );
        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }

	virtual bool eventFilter( QObject *object, QEvent *event )
	{
		QwtPlotZoomer::eventFilter(object,event);
		switch (event->type())
		{
		case QEvent::MouseButtonPress:
			return ((const QMouseEvent *)event)->button() == Qt::LeftButton;
		case QEvent::Wheel:
			return true;
		}

		return false;
	}

private:
	void setCursor()
	{
		parentWidget()->setCursor(QCursor(Qt::ArrowCursor));
	}
};

class MyPlotMagnifier : public QwtPlotMagnifier
{
public:
    MyPlotMagnifier( QWidget *canvas ):
        QwtPlotMagnifier( canvas )
    {
    }

	virtual bool eventFilter( QObject *object, QEvent *event )
	{
		QwtPlotMagnifier::eventFilter(object,event);

		switch (event->type())
		{
		case QEvent::MouseButtonPress:
			return ((const QMouseEvent *)event)->button() != Qt::LeftButton;
		case QEvent::Wheel:
			return true;
		case QEvent::KeyPress:
			return true;
		}

		return false;
	}
};

#endif//__SRC_COMPONENT_PLOTFLNODE_QWTPLOTMY_H__

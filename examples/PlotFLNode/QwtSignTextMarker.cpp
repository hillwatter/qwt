#include "QwtSignTextMarker.h"
#include "qwt_painter.h"
#include "qwt_scale_map.h"
#include "qwt_symbol.h"
#include "qwt_text.h"
#include "qwt_math.h"
#include "qwt_legend.h"
//#include "qwt_legend_item.h"
#include <qpainter.h>

class QwtSignTextMarker::PrivateData
{
public:
	PrivateData():
	  labelAlignment( Qt::AlignLeft ),
		  labelOrientation( Qt::Horizontal ),
		  spacing( 2 ),
		  xValue( 0.0 ),
		  yValue( 0.0 )
	  {
	  }

	  ~PrivateData()
	  {
		  
	  }

	  QwtText text;
	  Qt::Alignment labelAlignment;
	  Qt::Orientation labelOrientation;
	  int spacing;

	  QPen pen;

	  double xValue;
	  double yValue;
};

QwtSignTextMarker::QwtSignTextMarker():
		QwtPlotItem( QwtText( "Marker" ) )

{
	d_data = new PrivateData;
	setZ( 30.0 );
}

QwtSignTextMarker::~QwtSignTextMarker()
{
	delete d_data;
}

//! \return QwtPlotItem::Rtti_PlotMarker
int QwtSignTextMarker::rtti() const
{
    return QwtPlotItem::Rtti_PlotMarker;
}

//! Return Value
QPointF QwtSignTextMarker::value() const
{
    return QPointF( d_data->xValue, d_data->yValue );
}

//! Return x Value
double QwtSignTextMarker::xValue() const
{
    return d_data->xValue;
}

//! Return y Value
double QwtSignTextMarker::yValue() const
{
    return d_data->yValue;
}

//! Set Value
void QwtSignTextMarker::setValue( const QPointF& pos )
{
    setValue( pos.x(), pos.y() );
}

//! Set Value
void QwtSignTextMarker::setValue( double x, double y )
{
    if ( x != d_data->xValue || y != d_data->yValue )
    {
        d_data->xValue = x;
        d_data->yValue = y;
        itemChanged();
    }
}

//! Set X Value
void QwtSignTextMarker::setXValue( double x )
{
    setValue( x, d_data->yValue );
}

//! Set Y Value
void QwtSignTextMarker::setYValue( double y )
{
    setValue( d_data->xValue, y );
}

/*!
  Draw the marker

  \param painter Painter
  \param xMap x Scale Map
  \param yMap y Scale Map
  \param canvasRect Contents rect of the canvas in painter coordinates
*/
void QwtSignTextMarker::draw( QPainter *painter,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRectF &canvasRect ) const
{
    const QPointF pos( xMap.transform( d_data->xValue ), 
        yMap.transform( d_data->yValue ) );

 
    drawLabel( painter, pos );
}

void QwtSignTextMarker::drawLabel( QPainter *painter,
							  const QPointF &pos ) const
{
	if ( d_data->text.isEmpty() )
		return;

	Qt::Alignment align = d_data->labelAlignment;
	QPointF alignPos = pos;
	painter->setFont(d_data->text.font());
	const QSizeF textSize = d_data->text.textSize();
	QRect rect(alignPos.x(), alignPos.y(), textSize.width(),textSize.height());

	painter->drawText(rect,	Qt::AlignLeft, d_data->text.text());
	
}

void QwtSignTextMarker::setText( const QwtText& label )
{
    if ( label != d_data->text )
    {
        d_data->text = label;
        itemChanged();
    }
}

/*!
  \return the text
  \sa setText()
*/
QwtText QwtSignTextMarker::text() const
{
    return d_data->text;
}

void QwtSignTextMarker::setLabelOrientation( Qt::Orientation orientation )
{
    if ( orientation != d_data->labelOrientation )
    {
        d_data->labelOrientation = orientation;
        itemChanged();
    }
}

/*!
  \return the label orientation
  \sa setLabelOrientation(), labelAlignment()
*/
Qt::Orientation QwtSignTextMarker::labelOrientation() const
{
    return d_data->labelOrientation;
}



#ifndef __QwtPlotActions_h
#define __QwtPlotActions_h

#include <QToolBar>
#include <QShareActionsMngr.h>

class QwtPlotActions : public QShareActionsMngr
{
public:
	static QwtPlotActions& getInstance()
	{
		static QwtPlotActions s_instance;
		return s_instance;
	}

	virtual bool setup(QMainWindow* mw,const QString& name="");
	virtual void show(bool on);

protected:
	QToolBar* toolbar;
};

#endif//__QwtPlotActions_h

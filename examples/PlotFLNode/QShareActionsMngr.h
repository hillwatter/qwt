/*=========================================================================

  Program:   TestExpert
  Module:    QShareActionsMngr.h
  Author:    Xianliang Zeng

  Created:        2011-10-17
  Last Modified:  2011-10-17

  Copyright (c) APPSOFT
  All rights reserved.

=========================================================================*/
// .NAME ShareActionsMngr - abstract class to write a share actions manager
// .SECTION Description
// ShareActionsMngr is an abstract class that manage actions which are 
// shared by more than one widgets. It's originally used for 
// QwtContour3DWidget.
//
// ShareActionsMngr provides the convenience methods registerWidget() 
// and unregisterWidget().
// These methods are executed before and after execution of the Write() 
// method. You can also specify arguments to these methods.
// This class defines SetInput and GetInput methods which take or return
// a vtkRenderWindow.  
// .SECTION Caveats
// 

// .SECTION See Also
// Contour3DActions.h

#ifndef __QShareActionsMngr_h
#define __QShareActionsMngr_h

#include <QAction>
#include <QMainWindow>
#include <map>

inline void setActionGroupCheckable(QActionGroup* ag)
{
	QList<QAction*> tmplist = ag->actions();
	for (QList<QAction*>::iterator it=tmplist.begin(); it!=tmplist.end(); ++it)
		(*it)->setCheckable(true);
}

class QShareActionsMngr : public QObject
{
	Q_OBJECT
//public:
	//static QShareActionsMngr& getInstance()
	//{
	//	static QShareActionsMngr mngr;
	//	return mngr;
	//}

public:
	virtual bool setup(QMainWindow* mw,const QString& name="")=0;
	//{
	//	static bool setupped = false;
	//	if (setupped)
	//		return;
	//	setupped = true;
	//	//TODO: Add your action set up as below
	//	//animation = new QAction(QIcon(":/images/Resources/movie.png"), tr("Animation"), mw);
	//	//_ACTION_STATE init;
	//	//manageAction(animation,init);
	//	//addActionConnect(animation, SIGNAL(toggled(bool)),SLOT(toggleAnimation(bool)));
	//	return true;
	//}

	void registerWidget(QWidget* w);
	void unregisterWidget(QWidget* w);
	void connectWidget(QWidget* w);

public Q_SLOTS:
	//default implement is: hide all actions
	//reimplement to hide toolbar if needed for improving appearance.
	virtual void show(bool on);

protected:
	//the receiver is current widget
	struct _CONNECT_INFOR
	{
		const QObject* sender;
		const char* signal;
		const char* method;
		Qt::ConnectionType type;

		_CONNECT_INFOR()
			: sender(NULL)
			, signal(NULL)
			, method(NULL)
			, type(Qt::AutoConnection)
		{
		}
	};

	struct _ACTION_STATE
	{
		bool enabled;
		bool checked;

		_ACTION_STATE()
			: enabled(true)
			, checked(false)
		{
		}

		void update(QAction* action,bool save)
		{
			if (action != NULL)
			{
				if (save)
				{
					//enabled = action->isEnabled();
					checked = action->isChecked();
				}
				else
				{
					//action->setEnabled(enabled);
					action->setChecked(checked);
				}
			}
		}
	};

	typedef std::map<QAction*,_ACTION_STATE> ACTION2STATE; 

protected:
	QShareActionsMngr()
		: m_current_w(NULL)
	{
	}
	QShareActionsMngr(const QShareActionsMngr& other);
	QShareActionsMngr& operator=(const QShareActionsMngr& other);

	void manageAction(QAction* action,const _ACTION_STATE& init)
	{
		if (action != NULL)
		{
			m_initStates.insert(std::make_pair(action,init));
		}
	}
	void addActionConnect(const QObject * sender, const char * signal,
		const char * method,Qt::ConnectionType type = Qt::AutoConnection)
	{
		if (sender != NULL && signal != NULL && method != NULL)
		{
			_CONNECT_INFOR connect;
			connect.sender = sender;
			connect.signal = signal;
			connect.method = method;
			connect.type = type;

			m_connects.push_back(connect);
		}
	}

private:
	void updateStates(bool save=false);

private:
	QWidget* m_current_w;
	
	ACTION2STATE m_initStates;
	std::map<QWidget*,ACTION2STATE> m_w2states;
	std::vector<_CONNECT_INFOR> m_connects;

};

#endif//__ShareActionsMngr_h

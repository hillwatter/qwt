/****************************************************************************
** Last Modified: 2012-2-24-001
**
** File Name: SelectCurveDlg.h
** Created Time: 2012-2-24 10:32:35
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __SelectCurveDlg_h__
#define __SelectCurveDlg_h__

#include <QDialog>
#include <QVector>

class QwtPlotCurve;

class SelectCurveDlg : public QDialog
{
	Q_OBJECT
public:
	SelectCurveDlg(const QVector<QwtPlotCurve*>& curves,int iSelected,
		QWidget* parent=NULL,Qt::WindowFlags f=0);

	int curveSelected() const;

protected Q_SLOTS:
	void setSelectedCurve(int index);

private:
	int m_iSelected;

};
#endif//__SelectCurveDlg_h__

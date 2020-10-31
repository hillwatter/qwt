/****************************************************************************
** Last Modified: 2012-2-24-001
**
** File Name: SelectCurveDlg.cpp
** Created Time: 2012-2-24 10:40:27
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <assert.h>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <qwt_plot_curve.h>
#include "SelectCurveDlg.h"
#define _Q(s) QStringLiteral(s)

SelectCurveDlg::SelectCurveDlg(const QVector<QwtPlotCurve*>& curves,int iSelected,
							   QWidget* parent,Qt::WindowFlags f)
		: QDialog(parent,f)
{
	assert(iSelected < curves.size() && iSelected >= -1);
    setWindowTitle(_Q("切换到Y2轴"));

	QVBoxLayout* layout = new QVBoxLayout;
	QButtonGroup* group = new QButtonGroup(this);

    QRadioButton* btn = new QRadioButton(_Q("[切换到空]"));
	layout->addWidget(btn);
	group->addButton(btn,-1);
	btn->setChecked(true);

	for (size_t i = 0; i < curves.size(); ++i)
	{
		QRadioButton* btn = new QRadioButton(curves[i]->title().text());
		layout->addWidget(btn);
		group->addButton(btn,i);
	}

	m_iSelected = iSelected;
	if (m_iSelected != -1)
		group->button(m_iSelected)->setChecked(true);

	setLayout(layout);

	connect(group,SIGNAL(buttonClicked(int)),SLOT(setSelectedCurve(int)));
}

int SelectCurveDlg::curveSelected() const
{
	return m_iSelected;
}

void SelectCurveDlg::setSelectedCurve(int index)
{
	m_iSelected = index;
}

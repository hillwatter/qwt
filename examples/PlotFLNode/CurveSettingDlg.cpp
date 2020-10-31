/****************************************************************************
** Last Modified: 2011-11-8-001
**
** File Name: CurveSettingDlg.cpp
** Created Time: 2011-11-8 9:40:42
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <qwt_plot_curve.h>
#include "QwtPlotCurveSettingSheet.h"
#include "CurveSettingDlg.h"
#define _Q(s) QStringLiteral(s)

CurveSettingDlg::CurveSettingDlg(QVector<QwtPlotCurve*>& curves,
								 QWidget* parent,Qt::WindowFlags f)
	: QDialog(parent,f)
	, m_curves(curves)
{
    setWindowTitle(_Q("曲线属性"));
	resize(350,365);

	m_listViewCurves = new QListView;
	m_curveSettingSheet = new QwtPlotCurveSettingSheet;
    m_okButton = new QPushButton(_Q("确定"));
	m_okButton->setDefault(true);
    m_applyButton = new QPushButton(_Q("应用"));
    m_cancelButton = new QPushButton(_Q("取消"));

	QVBoxLayout* right = new QVBoxLayout;
	right->addWidget(m_curveSettingSheet);
	QHBoxLayout* buttons_layout = new QHBoxLayout;
	buttons_layout->addWidget(m_okButton);
	buttons_layout->addWidget(m_applyButton);
	buttons_layout->addWidget(m_cancelButton);
	right->addLayout(buttons_layout);

	QSplitter* splitter = new QSplitter;
	splitter->addWidget(m_listViewCurves);
	QWidget* settingSheet = new QWidget;
	right->setMargin(0);
	settingSheet->setLayout(right);
	splitter->addWidget(settingSheet);
	QList<int> sizes;
	sizes.append(LISTVIEW_WIDTH);
	sizes.append(SHEET_WIDTH);
	splitter->setSizes(sizes);

	QHBoxLayout* whole = new QHBoxLayout;
	whole->addWidget(splitter);
	//whole->addWidget(m_listViewCurves);
	//whole->addLayout(right);
	setLayout(whole);

	//connect controls to slots
	connect(m_listViewCurves,SIGNAL(clicked(const QModelIndex&)),
		SLOT(onCurveSelectChanged(const QModelIndex&)));
	connect(m_okButton,SIGNAL(clicked()),SLOT(onOK()));
	connect(m_applyButton,SIGNAL(clicked()),SLOT(onApply()));
	connect(m_cancelButton,SIGNAL(clicked()),SLOT(close()));

	initListView();
}

void CurveSettingDlg::onCurveSelectChanged(const QModelIndex& index)
{
	int i = index.row();
	if (i < 0 || i >= m_curves.size())
		return;

	m_curveSettingSheet->setCurve(m_curves[i]);
}

void CurveSettingDlg::onOK()
{
	onApply();
	close();
}

void CurveSettingDlg::onApply()
{
	m_curveSettingSheet->updateSettings();
	//replot
    Q_EMIT changed(const_cast<QwtPlotCurve*>(m_curveSettingSheet->curve()));
}

void CurveSettingDlg::initListView()
{
	//list view
	QStringList names;
	for (size_t i = 0; i < m_curves.size(); ++i)
	{
		names.append(m_curves[i]->title().text());
	}
	QStringListModel* model = new QStringListModel(names,this);
	m_listViewCurves->setModel(model);
	m_listViewCurves->setCurrentIndex(model->index(0));

	onCurveSelectChanged(m_listViewCurves->currentIndex());
}

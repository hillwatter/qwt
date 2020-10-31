/****************************************************************************
** Last Modified: 2012-2-24-001
**
** File Name: ActiveAxisDlg.cpp
** Created Time: 2012-2-24 11:55:24
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <QVBoxLayout>
#include <QCheckBox>
#include "ActiveAxisDlg.h"
#define _Q(s) QStringLiteral(s)

ActiveAxisDlg::ActiveAxisDlg(bool& x,bool& yLeft,bool& yRight,
							 QWidget* parent,Qt::WindowFlags f)
	: QDialog(parent,f)
	, m_x(x)
	, m_yLeft(yLeft)
	, m_yRight(yRight)
{
    setWindowTitle(_Q("激活设置"));

    m_xCheckBox = new QCheckBox(_Q("x轴"));
	if (m_x)
		m_xCheckBox->setCheckState(Qt::Checked);
    m_yLeftCheckBox = new QCheckBox(_Q("y左轴"));
	if (m_yLeft)
		m_yLeftCheckBox->setCheckState(Qt::Checked);
    m_yRightCheckBox = new QCheckBox(_Q("y右轴"));
	if (m_yRight)
		m_yRightCheckBox->setCheckState(Qt::Checked);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(m_xCheckBox);
	layout->addWidget(m_yLeftCheckBox);
	layout->addWidget(m_yRightCheckBox);
	setLayout(layout);
}

void ActiveAxisDlg::done(int r)
{
    m_x = Qt::Unchecked != m_xCheckBox->checkState();
    m_yLeft = Qt::Unchecked != m_yLeftCheckBox->checkState();
    m_yRight = Qt::Unchecked != m_yRightCheckBox->checkState();

    QDialog::done(r);
}

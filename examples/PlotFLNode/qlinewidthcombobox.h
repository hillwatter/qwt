/****************************************************************************
** Last Modified: 2011-11-8-002
**
** File Name: qlinewidthcombobox.h
** Created Time: 2011-11-7 17:57:05
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __qlinewidthcombobox_h__
#define __qlinewidthcombobox_h__

#include <QComboBox>
#include <QVector>

class QLineWidthComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit QLineWidthComboBox(QWidget *parent=NULL);

	qreal currentWidth() const;
	void setCurrentWidth(qreal width);

	qreal getWidth(int index) const;
	
private:
	void initItems();
	//todo: put all non-const functions here to stop from editting.

private:
	QVector<qreal> m_widths;

};

#endif//__qlinewidthcombobox_h__

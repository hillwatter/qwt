/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QPenSettingSheet.h
** Created Time: 2011-11-8 11:49:09
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QPenSettingSheet_h__
#define __QPenSettingSheet_h__

#include <QPen>
#include <QFrame>
#include <assert.h>

class QLineStyleComboBox;
class QLineWidthComboBox;
class QColorButton;
class QPushButton;

class  QPenSettingSheet : public QFrame
{
	Q_OBJECT
public:
	static const int WIDTH = 205;
	static const int HEIGHT = 150;
public:
	QPenSettingSheet(const QPen& pen=QPen(),
		QWidget* parent=NULL,Qt::WindowFlags f=0);

	const QPen& pen() const;
	void setPen(const QPen& pen);

Q_SIGNALS:
	void changed(const QPen&);

protected Q_SLOTS:
	void onStyleChanged(int);
	void onWidthChanged(int);
	void onColorChanged(const QColor&);

private:
	QLineStyleComboBox* m_styleComboBox;
	QLineWidthComboBox* m_widthComboBox;
	QColorButton* m_colorButton;

	class PreviewFrame;
	PreviewFrame* m_previewFrame;

};

#endif//__QPenSettingSheet_h__

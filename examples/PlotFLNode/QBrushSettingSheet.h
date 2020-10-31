/****************************************************************************
** Last Modified: 2011-11-14-002
**
** File Name: QBrushSettingSheet.h
** Created Time: 2011-11-14 11:35:47
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QBrushSettingSheet_h__
#define __QBrushSettingSheet_h__

#include <QBrush>
#include <QFrame>
//#include "qtguiex_global.h"

class QComboBox;
class QColorButton;
class QPushButton;

class QBrushSettingSheet : public QFrame
{
	Q_OBJECT
public:
	QBrushSettingSheet(const QBrush& brush=QBrush(),
		QWidget* parent=NULL,Qt::WindowFlags f=0);

	const QBrush& brush() const;
	void setBrush(const QBrush& brush);

Q_SIGNALS:
	void changed(const QBrush&);

protected Q_SLOTS:
	void onStyleChanged(int);
	void onColorChanged(const QColor&);
	void onChangePixmap();

private:
	void initSytleComboBox();

private:
	QComboBox* m_comboboxStyle;
	QColorButton* m_colorButton;
	QPushButton* m_buttonPixmap;

	class PreviewFrame;
	PreviewFrame* m_previewFrame;
};
#endif//__QBrushSettingSheet_h__

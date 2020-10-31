/****************************************************************************
** Last Modified: 2011-11-14-001
**
** File Name: QwtSymbolSettingSheet.h
** Created Time: 2011-11-14 11:22:20
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QwtSymbolSettingSheet_h__
#define __QwtSymbolSettingSheet_h__

#include <QFrame>
#include <qwt_symbol.h>

class QComboBox;
class QBrushSettingSheet;
class QPenSettingSheet;
class QSpinBox;

class QwtSymbolSettingSheet : public QFrame
{
public:
	QwtSymbolSettingSheet(const QwtSymbol& symbol=QwtSymbol(),
		QWidget* parent=NULL,Qt::WindowFlags f=0);

	const QwtSymbol& symbol();
	void setSymbol(const QwtSymbol& symbol);

Q_SIGNALS:
	void changed(const QwtSymbol&);


private:
	void initSytleComboBox();
	void updateSettings(bool save=true);

private:
	QwtSymbol m_symbol;

	QComboBox* m_comboboxStyle;
	QBrushSettingSheet* m_brushSettingSheet;
	QPenSettingSheet* m_penSettingSheet;
	QSpinBox* m_spinBoxWidth;
	QSpinBox* m_spinBoxHeight;

};
#endif//__QwtSymbolSettingSheet_h__

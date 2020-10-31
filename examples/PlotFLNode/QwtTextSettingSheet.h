/****************************************************************************
** Last Modified: 2011-11-9-001
**
** File Name: QwtTextSettingSheet.h
** Created Time: 2011-11-9 17:09:47
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __QwtTextSettingSheet_h__
#define __QwtTextSettingSheet_h__

#include <qwt_text.h>
#include <QFrame>
#include <QColorButton.h>

class QCheckBox;
class QLineEdit;
class QComboBox;

// .NAME 
// .SECTION Description
// .SECTION Caveats
// .SECTION See Also
class QwtTextSettingSheet : public QFrame
{
	Q_OBJECT
public:
	static const int WIDTH = 205;
	static const int HEIGHT = 100;

public:
	QwtTextSettingSheet(const QwtText& text=QwtText(),
		QWidget* parent=NULL,Qt::WindowFlags f=0,bool text_show=true);

	const QwtText& text() const;
	void setText(const QwtText& text);

protected Q_SLOTS:
	void onTextChanged();
	void onColorChanged(const QColor&);
	void onChangeFont();

private:
	void updateFontButton()
	{
		QString font = m_qwt_text.font().toString();
		m_buttonFont->setText(font);
	}

private:
	QwtText m_qwt_text;
	
	QLineEdit* m_lineEditText;
	QColorButton* m_colorButton;
	QPushButton* m_buttonFont;
	
	//class PreviewFrame;
	//PreviewFrame* m_previewFrame;
};

#endif//__QwtTextSettingDlg_h__

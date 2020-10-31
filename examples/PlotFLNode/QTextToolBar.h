/****************************************************************************
* @brief:
** Last Modified: 2012-3-22-001
**
** File Name: QTextToolBar.h
** Created Time: 2012-3-22 11:34:34
** Created By: ShaoLing.Jia
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef QTEXTTOOLBAR_H
#define QTEXTTOOLBAR_H

#include <QToolBar>
#include <QFont>

class QComboBox;
class QFontComboBox;


class QTextToolBar : public QToolBar
{
	Q_OBJECT

public:
	QTextToolBar(QWidget *parent);
	~QTextToolBar();

	void SetFont(const QFont &);
	QFont GetFont();

public Q_SLOTS:
	void OnFontChang();

Q_SIGNALS:
	void FontChanged(const QFont &font);

private:

	QFontComboBox *m_fontNameComb;
	QComboBox *m_fontSizeCheck;
	QAction *m_pBold;
	QAction *m_pItalic;
	QAction *m_underline;
		
};

#endif // QTEXTTOOLBAR_H

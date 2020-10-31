/****************************************************************************
* @brief:
** Last Modified: 2012-3-22-001
**
** File Name: QTextSignEdit.h
** Created Time: 2012-3-22 11:34:25
** Created By: ShaoLing.Jia
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef QTEXTSIGNEDIT_H
#define QTEXTSIGNEDIT_H

#include <QTextEdit>

class QTextToolBar;

class QTextSignEdit : public QTextEdit
{
	Q_OBJECT

public:
	QTextSignEdit(QWidget *parent = 0);
	~QTextSignEdit();

	void SetFont(const QFont &font);
	QFont GetFont();

    public Q_SLOTS:
		void show();
		void hide();
		void close();

		/**
		* @brief 字体改变处理槽
		*
		* @param
		*
		* @return
		*/
		void FontChanged(const QFont &font);

		/**
		* @brief 文字改变处理槽
		*
		* @param
		*
		* @return
		*/
		void OnTextChanged();

		/**
		* @brief 显示隐藏工具栏
		*
		* @param
		*
		* @return
		*/
		void OnShowToolBar(bool on = true);

protected:
	virtual void contextMenuEvent(QContextMenuEvent *event);

private:
	/**
	* @brief 根据当前内容动态调整控件大小
	*
	* @param
	*
	* @return
	*/
	void ChangeSize(const QFont &font);
	

private:

	QTextToolBar *m_textToolBar;
};

#endif // QTEXTSIGNEDIT_H

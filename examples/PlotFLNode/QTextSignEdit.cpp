#include "QTextSignEdit.h"
#include "QTextToolBar.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QMainWindow>
 #include <QTextDocument>
#include <qwt_text_engine.h>
#include <qwt_text.h>
#define _Q(s) QStringLiteral(s)

QTextSignEdit::QTextSignEdit(QWidget *parent)
	: QTextEdit(parent)
{
	m_textToolBar =new QTextToolBar(parent);
	m_textToolBar->hide();

	connect(m_textToolBar,SIGNAL(FontChanged(const QFont &)),
		this,SLOT(FontChanged(const QFont &)));
	connect(this,SIGNAL(textChanged()),this,SLOT(OnTextChanged()));

	m_textToolBar->SetFont(font());

	setAlignment(Qt::AlignTop | Qt::AlignLeft);

}

QTextSignEdit::~QTextSignEdit()
{

}

void QTextSignEdit::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu *menu = createStandardContextMenu();

	menu->addSeparator();
    QAction *pToolAct = menu->addAction(_Q("显示工具栏"));
	connect(pToolAct,SIGNAL(triggered(bool)),this,SLOT(show()));

	menu->exec(event->globalPos());
	delete menu;
}

void QTextSignEdit::SetFont(const QFont &font)
{
	m_textToolBar->SetFont(font);
	setFont(font);
}

QFont QTextSignEdit::GetFont()
{
	return m_textToolBar->GetFont();
}

void QTextSignEdit::FontChanged(const QFont &font)
{
	setFont(font);

	//改变编辑框大小	
	ChangeSize(font);
}

void QTextSignEdit::show()
{
	OnShowToolBar(true);

	//调整编辑框大小
	ChangeSize(GetFont());

	QTextEdit::show();
}

void QTextSignEdit::OnShowToolBar(bool on)
{
	if (on)
	{
		QPoint curPos = pos();
		QWidget *parent = qobject_cast<QWidget*>(this->parent());
		if (0x00 != parent)
		{
			curPos = parent->mapToGlobal(curPos);
			m_textToolBar->move(curPos.x() - 50, curPos.y() -50);
		}
		m_textToolBar->show();
	}
	else
	{
		m_textToolBar->hide();
	}
}

void QTextSignEdit::OnTextChanged()
{
	ChangeSize(GetFont());
}

void QTextSignEdit::ChangeSize(const QFont &font)
{
	QwtText text(toPlainText());
	text.setFont(font);

	const QSizeF textSize = text.textSize();
	QFontMetricsF fm(font);

	if (textSize.isEmpty())
	{
		resize(40, textSize.height() + 10);
	}
	else
	{
		resize(textSize.width() + 30, textSize.height() + 10);
	}
}

void QTextSignEdit::hide()
{
	m_textToolBar->hide();
	QTextEdit::hide();
}

void QTextSignEdit::close()
{
	m_textToolBar->hide();
	QTextEdit::close();
}

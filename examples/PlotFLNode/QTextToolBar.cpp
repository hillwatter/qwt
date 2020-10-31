#include "QTextToolBar.h"

#include <QComboBox>
#include <QFontComboBox>
#include <QFontDatabase>
#include <QAction>
#define _Q(s) QStringLiteral(s)

QTextToolBar::QTextToolBar(QWidget *parent)
	: QToolBar(parent)
{
	m_fontNameComb = new QFontComboBox(this);
	addWidget(m_fontNameComb);

	QFontDatabase fontdatabase;
	m_fontNameComb->addItems(fontdatabase.families());

	m_fontSizeCheck = new QComboBox(this);
	addWidget(m_fontSizeCheck);

	QList<int> sizeList = fontdatabase.standardSizes();
//    foreach(int isize, sizeList)
    for(int i = 0; i < sizeList.size(); ++i)
	{
        int isize = sizeList[i];
		QString str;
		str.setNum(isize);
		m_fontSizeCheck->addItem(str);
	}
	
	QFont boldFont;
	boldFont.setBold(true);
    m_pBold = addAction(_Q("B"));
	m_pBold->setFont(boldFont);
	m_pBold->setCheckable(true);

	QFont italicfont;
	italicfont.setItalic(true);
    m_pItalic = addAction(_Q("I"));
	m_pItalic->setFont(italicfont);
	m_pItalic->setCheckable(true);

	QFont underlinefont;
	underlinefont.setUnderline(true);
    m_underline = addAction(_Q("U"));
	m_underline->setFont(underlinefont);
	m_underline->setCheckable(true);	

	setFloatable(true);
	setMovable(true);

	connect(m_fontNameComb,SIGNAL(currentFontChanged(const QFont &)),this,SLOT(OnFontChang()));
	connect(m_fontSizeCheck,SIGNAL(currentIndexChanged(int)),this,SLOT(OnFontChang()));
	connect(m_pBold,SIGNAL(triggered()),this,SLOT(OnFontChang()));
	connect(m_pItalic,SIGNAL(triggered()),this,SLOT(OnFontChang()));
	connect(m_underline,SIGNAL(triggered()),this,SLOT(OnFontChang()));

	setWindowFlags(Qt::Tool);
	setWindowIcon(QIcon(".img/app/main.png"));

    setWindowTitle(_Q("字体"));
}

QTextToolBar::~QTextToolBar()
{

}

void QTextToolBar::SetFont(const QFont &font)
{
	m_fontNameComb->setCurrentFont(font);

	QString strSize;
	strSize.setNum(font.pointSize());
	int sizeIndex = m_fontSizeCheck->findText(strSize);
	if (-1 != sizeIndex)
	{
		m_fontSizeCheck->setCurrentIndex(sizeIndex);
	}

	m_pBold->setChecked(font.bold());
	m_pItalic->setChecked(font.italic());
	m_underline->setChecked(font.underline());
}

QFont QTextToolBar::GetFont()
{
	QFont font = m_fontNameComb->currentFont();

	QString strSize = m_fontSizeCheck->currentText();
	font.setPointSize(strSize.toInt());
	font.setBold(m_pBold->isChecked());
	font.setItalic(m_pItalic->isChecked());
	font.setUnderline(m_underline->isChecked());

	return font;
}

void QTextToolBar::OnFontChang()
{
    Q_EMIT FontChanged(GetFont());
}

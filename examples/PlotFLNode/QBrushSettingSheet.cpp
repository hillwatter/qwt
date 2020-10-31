/****************************************************************************
** Last Modified: 2011-11-14-002
**
** File Name: QBrushSettingSheet.cpp
** Created Time: 2011-11-14 11:36:54
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#include <assert.h>
#include <QPainter>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QVariant>
#include "QColorButton.h"
#include "QBrushSettingSheet.h"
#define _Q(s) QStringLiteral(s)

class QBrushSettingSheet::PreviewFrame : public QFrame
{
public:
	const static int MIN_H = 50;

public:
	PreviewFrame(QWidget* parent=NULL,Qt::WindowFlags f=0)
		: QFrame(parent,f)
	{
		setFixedHeight(MIN_H);
		setFrameShape(QFrame::Panel);
		setFrameShadow(QFrame::Plain);
		setStyleSheet("background-color:#FFFFFF");
	}

	QBrush brush;

protected:
	virtual void paintEvent(QPaintEvent* event)
	{
		QFrame::paintEvent(event);
		QPainter painter(this);

		painter.setBrush(brush);
		painter.drawRect(rect());
	}
};

QBrushSettingSheet::QBrushSettingSheet(const QBrush& brush,
									   QWidget* parent,Qt::WindowFlags f)
	: QFrame(parent,f)
{
	m_comboboxStyle = new QComboBox;
	initSytleComboBox();

	m_colorButton = new QColorButton;
	m_buttonPixmap = new QPushButton;
    m_buttonPixmap->setText(_Q("点击选择图片..."));
	m_previewFrame = new PreviewFrame;

	QGridLayout* gridLayout = new QGridLayout;
	int margin = 0;
	gridLayout->getContentsMargins(0,0,0,&margin);
	gridLayout->setContentsMargins(0,margin,0,margin);
	gridLayout->setColumnStretch(0,0);
	gridLayout->setColumnStretch(1,1);

    gridLayout->addWidget(new QLabel(_Q("类型：")),0,0);
    gridLayout->addWidget(new QLabel(_Q("颜色：")),1,0);
    gridLayout->addWidget(new QLabel(_Q("纹理：")),2,0);
    gridLayout->addWidget(new QLabel(_Q("预览：")),3,0);

	gridLayout->addWidget(m_comboboxStyle,0,1);
	gridLayout->addWidget(m_colorButton,1,1);
	gridLayout->addWidget(m_buttonPixmap,2,1);
	gridLayout->addWidget(m_previewFrame,3,1);
	setLayout(gridLayout);

	//connects
	connect(m_comboboxStyle,SIGNAL(currentIndexChanged(int)),
		SLOT(onStyleChanged(int)));
	connect(m_colorButton,SIGNAL(colorChanged(const QColor&)),
		SLOT(onColorChanged(const QColor&)));
	connect(m_buttonPixmap,SIGNAL(clicked()),SLOT(onChangePixmap()));

	setBrush(brush);
}

const QBrush& QBrushSettingSheet::brush() const
{
	return m_previewFrame->brush;
}

void QBrushSettingSheet::setBrush(const QBrush& brush)
{
    int index = m_comboboxStyle->findData(QVariant((int)brush.style()));
    m_comboboxStyle->setCurrentIndex(index);
    m_colorButton->setColor(brush.color());
	
    m_previewFrame->brush = brush;
    m_previewFrame->update();
}

void QBrushSettingSheet::onStyleChanged(int i)
{
	Qt::BrushStyle style = (Qt::BrushStyle)m_comboboxStyle->itemData(i).toInt();
	m_previewFrame->brush.setStyle(style);
	m_previewFrame->update();

    Q_EMIT changed(m_previewFrame->brush);
}

void QBrushSettingSheet::onColorChanged(const QColor& c)
{
	m_previewFrame->brush.setColor(c);
	m_previewFrame->update();

    Q_EMIT changed(m_previewFrame->brush);
}

void QBrushSettingSheet::onChangePixmap()
{
	static QString dir("D:\\");
	QString filter = "Images (*.bmp *.png *.xpm *.jpg)";
	QString selected_filter;
    QString file = QFileDialog::getOpenFileName(this,_Q("图片"),
		dir,filter,&selected_filter);
	dir = file.mid(0,file.lastIndexOf(QChar('/')));

	QPixmap pixmap(file);
	m_previewFrame->brush.setTexture(pixmap);
	m_previewFrame->update();

    Q_EMIT changed(m_previewFrame->brush);
}

void QBrushSettingSheet::initSytleComboBox()
{
	assert(m_comboboxStyle != NULL);

    m_comboboxStyle->addItem(_Q("NoBrush"),QVariant((int)Qt::NoBrush));
    m_comboboxStyle->addItem(_Q("SolidPattern"),QVariant((int)Qt::SolidPattern));
    m_comboboxStyle->addItem(_Q("Dense1Pattern"),QVariant((int)Qt::Dense1Pattern));
    m_comboboxStyle->addItem(_Q("Dense2Pattern"),QVariant((int)Qt::Dense2Pattern));
    m_comboboxStyle->addItem(_Q("Dense3Pattern"),QVariant((int)Qt::Dense3Pattern));
    m_comboboxStyle->addItem(_Q("Dense4Pattern"),QVariant((int)Qt::Dense4Pattern));
    m_comboboxStyle->addItem(_Q("Dense5Pattern"),QVariant((int)Qt::Dense5Pattern));
    m_comboboxStyle->addItem(_Q("Dense6Pattern"),QVariant((int)Qt::Dense6Pattern));
    m_comboboxStyle->addItem(_Q("Dense7Pattern"),QVariant((int)Qt::Dense7Pattern));
    m_comboboxStyle->addItem(_Q("HorPattern"),QVariant((int)Qt::HorPattern));
    m_comboboxStyle->addItem(_Q("VerPattern"),QVariant((int)Qt::VerPattern));
    m_comboboxStyle->addItem(_Q("CrossPattern"),QVariant((int)Qt::CrossPattern));
    m_comboboxStyle->addItem(_Q("BDiagPattern"),QVariant((int)Qt::BDiagPattern));
    m_comboboxStyle->addItem(_Q("FDiagPattern"),QVariant((int)Qt::FDiagPattern));
    m_comboboxStyle->addItem(_Q("DiagCrossPattern"),QVariant((int)Qt::DiagCrossPattern));
    m_comboboxStyle->addItem(_Q("LinearGradientPattern"),QVariant((int)Qt::LinearGradientPattern));
    m_comboboxStyle->addItem(_Q("RadialGradientPattern"),QVariant((int)Qt::RadialGradientPattern));
    m_comboboxStyle->addItem(_Q("ConicalGradientPattern"),QVariant((int)Qt::ConicalGradientPattern));
    m_comboboxStyle->addItem(_Q("TexturePattern"),QVariant((int)Qt::TexturePattern));
}

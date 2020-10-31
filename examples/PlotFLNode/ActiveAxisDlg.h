/****************************************************************************
** Last Modified: 2012-2-24-001
**
** File Name: ActiveAxisDlg.h
** Created Time: 2012-2-24 11:41:18
** Created By: Xianliang Zeng
**
** Copyright (c) APPSOFT
** All rights reserved.
****************************************************************************/
#ifndef __ActiveAxisDlg_h__
#define __ActiveAxisDlg_h__

#include <QDialog>

class QCheckBox;

class ActiveAxisDlg : public QDialog
{
    Q_OBJECT
public:
    ActiveAxisDlg(bool& x,bool& yLeft,bool& yRight,
                  QWidget* parent=NULL,Qt::WindowFlags f=0);


public Q_SLOTS:
    void done(int);

private:
    bool& m_x;
    bool& m_yLeft;
    bool& m_yRight;

    QCheckBox* m_xCheckBox;
    QCheckBox* m_yLeftCheckBox;
    QCheckBox* m_yRightCheckBox;
};
#endif//__ActiveAxisDlg_h__

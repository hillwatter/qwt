/*=========================================================================

  Program:   TestExpert
  Module:    QShareActionsMngr.cpp
  Author:    Xianliang Zeng

  Created:        2011-10-17
  Last Modified:  2011-10-17

  Copyright (c) APPSOFT
  All rights reserved.

=========================================================================*/
#include "QShareActionsMngr.h"
#include <assert.h>


void QShareActionsMngr::registerWidget(QWidget* w)
{
	if (w != NULL)
		m_w2states.insert(std::make_pair(w,m_initStates));
}

void QShareActionsMngr::unregisterWidget(QWidget* w)
{
	if (m_w2states.count(w))
	{
		if (w == m_current_w)
			connectWidget(NULL);

		m_w2states.erase(w);
	}
}

void QShareActionsMngr::connectWidget(QWidget* w)
{
	if (m_current_w == w)
		return;
	
	if (m_current_w != NULL)
	{
		//save states
		updateStates(true);
		for (size_t i = 0; i < m_connects.size(); ++i)
			disconnect(m_connects[i].sender,m_connects[i].signal,
			m_current_w,m_connects[i].method);
	}

	m_current_w = w;
	if (m_current_w == NULL)
	{
		show(false);
		return;
	}

	for (size_t i = 0; i < m_connects.size(); ++i)
		connect(m_connects[i].sender,m_connects[i].signal,
		m_current_w,m_connects[i].method,m_connects[i].type);
	updateStates(false);
}

void QShareActionsMngr::show(bool on)
{
	std::map<QAction*,_ACTION_STATE>::iterator it = m_initStates.begin();
	for (; it != m_initStates.end(); ++it)
		it->first->setVisible(on);
}

void QShareActionsMngr::updateStates(bool save)
{
	assert(m_current_w != NULL);
	assert(m_w2states.count(m_current_w) > 0);
	ACTION2STATE& states = m_w2states[m_current_w];

	std::map<QAction*,_ACTION_STATE>::iterator it = states.begin();
	for (; it != states.end(); ++it)
		it->second.update(it->first,save);
}
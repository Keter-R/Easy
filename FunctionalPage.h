#pragma once
#include <qwidget.h>
#include "Protocol.h"
#include "ui_FunctionalPage.h"

class FunctionalPage :
    public QWidget
{
    Q_OBJECT
	public:
		FunctionalPage(DataFormation::User user, QWidget* parent = nullptr);
	    ~FunctionalPage();
	private:
		Ui::FunctionalPageWidget ui;
		DataFormation::User currentUser;
};


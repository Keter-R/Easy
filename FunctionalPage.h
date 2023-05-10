#pragma once
#include <qwidget.h>
#include "Protocol.h"
#include "ui_FunctionalPage.h"
#include <QMouseEvent>

class FunctionalPage :
    public QWidget
{
    Q_OBJECT
	public:
		FunctionalPage(DataFormation::User user, QWidget* parent = nullptr);
	    ~FunctionalPage();
		void refreshAvatar();
		void changeAvatar(QImage img);
		void mousePressEvent(QMouseEvent* event) override;

	private:
		Ui::FunctionalPageWidget ui;
		DataFormation::User currentUser;
};


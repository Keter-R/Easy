#pragma once
#include <qwidget.h>
#include "Formation.h"
#include "Protocol.h"
#include "ui_ContactsPage.h"
#include "ContactsListWidget.h"

class ContactsPage :
    public QWidget
{
    Q_OBJECT
    public:
        ContactsPage(DataFormation::User user, QWidget* parent = nullptr);
	    ~ContactsPage();
        void refresh();

    private:
        Ui::ContactsPageWidget ui;
        DataFormation::User user;

    signals:
        void chatTo(QString account);
};


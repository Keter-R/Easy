#pragma once
#include <qwidget.h>
#include "ui_MainPage.h"
#include "Protocol.h"
#include "ContactsPage.h"
#include "FunctionalPage.h"


class MainPage :
    public QWidget
{
    Q_OBJECT
    public:
        MainPage(DataFormation::User currentUser, QWidget* parent = nullptr);
        ~MainPage();
    private:
        Ui::MainPageWidget ui;
        DataFormation::User currentUser;
        ContactsPage* contactsPage;
        FunctionalPage* functionalPage;

};


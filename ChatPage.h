#pragma once
#include <qwidget.h>
#include "ui_ChatPage.h"


class ChatPage :
    public QWidget
{
    Q_OBJECT
    public:
		ChatPage(QString user, QWidget* parent = nullptr);
        void setCurrentChaterAccount(QString account);
		~ChatPage();

    private:
        Ui::ChatPageWidget ui;
        QString currentUserAccount;
        QString currentChaterAccount;
};


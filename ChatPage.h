#pragma once
#include <qwidget.h>
#include "ui_ChatPage.h"
#include "Formation.h"
#include <set>

class ChatPage :
    public QWidget
{
    Q_OBJECT
    public:
		ChatPage(QString user, QWidget* parent = nullptr);
        void setCurrentChaterAccount(QString account);
		~ChatPage();
        void refresh(bool forced = false);
        void startAutoRefresh();
        void stopAutoRefresh();

    private:
        std::set<DataFormation::Message> displayedMessages;
        Ui::ChatPageWidget ui;
        QString currentUserAccount;
        QString currentChaterAccount;
        QTimer* refreshTimer;
};


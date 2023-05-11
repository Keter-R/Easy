#pragma once
#include <qwidget.h>
#include "Formation.h"
#include "ui_MessageListWidgetItem.h"

class MessageListWidgetItem :
    public QWidget
{
    Q_OBJECT
    public:
        MessageListWidgetItem(DataFormation::User sender, DataFormation::Message message, bool isSelf, QWidget* parent = nullptr);
		~MessageListWidgetItem();

    private:
        Ui::MessageListWidgetItem ui;
};


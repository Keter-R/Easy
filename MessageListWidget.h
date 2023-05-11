#pragma once
#include <qlistwidget.h>
#include "Formation.h"
#include "MessageListWidgetItem.h"

class MessageListWidget :
    public QListWidget
{
    Q_OBJECT
    public:
        MessageListWidget(QWidget* parent = nullptr);
        ~MessageListWidget();
        void addMessage(DataFormation::User sender, DataFormation::Message message, bool isSelf, int pos = -1);
};


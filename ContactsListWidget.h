#pragma once
#include <qlistwidget.h>
#include "ContactsListWidgetItem.h"

class ContactsListWidget :
    public QListWidget
{
    Q_OBJECT
    public:
        ContactsListWidget(QWidget* parent = nullptr);
        ~ContactsListWidget();
        void addItem(const QString& name, const QString& account);

    signals:
        void itemDoubleClicked(QString account);
};



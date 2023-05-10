#pragma once
#include <QListWidget>

class ContactsListWidgetItem :
    public QWidget
{
	Q_OBJECT
    public:
		ContactsListWidgetItem(QListWidget* parent = nullptr);
		ContactsListWidgetItem(QString name, QString account, QListWidget* parent = nullptr);
		~ContactsListWidgetItem();
	private:
		QString name;
		QString account;
};


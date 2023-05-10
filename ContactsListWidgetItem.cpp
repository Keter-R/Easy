#include "ContactsListWidgetItem.h"
#include <QLayout>
#include <QGridLayout>
#include <QLabel>

ContactsListWidgetItem::ContactsListWidgetItem(QListWidget* parent)
	: QWidget(parent)
{
}

ContactsListWidgetItem::ContactsListWidgetItem(QString name, QString account, QListWidget* parent)
	: QWidget(parent)
{
	this->name = name;
	this->account = account;
	this->setLayout(new QGridLayout(this));
	this->layout()->setContentsMargins(0, 0, 0, 0);
	QLabel* nameLabel = new QLabel(name, this);
	nameLabel->setStyleSheet("font-size: 20px;color: blue;");
	this->layout()->addWidget(nameLabel);
	QLabel* accountLabel = new QLabel("       " + account, this);
	accountLabel->setStyleSheet("font-size: 12px;");
	this->layout()->addWidget(accountLabel);
}

ContactsListWidgetItem::~ContactsListWidgetItem()
{
}

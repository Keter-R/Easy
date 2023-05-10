#include "ContactsListWidget.h"

ContactsListWidget::ContactsListWidget(QWidget* parent)
	: QListWidget(parent)
{
	connect(this, &QListWidget::itemDoubleClicked, [=](QListWidgetItem* item) {
		emit itemDoubleClicked(item->data(Qt::UserRole).toString());
		});
	this->setSpacing(5);
}

ContactsListWidget::~ContactsListWidget()
{
}

void ContactsListWidget::addItem(const QString& name, const QString& account)
{
	ContactsListWidgetItem* item = new ContactsListWidgetItem(name, account, this);
	QListWidgetItem* listItem = new QListWidgetItem(this);
	listItem->setBackgroundColor(Qt::lightGray);
	listItem->setSizeHint(QSize(0, 50));
	listItem->setData(Qt::UserRole, account);
	this->setItemWidget(listItem, item);
}
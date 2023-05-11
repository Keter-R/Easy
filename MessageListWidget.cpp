#include "MessageListWidget.h"

MessageListWidget::MessageListWidget(QWidget* parent)
	: QListWidget(parent)
{
}

MessageListWidget::~MessageListWidget()
{
}

void MessageListWidget::addMessage(DataFormation::User sender, DataFormation::Message message, bool isSelf, int pos)
{
	MessageListWidgetItem* itemWidget = new MessageListWidgetItem(sender, message, isSelf);
	QListWidgetItem* item = new QListWidgetItem(this);
	item->setSizeHint(itemWidget->sizeHint());
	this->setItemWidget(item, itemWidget);
	if (pos == -1)
	{
		this->addItem(item);
	}
	else
	{
		this->insertItem(pos, item);
	}
}
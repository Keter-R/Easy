#include "MessageListWidgetItem.h"

MessageListWidgetItem::MessageListWidgetItem(DataFormation::User sender, DataFormation::Message message, bool isSelf, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.avatarLabel->setPixmap(QPixmap::fromImage(sender.getRoundAvatar(40)));
	ui.timeLabel->setText(message.time);
	if (isSelf)
	{
		this->setLayoutDirection(Qt::RightToLeft);
		ui.timeLabel->setAlignment(Qt::AlignRight);
	}
	else
	{
		this->setLayoutDirection(Qt::LeftToRight);
		ui.timeLabel->setAlignment(Qt::AlignLeft);
	}
}

MessageListWidgetItem::~MessageListWidgetItem()
{
}
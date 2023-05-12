#include "MessageListWidgetItem.h"
#include <QPushButton>

MessageListWidgetItem::MessageListWidgetItem(DataFormation::User sender, DataFormation::Message message, bool isSelf, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.avatarLabel->setPixmap(QPixmap::fromImage(sender.getRoundAvatar(40)));
	ui.timeLabel->setText(message.time);
	DataFormation::MessageContent content = DataFormation::toMessageContent(message.content);
	if (content.type == "Text")
	{
		QLabel* textLabel = new QLabel(content.content, this);
		textLabel->setWordWrap(true);
		textLabel->setAlignment(Qt::AlignLeft);
		ui.contentWidget->layout()->addWidget(textLabel);
	}
	else if (content.type == "Image")
	{
		QWidget* imageWidget = new QWidget(this);
		QVBoxLayout* layout = new QVBoxLayout(imageWidget);
		QPushButton* imageBtton = new QPushButton(imageWidget);
		imageBtton->setFlat(true);
		imageBtton->setStyleSheet("border: none;");
		imageBtton->setIconSize(QSize(250, 250));
		imageBtton->setIcon(QPixmap::fromImage(DataFormation::toQImage(content.content)).scaled(250, 250, Qt::KeepAspectRatio));
		layout->addWidget(imageBtton);
		imageWidget->setLayout(layout);
		ui.contentWidget->layout()->addWidget(imageWidget);
		connect(imageBtton, &QPushButton::clicked, [=]()
			{
				QWidget* imageWidget = new QWidget();
				QVBoxLayout* layout = new QVBoxLayout(imageWidget);
				QPushButton* imageBtton = new QPushButton(imageWidget);
				imageBtton->setFlat(true);
				imageBtton->setStyleSheet("border: none;");
				imageBtton->setIcon(QPixmap::fromImage(DataFormation::toQImage(content.content)));
				imageWidget->setBaseSize(QPixmap::fromImage(DataFormation::toQImage(content.content)).scaled(1000, 1000, Qt::KeepAspectRatio).size());
				imageBtton->setIconSize(QSize(imageWidget->width(), imageWidget->height()));
				layout->addWidget(imageBtton);
				imageWidget->setLayout(layout);
				imageWidget->show();
			});


	}
	if (isSelf)
	{
		this->setLayoutDirection(Qt::RightToLeft);
		ui.contentWidget->setLayoutDirection(Qt::RightToLeft);
		ui.timeLabel->setAlignment(Qt::AlignRight);
	}
	else
	{
		this->setLayoutDirection(Qt::LeftToRight);
		ui.contentWidget->setLayoutDirection(Qt::LeftToRight);
		ui.timeLabel->setAlignment(Qt::AlignLeft);
	}
}

MessageListWidgetItem::~MessageListWidgetItem()
{
}
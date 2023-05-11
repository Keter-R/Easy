#include "ChatPage.h"
#include "Protocol.h"
#include <QMap>
#include <QTimer>

ChatPage::ChatPage(QString user, QWidget* parent) :currentUserAccount(user), QWidget(parent)
{
	ui.setupUi(this);
	refreshTimer = nullptr;
	connect(ui.sendButton, &QPushButton::clicked, this, [=]() {
		if (ui.textContent->toPlainText().isEmpty())
		{
			return;
		}
		DataFormation::Message msg;
		msg.sender = currentUserAccount;
		msg.receiver = currentChaterAccount;
		msg.content = ui.textContent->toPlainText();
		msg.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		RawSolution::Protocol::Instance()->addMessage(msg);
		ui.textContent->clear();
		this->refresh();
	});	
}

ChatPage::~ChatPage()
{
}

void ChatPage::setCurrentChaterAccount(QString account)
{
	if (account == currentUserAccount || account.isEmpty())
	{
		return;
	}
	currentChaterAccount = account;
	if(account[0] != 'R')
		ui.nameLabel->setText("Friend: " + RawSolution::Protocol::Instance()->getUser(account).name);
	else
		ui.nameLabel->setText("Chat Room: " + RawSolution::Protocol::Instance()->getChatRoom(account).name);
	this->refresh(true);
}

void ChatPage::refresh(bool forced)
{
	QMap<QString, DataFormation::User> users;
	if (forced)
	{
		displayedMessages.clear();
		ui.MessageList->clear();
	}
	QVector<DataFormation::Message> messages;
	if (currentChaterAccount[0] != 'R')
	{
		messages = RawSolution::Protocol::Instance()->getBiMessages(currentUserAccount, currentChaterAccount);
	}
	else
	{
		messages = RawSolution::Protocol::Instance()->getRoomMessages(currentChaterAccount);
	}
	for (auto msg : messages)
	{
		if (displayedMessages.find(msg) == displayedMessages.end())
		{
			displayedMessages.insert(msg);
			if (users.find(msg.sender) == users.end())
			{
				users.insert(msg.sender, RawSolution::Protocol::Instance()->getUser(msg.sender));
			}
			ui.MessageList->addMessage(users[msg.sender], msg, msg.sender == currentUserAccount);
			ui.MessageList->scrollToBottom();
		}
	}
}

void ChatPage::startAutoRefresh()
{
	refreshTimer = new QTimer(this);
	connect(refreshTimer, &QTimer::timeout, this, [=]() {
		this->refresh();
	});
	refreshTimer->start(400);
}

void ChatPage::stopAutoRefresh()
{
	if(refreshTimer && refreshTimer->isActive())
		refreshTimer->stop();
}
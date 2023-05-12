#include "ChatPage.h"
#include "Protocol.h"
#include <QMap>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextImageFormat>
#include <QTextBlock>


// emoji: (\xf0\x9f\x98\x80) to (\xf0\x9f\x98\x8A)
QString emojis[10] = { "\xf0\x9f\x98\x80", "\xf0\x9f\x98\x81", "\xf0\x9f\x98\x82", "\xf0\x9f\x98\x83", "\xf0\x9f\x98\x84", "\xf0\x9f\x98\x85", "\xf0\x9f\x98\x86", "\xf0\x9f\x98\x87", "\xf0\x9f\x98\x88", "\xf0\x9f\x98\x89" };

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
		DataFormation::MessageContent content;
		msg.sender = currentUserAccount;
		msg.receiver = currentChaterAccount;
		content.type = "Text";
		content.content = ui.textContent->toPlainText();
		msg.content = DataFormation::toQString(content);
		msg.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		RawSolution::Protocol::Instance()->addMessage(msg);
		ui.textContent->clear();
		this->refresh();
	});	
	connect(ui.uploadButton, &QPushButton::clicked, this, [=]() {
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Image Files (*.png *.jpg *.bmp)"));
		if (fileName.isEmpty())
		{
			return;
		}
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			return;
		}
		// convert image to base64
		QByteArray data = file.readAll().toBase64();
		file.close();
		DataFormation::MessageContent content;
		content.type = "Image";
		content.content = data;
		DataFormation::Message msg;
		msg.sender = currentUserAccount;
		msg.receiver = currentChaterAccount;
		msg.content = DataFormation::toQString(content);
		msg.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		RawSolution::Protocol::Instance()->addMessage(msg);
		this->refresh();
	});
	connect(ui.emojiButton, &QPushButton::clicked, this, [=]() {
		QMenu* menu = new QMenu(this);
		QAction* action;
		for (int i = 0; i < 10; i++)
		{
			action = new QAction(emojis[i], this);
			connect(action, &QAction::triggered, this, [=]() {
				QTextCursor cursor = ui.textContent->textCursor();
				cursor.insertText(action->text());
				ui.textContent->setTextCursor(cursor);
			});
			menu->addAction(action);
		}
		menu->exec(QCursor::pos());
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
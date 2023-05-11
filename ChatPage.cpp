#include "ChatPage.h"
#include "Protocol.h"

ChatPage::ChatPage(QString user, QWidget* parent) :currentUserAccount(user), QWidget(parent)
{
	ui.setupUi(this);
	
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
}

void ChatPage::refresh()
{

}
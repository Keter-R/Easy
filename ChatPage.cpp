#include "ChatPage.h"

ChatPage::ChatPage(QString user, QWidget* parent) :currentUserAccount(user), QWidget(parent)
{
	ui.setupUi(this);
	
}

ChatPage::~ChatPage()
{
}

void ChatPage::setCurrentChaterAccount(QString account)
{
	currentChaterAccount = account;
}
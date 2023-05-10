#include "ContactsPage.h"

ContactsPage::ContactsPage(DataFormation::User user, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->user = user;
	this->refresh();
}

ContactsPage::~ContactsPage()
{
}

void ContactsPage::refresh()
{
	user = RawSolution::Protocol::Instance()->getUser(user.account);
	ui.personList->clear();
	for (auto friendAccount : user.friends)
	{
		DataFormation::User friend_ = RawSolution::Protocol::Instance()->getUser(friendAccount);
		ui.personList->addItem(friend_.name, friend_.account);
	}
	ui.groupsList->clear();
	for (auto groupId : user.groups)
	{
		DataFormation::ChatRoom chatRoom = RawSolution::Protocol::Instance()->getChatRoom(groupId);
		ui.groupsList->addItem(chatRoom.name, chatRoom.roomId);
	}
	this->update();
}
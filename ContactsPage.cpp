#include "ContactsPage.h"
#include <QPushButton>
#include <QTimer>
#include <QThread>

ContactsPage::ContactsPage(DataFormation::User user, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->user = user;
	//this->refresh();
	connect(ui.personList, &ContactsListWidget::itemDoubleClicked, [=](QString account) {
		emit chatTo(account);
		});
	connect(ui.groupsList, &ContactsListWidget::itemDoubleClicked, [=](QString roomId) {
		emit chatTo(roomId);
		});
	ui.groupsList->hide();
	ui.personList->hide();
	connect(ui.personButton, &QPushButton::clicked, [=]() {
		if (ui.personList->isHidden())
		{
			ui.personList->show();
			ui.personButton->setIcon(QIcon("src/icon/view.svg"));
		}
		else
		{
			ui.personList->hide();
			ui.personButton->setIcon(QIcon("src/icon/view_off.svg"));
		}
		});
	connect(ui.groupButton, &QPushButton::clicked, [=]() {
		if (ui.groupsList->isHidden())
		{
			ui.groupsList->show();
			ui.groupButton->setIcon(QIcon("src/icon/view.svg"));
		}
		else
		{
			ui.groupsList->hide();
			ui.groupButton->setIcon(QIcon("src/icon/view_off.svg"));
		}
		});
}

ContactsPage::~ContactsPage()
{
}

void ContactsPage::refresh()
{
	ui.personList->clear();
	ui.groupsList->clear();
	user = RawSolution::Protocol::Instance()->getUser(user.account);
	for (auto friendAccount : user.friends)
	{
		DataFormation::User friend_ = RawSolution::Protocol::Instance()->getUser(friendAccount);
		ui.personList->addItem(friend_.name, friend_.account);
	}
	for (auto groupId : user.groups)
	{
		DataFormation::ChatRoom chatRoom = RawSolution::Protocol::Instance()->getChatRoom(groupId);
		ui.groupsList->addItem(chatRoom.name, chatRoom.roomId);
	}
}
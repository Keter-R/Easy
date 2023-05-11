#include "MainPage.h"

MainPage::MainPage(DataFormation::User currentUser, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(600, 800);
	this->setWindowTitle("EasyChat");
	contactsPage = new ContactsPage(currentUser, this);
	functionalPage = new FunctionalPage(currentUser, this);
	chatPage = new ChatPage(currentUser.account, this);
	ui.stackedWidget->addWidget(chatPage);
	ui.stackedWidget->addWidget(contactsPage);
	ui.stackedWidget->addWidget(functionalPage);
	ui.stackedWidget->setCurrentWidget(contactsPage);
	connect(ui.switchContactsPage, &QPushButton::clicked, [=]()
		{
			ui.stackedWidget->setCurrentWidget(contactsPage);
			contactsPage->refresh();
			chatPage->stopAutoRefresh();
		});
	connect(ui.switchFunctioanlPage, &QPushButton::clicked, [=]()
		{
			ui.stackedWidget->setCurrentWidget(functionalPage);
			chatPage->stopAutoRefresh();
		});
	connect(ui.switchChatPage, &QPushButton::clicked, [=]()
		{
			ui.stackedWidget->setCurrentWidget(chatPage);
			chatPage->startAutoRefresh();
		});
	connect(contactsPage, &ContactsPage::chatTo, [=](QString account)
		{
			ui.stackedWidget->setCurrentWidget(chatPage);
			chatPage->setCurrentChaterAccount(account);
			chatPage->startAutoRefresh();
		});
	connect(ui.stackedWidget, &QStackedWidget::currentChanged, [=](int id) {
		if (id == 0)
		{
			ui.switchChatPage->setChecked(true);
		}
		else if (id == 1)
		{
			ui.switchContactsPage->setChecked(true);
		}
		else if (id == 2)
		{
			ui.switchFunctioanlPage->setChecked(true);
		}
		});
}

MainPage::~MainPage()
{
}
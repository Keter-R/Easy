#include "MainPage.h"

MainPage::MainPage(DataFormation::User currentUser, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(600, 800);
	this->setWindowTitle("EasyChat");
	contactsPage = new ContactsPage(currentUser, this);
	functionalPage = new FunctionalPage(currentUser, this);
	ui.stackedWidget->addWidget(contactsPage);
	ui.stackedWidget->addWidget(functionalPage);
	ui.stackedWidget->setCurrentWidget(functionalPage);
	connect(ui.switchContactsPage, &QPushButton::clicked, [=]()
		{
			ui.stackedWidget->setCurrentWidget(contactsPage);
			contactsPage->refresh();
		});
	connect(ui.switchFunctioanlPage, &QPushButton::clicked, [=]()
		{
			ui.stackedWidget->setCurrentWidget(functionalPage);
		});
}

MainPage::~MainPage()
{
}
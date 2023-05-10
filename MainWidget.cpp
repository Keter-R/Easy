#include "MainWidget.h"

MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
{
	this->setFixedSize(600, 800);
	this->setWindowTitle("EasyChat");
	loginPage = new LoginPage(this);
	connect(loginPage, &LoginPage::loginSuccess, [=](DataFormation::User currentUser)
		{
			loginPage->deleteLater();
			mainPage = new MainPage(currentUser, this);
			mainPage->show();
		});
}

MainWidget::~MainWidget()
{
}
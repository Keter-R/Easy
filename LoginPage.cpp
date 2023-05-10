#include "LoginPage.h"
#include <QRegExpValidator>
#include <QMessageBox>

using namespace DataFormation;
using namespace RawSolution;

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.accountLine->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,10}"), this));
    ui.passwordLine->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{1,12}"), this));
    connect(ui.loginButton, &QPushButton::clicked, [=]()
        {
		QString account = ui.accountLine->text();
		QString password = ui.passwordLine->text();
        if (RawSolution::Protocol::Instance()->login(account, password))
        {
			User user = RawSolution::Protocol::Instance()->getUser(account);
			emit loginSuccess(user);
		}
        else
        {
			QMessageBox::warning(this, "Login Failed", "Account or password is wrong!");
		}
	});
}

LoginPage::~LoginPage()
{}

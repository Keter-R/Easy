#pragma once

#include <QtWidgets/QWidget>
#include "ui_LoginPage.h"
#include "Protocol.h"

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private:
    Ui::LoginPageWidget ui;

signals:
    void loginSuccess(DataFormation::User currentUser);
};

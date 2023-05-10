#pragma once
#include <qwidget.h>
#include "LoginPage.h"
#include "MainPage.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private:
    LoginPage* loginPage;
    MainPage* mainPage;

};


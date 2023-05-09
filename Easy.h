#pragma once

#include <QtWidgets/QWidget>
#include "ui_Easy.h"

class Easy : public QWidget
{
    Q_OBJECT

public:
    Easy(QWidget *parent = nullptr);
    ~Easy();

private:
    Ui::EasyClass ui;
};

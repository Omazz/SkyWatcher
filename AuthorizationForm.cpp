#include "AuthorizationForm.h"
#include "ui_AuthorizationForm.h"

AuthorizationForm::AuthorizationForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationForm)
{
    ui->setupUi(this);
}

AuthorizationForm::~AuthorizationForm()
{
    delete ui;
}

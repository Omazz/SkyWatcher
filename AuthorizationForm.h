#ifndef AUTHORIZATIONFORM_H
#define AUTHORIZATIONFORM_H

#include <QDialog>

namespace Ui {
class AuthorizationForm;
}

class AuthorizationForm : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationForm(QWidget *parent = nullptr);
    ~AuthorizationForm();

private:
    Ui::AuthorizationForm *ui;
};

#endif // AUTHORIZATIONFORM_H

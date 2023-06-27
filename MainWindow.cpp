#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openSkyAPI = new OpenSkyAPI(this);
    connect(openSkyAPI, &OpenSkyAPI::updateData, this, &MainWindow::setText);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    openSkyAPI->getStatesInField(36.3, 38.9, 11.0, 18.2);
}

void MainWindow::setText(QString text)
{
    ui->textBrowser->setText(text);
}

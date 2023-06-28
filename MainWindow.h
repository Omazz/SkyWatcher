#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "OpenSkyAPI.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QtCore>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void setText(QString text);

private:
    Ui::MainWindow* ui;
    OpenSkyAPI* m_openSkyAPI;

    QGraphicsScene* m_mainMapScene;
    QGraphicsPixmapItem* m_mainMapImage;

    QGraphicsScene* m_overviewMapScene;
    QGraphicsPixmapItem* m_overviewMapImage;
};


#endif // MAINWINDOW_H

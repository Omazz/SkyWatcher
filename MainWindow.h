#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "MapRequester.h"
#include "AircraftRequester.h"
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
    const static quint16 MAIN_MAP_SIZE = 512;
    const static quint16 OVERVIEW_MAP_SIZE = 128;

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void setText(QString text);

    void onUpdateMap(QPixmap map, quint8 x, quint8 y);

    void onUpdateAircrafts(QVector<Aircraft> aircrafts);

    void onChangeMapToMain();

    void on_SB_zoomLevel_valueChanged(int arg1);

    void on_PB_authorization_clicked();

private:
    void drawFields();

    Ui::MainWindow* ui;
    MapRequester* m_mapRequester = nullptr;
    AircraftRequester* m_aircraftRequester = nullptr;


    QGraphicsScene* m_mainMapScene = nullptr;
    QGraphicsPixmapItem* m_mainMapImage = nullptr;
    QGraphicsPixmapItem* m_fieldMapImage = nullptr;
    QList<QGraphicsLineItem*> m_lines;

    QGraphicsScene* m_overviewMapScene = nullptr;
    QGraphicsPixmapItem* m_overviewMapImage = nullptr;
    QGraphicsRectItem* m_fieldRect = nullptr;
};


#endif // MAINWINDOW_H

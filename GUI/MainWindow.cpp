#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->PB_colorAicrafts->setStyleSheet(QString("background-color: %1; border: 2px solid black;").arg(m_colorAircrafts.name()));
    ui->PB_colorAfterClick->setStyleSheet(QString("background-color: %1; border: 2px solid black;").arg(m_colorAfterClick.name()));
    ui->TW_airplanes->setStyleSheet(QString("QTableWidget::item:selected { background-color: %1; color: %2 }")
                                    .arg(m_colorAfterClick.name()).arg(getFontColor(m_colorAfterClick).name()));

    m_mapRequester = new MapRequester(this);
    m_aircraftRequester = new AircraftRequester(this);

    m_mainMapScene = new AircraftScene(this);
    ui->GV_mainMap->setMain();
    ui->GV_mainMap->setScene(m_mainMapScene);

    m_overviewMapScene = new QGraphicsScene(this);
    ui->GV_overviewMap->setScene(m_overviewMapScene);

    QPixmap pixmap("../Recources/Map.png");

    m_mainMapImage = new QGraphicsPixmapItem(pixmap.scaled(MAIN_MAP_SIZE, MAIN_MAP_SIZE, Qt::KeepAspectRatio));
    m_mainMapScene->addItem(m_mainMapImage);

    m_overviewMapImage = new QGraphicsPixmapItem(pixmap.scaled(OVERVIEW_MAP_SIZE, OVERVIEW_MAP_SIZE, Qt::KeepAspectRatio));
    m_overviewMapScene->addItem(m_overviewMapImage);

    m_mainMapScene->setSceneRect(0, 0, MAIN_MAP_SIZE, MAIN_MAP_SIZE);

    drawFields();

    m_fieldRect = new QGraphicsRectItem(QRectF(0, 0, OVERVIEW_MAP_SIZE - 3, OVERVIEW_MAP_SIZE - 3));
    m_fieldRect->setPen(QPen(Qt::red));
    m_overviewMapScene->addItem(m_fieldRect);

    ui->TW_airplanes->setSelectionMode(QAbstractItemView::NoSelection);
    ui->TW_airplanes->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_mainMapScene, &AircraftScene::clickOnAircrafts, this, &MainWindow::onClickOnAircrafts);
    connect(ui->GV_mainMap, &MapView::clickOnField, m_mapRequester, &MapRequester::onClickOnField);
    connect(ui->GV_mainMap, &MapView::clickOnField, this, &MainWindow::onClickOnField);
    connect(ui->GV_mainMap, &MapView::changeMapToMain, this, &MainWindow::onChangeMapToMain);
    connect(m_mapRequester, &MapRequester::updateMap, this, &MainWindow::onUpdateMap);
    connect(m_aircraftRequester, &AircraftRequester::updateAircrafts, this, &MainWindow::onUpdateAircrafts);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onUpdateMap(QPixmap map, quint8 x, quint8 y) {
    if(m_fieldMapImage != nullptr) {
        return;
    }

    ui->GV_mainMap->setIsField(true);
    ui->SB_zoomLevel->setEnabled(false);
    ui->statusbar->showMessage("Press \"Space\" for return to main map.");

    m_fieldMapImage = new QGraphicsPixmapItem(map.scaled(MAIN_MAP_SIZE, MAIN_MAP_SIZE, Qt::KeepAspectRatio));

    m_overviewMapScene->removeItem(m_fieldRect);
    delete m_fieldRect;
    qreal coef = OVERVIEW_MAP_SIZE / qPow(2, ui->GV_mainMap->zoomLevel());
    m_fieldRect = new QGraphicsRectItem(QRectF(coef*x, coef*y, coef - 3, coef - 3));
    m_fieldRect->setPen(QPen(Qt::red));
    m_overviewMapScene->addItem(m_fieldRect);
    m_mainMapScene->addItem(m_fieldMapImage);
}

void MainWindow::onUpdateAircrafts(QVector<Aircraft> aircrafts) {
    if(aircrafts.isEmpty() || !ui->GV_mainMap->isField()) {
        return;
    }

    if(ui->TW_airplanes->columnCount() != 3) {
        ui->TW_airplanes->setColumnCount(3);
        ui->TW_airplanes->setHorizontalHeaderItem(0, new QTableWidgetItem("ICAO 24"));
        ui->TW_airplanes->setHorizontalHeaderItem(1, new QTableWidgetItem("Country"));
        ui->TW_airplanes->setHorizontalHeaderItem(2, new QTableWidgetItem("Info"));
    }
    for(int i = 0; i < aircrafts.size(); ++i) {
        if(!m_aircraftsItems.contains(aircrafts[i].icao24)) {
            if(!aircrafts[i].longitude_isNull && !aircrafts[i].latitude_isNull) {
                QPair<qreal, qreal> aircraftPoint =
                        GeographicCoordsHandler::fromDegreesToTiles(aircrafts[i].longitude,
                                                                    aircrafts[i].latitude,
                                                                    ui->GV_mainMap->zoomLevel());

                qreal mapX = 512.0 * (aircraftPoint.first - floor(aircraftPoint.first));
                qreal mapY = 512.0 * (aircraftPoint.second - floor(aircraftPoint.second));

                m_aircraftsItems.insert(aircrafts[i].icao24, AircraftGraphicsItem(aircrafts[i].icao24, m_colorAircrafts, false));
                m_aircraftsItems[aircrafts[i].icao24].setPos(mapX, mapY);

                if(!aircrafts[i].true_track_isNull) {
                    m_aircraftsItems[aircrafts[i].icao24].setRotation(aircrafts[i].true_track);
                }

                m_mainMapScene->addItem(&m_aircraftsItems[aircrafts[i].icao24]);
            }

            QTableWidgetItem* icaoItem = new QTableWidgetItem(aircrafts[i].icao24);
            QTableWidgetItem* originCountryItem = new QTableWidgetItem(aircrafts[i].origin_country);
            ui->TW_airplanes->insertRow(ui->TW_airplanes->rowCount());
            ui->TW_airplanes->setItem(ui->TW_airplanes->rowCount() - 1, 0, icaoItem);
            ui->TW_airplanes->setItem(ui->TW_airplanes->rowCount() - 1, 1, originCountryItem);
            ui->TW_airplanes->verticalHeader()->setSectionResizeMode(ui->TW_airplanes->rowCount() - 1,
                                                                     QHeaderView::Fixed);
            AircraftInfoButton* aircraftInfoButton = new AircraftInfoButton();
            aircraftInfoButton->setAircraft(aircrafts[i]);
            aircraftInfoButton->setText("?");
            connect(aircraftInfoButton, &QPushButton::clicked, this, &MainWindow::createAircraftInfoDialog);

            ui->TW_airplanes->setCellWidget(ui->TW_airplanes->rowCount() - 1, 2, aircraftInfoButton);
        } else {

            if(!aircrafts[i].longitude_isNull && !aircrafts[i].latitude_isNull) {
                QPair<qreal, qreal> aircraftPoint =
                        GeographicCoordsHandler::fromDegreesToTiles(aircrafts[i].longitude,
                                                                    aircrafts[i].latitude,
                                                                    ui->GV_mainMap->zoomLevel());

                qreal mapX = 512.0 * (aircraftPoint.first - floor(aircraftPoint.first));
                qreal mapY = 512.0 * (aircraftPoint.second - floor(aircraftPoint.second));


                m_mainMapScene->removeItem(&m_aircraftsItems[aircrafts[i].icao24]);

                bool isSelectedUser = m_aircraftsItems[aircrafts[i].icao24].isSelectedUser();
                m_aircraftsItems[aircrafts[i].icao24] = AircraftGraphicsItem(aircrafts[i].icao24,
                                                                             isSelectedUser ? m_colorAfterClick : m_colorAircrafts,
                                                                             isSelectedUser);
                m_aircraftsItems[aircrafts[i].icao24].setPos(mapX, mapY);

                if(!aircrafts[i].true_track_isNull) {
                    m_aircraftsItems[aircrafts[i].icao24].setRotation(aircrafts[i].true_track);
                }

                m_mainMapScene->addItem(&m_aircraftsItems[aircrafts[i].icao24]);
            }
            // Поиск в таблице нужного самолёта
            for(int rowIndex = 0; rowIndex < ui->TW_airplanes->rowCount(); ++rowIndex) {
                if(ui->TW_airplanes->item(rowIndex, 0)->text() == aircrafts[i].icao24) {
                    QWidget* widget = ui->TW_airplanes->cellWidget(rowIndex, 2);
                    if(widget) {
                        AircraftInfoButton* aircraftInfoButton = dynamic_cast<AircraftInfoButton*>(widget);
                        if(aircraftInfoButton) {
                            aircraftInfoButton->setAircraft(aircrafts[i]);
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < ui->TW_airplanes->rowCount(); ++i) {
        bool seek = false;
        QString currentIcao24 = ui->TW_airplanes->item(i, 0)->text();
        for(int j = 0; j < aircrafts.size(); ++j) {
            if(aircrafts[j].icao24 == currentIcao24) {
                seek = true;
                break;
            }
        }
        if(!seek) {
            m_mainMapScene->removeItem(&m_aircraftsItems[currentIcao24]);
            m_aircraftsItems.remove(currentIcao24);
            ui->TW_airplanes->removeRow(i);
            i--;
        }
    }

    ui->TW_airplanes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->TW_airplanes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->TW_airplanes->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_mainMapScene->update();
}

void MainWindow::onChangeMapToMain() {
    if(!m_fieldMapImage) {
        return;
    }

    if(m_updateTimer) {
        m_updateTimer->stop();
        delete m_updateTimer;
        m_updateTimer = nullptr;
    }

    ui->SB_zoomLevel->setEnabled(true);
    ui->statusbar->clearMessage();
    m_aircraftsItems.clear();
    ui->TW_airplanes->clear();
    ui->TW_airplanes->setColumnCount(0);
    ui->TW_airplanes->setRowCount(0);

    m_overviewMapScene->removeItem(m_fieldRect);
    delete m_fieldRect;
    m_fieldRect = new QGraphicsRectItem(QRectF(0, 0, OVERVIEW_MAP_SIZE - 3, OVERVIEW_MAP_SIZE - 3));
    m_fieldRect->setPen(QPen(Qt::red));
    m_overviewMapScene->addItem(m_fieldRect);

    m_mainMapScene->removeItem(m_fieldMapImage);
    ui->GV_mainMap->setIsField(false);
    delete m_fieldMapImage;
    m_fieldMapImage = nullptr;

    for(int i = 0; i < m_lines.size(); ++i) {
        delete m_lines[i];
    }
    m_lines.clear();
    drawFields();
}

void MainWindow::on_SB_zoomLevel_valueChanged(int arg1) {
    Q_UNUSED(arg1);
    if(ui->GV_mainMap->isField()) {
        return;
    }

    for(int i = 0; i < m_lines.size(); ++i) {
        delete m_lines[i];
    }
    m_lines.clear();
    drawFields();
}

void MainWindow::drawFields() {
    int zoomLevel = ui->SB_zoomLevel->value();
    ui->GV_mainMap->setZoomLevel(zoomLevel);
    int numCells = qPow(2, zoomLevel);
    int cellSize = MAIN_MAP_SIZE / numCells;

    for(int i = 1; i < numCells; ++i) {
        QGraphicsLineItem* rowLine = new QGraphicsLineItem(QLine(0, i * cellSize, MAIN_MAP_SIZE, i * cellSize));
        rowLine->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        QGraphicsLineItem* columnLine = new QGraphicsLineItem(QLine(i * cellSize, 0, i * cellSize, MAIN_MAP_SIZE));
        columnLine->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        m_lines.push_back(rowLine);
        m_lines.push_back(columnLine);
        m_mainMapScene->addItem(rowLine);
        m_mainMapScene->addItem(columnLine);
    }
}

QColor MainWindow::getFontColor(QColor backgroundColor) {
    return ((backgroundColor.redF()*0.299) + (backgroundColor.greenF()*0.587) + (backgroundColor.blueF()*0.114)) < 0.5 ? Qt::white : Qt::black;
}

void MainWindow::createAircraftInfoDialog() {
    QObject* senderObject = sender();
    if (senderObject != nullptr) {
        AircraftInfoButton* aircraftInfoButton = dynamic_cast<AircraftInfoButton*>(senderObject);
        if (aircraftInfoButton != nullptr) {
            m_aircraftInfoDialog = new AircraftInfoDialog(this);
            m_aircraftInfoDialog->setAircraftInfo(aircraftInfoButton->getAircraft());
            ui->TW_airplanes->setEnabled(false);
            connect(m_aircraftInfoDialog, &QDialog::finished, this, &MainWindow::onAircraftInfoDialogFinished);
            m_aircraftInfoDialog->show();
        }
    }
}

void MainWindow::onAircraftInfoDialogFinished(int result) {
    Q_UNUSED(result);
    ui->TW_airplanes->setEnabled(true);
    m_aircraftInfoDialog = nullptr;
}

void MainWindow::onClickOnAircrafts(QVector<QString> aircrafts) {

    foreach(const QString& icao24, m_aircraftsItems.keys()) {
        m_aircraftsItems[icao24].setColor(m_colorAircrafts);
        m_aircraftsItems[icao24].setIsSelectedUser(false);
    }

    for(int i = 0; i < aircrafts.size(); ++i) {
        if(m_aircraftsItems.contains(aircrafts[i])) {
            m_aircraftsItems[aircrafts[i]].setColor(m_colorAfterClick);
            m_aircraftsItems[aircrafts[i]].setIsSelectedUser(true);
        }
    }

    m_mainMapScene->update();

    for(int rowIndex = 0; rowIndex < ui->TW_airplanes->rowCount(); ++rowIndex) {
        ui->TW_airplanes->item(rowIndex, 0)->setSelected(false);
        ui->TW_airplanes->item(rowIndex, 1)->setSelected(false);

        for(int aircraftIndex = 0; aircraftIndex < aircrafts.size(); ++aircraftIndex) {
            if(aircrafts[aircraftIndex] == ui->TW_airplanes->item(rowIndex, 0)->text()) {
                ui->TW_airplanes->item(rowIndex, 0)->setSelected(true);
                ui->TW_airplanes->item(rowIndex, 1)->setSelected(true);
                break;
            }
        }
    }

}

void MainWindow::onClickOnField(quint8 zoomLevel, qreal x, qreal y) {
    m_updateTimer = new AircraftTimer(this);
    m_updateTimer->setZoomLevel(zoomLevel);
    m_updateTimer->setX(x);
    m_updateTimer->setY(y);
    m_updateTimer->setTimerType(Qt::TimerType::PreciseTimer);
    m_updateTimer->setInterval(m_updateTime_msec);
    connect(m_updateTimer, &QTimer::timeout,
            m_aircraftRequester, &AircraftRequester::onGetAircraftsInField);
    QMetaObject::invokeMethod(m_updateTimer, "timeout");
    m_updateTimer->start();
}

void MainWindow::on_PB_colorAicrafts_clicked() {
    QColorDialog colorDialog(m_colorAircrafts, this);
    colorDialog.exec();
    QColor color = colorDialog.selectedColor();
    if(color.isValid()) {
        m_colorAircrafts = color;
        ui->PB_colorAicrafts->setStyleSheet(QString("background-color: %1; border: 2px solid black;").arg(m_colorAircrafts.name()));

    }
}


void MainWindow::on_PB_colorAfterClick_clicked() {
    QColorDialog colorDialog(m_colorAfterClick, this);
    colorDialog.exec();
    QColor color = colorDialog.selectedColor();

    if(color.isValid()) {
        m_colorAfterClick = color;
        ui->PB_colorAfterClick->setStyleSheet(QString("background-color: %1; border: 2px solid black;")
                                              .arg(m_colorAfterClick.name()));
        ui->TW_airplanes->setStyleSheet(QString("QTableWidget::item:selected { background-color: %1; color: %2 }")
                                        .arg(m_colorAfterClick.name()).arg(getFontColor(m_colorAfterClick).name()));

        foreach(const QString& icao24, m_aircraftsItems.keys()) {
            if(m_aircraftsItems.contains(icao24)) {
                if(m_aircraftsItems[icao24].isSelected()) {
                    m_aircraftsItems[icao24].setColor(m_colorAfterClick);
                }
            }
        }
    }

    m_mainMapScene->update();
}


void MainWindow::on_CB_timeUpdate_currentIndexChanged(int index) {
    switch(index) {
    case 0:
        m_updateTime_msec = 15000;
        break;
    case 1:
        m_updateTime_msec = 30000;
        break;
    case 2:
        m_updateTime_msec = 60000;
        break;
    case 3:
        m_updateTime_msec = 150000;
        break;
    case 4:
        m_updateTime_msec = 300000;
        break;
    default:
        m_updateTime_msec = 15000;
        break;
    }

    if(m_updateTimer != nullptr) {
        m_updateTimer->setInterval(m_updateTime_msec);
    }
}


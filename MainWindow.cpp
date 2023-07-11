#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_mapRequester = new MapRequester(this);
    connect(m_mapRequester, &MapRequester::updateData, this, &MainWindow::setText);
    m_aircraftRequester = new AircraftRequester(this);

    m_mainMapScene = new QGraphicsScene(this);
    ui->GV_mainMap->setMain();
    ui->GV_mainMap->setScene(m_mainMapScene);

    m_overviewMapScene = new QGraphicsScene(this);
    ui->GV_overviewMap->setScene(m_overviewMapScene);

    QPixmap pixmap("../Recources/Map.png");

    m_mainMapImage = new QGraphicsPixmapItem(pixmap.scaled(MAIN_MAP_SIZE, MAIN_MAP_SIZE, Qt::KeepAspectRatio));
    m_mainMapScene->addItem(m_mainMapImage);

    m_overviewMapImage = new QGraphicsPixmapItem(pixmap.scaled(OVERVIEW_MAP_SIZE, OVERVIEW_MAP_SIZE, Qt::KeepAspectRatio));
    m_overviewMapScene->addItem(m_overviewMapImage);

    // Устанавливаем размеры сцены
    m_mainMapScene->setSceneRect(0, 0, MAIN_MAP_SIZE, MAIN_MAP_SIZE);

    drawFields();

    m_fieldRect = new QGraphicsRectItem(QRectF(0, 0, OVERVIEW_MAP_SIZE - 3, OVERVIEW_MAP_SIZE - 3));
    m_fieldRect->setPen(QPen(Qt::red));
    m_overviewMapScene->addItem(m_fieldRect);

    ui->TW_airplanes->setSelectionMode(QAbstractItemView::NoSelection);
    ui->TW_airplanes->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->GV_mainMap, &MapView::clickOnField, m_mapRequester, &MapRequester::onClickOnField);
    connect(ui->GV_mainMap, &MapView::clickOnField, m_aircraftRequester, &AircraftRequester::onClickOnField);
    connect(ui->GV_mainMap, &MapView::changeMapToMain, this, &MainWindow::onChangeMapToMain);
    connect(m_mapRequester, &MapRequester::updateMap, this, &MainWindow::onUpdateMap);
    connect(m_aircraftRequester, &AircraftRequester::updateAircrafts, this, &MainWindow::onUpdateAircrafts);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::setText(QString text) {
    //ui->textBrowser->setText(text);
}

void MainWindow::onUpdateMap(QPixmap map, quint8 x, quint8 y) {
    if(m_fieldMapImage != nullptr) {
        return;
    }

    ui->GV_mainMap->setIsField(true);

    m_fieldMapImage = new QGraphicsPixmapItem(map.scaled(MAIN_MAP_SIZE, MAIN_MAP_SIZE, Qt::KeepAspectRatio));

    m_overviewMapScene->removeItem(m_fieldRect);
    delete m_fieldRect;
    m_fieldRect = new QGraphicsRectItem(QRectF(8*x, 8*y, 5, 5));
    m_fieldRect->setPen(QPen(Qt::red));
    m_overviewMapScene->addItem(m_fieldRect);
    m_mainMapScene->addItem(m_fieldMapImage);
}

void MainWindow::onUpdateAircrafts(QVector<Aircraft> aircrafts) {
    ui->TW_airplanes->clear();
    ui->TW_airplanes->setRowCount(aircrafts.size());
    ui->TW_airplanes->setColumnCount(3);
    ui->TW_airplanes->setHorizontalHeaderItem(0, new QTableWidgetItem("ICAO 24"));
    ui->TW_airplanes->setHorizontalHeaderItem(1, new QTableWidgetItem("Country"));
    ui->TW_airplanes->setHorizontalHeaderItem(2, new QTableWidgetItem("Info"));
    for(int i = 0; i < aircrafts.size(); ++i) {
        QTableWidgetItem* icaoItem = new QTableWidgetItem(aircrafts[i].icao24);

        QTableWidgetItem* originCountryItem = new QTableWidgetItem(aircrafts[i].origin_country);

        ui->TW_airplanes->setItem(i, 0, icaoItem);
        ui->TW_airplanes->setItem(i, 1, originCountryItem);

        AircraftInfoButton* aircraftInfoButton = new AircraftInfoButton();
        aircraftInfoButton->setAircraft(aircrafts[i]);
        aircraftInfoButton->setText("?");
        connect(aircraftInfoButton, &QPushButton::clicked, [&]() {
            AircraftInfoDialog* dialog = new AircraftInfoDialog(this);
            dialog->setAircraftInfo(aircraftInfoButton->getAircraft());
            dialog->show();
        });

        ui->TW_airplanes->setCellWidget(i, 2, aircraftInfoButton);
        ui->TW_airplanes->verticalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
    ui->TW_airplanes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->TW_airplanes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->TW_airplanes->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

}

void MainWindow::onChangeMapToMain() {
    if(m_fieldMapImage == nullptr) {
        return;
    }

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
    // Размеры и количество клеток
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


void MainWindow::on_PB_authorization_clicked()
{
    m_aircraftRequester->onAuthorization("lll123321", "lll123321");
}


#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_mapRequester = new MapRequester(this);
    connect(m_mapRequester, &MapRequester::updateData, this, &MainWindow::setText);

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

    connect(ui->GV_mainMap, &MapView::clickOnField, m_mapRequester, &MapRequester::onClickOnField);
    connect(ui->GV_mainMap, &MapView::changeMapToMain, this, &MainWindow::onChangeMapToMain);
    connect(m_mapRequester, &MapRequester::updateMap, this, &MainWindow::onUpdateMap);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

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


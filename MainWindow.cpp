#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_openSkyAPI = new OpenSkyAPI(this);
    connect(m_openSkyAPI, &OpenSkyAPI::updateData, this, &MainWindow::setText);

    m_mainMapScene = new QGraphicsScene(this);
    ui->GV_mainMap->setScene(m_mainMapScene);

    m_overviewMapScene = new QGraphicsScene(this);
    ui->GV_overviewMap->setScene(m_overviewMapScene);

    QPixmap pixmap("../../SkyWatcher/Recources/Map.png");

    m_mainMapImage = new QGraphicsPixmapItem(pixmap.scaled(512, 512, Qt::KeepAspectRatio));
    m_mainMapScene->addItem(m_mainMapImage);

    m_overviewMapImage = new QGraphicsPixmapItem(pixmap.scaled(128, 128, Qt::KeepAspectRatio));
    m_overviewMapScene->addItem(m_overviewMapImage);

    // Устанавливаем размеры сцены
    m_mainMapScene->setSceneRect(0, 0, 512, 512);

    // Размеры и количество клеток
    int cellSize = 32;
    int numCells = 16;

    // Заполняем сцену клетками
    for (int row = 0; row < numCells; ++row) {
        for (int col = 0; col < numCells; ++col) {
            // Рассчитываем координаты клетки
            int x = col * cellSize;
            int y = row * cellSize;

            // Создаем прямоугольник для клетки
            QRectF rect(x, y, cellSize, cellSize);

            // Создаем перо для границы клетки
            QPen pen(Qt::red);
            pen.setWidth(1);

            // Добавляем прямоугольник на сцену с границей
            m_mainMapScene->addRect(rect, pen);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "123";
    //openSkyAPI->getStatesInField(36.3, 38.9, 11.0, 18.2);
}

void MainWindow::setText(QString text)
{
    //ui->textBrowser->setText(text);
}

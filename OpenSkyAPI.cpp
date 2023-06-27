#include "OpenSkyAPI.h"

OpenSkyAPI::OpenSkyAPI(QObject *parent)
    : QObject{parent}
{
    netManager = new QNetworkAccessManager(this);
    netReply = nullptr;
}

void OpenSkyAPI::clearValues()
{
    dataBuffer.clear();
}


OpenSkyAPI::~OpenSkyAPI()
{
}


void OpenSkyAPI::getStatesInField(qreal latitudeMin, qreal latitudeMax, qreal longitudeMin, qreal longitudeMax) {
    clearValues();
    QNetworkRequest req{QUrl(QString("https://opensky-network.org/api/states/all?lamin=%1&lamax=%2&lomin=%3&lomax=%4")
                             .arg(latitudeMin).arg(latitudeMax).arg(longitudeMin).arg(longitudeMax))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&OpenSkyAPI::readData);
    connect(netReply,&QNetworkReply::finished,this,&OpenSkyAPI::finishReading);
}

void OpenSkyAPI::readData()
{
    dataBuffer.append(netReply->readAll());
}

void OpenSkyAPI::finishReading()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
    }else{
        qDebug() << "Success!";

        QJsonObject userJsonInfo = QJsonDocument::fromJson(dataBuffer).object();

//        //SET USERNAME
//        QString login = userJsonInfo.value("login").toString();
//        ui->usernameLabel->setText(login);

//        // SET DISPLAY NAME
//        QString name = userJsonInfo.value("name").toString();
//        ui->nameLabel->setText(name);

//        //SET BIO
//        auto bio = userJsonInfo.value("bio").toString();
//        ui->bioEdit->setText(bio);

//        //SET FOLLOWER AND FOLLOWING COUNT
//        auto follower = userJsonInfo.value("followers").toInt();
//        auto following = userJsonInfo.value("following").toInt();
//        ui->followerBox->setValue(follower);
//        ui->followingBox->setValue(following);

//        //SET ACCOUNT TYPE
//        QString type = userJsonInfo.value("type").toString();
//        ui->typeLabel->setText(type);

//        //SET PICTURE
//        auto picLink = userJsonInfo.value("avatar_url").toString();
//        QNetworkRequest link{QUrl(picLink)};
//        netReply = netManager->get(link);
//        connect(netReply,&QNetworkReply::finished,this,&MainWindow::setUserImage);
        emit updateData(dataBuffer.data());
    }
}

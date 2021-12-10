#include "mainwindow.h"
#include <QFileDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dataManager = new DataManager();

    createWidgets();
    createLayout();
    createConnections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createWidgets()
{
    textEditForReceive = new QTextEdit();
    textEditForTransmit = new QTextEdit();
    clearTextEditForReceivePushButton = new QPushButton(QString("Очистить"));
    clearTextEditForTransmitPushButton = new QPushButton(QString("Очистить"));
    transmitPushButton = new QPushButton("Передать");
    openImagePushButton = new QPushButton("Открыть новое изображение");
    imageLabel = new QLabel();
    imageLabel->setText("Здесь будет выбранное изображение");
    textImageTabWidget = new QTabWidget(this);
}

void MainWindow::createLayout()
{
    QWidget *mainWindowWidget = new QWidget();
    QGridLayout *mainWindowWidgetLayout = new QGridLayout();
    QLabel *title = new QLabel("Client");
    title->setFont(QFont("Times",16,QFont::Bold,true));
    mainWindowWidgetLayout->addWidget(title,0,0,1,1,Qt::AlignCenter);
    // добавление вкладки для текста
    textImageTabWidget->addTab(textEditForTransmit,QString("Текст для передачи"));
    // добавление вкладки для изображения
    QWidget *imageTabWidget = new QWidget(this);
    QGridLayout *imageTabLayout = new QGridLayout(this);
    imageTabLayout->addWidget(openImagePushButton,0,0,1,1,Qt::AlignCenter);
    imageTabLayout->addWidget(imageLabel,1,0,1,1,Qt::AlignCenter);
    imageTabWidget->setLayout(imageTabLayout);
    textImageTabWidget->addTab(imageTabWidget,QString("Изображение для передачи"));
    mainWindowWidgetLayout->addWidget(textImageTabWidget,1,0,1,1);
    mainWindowWidgetLayout->addWidget(transmitPushButton,2,0,1,1,Qt::AlignCenter);
    mainWindowWidget->setLayout(mainWindowWidgetLayout);
    setCentralWidget(mainWindowWidget);
}

void MainWindow::createConnections()
{
    connect(transmitPushButton,&QPushButton::clicked,[&](){
        switch (textImageTabWidget->currentIndex())
        {
            case imageTextEnum::TEXT:
            {
                //dataManager->sendText(textEditForTransmit->toPlainText());
                QByteArray payload;
                QDataStream payloadDataStream(&payload,QIODevice::WriteOnly);
                payloadDataStream << static_cast<int>(imageTextEnum::TEXT) << textEditForTransmit->toPlainText();
                dataManager->sendData(payload);
                break;
            }
            case imageTextEnum::IMAGE:
            {
                //dataManager->sendImage(imagePath);
                QByteArray payload;
                QDataStream payloadDataStream(&payload,QIODevice::WriteOnly);
                payloadDataStream << static_cast<int>(imageTextEnum::IMAGE) << imagePath;
                dataManager->sendData(payload);
                break;
            }
            default:
                break;
        }
    });

    connect(openImagePushButton,&QPushButton::clicked,[&]()
    {
        imagePath = QFileDialog::getOpenFileName(this, QString("Открыть изображение"), QString(),QString("Файлы изображений: (*.png, *.jpg)"));
        if(!imagePath.isEmpty())
        {
            imageLabel->setPixmap(QPixmap(imagePath));
        }
    });

    connect(clearTextEditForReceivePushButton,&QPushButton::clicked,[&](){
        textEditForReceive->clear();
    });
    connect(clearTextEditForTransmitPushButton,&QPushButton::clicked,[&](){
        textEditForTransmit->clear();
    });

    connect(dataManager,&DataManager::showStatusInfo,[&](QString msg){
        this->statusBar()->showMessage(msg,3000);
    });

    connect(dataManager,&DataManager::showReceivedInfo,[&](QByteArray info){
        textEditForReceive->append(QString(info));
    });
}



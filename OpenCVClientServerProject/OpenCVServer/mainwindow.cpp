#include "mainwindow.h"
#include <QFile>
#include <QGroupBox>

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
    labelForReceivedImage = new QLabel();
}

void MainWindow::createLayout()
{
    QWidget *mainWindowWidget = new QWidget();
    QGridLayout *mainWindowWidgetLayout = new QGridLayout();
    QLabel *title = new QLabel("Server");
    title->setFont(QFont("Times",16,QFont::Bold,true));
    mainWindowWidgetLayout->addWidget(title,0,0,1,1,Qt::AlignCenter);
    QGroupBox *groupBox = new QGroupBox(QString("Принятый текст"), this);
    QVBoxLayout *textEditForReceiveLayout = new QVBoxLayout(this);
    textEditForReceiveLayout->addWidget(textEditForReceive);
    groupBox->setLayout(textEditForReceiveLayout);
    mainWindowWidgetLayout->addWidget(groupBox,1,0,1,1);
    mainWindowWidget->setLayout(mainWindowWidgetLayout);
    setCentralWidget(mainWindowWidget);
}

void MainWindow::createConnections()
{
    connect(dataManager,&DataManager::showStatusInfo,[&](QString msg){
        this->statusBar()->showMessage(msg,3000);
    });

    connect(dataManager,&DataManager::showReceivedText,[&](QByteArray payload){
        textEditForReceive->append(QString(payload));
    });
}



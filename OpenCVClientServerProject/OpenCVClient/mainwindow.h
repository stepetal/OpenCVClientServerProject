#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QAction>
#include <QTextEdit>
#include <QLabel>
#include <QStatusBar>
#include <QDebug>
#include <QDataStream>
#include <QTabWidget>
#include "datamanager.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTextEdit *textEditForTransmit;
    QTextEdit *textEditForReceive;
    QPushButton *transmitPushButton;
    QPushButton *clearTextEditForTransmitPushButton;
    QPushButton *clearTextEditForReceivePushButton;
    QPushButton *openImagePushButton;
    QLabel *imageLabel;
    QString imagePath;
    DataManager *dataManager;
    QTabWidget *textImageTabWidget;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createWidgets();
    void createLayout();
    void createConnections();
};

#endif // MAINWINDOW_H

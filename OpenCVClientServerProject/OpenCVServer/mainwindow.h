#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QAction>
#include <QTextEdit>
#include <QLabel>
#include <QStatusBar>
#include "datamanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTextEdit *textEditForReceive;
    DataManager *dataManager;
    QLabel *labelForReceivedImage;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createWidgets();
    void createLayout();
    void createConnections();
};

#endif // MAINWINDOW_H

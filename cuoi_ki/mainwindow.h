#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <QtSerialPort/QSerialPort>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Serial port function
    void open_serial_port();
    void fnc_closeSerialPort();

    signals:
    void updateNumColor();

private slots:
    // GUI signals and slots
    void on_btnStart_clicked();
    void on_btnReset_clicked();
    void readData();
    void update_numColor();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    int red = 0;
};
#endif // MAINWINDOW_H

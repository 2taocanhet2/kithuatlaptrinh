#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnReset_clicked(){
    fnc_closeSerialPort();
    ui->btnStart->setEnabled(true);
    ui->btnReset->setEnabled(false);
    // RESET VAR
    red = 0;
    update_numColor();
}

void MainWindow::on_btnStart_clicked()
{
    fnc_closeSerialPort();
    open_serial_port();
    ui->btnStart->setEnabled(false);
    ui->btnReset->setEnabled(true);
}

void MainWindow::open_serial_port(){
    serial->setPortName("COM7");
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadOnly)) {
        connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(this, SIGNAL(updateNumColor()), this, SLOT(update_numColor()), Qt::QueuedConnection);
        readData();
        update_numColor();
     } else {
           QMessageBox::critical(this, tr("Error"), serial->errorString());
   }
}

void MainWindow::fnc_closeSerialPort()
{
     if (serial->isOpen())
             serial->close();
}

void MainWindow::readData()
{
    //This code is to read all data on serial port
    QByteArray data = serial->readLine();
    QString strData;
    if (!data.isEmpty()) {
            QString strData = QString(data);
            if (strData.compare("red", Qt::CaseInsensitive) == 0) {
                red++;
        }
    }
}

void MainWindow::update_numColor(){
    ui->numRed->setText(QString::number(red));
}

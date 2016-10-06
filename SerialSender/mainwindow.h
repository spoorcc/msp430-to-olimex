#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QRadioButton>

#define STORE_OPERATOR 0x20

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QSerialPort serial;

    void sendMessage(QByteArray message);
    void openPort(QString portName);
    void addRadioButtons();
    QByteArray getValuesFromRadioButtons();

    void setAllRadioButtons( bool trueOrFalse );
private slots:
    void bytesAreWritten(qint64 bytes);

    void on_sendPB_clicked();
    void on_clearPb_clicked();
};

#endif // MAINWINDOW_H

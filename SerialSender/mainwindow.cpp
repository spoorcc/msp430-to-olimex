#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openPort( "ttyACM0" );
    addRadioButtons();
}

MainWindow::~MainWindow()
{
    if( serial.isOpen() )
        serial.close();

      delete ui;
}

void MainWindow::sendMessage( QByteArray message )
{
    if( !message.endsWith(STORE_OPERATOR))
    {
        message.append( STORE_OPERATOR );
    }

    serial.write( message );
    serial.waitForBytesWritten(-1);
}

void MainWindow::openPort( QString portName )
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

        if( info.portName() == portName )
        {
            qDebug() <<  "Connecting to port" << info.portName();

            serial.setPort(info);
            serial.setBaudRate( QSerialPort::Baud9600 );
            serial.setFlowControl(QSerialPort::NoFlowControl);
            serial.setRequestToSend(true);
            serial.setDataBits( QSerialPort::Data8 );
            serial.setParity( QSerialPort::NoParity );
            serial.setStopBits(QSerialPort::OneStop );

            if (serial.open(QIODevice::ReadWrite))
            {
                qDebug() << "Connected to" << info.portName();

                connect( &serial, SIGNAL(bytesWritten(qint64)),
                                   SLOT(bytesAreWritten(qint64)));
            }
            else
            {
                qDebug() << serial.errorString() << serial.error();
            }
        }
    }
}

void MainWindow::bytesAreWritten(qint64 bytes)
{
    qDebug() << "Just written" << bytes << "bytes";
}

void MainWindow::on_sendPB_clicked()
{
    QByteArray message = getValuesFromRadioButtons();
    sendMessage(message);
}

void MainWindow::addRadioButtons()
{
    int rows = 8;
    int cols = 8;

    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < cols; j++)
        {
            QRadioButton* btn = new QRadioButton("", this);
            btn->setAutoExclusive(false);
            ui->gridLayout->addWidget( btn, i, j, 1, 1, Qt::AlignCenter );
        }
    }
}

QByteArray MainWindow::getValuesFromRadioButtons()
{
    int rows = 8;
    int cols = 8;

    QByteArray message;

    for( int i = 0; i < rows; i++ )
    {
        unsigned char rowValue = 0x00;

        for( int j = 0; j < cols; j++)
        {
            QLayoutItem* item = ui->gridLayout->itemAtPosition(i,j);

            QRadioButton* btn = static_cast<QRadioButton*>( item->widget() );

            rowValue += btn->isChecked()?(0x01<<j):0x00;
        }

        message.prepend( rowValue );
    }

    return message;
}

void MainWindow::setAllRadioButtons( bool trueOrFalse )
{
    int rows = 8, cols = 8;

    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < cols; j++)
        {
            QLayoutItem* item = ui->gridLayout->itemAtPosition(i,j);

            QRadioButton* btn = static_cast<QRadioButton*>( item->widget() );

            btn->setChecked( trueOrFalse );
        }
    }
}

void MainWindow::on_clearPb_clicked()
{
    setAllRadioButtons(false);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = 0;
    QList <QScreen *> list_screen = QGuiApplication::screens();
#if __arm__
    /* 重设大小 */
    this->resize(list_screen.at(0)->geometry().width(),list_screen.at(0)->geometry().height());
#else
    /* 否则则设置主窗体大小为 800x480 */
    this->resize(800, 480);
#endif

    //ledfile.setFileName("/dev/gpioled");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    unsigned char s = 48;
    int fd;
    fd = open("/dev/gpioled",O_RDWR);
    write(fd,&s,sizeof (s));
    ::close(fd);
    getLedState();


}

void MainWindow::on_pushButton_2_clicked()
{
    unsigned char s = 49;
    int fd;
    fd = open("/dev/gpioled",O_RDWR);
    write(fd,&s,sizeof (s));
    ::close(fd);
    getLedState();
}

bool MainWindow::getLedState()
{
    unsigned char s;
    int fd;
    fd = open("/dev/gpioled",O_RDWR);
    read(fd, &s, sizeof(s));
    ::close(fd);

    if (s == 49) {
        ui->label->setText("NO");
        return true;
    }
    else if(s == 48)
    {
        ui->label->setText("FFO");
        return false;
    }

}

/////////////////////////////////////////////////////////Accéleromètre permettant de connaitre l'angle du téléphone//////////////////////////////////////////////////

#include <QDateTime>
#include <QtMultimedia/QCamera>
#include <QPalette>
#include <QDialog>


Accélerometre::Accélerometre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hauteur)
{
    ui->setupUi(this);
    setWindowTitle(tr("Mesure de la hauteur de la ligne"));
    axez = new QAccelerometer;
    connect(axez, SIGNAL(readingChanged()), this, SLOT(update()));
    axez->setDataRate(0.1);
    axez->start();
}

Accélerometre::~Accélerometre()
{
    delete axez;
    delete ui;
}

void Accélerometre::update()
{
    QString text;

    reading = axez->reading();
    text = tr("%1\nAcceleration:\n  x = %2\n  y = %3\n  z = %4").arg(QDateTime::currentDateTime().toString()).arg(reading->x()).arg(reading->y()).arg(reading->z());
    ui->textEdit->setText(text);
    if(reading->z()<0)
    {
        if(reading->z()>(-0.2))
        {
            QPalette Pal(palette());
            Pal.setColor(QPalette::Background, Qt::green);
            ui->horizontalSlider->setAutoFillBackground(true);
            ui->horizontalSlider->setPalette(Pal);
        }
        else if(reading->z()<(-0.2))
        {
            QPalette Pal(palette());
            Pal.setColor(QPalette::Background, Qt::red);
            ui->horizontalSlider->setAutoFillBackground(true);
            ui->horizontalSlider->setPalette(Pal);
        }
    }
    else if(reading->z()>0)
    {
        if(reading->z()<0.4)
        {
            QPalette Pal(palette());
            Pal.setColor(QPalette::Background, Qt::green);
            ui->horizontalSlider->setAutoFillBackground(true);
            ui->horizontalSlider->setPalette(Pal);
        }
        else if(reading->z()>0.4)
        {
            QPalette Pal(palette());
            Pal.setColor(QPalette::Background, Qt::red);
            ui->horizontalSlider->setAutoFillBackground(true);
            ui->horizontalSlider->setPalette(Pal);
        }
    }

    ui->horizontalSlider->setSliderPosition((reading->z()*1000));
}

#include "imageWindowMap.h"
#include <QPixmap>
#include <QDebug>

ImageWindowMap::ImageWindowMap(QWidget *parent) : QWidget(parent), backgroundImagePath(""), imagePath("")
{
    //QFrame
        frame = new QFrame(this);
        frame->setStyleSheet("background: transparent;");
        frame->setContentsMargins(0, 0, 0, 0);

        backgroundLabel = new QLabel(frame);
        backgroundLabel->setAlignment(Qt::AlignCenter);
        backgroundLabel->setStyleSheet("background: transparent;");
        backgroundLabel->setContentsMargins(0, 0, 0, 0);

        imageLabel = new QLabel(frame);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setStyleSheet("background: transparent;");  // Сделать фон QLabel прозрачным
        imageLabel->setContentsMargins(0, 0, 0, 0);

        QGridLayout *gridLayout = new QGridLayout(frame);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->addWidget(backgroundLabel, 0, 0);
        gridLayout->addWidget(imageLabel, 0, 0);
        frame->setLayout(gridLayout);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addWidget(frame);
        setLayout(mainLayout);

        // Устанавливаем минимальные размеры для окна
        setMinimumSize(300, 300);

        // Устанавливаем фоновую картинку для окна
        setWindowBackgroundImage(":/Images/map_back.png");
}

void ImageWindowMap::setImage(const QString &imagePath)
{
        qDebug() << "Setting image:" << imagePath;
        this->imagePath = imagePath;
        updateForegroundImage();
}

void ImageWindowMap::setWindowBackgroundImage(const QString &imagePath)
{
    //QFrame
    qDebug() << "Setting background image: " << imagePath;
    backgroundImagePath = imagePath;
    updateBackgroundImage();
}

void ImageWindowMap::resizeEvent(QResizeEvent *event)
{
   QWidget::resizeEvent(event);
   updateBackgroundImage();
   updateForegroundImage();
}

void ImageWindowMap::updateBackgroundImage()
{
    if (backgroundImagePath.isEmpty())
        return;

    QPixmap pixmap = scaledPixmap(backgroundImagePath);
    if (!pixmap.isNull())
    {
        QString style = QString("QFrame { background-color: #303030;}").arg(backgroundImagePath);
        frame->setStyleSheet(style);
        backgroundLabel->setPixmap(pixmap);
        backgroundLabel->setAlignment(Qt::AlignCenter);
        qDebug() << "Background image set successfully:" << backgroundImagePath;
    }
    else
    {
        qDebug() << "Failed to load background image:" << backgroundImagePath;
    }
}

void ImageWindowMap::updateForegroundImage()
{
    if (imagePath.isEmpty())
        return;

    QPixmap pixmap = scaledPixmap(imagePath);
    if (!pixmap.isNull())
    {
        imageLabel->setPixmap(pixmap);
        imageLabel->setAlignment(Qt::AlignCenter);
        qDebug() << "Foreground image set successfully:" << imagePath;
    }
    else
    {
        qDebug() << "Failed to load foreground image:" << imagePath;
    }
}

QPixmap ImageWindowMap::scaledPixmap(const QString &path)
{
    QPixmap pixmap(path);
    return pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

#include "imageWindowMap.h"
#include <QPixmap>
#include <QDebug>
#include <QStackedLayout>

ImageWindowMap::ImageWindowMap(QWidget *parent) : QWidget(parent), backgroundImagePath("")
{
    //QFrame
        frame = new QFrame(this);
        frame->setStyleSheet("background: transparent;");
        frame->setContentsMargins(0, 0, 0, 0);

        backgroundLabel = new QLabel(frame);
        backgroundLabel->setAlignment(Qt::AlignCenter);
        backgroundLabel->setStyleSheet("background: transparent;");
        backgroundLabel->setContentsMargins(0, 0, 0, 0);

        QGridLayout *gridLayout = new QGridLayout(frame);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->addWidget(backgroundLabel, 0, 0);
       // gridLayout->addWidget(imageLabel, 0, 0);
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
        images.clear();
        images.append(imagePath);
        updateForegroundImage();
}

void ImageWindowMap::setWindowBackgroundImage(const QString &imagePath)
{
    //QFrame
    qDebug() << "Setting background image: " << imagePath;
    backgroundImagePath = imagePath;
    updateBackgroundImage();
}

void ImageWindowMap::addImage(const QString &imagePath)
{
    qDebug() << "Adding image:" << imagePath;
    images.append(imagePath);
    QLabel *imageLabel = new QLabel(frame);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("background: transparent;");
    imageLabels.append(imageLabel);
    static_cast<QGridLayout*>(frame->layout())->addWidget(imageLabel, 0, 0);
    updateForegroundImage();
}

void ImageWindowMap::removeImage(const QString &imagePath)
{
    int index = images.indexOf(imagePath);
    if (index != -1)
    {
     images.removeAt(index);
     QLabel *imageLabel = imageLabels.takeAt(index);
     frame->layout()->removeWidget(imageLabel);
     delete imageLabel;
    }
   updateForegroundImage();
}

void ImageWindowMap::updateImage(const QString &oldImagePath, const QString &newImagePath)
{
    int index = images.indexOf(oldImagePath);
    if (index != -1) {
        images[index] = newImagePath;
        updateForegroundImage();
    }
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
        QString style = QString("QFrame { background-color: #303030;}");
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
    for (int i = 0; i < images.size(); ++i)
        {
            QPixmap pixmap = scaledPixmap(images[i]);
            if (!pixmap.isNull())
            {
                imageLabels[i]->setPixmap(pixmap);
                imageLabels[i]->setAlignment(Qt::AlignCenter);
                qDebug() << "Foreground image set successfully:" << images[i];
            }
            else
            {
                qDebug() << "Failed to load foreground image:" << images[i];
            }
        }
}

QPixmap ImageWindowMap::scaledPixmap(const QString &path)
{
    QPixmap pixmap(path);
    return pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

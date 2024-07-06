#ifndef IMAGEWINDOWMAP_H
#define IMAGEWINDOWMAP_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>

class ImageWindowMap : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWindowMap(QWidget *parent = nullptr);
    void setImage(const QString &imagePath);
    void setWindowBackgroundImage(const QString &imagePath);
    void addImage(const QString &imagePath);
    void removeImage(const QString &imagePath);
    void updateImage(const QString &oldImagePath, const QString &newImagePath);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *backgroundLabel;
    QLabel *imageLabel;
    QFrame *frame;
    QVector<QLabel*> imageLabels;
    QString backgroundImagePath;
    QVector<QString> images;

    void updateBackgroundImage();
    void updateForegroundImage();
    QPixmap scaledPixmap(const QString &path);
};

#endif // IMAGEWINDOWMAP_H

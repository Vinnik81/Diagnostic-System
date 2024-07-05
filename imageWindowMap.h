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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *backgroundLabel;
    QLabel *imageLabel;
    QFrame *frame;
    QString backgroundImagePath;
    QString imagePath;

    void updateBackgroundImage();
    void updateForegroundImage();
    QPixmap scaledPixmap(const QString &path);
};

#endif // IMAGEWINDOWMAP_H

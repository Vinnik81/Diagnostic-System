#ifndef ALARMWINDOW_H
#define ALARMWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include "clickableWidget.h"
#include "imageWindowMap.h"
#include <QMap>

QT_BEGIN_NAMESPACE
//namespace Ui { class AlarmWindow; }
QT_END_NAMESPACE

class AlarmWindow : public QWidget
{
    Q_OBJECT

public:
     AlarmWindow(QWidget *parent = nullptr);
    ~AlarmWindow();

private:
    QGridLayout *gridLayout;
    QVector<ClickableWidget*> buttons;
    ClickableWidget *selectedButton = nullptr;
    ImageWindowMap *imageWindowMap;
    QString previousDefaultImagePath;
    QString previousSelectImagePath;


    void setupUI();
    void loadStates();
    void updateLayout();
    void updateButtonSizes();
    void resizeEvent(QResizeEvent *event) override;
   // Ui::AlarmWindowSvg *ui;

private slots:
    void handleButtonClick(ClickableWidget *widget);
};
#endif // ALARMWINDOW_H

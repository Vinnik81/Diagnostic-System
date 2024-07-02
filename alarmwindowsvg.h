#ifndef ALARMWINDOWSVG_H
#define ALARMWINDOWSVG_H

#include <QWidget>
#include <QGridLayout>
#include "clickableWidgetSvg.h"

QT_BEGIN_NAMESPACE
//namespace Ui { class AlarmWindowSvg; }
QT_END_NAMESPACE

class AlarmWindowSvg : public QWidget
{
    Q_OBJECT

public:
    AlarmWindowSvg(QWidget *parent = nullptr);
    ~AlarmWindowSvg();

private:
    QGridLayout *gridLayout;
    QVector<ClickableWidgetSvg*> buttons;
    ClickableWidgetSvg *selectedButton = nullptr;

    void setupUI();
    void loadStates();
    void updateLayout();
    void updateButtonSizes();
    void resizeEvent(QResizeEvent *event) override;
   // Ui::AlarmWindowSvg *ui;

private slots:
    void handleButtonClick(ClickableWidgetSvg *widget);
};
#endif // ALARMWINDOWSVG_H

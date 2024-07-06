#include "alarmwindow.h"
#include "ui_alarmwindow.h"
#include "clickableWidget.h"
#include <QDebug>
#include <QIcon>
#include <QSizePolicy>
#include <QResizeEvent>
#include <QtMath>

AlarmWindow::AlarmWindow(QWidget *parent)
    : QWidget(parent)
    , gridLayout(new QGridLayout(this))
    , imageWindowMap(new ImageWindowMap)
    //, ui(new Ui::AlarmWindowSvg)
{
    setupUI();
    loadStates();
    updateLayout();
    //ui->setupUi(this);

    imageWindowMap->show();
}

AlarmWindow::~AlarmWindow()
{
   // delete ui;
}

void AlarmWindow::setupUI()
{
    setLayout(gridLayout);
    setMinimumSize(200, 500);
    setStyleSheet("AlarmWindow {background-color: #303030;}");
}

void AlarmWindow::loadStates()
{
    struct Aggregator
    {
        QString id;
        QString state;
        QString defaultImagePath;
        QString selectImagePath;
    };

    QVector<Aggregator> aggregators = {
        {"H-1", "icon_pump_red", ":/Images/map_agregat_1_red_default.png", ":/Images/map_agregat_1_red_select.png"},
        {"H-2", "icon_pump_red", ":/Images/map_agregat_2_red_default.png", ":/Images/map_agregat_2_red_select.png"},
        {"H-3", "icon_pump_green", ":/Images/map_agregat_3_green_default.png", ":/Images/map_agregat_3_green_select.png"},
        {"H-4", "icon_pump_red", ":/Images/map_agregat_4_red_default.png", ":/Images/map_agregat_4_red_select.png"},
        {"H-5", "icon_pump_green", ":/Images/map_agregat_5_green_default.png", ":/Images/map_agregat_5_green_select.png"},
        {"H-6", "icon_pump_yellow", ":/Images/map_agregat_6_yellow_default.png", ":/Images/map_agregat_6_yellow_select.png"},
        // {"H-53", "icon_pump_red", ":/Images/map_agregat_8_red_default.png", ":/Images/map_agregat_8_red_select.png"},
        {"H-14/1", "icon_pump_yellow", ":/Images/map_agregat_7_yellow_default.png", ":/Images/map_agregat_7_yellow_select.png"},
        //{"H-14/2", "icon_pump_green", ":/Images/map_agregat_7_green_default.png", ":/Images/map_agregat_7_green_select.png"},
        //{"H-21/1", "icon_pump_red", ":/Images/map_agregat_5_red_default.png", ":/Images/map_agregat_5_red_select.png"},
       // {"H-50", "icon_pump_green", ":/Images/map_agregat_7_green_default.png", ":/Images/map_agregat_7_green_select.png"},
        {"H-51", "icon_pump_grey", ":/Images/map_agregat_8_grey_default.png", ":/Images/map_agregat_8_grey_select.png"}
    };

    for (const auto &agg : aggregators)
    {
        ClickableWidget *button = new ClickableWidget(agg.id, ":/Images/" + agg.state + ".svg", this);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setProperty("defaultImagePath", agg.defaultImagePath);
        button->setProperty("selectImagePath", agg.selectImagePath);
        connect(button, &ClickableWidget::clicked, this, &AlarmWindow::handleButtonClick);
        buttons.append(button);
        imageWindowMap->addImage(agg.defaultImagePath);
    }

    updateLayout();
}

void AlarmWindow::updateButtonSizes()
{

    int totalButtons = buttons.size();
    int columns = qMax(1, width() / 100);
    columns = qMin(columns, 4);  // Ограничение количества столбцов четырьмя
    int rows = (totalButtons + columns - 1) / columns;

    for (int i = 0; i < totalButtons; ++i)
    {
        int buttonWidth = width() / columns;
        int buttonHeight = height() / rows;
        int buttonSize = qMin(buttonWidth, buttonHeight);

        buttons[i]->setFixedSize(buttonSize, buttonSize);
        buttons[i]->setIconSize(QSize(buttonSize * 0.6, buttonSize * 0.6));

        QFont font = buttons[i]->font();
        font.setPointSize(buttonSize / 10);
        buttons[i]->setFont(font);
    }
}

void AlarmWindow::updateLayout()
{
    QLayoutItem *item;

    while ((item = gridLayout->takeAt(0)) != nullptr)
    {
        delete item;
    }

    int totalButtons = buttons.size();
    int columns = qMax(1, width() / 100);
    columns = qMin(columns, 4);  // Ограничение количества столбцов четырьмя

    for (int i = 0; i < totalButtons; ++i)
    {
        int row = i / columns;
        int column = i % columns;
        gridLayout->addWidget(buttons[i], row, column);
    }

    updateButtonSizes();
}

void AlarmWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateLayout();
}

void AlarmWindow::handleButtonClick(ClickableWidget *widget)
{
    if (selectedButton)
    {
        // Получаем пути к изображениям для ранее выделенного виджета
        QString previousDefaultImagePath = selectedButton->property("defaultImagePath").toString();
        QString previousSelectImagePath = selectedButton->property("selectImagePath").toString();

        // Смена изображения на дефолтное
        imageWindowMap->updateImage(previousSelectImagePath, previousDefaultImagePath);
        selectedButton->setHighlighted(false);
    }

    widget->setHighlighted(true);
    selectedButton = widget;

    QString defaultImagePath = widget->property("defaultImagePath").toString();
    QString selectImagePath = widget->property("selectImagePath").toString();
    imageWindowMap->updateImage(defaultImagePath, selectImagePath);

    qDebug() << widget->getId() << "clicked";
}

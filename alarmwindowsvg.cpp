#include "alarmwindowsvg.h"
#include "ui_alarmwindowsvg.h"
#include "clickableWidgetSvg.h"
#include <QDebug>
#include <QIcon>
#include <QSizePolicy>
#include <QResizeEvent>
#include <QtMath>

AlarmWindowSvg::AlarmWindowSvg(QWidget *parent)
    : QWidget(parent)
    , gridLayout(new QGridLayout(this))
    //, ui(new Ui::AlarmWindowSvg)
{
    setupUI();
    loadStates();
    updateLayout();
    //ui->setupUi(this);
}

AlarmWindowSvg::~AlarmWindowSvg()
{
   // delete ui;
}

void AlarmWindowSvg::setupUI()
{
    setLayout(gridLayout);
    setMinimumSize(200, 500);
    setStyleSheet("AlarmWindowSvg {background-color: #303030;}");
}

void AlarmWindowSvg::loadStates()
{
    struct Aggregator
    {
        QString id;
        QString state;
    };

    QVector<Aggregator> aggregators = {
        {"H-1", "icon_pump_red"}, {"H-2", "icon_pump_red"}, {"H-3", "icon_pump_green"},
        {"H-4", "icon_pump_red"}, {"H-5", "icon_pump_green"}, {"H-6", "icon_pump_yellow"},
        {"H-53", "icon_pump_red"}, {"H-14/1", "icon_pump_yellow"}, {"H-14/2", "icon_pump_green"},
        {"H-21/1", "icon_pump_red"}, {"H-50", "icon_pump_green"}, {"H-51", "icon_pump_grey"}
    };

    for (const auto &agg : aggregators)
    {
        ClickableWidgetSvg *button = new ClickableWidgetSvg(agg.id, ":/Images/" + agg.state + ".svg", this);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(button, &ClickableWidgetSvg::clicked, this, &AlarmWindowSvg::handleButtonClick);
        buttons.append(button);
    }

    updateLayout();
}

void AlarmWindowSvg::updateButtonSizes()
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

void AlarmWindowSvg::updateLayout()
{
    QLayoutItem *item;

    while ((item = gridLayout->takeAt(0)) != nullptr)
    {
        delete item;
    }

    int totalButtons = buttons.size();
    int columns = qMax(1, width() / 100);
    columns = qMin(columns, 4);  // Ограничение количества столбцов четырьмя
   // int rows = (totalButtons + columns - 1) / columns;

    for (int i = 0; i < totalButtons; ++i)
    {
        int row = i / columns;
        int column = i % columns;
        gridLayout->addWidget(buttons[i], row, column);
    }

    updateButtonSizes();
}

void AlarmWindowSvg::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateLayout();
}

void AlarmWindowSvg::handleButtonClick(ClickableWidgetSvg *widget)
{
    if (selectedButton)
    {
        selectedButton->setHighlighted(false);
    }

    widget->setHighlighted(true);
    selectedButton = widget;

    qDebug() << widget->getId() << "clicked";

   /* ClickableWidgetSvg *button = qobject_cast<ClickableWidgetSvg*>(sender());

    if (button)
    {
        qDebug() << button->getId() << "clicked";
    } */
}

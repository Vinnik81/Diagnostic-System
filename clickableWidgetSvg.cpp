#include "clickableWidgetSvg.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>

ClickableWidgetSvg::ClickableWidgetSvg(const QString &id, const QString &svgPath, QWidget *parent)
    : QWidget(parent), id(id), svgPath(svgPath), svgRenderer(new QSvgRenderer(svgPath, this))
{


    iconLabel = new QLabel(this);
     textLabel = new QLabel(id, this);

     layout = new QVBoxLayout(this);
     layout->setSpacing(0);

     iconLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     iconLabel->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
     textLabel->setAlignment(Qt::AlignCenter);
     textLabel->setStyleSheet("color: white;");

     layout->addWidget(iconLabel);
     layout->addWidget(textLabel);
     setLayout(layout);

     setIconSize(QSize(96, 96)); // Установка начального размера иконки
 }

void ClickableWidgetSvg::setIconSize(const QSize &size)
{
    if (!svgRenderer->isValid())
        return;

    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    svgRenderer->render(&painter);
    iconLabel->setPixmap(pixmap);
}

void ClickableWidgetSvg::setFont(const QFont &font)
{
    textLabel->setFont(font);
}

QString ClickableWidgetSvg::getId() const
{
    return id;
}

void ClickableWidgetSvg::setHighlighted(bool highlighted)
{
    isHighlighted = highlighted;
    if (isHighlighted)
    {
        setStyleSheet("background-color: #606060;");
    }
    else
    {
        setStyleSheet("background: #303030;");
    }
}

void ClickableWidgetSvg::mousePressEvent(QMouseEvent *event)
{
    emit clicked(this);
    QWidget::mousePressEvent(event);
}

void ClickableWidgetSvg::enterEvent(QEvent *event)
{
    if (!isHighlighted)
    {
    setStyleSheet("background-color: #606060;");
    }
    QWidget::enterEvent(event);
}

void ClickableWidgetSvg::leaveEvent(QEvent *event)
{
    if (!isHighlighted)
    {
    setStyleSheet("background: #303030;");
    }
    QWidget::leaveEvent(event);
}

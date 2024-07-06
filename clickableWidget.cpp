#include "clickableWidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QSvgWidget>
#include <QDebug>

ClickableWidget::ClickableWidget(const QString &id, const QString &svgPath, QWidget *parent)
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

         qDebug() << "ClickableWidget created for ID:" << id << ", SVG Path:" << svgPath;
 }

void ClickableWidget::setIconSize(const QSize &size)
{
    if (!svgRenderer->isValid())
        return;

    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    svgRenderer->render(&painter);
    iconLabel->setPixmap(pixmap);
}

void ClickableWidget::setFont(const QFont &font)
{
    textLabel->setFont(font);
}

QString ClickableWidget::getId() const
{
    return id;
}

void ClickableWidget::setHighlighted(bool highlighted)
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

void ClickableWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Widget clicked: " << id;
    emit clicked(this);
    QWidget::mousePressEvent(event);
}

void ClickableWidget::enterEvent(QEvent *event)
{
    if (!isHighlighted)
    {
    setStyleSheet("background-color: #606060;");
    }
    QWidget::enterEvent(event);
}

void ClickableWidget::leaveEvent(QEvent *event)
{
    if (!isHighlighted)
    {
    setStyleSheet("background: #303030;");
    }
    QWidget::leaveEvent(event);
}

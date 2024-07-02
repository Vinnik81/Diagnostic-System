#ifndef CLICKABLEWIDGETSVG_H
#define CLICKABLEWIDGETSVG_H

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QSvgRenderer>
#include <QVBoxLayout>

class ClickableWidgetSvg : public QWidget
{
    Q_OBJECT

public:
    explicit ClickableWidgetSvg(const QString &id, const QString &svgPath, QWidget *parent = nullptr);

    void setIconSize(const QSize &size);
    void setFont(const QFont &font);
    QString getId() const;
    void setHighlighted(bool highlighted);

signals:
    void clicked(ClickableWidgetSvg *widget);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QString id;
    QLabel *iconLabel;
    QLabel *textLabel;
    QString svgPath;
    QSvgRenderer *svgRenderer;
    QVBoxLayout *layout;
    bool isHighlighted = false;
};


#endif // CLICKABLEWIDGETSVG_H

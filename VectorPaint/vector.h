#pragma once

#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

class Vector : public QGraphicsLineItem
{
public:
    Vector(double x1, double y1, double x2, double y2, QColor color = Qt::black);
    QPointF start() const;
    QPointF end() const;
    bool m_selected = false;
protected:
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QColor m_color;

    bool m_hovered = false;
};

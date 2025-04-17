#include "vector.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>


Vector::Vector(qreal x1, qreal y1, qreal x2, qreal y2, QColor color)
    : QGraphicsLineItem(x1, y1, x2, y2), m_color(color) {
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(true);
}

QPointF Vector::start() const
{
    return line().p1();
}

QPointF Vector::end() const
{
    return line().p2();
}

void Vector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(m_color, 2));
    painter->setBrush(m_color);


    painter->drawLine(line());

    QLineF mainLine = line();
    double angle = std::atan2(-mainLine.dy(), mainLine.dx());

    QPointF arrowP1 = mainLine.p2() - QPointF(std::cos(angle + M_PI / 6) * 10,
                                              -std::sin(angle + M_PI / 6) * 10);
    QPointF arrowP2 = mainLine.p2() - QPointF(std::cos(angle - M_PI / 6) * 10,
                                              -std::sin(angle - M_PI / 6) * 10);

    QPolygonF arrowHead;
    arrowHead << mainLine.p2() << arrowP1 << arrowP2;

    painter->drawPolygon(arrowHead);

    QPen pen(m_color, 2);
    if (m_hovered)
        pen.setWidth(4);

    if (m_selected)
        pen.setColor(Qt::darkGreen);
    painter->setPen(pen);
    painter->drawLine(line());
}

void Vector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_selected = !m_selected;
    setSelected(m_selected);
    update();
    QGraphicsLineItem::mousePressEvent(event);
}

void Vector::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = true;
    update();
    QString tip = QString("(%1, %2) → (%3, %4)")
                      .arg(line().x1()).arg(line().y1())
                      .arg(line().x2()).arg(line().y2());
    setToolTip(tip);
    QGraphicsLineItem::hoverEnterEvent(event);
}

void Vector::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = false;
    update();
    QGraphicsLineItem::hoverLeaveEvent(event);
}

#include "pie.h"

#include <QPainter>
#include "antrender.h"

PieChart::PieChart(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

QString PieChart::name() const
{
    return m_name;
}

void PieChart::setName(const QString &name)
{
    m_name = name;
}

QColor PieChart::color() const
{
    return m_color;
}

void PieChart::setColor(const QColor &color)
{
    m_color = color;
}

void PieChart::paint(QPainter *painter)
{
    AntRender::rend(painter, boundingRect().adjusted(1, 1, -1, -1));
}


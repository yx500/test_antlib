#pragma once

#include <QPainter>

class AntRender
{
public:

  static QString name;
  static void rend(QPainter *painter, const QRectF& boundingRect);
};


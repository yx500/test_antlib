#pragma once

#include <QPainter>

class AntRender
{
public:

  static QString name;
  static void rend(const QString &path, QPainter *painter, const QRectF& boundingRect);
};


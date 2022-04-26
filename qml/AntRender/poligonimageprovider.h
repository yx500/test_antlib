#pragma once

#include <QQuickImageProvider>

#include "poligondata.h"

class PoligonImageProvider: public QQuickImageProvider
{
public:
  PoligonImageProvider(PoligonData* data);

  QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

private:

  QString renewUrl();
  PoligonData* data=nullptr;

};




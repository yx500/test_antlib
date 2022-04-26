#include "poligondata.h"

//static int ccc=0;

PoligonData::PoligonData(QObject *parent)
    : QObject(parent)
{
  //  qDebug()<<"PoligonData"<<idx()<<++ccc;
}

PoligonData::~PoligonData() {
  //  qDebug()<<"~PoligonData"<<idx()<<--ccc;
}

void PoligonData::update()
{
  setImageUrl( renewUrl() );
}


void PoligonData::setPoligon(const QString &newArr)
{
  m_poligon.clear();
  m_poligon.reserve(newArr.size());
  Q_EMIT poligonChanged();
  setImageUrl( renewUrl() );
}

void PoligonData::setImageUrl(const QString &newImageUrl)
{
  if (m_imageUrl == newImageUrl)
    return;
  m_imageUrl = newImageUrl;
  Q_EMIT imageUrlChanged();
}

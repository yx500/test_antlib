#include <QQuickItem>
#include <QImage>
#include <QBitmap>
#include <QPainter>
#include <QtDebug>

#include "poligonimageprovider.h"
#include "poligonrendercontrol.h"



PoligonImageProvider::PoligonImageProvider(PoligonData* d)
    : QQuickImageProvider(QQuickImageProvider::Pixmap), data( d )
{
}


static void drawPoligon (
    QImage &image,
    const QList<qreal> &poligon,
    int poligonWidth,
    int firstSampleToDraw,
    double scaleX, double scaleTime );

QPixmap PoligonImageProvider::requestPixmap(const QString &/*id*/, QSize *size, const QSize &requestedSize)
{
  //  if(data->idx()==3){
  //    qDebug() << data->idx() //<<"imgSz: "<< imgSz
  //             <<"requestedSize: "<< requestedSize
  //             <<"size: "<< (size ? *size : QSize())
  //             <<"poligonWidth: "<< SeismicParams::instance()->poligonWidth()
  //             <<"id:" << id
  //        ;
  //  }

  int width = PoligonRenderControl::instance()->poligonWidth()*2+1;
  int height = requestedSize.height() > 0 ? std::min( requestedSize.height(), 10000) : 1000;
  QSize imgSz(width, height);
  if (size)
    *size = imgSz;

  if( data && !data->poligon().isEmpty() ){
    QImage tmp(imgSz, QImage::Format_ARGB32_Premultiplied);
    tmp.fill(Qt::transparent);
    drawPoligon(tmp
              , data->poligon()
              , PoligonRenderControl::instance()->poligonWidth()
              , PoligonRenderControl::instance()->firstSample()
              , PoligonRenderControl::instance()->scaleV()
              , PoligonRenderControl::instance()->scaleT()
              );
    return QPixmap::fromImage(tmp);
  }

  QPixmap pixmap(imgSz);
  pixmap.fill(Qt::transparent);
  //  pixmap.fill(QColor("yellow").rgba());
  //  QBitmap pixmap(imgSz); pixmap.clear();
  QPainter painter(&pixmap);
  painter.setPen(Qt::darkRed);
  painter.drawLine( QPoint(imgSz.width()/2, 0), QPoint(imgSz.width()/2, imgSz.height()) );

  if( !data  || 0 ){
    QRect r = pixmap.rect() - QMargins(0,0,1,1);
    painter.drawEllipse(r);
    //  QFont f = painter.font();
    //  f.setPixelSize(20);
    //  painter.setFont(f);
    //  painter.setPen(Qt::black);
    //  painter.drawText(QRectF(0, 0, width, height), Qt::AlignCenter, id);
  }

  return pixmap;
}




static void drawPoligon (
    QImage &image,// int image[], int imageHeight, int imageWidth,
    const QList<qreal> &poligon, //double  poligon[], int poligonLength,
    int poligonWidth,
    int firstSampleToDraw,
    double scaleX, double scaleTime)
{
  int imageHeight = image.height();
//  int imageWidth = image.width();
  int poligonLength = poligon.length();
  const int poligonXcoord = image.width()/2;

  // as first step before all poligon drawing, need to reset whole image to white color;
  const QRgb BLACK_COLOR = qRgb(189, 149, 39);
  //  scaleX = scaleX*poligonWidth*0.05;
  if (scaleTime <= 1) {
    double currentSample = firstSampleToDraw;
    int oldValue = 0;
    for (int i = 0; i < imageHeight; i ++) {
      int value = 0;
      if (currentSample < poligonLength-1) {
        int x = (int)currentSample;
        double v1 = poligon [x];
        double v2 = poligon [x+1];
        value = (int) (scaleX * (v1+(v2-v1)*(currentSample-x)));
      }
      value = std::min (value, poligonWidth);
      value = std::max (value, -poligonWidth);

      QRgb* line = (QRgb *)image.scanLine(i);
      if (value >= 0) {
        int minV = std::min(0, oldValue);
        for (int j = poligonXcoord + minV; j <= poligonXcoord + value; j++) {
          //>          image[i*imageWidth+j] = BLACK_COLOR;
          Q_ASSERT( j < image.width() );
          if ( j < image.width() )
            line[j]=BLACK_COLOR;
        }
      } else {
        int minV = std::min(value, oldValue);
        int maxV = std::max(value, oldValue);
        for (int j = poligonXcoord+minV; j <= poligonXcoord + maxV; j++) {
          //>          image[i*imageWidth+j] = BLACK_COLOR;
          Q_ASSERT( j < image.width() );
          if ( j < image.width() )
            line[j]=BLACK_COLOR;
        }
      }
      oldValue = value;
      currentSample += scaleTime;
    }
  } else {
    double currentPixel = 0;
    double deltaPixel = 1/scaleTime;
    int oldValue = 0;
    for (int i = firstSampleToDraw; i < poligonLength; i++) {
      if (currentPixel >= imageHeight) {
        break;
      }
      int poligonValue = (int) (poligon[i]*scaleX);
      poligonValue = std::min(poligonValue, poligonWidth);
      poligonValue = std::max(poligonValue, -poligonWidth);

      int minV = std::min(poligonValue, oldValue);
      minV=std::min(0, minV);
      int maxV = std::max(poligonValue, oldValue);
      QRgb* line = (QRgb *)image.scanLine((int)currentPixel);
      for (int j = poligonXcoord+minV; j <= poligonXcoord + maxV; j++) {
        //>        image[(int)currentPixel*imageWidth+j] = BLACK_COLOR;
        Q_ASSERT( j < image.width() );
        if ( j < image.width() )
          line[j]=BLACK_COLOR;
      }
      oldValue = poligonValue;
      currentPixel += deltaPixel;
    }
  }
}

#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QDebug>
#include "myprop_helpers.h"

class PoligonData : public QObject
{
  Q_OBJECT
  QML_ELEMENT

  Q_PROPERTY(int idx READ idx);
  MYSIMPLE_PROP(bool,   busy);
  Q_PROPERTY(QString imageUrl READ imageUrl WRITE setImageUrl NOTIFY imageUrlChanged);
  Q_PROPERTY(QString poligon READ poligon WRITE setPoligon NOTIFY poligonChanged);

  MYSIMPLE_PROP(QString,   key_name);

public:

  explicit PoligonData(QObject *parent = nullptr);
  ~PoligonData();

  int idx() const { return m_idx; }
  void setIdx(const int idx) { m_idx = idx; update(); }

  const QString &poligon() const { return m_poligon; }
  void setPoligon(const QString &newArr);

  const QString &imageUrl() const { return m_imageUrl; }
  void setImageUrl(const QString &newImageUrl);

  Q_INVOKABLE const QString providerName() const { return QString("apoligon%1").arg(m_idx); }
  Q_INVOKABLE void  update();

Q_SIGNALS:
  void poligonChanged();
  void imageUrlChanged();
  void avgValueChanged();

private:

  int m_counter=0;
  QString renewUrl(){ return  QString("image://%1/c%2").arg( providerName() ).arg( ++m_counter ); }

  int       m_idx=-1;
  QString   m_poligon;
  QString   m_imageUrl;
};


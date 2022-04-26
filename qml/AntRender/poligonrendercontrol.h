#pragma once

#include <QObject>
#include <QQmlEngine>

#include "poligondata.h"
#include "myprop_helpers.h"
#include <array>

class PoligonRenderControl: public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  MYSIMPLE_PROP(qreal, scaleT);
  MYSIMPLE_PROP(qreal, scaleV);
  MYSIMPLE_PROP(int,   poligonWidth);
  MYSIMPLE_PROP(int,   firstSample);

public:
  explicit PoligonRenderControl(QObject *parent = nullptr): QObject(parent) {};

  static PoligonRenderControl* instance(){
    static PoligonRenderControl* instance(new PoligonRenderControl);
    return instance;
  }

  static void initializeEngine(QQmlEngine *engine, const char *uri, QObject *parent = nullptr);

  Q_INVOKABLE PoligonData* get(int idx);
  Q_INVOKABLE int  size() { return PoligonsCapacity; };
  Q_INVOKABLE void repaintPoligons();

private:
  static constexpr int PoligonsCapacity=96;
  static inline std::array<PoligonData*, PoligonsCapacity> poligons;
};


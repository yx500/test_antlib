#include "poligonrendercontrol.h"
#include <QQmlContext>
#include <algorithm>

#include "qobjectvectormodel.h"
#include "poligonimageprovider.h"


void PoligonRenderControl::initializeEngine(QQmlEngine *engine, const char *uri, QObject *parent){

  qmlRegisterType<PoligonData>(uri, 1, 0, "SeismicPoligonData");
  using Model = QObjectVectorModel<PoligonData>;
  auto model = new Model(parent);
  for (size_t i=0; i<poligons.size(); ++i) {
    auto data = poligons[i] = new PoligonData(parent);
    engine->setObjectOwnership(data, QQmlEngine::CppOwnership);
    data->setIdx(i);
    data->busy(false);
    auto provider = new PoligonImageProvider(data);
    engine->addImageProvider( data->providerName(), provider );
    model->append(data);
  }
  engine->rootContext()->setContextProperty("poligonImageProvidersModel", model);

  qmlRegisterSingletonType<PoligonRenderControl>(uri, 1, 0, "ThePoligonRenderControl",  [](QQmlEngine *engine, QJSEngine *)-> QObject* {
    engine->setObjectOwnership(PoligonRenderControl::instance(), QQmlEngine::CppOwnership);
    return PoligonRenderControl::instance();
  });
}

PoligonData *PoligonRenderControl::get(int idx)
{
  static PoligonData *null( new PoligonData() );
  return size_t(idx) < poligons.size() ? poligons.at(idx) : null;
}

void PoligonRenderControl::repaintPoligons()
{
  for(auto&& t: poligons)
    t->update();
}


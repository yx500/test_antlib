#include "register_qtypes.h"
#include <QQmlEngine>
#include <QQmlContext>
#include <QtQuick>

#include "fileio.h"
#include "logger.h"
//#include "tracesvgprovider.h"

void register_qtypes::registerTypes(const char *uri)
{
  qDebug() << "QMl type register uri:" << uri;
  qmlRegisterType<FileIO>(uri, 1, 0, "FileIO");

  //singletons invariants
  qmlRegisterSingletonType<Logger>(uri, 1, 0, "TheLog", [](QQmlEngine *engine, QJSEngine *)-> QObject* {
    engine->setObjectOwnership(Logger::instance(), QQmlEngine::CppOwnership);
    return Logger::instance();
  });

}

#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QDir>
#include <QDirIterator>
#include <QSettings>
#include <QFontDatabase>
#include <QQuickStyle>
#include <QIcon>
#include "poligonrendercontrol.h"
#include "register_qtypes.h"
#include "logger.h"

static const char uri[] = "Apoligon";


int main(int argc, char *argv[])
{
#ifdef GIT_REVISION
  qDebug() << "Version: " << GIT_REVISION << "/n";
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  //see HighDpiFix.cpp
#else
  QQuickStyle::setStyle("Basic");
#endif
  Logger::init(argc, argv);

  QGuiApplication app(argc, argv);
  app.setOrganizationName("Apoligon");
  app.setApplicationName("apoligon-face");
  QSettings::setDefaultFormat(QSettings::IniFormat);
  QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, "./" );
  QSettings settings;
  qDebug()<<"Ini file:"<<settings.fileName();

//  app.setWindowIcon( QIcon(":/Design/images/favicon.png"));

  QQmlApplicationEngine engine;
//  engine.rootContext()->setContextProperty("translator", &translator);
  register_qtypes::registerTypes(uri);
  //singletons invariants
  engine.rootContext()->setContextProperty("myconsole", Logger::instance());
  PoligonRenderControl::initializeEngine(&engine, uri, &app);


//  QDirIterator it(":", QDirIterator::Subdirectories); while (it.hasNext()) qDebug() << it.next();

  const QUrl url(QStringLiteral("qrc:/AntRender/AppPoligons.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
      &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      }, Qt::QueuedConnection);

  engine.addImportPath(QStringLiteral(":/"));
  engine.addImportPath("../desktop");
  engine.addImportPath(".");
  engine.load(url);

  return app.exec();
}

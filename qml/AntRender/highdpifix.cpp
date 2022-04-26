#include <QtGui/QGuiApplication>
#ifdef Q_OS_WIN
#    include <Windows.h>
#endif

namespace apoligon {

// Fix dpi at application startup
class HighDpiFix
{
  HighDpiFix()
  {
#ifdef Q_OS_WIN
#    if _WIN32_WINNT >= 0x0600
    ::SetProcessDPIAware();
#    endif
#endif // Q_OS_WIN

#if QT_VERSION_MAJOR < 6 // AA_EnableHighDpiScaling is enabled by default on qt6
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  }
  static HighDpiFix singleton;
};

HighDpiFix HighDpiFix::singleton;

}

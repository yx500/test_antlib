#include "logger.h"
#include <QDebug>
#include <QFile>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <QDateTime>

// Get the default Qt message handler.
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(0);


static std::unique_ptr<QFile> log_file;

static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  // Call the default handler.
  (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
  if( !log_file) return;


  QString tag;
  switch (type) {
  case QtDebugMsg:    tag = QString("Dbg  | "); break;
  case QtWarningMsg:  tag = QString("Warn | "); break;
  case QtInfoMsg:     tag = QString("Inf  | "); break;
  case QtCriticalMsg: tag = QString("Critical | "); break;
  case QtFatalMsg:    tag = QString("Fatal    | "); break;
  }

  QByteArray localMsg = msg.toLocal8Bit();
  const char *file = context.file ? context.file : "";
//  const char *function = context.function ? context.function : "";
  QString txt = QString(" (%2:%3)").arg(file).arg(context.line); //.arg(function);

  if( log_file && log_file->open(QIODevice::WriteOnly | QIODevice::Append) ){
    QTextStream ts(log_file.get());
    ts << QDateTime::currentDateTime().toString("hh:mm:ss.zzz | ") << tag << localMsg.constData();
    if( type > QtWarningMsg )
      ts << txt;
    ts << "\n";
    log_file->close();
  }
}


void Logger::init(int /*argc*/, char *argv[])
{
  //todo util::LogOptions::parse(argc, argv);
  log_file = std::make_unique<QFile>( QString("%1.log").arg(argv[0]) ) ;
  log_file->remove();
  qInstallMessageHandler(myMessageOutput);
}

void Logger::debug(const QString &msg)
{
  qDebug()<<msg;
}

void Logger::log(const QString &msg)
{
  qInfo()<<msg;
}

void Logger::error(const QString &msg)
{
  qCritical()<<msg;
}


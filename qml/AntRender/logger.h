#pragma once

#include <QObject>
#include <QQmlEngine>


class Logger: public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

public:
  explicit Logger(QObject *parent = nullptr) : QObject(parent) {}

  static Logger* instance(){
    static Logger instance;
    return &instance;
  }
  static void init(int argc, char *argv[]);

  Q_INVOKABLE  void debug(const QString& msg);
  Q_INVOKABLE  void log(const QString& msg);
  Q_INVOKABLE  void error(const QString& msg);

};


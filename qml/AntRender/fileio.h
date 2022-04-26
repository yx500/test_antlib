#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QFile>
#include "myprop_helpers.h"

class FileIO : public QObject
{
  Q_OBJECT
  QML_ELEMENT

  Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
  Q_PROPERTY(bool exists READ exists)
  Q_PROPERTY(bool writeable READ writeable)
  Q_PROPERTY(bool readable READ readable)
  Q_PROPERTY(qint64 size READ size)
  MYSIMPLE_PROP(QString, error)

public:
  explicit FileIO(QObject *parent = nullptr);
  Q_INVOKABLE QString read();
  Q_INVOKABLE bool write(const QString& text);
  Q_INVOKABLE bool append(const QString& text);
  Q_INVOKABLE bool rename(const QString& newName);

  inline QString source() const { return m_file.fileName(); }
  inline bool exists() const { return m_file.exists(); }
  inline bool writeable() const { return m_file.permissions().testFlag(QFileDevice::WriteUser); }
  inline bool readable() const { return m_file.permissions().testFlag(QFileDevice::ReadUser); }
  inline qint64 size() const { return m_file.size(); }
  Q_INVOKABLE inline QString readAll() { return read(); }

  Q_INVOKABLE QString readBinaryToBase64();
  Q_INVOKABLE QString readBinaryToBase64(const QString& source){
    setSource(source);
    return readBinaryToBase64();
  }


public Q_SLOTS:
  void setSource(const QString& source);

Q_SIGNALS:
  void sourceChanged(const QString& source);

private:
  QFile m_file;
};

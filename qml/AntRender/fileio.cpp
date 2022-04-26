#include "fileio.h"

#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>

FileIO::FileIO(QObject *parent)
    : QObject(parent)
      , error_()
{
}

void FileIO::setSource(const QString &source)
{
  error_ = "";
  // fix to convert URL's to local file names
  QUrl url(source);
  QString localName = url.isLocalFile() ? QDir::toNativeSeparators(url.toLocalFile()) : source;
  if (m_file.fileName() != localName) {
    m_file.setFileName(localName);
    Q_EMIT sourceChanged(localName);
  }
}

bool FileIO::rename(const QString &newName)
{
  bool success = m_file.rename(newName);
  if (success) {
    Q_EMIT sourceChanged(newName);
  }
  return success;
}

QString FileIO::readBinaryToBase64()
{
  if (m_file.fileName().isEmpty()) {
    error( tr("empty source file name") );
    return QString();
  }

  if (!m_file.open(QIODevice::ReadOnly)) {
    error( tr("cannot open file '%1' for reading: %2").arg(m_file.fileName(), m_file.errorString()) );
    return QString();
  }

  QString txt = m_file.readAll().toBase64();
  m_file.close();
  return txt;
}

QString FileIO::read()
{
  if (m_file.fileName().isEmpty()) {
    error( tr("empty source file name") );
    return QString();
  }

  if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    error( tr("cannot open file '%1' for reading: %2").arg(m_file.fileName(), m_file.errorString()) );
    return QString();
  }

  QString txt = QString::fromUtf8(m_file.readAll());
  m_file.close();
  return txt;
}


bool FileIO::write(const QString& text)
{
  if (m_file.fileName().isEmpty()) {
    error( tr("empty source file name") );
    return false;
  }

  if (!m_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
    error( tr("cannot open file '%1' for writing: %2").arg(m_file.fileName(), m_file.errorString()) );
    return false;
  }

  QTextStream out(&m_file);
  out << text;
  m_file.close();
  return true;
}

bool FileIO::append(const QString& text)
{
  if (m_file.fileName().isEmpty()) {
    error( tr("empty source file name") );
    return false;
  }

  if (!m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    error( tr("cannot open file '%1' for writing: %2").arg(m_file.fileName(), m_file.errorString()) );
    return false;
  }

  QTextStream out(&m_file);
  out << text;
  m_file.close();
  return true;
}

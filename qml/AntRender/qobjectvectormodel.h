#pragma once

#include <QAbstractListModel>
#include <algorithm>

template <class qobj_type>
class QObjectVectorModel: public QAbstractListModel
{
  //cannot use Q_OBJECT but that's ok here

public:
  explicit QObjectVectorModel(QObject *parent = nullptr)
      : QAbstractListModel(parent) {}

  QObjectVectorModel(std::initializer_list<qobj_type> initialContents, QObject *parent = nullptr)
      : QAbstractListModel(parent) {
    contents.reserve(static_cast<int>(initialContents.size()));
    std::copy(initialContents.begin(), initialContents.end(), std::back_inserter(contents));
  }

  void setValue(int row, qobj_type value) {
    if (contents[row] != value) {
      contents[row] = value;
      const auto idx = index(row);
      Q_EMIT dataChanged(idx, idx, QVector<int>{Qt::DisplayRole});
    }
  }

  void append(qobj_type* value) {
    beginInsertRows(QModelIndex(), contents.count(), contents.count());
    contents.append(value);
    endInsertRows();
  }

  void append(std::initializer_list<qobj_type> values) {
    beginInsertRows(QModelIndex(), contents.count(), contents.count() + static_cast<int>(values.size()) -1);
    contents.append(values);
    endInsertRows();
  }

  void insert(int row, qobj_type value) {
    beginInsertRows({}, row, row);
    contents.insert(row, value);
    endInsertRows();
  }

  void insert(int row, std::initializer_list<qobj_type> values) {
    beginInsertRows({}, row, row +  static_cast<int>(values.size()) -1);
    contents.reserve( contents.size() + static_cast<int>(values.size()));
    auto oldEnd = contents.end();
    contents.append(values);
    std::rotate(contents.begin() + row, oldEnd, contents.end());
    endInsertRows();
  }

  // QAbstractItemModel interface
public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override
  {
    if (parent.isValid())
      return 0;
    return contents.count();
  }

  QVariant data(const QModelIndex &index, int role) const override
  {
    if (!index.isValid())  return {};

    if(index.row() >= 0 && index.row() < rowCount()){
      auto data = contents.at(index.row());
        switch (role) {
        case Qt::DisplayRole:
          return QString( qobj_type::staticMetaObject.className() )+ ", row: " + QString::number(index.row());
        case Qt::UserRole + 1:
          return QVariant::fromValue(data);
        default:
          return qobj_type::staticMetaObject.property(role - Qt::UserRole - 1).read(data);
        }
    }

    return {};
  }

  bool removeRows(int row, int count, const QModelIndex &parent = {}) override
  {
    if (row < 0 || count < 0 || row + count >= contents.count())
      return false;
    beginRemoveRows(parent, row, row + count -1);
    auto it = std::rotate(contents.begin() + row, contents.begin() + row + count, contents.end());
    contents.erase(it, contents.end());
    endRemoveRows();
    return true;
  }

protected:
  QHash<int, QByteArray> roleNames() const override
  {
    QHash<int, QByteArray> roles;
    int role = Qt::UserRole + 1;
    roles.insert(role++, "qobj");
    auto mo = qobj_type::staticMetaObject;
    for( int i = mo.propertyOffset(); i < mo.propertyCount(); ++i)
      roles.insert(role++, mo.property(i).name());
    return roles;
  }

private:
  QVector<qobj_type*> contents;
};


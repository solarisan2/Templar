#ifndef USEDSOURCEFILEMODEL_H
#define USEDSOURCEFILEMODEL_H
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include <QAbstractItemModel>

namespace Templar {


struct SourceFileNode
{
    SourceFileNode()
        : parent(nullptr), id(std::numeric_limits<size_t>::max()), row(-1), visible(true)
    {}
    SourceFileNode(const QString &name,SourceFileNode *parent)
        : name(name), parent(parent), id(std::numeric_limits<size_t>::max()), row(-1), visible(true)
    {}
    SourceFileNode *parent;
    QString name;
    QString fullPath;
    bool visible;
    QVector< SourceFileNode * > children;
    size_t id;
    int row;
    void setVisible(bool value);
};

typedef QMap<size_t, SourceFileNode*> UsedFileMap;

class UsedSourceFileModel : public QAbstractItemModel
{
public:
    UsedSourceFileModel(const QString &fileName);
    void Add(const QString &newPath );

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const { return 1; }
    QVariant data(const QModelIndex &index, int role) const;
   // bool hasChildren(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    SourceFileNode root;
    static UsedFileMap nodeIdMap;

};
}
#endif // USEDSOURCEFILEMODEL_H
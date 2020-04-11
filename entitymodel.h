#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include <iostream>
#include <QFileInfoList>

#include "inheritexceptiondelegate.h"
#include "imodeldelegates.h"
#include "ifilemodel.h"

#define THROW_MSG_INHERIT "Template argument not direct base of Model"

typedef QList<const IFileModel<>*> DefaultFileModelList;

using namespace std;
namespace EntityModelContext {
    enum typeMode {nullEntity = 0x00,fileInformationEntity = 0x01,fileActionEntity = 0x02,directoryCountEntity = 0x04};
    class EntityModel;
}

class EntityModel : public IModel<int>
{
public:
    QUuid id() const override
    {
        return _id;
    }
    int type() const override
    {
        return _type;
    }

    void setType(const int &type) override
    {
        _type = type;
    }
private:
    int _type = EntityModelContext::nullEntity;
    QUuid _id;
};


class ErrorEntity : public EntityModel
{
public:
    QString errorDescription() const
    {
        return _errorDescription;
    }

    void setErrorDescription(const QString &msg)
    {
        _errorDescription = msg;
    }
private:
    QString _errorDescription = "No error";
};

struct DirectoryEntity : public EntityModel
{
public:
    quint64 size() const
    {
        return _directorySize;
    }

    void setSize(const quint64 &size)
    {
        _directorySize = size;
    }

    QString name() const
    {
        return _directoryName;
    }

    void setName(const QString &name)
    {
        _directoryName = name;
    }

    QString path() const
    {
        return _directoryPath;
    }

    void setPath(const QString &path)
    {
        _directoryPath = path;
    }

private:
    quint64 _directorySize;
    QString _directoryName;
    QString _directoryPath;
};

template<typename TFileList = DefaultFileModelList>
class FileRuleEntity : public EntityModel
{
public:
    QStringList paths() const
    {
        return _directoryPaths;
    }

    void setPaths(const QStringList &paths)
    {
        _directoryPaths = paths;
    }

    TFileList files() const
    {
        return _allFiles;
    }

    void setFiles(const TFileList &files)
    {
        _allFiles = files;
    }

    int ruleAction() const
    {
        return _fileActionRule;
    }

    void setRuleAction(const int &action)
    {
        _fileActionRule = action;
    }

    QStringList destinations() const
    {
        return _fileDestinations;
    }
    void setDestinations(const QStringList &paths)
    {
        _fileDestinations = paths;
    }

private:
    QStringList _directoryPaths;
    TFileList _allFiles;
    int _fileActionRule = 0x01;
    QStringList _fileDestinations = QStringList();
};

class FileInformationEntity : public EntityModel
{
public:
    QStringList filePaths() const
    {
        return _filePaths;
    }

    void setFilePaths(const QStringList &paths)
    {
        _filePaths = paths;
    }

private:
    QStringList _filePaths;
};

#endif // ENTITYMODEL_H

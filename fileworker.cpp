#include "fileworker.h"

FileWorker::FileWorker()
{
    busyMessage = "Luke Fileworker is busy. Patience my young padawan.";
    isBusy = false;
    #ifdef __WIN32__
        qt_ntfs_permission_lookup++;
    #elif __WIN64__
        qt_ntfs_permission_lookup++;
#endif
}

bool FileWorker::removeFileItems(const FileModelList& filePaths, QStringList *const err)
{
    if(filePaths.isEmpty())
        return true;

    for(ITreeModelDelegate<FileModel,DefaultModelType>* modelDelegate: filePaths)
    {
        const FileModel *model = static_cast<const FileModel*>(modelDelegate->model());
        QString absoluteFilePath = model->absoluteFilePath();
        if(model->isFile())
        {
            QFile fileItem(model->absoluteFilePath());
            if(!fileItem.remove())
            {
                *err << "Operation on: " + model->fileName() + " in: " +
                    model->absolutePath() + " returned: " + fileItem.errorString();
            }
        }
        else if(model->isDir())
        {
            removeFileItems(modelDelegate->children(),err);
            QDir dir(absoluteFilePath);
            dir.rmdir(absoluteFilePath);
        }
    }

    return true;
}

bool FileWorker::moveFileItems(const FileModelList fileObjects, const QStringList destinations, QStringList * const err)
{

    // TODO: Implement some error handling when something goes wrong
    bool result = true;
    for(QString destPath : destinations)
    {
        QDir dir(destPath);
        if(!dir.exists())
            dir.mkdir(destPath);

        for(ITreeModelDelegate<FileModel,DefaultModelType>* modelDelegate : fileObjects)
        {
            bool noErrors = true;
            auto model = static_cast<const FileModel*>(modelDelegate->model());
            QString AbsoluteFilePath = StaticStringCollections::checkAndCorrectForBackslash(destPath) + model->fileName();
            if(model->isDir())
            {
                noErrors = moveFileItems(modelDelegate->children(),QStringList() << AbsoluteFilePath,err);
                result = noErrors ? result : false;
            }
            else if(model->isFile())
            {
                QFile file(model->absoluteFilePath());
                QString errString;
                noErrors = file.copy(AbsoluteFilePath);
                result = noErrors ? result : false;
                if(!noErrors)
                {
                    *err << QString("Failed to delete file '%1'. Error provided: %2")
                            .arg(model->fileName()).arg(file.errorString());
                }
            }
            else if(!model->exists())
                continue;
            if(noErrors)
                removeFileItems(FileModelList() << FileModelDelegate<FileModel>::buildFileModelDelegate(model->absoluteFilePath()),err);
        }
    }
    return result;
}

bool FileWorker::copyFileItems(const FileModelList fileObjects, const QStringList destinations, QStringList * const err)
{
    // TODO: Implement some error handling when something goes wrong
    Q_UNUSED(err);
    bool result = true;
    for(QString destPath : destinations)
    {
        QDir dir(destPath);
        if(!dir.exists())
            dir.mkdir(destPath);

        for(const ITreeModelDelegate<FileModel,DefaultModelType>* modelDelegate : fileObjects)
        {
            bool noErrors = true;
            const FileModel* model = static_cast<const FileModel*>(modelDelegate->model());
            QString AbsoluteFilePath = StaticStringCollections::checkAndCorrectForBackslash(destPath) + model->fileName();
            if(model->isDir())
            {
                noErrors = copyFileItems(modelDelegate->children(),QStringList() << AbsoluteFilePath);
                result = noErrors ? result : false;
            }
            else if(model->isFile())
            {
                noErrors = QFile::copy(model->absoluteFilePath(),AbsoluteFilePath);
                result = noErrors ? result : false;
            }
            else if(!model->exists())
                continue;
        }
    }
    return result;
}

void FileWorker::processDirectoryCountEntity(const IModelDelegate<DirectoryEntity, EntityType> *delegate)
{
    auto entity = new DirectoryEntity(*delegate->model());

    QFileInfo fInfo = entity->directoryPath;

    entity->directorySize = folderSize(fInfo.absoluteFilePath());

    emit sendFolderSizeEntity(entity);
}

void FileWorker::processEntity(IModelDelegate<EntityModel,EntityType> *delegate)
{
    isBusy = true;
    if(delegate->type() == EntityModel::nullEntity)
    {
        emit jobDone(true);
        isBusy = false;
        return;
    }

    if(delegate->type() == EntityModel::fileActionEntity)
    {
        try {
            processFileEntity(DelegateBuilder::buildDelegate<FileRuleEntity>(delegate->model()));
        } catch (InheritExceptionDelegate<EntityModel,FileRuleEntity> *e) {
            throw e->what();
        }
    }
    else if(delegate->type() == EntityModel::fileInformationEntity)
    {
        try {
            processFileInformationEntity(DelegateBuilder::buildDelegate<FileInformationEntity>(delegate->model()));
        } catch (const InheritExceptionDelegate<EntityModel,FileInformationEntity> *e) {
            throw e->what();
        }
    }
    else if(delegate->type() == EntityModel::directoryCountEntity)
    {
        try {
            processDirectoryCountEntity(DelegateBuilder::buildDelegate<DirectoryEntity>(delegate->model()));
        } catch (const InheritExceptionDelegate<EntityModel,DirectoryEntity> *e) {
            throw e->what();
        }
    }

    delegate = nullptr;
    isBusy = false;

    emit requestNextEntity();
}

int FileWorker::folderCount(QString p)
{
    QFileInfo info = p;
    QDirIterator ite(info.absoluteFilePath(),
                     QDir::NoDotAndDotDot |
                     QDir::NoDot | QDir::AllEntries,
                     QDirIterator::Subdirectories);
    int taeller = 0;
    while(ite.hasNext())
    {
        if(QFileInfo(ite.fileInfo()).isDir())
            taeller++;
        emit sendStatusLineMessage(QString("%1 folders").arg(QString::number(taeller)));
        ite.next();
    }
    return taeller;
}

int FileWorker::fileCountFromPath(QString p)
{
    QDirIterator ite(QFileInfo(p).absoluteFilePath(),
                     QDir::NoDotAndDotDot |
                     QDir::NoDot | QDir::Files,
                     QDirIterator::Subdirectories);
    int taeller = 0;
    while(ite.hasNext())
    {
        if(QFileInfo(ite.next()).isFile())
            taeller++;
        emit sendStatusLineMessage(QString("%1 files").arg(QString::number(taeller)));
    }
    return taeller;
}

qint64 FileWorker::folderSize(const QString &path)
{
    long long sZ = 0;

    QDirIterator iT(QFileInfo(path).absoluteFilePath(),
                    QDir::NoDotAndDotDot |
                    QDir::Files | QDir::System |
                    QDir::Hidden,
                    QDirIterator::Subdirectories);
    while(iT.hasNext())
     {
         QString fP = iT.next();

         QFile f(fP);
         if(f.open(QIODevice::ReadOnly))
         {
            sZ += f.size();
            emit sendStatusLineMessage( "Calculating folder size: " + f.fileName());
         }
         f.close();
     }
    return sZ;
}

void FileWorker::handleProcessRequest()
{
    if(isBusy)
        return;
    else
        emit requestNextEntity();

}

void FileWorker::processFileInformationEntity(const IModelDelegate<FileInformationEntity,EntityType> *delegate)
{
    auto entity = delegate->model();

    QList<DirectoryItem> directories;
    for (auto path : entity->filePaths)
    {
        DirectoryItem item;

        QString denotation;
        item.path = path;
        double directorySize = SBC::convertFromBytes(folderSize(path),denotation);
        item.dirSize = QString::number(directorySize) + " " + denotation;
        item.numberOfDirectories = folderCount(path);
        item.numberOfFiles = fileCountFromPath(path);
        item.directoryContent = QDir(path).entryInfoList(QDir::AllEntries |
                                                         QDir::System |
                                                         QDir::Hidden);
        item.directoryItemModels = ByteCollection::assembleItemModelsFromPath(path);
        item.sufList = ByteCollection::getListOfSuffixOccuriencies(path);
        directories << item;
    }

    emit processFinished(directories);
}

void FileWorker::reProcessFileInformationEntity(const QStringList &paths)
{
    QList<DirectoryItem>directories;
    for(const QString &p : paths)
    {
        QString denotation;
        DirectoryItem item;
        item.path = p;
        double directorySize = SBC::convertFromBytes(folderSize(p),denotation);
        item.dirSize = QString::number(directorySize) + " " + denotation;
        item.numberOfDirectories = folderCount(p);
        item.numberOfFiles = fileCountFromPath(p);
        item.directoryItemModels = ByteCollection::assembleItemModelsFromPath(p);
        item.sufList = ByteCollection::getListOfSuffixOccuriencies(p);
        directories << item;
    }
    emit processFinished(directories);
}

void FileWorker::processFileEntity(const IModelDelegate<FileRuleEntity,EntityType> *delegate)
{
    auto model = delegate->model();

    if(model->fileActionRule == FilesContext::Delete || model->fileActionRule == FilesContext::None)
    {
        // TODO: You have to pass an error related stringlist in order to be able to display errors
        removeFileItems(model->allFiles);
        auto entity = DelegateBuilder::buildFileInformationEntity
                <FileInformationEntity>(model->directoryPaths)->model();

        processFileInformationEntity(DelegateBuilder::buildDelegate<FileInformationEntity>(entity));
    }
    else if(model->fileActionRule == FilesContext::Move)
    {
        moveFileItems(model->allFiles,model->fileDestinations);
        auto entity = DelegateBuilder::buildFileInformationEntity
                <FileInformationEntity>(model->directoryPaths)->model();

        processFileInformationEntity(DelegateBuilder::buildDelegate<FileInformationEntity>(entity));

    }
    else if(model->fileActionRule == FilesContext::Copy)
        copyFileItems(model->allFiles,model->fileDestinations);

    model = nullptr;
}

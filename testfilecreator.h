#ifndef TESTFILECREATOR_H
#define TESTFILECREATOR_H

#include <qfile.h>
#include <qlist.h>
#include <qfileinfo.h>
#include <qdir.h>
#include <qdiriterator.h>
#include <QDateTime>
#include <qmap.h>
#include "mainapplication.h"
#include <QFileInfoList>
#include <iterator>


extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

#define NUMBER_OF_MAPPINGS 50


struct VIRTUAL_FILE_OBJECT
{
    QString filePath;
    myDateTime dateCreated; // Has to be altered to perform tests
    QFileInfo additionalInformation; // Static information not to be altered

};

class VirtualObjects
{
public:
    explicit VirtualObjects();
    const VIRTUAL_FILE_OBJECT value(const QString &path);

    void operator<<(const VIRTUAL_FILE_OBJECT &obj);
    bool operator==(VirtualObjects objects);
    VIRTUAL_FILE_OBJECT operator[](int a);

    inline int count(){return _objects.count();}

private:
    QList<VIRTUAL_FILE_OBJECT> _objects;
};

const QString dummyContent = "This is a testfile containing only dummy content\n";

class TestFileCreator
{
public:
    TestFileCreator();

    void createFiles(const QString &directory, const QStringList &fileNames);
    VirtualObjects getVirtualFiles(const QString &filePath);
    bool emptyTestFolder(const QString &dirPath);

    VirtualObjects virtualObjects() const;

private:
    // Private member methods
    void fillDateMappings();
    void appendVirtualFileObject(const QFileInfo &file);
    // Member variables
    QMap<int,myDateTime> dateMappings;
    VirtualObjects _virtualObjects;
};

#endif // TESTFILECREATOR_H

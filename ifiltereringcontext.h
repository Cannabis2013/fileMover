#ifndef IRULEPROCESSOR_H
#define IRULEPROCESSOR_H

#include <qlist.h>

template<class TObject,class TSubject, class TFileListServiceProvider>
class IFiltereringContext
{
public:
    virtual QList<const TSubject*> process(const QList<const TObject*> objects) = 0;
    virtual void setListService(TFileListServiceProvider *service) = 0;
    virtual TFileListServiceProvider *listService() = 0;
};

#endif // IRULEPROCESSOR_H

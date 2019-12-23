#ifndef RULES_H
#define RULES_H
#include "worker.h"
#include "ruledefinitions.h"
#include <QPair>
#include <QStringList>
#include "mydatetime.h"

struct SubRule
{
    // Enumerated values..
    rD::copyMode copymode = rD::noMode;
    rD::fileCompareEntity fileCompareMode = rD::noCompareModeSet;
    rD::fileConditionEntity fieldCondition = rD::nonConditionalMode;

    QPair<uint,QString>sizeLimit;
    QPair<QPair<uint,QString>,QPair<int,QString>> sizeInterval;
    myDateTime date;
    QPair<myDateTime,myDateTime>dateIntervals;
    bool matchWholeWords = false;
    QStringList keyWords;
};

typedef QPair<int,QString> SizeOperand;
typedef QPair<QPair<int,QString>,QPair<int,QString>> SizeInterval;

struct Rule
{
    QString title = "title";
    rD::fileTypeEntity typeFilter = rD::File;
    rD::fileActionEntity actionRuleEntity;
    QStringList destinationPath;
    QString appliesToPath = "Alle";
    bool deepScanMode = false;
    QList<SubRule> subRules;
};


#endif // RULES_H

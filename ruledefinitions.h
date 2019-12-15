#ifndef RULEDEFINITIONS_H
#define RULEDEFINITIONS_H

#include <qlist.h>

/*
 * Mappings:
 *      actionMappings<QString,enum>
 *      conditionMappings<QString,enum>
 *      compareMappings<QString,enum>
 *
 * RuleEntity types:
 *      fileActionEntity
 *      fileConditionEntity
 *      fileCompareEntity
 * fileActionEntity:
 *      Move
 *      Delete
 *      Copy
 *      None
 *
 *  fileConditionEntities
 *      notDefined
 *      filepathMode
 *      extensionMode
 *      parentFolderMode
 *      sizeMode
 *      dateCreatedMode
 *      nonConditionalMode
 *
 *  fileCompareEntity types categorized:
 *      Date:
 *          youngerThan
 *          exactDate
 *          olderThan
 *          interval
 *      Keyword:
 *          containSuffix
 *          dontContainSuffix
 *          matchSuffix
 *          dontMatchSuffix
 *          containWords
 *          dontContainWords
 *          matchWords
 *          dontMatchWords
 *      Size:
 *          lesser
 *          lesserOrequal
 *          equal
 *          biggerOrequal
 *          bigger
 *          sizeInterval
 *          interval
 *
 *  fileCompareEntities using QLineEdit widgets:
 *      containSuffix
 *      dontContainSuffix
 *      matchSuffix
 *      dontMatchSuffix
 *      containWords
 *      dontContainWords
 *      matchWords
 *      dontMatchWords
 *  fileConditionRuleEntities using custom widgets:
 *      dateCreatedMode
 *      dateModifiedMode
 *      sizeMode
 *      typeMode
 */

struct ruleDefinitions
{
    // Enumerated variables..
    enum ruleEntityType {actionProperty,conditionProperty, compareProperty, everyProperty};
    enum fileActionEntity{Move,Delete,Copy,none};
    enum fileConditionEntity{notDefined,
                                 filepathMode,
                                 extensionMode,
                                 sizeMode,
                                 parentFolderMode,
                                 dateCreatedMode,
                                 dateModifiedMode,
                                 nonConditionalMode};

    enum fileCompareEntity{match,
                     dontMatch,
                     contains,
                     dontContain,
                     lesser,
                     lesserOrEqual,
                     equal,
                     biggerOrEqual,
                     bigger,
                     interval,
                     olderThan,
                     exactDate,
                     youngerThan,
                     noDateSet,
                     noCompareModeSet};

    enum fileTypeEntity {Folder, File, unresolved};

    enum copyMode{move,copy,noMode};

    QString nonIntervalString = "Enkel grænse", intervalString = "Interval grænse";
    QStringList intervalConditionalList {"Enkel grænse","Interval grænse"};

    // List variables..
    static QStringList sizeUnits(){return QStringList{"b","kb","mb","gb"};}


    /*
     * Mappings
     *      - actionMappings
     *      - conditionMappings
     *      - compareMappings
     *      - fileTypeFilterMappings
     */

    const QList<QPair<QString,fileActionEntity> > actionMappings {
        QPair<QString,fileActionEntity>("Flytte indhold",fileActionEntity::Move),
                QPair<QString,fileActionEntity>("Slette indhold",fileActionEntity::Delete),
                QPair<QString,fileActionEntity>("Kopiere indhold",fileActionEntity::Copy),
                QPair<QString,fileActionEntity>("Gøre intet",fileActionEntity::none)};

    const QList<QPair<QString,fileConditionEntity> > conditionMappings {
        QPair<QString,fileConditionEntity>("Filnavn",fileConditionEntity::filepathMode),
                QPair<QString,fileConditionEntity>("Filendelse",fileConditionEntity::extensionMode),
                QPair<QString,fileConditionEntity>("Størrelse",fileConditionEntity::sizeMode),
                QPair<QString,fileConditionEntity>("I mappen",fileConditionEntity::parentFolderMode),
                QPair<QString,fileConditionEntity>("Dato oprettet",fileConditionEntity::dateCreatedMode),
                QPair<QString,fileConditionEntity>("Dato redigeret",fileConditionEntity::dateModifiedMode),
                QPair<QString,fileConditionEntity>("Ingen betingelser",fileConditionEntity::nonConditionalMode)};

    const QList<QPair<QString,fileCompareEntity> > compareMappings {
        QPair<QString,fileCompareEntity>("Indeholder følgende",fileCompareEntity::contains),
                QPair<QString,fileCompareEntity>("Indeholder ikke følgende",fileCompareEntity::dontMatch),
                QPair<QString,fileCompareEntity>("Matcher følgende",fileCompareEntity::match),
                QPair<QString,fileCompareEntity>("Matcher ikke følgende",fileCompareEntity::dontMatch),
                QPair<QString,fileCompareEntity>("Større end",fileCompareEntity::bigger),
                QPair<QString,fileCompareEntity>("Større eller lig med",fileCompareEntity::biggerOrEqual),
                QPair<QString,fileCompareEntity>("Lig med",fileCompareEntity::equal),
                QPair<QString,fileCompareEntity>("Mindre eller lig med",fileCompareEntity::lesserOrEqual),
                QPair<QString,fileCompareEntity>("Mindre end",fileCompareEntity::lesser),
                QPair<QString,fileCompareEntity>("Ældre end",fileCompareEntity::olderThan),
                QPair<QString,fileCompareEntity>("Præcis dato",fileCompareEntity::exactDate),
                QPair<QString,fileCompareEntity>("Yngre end",fileCompareEntity::youngerThan)};

    const QList<QPair<QString,fileTypeEntity> > fileTypeFilterMappings
    {
        QPair<QString,fileTypeEntity>("Filer", fileTypeEntity::File),
                QPair<QString,fileTypeEntity>("Mapper", fileTypeEntity::Folder),
                QPair<QString,fileTypeEntity>("Uafklaret", fileTypeEntity::unresolved)
    };

    // Retrieve list methods

    const QStringList allEntitiesToStrings(ruleEntityType property = ruleEntityType::everyProperty)
    {
        QStringList resultingList;
        if(property == ruleEntityType::actionProperty || property == ruleEntityType::everyProperty)
        {
            for ( QPair<QString,fileActionEntity> actionMapping : actionMappings)
                resultingList << actionMapping.first;
        }
        if(property == ruleEntityType::conditionProperty || property == ruleEntityType::everyProperty)
        {
            for ( QPair<QString,fileConditionEntity> pair : conditionMappings)
                resultingList << pair.first;
        }
        if(property == ruleEntityType::compareProperty || property == ruleEntityType::everyProperty)
        {
            for ( QPair<QString,fileCompareEntity> pair : compareMappings)
                resultingList << pair.first;
        }

        return resultingList;
    }

    const QStringList allCompareEntitiesToStrings(fileConditionEntity condition)
    {
        QStringList resultingList;
        if(condition == fileConditionEntity::filepathMode ||
                condition == fileConditionEntity::extensionMode)
        {
            for(QPair<QString,fileCompareEntity> pair : compareMappings) {
                if(pair.second == fileCompareEntity::contains ||
                        pair.second == fileCompareEntity::dontMatch ||
                        pair.second == fileCompareEntity::match ||
                        pair.second == fileCompareEntity::dontMatch)
                {
                    resultingList << pair.first;
                }
            }
        }
        else if(condition == fileConditionEntity::sizeMode)
        {
            for(QPair<QString,fileCompareEntity> pair : compareMappings)
            {
                if(pair.second == fileCompareEntity::bigger ||
                        pair.second ==fileCompareEntity::biggerOrEqual ||
                        pair.second ==fileCompareEntity::equal ||
                        pair.second ==fileCompareEntity::lesserOrEqual ||
                        pair.second == fileCompareEntity::lesser)
                {
                    resultingList << pair.first;
                }
            }
        }
        else if(condition == fileConditionEntity::dateCreatedMode ||
                condition == fileConditionEntity::dateModifiedMode)
        {
            for(QPair<QString,fileCompareEntity> pair : compareMappings)
            {
                if(pair.second == fileCompareEntity::olderThan ||
                        pair.second == fileCompareEntity::exactDate ||
                        pair.second == fileCompareEntity::youngerThan)
                {
                    resultingList << pair.first;
                }
            }
        }

        return resultingList;
    }

    const QStringList allFileTypeEntitiesToStrings()
    {
        QStringList resultingList;

        for (QPair<QString,fileTypeEntity> pair : fileTypeFilterMappings)
            resultingList << pair.first;

        return resultingList;
    }

    // From type1 to type2 methods

    QString fileActionEntityToString(const fileActionEntity mode)
    {
        for(QPair<QString,fileActionEntity> pair : actionMappings)
        {
            if(pair.second == mode)
                return pair.first;
        }
        return QString();
    }

    fileActionEntity fileActionEntityFromString(const QString mode)
    {
        for(QPair<QString,fileActionEntity> pair : actionMappings)
        {
            if(pair.first == mode)
                return pair.second;
        }
        return fileActionEntity::none;
    }

    QString fileConditionEntityToString(const fileConditionEntity mode)
    {
        for(QPair<QString,fileConditionEntity> pair : conditionMappings)
        {
            if(pair.second == mode)
                return pair.first;
        }
        return QString();
    }

    fileConditionEntity fileConditionEntityFromString(const QString string)
    {
        for(QPair<QString,fileConditionEntity> pair : conditionMappings)
        {
            if(pair.first == string)
                return pair.second;
        }
        return fileConditionEntity::notDefined;
    }

    QString fileCompareEntityToString(const fileCompareEntity mode)
    {
        for(QPair<QString,fileCompareEntity> pair : compareMappings)
        {
            if(pair.second == mode)
                return pair.first;
        }
        return QString();
    }

    fileCompareEntity fileCompareEntityFromString(const QString string)
    {
        for(QPair<QString,fileCompareEntity> pair : compareMappings)
        {
            if(pair.first == string)
                return pair.second;
        }
        return fileCompareEntity::noCompareModeSet;
    }

    QString fileTypeEntityToString(fileTypeEntity type)
    {
        for (QPair<QString,fileTypeEntity> pair : fileTypeFilterMappings)
        {
            if(pair.second == type)
                return pair.first;
        }

        return QString();
    }

    fileTypeEntity fileTypeEntityFromString(QString string)
    {
        for (QPair<QString,fileTypeEntity> pair : fileTypeFilterMappings)
        {
            if(pair.first == string)
                return pair.second;
        }

        return fileTypeEntity::unresolved;
    }
};
typedef ruleDefinitions rD;

#endif // RULEDEFINITIONS_H

#ifndef RULEDEFINITIONS_H
#define RULEDEFINITIONS_H

#include <qtranslator.h>

#include "iruledefinitions.h"
#include "TypeDefinitions.h"

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

class RuleDefinitions : public IRuleDefinitions<RulesContext::RuleType,
        RulesContext::RuleAction,
        RulesContext::RuleCriteria,
        RulesContext::RuleCompareCriteria,
        RulesContext::FileType>
{
public:
    // Enumerated variables..
    QString nonIntervalString = "Enkel grænse", intervalString = "Interval grænse";
    QStringList intervalMode {"Enkel grænse","Interval grænse"};

    // List variables..

    const QStringList intervalConditionalList() override
    {
        return intervalMode;
    }

    QStringList sizeUnits() override {return {"b","kb","mb","gb"};}


    /*
     * Mapping methods
     *      - actionMappings
     *      - conditionMappings
     *      - compareMappings
     *      - fileTypeFilterMappings
     */


    // Retrieve list methods

    QString buildDefaultStringValue() override
    {
        return "No criterias";
    }

    const QStringList buildStringListFromEntity(RulesContext::RuleType property = RulesContext::All) override
    {
        QStringList resultingList;
        if(property == RulesContext::Action || property == RulesContext::All)
        {
            for ( QPair<QString,RulesContext::RuleAction> actionMapping : actionMappings())
                resultingList << actionMapping.first;
        }
        if(property == RulesContext::Criteria || property == RulesContext::All)
        {
            for ( QPair<QString,RulesContext::RuleCriteria> pair : criteriaMappings())
                resultingList << pair.first;
        }
        if(property == RulesContext::CompareCriteria || property == RulesContext::All)
        {
            for ( QPair<QString,RulesContext::RuleCompareCriteria> pair : compareCriteriaMappings())
                resultingList << pair.first;
        }

        return resultingList;
    }

    const QStringList fileCompareModesToStringList(RulesContext::RuleCriteria condition) override
    {
        QStringList resultingList;
        if(condition == RulesContext::fileBaseMode ||
                condition == RulesContext::filepathMode ||
                condition == RulesContext::fileExtensionMode)
        {
            for(QPair<QString,RulesContext::RuleCompareCriteria> pair : compareCriteriaMappings()) {
                if(pair.second == RulesContext::contains ||
                        pair.second == RulesContext::dontMatch ||
                        pair.second == RulesContext::match ||
                        pair.second == RulesContext::dontMatch)
                {
                    resultingList << pair.first;
                }
            }
        }
        else if(condition == RulesContext::fileSize)
        {
            for(QPair<QString,RulesContext::RuleCompareCriteria> pair : compareCriteriaMappings())
            {
                if(pair.second == RulesContext::greaterThan ||
                        pair.second ==RulesContext::greaterOrEqualThan ||
                        pair.second ==RulesContext::equal ||
                        pair.second ==RulesContext::lesserOrEqualThan ||
                        pair.second == RulesContext::lesserThan)
                {
                    resultingList << pair.first;
                }
            }
        }
        else if(condition == RulesContext::fileCreatedMode ||
                condition == RulesContext::fileModifiedMode)
        {
            for(QPair<QString,RulesContext::RuleCompareCriteria> pair : compareCriteriaMappings())
            {
                if(pair.second == RulesContext::olderThan ||
                        pair.second == RulesContext::exactDate ||
                        pair.second == RulesContext::youngerThan)
                {
                    resultingList << pair.first;
                }
            }
        }

        return resultingList;
    }

    const QStringList allFileTypeEntitiesToStrings() override
    {
        QStringList resultingList;

        for (QPair<QString,RulesContext::FileType> pair : fileTypeFilterMappings())
            resultingList << pair.first;

        return resultingList;
    }

    // From type1 to type2 methods

    QString fileActionEntityToString(const RulesContext::RuleAction mode) override
    {
        for(QPair<QString,RulesContext::RuleAction> pair : actionMappings())
        {
            if(pair.second == mode)
                return pair.first;
        }
        return QString();
    }

    RulesContext::RuleAction fileActionEntityFromString(const QString mode) override
    {
        for(QPair<QString,RulesContext::RuleAction> pair : actionMappings())
        {
            if(pair.first == mode)
                return pair.second;
        }
        return RulesContext::NoAction;
    }

    QString buildStringFromCriteria(const RulesContext::RuleCriteria mode) override
    {
        for(QPair<QString,RulesContext::RuleCriteria> pair : criteriaMappings())
        {
            if(pair.second == mode)
                return pair.first;
        }
        return QString();
    }

    RulesContext::RuleCriteria buildCriteriaFromString(const QString string) override
    {
        for(QPair<QString,RulesContext::RuleCriteria> pair : criteriaMappings())
        {
            if(pair.first == string)
                return pair.second;
        }
        return RulesContext::notDefined;
    }

    QString buildStringFromCompareCriteria(const RulesContext::RuleCompareCriteria mode) override
    {
        for(QPair<QString,RulesContext::RuleCompareCriteria> pair : compareCriteriaMappings())
        {
            if(pair.second == mode)
                return pair.first;
        }
        return QString();
    }

    RulesContext::RuleCompareCriteria fileCompareEntityFromString(const QString string) override
    {
        for(QPair<QString,RulesContext::RuleCompareCriteria> pair : compareCriteriaMappings())
        {
            if(pair.first == string)
                return pair.second;
        }
        return RulesContext::noCompareModeSet;
    }

    QString fileTypeEntityToString(RulesContext::FileType type) override
    {
        for (QPair<QString,RulesContext::FileType> pair : fileTypeFilterMappings())
        {
            if(pair.second == type)
                return pair.first;
        }

        return QString();
    }

    RulesContext::FileType fileTypeEntityFromString(const QString &string) override
    {
        for (QPair<QString,RulesContext::FileType> pair : fileTypeFilterMappings())
        {
            if(pair.first == string)
                return pair.second;
        }

        return RulesContext::Unresolved;
    }

private:
    const QList<QPair<QString,RulesContext::RuleAction> > actionMappings() override {
        return {
            QPair<QString,RulesContext::RuleAction>(("Move content"),RulesContext::RuleAction::MoveAction),
            QPair<QString,RulesContext::RuleAction>("Delete content",RulesContext::DeleteAction),
            QPair<QString,RulesContext::RuleAction>("Copy content",RulesContext::CopyAction),
            QPair<QString,RulesContext::RuleAction>("Do nothing",RulesContext::NoAction)};
        }

    const QList<QPair<QString,RulesContext::RuleCriteria> > criteriaMappings() override {
        return {
            QPair<QString,RulesContext::RuleCriteria>("Base name",RulesContext::fileBaseMode),
            QPair<QString,RulesContext::RuleCriteria>("File name",RulesContext::filepathMode),
            QPair<QString,RulesContext::RuleCriteria>("File suffix",RulesContext::fileExtensionMode),
            QPair<QString,RulesContext::RuleCriteria>("File size",RulesContext::fileSize),
            QPair<QString,RulesContext::RuleCriteria>("In folder",RulesContext::fileParentMode),
            QPair<QString,RulesContext::RuleCriteria>("Date created",RulesContext::fileCreatedMode),
            QPair<QString,RulesContext::RuleCriteria>("Date edited",RulesContext::fileModifiedMode),
            QPair<QString,RulesContext::RuleCriteria>("No conditions",RulesContext::nonConditionalMode)};
        }

    const QList<QPair<QString,RulesContext::RuleCompareCriteria> > compareCriteriaMappings() override {

        return {
            QPair<QString,RulesContext::RuleCompareCriteria>("Contains",RulesContext::contains),
            QPair<QString,RulesContext::RuleCompareCriteria>("Does not contain",RulesContext::dontMatch),
            QPair<QString,RulesContext::RuleCompareCriteria>("Matching",RulesContext::match),
            QPair<QString,RulesContext::RuleCompareCriteria>("Does not match",RulesContext::dontMatch),
            QPair<QString,RulesContext::RuleCompareCriteria>("Greater than",RulesContext::greaterThan),
            QPair<QString,RulesContext::RuleCompareCriteria>("Greater or equal than",RulesContext::greaterOrEqualThan),
            QPair<QString,RulesContext::RuleCompareCriteria>("Equal",RulesContext::equal),
            QPair<QString,RulesContext::RuleCompareCriteria>("Less or equal than",RulesContext::lesserOrEqualThan),
            QPair<QString,RulesContext::RuleCompareCriteria>("Equal than",RulesContext::lesserThan),
            QPair<QString,RulesContext::RuleCompareCriteria>("Older than",RulesContext::olderThan),
            QPair<QString,RulesContext::RuleCompareCriteria>("Extact date",RulesContext::exactDate),
            QPair<QString,RulesContext::RuleCompareCriteria>("Younger than",RulesContext::youngerThan)};
        }

    const QList<QPair<QString,RulesContext::FileType> > fileTypeFilterMappings() override
    {
        return {
            QPair<QString,RulesContext::FileType>("Files", RulesContext::File),
            QPair<QString,RulesContext::FileType>("Folders", RulesContext::Folder),
            QPair<QString,RulesContext::FileType>("Undetermined", RulesContext::Unresolved)
        };
    };
};

typedef IRuleDefinitions<RulesContext::RuleType,RulesContext::RuleAction,RulesContext::RuleCriteria,RulesContext::RuleCompareCriteria,RulesContext::FileType> IDefinitions;

#endif // RULEDEFINITIONS_H

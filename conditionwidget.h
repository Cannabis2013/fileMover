#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H

#include <QWidget>
#include <qpair.h>
#include <qstring.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <QStackedWidget>
#include <qcheckbox.h>
#include <QTextCodec>
#include <QDateEdit>

#include "genericserviceinjector.h"
#include "rulesmanager.h"



namespace Ui {
class conditionWidget;
}

class conditionWidget : public QWidget, GenericServiceInjector<IDefinitions>
{
    Q_OBJECT

public:
    explicit conditionWidget(QWidget *parent = nullptr);
    ~conditionWidget();

    enum IteratorMode {filesOnly = 0,folderOnly = 1,allEntries = 2, noTypeSet = 3};


private slots:

    void on_modeSelector_currentIndexChanged(int index);
    void on_folderSelector_toggled(bool checked);
    void on_fileSelector_toggled(bool checked);

private:
    // void members..

    // Editrule related..

    void setKeyWords(QString kW);
    void setConditionalFixedSize(QPair<int,QString>fSize, RulesContext::RuleCompareCriteria cMode);
    void setConditionalIntervalSize(QPair<QPair<int,QString>,QPair<int,QString>> iSize);

    void setTypeValues(const int &tMode);
    void setFixedDate(const CustomDate &dateTime);
    void setIntervalDate(QPair<CustomDate,CustomDate> iDate);

    /*
     * General view related..
     * The following methods is called whenever a condition is selected and widgets needs to be updated.
     * When that situation occurs, setMode() is called which calls setCurrentView(QString).
     * Setmode initializes the combobox with the necessary content based on the selected condition.
     * setCurrentView(QString) changes the index of the QStackedWidget and may hide widgets
     * unsuited for the current view.
    */

    void setMode(QString condition);
    void setCurrentView(QString txt);

    // Set the index of QStackWidget prior to the argument.
    void setCurrentView(int index);

    void setCompareView(RulesContext::RuleCompareCriteria compare);

    // General values and other..
    void initDefaultOperators();
    void initDefaultUnits();

    void resetValues();

    // non-void members..
    //  Comparemode
    RulesContext::RuleCompareCriteria currentCompareMode();
    QString currentMode() const {return mainModeSelector->currentText();}


    // Current view index..
    int currentViewIndex() const {return mainModeView->currentIndex();}
    // Filename/filepath related..
    QString keyWordValues() const;
    // Get size values..
    QPair<quint64, QString> fixedSizeValues() const;
    QPair<QPair<quint64,QString>,QPair<quint64,QString>> intervalSizeValues() const;
    // Get Date values..
    CustomDate fixedConditionalDate() const;
    QPair<CustomDate,CustomDate>intervalDates() const;
    // Get type values..
    int typeMode() const;

    // Member variables...
    QCheckBox *folderCheckBox,*fileCheckBox;
    QComboBox *mainModeSelector,
        *fixedSizeUnitSelector,
        *fixedSizeModeSelector,
        *sizeMinIntervalUnitSelector,
        *sizeMaxIntervalUnitSelector,
        *dateOperatorSelector;
    QLineEdit *keyWordSelector;
    QPair<int,int>indexRange;
    QSpinBox *fixedSizeSelector,*minIntervalSizeSelector,*maxIntervalSizeSelector;
    QStackedWidget *mainModeView;
    RulesContext::RuleCriteria currentFileModeRule;
    Ui::conditionWidget *ui;

    friend class AbstractRuleDialog;
    friend class EditRuleDialog;
    friend class AddRuleDialog;
};

#endif // CONDITIONWIDGET_H

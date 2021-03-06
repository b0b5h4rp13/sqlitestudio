#ifndef MULTIEDITORDATETIME_H
#define MULTIEDITORDATETIME_H

#include "multieditorwidget.h"
#include "multieditorwidgetplugin.h"
#include "plugins/builtinplugin.h"
#include <QStringList>
#include <QDateTime>

class QCalendarWidget;
class QDateTimeEdit;
class QLabel;

class GUI_API_EXPORT MultiEditorDateTime : public MultiEditorWidget
{
        Q_OBJECT
    public:
        explicit MultiEditorDateTime(QWidget *parent = 0);

        static void staticInit();

        void setValue(const QVariant& value);
        QVariant getValue();
        bool needsValueUpdate();

        QList<QWidget*> getNoScrollWidgets();

        bool getReadOnly() const;
        void setReadOnly(bool value);
        void focusThisWidget();

    protected:
        void updateCalendarDisplay();
        void setDisplayFormat(const QString& format);

        virtual QStringList getParsingFormats();

        QDateTimeEdit* dateTimeEdit = nullptr;
        bool showCalendars = true;

    private:
        enum FormatType
        {
            STRING,
            JULIAN_DAY,
            UNIXTIME,
            OTHER
        };

        void updateReadOnlyDisplay();
        QDateTime fromString(const QString& value);

        static QStringList formats;

        QLabel* dateTimeLabel = nullptr;
        QCalendarWidget* calendar = nullptr;
        QString originalValueFormat;
        FormatType formatType;
        bool updatingCalendar = false;
        bool readOnly = false;

    private slots:
        void calendarDateChanged();
        void dateChanged(const QDate& date);
        void timeChanged(const QTime& time);
};

class GUI_API_EXPORT MultiEditorDateTimePlugin : public BuiltInPlugin, public MultiEditorWidgetPlugin
{
    Q_OBJECT

    SQLITESTUDIO_PLUGIN_AUTHOR("sqlitestudio.pl")
    SQLITESTUDIO_PLUGIN_DESC("Date and time data editor.")
    SQLITESTUDIO_PLUGIN_TITLE("Date and time")
    SQLITESTUDIO_PLUGIN_VERSION(10000)

    public:
        MultiEditorWidget* getInstance();
        bool validFor(const DataType& dataType);
        int getPriority(const DataType& dataType);
        QString getTabLabel();
};

#endif // MULTIEDITORDATETIME_H

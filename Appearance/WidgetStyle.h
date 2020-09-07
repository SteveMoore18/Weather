#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include <QObject>
#include <QFile>

class WidgetStyle
{

public:
    enum WidgetName {
        BUTTON,
        LABEL,
        LINEEDIT
    };

    WidgetStyle();

    QString getStyle(const WidgetName & value);

private:

};

#endif // WIDGETSTYLE_H

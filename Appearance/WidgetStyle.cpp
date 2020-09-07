#include "WidgetStyle.h"

WidgetStyle::WidgetStyle()
{

}

QString WidgetStyle::getStyle(const WidgetName & value)
{

    QFile cssFile;
    QString fileName;
    QString cssText;

    switch (value) {

    case WidgetName::BUTTON:
        fileName = ":/css/CSS/ButtonStyle.css";
        break;

    case WidgetName::LABEL:
        fileName = ":/css/CSS/Label.css";
        break;

    case WidgetName::LINEEDIT:
        fileName = ":/css/CSS/LineEditStyle.css";
        break;

    default:
        cssFile.close();
        return "";

    }

    if (fileName == "")
        return "";

    cssFile.setFileName(fileName);
    if (cssFile.open(QIODevice::ReadOnly)) {
        cssText = cssFile.readAll();
    }

    cssFile.close();

    return cssText;
}

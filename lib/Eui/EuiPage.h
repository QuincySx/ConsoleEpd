#ifndef _EUI_PAGE_H_
#define _EUI_PAGE_H_

#include "EuiWidgets.h"

class EuiPage {
private:
    GxEPD2_GFX &canvas;
    std::shared_ptr<EuiLayout> pageLayout;

public:
    EuiPage() = default;

    EuiPage(GxEPD2_GFX &canvas) : canvas(canvas) {
        pageLayout = std::make_shared<EuiLayout>(
                Measure::makeMeasureSpec(canvas.width(), Measure::EXACTLY),
                Measure::makeMeasureSpec(canvas.height(), Measure::EXACTLY), Vertical);
    }

    virtual ~EuiPage() = default;

    void setPadding(Area padding);

    void setMargin(Area margin);

    void setSpace(uint16_t space);

    void setAlign(Align align);

    void setAxis(Axis axis);

    void setBgColor(uint16_t bgColor);

    void setBgRadius(uint16_t radius);

    void setBgFill(bool bgFill);

    void addWidget(EuiWidget widget);

    virtual void display(bool partialUpdate);

    virtual void display() {
        display(false);
    }
};

#endif
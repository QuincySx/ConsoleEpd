#ifndef _EUI_WIDGETS_H_
#define _EUI_WIDGETS_H_

#include <vector>
#include <memory>

#include "GxEPD2_GFX.h"
#include "gfxfont.h"
#include "Fonts/FreeSans24pt7b.h"
#include "Fonts/FreeSans18pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSans9pt7b.h"
#include "Fonts/FreeSansBold24pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/FreeSansBold9pt7b.h"

#include "MeasureSpec.hpp"

struct Area {
    uint16_t left;
    uint16_t top;
    uint16_t right;
    uint16_t bottom;

    Area() : left(0), top(0), right(0), bottom(0) {}

    Area(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) : left(left), top(top), right(right),
                                                                         bottom(bottom) {}

    Area(uint16_t x, uint16_t y) : left(x), top(y), right(x), bottom(y) {}
};

class EuiWidget {
protected:
    int16_t eid{0};

    MEASURE_SPEC_CLASS widthSpec;
    MEASURE_SPEC_CLASS heightSpec;

    int16_t absX;
    int16_t absY;

    uint16_t bgColor;
    uint16_t bgRadius;
    bool bgFill;

    Area padding;
    Area margin;

public:
    EuiWidget(MEASURE_SPEC_CLASS widthSpec, MEASURE_SPEC_CLASS heightSpec, Area padding, Area margin)
            : widthSpec(widthSpec), heightSpec(heightSpec), bgColor(GxEPD_WHITE), bgRadius(0), bgFill(true),
              padding(padding), margin(margin) {}

    EuiWidget(MEASURE_SPEC_CLASS widthSpec, MEASURE_SPEC_CLASS heightSpec)
            : EuiWidget(widthSpec, heightSpec, Area(0, 0, 0, 0), Area(0, 0)) {}

    EuiWidget() : EuiWidget(0, 0, Area(0, 0, 0, 0), Area(0, 0)) {}

    virtual ~EuiWidget() = default;

    void setEid(int16_t eid) {
        this->eid = eid;
    }

    int16_t getEid() {
        return eid;
    }

    void setWidth(uint16_t width) {
        setWidth(width, Measure::AT_MOST);
    }

    void setHeight(uint16_t height) {
        setHeight(height, Measure::AT_MOST);
    }

    void setWidth(uint16_t width, Measure::MeasureMode widthMode) {
        this->widthSpec = Measure::makeMeasureSpec(width, widthMode);
    }

    void setHeight(uint16_t height, Measure::MeasureMode heightMode) {
        this->heightSpec = Measure::makeMeasureSpec(height, heightMode);
    }

    int16_t getWidth() {
        return Measure::getSize(widthSpec);
    }

    int16_t getHeight() {
        return Measure::getSize(heightSpec);
    }

    int16_t getContentWidth() {
        return getWidth() - padding.left - padding.right;
    }

    int16_t getContentHeight() {
        return getHeight() - padding.top - padding.bottom;
    }

    Measure::MeasureMode getWidthMode() {
        return Measure::getMode(widthSpec);
    }

    Measure::MeasureMode getHeightMode() {
        return Measure::getMode(heightSpec);
    }

    void setAbsX(int16_t x) {
        this->absX = x;
    }

    void setAbsY(int16_t y) {
        this->absY = y;
    }

    int16_t getAbsX() {
        return absX;
    }

    int16_t getAbsY() {
        return absY;
    }

    void setPadding(Area padding) {
        this->padding = padding;
    }

    void setMargin(Area margin) {
        this->margin = margin;
    }

    Area getPadding() {
        return padding;
    }

    Area getMargin() {
        return margin;
    }

    void setBgColor(uint16_t bgColor) {
        this->bgColor = bgColor;
    }

    void setBgRadius(uint16_t radius) {
        this->bgRadius = radius;
    }

    /**
     * @brief Set the Bg Fill widget area. default is true
     *
     * @param bgFill
     */
    void setBgFill(bool bgFill) {
        this->bgFill = bgFill;
    }

    virtual void
    measure(GxEPD2_GFX &display, MEASURE_SPEC_CLASS parentContentWidthSpec, MEASURE_SPEC_CLASS parentContentHeightSpec);

    virtual void
    layout(GxEPD2_GFX &display, int16_t parentAbsX, int16_t parentAbsY, MEASURE_SPEC_CLASS parentContentWidth,
           MEASURE_SPEC_CLASS parentContentHeight);

    virtual void draw(GxEPD2_GFX &display, bool partialUpdate);

    virtual void draw(GxEPD2_GFX &display) {
        draw(display, false);
    };
};

enum Align {
    ALIGN_START,
    ALIGN_END,
    ALIGN_CENTER,
    ALIGN_SPACE_BETWEEN,
};

enum Axis {
    Horizontal,
    Vertical
};

class EuiLayout : public EuiWidget {
protected:
    std::vector<std::shared_ptr<EuiWidget>> children;
    uint16_t space;
    Axis axis{Horizontal};
    Align align{ALIGN_START};

public:
    EuiLayout() = default;

    ~EuiLayout() override = default;

    EuiLayout(MEASURE_SPEC_CLASS width, MEASURE_SPEC_CLASS height, uint16_t space,
              Area padding, Area margin, Axis axis)
            : EuiWidget(width, height, padding, margin), space(space), axis(axis) {}

    EuiLayout(MEASURE_SPEC_CLASS width, MEASURE_SPEC_CLASS height, uint16_t space, Axis axis)
            : EuiLayout(width, height, space, Area(0, 0), Area(0, 0), axis) {}

    EuiLayout(MEASURE_SPEC_CLASS width, MEASURE_SPEC_CLASS height, Axis axis)
            : EuiLayout(width, height, 0, Area(0, 0), Area(0, 0), axis) {}

    EuiLayout(MEASURE_SPEC_CLASS width, MEASURE_SPEC_CLASS height)
            : EuiLayout(width, height, 0, Area(0, 0), Area(0, 0), Horizontal) {}


    void setAlign(Align align) {
        this->align = align;
    }

    void setAxis(Axis axis) {
        this->axis = axis;
    }

    void setSpace(uint16_t space) {
        this->space = space;
    }

    Align getAlign() {
        return align;
    }

    Axis getAxis() {
        return axis;
    }

    std::vector<std::shared_ptr<EuiWidget>> getChildren() {
        return children;
    }

    void addWidget(EuiWidget widget);

    virtual void
    measure(GxEPD2_GFX &display, MEASURE_SPEC_CLASS parentContentWidthSpec, MEASURE_SPEC_CLASS parentContentHeightSpec);

    virtual void
    layout(GxEPD2_GFX &display, int16_t parentAbsX, int16_t parentAbsY, MEASURE_SPEC_CLASS parentContentWidthSpec,
           MEASURE_SPEC_CLASS parentContentHeightSpec);

    virtual void draw(GxEPD2_GFX &display, bool partialUpdate);

    virtual void draw(GxEPD2_GFX &display) {
        draw(display, false);
    };
};

class EuiWidgetText : public EuiWidget {
private:
    const char *content;
    const GFXfont *font;
    uint16_t textColor;

    uint16_t textDrawX;
    uint16_t textDrawY;

public:
    EuiWidgetText(const char *content, const GFXfont *font, uint16_t textColor)
            : EuiWidget(0, 0, Area(0, 0), Area(2, 2)), content(content), font(font),
              textColor(textColor) {}

    EuiWidgetText(const char *content, const GFXfont *font) : EuiWidgetText(content, font, GxEPD_BLACK) {}

    EuiWidgetText(const char *content) : EuiWidgetText(content, &FreeSans18pt7b, GxEPD_BLACK) {}

    EuiWidgetText() = default;

    virtual ~EuiWidgetText() override = default;

    void setContent(const char *content);

    void setFont(const GFXfont *font);

    void setTextColor(uint16_t textColor);

    virtual void measure(GxEPD2_GFX &display);

    virtual void draw(GxEPD2_GFX &display, bool partialUpdate);

    virtual void draw(GxEPD2_GFX &display) {
        draw(display, false);
    };
};

class EuiWidgetImage : public EuiWidget {
private:
    uint16_t *image;
    uint16_t imageWidth;
    uint16_t imageHeight;

public:
    EuiWidgetImage() {}

    virtual ~EuiWidgetImage() override = default;
};

#endif
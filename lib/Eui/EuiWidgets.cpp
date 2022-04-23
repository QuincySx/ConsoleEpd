#include "EuiWidgets.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

// ==== **** EuiWidget **** ====
void EuiWidget::draw(GxEPD2_GFX &display, bool partialUpdate)
{
    Serial.printf("EuiWidget draw id:%d\n", eid);
    auto width = Measure::getSize(widthSpec);
    auto height = Measure::getSize(heightSpec);

    if (bgFill && bgRadius == 0)
    {
        display.fillRect(absX + margin.left, absY + margin.top, width, height, bgColor);
    }
    else if (bgFill && bgRadius > 0)
    {
        display.fillRoundRect(absX + margin.left, absY + margin.top, width, height, bgRadius, bgColor);
    }
    else if (!bgFill && bgRadius == 0)
    {
        display.drawRect(absX + margin.left, absY + margin.top, width, height, bgColor);
    }
    else if (!bgFill && bgRadius > 0)
    {
        display.drawRoundRect(absX + margin.left, absY + margin.top, width, height, bgRadius, bgColor);
    }
}

void EuiWidget::layout(GxEPD2_GFX &display, int16_t parentAbsX, int16_t parentAbsY, MEASURE_SPEC_CLASS parentContentWidth,
                       MEASURE_SPEC_CLASS parentContentHeight)
{
    Serial.printf("EuiWidget layout id:%d\n", eid);
}

void EuiWidget::measure(GxEPD2_GFX &display, MEASURE_SPEC_CLASS parentContentWidthSpec,
                        MEASURE_SPEC_CLASS parentContentHeightSpec)
{
    Serial.printf("EuiWidget measure id:%d\n", eid);
}

// ==== **** EuiLayout **** ====
void EuiLayout::addWidget(EuiWidget widget)
{
    children.push_back(std::make_shared<EuiWidget>(widget));
}

void EuiLayout::measure(GxEPD2_GFX &display, MEASURE_SPEC_CLASS parentContentWidthSpec,
                        MEASURE_SPEC_CLASS parentContentHeightSpec)
{
    uint16_t parentWidth = Measure::getSize(parentContentWidthSpec);
    uint16_t parentHeight = Measure::getSize(parentContentHeightSpec);
    Measure::MeasureMode parentWidthMode = Measure::getMode(parentContentWidthSpec);
    Measure::MeasureMode parentHeightMode = Measure::getMode(parentContentHeightSpec);

    // measure children
    uint16_t wrapWidth = 0;
    uint16_t wrapHeight = 0;

    wrapWidth += padding.left + padding.right;
    wrapHeight += padding.top + padding.bottom;

    Serial.printf("EuiLayout measure id:%d wrapWidth:%d, wrapHeight:%d\n", eid, wrapWidth, wrapHeight);

    for (auto& widget : children)
    {
        Serial.printf("Begin EuiLayout measure child id:%d\n", widget->getEid());
        // widget->measure(display, parentContentWidthSpec, parentContentHeightSpec);
        if (axis == Horizontal)
        {
            wrapWidth += widget->getWidth() + widget->getMargin().left + widget->getMargin().right + space;
            wrapHeight = max(wrapHeight, widget->getHeight() + widget->getMargin().top + widget->getMargin().bottom);
        }
        else
        {
            wrapWidth = max(wrapWidth, widget->getWidth() + widget->getMargin().left + widget->getMargin().right);
            wrapHeight += widget->getHeight() + widget->getMargin().top + widget->getMargin().bottom + space;
        }
        Serial.printf("End EuiLayout measure child id:%d wrapWidth:%d, wrapHeight:%d\n", widget->getEid(), wrapWidth, wrapHeight);
    }
    if (children.size() > 0)
    {
        if (axis == Horizontal)
        {
            wrapWidth -= space;
        }
        else
        {
            wrapHeight -= space;
        }
    }

    Serial.printf("EuiLayout measure Mode id:%d\n", eid);
    Measure::MeasureMode widthMode = Measure::getMode(widthSpec);
    if (widthMode == Measure::AT_MOST || widthMode == Measure::UNSPECIFIED)
    {
        this->widthSpec = Measure::makeMeasureSpec(wrapWidth, widthMode);
    }
    else if (widthMode == Measure::FILL)
    {
        this->widthSpec = Measure::makeMeasureSpec(parentWidthMode - margin.left - margin.right, widthMode);
    }

    Measure::MeasureMode heightMode = Measure::getMode(heightSpec);
    if (heightMode == Measure::AT_MOST || heightMode == Measure::UNSPECIFIED)
    {
        this->heightSpec = Measure::makeMeasureSpec(wrapHeight, heightMode);
    }
    else if (heightMode == Measure::FILL)
    {
        this->heightSpec = Measure::makeMeasureSpec(parentHeight - margin.top - margin.bottom, heightMode);
    }
    Serial.printf("EuiWidget eid:%d measure, width:%d, height:%d, parentContentWidth: %d, parentContentHeight: %d\n",
                  eid, Measure::getSize(widthSpec), Measure::getSize(heightSpec), parentWidth, parentHeight);
    Serial.printf(
        "EuiWidget eid:%d measure, widthMode:%d, heightMode:%d, parentContentWidthMode: %d, parentContentHeightMode: %d\n",
        eid, Measure::getMode(widthSpec), Measure::getMode(heightSpec), parentWidthMode, parentHeightMode);
}

void EuiLayout::layout(GxEPD2_GFX &display, int16_t parentAbsX, int16_t parentAbsY,
                       MEASURE_SPEC_CLASS parentContentWidthSpec,
                       MEASURE_SPEC_CLASS parentContentHeightSpec)
{
    uint16_t parentContentWidth = Measure::getSize(parentContentWidthSpec);
    uint16_t parentContentHeight = Measure::getSize(parentContentHeightSpec);
    Measure::MeasureMode parentWidthMode = Measure::getMode(parentContentWidthSpec);
    Measure::MeasureMode parentHeightMode = Measure::getMode(parentContentHeightSpec);

    // layout children
    this->absX = parentAbsX + margin.left;
    this->absY = parentAbsY + margin.top;

    Serial.printf("EuiWidget eid:%d layout, absX:%d, absY:%d\n", eid, absX, absY);

    if (axis == Horizontal)
    {
        if (align == ALIGN_CENTER)
        {
            int16_t unusedWidth =
                parentContentWidth - padding.left - padding.right - Measure::getSize(widthSpec) - margin.left -
                margin.right;
            int16_t eachUnusedWidth = unusedWidth / (children.size() + 1);
            int16_t offsetX = absX + margin.left + eachUnusedWidth;
            for (auto widget : children)
            {
                widget->setAbsX(offsetX);
                offsetX += widget->getWidth() + widget->getMargin().left + widget->getMargin().right + space +
                           eachUnusedWidth;
            }
        }
        else if (align == ALIGN_END)
        {
            int16_t offsetX = absX + parentContentWidth - padding.right - margin.right;

            for (auto widget : children)
            {
                offsetX -= widget->getWidth() + widget->getMargin().right + widget->getMargin().left;
                widget->setAbsX(offsetX);
                offsetX -= space;
            }
        }
        else if (align == ALIGN_SPACE_BETWEEN)
        {
            int16_t unusedWidth =
                parentContentWidth - padding.left - padding.right - Measure::getSize(widthSpec) - margin.left -
                margin.right;
            int16_t eachUnusedWidth = 0;
            if (children.size() > 1)
            {
                eachUnusedWidth = unusedWidth / (children.size() - 1);
            }

            int16_t offsetX = absX + margin.left;
            for (auto widget : children)
            {
                widget->setAbsX(offsetX);
                offsetX += widget->getWidth() + widget->getMargin().left + widget->getMargin().right + space +
                           eachUnusedWidth;
            }
        }
    }
    else
    {
        if (align == ALIGN_CENTER)
        {
            int16_t unusedHeight =
                parentContentHeight - padding.top - padding.bottom - Measure::getSize(heightSpec) - margin.top -
                margin.bottom;
            int16_t eachUnusedHeight = unusedHeight / (children.size() + 1);
            int16_t offsetY = absY + margin.top + eachUnusedHeight;
            for (auto widget : children)
            {
                widget->setAbsY(offsetY);
                offsetY += widget->getHeight() + widget->getMargin().top + widget->getMargin().bottom + space +
                           eachUnusedHeight;
            }
        }
        else if (align == ALIGN_END)
        {
            int16_t offsetY = absY + parentContentHeight - padding.bottom - margin.bottom;
            Serial.printf("offsetY: %d, parentContentHeight: %d\n", offsetY, parentContentHeight);
            for (auto widget : children)
            {
                offsetY -= widget->getHeight() + widget->getMargin().top + widget->getMargin().bottom;
                Serial.printf("offsetY: %d\n", offsetY);
                widget->setAbsY(offsetY);
                offsetY -= space;
            }
        }
        else if (align == ALIGN_SPACE_BETWEEN)
        {
            int16_t unusedHeight =
                parentContentHeight - padding.top - padding.bottom - Measure::getSize(heightSpec) - margin.top -
                margin.bottom;
            int16_t eachUnusedHeight = 0;
            if (children.size() > 1)
            {
                eachUnusedHeight = unusedHeight / (children.size() - 1);
            }

            int16_t offsetY = absY + margin.top;
            for (auto widget : children)
            {
                widget->setAbsY(offsetY);
                offsetY += widget->getHeight() + widget->getMargin().top + widget->getMargin().bottom + space +
                           eachUnusedHeight;
            }
        }
    }
}

void EuiLayout::draw(GxEPD2_GFX &display, bool partialUpdate)
{
    // draw background
    Serial.printf("EuiLayout draw background eid:%d\n", eid);
    EuiWidget::draw(display, partialUpdate);

    for (auto& widget : children)
    {
        Serial.printf("EuiLayout draw list child id:%d\n", widget->getEid());
    }

    for (auto& widget : children)
    {
        try
        {
            Serial.printf("EuiLayout draw child id:%d\n", widget->getEid());
            widget->draw(display, partialUpdate);
        }
        catch (const std::exception &e)
        {
            Serial.printf("EuiLayout draw eid:%d exception:%s\n", widget->getEid(), e.what());
        }
    }
}

// ==== **** EuiWidgetText **** ====
void EuiWidgetText::setContent(const char *content)
{
    this->content = content;
}

void EuiWidgetText::setFont(const GFXfont *font)
{
    this->font = font;
}

void EuiWidgetText::setTextColor(uint16_t textColor)
{
    this->textColor = textColor;
}

void EuiWidgetText::measure(GxEPD2_GFX &display)
{
    Serial.printf("EuiWidgetText measure\n");
    display.setTextWrap(false);
    display.setFont(font);
    display.setTextColor(textColor);

    int16_t tbx, tby;
    uint16_t tbw, tbh;
    display.getTextBounds(content, 0, 0, &tbx, &tby, &tbw, &tbh);

    this->setWidth(tbw + padding.left + padding.right);
    this->setHeight(tbh + padding.top + padding.bottom);

    this->textDrawX = padding.left + margin.left - tbx;
    this->textDrawY = padding.top + margin.top - tby;

    EuiWidget::measure(display, Measure::makeMeasureSpec(0, Measure::AT_MOST),
                       Measure::makeMeasureSpec(0, Measure::AT_MOST));
}

void EuiWidgetText::draw(GxEPD2_GFX &display, bool partialUpdate)
{
    // draw background
    Serial.printf("EuiWidgetText draw background:%s\n", content);
    EuiWidget::draw(display, partialUpdate);

    Serial.printf("EuiWidgetText draw :%s\n", content);
    display.setTextWrap(false);
    display.setFont(font);
    display.setTextColor(textColor);

    display.setCursor(textDrawX + absX, textDrawY + absY);
    display.println(content);
}

// ==== **** EuiWidgetImage **** ====


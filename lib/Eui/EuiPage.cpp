#include "EuiPage.h"


void EuiPage::setPadding(Area padding) {
    pageLayout->setPadding(padding);
}

void EuiPage::setMargin(Area margin) {
    pageLayout->setMargin(margin);
}

void EuiPage::setSpace(uint16_t space) {
    pageLayout->setSpace(space);
}

void EuiPage::setAlign(Align align) {
    pageLayout->setAlign(align);
}

void EuiPage::setAxis(Axis axis) {
    pageLayout->setAxis(axis);
}

void EuiPage::setBgColor(uint16_t bgColor) {
    pageLayout->setBgColor(bgColor);
}

void EuiPage::setBgRadius(uint16_t radius) {
    pageLayout->setBgRadius(radius);
}

void EuiPage::setBgFill(bool bgFill) {
    pageLayout->setBgFill(bgFill);
}

void EuiPage::addWidget(EuiWidget widget) {
    pageLayout->addWidget(widget);
}

void EuiPage::display(bool partialUpdate) {
    Serial.printf("GxPage draw\n");
    canvas.setFullWindow();
    canvas.setRotation(0);

    MEASURE_SPEC_CLASS widthSpec = Measure::makeMeasureSpec(
            canvas.width() - pageLayout->getMargin().left - pageLayout->getMargin().right, Measure::EXACTLY);
    MEASURE_SPEC_CLASS heightSpec = Measure::makeMeasureSpec(
            canvas.height() - pageLayout->getMargin().top - pageLayout->getMargin().bottom, Measure::EXACTLY);

    pageLayout->setWidth(widthSpec);
    pageLayout->setHeight(heightSpec);

    Serial.printf("GxPage measure\n");
    pageLayout->measure(canvas,
                        widthSpec,
                        heightSpec);

    Serial.printf("GxPage layout\n");

    pageLayout->layout(canvas,
                       pageLayout->getMargin().left,
                       pageLayout->getMargin().top,
                       widthSpec,
                       heightSpec);

    canvas.firstPage();
    do {
        Serial.printf("nextPage draw\n");
        canvas.fillScreen(GxEPD_WHITE);
        pageLayout->draw(canvas, partialUpdate);
        canvas.display(partialUpdate);
    } while (canvas.nextPage());
}

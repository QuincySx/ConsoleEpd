#include <EuiPage.h>

class Test1Page : EuiPage
{
private:

public:
    Test1Page(GxEPD2_GFX &canvas) : EuiPage(canvas)
    {
        EuiWidgetText text1("112233", &FreeSans18pt7b, GxEPD_BLACK);
        text1.setEid(1);
        text1.setPadding(Area(10, 10));
        text1.setMargin(Area(10, 10));
        text1.setBgColor(GxEPD_BLACK);
        text1.setBgFill(false);
        text1.setBgRadius(10);

        EuiWidget space1(Measure::makeMeasureSpec(2, Measure::EXACTLY), Measure::makeMeasureSpec(0, Measure::AT_MOST));
        space1.setBgColor(GxEPD_BLACK);
        space1.setEid(2);

        EuiWidgetText text2("778899", &FreeSans18pt7b, GxEPD_BLACK);
        text2.setEid(3);
        text2.setPadding(Area(10, 10));
        text2.setMargin(Area(10, 10));
        text2.setBgColor(GxEPD_BLACK);
        text2.setBgFill(false);
        text2.setBgRadius(10);

        EuiLayout layout1(Measure::makeMeasureSpec(0, Measure::FILL), Measure::makeMeasureSpec(0, Measure::AT_MOST));
        layout1.setEid(4);
        layout1.setAlign(ALIGN_END);
        layout1.setBgColor(GxEPD_BLACK);
        layout1.setBgFill(false);
        layout1.setBgRadius(20);
        layout1.setSpace(10);

        layout1.addWidget(text1);
        layout1.addWidget(space1);
        layout1.addWidget(text2);
        addWidget(layout1);

        EuiWidgetText text3("Hi, HHH", &FreeSans18pt7b, GxEPD_WHITE);
        text3.setEid(5);
        text3.setPadding(Area(20, 30));
        text3.setMargin(Area(20, 10));
        text3.setBgColor(GxEPD_BLACK);
        text3.setBgRadius(10);

        EuiLayout layout2(Measure::makeMeasureSpec(0, Measure::AT_MOST), Measure::makeMeasureSpec(0, Measure::AT_MOST));
        layout2.setEid(6);
        layout2.setBgColor(GxEPD_BLACK);
        layout2.setBgFill(false);
        layout2.setBgRadius(10);

        layout2.addWidget(text3);
        addWidget(layout2);

        EuiWidget widget1(Measure::makeMeasureSpec(80, Measure::EXACTLY), Measure::makeMeasureSpec(30, Measure::EXACTLY));
        widget1.setEid(7);
        widget1.setBgColor(GxEPD_BLACK);

        EuiLayout layout3(Measure::makeMeasureSpec(0, Measure::AT_MOST), Measure::makeMeasureSpec(0, Measure::AT_MOST));
        layout3.setEid(8);
        layout3.setBgColor(GxEPD_BLACK);
        layout3.setBgFill(false);
        layout3.setBgRadius(10);
        layout3.setPadding(Area(10, 10));
        layout3.setMargin(Area(10, 10));
        layout3.addWidget(widget1);

        EuiLayout layout4(Measure::makeMeasureSpec(0, Measure::AT_MOST), Measure::makeMeasureSpec(0, Measure::AT_MOST));
        layout4.setEid(9);
        layout4.setBgColor(GxEPD_BLACK);
        layout4.setBgFill(false);
        layout4.setBgRadius(10);

        layout4.addWidget(layout3);
        addWidget(layout4);

        setMargin(Area(10, 10));
        setPadding(Area(10, 10));
        // setAlign(ALIGN_SPACE_BETWEEN);
        setAlign(ALIGN_END);
        setSpace(10);

        setBgColor(GxEPD_BLACK);
        setBgFill(false);
        setBgRadius(10);
    };

    void display(){
        EuiPage::display();
    }
};

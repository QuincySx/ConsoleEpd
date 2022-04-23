#include <EuiPage.h>

class Test3Page : EuiPage
{
private:
public:
    Test3Page(GxEPD2_GFX &canvas) : EuiPage(canvas)
    {
        EuiWidgetText text1("112233", &FreeSans18pt7b, GxEPD_BLACK);

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
        setSpace(10);

        setBgColor(GxEPD_BLACK);
        setBgFill(false);
        setBgRadius(10);
    };

    void display()
    {
        EuiPage::display();
    }
};

#include <iomanip>
#include <memory>

#include "gtest/gtest.h"
#include "hmicore/config_reader.h"
#include "hmicore/renderer_gva.h"
#include "hmicore/touch_gva.h"
#include "hmicore/widgets/widget.h"
#include "hmicore/widgets/widget_types.h"
#include "hmicore/widgets/widgets.h"
#include "updater/updater.h"

std::unordered_map<gva::widget::WidgetEnum, std::shared_ptr<gva::WidgetX>> widget_list;

TEST(TestUpdater, Start) {
  gva::Updater updater(1);

  //
  // Setup the required widgets
  //
  gva::RendererGva renderer(640, 480);
  gva::TouchGva touch;

  widget_list[gva::widget::WidgetEnum::KWidgetTypeCompass] =
      std::make_shared<gva::WidgetPlanPositionIndicator>(renderer);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeKeyboard] = std::make_shared<gva::WidgetKeyboard>(renderer);
  widget_list[gva::widget::WidgetEnum::kWidgetTypeDialSpeedometer] =
      std::make_shared<gva::WidgetDriverSpeedometer>(renderer);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeDialRpmFuel] = std::make_shared<gva::WidgetDriverRpmFuel>(renderer);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeAlarmIndicator] =
      std::make_shared<gva::WidgetAlarmIndicator>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeTopLabels] = std::make_shared<gva::WidgetTopLabels>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeBottomLabels] =
      std::make_shared<gva::WidgetBottomLabels>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeLeftLabels] =
      std::make_shared<gva::WidgetSideLabels>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeRightLabels] =
      std::make_shared<gva::WidgetSideLabels>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeRightLabels] =
      std::make_shared<gva::WidgetSideLabels>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeTable] =
      std::make_shared<gva::WidgetTable>(renderer, &touch, gva::ConfigData::GetInstance()->GetThemeBackground());
  widget_list[gva::widget::WidgetEnum::KWidgetTypeTableDynamic] =
      std::make_shared<gva::WidgetTableDynamic>(renderer, &touch, gva::ConfigData::GetInstance()->GetThemeBackground());
  widget_list[gva::widget::WidgetEnum::KWidgetObjectLocalisation] =
      std::make_shared<gva::WidgetObjectLocalisation>(renderer, &touch);
  widget_list[gva::widget::WidgetEnum::KWidgetTypeStatusBar] = std::make_shared<gva::WidgetStatusBar>(renderer, &touch);
  updater.RegisterWidgets(widget_list);
  sleep(2);
  gva::Updater::running_ = false;
}
#include <memory>

#include "gtest/gtest.h"
#include "hmicore/widgets/widget.h"
#include "hmicore/widgets/widget_types.h"
#include "updater/updater.h"

std::unordered_map<gva::widget::WidgetEnum, std::shared_ptr<gva::WidgetX>> widget_list;

TEST(TestUpdater, Start) {
  gva::Updater updater(1);
  updater.RegisterWidgets(widget_list);
}
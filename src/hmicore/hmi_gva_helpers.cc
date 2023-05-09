//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file hmi_gva_helpers.cc
///

#include <filesystem>
#include <sstream>

#include "hmi_gva.h"

namespace gva {

void HmiHelper::TableLicences(WidgetTable *table) {
  table->Reset();
  table->SetVisible(true);

  table->SetX(110);
  table->SetY(71);
  table->SetWidth(420);

  table->AddRow(widget::WeightType::kWeightBold);
  table->AddCell("Software", 80);
  table->AddCell("Licence", 20);

  table->AddRow();
  std::string tmp = "Vivoe Lite";
  table->AddCell(tmp, 80);
  table->AddCell("MIT", 20);

  table->AddRow();
  table->AddCell("RTP Payloader", 80);
  table->AddCell("MIT", 20);

  table->AddRow();
  table->AddCell("OSMScout", 80);
  table->AddCell("LGPL", 20);

  table->AddRow();
  table->AddCell("Open Street Map", 80);
  table->AddCell("ODbL", 20);

  table->AddRow();
  table->AddCell("Cyclone DDS", 80);
  table->AddCell("Eclipse", 20);

  table->AddRow();
  table->AddCell("Protobuf", 80);
  table->AddCell("BSD", 20);
}

void HmiHelper::TableSystem(WidgetTable *table) {
  table->Reset();
  table->SetVisible(true);
  table->SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

  table->SetX(110);
  table->SetY(71);
  table->SetWidth(420);

  table->AddRow(widget::WeightType::kWeightBold);
  table->AddCell("Fuction", 80);
  table->AddCell("Status", 20);

  table->AddRow();
  std::stringstream stream;
  stream << "HMI Version " << kSemVerMajor << "." << kSemVerMinor << "." << kSemVerPatch;
  table->AddCell(stream.str(), 80);
  table->AddCell("Ok", 20);

  table->AddRow();
  table->AddCell("GPS Source, " + ConfigData::GetInstance()->GetGpsDevice(), 80);
  if (std::filesystem::exists(ConfigData::GetInstance()->GetGpsDevice())) {
    table->AddCell("OK", 20);
  } else {
    table->AddCell("Error", 20, Renderer::PackRgb(HMI_RED));
  }

  table->AddRow();
  table->AddCell("CAN Source, " + ConfigData::GetInstance()->GetOdbDevice(), 80);
  if (std::filesystem::exists(ConfigData::GetInstance()->GetOdbDevice())) {
    table->AddCell("OK", 20);
  } else {
    table->AddCell("Error", 20, Renderer::PackRgb(HMI_RED));
  }

  table->AddRow();
  table->AddCell("UK Maps, " + ConfigData::GetInstance()->GetMapPath(), 80);
  if (std::filesystem::exists(ConfigData::GetInstance()->GetMapPath())) {
    table->AddCell("OK", 20);
  } else {
    table->AddCell("Error", 20, Renderer::PackRgb(HMI_RED));
  }

  table->AddRow();
  table->AddCell("Timesource GPS Lock", 80);
  table->AddCell("Off", 20, Renderer::PackRgb(HMI_ORANGE));
}

void HmiHelper::TableAlarms(WidgetTable *table) {
  table->Reset();
  table->SetVisible(true);
  table->SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

  table->SetX(110);
  table->SetY(46);
  table->SetWidth(420);

  table->AddRow(widget::WeightType::kWeightBold);
  table->AddCell("Time", 20);
  table->AddCell("Alarm Text", 50);
  table->AddCell("Cat", 10);
  table->AddCell("Status", 20);
  table->SetCurrentRow(1);

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_RED), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 15:06", 20);
  table->AddCell("Low engine oil pressure", 50);
  table->AddCell("W", 10);
  table->AddCell("RES", 20);

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_RED), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 15:26", 20);
  table->AddCell("Engine over temperature", 50);
  table->AddCell("W", 10);
  table->AddCell("UNACK", 20);

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_RED), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 15:29", 20);
  table->AddCell("Engine over temperature", 50);
  table->AddCell("W", 10);
  table->AddCell("RES", 20);

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_ORANGE), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 14:00", 20);
  table->AddCell("Gun fault", 50);
  table->AddCell("C", 10);
  table->AddCell("RES", 20);

  table->AddRow();
  table->AddCell("15/6 18:16", 20);
  table->AddCell("Air con fault", 50);
  table->AddCell("A", 10);
  table->AddCell("ACK", 20);

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_GREY), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 19:03", 20);
  table->AddCell("Gun barrel over temperature", 50);
  table->AddCell("C", 10);
  table->AddCell("ACK(OVR)", 20, Renderer::PackRgb(HMI_GREY));

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_ORANGE), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 19:04", 20);
  table->AddCell("LRU xx fault", 50);
  table->AddCell("C", 10);
  table->AddCell("ACK", 20);

  table->AddRow();
  table->AddCell("15/6 19:10", 20);
  table->AddCell("SAS Camera 1 (Day) over temperature", 50);
  table->AddCell("A", 10);
  table->AddCell("ACK", 20);

  table->AddRow(Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_ORANGE), Renderer::PackRgb(HMI_WHITE),
                Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal);
  table->AddCell("15/6 19:10", 20);
  table->AddCell("CBRN detected high CO2", 50);
  table->AddCell("C", 10);
  table->AddCell("ACK", 20);

  table->AddRow();
  table->AddCell("Page 1 of 1", 100, widget::CellAlignType::kAlignRight);
}

}  // namespace gva
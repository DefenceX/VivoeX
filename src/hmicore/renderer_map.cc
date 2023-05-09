//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer_map.cc
///

#include "renderer_map.h"

#include <glog/logging.h>
#include <osmscout/Database.h>
#include <osmscoutmap/MapService.h>
#include <osmscoutmapcairo/MapPainterCairo.h>

#include <iomanip>
#include <iostream>

#include "gva.h"
#include "hmicore/config_reader.h"

namespace gva {

rendererMap::rendererMap(std::string_view map, std::string_view style, int width, int height)
    : width_(width), height_(height), map_(map), style_(style) {
  database_ = std::make_shared<osmscout::Database>(databaseParameter_);
  mapService_ = std::make_shared<osmscout::MapService>(database_);

  if (!database_->Open(map_.c_str())) {
    LOG(ERROR) << "Cannot open libosmscout database";
  }

  styleConfig_ = std::make_shared<osmscout::StyleConfig>(database_->GetTypeConfig());

  if (!styleConfig_->Load(style_)) {
    LOG(ERROR) << "Cannot open libosmscout style";
  }

  surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_, height_);
  if (surface_ != nullptr) {
    cairo_ = cairo_create(surface_);
    LOG(INFO) << "Created libosmscout cairo surface";
  } else {
    LOG(ERROR) << "Cannot create libosmscout cairo surface";
  }

  DrawParameter_.SetFontSize(3.0);
  DrawParameter_.SetLabelLineMinCharCount(15);
  DrawParameter_.SetLabelLineMaxCharCount(30);
  DrawParameter_.SetLabelLineFitToArea(true);
  DrawParameter_.SetLabelLineFitToWidth((double)std::min(projection_.GetWidth(), projection_.GetHeight()));
  painter_ = std::make_shared<osmscout::MapPainterCairo>(styleConfig_);
};

rendererMap::~rendererMap() {
  while (cairo_surface_get_reference_count(surface_)) {
    cairo_surface_destroy(surface_);
  };
};

GvaStatusTypes rendererMap::Project(double zoom, double lon, double lat, cairo_surface_t **surface) {
  if (surface_ != nullptr) {
    if (cairo_ != nullptr) {
      printf("%dx%d %f %f \n", width_, height_, lat, lon);
      projection_.Set(osmscout::GeoCoord(lat, lon), osmscout::Magnification(zoom), 96.0, width_, height_);

      mapService_->LookupTiles(projection_, tiles_);
      mapService_->LoadMissingTileData(searchParameter_, *styleConfig_, tiles_);
      mapService_->AddTileDataToMapData(tiles_, data_);

      if (painter_->DrawMap(projection_, DrawParameter_, data_, cairo_)) {
        // Map rendered
      }
    }
  } else {
    return GvaStatusTypes::kGvaError;
  }

  *surface = surface_;
  return GvaStatusTypes::kGvaSuccess;
};

}  // namespace gva

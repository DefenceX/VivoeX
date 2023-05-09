//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer_map.h
///

#ifndef HMICORE_RENDERER_MAP_H_
#define HMICORE_RENDERER_MAP_H_

#include <cairo.h>
#include <osmscout/Database.h>
#include <osmscoutmap/MapService.h>
#include <osmscoutmapcairo/MapPainterCairo.h>

#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "hmicore/gva.h"

namespace gva {

class rendererMap {
 public:
  rendererMap(std::string_view map, std::string_view style, int width, int height);
  ~rendererMap();
  rendererMap &operator=(const rendererMap &a) = delete;
  rendererMap const &operator=(rendererMap &&a) = delete;

  GvaStatusTypes Project(double zoom, double lon, double lat, cairo_surface_t **surface);
  void SetHeight(int height) { height_ = height; }
  void SetWidth(int width) { width_ = width; }

 private:
  int width_;
  int height_;
  std::string map_;
  std::string style_;
  osmscout::MapServiceRef mapService_;
  osmscout::StyleConfigRef styleConfig_;
  osmscout::DatabaseParameter databaseParameter_;
  osmscout::DatabaseRef database_;
  osmscout::MercatorProjection projection_;
  osmscout::MapParameter DrawParameter_;
  osmscout::AreaSearchParameter searchParameter_;
  osmscout::MapData data_;
  std::list<osmscout::TileRef> tiles_;
  std::shared_ptr<osmscout::MapPainterCairo> painter_;
  cairo_surface_t *surface_;
  cairo_t *cairo_;
};

}  // namespace gva

#endif  // HMICORE_RENDERER_MAP_H_

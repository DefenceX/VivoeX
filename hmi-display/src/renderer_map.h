//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the 'Software'), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
///
/// \file renderer_map.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_MAP_H_
#define HMI_DISPLAY_SRC_RENDERER_MAP_H_

#include <cairo.h>
#include <osmscout/Database.h>
#include <osmscoutmap/MapService.h>
#include <osmscoutmapcairo/MapPainterCairo.h>

#include <iostream>
#include <list>
#include <string>

#include "src/gva.h"

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

#endif  // HMI_DISPLAY_SRC_RENDERER_MAP_H_

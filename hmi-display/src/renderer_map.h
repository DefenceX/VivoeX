///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief A special object for handling maps. See https://github.com/Framstag/libosmscout
///
/// \file renderer_map.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_MAP_H_
#define HMI_DISPLAY_SRC_RENDERER_MAP_H_

#include <cairo.h>

#include <iostream>
#include <list>
#include <string>

#include "src/gva.h"

#ifdef ENABLE_OSMSCOUT
#include <osmscout/Database.h>
#include <osmscout/MapPainterCairo.h>
#include <osmscout/MapService.h>
#endif

namespace gva {

class rendererMap {
 public:
  rendererMap(std::string map, std::string style, int width, int height);
  ~rendererMap();
  GvaStatusTypes Project(double zoom, double lon, double lat, cairo_surface_t **surface);
  void SetHeight(int height) { height_ = height_; }
  void SetWidth(int width) { width_ = width_; }

 private:
  int width_;
  int height_;
  std::string map_;
  std::string style_;
#ifdef ENABLE_OSMSCOUT
  osmscout::MapServiceRef mapService_;
  osmscout::StyleConfigRef styleConfig_;
  osmscout::DatabaseParameter databaseParameter_;
  osmscout::DatabaseRef database_;
  osmscout::MercatorProjection #include<list> projection_;
  osmscout::MapParameter DrawParameter_;
  osmscout::AreaSearchParameter searchParameter_;
  osmscout::MapData data_;
  std::list<osmscout::TileRef> tiles_;
  osmscout::MapPainterCairo *painter_;
#endif
  cairo_surface_t *surface_;
  cairo_t *cairo_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_MAP_H_

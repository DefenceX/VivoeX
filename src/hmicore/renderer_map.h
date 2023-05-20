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

/// Class definition of the rendererMap
class rendererMap {
 public:
  ///
  /// \brief Construct a new renderer Map object
  ///
  /// \param map the map file
  /// \param style the style file
  /// \param width the width of the map
  /// \param height the height of the map
  ///
  rendererMap(std::string_view map, std::string_view style, int width, int height);

  ///
  /// \brief Destroy the renderer Map object
  ///
  ///
  ~rendererMap();

  ///
  /// \brief Copy constructor, deleted
  ///
  /// \param a
  /// \return rendererMap&
  ///
  rendererMap &operator=(const rendererMap &a) = delete;

  ///
  /// \brief Move constructor, deleted
  ///
  /// \param a
  /// \return rendererMap const&
  ///
  rendererMap const &operator=(rendererMap &&a) = delete;

  ///
  /// \brief Project the map
  ///
  /// \param zoom the zoom level
  /// \param lon the longitude
  /// \param lat the latitude
  /// \param surface the surface to project onto
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes Project(double zoom, double lon, double lat, cairo_surface_t **surface);

  ///
  /// \brief Set the Height attribute
  ///
  /// \param height the height of the map
  ///
  void SetHeight(int height) { height_ = height; }

  ///
  /// \brief Set the Width attribute
  ///
  /// \param width the width of the map
  ///
  void SetWidth(int width) { width_ = width; }

 private:
  /// The width of the map
  int width_;
  /// The height of the map
  int height_;
  /// The map file
  std::string map_;
  /// The style file
  std::string style_;
  /// The map service
  osmscout::MapServiceRef mapService_;
  /// The style config
  osmscout::StyleConfigRef styleConfig_;
  /// The database parameter
  osmscout::DatabaseParameter databaseParameter_;
  /// The database
  osmscout::DatabaseRef database_;
  /// The projection
  osmscout::MercatorProjection projection_;
  /// The draw parameter
  osmscout::MapParameter DrawParameter_;
  /// The search parameter
  osmscout::AreaSearchParameter searchParameter_;
  /// The data
  osmscout::MapData data_;
  /// The tiles
  std::list<osmscout::TileRef> tiles_;
  /// The painter
  std::shared_ptr<osmscout::MapPainterCairo> painter_;
  /// The cairo surface
  cairo_surface_t *surface_;
  /// The cairo object
  cairo_t *cairo_;
};

}  // namespace gva

#endif  // HMICORE_RENDERER_MAP_H_

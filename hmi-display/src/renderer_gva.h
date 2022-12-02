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
/// \brief The Generic Vehicle Architecture (GVA) renderer for complex objects and widgets.
///
/// \file renderer_gva.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_GVA_H_
#define HMI_DISPLAY_SRC_RENDERER_GVA_H_

#include <memory>
#include <string>
#include <vector>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/renderer_cairo.h"
#include "src/widgets/widget_types.h"

#define MAX_ROWS 50
#define MAX_CELLS 10
#define MAX_TEXT 80

namespace gva {

class RenderBase {
 public:
  RenderBase() = default;
  RenderBase(uint32_t x, uint32_t y) : m_x(x), m_y(y), m_width(0), m_height(0) {}
  RenderBase(uint32_t x, uint32_t y, uint32_t width) : m_x(x), m_y(y), m_width(width), m_height(0) {}
  RenderBase(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
      : m_x(x), m_y(y), m_width(width), m_height(height) {}
  uint32_t GetX() { return m_x; }
  uint32_t GetY() { return m_y; }
  uint32_t GetWidth() { return m_width; }
  uint32_t GetHeight() { return m_height; }

 private:
  uint32_t m_x = 0;
  uint32_t m_y = 0;
  uint32_t m_width = 0;
  uint32_t m_height = 0;
};

class GvaCell {
 public:
  std::string text;
  widget::CellAlignType align;
  widget::GvaColourType foreground;
  widget::GvaColourType background;
  widget::GvaColourType textcolour;
  widget::WeightType weight;
};

class GvaRow : public RenderBase {
 public:
  GvaRow() = default;
  GvaRow(uint32_t x, uint32_t y) : RenderBase(x, y) {}
  uint32_t addCell(GvaCell newcell, uint32_t width);
  GvaCell cell_[MAX_CELLS];
  uint32_t widths_[MAX_CELLS];
  uint32_t cells_ = 0;
};

class GvaTable : public RenderBase {
 public:
  GvaTable(uint32_t x, uint32_t y, uint32_t width) : RenderBase(x, y, width) {}
  uint32_t AddRow(GvaRow newrow) {
    row_[rows_++] = newrow;
    return rows_;
  }
  void SetFontName(std::string name) { fontname_ = name; }
  void SetBorderThickness(uint32_t thickness) { border_ = thickness; }
  uint32_t rows_ = 0;
  uint32_t border_ = gva::ConfigData::GetInstance()->GetThemeTableBorderThickness();
  GvaRow row_[MAX_ROWS];
  std::string fontname_ = "Courier";
};

class Hotspot : public RenderBase {
 public:
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) : RenderBase(x, y), group_id_(groupId), binding_(0) {}
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
      : RenderBase(x, y, width, height), group_id_(groupId), binding_(binding) {}
  GvaFunctionGroupEnum GetGroupId() { return group_id_; }
  uint32_t GetBinding() { return binding_; }

 private:
  GvaFunctionGroupEnum group_id_;  // Group hostpots together
  uint32_t binding_;               // Bind a value or a key to this Hotspot
};

class TouchGva {
 public:
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) {
    hotspots_.push_back(Hotspot(groupId, x, y));
    return GvaStatusTypes::kGvaSuccess;
  }
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height) {
    hotspots_.push_back(Hotspot(groupId, binding, x, y, width, height));
    return GvaStatusTypes::kGvaSuccess;
  }
  GvaStatusTypes AddAbsolute(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t xx,
                             uint32_t yy) {
    hotspots_.push_back(Hotspot(groupId, binding, x, y, xx - x, yy - y));
    return GvaStatusTypes::kGvaSuccess;
  }
  void SetResolution(uint32_t x, uint32_t y) {
    x_ = x;
    y_ = y;
  }
  void Reset() { hotspots_.clear(); }
  bool Check(GvaFunctionGroupEnum groupId, uint32_t *binding, uint32_t x, uint32_t y) {
    // Adjust for resized windows
    x = x / static_cast<float>(Renderer::GetWidth() / static_cast<float>(kMinimumWidth));
    y = y / static_cast<float>(Renderer::GetHeight() / static_cast<float>(kMinimumHeight));
    // Invert now adjusted for size
    y = kMinimumHeight - y;

    for (auto i = hotspots_.begin(); i != hotspots_.end(); ++i) {
      if ((x > i->GetX()) && (x < (i->GetX() + i->GetWidth())) && (y > i->GetY()) &&
          (y < (i->GetY() + i->GetHeight())) && (i->GetGroupId() == groupId)) {
        *binding = i->GetBinding();
        return true;
      }
    }
    return false;
  }

 public:
  uint32_t x_;
  uint32_t y_;
  std::vector<Hotspot> hotspots_;
};

class RendererGva : public RendererCairo {
 public:
  RendererGva() = delete;
  RendererGva(uint32_t width, uint32_t height);
  ~RendererGva() = default;

  ///
  /// \brief Draw all the labels on the screen
  ///
  /// \param text The text to go in the label
  /// \param fontSize The font size
  /// \param x X Position on the screen
  /// \param y Y Position on the screen
  ///
  void DrawLabels(char *text, uint32_t fontSize, uint32_t x, uint32_t y);

  ///
  /// \param x position of the labels, useful for labels on left and right sides of the screen
  /// \param state State of the label
  /// \param toggle Toggle
  /// \param toggleOn Toggle on
  /// \param labels Array of labels to be rendered
  ///
  void DrawFunctionLabels(uint32_t x, const std::array<FunctionKeys::Labels, 6> &labels);

  /// Init
  ///  \brief Draw the labels on the top of the screen
  ///
  ///  \param y The y pixel position
  ///  \param state State of the label
  ///
  void DrawTopLabels(uint32_t y, const std::array<FunctionSelect::Labels, 8> &labels);

  ///
  /// \brief Draw the control labels on the bottom of the screen
  ///
  /// \param y The y pixel position
  /// \param state State of the label
  ///
  void DrawControlLabels(const uint32_t y, const std::array<CommonTaskKeys::Labels, 8> &labels);

  ///
  /// \brief Draw an icon
  ///
  /// \param icon The type of icon to be rendered
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param width Width of the icon
  /// \param height Height of the icon
  ///
  void DrawIcon(widget::IconType icon, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

  ///
  /// \brief Draw a table
  ///
  /// \param table The table values
  ///
  void DrawTable(GvaTable *table);

  ///
  /// \brief Draw the operational mode
  ///
  ///
  void DrawMode();

  ///
  /// \brief Draw keyboard buttons
  ///
  /// \param keytext The button text
  /// \param fontSize The font size to be used
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param size Size in pixels
  ///
  void DrawButton(const std::string keytext, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t size);

  ///
  /// \brief Draw keyboard buttons
  ///
  /// \param keytext The button text
  /// \param fontSize The font size to be used
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param size Size in pixels
  /// \param height Height of button in pixels
  /// \param width Width of button in pixels
  /// \param align Alignment
  ///
  void DrawButton(const std::string keytext, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t height, uint32_t width,
                  widget::CellAlignType align);

  ///
  /// \brief Get the Touch object
  ///
  /// \return TouchGva*
  ///
  TouchGva *GetTouch() { return &touch_; }

 private:
  TouchGva touch_;

 private:
  void SetStateLabel(LabelStates state, ConfigData *config);
  void SetStateText(LabelStates state, ConfigData *config);
  ConfigData *config_ = nullptr;
};

class WidgetBase {
 public:
  explicit WidgetBase(RendererGva &renderer) : renderer_(renderer) {}
  void Draw(uint32_t x, uint32_t y, uint32_t width, uint32_t height, std::string text, uint32_t text_colour);
  uint32_t GetX() { return x_; }
  uint32_t GetY() { return y_; }

  RendererGva &renderer_;

 private:
  uint32_t x_;
  uint32_t y_;
};

class WidgetFunctionKeyToggle : public WidgetBase {
 public:
  explicit WidgetFunctionKeyToggle(RendererGva &renderer) : WidgetBase(renderer) {}
  void Toggle(const std::string &label1, const std::string &label2);
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_GVA_H_

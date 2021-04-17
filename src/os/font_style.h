#ifndef _OS_FONT_STYLE_H
#define _OS_FONT_STYLE_H
#include <cstdint>

namespace os
{
   class FontStyle
   {
   public:
      enum Weight {
         Invisible_Weight     = 0,
         Thin_Weight          = 100,
         ExtraLight_Weight    = 200,
         Light_Weight         = 300,
         Normal_Weight        = 400,
         Medium_Weight        = 500,
         SemiBold_Weight      = 600,
         Bold_Weight          = 700,
         ExtraBold_Weight     = 800,
         Black_Weight         = 900,
         ExtraBlack_Weight    = 1000
      };

      enum Width {
         UltraCondensed_Width    = 1,
         ExtraCondensed_Width    = 2,
         Condensed_Width         = 3,
         SemiCondensed_Width     = 4,
         Normal_Width            = 5,
         SemiExpanded_Width      = 6,
         Expanded_Width          = 7,
         ExtraExpanded_Width     = 8,
         UltraExpanded_Width     = 9
      };

      enum Slant {
         Upright_Slant,
         Italic_Slant,
         Oblique_Slant
      };

      constexpr FontStyle(Weight weight, Width width, Slant slant) :
         m_value((int)weight |
                 (int)width<< 16 |
                 (int)slant  << 24) {}

      constexpr FontStyle() : FontStyle(Normal_Weight,
                                        Normal_Width,
                                        Upright_Slant) {}

      Weight weight() const {
         return (Weight)(m_value & 0xffff);
      }

      Width width() const {
         return (Width)((m_value >> 16) & 0xff);
      }

      Slant slant() const {
         return (Slant)((m_value >> 24) & 0xff);
      }

      static constexpr FontStyle MakeNormal() {
         return FontStyle(Normal_Weight, Normal_Width, Upright_Slant);
      }

      static constexpr FontStyle MakeBold() {
         return FontStyle(Bold_Weight, Normal_Width, Upright_Slant);
      }

      static constexpr FontStyle MakeItalic() {
         return FontStyle(Normal_Weight, Normal_Width, Italic_Slant);
      }

      static constexpr FontStyle MakeBoldItalic() {
         return FontStyle(Bold_Weight, Normal_Width, Italic_Slant);
      }
   private:
      uint32_t m_value;
   };
} // namespace os

#endif
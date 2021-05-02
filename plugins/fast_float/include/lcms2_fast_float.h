//---------------------------------------------------------------------------------
//
//  Little Color Management System, fast floating point extensions
//  Copyright (c) 1998-2020 Marti Maria Saguer, all rights reserved
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------------

#ifndef _LCMS2_FAST_FLOAT_H
#define _LCMS2_FAST_FLOAT_H

#include "lcms2_plugin.h"

#ifndef CMS_USE_CPP_API
#   ifdef __cplusplus
extern "C" {
#   endif
#endif

#define LCMS2_FAST_FLOAT_VERSION   1200

// The one and only plug-in entry point. To install this plugin in your code
// you need to place this in some initialization place:
//
//  cmsPlugin(cmsFastFloatExtensions());
// 

void* cmsFastFloatExtensions(void);


// New encodings that the plug-in implements

#define BIT15_SH(a)           ((a) << 26)
#define T_BIT15(a)            (((a)>>26)&1)
#define DITHER_SH(a)          ((a) << 27)
#define T_DITHER(a)           (((a)>>27)&1)

#define TYPE_GRAY_15           (COLORSPACE_SH(PT_GRAY)|CHANNELS_SH(1)|BYTES_SH(2)|BIT15_SH(1))
#define TYPE_GRAY_15_REV       (COLORSPACE_SH(PT_GRAY)|CHANNELS_SH(1)|BYTES_SH(2)|FLAVOR_SH(1)|BIT15_SH(1))
#define TYPE_GRAY_15_SE        (COLORSPACE_SH(PT_GRAY)|CHANNELS_SH(1)|BYTES_SH(2)|ENDIAN16_SH(1)|BIT15_SH(1))
#define TYPE_GRAYA_15          (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(2)|BIT15_SH(1))
#define TYPE_GRAYA_15_SE       (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(2)|ENDIAN16_SH(1)|BIT15_SH(1))
#define TYPE_GRAYA_15_PLANAR   (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(2)|PLANAR_SH(1)|BIT15_SH(1))

#define TYPE_RGB_15            (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(2)|BIT15_SH(1))
#define TYPE_RGB_15_PLANAR     (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(2)|PLANAR_SH(1)|BIT15_SH(1))
#define TYPE_RGB_15_SE         (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(2)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_BGR_15            (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|BIT15_SH(1))
#define TYPE_BGR_15_PLANAR     (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|PLANAR_SH(1)|BIT15_SH(1))
#define TYPE_BGR_15_SE         (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_RGBA_15           (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|BIT15_SH(1))
#define TYPE_RGBA_15_PLANAR    (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|PLANAR_SH(1)|BIT15_SH(1))
#define TYPE_RGBA_15_SE        (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_ARGB_15           (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|SWAPFIRST_SH(1)|BIT15_SH(1))

#define TYPE_ABGR_15           (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|BIT15_SH(1))
#define TYPE_ABGR_15_PLANAR    (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|PLANAR_SH(1)|BIT15_SH(1))
#define TYPE_ABGR_15_SE        (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_BGRA_15           (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|SWAPFIRST_SH(1)|BIT15_SH(1))
#define TYPE_BGRA_15_SE        (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|ENDIAN16_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1)|BIT15_SH(1))

#define TYPE_CMY_15            (COLORSPACE_SH(PT_CMY)|CHANNELS_SH(3)|BYTES_SH(2)|BIT15_SH(1))
#define TYPE_YMC_15            (COLORSPACE_SH(PT_CMY)|CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1)|BIT15_SH(1))
#define TYPE_CMY_15_PLANAR     (COLORSPACE_SH(PT_CMY)|CHANNELS_SH(3)|BYTES_SH(2)|PLANAR_SH(1)|BIT15_SH(1))
#define TYPE_CMY_15_SE         (COLORSPACE_SH(PT_CMY)|CHANNELS_SH(3)|BYTES_SH(2)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_CMYK_15           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|BIT15_SH(1))
#define TYPE_CMYK_15_REV       (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|FLAVOR_SH(1)|BIT15_SH(1))
#define TYPE_CMYK_15_PLANAR    (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|PLANAR_SH(1)|BIT15_SH(1))
#define TYPE_CMYK_15_SE        (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_KYMC_15           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|DOSWAP_SH(1)|BIT15_SH(1))
#define TYPE_KYMC_15_SE        (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|DOSWAP_SH(1)|ENDIAN16_SH(1)|BIT15_SH(1))

#define TYPE_KCMY_15           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|SWAPFIRST_SH(1)|BIT15_SH(1))
#define TYPE_KCMY_15_REV       (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|FLAVOR_SH(1)|SWAPFIRST_SH(1)|BIT15_SH(1))
#define TYPE_KCMY_15_SE        (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(2)|ENDIAN16_SH(1)|SWAPFIRST_SH(1)|BIT15_SH(1))

#define TYPE_GRAY_8_DITHER     (COLORSPACE_SH(PT_GRAY)|CHANNELS_SH(1)|BYTES_SH(1)|DITHER_SH(1))
#define TYPE_RGB_8_DITHER      (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(1)|DITHER_SH(1))
#define TYPE_RGBA_8_DITHER      (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1)|DITHER_SH(1))
#define TYPE_BGR_8_DITHER      (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1)|DITHER_SH(1))
#define TYPE_ABGR_8_DITHER      (COLORSPACE_SH(PT_RGB)|CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1)|EXTRA_SH(1)|DITHER_SH(1))
#define TYPE_CMYK_8_DITHER     (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(1)|DITHER_SH(1))
#define TYPE_KYMC_8_DITHER     (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(1)|DOSWAP_SH(1)|DITHER_SH(1))


#define TYPE_AGRAY_8           (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|DOSWAP_SH(1)|BYTES_SH(1))
#define TYPE_AGRAY_16          (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|DOSWAP_SH(1)|BYTES_SH(2))
#define TYPE_AGRAY_FLT         (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|DOSWAP_SH(1)|BYTES_SH(4))
#define TYPE_GRAYA_FLT         (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(4))
#define TYPE_AGRAY_DBL         (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|DOSWAP_SH(1)|BYTES_SH(0))

#define TYPE_ACMYK_8           (COLORSPACE_SH(PT_CMYK)|EXTRA_SH(1)|CHANNELS_SH(4)|BYTES_SH(1)|SWAPFIRST_SH(1))
#define TYPE_KYMCA_8           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|EXTRA_SH(1)|BYTES_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1))
#define TYPE_AKYMC_8           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|EXTRA_SH(1)|BYTES_SH(1)|DOSWAP_SH(1))

#define TYPE_CMYKA_16           (COLORSPACE_SH(PT_CMYK)|EXTRA_SH(1)|CHANNELS_SH(4)|BYTES_SH(2))
#define TYPE_ACMYK_16           (COLORSPACE_SH(PT_CMYK)|EXTRA_SH(1)|CHANNELS_SH(4)|BYTES_SH(2)|SWAPFIRST_SH(1))
#define TYPE_KYMCA_16           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|EXTRA_SH(1)|BYTES_SH(2)|DOSWAP_SH(1)|SWAPFIRST_SH(1))
#define TYPE_AKYMC_16           (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|EXTRA_SH(1)|BYTES_SH(2)|DOSWAP_SH(1))


#define TYPE_AGRAY_8_PLANAR    (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(1)|PLANAR_SH(1)|SWAPFIRST_SH(1))
#define TYPE_AGRAY_16_PLANAR   (COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(2)|PLANAR_SH(1)|SWAPFIRST_SH(1))

#define TYPE_GRAYA_FLT_PLANAR  (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(4)|PLANAR_SH(1))
#define TYPE_AGRAY_FLT_PLANAR  (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(4)|PLANAR_SH(1)|SWAPFIRST_SH(1))

#define TYPE_GRAYA_DBL_PLANAR  (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(0)|PLANAR_SH(1))
#define TYPE_AGRAY_DBL_PLANAR  (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(0)|PLANAR_SH(1)|SWAPFIRST_SH(1))

#define TYPE_ARGB_16_PLANAR    (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|SWAPFIRST_SH(1)|PLANAR_SH(1))
#define TYPE_BGRA_16_PLANAR    (COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(2)|SWAPFIRST_SH(1)|DOSWAP_SH(1)|PLANAR_SH(1))

#ifndef CMS_USE_CPP_API
#   ifdef __cplusplus
    }
#   endif
#endif

#endif


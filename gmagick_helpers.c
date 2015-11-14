/*
   +----------------------------------------------------------------------+
   | PHP Version 5 / Gmagick	                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 2009 Vito Chin, Mikko Koppanen                         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Mikko Kopppanen <mkoppanen@php.net>                          |
   |         Vito Chin <vito@php.net>		                          |
   +----------------------------------------------------------------------+
*/

#include "php_gmagick.h"
#include "php_gmagick_macros.h"


/* {{{ void php_gmagick_initialize_constants()
*/
void php_gmagick_initialize_constants()
{
	TSRMLS_FETCH();

	/* Constants defined in php_gmagick.h */
	GMAGICK_REGISTER_CONST_LONG("COLOR_BLACK", GMAGICK_COLOR_BLACK);
	GMAGICK_REGISTER_CONST_LONG("COLOR_BLUE", GMAGICK_COLOR_BLUE);
	GMAGICK_REGISTER_CONST_LONG("COLOR_CYAN", GMAGICK_COLOR_CYAN);
	GMAGICK_REGISTER_CONST_LONG("COLOR_GREEN", GMAGICK_COLOR_GREEN);
	GMAGICK_REGISTER_CONST_LONG("COLOR_RED", GMAGICK_COLOR_RED);
	GMAGICK_REGISTER_CONST_LONG("COLOR_YELLOW", GMAGICK_COLOR_YELLOW);
	GMAGICK_REGISTER_CONST_LONG("COLOR_MAGENTA", GMAGICK_COLOR_MAGENTA);
	GMAGICK_REGISTER_CONST_LONG("COLOR_OPACITY", GMAGICK_COLOR_OPACITY);
	GMAGICK_REGISTER_CONST_LONG("COLOR_ALPHA", GMAGICK_COLOR_ALPHA);
	GMAGICK_REGISTER_CONST_LONG("COLOR_FUZZ", GMAGICK_COLOR_FUZZ);

	/* Returning the version as a constant string */
	GMAGICK_REGISTER_CONST_LONG("GMAGICK_EXTNUM", PHP_GMAGICK_EXTNUM);

	/* GraphicsMagick defined constants */
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_DEFAULT", OverCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_UNDEFINED", UndefinedCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_NO", NoCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_ADD", AddCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_ATOP", AtopCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_BUMPMAP", BumpmapCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_CLEAR", ClearCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COLORIZE", ColorizeCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYBLACK", CopyBlackCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYBLUE", CopyBlueCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPY", CopyCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYCYAN", CopyCyanCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYGREEN", CopyGreenCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYMAGENTA", CopyMagentaCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYOPACITY", CopyOpacityCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYRED", CopyRedCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_COPYYELLOW", CopyYellowCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_DARKEN", DarkenCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_DIFFERENCE", DifferenceCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_DISPLACE", DisplaceCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_DISSOLVE", DissolveCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_HUE", HueCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_IN", InCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_LIGHTEN", LightenCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_LUMINIZE", LuminizeCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_MINUS", MinusCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_MODULATE", ModulateCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_MULTIPLY", MultiplyCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_OUT", OutCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_OVER", OverCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_OVERLAY", OverlayCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_PLUS", PlusCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_REPLACE", ReplaceCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_SATURATE", SaturateCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_SCREEN", ScreenCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_SUBTRACT", SubtractCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_THRESHOLD", ThresholdCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("COMPOSITE_XOR", XorCompositeOp);
	GMAGICK_REGISTER_CONST_LONG("MONTAGEMODE_FRAME", FrameMode);
	GMAGICK_REGISTER_CONST_LONG("MONTAGEMODE_UNFRAME", UnframeMode);
	GMAGICK_REGISTER_CONST_LONG("MONTAGEMODE_CONCATENATE", ConcatenateMode);
	GMAGICK_REGISTER_CONST_LONG("STYLE_NORMAL", NormalStyle );
	GMAGICK_REGISTER_CONST_LONG("STYLE_ITALIC", ItalicStyle );
	GMAGICK_REGISTER_CONST_LONG("STYLE_OBLIQUE", ObliqueStyle );
	GMAGICK_REGISTER_CONST_LONG("STYLE_ANY", AnyStyle );
	GMAGICK_REGISTER_CONST_LONG("FILTER_UNDEFINED", UndefinedFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_POINT", PointFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_BOX", BoxFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_TRIANGLE", TriangleFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_HERMITE", HermiteFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_HANNING", HanningFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_HAMMING", HammingFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_BLACKMAN", BlackmanFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_GAUSSIAN", GaussianFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_QUADRATIC", QuadraticFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_CUBIC", CubicFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_CATROM", CatromFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_MITCHELL", MitchellFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_LANCZOS", LanczosFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_BESSEL", BesselFilter );
	GMAGICK_REGISTER_CONST_LONG("FILTER_SINC", SincFilter );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_UNDEFINED", UndefinedType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_BILEVEL", BilevelType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_GRAYSCALE", GrayscaleType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_GRAYSCALEMATTE", GrayscaleMatteType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_PALETTE",  PaletteType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_PALETTEMATTE", PaletteMatteType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_TRUECOLOR", TrueColorType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_TRUECOLORMATTE", TrueColorMatteType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_COLORSEPARATION", ColorSeparationType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_COLORSEPARATIONMATTE", ColorSeparationMatteType );
	GMAGICK_REGISTER_CONST_LONG("IMGTYPE_OPTIMIZE", OptimizeType );
	GMAGICK_REGISTER_CONST_LONG("RESOLUTION_UNDEFINED", UndefinedResolution );
	GMAGICK_REGISTER_CONST_LONG("RESOLUTION_PIXELSPERINCH", PixelsPerInchResolution );
	GMAGICK_REGISTER_CONST_LONG("RESOLUTION_PIXELSPERCENTIMETER", PixelsPerCentimeterResolution);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_UNDEFINED", UndefinedCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_NO", NoCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_BZIP", BZipCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_FAX", FaxCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_GROUP4", Group4Compression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_JPEG", JPEGCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_LOSSLESSJPEG", LosslessJPEGCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_LZW", LZWCompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_RLE", RLECompression);
	GMAGICK_REGISTER_CONST_LONG("COMPRESSION_ZIP", ZipCompression);
	GMAGICK_REGISTER_CONST_LONG("PAINT_POINT", PointMethod);
	GMAGICK_REGISTER_CONST_LONG("PAINT_REPLACE", ReplaceMethod);
	GMAGICK_REGISTER_CONST_LONG("PAINT_FLOODFILL", FloodfillMethod);
	GMAGICK_REGISTER_CONST_LONG("PAINT_FILLTOBORDER", FillToBorderMethod);
	GMAGICK_REGISTER_CONST_LONG("PAINT_RESET", ResetMethod);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_NORTHWEST", NorthWestGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_NORTH", NorthGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_NORTHEAST", NorthEastGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_WEST", WestGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_CENTER", CenterGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_EAST", EastGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_SOUTHWEST", SouthWestGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_SOUTH", SouthGravity);
	GMAGICK_REGISTER_CONST_LONG("GRAVITY_SOUTHEAST", SouthEastGravity);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_NORMAL", NormalStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_ULTRACONDENSED", UltraCondensedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_CONDENSED", CondensedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_SEMICONDENSED", SemiCondensedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_SEMIEXPANDED", SemiExpandedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_EXPANDED", ExpandedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_EXTRAEXPANDED", ExtraExpandedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_ULTRAEXPANDED", UltraExpandedStretch);
	GMAGICK_REGISTER_CONST_LONG("STRETCH_ANY", AnyStretch);
	GMAGICK_REGISTER_CONST_LONG("ALIGN_UNDEFINED", UndefinedAlign);
	GMAGICK_REGISTER_CONST_LONG("ALIGN_LEFT", LeftAlign);
	GMAGICK_REGISTER_CONST_LONG("ALIGN_CENTER", CenterAlign);
	GMAGICK_REGISTER_CONST_LONG("ALIGN_RIGHT",	RightAlign);
	GMAGICK_REGISTER_CONST_LONG("DECORATION_NO", NoDecoration);
	GMAGICK_REGISTER_CONST_LONG("DECORATION_UNDERLINE", UnderlineDecoration);
	GMAGICK_REGISTER_CONST_LONG("DECORATION_OVERLINE", OverlineDecoration);
	GMAGICK_REGISTER_CONST_LONG("DECORATION_LINETROUGH", LineThroughDecoration);
	GMAGICK_REGISTER_CONST_LONG("NOISE_UNIFORM", UniformNoise);
	GMAGICK_REGISTER_CONST_LONG("NOISE_GAUSSIAN", GaussianNoise);
	GMAGICK_REGISTER_CONST_LONG("NOISE_MULTIPLICATIVEGAUSSIAN", MultiplicativeGaussianNoise);
	GMAGICK_REGISTER_CONST_LONG("NOISE_IMPULSE", ImpulseNoise);
	GMAGICK_REGISTER_CONST_LONG("NOISE_LAPLACIAN", LaplacianNoise );
	GMAGICK_REGISTER_CONST_LONG("NOISE_POISSON", PoissonNoise);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_UNDEFINED", UndefinedChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_RED", RedChannel);
#if defined(GrayChannel)
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_GRAY", GrayChannel);
#endif
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_CYAN", CyanChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_GREEN", GreenChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_MAGENTA", MagentaChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_BLUE", BlueChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_YELLOW", YellowChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_OPACITY", OpacityChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_MATTE", MatteChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_BLACK", BlackChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_INDEX", IndexChannel);
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_ALL", AllChannels);
#ifdef DefaultChannels
	GMAGICK_REGISTER_CONST_LONG("CHANNEL_DEFAULT", DefaultChannels);
#endif
	GMAGICK_REGISTER_CONST_LONG("METRIC_UNDEFINED", UndefinedMetric);
	GMAGICK_REGISTER_CONST_LONG("METRIC_MEANABSOLUTEERROR", MeanAbsoluteErrorMetric);
	GMAGICK_REGISTER_CONST_LONG("METRIC_MEANSQUAREERROR", MeanSquaredErrorMetric);
	GMAGICK_REGISTER_CONST_LONG("METRIC_PEAKABSOLUTEERROR", PeakAbsoluteErrorMetric);
	GMAGICK_REGISTER_CONST_LONG("METRIC_PEAKSIGNALTONOISERATIO", PeakSignalToNoiseRatioMetric);
	GMAGICK_REGISTER_CONST_LONG("METRIC_ROOTMEANSQUAREDERROR", RootMeanSquaredErrorMetric);
	GMAGICK_REGISTER_CONST_LONG("PIXEL_CHAR", CharPixel);
	GMAGICK_REGISTER_CONST_LONG("PIXEL_DOUBLE", DoublePixel);
	GMAGICK_REGISTER_CONST_LONG("PIXEL_FLOAT", FloatPixel);
	GMAGICK_REGISTER_CONST_LONG("PIXEL_INTEGER", IntegerPixel);
	GMAGICK_REGISTER_CONST_LONG("PIXEL_LONG", LongPixel);
	GMAGICK_REGISTER_CONST_LONG("PIXEL_SHORT", ShortPixel);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_UNDEFINED", UndefinedColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_RGB", RGBColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_GRAY", GRAYColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_TRANSPARENT", TransparentColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_OHTA", OHTAColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_LAB", LABColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_XYZ", XYZColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_YCBCR", YCbCrColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_YCC", YCCColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_YIQ", YIQColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_YPBPR", YPbPrColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_YUV", YUVColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_CMYK", CMYKColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_SRGB", sRGBColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_HSL", HSLColorspace);
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_HWB", HWBColorspace);
#if defined(Rec601LumaColorspace)
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_REC601LUMA", Rec601LumaColorspace);
#endif
#if defined(Rec709LumaColorspace)
	GMAGICK_REGISTER_CONST_LONG("COLORSPACE_REC709LUMA", Rec709LumaColorspace);
#endif
	GMAGICK_REGISTER_CONST_LONG("VIRTUALPIXELMETHOD_UNDEFINED", UndefinedVirtualPixelMethod);
	GMAGICK_REGISTER_CONST_LONG("VIRTUALPIXELMETHOD_CONSTANT", ConstantVirtualPixelMethod);  /* deprecated */
	GMAGICK_REGISTER_CONST_LONG("VIRTUALPIXELMETHOD_EDGE", EdgeVirtualPixelMethod);
	GMAGICK_REGISTER_CONST_LONG("VIRTUALPIXELMETHOD_MIRROR", MirrorVirtualPixelMethod);
	GMAGICK_REGISTER_CONST_LONG("VIRTUALPIXELMETHOD_TILE", TileVirtualPixelMethod);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_UNDEFINED", UndefinedPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_ROTATE", RotatePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SHEAR", ShearPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_ROLL", RollPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_HUE", HuePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SATURATION", SaturationPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_BRIGHTNESS", BrightnessPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_GAMMA", GammaPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SPIFF", SpiffPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_DULL", DullPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_GRAYSCALE", GrayscalePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_QUANTIZE", QuantizePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_DESPECKLE", DespecklePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_REDUCENOISE", ReduceNoisePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_ADDNOISE", AddNoisePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SHARPEN", SharpenPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_BLUR", BlurPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_THRESHOLD", ThresholdPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_EDGEDETECT", EdgeDetectPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SPREAD", SpreadPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SOLARIZE", SolarizePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SHADE", ShadePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_RAISE", RaisePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SEGMENT", SegmentPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_SWIRL", SwirlPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_IMPLODE", ImplodePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_WAVE", WavePreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_OILPAINT", OilPaintPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_CHARCOALDRAWING", CharcoalDrawingPreview);
	GMAGICK_REGISTER_CONST_LONG("PREVIEW_JPEG", JPEGPreview);
	GMAGICK_REGISTER_CONST_LONG("RENDERINGINTENT_UNDEFINED", UndefinedIntent);
	GMAGICK_REGISTER_CONST_LONG("RENDERINGINTENT_SATURATION", SaturationIntent);
	GMAGICK_REGISTER_CONST_LONG("RENDERINGINTENT_PERCEPTUAL", PerceptualIntent);
	GMAGICK_REGISTER_CONST_LONG("RENDERINGINTENT_ABSOLUTE", AbsoluteIntent);
	GMAGICK_REGISTER_CONST_LONG("RENDERINGINTENT_RELATIVE", RelativeIntent);
	GMAGICK_REGISTER_CONST_LONG("INTERLACE_UNDEFINED", UndefinedInterlace);
	GMAGICK_REGISTER_CONST_LONG("INTERLACE_NO", NoInterlace);
	GMAGICK_REGISTER_CONST_LONG("INTERLACE_LINE", LineInterlace);
	GMAGICK_REGISTER_CONST_LONG("INTERLACE_PLANE", PlaneInterlace);
	GMAGICK_REGISTER_CONST_LONG("INTERLACE_PARTITION", PartitionInterlace);
	GMAGICK_REGISTER_CONST_LONG("FILLRULE_UNDEFINED", UndefinedRule);
	GMAGICK_REGISTER_CONST_LONG("FILLRULE_EVENODD", EvenOddRule);
	GMAGICK_REGISTER_CONST_LONG("FILLRULE_NONZERO", NonZeroRule);
	GMAGICK_REGISTER_CONST_LONG("PATHUNITS_USERSPACE", UserSpace);
	GMAGICK_REGISTER_CONST_LONG("PATHUNITS_USERSPACEONUSE", UserSpaceOnUse);
	GMAGICK_REGISTER_CONST_LONG("PATHUNITS_OBJECTBOUNDINGBOX", ObjectBoundingBox);
	GMAGICK_REGISTER_CONST_LONG("LINECAP_UNDEFINED", UndefinedCap);
	GMAGICK_REGISTER_CONST_LONG("LINECAP_BUTT", ButtCap);
	GMAGICK_REGISTER_CONST_LONG("LINECAP_ROUND", RoundCap);
	GMAGICK_REGISTER_CONST_LONG("LINECAP_SQUARE", SquareCap);
	GMAGICK_REGISTER_CONST_LONG("LINEJOIN_UNDEFINED", UndefinedJoin);
	GMAGICK_REGISTER_CONST_LONG("LINEJOIN_MITER", MiterJoin);
	GMAGICK_REGISTER_CONST_LONG("LINEJOIN_ROUND", RoundJoin);
	GMAGICK_REGISTER_CONST_LONG("LINEJOIN_BEVEL", BevelJoin);
	GMAGICK_REGISTER_CONST_LONG("RESOURCETYPE_UNDEFINED", UndefinedResource);
	GMAGICK_REGISTER_CONST_LONG("RESOURCETYPE_AREA", AreaResource);
	GMAGICK_REGISTER_CONST_LONG("RESOURCETYPE_DISK", DiskResource);
	GMAGICK_REGISTER_CONST_LONG("RESOURCETYPE_FILE", FileResource);
	GMAGICK_REGISTER_CONST_LONG("RESOURCETYPE_MAP", MapResource);
	GMAGICK_REGISTER_CONST_LONG("RESOURCETYPE_MEMORY", MemoryResource);
	GMAGICK_REGISTER_CONST_LONG("DISPOSE_UNDEFINED", UndefinedDispose);
	GMAGICK_REGISTER_CONST_LONG("DISPOSE_NONE", NoneDispose);
	GMAGICK_REGISTER_CONST_LONG("DISPOSE_BACKGROUND", BackgroundDispose);
	GMAGICK_REGISTER_CONST_LONG("DISPOSE_PREVIOUS", PreviousDispose);
#if defined(UndefinedOrientation) && defined(LeftBottomOrientation)
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_UNDEFINED", UndefinedOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_TOPLEFT", TopLeftOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_TOPRIGHT", TopRightOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_BOTTOMRIGHT", BottomRightOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_BOTTOMLEFT", BottomLeftOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_LEFTTOP", LeftTopOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_RIGHTTOP", RightTopOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_RIGHTBOTTOM", RightBottomOrientation);
	GMAGICK_REGISTER_CONST_LONG("ORIENTATION_LEFTBOTTOM", LeftBottomOrientation);
#endif
#if defined(QuantumDepth)
	GMAGICK_REGISTER_CONST_LONG("QUANTUM_DEPTH", QuantumDepth);
#endif

	/* from magick/version.h */
	GMAGICK_REGISTER_CONST_STRING("VERSION_TXT", MagickLibVersionText);
	GMAGICK_REGISTER_CONST_LONG("VERSION_LIB", MagickLibVersion);
	/* from config */
	GMAGICK_REGISTER_CONST_LONG("VERSION_NUM", GMAGICK_LIB_MASK);
}
/* }}} */

/* {{{ void *get_pointinfo_array(zval *coordinate_array, int *num_elements TSRMLS_DC)
*/
void *get_pointinfo_array(zval *coordinate_array, int *num_elements TSRMLS_DC)
{
	PointInfo *coordinates;
	long elements_count, sub_elements_count, i;
	HashTable *coords;
	zval *current, *pz_x, *pz_y;
	HashTable *sub_array;

	*num_elements = 0;
	i = 0;

	coords = HASH_OF(coordinate_array);
	elements_count = zend_hash_num_elements(coords);

	if (elements_count < 1) {
		coordinates = (PointInfo *)NULL;
		return coordinates;
	}

	coordinates = (PointInfo *)emalloc(sizeof(PointInfo) * elements_count);

	ZEND_HASH_FOREACH_VAL(coords, current) {
		/* If its something than array lets error here */
		if(current == NULL || Z_TYPE_P(current) != IS_ARRAY) {
			efree(coordinates);
			coordinates = (PointInfo *)NULL;			
			return coordinates;
		}

		/* Subarray should have two elements. X and Y */
		sub_array = HASH_OF(current);
		sub_elements_count = zend_hash_num_elements(sub_array);

		/* Exactly two elements */
		if (sub_elements_count != 2) {
			efree(coordinates);
			coordinates = (PointInfo *)NULL;
			return coordinates;
		}

		/* Get X */
		pz_x = zend_hash_str_find(sub_array, "x", strlen("x"));
		if(Z_TYPE_P(pz_x) != IS_DOUBLE && Z_TYPE_P(pz_x) != IS_LONG) {
			efree(coordinates);
			coordinates = (PointInfo *)NULL;
			return coordinates;
		}

		/* Get Y */
		pz_y = zend_hash_str_find(sub_array, "y", strlen("y"));
		if(Z_TYPE_P(pz_y) != IS_DOUBLE && Z_TYPE_P(pz_y) != IS_LONG) {
			efree(coordinates);
			coordinates = (PointInfo *)NULL;
			return coordinates;
		}

		/* Assign X and Y */
		if (Z_TYPE_P(pz_x) == IS_LONG) {
			coordinates[i].x = (double)Z_LVAL_P(pz_x);
		} else {
			coordinates[i].x = Z_DVAL_PP(pz_x);
		}

		if (Z_TYPE_P(pz_y) == IS_LONG) {
			coordinates[i].y = (double)Z_LVAL_P(pz_y);
		} else {
			coordinates[i].y = Z_DVAL_P(pz_y);
		}

		i++;
	} ZEND_HASH_FOREACH_END();

	*num_elements = elements_count;

	return coordinates;
}
/* }}} */

/* {{{ check_configured_font(char *font, int font_len TSRMLS_DC)
*/
int check_configured_font(char *font, int font_len TSRMLS_DC)
{
	int retval = 0;
	char **fonts;
	unsigned long num_fonts = 0, i = 0;

	/* Check that user is only able to set a proper font */
	fonts = (char **) MagickQueryFonts("*", &num_fonts);

	for(i = 0 ; i < num_fonts ; i++) {
		/* Let's see if the font is among configured fonts */
		if (strncmp(fonts[i], font, font_len) == 0) {
			retval = 1;
			break;
		}
	}

	GMAGICK_FREE_MEMORY(char **, fonts);
	return retval;
}
/* }}} */

/* {{{ get_double_array_from_zval(zval *param_array, long *num_elements TSRMLS_DC)
*/
double *get_double_array_from_zval(zval *param_array, long *num_elements TSRMLS_DC)
{
	zval *current;
	HashTable *ht;
	double *double_array;
	long elements_count, i;

	*num_elements = 0;
	i = 0;

	ht = HASH_OF(param_array);
	elements_count = zend_hash_num_elements(ht);

	if (elements_count == 0) {
		double_array = (double *)NULL;
		return double_array;
	}

	double_array = (double *)emalloc(sizeof(double) * elements_count);

	ZEND_HASH_FOREACH_VAL(ht, current) {
		if(Z_TYPE_P(current) == IS_LONG) {
			double_array[i] = (double)Z_LVAL_P(current);
		} else if (Z_TYPE_P(current) == IS_DOUBLE) {
			double_array[i] = Z_DVAL_P(current);
		} else {
			efree(double_array);
			double_array = (double *)NULL;
			return double_array;
		}

		i++;
	} ZEND_HASH_FOREACH_END();

	*num_elements = elements_count;
	return double_array;
}

/* {{{ count_occurences_of(char needle, char *haystack TSRMLS_DC)
*/
int count_occurences_of(char needle, char *haystack TSRMLS_DC)
{
	int occurances = 0;

	if (haystack == (char *)NULL) {
		return 0;
	}

	while (*haystack != '\0') {

		if (*(haystack++) == needle) {
			occurances++;
		}
	}
	return occurances;
}

/* {{{ zend_bool crop_thumbnail_image(MagickWand *magick_wand, long desired_width, long desired_height TSRMLS_DC)
*/
zend_bool crop_thumbnail_image(MagickWand *magick_wand, long desired_width, long desired_height TSRMLS_DC)
{
	double ratio_x, ratio_y;
	long crop_x = 0, crop_y = 0, new_width, new_height;

	long orig_width  = MagickGetImageWidth(magick_wand);
	long orig_height = MagickGetImageHeight(magick_wand);

	/* Already at the size, just strip profiles */
	if ((orig_width == desired_width) && (orig_height == desired_height)) {
		if (!MagickStripImage(magick_wand)) {
			return 0;
		}
		return 1;
	}

	ratio_x = (double)desired_width / (double)orig_width; 
	ratio_y = (double)desired_height / (double)orig_height; 

	if (ratio_x > ratio_y) { 
		new_width  = desired_width; 
		new_height = ratio_x * (double)orig_height; 
	} else { 
		new_height = desired_height; 
		new_width  = ratio_y * (double)orig_width; 
	}

	if (MagickResizeImage(magick_wand, new_width, new_height, UndefinedFilter, 0.5) == MagickFalse) {
		return 0;
	}

	/* all done here */
	if ((new_width == desired_width) && (new_height == desired_height)) {
		return 1;
	}

	crop_x = (new_width - desired_width) / 2;
	crop_y = (new_height - desired_height) / 2;

	if (MagickCropImage(magick_wand, desired_width, desired_height, crop_x, crop_y) == MagickFalse) {
		return 0;
	}
	return 1;
}

/** zend_bool php_gmagick_thumbnail_dimensions(MagickWand *magick_wand, zend_bool bestfit, long desired_width, long desired_height, long *new_width, long *new_height)
*/
zend_bool php_gmagick_thumbnail_dimensions(MagickWand *magick_wand, zend_bool bestfit, long desired_width, long desired_height, long *new_width, long *new_height)
{
	long orig_width, orig_height;
	
	orig_width  = MagickGetImageWidth(magick_wand); 
	orig_height = MagickGetImageHeight(magick_wand);
	
	if ((orig_width == desired_width) && (orig_height == desired_height)) { 
		*new_width  = desired_width; 
		*new_height = desired_height;
		return 1;
	}
	
	if (bestfit) { 
		double ratio_x, ratio_y; 
		
		if (desired_width <= 0 || desired_height <= 0) {
			return 0;
		}

		ratio_x = (double)desired_width / (double)orig_width; 
		ratio_y = (double)desired_height / (double)orig_height; 
		
		if (ratio_x < ratio_y) { 
			*new_width  = desired_width; 
			*new_height = ratio_x * (double)orig_height; 
		} else { 
			*new_height = desired_height; 
			*new_width  = ratio_y * (double)orig_width; 
		} 
		
		*new_width  = (*new_width < 1)  ? 1 : *new_width; 
		*new_height = (*new_height < 1) ? 1 : *new_height; 
 
	} else { 
		double ratio; 
		
		if (desired_width <= 0 && desired_height <= 0) { 
			return 0;
		}
		
		if (desired_width <= 0 || desired_height <= 0) {		 
			if (desired_width <= 0) { 
				ratio = (double)orig_height / (double)desired_height; 
				*new_width  = orig_width / ratio;
				*new_height = desired_height;
			} else { 
				ratio = (double)orig_width / (double)desired_width; 
				*new_height = orig_height / ratio;
				*new_width  = desired_width;
			}
		} else {
			*new_width  = desired_width; 
			*new_height = desired_height;
		}
	}
	return 1;
}

/** zend_bool php_gmagick_ensure_not_empty(MagickWand *magick_wand, zend_bool bestfit, long desired_width, long desired_height, long *new_width, long *new_height)
*/
zend_bool php_gmagick_ensure_not_empty(MagickWand *magick_wand)
{
	if (MagickGetNumberImages(magick_wand) == 0) {
	    TSRMLS_FETCH ();
			GMAGICK_THROW_GMAGICK_EXCEPTION_EX(magick_wand, "Can not process empty Gmagick object");   
	    return 0;
	}
	return 1;
}

/** double *php_imagick_zval_to_double_array(zval *param_array, long *num_elements TSRMLS_DC)
*/
double *php_gmagick_zval_to_double_array(zval *param_array, long *num_elements TSRMLS_DC)
{
	zval *current;
	HashTable *ht;
	double *double_array;
	long elements_count, i = 0;

	*num_elements = 0;
	ht = HASH_OF(param_array);
	elements_count = zend_hash_num_elements(ht);

	if (elements_count == 0) {
		return NULL;
	}

	/* Number of elements + 1 for final 0 */
	double_array = (double *)emalloc(sizeof(double) * (elements_count+1));

	ZEND_HASH_FOREACH_VAL(ht, current) {
		double_array[i] = zval_get_double(current);
		i++;
	} ZEND_HASH_FOREACH_END();

	double_array[elements_count] = 0.0;

	return double_array;
}

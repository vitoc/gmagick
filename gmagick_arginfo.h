/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: acb0515dcece6de92a056f9d795e0f168fd9c6da */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Gmagick___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, filename, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick___tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_readimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, filename, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_read arginfo_class_Gmagick_readimage

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_readimagefile, 0, 1, Gmagick, 0)
	ZEND_ARG_INFO(0, filehandle)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, filename, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_writeimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, filename, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, all_frames, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_write arginfo_class_Gmagick_writeimage

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_writeimagefile, 0, 1, Gmagick, 0)
	ZEND_ARG_INFO(0, filehandle)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, format, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getversion, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_annotateimage, 0, 5, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, drawing_wand, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_blurimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sigma, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#if GMAGICK_LIB_MASK >= 1003007
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setcompressionquality, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, quality, IS_LONG, 0)
ZEND_END_ARG_INFO()
#endif

#if GMAGICK_LIB_MASK >= 1005000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimagematte, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()
#endif

#if defined(GMAGICK_HAVE_SET_IMAGE_PAGE)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimagepage, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()
#endif

#if defined(GMAGICK_HAVE_SET_IMAGE_PAGE)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimagepage, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_thumbnailimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fit, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, legacy, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_resizeimage, 0, 4, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, filter, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blur, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fit, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, legacy, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_clear, 0, 0, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_cropimage, 0, 4, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_cropthumbnailimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_coalesceimages arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_compositeimage, 0, 4, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, source, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, COMPOSE, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_addimage, 0, 1, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, source, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_addnoiseimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, noise_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_borderimage, 0, 3, Gmagick, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, color, GmagickPixel, MAY_BE_STRING, NULL)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_thresholdimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, threshold, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channel, IS_LONG, 0, "CHANNEL_DEFAULT")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_charcoalimage arginfo_class_Gmagick_blurimage

#define arginfo_class_Gmagick_chopimage arginfo_class_Gmagick_cropimage

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_commentimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, comment, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_current arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_cyclecolormapimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, displace, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_deconstructimages arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_despeckleimage arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_destroy, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_drawimage, 0, 1, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, drawing_wand, GmagickDraw, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_edgeimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_embossimage arginfo_class_Gmagick_blurimage

#define arginfo_class_Gmagick_enhanceimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_equalizeimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_flipimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_flopimage arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_frameimage, 0, 5, Gmagick, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, color, GmagickPixel, MAY_BE_STRING, NULL)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, inner_bevel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, outer_bevel, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_gammaimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, gamma, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getcopyright arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getfilename arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getimage arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, replace, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_getimagebackgroundcolor, 0, 0, GmagickPixel, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimageblob arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getimagesblob arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getimageblueprimary arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimagebordercolor arginfo_class_Gmagick_getimagebackgroundcolor

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimagechanneldepth, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, channel_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimagecolors, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagecolorspace arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagecompose arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagedelay arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagedepth arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getnumberimages arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagedispose arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimageextrema arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimagefilename arginfo_class_Gmagick___tostring

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimagegamma, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagegreenprimary arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimageheight arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagehistogram arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimageindex arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimageinterlacescheme arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimageiterations arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagemattecolor arginfo_class_Gmagick_getimagebackgroundcolor

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimageprofile, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimageredprimary arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimagerenderingintent arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimageresolution arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimagescene arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagesignature arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getimagetype arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimageunits arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getimagewhitepoint arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getimagewidth arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_getpackagename arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getquantumdepth arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getreleasedate arginfo_class_Gmagick___tostring

#define arginfo_class_Gmagick_getsamplingfactors arginfo_class_Gmagick_getversion

#define arginfo_class_Gmagick_getsize arginfo_class_Gmagick_getversion

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setinterlacescheme, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, interlace_scheme, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_hasnextimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_haspreviousimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_implodeimage arginfo_class_Gmagick_edgeimage

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_labelimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, label, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_levelimage, 0, 3, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, blackPoint, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, gamma, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, whitePoint, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channel, IS_LONG, 0, "Gmagick::CHANNEL_DEFAULT")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_magnifyimage arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_mapimage, 0, 2, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, gmagick, gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, dither, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_medianfilterimage, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_minifyimage arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_modulateimage, 0, 3, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, brightness, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, saturation, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, hue, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_motionblurimage, 0, 3, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sigma, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_newimage, 0, 3, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, background, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, format, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_nextimage arginfo_class_Gmagick_destroy

#define arginfo_class_Gmagick_normalizeimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_oilpaintimage arginfo_class_Gmagick_edgeimage

#define arginfo_class_Gmagick_previousimage arginfo_class_Gmagick_destroy

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_profileimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, profile, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_quantizeimage, 0, 5, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, numColors, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, colorspace, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, treeDepth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dither, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, measureError, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_quantizeimages arginfo_class_Gmagick_quantizeimage

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_queryfontmetrics, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, draw, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_queryfonts, 0, 0, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, pattern, IS_STRING, 0, "\"*\"")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_queryformats arginfo_class_Gmagick_queryfonts

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_radialblurimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channel, IS_LONG, 0, "Gmagick::CHANNEL_DEFAULT")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_raiseimage, 0, 5, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, raise, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_readimageblob, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, imageContents, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, filename, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_reducenoiseimage arginfo_class_Gmagick_edgeimage

#define arginfo_class_Gmagick_removeimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_removeimageprofile arginfo_class_Gmagick_getimageprofile

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_resampleimage, 0, 4, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, xResolution, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, yResolution, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, filter, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blur, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_rollimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_rotateimage, 0, 2, Gmagick, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, background, GmagickPixel, MAY_BE_STRING, NULL)
	ZEND_ARG_TYPE_INFO(0, degrees, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_scaleimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fit, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_separateimagechannel, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, channel, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_setfilename arginfo_class_Gmagick_readimage

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagebackgroundcolor, 0, 1, Gmagick, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, color, GmagickPixel, MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageblueprimary, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_setimagebordercolor arginfo_class_Gmagick_setimagebackgroundcolor

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagechanneldepth, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, channel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagecolorspace, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, colorspace, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagecompose, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, composite, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagecompression arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagecompression, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, compression, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagedelay, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, delay, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagedepth, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagedispose, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, disposeType, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_setimagefilename arginfo_class_Gmagick_readimage

#define arginfo_class_Gmagick_getimageformat arginfo_class_Gmagick___tostring

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageformat, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, imageFormat, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_setimagegamma arginfo_class_Gmagick_gammaimage

#define arginfo_class_Gmagick_setimagegreenprimary arginfo_class_Gmagick_setimageblueprimary

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageindex, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageinterlacescheme, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, interlace, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageiterations, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, iterations, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_setimageprofile arginfo_class_Gmagick_profileimage

#define arginfo_class_Gmagick_setimageredprimary arginfo_class_Gmagick_setimageblueprimary

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagerenderingintent, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, rendering_intent, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageresolution, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, xResolution, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, yResolution, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagescene, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, scene, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimagetype, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, imgType, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setimageunits, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, resolution, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_setimagewhitepoint arginfo_class_Gmagick_setimageblueprimary

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setsamplingfactors, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, factors, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_setsize, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, columns, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rows, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_shearimage, 0, 3, Gmagick, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, background, GmagickPixel, MAY_BE_STRING, NULL)
	ZEND_ARG_TYPE_INFO(0, xShear, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, yShear, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_solarizeimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, threshold, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_spreadimage arginfo_class_Gmagick_edgeimage

#define arginfo_class_Gmagick_stripimage arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_swirlimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, degrees, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_trimimage, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, fuzz, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_blackthresholdimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, threshold, GmagickPixel, MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_whitethresholdimage arginfo_class_Gmagick_blackthresholdimage

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_colordecisionlist, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, color_correction_collection, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_clipimage arginfo_class_Gmagick_destroy

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_clippathimage, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, pathname, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, inside, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_colorfloodfillimage, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, fill)
	ZEND_ARG_TYPE_INFO(0, fuzz, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, bordercolor, GmagickPixel, MAY_BE_STRING, NULL)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_colorizeimage, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, colorize)
	ZEND_ARG_OBJ_TYPE_MASK(0, opacity, GmagickPixel, MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_compareimagechannels, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, reference, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, channel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, metric, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_compareimages, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, reference, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, metric, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_contrastimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, sharpen, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_convolveimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, kernel, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_extentimage, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimageboundingbox, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, fuzz, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimageattribute, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimageattribute, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, attribute, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getimagechannelextrema, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, channel, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagechannelmean arginfo_class_Gmagick_getimagechannelextrema

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_getimagecolormapcolor, 0, 1, GmagickPixel, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimagecolormapcolor, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagegravity arginfo_class_Gmagick_getimagecolors

#if defined(HAVE_GMAGICK_SET_IMAGE_GRAVITY)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimagegravity, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gravity, IS_LONG, 0)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimagemattecolor, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagevirtualpixelmethod arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimagevirtualpixelmethod, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, method, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_haldclutimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, hald, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_mattefloodfillimage, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, fuzz, IS_DOUBLE, 0)
	ZEND_ARG_INFO(0, bordercolor)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_montageimage, 0, 5, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, drawing_wand, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, tile_geometry, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, thumbnail_geometry, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, frame, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_morphimages, 0, 1, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, frames, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_mosaicimages arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_shaveimage, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, columns, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rows, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_steganoimage, 0, 2, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, watermark_wand, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_stereoimage, 0, 1, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, object_wand, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_transformimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, crop, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, geometry, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_waveimage, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, amplitude, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagefuzz arginfo_class_Gmagick_getimagegamma

#define arginfo_class_Gmagick_setimagefuzz arginfo_class_Gmagick_trimimage

#define arginfo_class_Gmagick_getimagesavedtype arginfo_class_Gmagick_getimagecolors

#define arginfo_class_Gmagick_setdepth arginfo_class_Gmagick_setimagedepth

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimageoption, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setimagesavedtype, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setformat, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setresolutionunits, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, resolution_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_getimagegeometry arginfo_class_Gmagick_getversion

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_getresourcelimit, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setresourcelimit, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, limit, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_negateimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gray, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channel, IS_LONG, 0, "CHANNEL_DEFAULT")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_sharpenimage, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sigma, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_textureimage, 0, 1, Gmagick, 0)
	ZEND_ARG_OBJ_INFO(0, texture_wand, Gmagick, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_flattenimages arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_sampleimage, 0, 2, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, cols, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rows, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fit, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, legacy, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_cloneimage arginfo_class_Gmagick_clear

#define arginfo_class_Gmagick_appendimages arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Gmagick_unsharpmaskimage, 0, 4, Gmagick, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sigma, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, amount, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, threshold, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_setresolution, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, x_resolution, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y_resolution, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, amount, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, threshold, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_adaptivethresholdimage, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Gmagick_affinetransformimage, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, drawing_wand, GmagickDraw, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Gmagick_averageimages arginfo_class_Gmagick_clear

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GmagickPixel___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, color, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_class_GmagickPixel_getcolor, 0, 0, MAY_BE_STRING|MAY_BE_ARRAY)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, as_array, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, normalize_array, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickPixel_setcolor, 0, 1, GmagickPixel, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickPixel_getcolorcount arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickPixel_setcolorcount, 0, 1, GmagickPixel, 0)
	ZEND_ARG_TYPE_INFO(0, color_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GmagickPixel_getcolorvalue, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickPixel_setcolorvalue, 0, 2, GmagickPixel, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GmagickPixel_getcolorvaluequantum, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickPixel_setcolorvaluequantum arginfo_class_GmagickPixel_setcolorvalue

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokecolor, 0, 1, GmagickDraw, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, color, GmagickPixel, MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokewidth, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_ellipse, 0, 6, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, ox, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, oy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, start, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, end, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_annotate, 0, 3, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GmagickDraw_affine, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, affine, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_arc, 0, 6, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, sx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ex, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ey, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sd, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ed, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_bezier, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, coordinates, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getfillcolor arginfo_class_Gmagick_getimagebackgroundcolor

#define arginfo_class_GmagickDraw_getfillopacity arginfo_class_Gmagick_getimagegamma

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_class_GmagickDraw_getfont, 0, 0, MAY_BE_STRING|MAY_BE_FALSE)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getfontfamily arginfo_class_GmagickDraw_getfont

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfontfamily, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, font_family, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getfontsize arginfo_class_Gmagick_getimagegamma

#define arginfo_class_GmagickDraw_getfontstyle arginfo_class_Gmagick_getimagecolors

#define arginfo_class_GmagickDraw_getfontweight arginfo_class_Gmagick_getimagecolors

#define arginfo_class_GmagickDraw_getstrokeopacity arginfo_class_Gmagick_getimagegamma

#define arginfo_class_GmagickDraw_getstrokecolor arginfo_class_Gmagick_getimagebackgroundcolor

#define arginfo_class_GmagickDraw_getstrokewidth arginfo_class_Gmagick_getimagegamma

#define arginfo_class_GmagickDraw_gettextdecoration arginfo_class_Gmagick_getimagecolors

#define arginfo_class_GmagickDraw_gettextencoding arginfo_class_GmagickDraw_getfont

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_line, 0, 4, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, sx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ex, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ey, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_point, 0, 2, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_polygon arginfo_class_GmagickDraw_bezier

#define arginfo_class_GmagickDraw_polyline arginfo_class_GmagickDraw_bezier

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_rectangle, 0, 4, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_rotate, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, degrees, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_roundrectangle, 0, 6, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_scale arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_setfillcolor arginfo_class_GmagickDraw_setstrokecolor

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfillopacity, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, fill_opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfont, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, font, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfontsize, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, pointsize, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfontstyle, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, style, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfontweight, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, weight, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokeopacity, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, stroke_opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_settextdecoration, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, decoration, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_settextencoding, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, encoding, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getgravity arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setgravity, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, gravity, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getstrokeantialias arginfo_class_Gmagick_destroy

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokeantialias, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, antialias, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getstrokedashoffset arginfo_class_Gmagick_getimagegamma

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokedashoffset, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getstrokelinecap arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokelinecap, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, linecap, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getstrokelinejoin arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokelinejoin, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, linejoin, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getstrokemiterlimit arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokemiterlimit, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, miterlimit, IS_LONG, 0)
ZEND_END_ARG_INFO()

#if GMAGICK_LIB_MASK >= 1003000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GmagickDraw_getstrokedasharray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()
#endif

#if GMAGICK_LIB_MASK >= 1003000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokedasharray, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, dash_array, IS_ARRAY, 0)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_circle, 0, 4, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, ox, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, oy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, px, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, py, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getclippath arginfo_class_GmagickDraw_getfont

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setclippath, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, clip_mask, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getcliprule arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setcliprule, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, fill_rule, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getclipunits arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setclipunits, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, clip_units, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_color, 0, 3, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, paint_method, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_comment, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, comment, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfillpatternurl, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, fill_url, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getfillrule arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setfillrule, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, fill_rule, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_getfontstretch arginfo_class_Gmagick_getimagecolors

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GmagickDraw_setfontstretch, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, font_stretch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pathclose, 0, 0, GmagickDraw, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pathcurvetoabsolute, 0, 6, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_pathcurvetorelative arginfo_class_GmagickDraw_pathcurvetoabsolute

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pathcurvetoquadraticbezierabsolute, 0, 4, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_pathcurvetoquadraticbezierrelative arginfo_class_GmagickDraw_pathcurvetoquadraticbezierabsolute

#define arginfo_class_GmagickDraw_pathcurvetoquadraticbeziersmoothabsolute arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_pathcurvetoquadraticbeziersmoothrelative arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_pathcurvetosmoothabsolute arginfo_class_GmagickDraw_pathcurvetoquadraticbezierabsolute

#define arginfo_class_GmagickDraw_pathcurvetosmoothrelative arginfo_class_GmagickDraw_pathcurvetoquadraticbezierabsolute

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pathellipticarcabsolute, 0, 7, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x_axis_rotation, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, large_arc_flag, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, sweep_flag, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_pathellipticarcrelative arginfo_class_GmagickDraw_pathellipticarcabsolute

#define arginfo_class_GmagickDraw_pathmovetoabsolute arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_pathmovetorelative arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_pathlinetoabsolute arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_pathlinetorelative arginfo_class_GmagickDraw_point

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pathlinetohorizontalabsolute, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_pathlinetohorizontalrelative arginfo_class_GmagickDraw_pathlinetohorizontalabsolute

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pathlinetoverticalabsolute, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_pathlinetoverticalrelative arginfo_class_GmagickDraw_pathlinetoverticalabsolute

#define arginfo_class_GmagickDraw_pathstart arginfo_class_GmagickDraw_pathclose

#define arginfo_class_GmagickDraw_pathfinish arginfo_class_GmagickDraw_pathclose

#define arginfo_class_GmagickDraw_popclippath arginfo_class_GmagickDraw_pathclose

#define arginfo_class_GmagickDraw_popdefs arginfo_class_GmagickDraw_pathclose

#define arginfo_class_GmagickDraw_pushdefs arginfo_class_GmagickDraw_pathclose

#define arginfo_class_GmagickDraw_poppattern arginfo_class_GmagickDraw_pathclose

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pushpattern, 0, 5, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, pattern_id, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_pushclippath, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, clip_mask_id, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_skewx arginfo_class_GmagickDraw_rotate

#define arginfo_class_GmagickDraw_skewy arginfo_class_GmagickDraw_rotate

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GmagickDraw_setstrokepatternurl, 0, 1, GmagickDraw, 0)
	ZEND_ARG_TYPE_INFO(0, stroke_url, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_gettextantialias arginfo_class_Gmagick_destroy

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GmagickDraw_settextantialias, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, anti_alias, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GmagickDraw_gettextundercolor arginfo_class_Gmagick_getimagebackgroundcolor

#define arginfo_class_GmagickDraw_settextundercolor arginfo_class_GmagickDraw_setstrokecolor

#define arginfo_class_GmagickDraw_translate arginfo_class_GmagickDraw_point

#define arginfo_class_GmagickDraw_setviewbox arginfo_class_GmagickDraw_rectangle

#define arginfo_class_GmagickDraw_popGraphicContext arginfo_class_GmagickDraw_pathclose

#define arginfo_class_GmagickDraw_pushGraphicContext arginfo_class_GmagickDraw_pathclose


ZEND_METHOD(Gmagick, __construct);
ZEND_METHOD(Gmagick, __tostring);
ZEND_METHOD(Gmagick, readimage);
ZEND_METHOD(Gmagick, readimagefile);
ZEND_METHOD(Gmagick, writeimage);
ZEND_METHOD(Gmagick, writeimagefile);
ZEND_METHOD(Gmagick, getversion);
ZEND_METHOD(Gmagick, annotateimage);
ZEND_METHOD(Gmagick, blurimage);
#if GMAGICK_LIB_MASK >= 1003007
ZEND_METHOD(Gmagick, setcompressionquality);
#endif
#if GMAGICK_LIB_MASK >= 1005000
ZEND_METHOD(Gmagick, getimagematte);
#endif
#if defined(GMAGICK_HAVE_SET_IMAGE_PAGE)
ZEND_METHOD(Gmagick, setimagepage);
#endif
#if defined(GMAGICK_HAVE_SET_IMAGE_PAGE)
ZEND_METHOD(Gmagick, getimagepage);
#endif
ZEND_METHOD(Gmagick, thumbnailimage);
ZEND_METHOD(Gmagick, resizeimage);
ZEND_METHOD(Gmagick, clear);
ZEND_METHOD(Gmagick, cropimage);
ZEND_METHOD(Gmagick, cropthumbnailimage);
ZEND_METHOD(Gmagick, coalesceimages);
ZEND_METHOD(Gmagick, compositeimage);
ZEND_METHOD(Gmagick, addimage);
ZEND_METHOD(Gmagick, addnoiseimage);
ZEND_METHOD(Gmagick, borderimage);
ZEND_METHOD(Gmagick, thresholdimage);
ZEND_METHOD(Gmagick, charcoalimage);
ZEND_METHOD(Gmagick, chopimage);
ZEND_METHOD(Gmagick, commentimage);
ZEND_METHOD(Gmagick, current);
ZEND_METHOD(Gmagick, cyclecolormapimage);
ZEND_METHOD(Gmagick, deconstructimages);
ZEND_METHOD(Gmagick, despeckleimage);
ZEND_METHOD(Gmagick, destroy);
ZEND_METHOD(Gmagick, drawimage);
ZEND_METHOD(Gmagick, edgeimage);
ZEND_METHOD(Gmagick, embossimage);
ZEND_METHOD(Gmagick, enhanceimage);
ZEND_METHOD(Gmagick, equalizeimage);
ZEND_METHOD(Gmagick, flipimage);
ZEND_METHOD(Gmagick, flopimage);
ZEND_METHOD(Gmagick, frameimage);
ZEND_METHOD(Gmagick, gammaimage);
ZEND_METHOD(Gmagick, getcopyright);
ZEND_METHOD(Gmagick, getfilename);
ZEND_METHOD(Gmagick, getimage);
ZEND_METHOD(Gmagick, setimage);
ZEND_METHOD(Gmagick, getimagebackgroundcolor);
ZEND_METHOD(Gmagick, getimageblob);
ZEND_METHOD(Gmagick, getimagesblob);
ZEND_METHOD(Gmagick, getimageblueprimary);
ZEND_METHOD(Gmagick, getimagebordercolor);
ZEND_METHOD(Gmagick, getimagechanneldepth);
ZEND_METHOD(Gmagick, getimagecolors);
ZEND_METHOD(Gmagick, getimagecolorspace);
ZEND_METHOD(Gmagick, getimagecompose);
ZEND_METHOD(Gmagick, getimagedelay);
ZEND_METHOD(Gmagick, getimagedepth);
ZEND_METHOD(Gmagick, getnumberimages);
ZEND_METHOD(Gmagick, getimagedispose);
ZEND_METHOD(Gmagick, getimageextrema);
ZEND_METHOD(Gmagick, getimagefilename);
ZEND_METHOD(Gmagick, getimagegamma);
ZEND_METHOD(Gmagick, getimagegreenprimary);
ZEND_METHOD(Gmagick, getimageheight);
ZEND_METHOD(Gmagick, getimagehistogram);
ZEND_METHOD(Gmagick, getimageindex);
ZEND_METHOD(Gmagick, getimageinterlacescheme);
ZEND_METHOD(Gmagick, getimageiterations);
ZEND_METHOD(Gmagick, getimagemattecolor);
ZEND_METHOD(Gmagick, getimageprofile);
ZEND_METHOD(Gmagick, getimageredprimary);
ZEND_METHOD(Gmagick, getimagerenderingintent);
ZEND_METHOD(Gmagick, getimageresolution);
ZEND_METHOD(Gmagick, getimagescene);
ZEND_METHOD(Gmagick, getimagesignature);
ZEND_METHOD(Gmagick, getimagetype);
ZEND_METHOD(Gmagick, getimageunits);
ZEND_METHOD(Gmagick, getimagewhitepoint);
ZEND_METHOD(Gmagick, getimagewidth);
ZEND_METHOD(Gmagick, getpackagename);
ZEND_METHOD(Gmagick, getquantumdepth);
ZEND_METHOD(Gmagick, getreleasedate);
ZEND_METHOD(Gmagick, getsamplingfactors);
ZEND_METHOD(Gmagick, getsize);
ZEND_METHOD(Gmagick, setinterlacescheme);
ZEND_METHOD(Gmagick, hasnextimage);
ZEND_METHOD(Gmagick, haspreviousimage);
ZEND_METHOD(Gmagick, implodeimage);
ZEND_METHOD(Gmagick, labelimage);
ZEND_METHOD(Gmagick, levelimage);
ZEND_METHOD(Gmagick, magnifyimage);
ZEND_METHOD(Gmagick, mapimage);
ZEND_METHOD(Gmagick, medianfilterimage);
ZEND_METHOD(Gmagick, minifyimage);
ZEND_METHOD(Gmagick, modulateimage);
ZEND_METHOD(Gmagick, motionblurimage);
ZEND_METHOD(Gmagick, newimage);
ZEND_METHOD(Gmagick, nextimage);
ZEND_METHOD(Gmagick, normalizeimage);
ZEND_METHOD(Gmagick, oilpaintimage);
ZEND_METHOD(Gmagick, previousimage);
ZEND_METHOD(Gmagick, profileimage);
ZEND_METHOD(Gmagick, quantizeimage);
ZEND_METHOD(Gmagick, quantizeimages);
ZEND_METHOD(Gmagick, queryfontmetrics);
ZEND_METHOD(Gmagick, queryfonts);
ZEND_METHOD(Gmagick, queryformats);
ZEND_METHOD(Gmagick, radialblurimage);
ZEND_METHOD(Gmagick, raiseimage);
ZEND_METHOD(Gmagick, readimageblob);
ZEND_METHOD(Gmagick, reducenoiseimage);
ZEND_METHOD(Gmagick, removeimage);
ZEND_METHOD(Gmagick, removeimageprofile);
ZEND_METHOD(Gmagick, resampleimage);
ZEND_METHOD(Gmagick, rollimage);
ZEND_METHOD(Gmagick, rotateimage);
ZEND_METHOD(Gmagick, scaleimage);
ZEND_METHOD(Gmagick, separateimagechannel);
ZEND_METHOD(Gmagick, setfilename);
ZEND_METHOD(Gmagick, setimagebackgroundcolor);
ZEND_METHOD(Gmagick, setimageblueprimary);
ZEND_METHOD(Gmagick, setimagebordercolor);
ZEND_METHOD(Gmagick, setimagechanneldepth);
ZEND_METHOD(Gmagick, setimagecolorspace);
ZEND_METHOD(Gmagick, setimagecompose);
ZEND_METHOD(Gmagick, getimagecompression);
ZEND_METHOD(Gmagick, setimagecompression);
ZEND_METHOD(Gmagick, setimagedelay);
ZEND_METHOD(Gmagick, setimagedepth);
ZEND_METHOD(Gmagick, setimagedispose);
ZEND_METHOD(Gmagick, setimagefilename);
ZEND_METHOD(Gmagick, getimageformat);
ZEND_METHOD(Gmagick, setimageformat);
ZEND_METHOD(Gmagick, setimagegamma);
ZEND_METHOD(Gmagick, setimagegreenprimary);
ZEND_METHOD(Gmagick, setimageindex);
ZEND_METHOD(Gmagick, setimageinterlacescheme);
ZEND_METHOD(Gmagick, setimageiterations);
ZEND_METHOD(Gmagick, setimageprofile);
ZEND_METHOD(Gmagick, setimageredprimary);
ZEND_METHOD(Gmagick, setimagerenderingintent);
ZEND_METHOD(Gmagick, setimageresolution);
ZEND_METHOD(Gmagick, setimagescene);
ZEND_METHOD(Gmagick, setimagetype);
ZEND_METHOD(Gmagick, setimageunits);
ZEND_METHOD(Gmagick, setimagewhitepoint);
ZEND_METHOD(Gmagick, setsamplingfactors);
ZEND_METHOD(Gmagick, setsize);
ZEND_METHOD(Gmagick, shearimage);
ZEND_METHOD(Gmagick, solarizeimage);
ZEND_METHOD(Gmagick, spreadimage);
ZEND_METHOD(Gmagick, stripimage);
ZEND_METHOD(Gmagick, swirlimage);
ZEND_METHOD(Gmagick, trimimage);
ZEND_METHOD(Gmagick, blackthresholdimage);
ZEND_METHOD(Gmagick, whitethresholdimage);
ZEND_METHOD(Gmagick, colordecisionlist);
ZEND_METHOD(Gmagick, clipimage);
ZEND_METHOD(Gmagick, clippathimage);
ZEND_METHOD(Gmagick, colorfloodfillimage);
ZEND_METHOD(Gmagick, colorizeimage);
ZEND_METHOD(Gmagick, compareimagechannels);
ZEND_METHOD(Gmagick, compareimages);
ZEND_METHOD(Gmagick, contrastimage);
ZEND_METHOD(Gmagick, convolveimage);
ZEND_METHOD(Gmagick, extentimage);
ZEND_METHOD(Gmagick, getimageboundingbox);
ZEND_METHOD(Gmagick, getimageattribute);
ZEND_METHOD(Gmagick, setimageattribute);
ZEND_METHOD(Gmagick, getimagechannelextrema);
ZEND_METHOD(Gmagick, getimagechannelmean);
ZEND_METHOD(Gmagick, getimagecolormapcolor);
ZEND_METHOD(Gmagick, setimagecolormapcolor);
ZEND_METHOD(Gmagick, getimagegravity);
#if defined(HAVE_GMAGICK_SET_IMAGE_GRAVITY)
ZEND_METHOD(Gmagick, setimagegravity);
#endif
ZEND_METHOD(Gmagick, setimagemattecolor);
ZEND_METHOD(Gmagick, getimagevirtualpixelmethod);
ZEND_METHOD(Gmagick, setimagevirtualpixelmethod);
ZEND_METHOD(Gmagick, haldclutimage);
ZEND_METHOD(Gmagick, mattefloodfillimage);
ZEND_METHOD(Gmagick, montageimage);
ZEND_METHOD(Gmagick, morphimages);
ZEND_METHOD(Gmagick, mosaicimages);
ZEND_METHOD(Gmagick, shaveimage);
ZEND_METHOD(Gmagick, steganoimage);
ZEND_METHOD(Gmagick, stereoimage);
ZEND_METHOD(Gmagick, transformimage);
ZEND_METHOD(Gmagick, waveimage);
ZEND_METHOD(Gmagick, getimagefuzz);
ZEND_METHOD(Gmagick, setimagefuzz);
ZEND_METHOD(Gmagick, getimagesavedtype);
ZEND_METHOD(Gmagick, setdepth);
ZEND_METHOD(Gmagick, setimageoption);
ZEND_METHOD(Gmagick, setimagesavedtype);
ZEND_METHOD(Gmagick, setformat);
ZEND_METHOD(Gmagick, setresolutionunits);
ZEND_METHOD(Gmagick, getimagegeometry);
ZEND_METHOD(Gmagick, getresourcelimit);
ZEND_METHOD(Gmagick, setresourcelimit);
ZEND_METHOD(Gmagick, negateimage);
ZEND_METHOD(Gmagick, sharpenimage);
ZEND_METHOD(Gmagick, textureimage);
ZEND_METHOD(Gmagick, flattenimages);
ZEND_METHOD(Gmagick, sampleimage);
ZEND_METHOD(Gmagick, cloneimage);
ZEND_METHOD(Gmagick, appendimages);
ZEND_METHOD(Gmagick, unsharpmaskimage);
ZEND_METHOD(Gmagick, setresolution);
ZEND_METHOD(Gmagick, adaptivethresholdimage);
ZEND_METHOD(Gmagick, affinetransformimage);
ZEND_METHOD(Gmagick, averageimages);
ZEND_METHOD(GmagickPixel, __construct);
ZEND_METHOD(GmagickPixel, getcolor);
ZEND_METHOD(GmagickPixel, setcolor);
ZEND_METHOD(GmagickPixel, getcolorcount);
ZEND_METHOD(GmagickPixel, setcolorcount);
ZEND_METHOD(GmagickPixel, getcolorvalue);
ZEND_METHOD(GmagickPixel, setcolorvalue);
ZEND_METHOD(GmagickPixel, getcolorvaluequantum);
ZEND_METHOD(GmagickPixel, setcolorvaluequantum);
ZEND_METHOD(GmagickDraw, setstrokecolor);
ZEND_METHOD(GmagickDraw, setstrokewidth);
ZEND_METHOD(GmagickDraw, ellipse);
ZEND_METHOD(GmagickDraw, annotate);
ZEND_METHOD(GmagickDraw, affine);
ZEND_METHOD(GmagickDraw, arc);
ZEND_METHOD(GmagickDraw, bezier);
ZEND_METHOD(GmagickDraw, getfillcolor);
ZEND_METHOD(GmagickDraw, getfillopacity);
ZEND_METHOD(GmagickDraw, getfont);
ZEND_METHOD(GmagickDraw, getfontfamily);
ZEND_METHOD(GmagickDraw, setfontfamily);
ZEND_METHOD(GmagickDraw, getfontsize);
ZEND_METHOD(GmagickDraw, getfontstyle);
ZEND_METHOD(GmagickDraw, getfontweight);
ZEND_METHOD(GmagickDraw, getstrokeopacity);
ZEND_METHOD(GmagickDraw, getstrokecolor);
ZEND_METHOD(GmagickDraw, getstrokewidth);
ZEND_METHOD(GmagickDraw, gettextdecoration);
ZEND_METHOD(GmagickDraw, gettextencoding);
ZEND_METHOD(GmagickDraw, line);
ZEND_METHOD(GmagickDraw, point);
ZEND_METHOD(GmagickDraw, polygon);
ZEND_METHOD(GmagickDraw, polyline);
ZEND_METHOD(GmagickDraw, rectangle);
ZEND_METHOD(GmagickDraw, rotate);
ZEND_METHOD(GmagickDraw, roundrectangle);
ZEND_METHOD(GmagickDraw, scale);
ZEND_METHOD(GmagickDraw, setfillcolor);
ZEND_METHOD(GmagickDraw, setfillopacity);
ZEND_METHOD(GmagickDraw, setfont);
ZEND_METHOD(GmagickDraw, setfontsize);
ZEND_METHOD(GmagickDraw, setfontstyle);
ZEND_METHOD(GmagickDraw, setfontweight);
ZEND_METHOD(GmagickDraw, setstrokeopacity);
ZEND_METHOD(GmagickDraw, settextdecoration);
ZEND_METHOD(GmagickDraw, settextencoding);
ZEND_METHOD(GmagickDraw, getgravity);
ZEND_METHOD(GmagickDraw, setgravity);
ZEND_METHOD(GmagickDraw, getstrokeantialias);
ZEND_METHOD(GmagickDraw, setstrokeantialias);
ZEND_METHOD(GmagickDraw, getstrokedashoffset);
ZEND_METHOD(GmagickDraw, setstrokedashoffset);
ZEND_METHOD(GmagickDraw, getstrokelinecap);
ZEND_METHOD(GmagickDraw, setstrokelinecap);
ZEND_METHOD(GmagickDraw, getstrokelinejoin);
ZEND_METHOD(GmagickDraw, setstrokelinejoin);
ZEND_METHOD(GmagickDraw, getstrokemiterlimit);
ZEND_METHOD(GmagickDraw, setstrokemiterlimit);
#if GMAGICK_LIB_MASK >= 1003000
ZEND_METHOD(GmagickDraw, getstrokedasharray);
#endif
#if GMAGICK_LIB_MASK >= 1003000
ZEND_METHOD(GmagickDraw, setstrokedasharray);
#endif
ZEND_METHOD(GmagickDraw, circle);
ZEND_METHOD(GmagickDraw, getclippath);
ZEND_METHOD(GmagickDraw, setclippath);
ZEND_METHOD(GmagickDraw, getcliprule);
ZEND_METHOD(GmagickDraw, setcliprule);
ZEND_METHOD(GmagickDraw, getclipunits);
ZEND_METHOD(GmagickDraw, setclipunits);
ZEND_METHOD(GmagickDraw, color);
ZEND_METHOD(GmagickDraw, comment);
ZEND_METHOD(GmagickDraw, setfillpatternurl);
ZEND_METHOD(GmagickDraw, getfillrule);
ZEND_METHOD(GmagickDraw, setfillrule);
ZEND_METHOD(GmagickDraw, getfontstretch);
ZEND_METHOD(GmagickDraw, setfontstretch);
ZEND_METHOD(GmagickDraw, pathclose);
ZEND_METHOD(GmagickDraw, pathcurvetoabsolute);
ZEND_METHOD(GmagickDraw, pathcurvetorelative);
ZEND_METHOD(GmagickDraw, pathcurvetoquadraticbezierabsolute);
ZEND_METHOD(GmagickDraw, pathcurvetoquadraticbezierrelative);
ZEND_METHOD(GmagickDraw, pathcurvetoquadraticbeziersmoothabsolute);
ZEND_METHOD(GmagickDraw, pathcurvetoquadraticbeziersmoothrelative);
ZEND_METHOD(GmagickDraw, pathcurvetosmoothabsolute);
ZEND_METHOD(GmagickDraw, pathcurvetosmoothrelative);
ZEND_METHOD(GmagickDraw, pathellipticarcabsolute);
ZEND_METHOD(GmagickDraw, pathellipticarcrelative);
ZEND_METHOD(GmagickDraw, pathmovetoabsolute);
ZEND_METHOD(GmagickDraw, pathmovetorelative);
ZEND_METHOD(GmagickDraw, pathlinetoabsolute);
ZEND_METHOD(GmagickDraw, pathlinetorelative);
ZEND_METHOD(GmagickDraw, pathlinetohorizontalabsolute);
ZEND_METHOD(GmagickDraw, pathlinetohorizontalrelative);
ZEND_METHOD(GmagickDraw, pathlinetoverticalabsolute);
ZEND_METHOD(GmagickDraw, pathlinetoverticalrelative);
ZEND_METHOD(GmagickDraw, pathstart);
ZEND_METHOD(GmagickDraw, pathfinish);
ZEND_METHOD(GmagickDraw, popclippath);
ZEND_METHOD(GmagickDraw, popdefs);
ZEND_METHOD(GmagickDraw, pushdefs);
ZEND_METHOD(GmagickDraw, poppattern);
ZEND_METHOD(GmagickDraw, pushpattern);
ZEND_METHOD(GmagickDraw, pushclippath);
ZEND_METHOD(GmagickDraw, skewx);
ZEND_METHOD(GmagickDraw, skewy);
ZEND_METHOD(GmagickDraw, setstrokepatternurl);
ZEND_METHOD(GmagickDraw, gettextantialias);
ZEND_METHOD(GmagickDraw, settextantialias);
ZEND_METHOD(GmagickDraw, gettextundercolor);
ZEND_METHOD(GmagickDraw, settextundercolor);
ZEND_METHOD(GmagickDraw, translate);
ZEND_METHOD(GmagickDraw, setviewbox);
ZEND_METHOD(GmagickDraw, popGraphicContext);
ZEND_METHOD(GmagickDraw, pushGraphicContext);


static const zend_function_entry class_Gmagick_methods[] = {
	ZEND_ME(Gmagick, __construct, arginfo_class_Gmagick___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, __tostring, arginfo_class_Gmagick___tostring, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, readimage, arginfo_class_Gmagick_readimage, ZEND_ACC_PUBLIC)
	ZEND_MALIAS(Gmagick, read, readimage, arginfo_class_Gmagick_read, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, readimagefile, arginfo_class_Gmagick_readimagefile, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, writeimage, arginfo_class_Gmagick_writeimage, ZEND_ACC_PUBLIC)
	ZEND_MALIAS(Gmagick, write, writeimage, arginfo_class_Gmagick_write, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, writeimagefile, arginfo_class_Gmagick_writeimagefile, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getversion, arginfo_class_Gmagick_getversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Gmagick, annotateimage, arginfo_class_Gmagick_annotateimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, blurimage, arginfo_class_Gmagick_blurimage, ZEND_ACC_PUBLIC)
#if GMAGICK_LIB_MASK >= 1003007
	ZEND_ME(Gmagick, setcompressionquality, arginfo_class_Gmagick_setcompressionquality, ZEND_ACC_PUBLIC)
#endif
#if GMAGICK_LIB_MASK >= 1005000
	ZEND_ME(Gmagick, getimagematte, arginfo_class_Gmagick_getimagematte, ZEND_ACC_PUBLIC)
#endif
#if defined(GMAGICK_HAVE_SET_IMAGE_PAGE)
	ZEND_ME(Gmagick, setimagepage, arginfo_class_Gmagick_setimagepage, ZEND_ACC_PUBLIC)
#endif
#if defined(GMAGICK_HAVE_SET_IMAGE_PAGE)
	ZEND_ME(Gmagick, getimagepage, arginfo_class_Gmagick_getimagepage, ZEND_ACC_PUBLIC)
#endif
	ZEND_ME(Gmagick, thumbnailimage, arginfo_class_Gmagick_thumbnailimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, resizeimage, arginfo_class_Gmagick_resizeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, clear, arginfo_class_Gmagick_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, cropimage, arginfo_class_Gmagick_cropimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, cropthumbnailimage, arginfo_class_Gmagick_cropthumbnailimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, coalesceimages, arginfo_class_Gmagick_coalesceimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, compositeimage, arginfo_class_Gmagick_compositeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, addimage, arginfo_class_Gmagick_addimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, addnoiseimage, arginfo_class_Gmagick_addnoiseimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, borderimage, arginfo_class_Gmagick_borderimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, thresholdimage, arginfo_class_Gmagick_thresholdimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, charcoalimage, arginfo_class_Gmagick_charcoalimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, chopimage, arginfo_class_Gmagick_chopimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, commentimage, arginfo_class_Gmagick_commentimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, current, arginfo_class_Gmagick_current, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, cyclecolormapimage, arginfo_class_Gmagick_cyclecolormapimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, deconstructimages, arginfo_class_Gmagick_deconstructimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, despeckleimage, arginfo_class_Gmagick_despeckleimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, destroy, arginfo_class_Gmagick_destroy, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, drawimage, arginfo_class_Gmagick_drawimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, edgeimage, arginfo_class_Gmagick_edgeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, embossimage, arginfo_class_Gmagick_embossimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, enhanceimage, arginfo_class_Gmagick_enhanceimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, equalizeimage, arginfo_class_Gmagick_equalizeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, flipimage, arginfo_class_Gmagick_flipimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, flopimage, arginfo_class_Gmagick_flopimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, frameimage, arginfo_class_Gmagick_frameimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, gammaimage, arginfo_class_Gmagick_gammaimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getcopyright, arginfo_class_Gmagick_getcopyright, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getfilename, arginfo_class_Gmagick_getfilename, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimage, arginfo_class_Gmagick_getimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimage, arginfo_class_Gmagick_setimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagebackgroundcolor, arginfo_class_Gmagick_getimagebackgroundcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageblob, arginfo_class_Gmagick_getimageblob, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagesblob, arginfo_class_Gmagick_getimagesblob, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageblueprimary, arginfo_class_Gmagick_getimageblueprimary, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagebordercolor, arginfo_class_Gmagick_getimagebordercolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagechanneldepth, arginfo_class_Gmagick_getimagechanneldepth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagecolors, arginfo_class_Gmagick_getimagecolors, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagecolorspace, arginfo_class_Gmagick_getimagecolorspace, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagecompose, arginfo_class_Gmagick_getimagecompose, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagedelay, arginfo_class_Gmagick_getimagedelay, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagedepth, arginfo_class_Gmagick_getimagedepth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getnumberimages, arginfo_class_Gmagick_getnumberimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagedispose, arginfo_class_Gmagick_getimagedispose, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageextrema, arginfo_class_Gmagick_getimageextrema, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagefilename, arginfo_class_Gmagick_getimagefilename, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagegamma, arginfo_class_Gmagick_getimagegamma, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagegreenprimary, arginfo_class_Gmagick_getimagegreenprimary, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageheight, arginfo_class_Gmagick_getimageheight, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagehistogram, arginfo_class_Gmagick_getimagehistogram, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageindex, arginfo_class_Gmagick_getimageindex, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageinterlacescheme, arginfo_class_Gmagick_getimageinterlacescheme, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageiterations, arginfo_class_Gmagick_getimageiterations, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagemattecolor, arginfo_class_Gmagick_getimagemattecolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageprofile, arginfo_class_Gmagick_getimageprofile, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageredprimary, arginfo_class_Gmagick_getimageredprimary, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagerenderingintent, arginfo_class_Gmagick_getimagerenderingintent, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageresolution, arginfo_class_Gmagick_getimageresolution, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagescene, arginfo_class_Gmagick_getimagescene, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagesignature, arginfo_class_Gmagick_getimagesignature, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagetype, arginfo_class_Gmagick_getimagetype, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageunits, arginfo_class_Gmagick_getimageunits, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagewhitepoint, arginfo_class_Gmagick_getimagewhitepoint, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagewidth, arginfo_class_Gmagick_getimagewidth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getpackagename, arginfo_class_Gmagick_getpackagename, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getquantumdepth, arginfo_class_Gmagick_getquantumdepth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getreleasedate, arginfo_class_Gmagick_getreleasedate, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getsamplingfactors, arginfo_class_Gmagick_getsamplingfactors, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getsize, arginfo_class_Gmagick_getsize, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setinterlacescheme, arginfo_class_Gmagick_setinterlacescheme, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, hasnextimage, arginfo_class_Gmagick_hasnextimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, haspreviousimage, arginfo_class_Gmagick_haspreviousimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, implodeimage, arginfo_class_Gmagick_implodeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, labelimage, arginfo_class_Gmagick_labelimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, levelimage, arginfo_class_Gmagick_levelimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, magnifyimage, arginfo_class_Gmagick_magnifyimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, mapimage, arginfo_class_Gmagick_mapimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, medianfilterimage, arginfo_class_Gmagick_medianfilterimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, minifyimage, arginfo_class_Gmagick_minifyimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, modulateimage, arginfo_class_Gmagick_modulateimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, motionblurimage, arginfo_class_Gmagick_motionblurimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, newimage, arginfo_class_Gmagick_newimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, nextimage, arginfo_class_Gmagick_nextimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, normalizeimage, arginfo_class_Gmagick_normalizeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, oilpaintimage, arginfo_class_Gmagick_oilpaintimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, previousimage, arginfo_class_Gmagick_previousimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, profileimage, arginfo_class_Gmagick_profileimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, quantizeimage, arginfo_class_Gmagick_quantizeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, quantizeimages, arginfo_class_Gmagick_quantizeimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, queryfontmetrics, arginfo_class_Gmagick_queryfontmetrics, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, queryfonts, arginfo_class_Gmagick_queryfonts, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, queryformats, arginfo_class_Gmagick_queryformats, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, radialblurimage, arginfo_class_Gmagick_radialblurimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, raiseimage, arginfo_class_Gmagick_raiseimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, readimageblob, arginfo_class_Gmagick_readimageblob, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, reducenoiseimage, arginfo_class_Gmagick_reducenoiseimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, removeimage, arginfo_class_Gmagick_removeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, removeimageprofile, arginfo_class_Gmagick_removeimageprofile, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, resampleimage, arginfo_class_Gmagick_resampleimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, rollimage, arginfo_class_Gmagick_rollimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, rotateimage, arginfo_class_Gmagick_rotateimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, scaleimage, arginfo_class_Gmagick_scaleimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, separateimagechannel, arginfo_class_Gmagick_separateimagechannel, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setfilename, arginfo_class_Gmagick_setfilename, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagebackgroundcolor, arginfo_class_Gmagick_setimagebackgroundcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageblueprimary, arginfo_class_Gmagick_setimageblueprimary, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagebordercolor, arginfo_class_Gmagick_setimagebordercolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagechanneldepth, arginfo_class_Gmagick_setimagechanneldepth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagecolorspace, arginfo_class_Gmagick_setimagecolorspace, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagecompose, arginfo_class_Gmagick_setimagecompose, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagecompression, arginfo_class_Gmagick_getimagecompression, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagecompression, arginfo_class_Gmagick_setimagecompression, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagedelay, arginfo_class_Gmagick_setimagedelay, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagedepth, arginfo_class_Gmagick_setimagedepth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagedispose, arginfo_class_Gmagick_setimagedispose, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagefilename, arginfo_class_Gmagick_setimagefilename, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageformat, arginfo_class_Gmagick_getimageformat, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageformat, arginfo_class_Gmagick_setimageformat, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagegamma, arginfo_class_Gmagick_setimagegamma, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagegreenprimary, arginfo_class_Gmagick_setimagegreenprimary, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageindex, arginfo_class_Gmagick_setimageindex, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageinterlacescheme, arginfo_class_Gmagick_setimageinterlacescheme, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageiterations, arginfo_class_Gmagick_setimageiterations, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageprofile, arginfo_class_Gmagick_setimageprofile, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageredprimary, arginfo_class_Gmagick_setimageredprimary, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagerenderingintent, arginfo_class_Gmagick_setimagerenderingintent, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageresolution, arginfo_class_Gmagick_setimageresolution, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagescene, arginfo_class_Gmagick_setimagescene, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagetype, arginfo_class_Gmagick_setimagetype, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageunits, arginfo_class_Gmagick_setimageunits, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagewhitepoint, arginfo_class_Gmagick_setimagewhitepoint, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setsamplingfactors, arginfo_class_Gmagick_setsamplingfactors, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setsize, arginfo_class_Gmagick_setsize, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, shearimage, arginfo_class_Gmagick_shearimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, solarizeimage, arginfo_class_Gmagick_solarizeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, spreadimage, arginfo_class_Gmagick_spreadimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, stripimage, arginfo_class_Gmagick_stripimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, swirlimage, arginfo_class_Gmagick_swirlimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, trimimage, arginfo_class_Gmagick_trimimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, blackthresholdimage, arginfo_class_Gmagick_blackthresholdimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, whitethresholdimage, arginfo_class_Gmagick_whitethresholdimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, colordecisionlist, arginfo_class_Gmagick_colordecisionlist, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, clipimage, arginfo_class_Gmagick_clipimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, clippathimage, arginfo_class_Gmagick_clippathimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, colorfloodfillimage, arginfo_class_Gmagick_colorfloodfillimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, colorizeimage, arginfo_class_Gmagick_colorizeimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, compareimagechannels, arginfo_class_Gmagick_compareimagechannels, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, compareimages, arginfo_class_Gmagick_compareimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, contrastimage, arginfo_class_Gmagick_contrastimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, convolveimage, arginfo_class_Gmagick_convolveimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, extentimage, arginfo_class_Gmagick_extentimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageboundingbox, arginfo_class_Gmagick_getimageboundingbox, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimageattribute, arginfo_class_Gmagick_getimageattribute, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageattribute, arginfo_class_Gmagick_setimageattribute, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagechannelextrema, arginfo_class_Gmagick_getimagechannelextrema, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagechannelmean, arginfo_class_Gmagick_getimagechannelmean, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagecolormapcolor, arginfo_class_Gmagick_getimagecolormapcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagecolormapcolor, arginfo_class_Gmagick_setimagecolormapcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagegravity, arginfo_class_Gmagick_getimagegravity, ZEND_ACC_PUBLIC)
#if defined(HAVE_GMAGICK_SET_IMAGE_GRAVITY)
	ZEND_ME(Gmagick, setimagegravity, arginfo_class_Gmagick_setimagegravity, ZEND_ACC_PUBLIC)
#endif
	ZEND_ME(Gmagick, setimagemattecolor, arginfo_class_Gmagick_setimagemattecolor, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagevirtualpixelmethod, arginfo_class_Gmagick_getimagevirtualpixelmethod, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagevirtualpixelmethod, arginfo_class_Gmagick_setimagevirtualpixelmethod, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, haldclutimage, arginfo_class_Gmagick_haldclutimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, mattefloodfillimage, arginfo_class_Gmagick_mattefloodfillimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, montageimage, arginfo_class_Gmagick_montageimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, morphimages, arginfo_class_Gmagick_morphimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, mosaicimages, arginfo_class_Gmagick_mosaicimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, shaveimage, arginfo_class_Gmagick_shaveimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, steganoimage, arginfo_class_Gmagick_steganoimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, stereoimage, arginfo_class_Gmagick_stereoimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, transformimage, arginfo_class_Gmagick_transformimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, waveimage, arginfo_class_Gmagick_waveimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagefuzz, arginfo_class_Gmagick_getimagefuzz, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagefuzz, arginfo_class_Gmagick_setimagefuzz, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagesavedtype, arginfo_class_Gmagick_getimagesavedtype, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setdepth, arginfo_class_Gmagick_setdepth, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimageoption, arginfo_class_Gmagick_setimageoption, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setimagesavedtype, arginfo_class_Gmagick_setimagesavedtype, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setformat, arginfo_class_Gmagick_setformat, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setresolutionunits, arginfo_class_Gmagick_setresolutionunits, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getimagegeometry, arginfo_class_Gmagick_getimagegeometry, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, getresourcelimit, arginfo_class_Gmagick_getresourcelimit, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setresourcelimit, arginfo_class_Gmagick_setresourcelimit, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, negateimage, arginfo_class_Gmagick_negateimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, sharpenimage, arginfo_class_Gmagick_sharpenimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, textureimage, arginfo_class_Gmagick_textureimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, flattenimages, arginfo_class_Gmagick_flattenimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, sampleimage, arginfo_class_Gmagick_sampleimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, cloneimage, arginfo_class_Gmagick_cloneimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, appendimages, arginfo_class_Gmagick_appendimages, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, unsharpmaskimage, arginfo_class_Gmagick_unsharpmaskimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, setresolution, arginfo_class_Gmagick_setresolution, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, adaptivethresholdimage, arginfo_class_Gmagick_adaptivethresholdimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, affinetransformimage, arginfo_class_Gmagick_affinetransformimage, ZEND_ACC_PUBLIC)
	ZEND_ME(Gmagick, averageimages, arginfo_class_Gmagick_averageimages, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GmagickPixel_methods[] = {
	ZEND_ME(GmagickPixel, __construct, arginfo_class_GmagickPixel___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, getcolor, arginfo_class_GmagickPixel_getcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, setcolor, arginfo_class_GmagickPixel_setcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, getcolorcount, arginfo_class_GmagickPixel_getcolorcount, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, setcolorcount, arginfo_class_GmagickPixel_setcolorcount, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, getcolorvalue, arginfo_class_GmagickPixel_getcolorvalue, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, setcolorvalue, arginfo_class_GmagickPixel_setcolorvalue, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, getcolorvaluequantum, arginfo_class_GmagickPixel_getcolorvaluequantum, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickPixel, setcolorvaluequantum, arginfo_class_GmagickPixel_setcolorvaluequantum, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GmagickDraw_methods[] = {
	ZEND_ME(GmagickDraw, setstrokecolor, arginfo_class_GmagickDraw_setstrokecolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokewidth, arginfo_class_GmagickDraw_setstrokewidth, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, ellipse, arginfo_class_GmagickDraw_ellipse, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, annotate, arginfo_class_GmagickDraw_annotate, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, affine, arginfo_class_GmagickDraw_affine, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, arc, arginfo_class_GmagickDraw_arc, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, bezier, arginfo_class_GmagickDraw_bezier, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfillcolor, arginfo_class_GmagickDraw_getfillcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfillopacity, arginfo_class_GmagickDraw_getfillopacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfont, arginfo_class_GmagickDraw_getfont, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfontfamily, arginfo_class_GmagickDraw_getfontfamily, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfontfamily, arginfo_class_GmagickDraw_setfontfamily, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfontsize, arginfo_class_GmagickDraw_getfontsize, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfontstyle, arginfo_class_GmagickDraw_getfontstyle, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfontweight, arginfo_class_GmagickDraw_getfontweight, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokeopacity, arginfo_class_GmagickDraw_getstrokeopacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokecolor, arginfo_class_GmagickDraw_getstrokecolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokewidth, arginfo_class_GmagickDraw_getstrokewidth, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, gettextdecoration, arginfo_class_GmagickDraw_gettextdecoration, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, gettextencoding, arginfo_class_GmagickDraw_gettextencoding, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, line, arginfo_class_GmagickDraw_line, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, point, arginfo_class_GmagickDraw_point, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, polygon, arginfo_class_GmagickDraw_polygon, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, polyline, arginfo_class_GmagickDraw_polyline, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, rectangle, arginfo_class_GmagickDraw_rectangle, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, rotate, arginfo_class_GmagickDraw_rotate, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, roundrectangle, arginfo_class_GmagickDraw_roundrectangle, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, scale, arginfo_class_GmagickDraw_scale, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfillcolor, arginfo_class_GmagickDraw_setfillcolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfillopacity, arginfo_class_GmagickDraw_setfillopacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfont, arginfo_class_GmagickDraw_setfont, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfontsize, arginfo_class_GmagickDraw_setfontsize, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfontstyle, arginfo_class_GmagickDraw_setfontstyle, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfontweight, arginfo_class_GmagickDraw_setfontweight, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokeopacity, arginfo_class_GmagickDraw_setstrokeopacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, settextdecoration, arginfo_class_GmagickDraw_settextdecoration, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, settextencoding, arginfo_class_GmagickDraw_settextencoding, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getgravity, arginfo_class_GmagickDraw_getgravity, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setgravity, arginfo_class_GmagickDraw_setgravity, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokeantialias, arginfo_class_GmagickDraw_getstrokeantialias, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokeantialias, arginfo_class_GmagickDraw_setstrokeantialias, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokedashoffset, arginfo_class_GmagickDraw_getstrokedashoffset, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokedashoffset, arginfo_class_GmagickDraw_setstrokedashoffset, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokelinecap, arginfo_class_GmagickDraw_getstrokelinecap, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokelinecap, arginfo_class_GmagickDraw_setstrokelinecap, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokelinejoin, arginfo_class_GmagickDraw_getstrokelinejoin, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokelinejoin, arginfo_class_GmagickDraw_setstrokelinejoin, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getstrokemiterlimit, arginfo_class_GmagickDraw_getstrokemiterlimit, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokemiterlimit, arginfo_class_GmagickDraw_setstrokemiterlimit, ZEND_ACC_PUBLIC)
#if GMAGICK_LIB_MASK >= 1003000
	ZEND_ME(GmagickDraw, getstrokedasharray, arginfo_class_GmagickDraw_getstrokedasharray, ZEND_ACC_PUBLIC)
#endif
#if GMAGICK_LIB_MASK >= 1003000
	ZEND_ME(GmagickDraw, setstrokedasharray, arginfo_class_GmagickDraw_setstrokedasharray, ZEND_ACC_PUBLIC)
#endif
	ZEND_ME(GmagickDraw, circle, arginfo_class_GmagickDraw_circle, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getclippath, arginfo_class_GmagickDraw_getclippath, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setclippath, arginfo_class_GmagickDraw_setclippath, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getcliprule, arginfo_class_GmagickDraw_getcliprule, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setcliprule, arginfo_class_GmagickDraw_setcliprule, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getclipunits, arginfo_class_GmagickDraw_getclipunits, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setclipunits, arginfo_class_GmagickDraw_setclipunits, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, color, arginfo_class_GmagickDraw_color, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, comment, arginfo_class_GmagickDraw_comment, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfillpatternurl, arginfo_class_GmagickDraw_setfillpatternurl, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfillrule, arginfo_class_GmagickDraw_getfillrule, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfillrule, arginfo_class_GmagickDraw_setfillrule, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, getfontstretch, arginfo_class_GmagickDraw_getfontstretch, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setfontstretch, arginfo_class_GmagickDraw_setfontstretch, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathclose, arginfo_class_GmagickDraw_pathclose, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetoabsolute, arginfo_class_GmagickDraw_pathcurvetoabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetorelative, arginfo_class_GmagickDraw_pathcurvetorelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetoquadraticbezierabsolute, arginfo_class_GmagickDraw_pathcurvetoquadraticbezierabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetoquadraticbezierrelative, arginfo_class_GmagickDraw_pathcurvetoquadraticbezierrelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetoquadraticbeziersmoothabsolute, arginfo_class_GmagickDraw_pathcurvetoquadraticbeziersmoothabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetoquadraticbeziersmoothrelative, arginfo_class_GmagickDraw_pathcurvetoquadraticbeziersmoothrelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetosmoothabsolute, arginfo_class_GmagickDraw_pathcurvetosmoothabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathcurvetosmoothrelative, arginfo_class_GmagickDraw_pathcurvetosmoothrelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathellipticarcabsolute, arginfo_class_GmagickDraw_pathellipticarcabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathellipticarcrelative, arginfo_class_GmagickDraw_pathellipticarcrelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathmovetoabsolute, arginfo_class_GmagickDraw_pathmovetoabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathmovetorelative, arginfo_class_GmagickDraw_pathmovetorelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathlinetoabsolute, arginfo_class_GmagickDraw_pathlinetoabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathlinetorelative, arginfo_class_GmagickDraw_pathlinetorelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathlinetohorizontalabsolute, arginfo_class_GmagickDraw_pathlinetohorizontalabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathlinetohorizontalrelative, arginfo_class_GmagickDraw_pathlinetohorizontalrelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathlinetoverticalabsolute, arginfo_class_GmagickDraw_pathlinetoverticalabsolute, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathlinetoverticalrelative, arginfo_class_GmagickDraw_pathlinetoverticalrelative, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathstart, arginfo_class_GmagickDraw_pathstart, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pathfinish, arginfo_class_GmagickDraw_pathfinish, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, popclippath, arginfo_class_GmagickDraw_popclippath, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, popdefs, arginfo_class_GmagickDraw_popdefs, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pushdefs, arginfo_class_GmagickDraw_pushdefs, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, poppattern, arginfo_class_GmagickDraw_poppattern, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pushpattern, arginfo_class_GmagickDraw_pushpattern, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pushclippath, arginfo_class_GmagickDraw_pushclippath, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, skewx, arginfo_class_GmagickDraw_skewx, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, skewy, arginfo_class_GmagickDraw_skewy, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setstrokepatternurl, arginfo_class_GmagickDraw_setstrokepatternurl, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, gettextantialias, arginfo_class_GmagickDraw_gettextantialias, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, settextantialias, arginfo_class_GmagickDraw_settextantialias, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, gettextundercolor, arginfo_class_GmagickDraw_gettextundercolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, settextundercolor, arginfo_class_GmagickDraw_settextundercolor, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, translate, arginfo_class_GmagickDraw_translate, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, setviewbox, arginfo_class_GmagickDraw_setviewbox, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, popGraphicContext, arginfo_class_GmagickDraw_popGraphicContext, ZEND_ACC_PUBLIC)
	ZEND_ME(GmagickDraw, pushGraphicContext, arginfo_class_GmagickDraw_pushGraphicContext, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

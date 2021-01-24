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
#include "php_gmagick_helpers.h"
			
#if GMAGICK_LIB_MASK >= 1004000 
#if PHP_VERSION_ID < 50399
static MagickBool SafeModeMonitor(const ConfirmAccessMode mode,
				       const char *path,
				       ExceptionInfo *exception)
{
	ARG_NOT_USED(exception);
#if defined(CHECKUID_CHECK_FILE_AND_DIR)	
	if (PG(safe_mode) && (!php_checkuid_ex(path, NULL, CHECKUID_CHECK_FILE_AND_DIR, CHECKUID_NO_ERRORS))) {
		exception = "SafeModeFail";		
		return MagickFail;
	}
#endif	
	return MagickPass;
}

static MagickBool OpenBaseDirMonitor(const ConfirmAccessMode mode,
					const char *path,
					ExceptionInfo *exception)
{
	ARG_NOT_USED(exception);
	if (php_check_open_basedir_ex(path, 0 TSRMLS_CC)) {
		return MagickFail;
	}
	return MagickPass;
}
#endif //#if PHP_VERSION_ID < 50399
#endif //#if GMAGICK_LIB_MASK >= 1004000

/* {{{ Gmagick Gmagick::read(string filename)
	Reads image
*/
PHP_METHOD(gmagick, readimage)
{
	php_gmagick_object *intern;
	char *filename = NULL;
	size_t filename_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename, &filename_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
#if GMAGICK_LIB_MASK >= 1004000 && PHP_VERSION_ID <= 50399
	GMAGICK_SAFEMODE_OPENBASEDIR_CONFIRMACCESS(filename);
#else
	GMAGICK_SAFEMODE_OPENBASEDIR_CHECK(filename);
#endif
	if (MagickReadImage(intern->magick_wand, filename) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to read the image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ Gmagick Gmagick::__construct([string filename])
	Constructs a new Gmagick object
*/
PHP_METHOD(gmagick, __construct)
{
	php_gmagick_object *intern;
	char *filename = NULL;
	size_t filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s!", &filename, &filename_len) == FAILURE) {
		return;
	}
	if (!filename) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
#if GMAGICK_LIB_MASK >= 1004000 && PHP_VERSION_ID <= 50399
	GMAGICK_SAFEMODE_OPENBASEDIR_CONFIRMACCESS(filename);
#else
	GMAGICK_SAFEMODE_OPENBASEDIR_CHECK(filename);
#endif

	if (MagickReadImage(intern->magick_wand, filename) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to read the image");
	}
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::annotateImage(GmagickDraw drawing_wand, float x, float y, float angle, string text)
	Annotates an image with text.
*/
PHP_METHOD(gmagick, annotateimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	php_gmagickdraw_object *internd;
	double x, y, angle;
	char *text;
	size_t text_len;
	zval *objvar;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oddds", &objvar, php_gmagickdraw_sc_entry, &x, &y, &angle, &text, &text_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	internd = Z_GMAGICKDRAW_OBJ_P(objvar);
	status = MagickAnnotateImage(intern->magick_wand, internd->drawing_wand, x, y, angle, text);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to annotate image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::blurImage(float radius, float sigma )
	Adds blur filter to image. Optional third parameter to blur a specific channel.
*/
PHP_METHOD(gmagick, blurimage)
{
	double radius, sigma;
	php_gmagick_object *intern;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &radius, &sigma) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickBlurImage(intern->magick_wand, radius, sigma);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to blur image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ Gmagick Gmagick::write(string filename[, boolean all_frames])
	Writes the current image sequence to a file
*/
PHP_METHOD(gmagick, writeimage)
{
	MagickBool status;
	php_gmagick_object *intern;
	char *filename = NULL;
	size_t filename_len;
	zend_bool all_frames = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &filename, &filename_len, &all_frames) == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	if (!filename) {
		filename = MagickGetImageFilename(intern->magick_wand);
		if (!filename) {
			GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "No image filename specified");
		}
		filename_len = strlen(filename);
	}

	if (!filename_len) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to write the image. Empty filename string provided");
	}
	
	if (all_frames) {
		status = MagickWriteImages(intern->magick_wand, filename, MagickTrue);
	} else {
		status = MagickWriteImage(intern->magick_wand, filename);
	}
	
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to write the image");
	}
	
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::thumbnail(int width, int height[, bool fit[, bool legacy = false]])
	Scales an image to the desired dimensions.  If legacy is true, uses the 
	incorrect behaviour that was present until Gmagick 2.0.1. If false (default) it uses the correct
	behaviour.
*/
PHP_METHOD(gmagick, thumbnailimage)
{
	zend_long columns, rows, width, height;
	php_gmagick_object *intern;
	zend_bool fit = 0;
	zend_bool legacy = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll|bb", &columns, &rows, &fit, &legacy) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	if (MagickStripImage(intern->magick_wand) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to strip image");
	}

	if (!php_gmagick_thumbnail_dimensions(intern->magick_wand, fit, columns, rows, &width, &height, legacy)) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to calculate image dimensions");
	}

	if (MagickResizeImage(intern->magick_wand, width, height, UndefinedFilter, 0.5) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to thumbnail image");
	}
	
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::resize(int width, int height, int filter, float blur[, bool fit = false[, bool legacy = false]])
	Scales an image to the desired dimensions  If legacy is true, uses the 
	incorrect behaviour that was present until Gmagick 2.0.1. If false (default) it uses the correct
	behaviour.
*/
PHP_METHOD(gmagick, resizeimage)
{
	double blur;
	zend_long width, height, new_width, new_height, filter = 0;
	php_gmagick_object *intern;
	zend_bool fit = 0;
	zend_bool legacy = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llld|bb", &width, &height, &filter, &blur, &fit, &legacy) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	
	if (!php_gmagick_thumbnail_dimensions(intern->magick_wand, fit, width, height, &new_width, &new_height, legacy)) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to calculate image dimensions");
	}

	/* No magick is going to happen */

	if (MagickResizeImage(intern->magick_wand, new_width, new_height, filter, blur) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to resize image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::clear()
	Removes all images from object
*/
PHP_METHOD(gmagick, clear)
{
	php_gmagick_object *intern;
	int i, image_count;
	zend_bool failure = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	image_count = MagickGetNumberImages(intern->magick_wand);

	for (i = 0; i < image_count; i++) {
		if (MagickRemoveImage(intern->magick_wand) == MagickFalse) {
			failure = 1;
		}
	}
	
	if (failure) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Failed to remove all images");
	}
	
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::crop(int width, int height, int x, int y)
	Crops image
*/
PHP_METHOD(gmagick, cropimage)
{
	php_gmagick_object *intern;
	long x, y, width, height;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &width, &height, &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	
	if (MagickCropImage(intern->magick_wand, width, height, x, y) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Failed to crop the image");
	}
	
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::cropthumbnailimage(int columns, int rows[, bool legacy])
	 Creates a crop thumbnail. If legacy is true, uses the 
	incorrect behaviour that was present until Gmagick 2.0.1. If false (default) it uses the correct
	behaviour.
*/
PHP_METHOD(gmagick, cropthumbnailimage)
{
	zend_long crop_width, crop_height;
	zend_bool legacy = 0;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll|b", &crop_width, &crop_height, &legacy) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	if (!crop_thumbnail_image(intern->magick_wand, crop_width, crop_height, legacy TSRMLS_CC)) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to crop-thumbnail image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::coalesceImages()
    Composites a set of images while respecting any page offsets and disposal methods.  
    GIF, MIFF, and MNG animation sequences typically start with an image background and 
    each subsequent image varies in size and offset.  returns a new sequence where each image in the 
    sequence is the same size as the first and composited with the next image in the sequence.
*/
PHP_METHOD(gmagick, coalesceimages)
{
	MagickWand *tmp_wand;
	php_gmagick_object *intern, *intern_return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickCoalesceImages(intern->magick_wand);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Coalesce image failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);
	return;

}
/* }}} */

/* {{{ proto Gmagick Gmagick::composite(Gmagick source, int compose, int x, int y)
	Crops image
*/
PHP_METHOD(gmagick, compositeimage)
{
	zval *source_obj;
	php_gmagick_object *source, *intern;
	zend_long x, y, compose;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Olll", &source_obj, php_gmagick_sc_entry, &compose, &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	source = Z_GMAGICK_OBJ_P(source_obj);

	/*
		Causes a bug with some GraphicsMagick versions where the exception is 
		not cleared. This would cause all subsequent operations to fail.
	if (MagickGetNumberImages(source->magick_wand) == 0) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "The source object must contain an image");
	} */

	if (MagickCompositeImage(intern->magick_wand, source->magick_wand, compose, x, y) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Failed to composite the image");
	}
	
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::drawImage(GmagickDraw drawing_wand)
	Renders the GmagickDrawing object on the current image.
*/
PHP_METHOD(gmagick, drawimage)
{
	zval *objvar;
	php_gmagick_object *intern;
	MagickBool status;
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &objvar, php_gmagickdraw_sc_entry) == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	internd = Z_GMAGICKDRAW_OBJ_P(objvar);

	status = MagickDrawImage(intern->magick_wand, internd->drawing_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to draw image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick GMAGICK::addImage(GMAGICK source )
	Adds new image to GMAGICK object from the current position of the source object.
*/
PHP_METHOD(gmagick, addimage)
{
	php_gmagick_object *intern, *intern_add;
	zval *add_obj;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &add_obj, php_gmagick_sc_entry) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	intern_add = Z_GMAGICK_OBJ_P(add_obj);

	GMAGICK_CHECK_NOT_EMPTY(intern_add->magick_wand, 1, 1);

	status = MagickAddImage(intern->magick_wand, intern_add->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to add image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick GMAGICK::addNoiseImage(int noise_type[, int channel])
	Adds random noise to the image. Channel parameter is ignored in ImageMagick below 6.2.8
*/
PHP_METHOD(gmagick, addnoiseimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	zend_long noise;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &noise) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickAddNoiseImage(intern->magick_wand, noise);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to add image noise");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::borderImage(GmagickPixel bordercolor, int width, int height)
	Surrounds the image with a border of the color defined by the bordercolor pixel wand.
*/
PHP_METHOD(gmagick, borderimage)
{
	zval *param;
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;
	zend_long width, height;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zll", &param, &width, &height) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	status = MagickBorderImage(intern->magick_wand, internp->pixel_wand, width, height);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to border image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool Gmagick::thresholdImage(float threshold[, int channel] )
	Changes the value of individual pixels based on the intensity of each pixel compared to threshold.  The result is a high-contrast, two color image.
*/
PHP_METHOD(gmagick, thresholdimage)
{
	php_gmagick_object *intern;
	double threshold;
	MagickBool status;
	zend_long channel = DefaultChannels;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d|l", &threshold, &channel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickThresholdImageChannel(intern->magick_wand, channel, threshold);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to threshold image");
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::charcoalImage(float radius, float sigma)
	Simulates a charcoal drawing.
*/
PHP_METHOD(gmagick, charcoalimage)
{
	double sigma, radius;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &radius, &sigma) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickCharcoalImage(intern->magick_wand, sigma, radius);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to charcoal image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::chopImage(int width, int height, int x, int y)
	Removes a region of an image and collapses the image to occupy the removed portion
*/
PHP_METHOD(gmagick, chopimage)
{
	php_gmagick_object *intern;
	zend_long width, height, x, y;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &width, &height, &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickChopImage(intern->magick_wand, width, height, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to chop image");
	}

	GMAGICK_CHAIN_METHOD;

}
/* }}} */

/* {{{ proto Gmagick Gmagick::commentImage(string comment)
	Adds a comment to your image.
*/
PHP_METHOD(gmagick, commentimage)
{
	php_gmagick_object *intern;
	char *comment;
	size_t comment_len;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &comment, &comment_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickCommentImage(intern->magick_wand, comment);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to comment image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::current()
    Returns reference to the current Gmagick object with image pointer at the correct sequence.
*/
PHP_METHOD(gmagick, current)
{
	RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::cycleColormapImage(int displace)
	Displaces an image's colormap by a given number of positions.  If you cycle the colormap a number of times you can produce a psychodelic effect.
*/
PHP_METHOD(gmagick, cyclecolormapimage)
{
	php_gmagick_object *intern;
	zend_long displace;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &displace) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickCycleColormapImage(intern->magick_wand, displace);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to cycle image colormap");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::deconstructImages()
	Compares each image with the next in a sequence and returns the maximum bounding region of any pixel differences it discovers.
*/
PHP_METHOD(gmagick, deconstructimages)
{
	MagickWand *tmp_wand;
	php_gmagick_object *intern, *intern_return;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickDeconstructImages(intern->magick_wand);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Deconstruct image failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::despeckleImage()
	Reduces the speckle noise in an image while perserving the edges of the original image.
*/
PHP_METHOD(gmagick, despeckleimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickDespeckleImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to despeckle image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool Gmagick::destroy()
	Destroys the Gmagick object
*/
PHP_METHOD(gmagick, destroy)
{
	php_gmagick_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	if (intern->magick_wand == (MagickWand *)NULL) {
		RETURN_FALSE;
	}
	DestroyMagickWand(intern->magick_wand);
	intern->magick_wand = NewMagickWand();
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::edgeImage(float radius)
	Enhance edges within the image with a convolution filter of the given radius.  Use a radius of 0 and Edge() selects a suitable radius for you.
*/
PHP_METHOD(gmagick, edgeimage)
{
	php_gmagick_object *intern;
	double radius;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radius) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickEdgeImage(intern->magick_wand, radius);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to edge image");
	}

	GMAGICK_CHAIN_METHOD;

}
/* }}} */

/* {{{ proto Gmagick Gmagick::embossImage(float radius, float sigma)
	Returns a grayscale image with a three-dimensional effect.  We convolve the image with a Gaussian operator of the given radius and standard deviation (sigma).  For reasonable results, radius should be larger than sigma.  Use a radius of 0 and it will choose a suitable radius for you.
*/
PHP_METHOD(gmagick, embossimage)
{
	php_gmagick_object *intern;
	double radius, sigma;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &radius, &sigma) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickEmbossImage(intern->magick_wand, radius, sigma);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to emboss image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */




/* {{{ proto Gmagick Gmagick::enhanceImage()
	Applies a digital filter that improves the quality of a noisy image.
*/
PHP_METHOD(gmagick, enhanceimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickEnhanceImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to enchance image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::equalizeImage()
	Equalizes the image histogram.
*/
PHP_METHOD(gmagick, equalizeimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickEqualizeImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to equalize image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::flipImage()
	Creates a vertical mirror image by reflecting the pixels around the central x-axis.
*/
PHP_METHOD(gmagick, flipimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickFlipImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to flip image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::flopImage()
	Creates a horizontal mirror image by reflecting the pixels around the central y-axis.
*/
PHP_METHOD(gmagick, flopimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickFlopImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to flop image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::frameImage(GmagickPixel matte_color, int width, int height, int inner_bevel, int outer_bevel)
	Adds a simulated three-dimensional border around the image
*/
PHP_METHOD(gmagick, frameimage)
{
	zval *param;
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;
	zend_long width, height, inner_bevel, outer_bevel;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zllll", &param, &width, &height, &inner_bevel, &outer_bevel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	status = MagickFrameImage(intern->magick_wand, internp->pixel_wand, width, height, inner_bevel, outer_bevel);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to frame image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::gammaImage(float gamma[, int channel])
	Gamma-corrects an image.  The same image viewed on different devices will have perceptual differences in the way the image's intensities are represented on the screen.  Specify individual gamma levels for the red, green, and blue channels, or adjust all three with the gamma parameter.  Values typically range from 0.8 to 2.3.
*/
PHP_METHOD(gmagick, gammaimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	double gamma;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &gamma) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGammaImage(intern->magick_wand, gamma);
    //TODO - read channels.
	//status = MagickGammaImageChannel(intern->magick_wand, channel, gamma);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to gamma image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto string Gmagick::getCopyright()
	Returns the ImageMagick API copyright as a string constant.
*/
PHP_METHOD(gmagick, getcopyright)
{
	char *copyright;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	copyright = (char *)MagickGetCopyright();
	ZVAL_STRING(return_value, copyright);

	/* GMAGICK_FREE_MEMORY(char *, copyright); */
	return;
}
/* }}} */

/* {{{ proto string Gmagick::getFilename()
	Returns the filename associated with an image sequence.
*/
PHP_METHOD(gmagick, getfilename)
{
	php_gmagick_object *intern;
	char *filename;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	filename = (char *)MagickGetFilename(intern->magick_wand);

	if (filename) {
		ZVAL_STRING(return_value, filename);
		GMAGICK_FREE_MEMORY(char *, filename);
	}
	return;
}
/* }}} */

/* {{{ proto GmagickPixel Gmagick::getImageBackgroundColor()
	Returns the image background color.
*/
PHP_METHOD(gmagick, getimagebackgroundcolor)
{
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;	
	PixelWand *tmp_wand;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	tmp_wand = NewPixelWand();
	status = MagickGetImageBackgroundColor(intern->magick_wand, tmp_wand);

	if (tmp_wand == (PixelWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image background color");
	}

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image background color");
	}

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto string Gmagick::getImageBlob()
Returns the current image sequence as a string
*/
PHP_METHOD(gmagick, getimageblob)
{
	php_gmagick_object *intern;
	unsigned char *image_contents;
	size_t image_size;
	char *buffer;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_HAS_FORMAT(buffer, intern->magick_wand, 1);

	MagickResetIterator(intern->magick_wand);
	image_contents = MagickWriteImageBlob(intern->magick_wand, &image_size);
	if (!image_contents) {
		return;
	}

	ZVAL_STRINGL(return_value, (char *)image_contents, image_size);
	GMAGICK_FREE_MEMORY(unsigned char *, image_contents);
	return;
}
/* }}} */ 

/* {{{ proto string Gmagick::getImagesBlob()
	Returns all image sequences as a string
*/
PHP_METHOD(gmagick, getimagesblob)
{
	php_gmagick_object *intern;
	unsigned char *image_contents;
	size_t image_size;
	char *buffer;
	size_t current;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	/* Get the current iterator position */
	current = MagickGetImageIndex(intern->magick_wand);

	/* Reset the iterator */
	MagickResetIterator(intern->magick_wand);

	/* Loop all images to make sure they have a format */
	while (MagickNextImage(intern->magick_wand)) {
		GMAGICK_HAS_FORMAT(buffer, intern->magick_wand, 1);
	}

	/* Get the current iterator position */
	status = MagickSetImageIndex(intern->magick_wand, current);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set the iterator index");
	}

	image_contents = MagickWriteImageBlob(intern->magick_wand, &image_size);
	if (!image_contents) {
		return;
	}

	ZVAL_STRINGL(return_value, (char *)image_contents, image_size);
	GMAGICK_FREE_MEMORY(unsigned char *, image_contents);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageBackgroundColor(GmagickPixel background)
	Sets the image background color.
*/
PHP_METHOD(gmagick, setimagebackgroundcolor)
{
	zval *param;
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	status = MagickSetImageBackgroundColor(intern->magick_wand, internp->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image background color");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto array Gmagick::getImageBluePrimary(float x, float y)
	Returns the chromaticy blue primary point for the image.
*/
PHP_METHOD(gmagick, getimageblueprimary)
{
	php_gmagick_object *intern;
	MagickBool status;
	double x, y;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageBluePrimary(intern->magick_wand, &x, &y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image blue primary");
	}

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

	return;
}
/* }}} */

/* {{{ proto GmagickPixel Gmagick::getImageBorderColor()
	Returns the image border color.
*/
PHP_METHOD(gmagick, getimagebordercolor)
{
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;
	PixelWand *tmp_wand;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = NewPixelWand();
	status = MagickGetImageBorderColor(intern->magick_wand, tmp_wand);

	if (tmp_wand == (PixelWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image border color");
	}

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image border color");
	}

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageChannelDepth()
	Gets the depth for a particular image channel.
*/
PHP_METHOD(gmagick, getimagechanneldepth)
{
	php_gmagick_object *intern;
	zend_long channel_type, channel_depth;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &channel_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	channel_depth = MagickGetImageChannelDepth(intern->magick_wand, channel_type);
	RETVAL_LONG(channel_depth);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageBluePrimary(float x,float y)
	Sets the image chromaticity blue primary point
*/
PHP_METHOD(gmagick, setimageblueprimary)
{
	php_gmagick_object *intern;
	double x, y;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageBluePrimary(intern->magick_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image blue primary");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageBorderColor(GmagickPixel border)
	Sets the image border color
*/
PHP_METHOD(gmagick, setimagebordercolor)
{
	zval *param;
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	status = MagickSetImageBorderColor(intern->magick_wand, internp->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image border color");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageChannelDepth(int channel, int depth)
	Sets the depth of a particular image channel
*/
PHP_METHOD(gmagick, setimagechanneldepth)
{
	php_gmagick_object *intern;
	zend_long channel_type, depth;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &channel_type, &depth) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageChannelDepth(intern->magick_wand, channel_type, depth);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image channel depth");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageColorspace(int colorspace)
	Sets the image colorspace
*/
PHP_METHOD(gmagick, setimagecolorspace)
{
	php_gmagick_object *intern;
	zend_long colorspace;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &colorspace) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageColorspace(intern->magick_wand, colorspace);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image colorspace");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setInterlaceScheme(INTERLACETYPE interlace_scheme)
	Sets the image interlace scheme.
*/
PHP_METHOD(gmagick, setinterlacescheme)
{
	php_gmagick_object *intern;
	zend_long schema;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &schema) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetInterlaceScheme(intern->magick_wand, schema);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set interlace scheme");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int Gmagick::getImageColorspace()
	Gets the image colorspace.
*/
PHP_METHOD(gmagick, getimagecolorspace)
{
	php_gmagick_object *intern;
	long colorSpace;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	colorSpace = MagickGetImageColorspace(intern->magick_wand);
	RETVAL_LONG(colorSpace);
}
/* }}} */

/* {{{ proto int Gmagick::getImageColors()
	Gets the number of unique colors in the image.
*/
PHP_METHOD(gmagick, getimagecolors)
{
	php_gmagick_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	ZVAL_LONG(return_value, (long)MagickGetImageColors(intern->magick_wand));
	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageCompose()
	Returns the composite operator associated with the image.
*/
PHP_METHOD(gmagick, getimagecompose)
{
	php_gmagick_object *intern;
	long composite;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	composite = MagickGetImageCompose(intern->magick_wand);
	RETVAL_LONG(composite);
}
/* }}} */

/* {{{ proto int Gmagick::getImageDelay()
	Gets the image delay.
*/
PHP_METHOD(gmagick, getimagedelay)
{
	php_gmagick_object *intern;
	long delay;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	delay = MagickGetImageDelay(intern->magick_wand);
	RETVAL_LONG(delay);
}
/* }}} */

/* {{{ proto int Gmagick::getImageDepth()
	Gets the image depth.
*/
PHP_METHOD(gmagick, getimagedepth)
{
	php_gmagick_object *intern;
	long depth;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	depth = MagickGetImageDepth(intern->magick_wand);
	RETVAL_LONG(depth);
}
/* }}} */

/* {{{ proto int Gmagick::getNumberImages()
	Returns the number of images associated with Gmagick object.
*/
PHP_METHOD(gmagick, getnumberimages)
{
	php_gmagick_object *intern;
	unsigned long num_images;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());

	num_images = MagickGetNumberImages(intern->magick_wand);
	RETVAL_LONG(num_images);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageCompose(int compose)
	Sets the image composite operator, useful for specifying how to composite the image thumbnail when using the Gmagick::montageImage() method.
*/
PHP_METHOD(gmagick, setimagecompose)
{
	php_gmagick_object *intern;
	zend_long compose;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &compose) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageCompose(intern->magick_wand, compose);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image composite operator");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageCompression(int compression)
    Sets the image compression.
*/
PHP_METHOD(gmagick, setimagecompression)
{
	php_gmagick_object *intern;
	zend_long compression;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &compression) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	if (php_gmagick_ensure_not_empty (intern->magick_wand) == 0) {
		return;
	}

	status = MagickSetImageCompression(intern->magick_wand, compression);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image compression");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto int Gmagick::getImageCompression
	Gets the image compression
*/
PHP_METHOD(gmagick, getimagecompression)
{
	php_gmagick_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	RETVAL_LONG(MagickGetImageCompression(intern->magick_wand));
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageDelay(int delay)
	Sets the image delay.
*/
PHP_METHOD(gmagick, setimagedelay)
{
	php_gmagick_object *intern;
	zend_long delay;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &delay) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageDelay(intern->magick_wand, delay);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image delay");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageDepth(int depth)
	Sets the image depth.
*/
PHP_METHOD(gmagick, setimagedepth)
{
	php_gmagick_object *intern;
	zend_long depth;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &depth) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageDepth(intern->magick_wand, depth);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image depth");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int Gmagick::getImageDispose()
	Gets the image disposal method.
*/
PHP_METHOD(gmagick, getimagedispose)
{
	php_gmagick_object *intern;
	long dispose;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	dispose = MagickGetImageDispose(intern->magick_wand);
	RETVAL_LONG(dispose);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageDispose(int dispose)
	Sets the image disposal method
*/
PHP_METHOD(gmagick, setimagedispose)
{
	php_gmagick_object *intern;
	zend_long dispose;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &dispose) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageDispose(intern->magick_wand, dispose);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image dispose");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setFilename(string filename)
	Sets the filename before you read or write an image file.
*/
PHP_METHOD(gmagick, setfilename)
{
	php_gmagick_object *intern;
	char *filename;
	size_t filename_len;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetFilename(intern->magick_wand, filename);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set filename");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::getImage()
	Returns a new Gmagick object with the current image sequence.
*/
PHP_METHOD(gmagick, getimage)
{
	MagickWand *tmp_wand;
	php_gmagick_object *intern, *intern_return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickGetImage(intern->magick_wand);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Get image failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto bool Gmagick::setImage(Gmagick replace )
	Replaces the current sequence
*/
PHP_METHOD(gmagick, setimage)
{
	zval *objvar;
	MagickBool status;
	php_gmagick_object *intern, *replace;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &objvar, php_gmagick_sc_entry) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	replace = Z_GMAGICK_OBJ_P(objvar);
	GMAGICK_CHECK_NOT_EMPTY(replace->magick_wand, 1, 1);

	status = MagickSetImage(intern->magick_wand, replace->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set the image");
	}
	RETURN_TRUE;

}
/* }}} */

/* {{{ proto array Gmagick::getImageExtrema()
	Gets the extrema for the image.  Returns an associative array with the keys "min" and "max".
*/
PHP_METHOD(gmagick, getimageextrema)
{
	php_gmagick_object *intern;
	unsigned long min, max;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageExtrema(intern->magick_wand, &min, &max);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image extrema");
	}

	array_init(return_value);
	add_assoc_long(return_value, "min", min);
	add_assoc_long(return_value, "max", max);

	return;
}
/* }}} */


/* {{{ proto string Gmagick::getImageFilename()
	Returns the filename of a particular image in a sequence
*/
PHP_METHOD(gmagick, getimagefilename)
{
	php_gmagick_object *intern;
	char *filename;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	filename = MagickGetImageFilename(intern->magick_wand);

	if (filename == (char *)NULL) {
		return;
	}

	ZVAL_STRING(return_value, filename);
	GMAGICK_FREE_MEMORY(char *, filename);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageFilename(string filename)
	Sets the filename of a particular image in a sequence.
*/
PHP_METHOD(gmagick, setimagefilename)
{
	php_gmagick_object *intern;
	char *filename;
	size_t filename_len;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageFilename(intern->magick_wand, filename);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image filename");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto string Gmagick::getImageFormat()
	Returns the format of a particular image in a sequence.
*/
PHP_METHOD(gmagick, getimageformat)
{
	php_gmagick_object *intern;
	char *format;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	format = MagickGetImageFormat(intern->magick_wand);
	if (!format) {
		return;
	}

	ZVAL_STRING(return_value, format);
	GMAGICK_FREE_MEMORY(char *, format);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageFormat(string format)
	Sets the format of a particular image in a sequence.
*/
PHP_METHOD(gmagick, setimageformat)
{
	char *format;
	size_t format_len;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &format, &format_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageFormat(intern->magick_wand, format);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image format");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

#if GMAGICK_LIB_MASK >= 1003007
/* {{{ proto Gmagick Gmagick::setCompressionQuality(int quality)
	Sets the compression quality factor (0-100). The GraphicsMagick default value is 75.
*/
PHP_METHOD(gmagick, setcompressionquality)
{
	php_gmagick_object *intern;
	zend_long compression_quality;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &compression_quality) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetCompressionQuality(intern->magick_wand, compression_quality);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set compression quality");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */
#endif

/* {{{ proto float Gmagick::getImageGamma()
	Gets the image gamma.
*/
PHP_METHOD(gmagick, getimagegamma)
{
	php_gmagick_object *intern;
	double gamma;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	gamma = MagickGetImageGamma(intern->magick_wand);
	RETVAL_DOUBLE(gamma);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageGamma(float gamma)
	Sets the image gamma.
*/
PHP_METHOD(gmagick, setimagegamma)
{
	php_gmagick_object *intern;
	double gamma;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &gamma) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageGamma(intern->magick_wand, gamma);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image gamma");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto array Gmagick::getImageGreenPrimary()
	Returns the chromaticy green primary point. Returns an array with the keys "x" and "y".
*/
PHP_METHOD(gmagick, getimagegreenprimary)
{
	php_gmagick_object *intern;
	double x, y;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageGreenPrimary(intern->magick_wand, &x, &y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image green primary");
	}

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageGreenPrimary(float x, float y)
	Sets the image chromaticity green primary point
*/
PHP_METHOD(gmagick, setimagegreenprimary)
{
	php_gmagick_object *intern;
	double x, y;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageGreenPrimary(intern->magick_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image green primary");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto int Gmagick::getImageHeight()
	Returns the image height.
*/
PHP_METHOD(gmagick, getimageheight)
{
	php_gmagick_object *intern;
	long height;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	height = MagickGetImageHeight(intern->magick_wand);
	RETVAL_LONG(height);
}
/* }}} */

/* {{{ proto array Gmagick::getImageHistogram()
	Returns the image histogram as an array of GmagickPixel objects.
*/
PHP_METHOD(gmagick, getimagehistogram)
{
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	PixelWand **wand_array;
	unsigned long colors = 0;
	unsigned long i;
	zval tmp_pixelwand;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	wand_array = MagickGetImageHistogram(intern->magick_wand, &colors);
	array_init(return_value);

	for (i = 0; i < colors; i++) {
		object_init_ex(&tmp_pixelwand, php_gmagickpixel_sc_entry);
		internp = Z_GMAGICKPIXEL_OBJ_P(&tmp_pixelwand);
		GMAGICKPIXEL_REPLACE_PIXELWAND(internp, wand_array[i]);
		add_next_index_zval(return_value, &tmp_pixelwand);
	}

	GMAGICK_FREE_MEMORY(PixelWand **, wand_array);
	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageIndex()
	Returns the index of the current active image, within the Gmagick object.
*/
PHP_METHOD(gmagick, getimageindex)
{
	MagickBool status;
	php_gmagick_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	status = MagickGetImageIndex(intern->magick_wand);
	ZVAL_LONG(return_value, (long)status);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageIndex(int index)
	Returns the index of the current active image, within the Gmagick object.
*/
PHP_METHOD(gmagick, setimageindex)
{
	zend_long index;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetImageIndex(intern->magick_wand, index);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image index");
	}
	intern->next_out_of_bound = 0;
	GMAGICK_CHAIN_METHOD;

}
/* }}} */


/* {{{ proto int Gmagick::getImageInterlaceScheme()
	Gets the image interlace scheme.
*/
PHP_METHOD(gmagick, getimageinterlacescheme)
{
	php_gmagick_object *intern;
	long interlace;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	interlace = MagickGetImageInterlaceScheme(intern->magick_wand);
	RETVAL_LONG(interlace);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageInterlaceScheme(int interlace_scheme)
	Sets the image interlace scheme
*/
PHP_METHOD(gmagick, setimageinterlacescheme)
{
	php_gmagick_object *intern;
	zend_long interlace;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &interlace) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageInterlaceScheme(intern->magick_wand, interlace);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image interlace scheme");
	}
	
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int Gmagick::getImageIterations()
	Gets the image iterations.
*/
PHP_METHOD(gmagick, getimageiterations)
{
	php_gmagick_object *intern;
	long iterations;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	iterations = MagickGetImageIterations(intern->magick_wand);
	RETVAL_LONG(iterations);
}
/* }}} */

/* {{{ proto array Gmagick::getImageGeometry()
	Returns the width and height as an associative array.
*/
PHP_METHOD(gmagick, getimagegeometry)
{
	long width,height;
	php_gmagick_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	width = MagickGetImageWidth(intern->magick_wand);
	height = MagickGetImageHeight(intern->magick_wand);

	array_init(return_value);
	add_assoc_long(return_value, "width", width);
	add_assoc_long(return_value, "height", height);

	return;
}
/* }}} */

/* {{{ proto GmagickPixel Gmagick::getImageMatteColor()
	Returns the image matte color.
*/
PHP_METHOD(gmagick, getimagemattecolor)
{
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	MagickBool status;
	PixelWand *tmp_wand;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = NewPixelWand();

	status = MagickGetImageMatteColor(intern->magick_wand, tmp_wand);

	if (tmp_wand == (PixelWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image matte color");
	}

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable get image matter color");
	}

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

#if GMAGICK_LIB_MASK >= 1005000
/* {{{ proto int Gmagick::getImageMatte()
	Returns true if the image has a matte channel otherwise false
*/
PHP_METHOD(gmagick, getimagematte)
{
	php_gmagick_object *intern;
	long matte;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	matte = MagickGetImageMatte(intern->magick_wand);	

	RETVAL_LONG(matte);
}
/* }}} */
#endif

#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE
/* {{{ proto array Gmagick::getImagePage()
	Returns the page geometry associated with the image in an array with the keys "width", "height", "x", and "y".
*/
PHP_METHOD(gmagick, getimagepage)
{
	php_gmagick_object *intern;
	MagickBool status;
	unsigned long width, height;
	long x, y;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	if (php_gmagick_ensure_not_empty (intern->magick_wand) == 0)
		return;

	status = MagickGetImagePage(intern->magick_wand, &width, &height, &x, &y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image page");
		return;
	}

	array_init(return_value);

	add_assoc_long(return_value, "width", width);
	add_assoc_long(return_value, "height", height);
	add_assoc_long(return_value, "x", x);
	add_assoc_long(return_value, "y", y);

	return;
}
/* }}} */
#endif // GMAGICK_HAVE_SET_IMAGE_PAGE

/* {{{ proto string Gmagick::getImageProfile(string name)
	Returns the named image profile.
*/
PHP_METHOD(gmagick, getimageprofile)
{
	php_gmagick_object *intern;
	char *profile, *name;
	size_t name_len;

	unsigned long length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	profile = (char *)MagickGetImageProfile(intern->magick_wand, name, &length);

	if (profile != (char *)NULL) {
		ZVAL_STRINGL(return_value, profile, length);
		GMAGICK_FREE_MEMORY(char *, profile);
		return;
	}

	GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "Can not get image profile", 1);
}
/* }}} */

/* {{{ proto array Gmagick::getImageRedPrimary()
	Returns the chromaticy red primary point as an array with the keys "x" and "y".
*/
PHP_METHOD(gmagick, getimageredprimary)
{
	php_gmagick_object *intern;
	MagickBool status;
	double x, y;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageRedPrimary(intern->magick_wand, &x, &y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image red primary");
	}

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageRenderingIntent()
	Gets the image rendering intent.
*/
PHP_METHOD(gmagick, getimagerenderingintent)
{
	php_gmagick_object *intern;
	long renderingIntent;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	renderingIntent = MagickGetImageRenderingIntent(intern->magick_wand);
	RETVAL_LONG(renderingIntent);
}
/* }}} */


/* {{{ proto array Gmagick::getImageResolution()
	Gets the image X and Y resolution.
*/
PHP_METHOD(gmagick, getimageresolution)
{
	php_gmagick_object *intern;
	MagickBool status;
	double x, y;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageResolution(intern->magick_wand, &x, &y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image resolution");
	}

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageScene()
	Gets the image scene.
*/
PHP_METHOD(gmagick, getimagescene)
{
	php_gmagick_object *intern;
	unsigned long scene;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	scene = MagickGetImageScene(intern->magick_wand);
	RETVAL_LONG(scene);
}
/* }}} */

/* {{{ proto string Gmagick::getImageSignature()
	Generates an SHA-256 message digest for the image pixel stream.
*/
PHP_METHOD(gmagick, getimagesignature)
{
	php_gmagick_object *intern;
	char *signature;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	signature = MagickGetImageSignature(intern->magick_wand);
	ZVAL_STRING(return_value, signature);
	GMAGICK_FREE_MEMORY(char *, signature);
	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageType()
	Gets the potential image type:
*/
PHP_METHOD(gmagick, getimagetype)
{
	php_gmagick_object *intern;
	long imageType;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	imageType = MagickGetImageType(intern->magick_wand);
	RETVAL_LONG(imageType);
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageIterations(int iterations)
	Sets the image iterations.
*/
PHP_METHOD(gmagick, setimageiterations)
{
	php_gmagick_object *intern;
	zend_long iterations;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &iterations) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageIterations(intern->magick_wand, iterations);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image iterations");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageProfile(string name, string profile)
	Adds a named profile to the Gmagick object
*/
PHP_METHOD(gmagick, setimageprofile)
{
	php_gmagick_object *intern;
	char *name;
	unsigned char*profile;
	size_t profile_len, name_len;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &name, &name_len, &profile, &profile_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageProfile(intern->magick_wand, name, profile, profile_len);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image profile");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageRedPrimary(float x,float y)
	Sets the image chromaticity red primary point.
*/
PHP_METHOD(gmagick, setimageredprimary)
{
	php_gmagick_object *intern;
	double x, y;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageRedPrimary(intern->magick_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image red primary");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageRenderingIntent(int rendering_intent)
	Sets the image rendering intent.
*/
PHP_METHOD(gmagick, setimagerenderingintent)
{
	php_gmagick_object *intern;
	zend_long rendering_intent;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &rendering_intent) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageRenderingIntent(intern->magick_wand, rendering_intent);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image rendering intent");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageResolution(float x_resolution,const float y_resolution)
	Sets the image resolution.
*/
PHP_METHOD(gmagick, setimageresolution)
{
	php_gmagick_object *intern;
	double x_res, y_res;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x_res, &y_res) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageResolution(intern->magick_wand, x_res, y_res);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image resolution");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageScene(int scene)
	Sets the image scene.
*/
PHP_METHOD(gmagick, setimagescene)
{
	php_gmagick_object *intern;
	zend_long scene;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &scene) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageScene(intern->magick_wand, scene);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image scene");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageType(int image_type)
	Sets the image type.
*/
PHP_METHOD(gmagick, setimagetype)
{
	php_gmagick_object *intern;
	zend_long image_type;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &image_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageType(intern->magick_wand, image_type);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image type");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE
/* {{{ proto bool Imagick::setImagePage(int width, int height, int x, int y)
	Sets the page geometry of the image.
*/
PHP_METHOD(gmagick, setimagepage)
{
	php_gmagick_object *intern;
	zend_long width, height, x, y;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &width, &height, &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImagePage(intern->magick_wand, width, height, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image page");
	}
	RETURN_TRUE;
}
/* }}} */
#endif //GMAGICK_HAVE_SET_IMAGE_PAGE 

/* {{{ proto int Gmagick::getImageUnits()
	Gets the image units of resolution.
*/
PHP_METHOD(gmagick, getimageunits)
{
	php_gmagick_object *intern;
	long resolutionType;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	resolutionType = MagickGetImageUnits(intern->magick_wand);
	RETVAL_LONG(resolutionType);
}
/* }}} */

/* {{{ proto array Gmagick::getImageWhitePoint()
	Returns the chromaticy white point as an associative array with the keys "x" and "y".
*/
PHP_METHOD(gmagick, getimagewhitepoint)
{
	php_gmagick_object *intern;
	MagickBool status;
	double x, y;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageWhitePoint(intern->magick_wand, &x, &y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image white point");
	}

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

	return;
}
/* }}} */

/* {{{ proto int Gmagick::getImageWidth()
	Returns the image width.
*/
PHP_METHOD(gmagick, getimagewidth)
{
	php_gmagick_object *intern;
	unsigned long width;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	width = MagickGetImageWidth(intern->magick_wand);
	RETVAL_LONG(width);
}
/* }}} */

/* {{{ proto string Gmagick::getPackageName()
	Returns the ImageMagick package name as a string constant.
*/
PHP_METHOD(gmagick, getpackagename)
{
	char *package_name;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	package_name = (char *)MagickGetPackageName();
	ZVAL_STRING(return_value, package_name);

	/* GMAGICK_FREE_MEMORY(char *, packageName); */
	return;
}
/* }}} */

/* {{{ proto array Gmagick::getQuantumDepth()
	Returns the ImageMagick quantum depth as a string constant.
*/
PHP_METHOD(gmagick, getquantumdepth)
{
	char *quantum_depth;
	unsigned long depth;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	quantum_depth = (char *)MagickGetQuantumDepth(&depth);

	array_init(return_value);
	add_assoc_long(return_value, "quantumDepthLong", depth);
	add_assoc_string(return_value, "quantumDepthString", quantum_depth);

	return;
}
/* }}} */

/* {{{ proto string Gmagick::getReleaseDate()
	Returns the ImageMagick release date as a string constant.
*/
PHP_METHOD(gmagick, getreleasedate)
{
	char *release_date;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	release_date = (char *)MagickGetReleaseDate();
	ZVAL_STRING(return_value, release_date);

	/* GMAGICK_FREE_MEMORY(char *, releaseDate); */
	return;
}
/* }}} */

/* {{{ proto int Gmagick::getResourceLimit(int type)
	Returns the specified resource limit in megabytes.
*/
PHP_METHOD(gmagick, getresourcelimit)
{
	zend_long resource_type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &resource_type) == FAILURE) {
		return;
	}

	RETVAL_LONG(MagickGetResourceLimit(resource_type));
}
/* }}} */

/* {{{ proto array Gmagick::getSamplingFactors()
	Gets the horizontal and vertical sampling factor.
*/
PHP_METHOD(gmagick, getsamplingfactors)
{
	php_gmagick_object *intern;
	double *sampling_factors;
	unsigned long number_factors = 0, i;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	sampling_factors = (double *)MagickGetSamplingFactors(intern->magick_wand, &number_factors);

	array_init(return_value);

	for (i = 0 ; i < number_factors; i++) {
		add_next_index_double(return_value, sampling_factors[i]);
	}

	return;
}
/* }}} */

/* {{{ proto array Gmagick::getSize()
	Returns the size associated with the Gmagick object as an array with the keys "columns" and "rows".
*/
PHP_METHOD(gmagick, getsize)
{
	php_gmagick_object *intern;
	unsigned long columns, rows;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickGetSize(intern->magick_wand, &columns, &rows);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get size");
	}

	array_init(return_value);
	add_assoc_long(return_value, "columns", columns);
	add_assoc_long(return_value, "rows", rows);

	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setImageUnits(int units)
	Sets the image units of resolution.
*/
PHP_METHOD(gmagick, setimageunits)
{
	php_gmagick_object *intern;
	zend_long units;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &units) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageUnits(intern->magick_wand, units);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image units");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */



/* {{{ proto Gmagick Gmagick::setImageWhitePoint(float x,float y)
	Sets the image chromaticity white point.
*/
PHP_METHOD(gmagick, setimagewhitepoint)
{
	php_gmagick_object *intern;
	double x, y;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageWhitePoint(intern->magick_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image white point");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setSamplingFactors(array factors)
	Sets the image sampling factors.
*/
PHP_METHOD(gmagick, setsamplingfactors)
{
	php_gmagick_object *intern;
	MagickBool status;
	zval *factors;
	double *double_array;
	long elements = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &factors) == FAILURE) {
		return;
	}

	double_array = get_double_array_from_zval(factors, &elements TSRMLS_CC);

	if (double_array == (double *)NULL) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "Can't read array", 1);
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	status = MagickSetSamplingFactors(intern->magick_wand, elements, double_array);
	efree(double_array);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set sampling factors");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool Gmagick::setResourceLimit(RESOURCETYPE type, int limit)
	Sets the limit for a particular resource in megabytes.
*/
PHP_METHOD(gmagick, setresourcelimit)
{
	MagickBool status;
	zend_long type, limit;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &type, &limit) == FAILURE) {
		return;
	}
	
	status = MagickSetResourceLimit(type, limit);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "Unable to set resource limit", 1);
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::setSize(int columns, int rows)
	Sets the size of the Gmagick object.  Set it before you read a raw image format such as RGB, GRAY, or CMYK.
*/
PHP_METHOD(gmagick, setsize)
{
	php_gmagick_object *intern;
	zend_long columns, rows;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &columns, &rows) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetSize(intern->magick_wand, columns, rows);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set size");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto array Gmagick::getVersion()
	Returns the ImageMagick API version as a string constant and as a number.
*/
PHP_METHOD(gmagick, getversion)
{
	char *version_string;
	unsigned long version_number;

	version_string = (char *)MagickGetVersion(&version_number);
	array_init(return_value);

	add_assoc_long(return_value, "versionNumber", version_number);
	add_assoc_string(return_value, "versionString", version_string);

	/* GMAGICK_FREE_MEMORY(char *, versionString); */
	return;
}
/* }}} */

/* {{{ proto bool Gmagick::hasNextImage()
	Returns true if the wand has more images when traversing the list in the forward direction
*/
PHP_METHOD(gmagick, hasnextimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickHasNextImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::hasPreviousImage()
	Returns true if the wand has more images when traversing the list in the reverse direction
*/
PHP_METHOD(gmagick, haspreviousimage)
{
	php_gmagick_object *intern;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickHasPreviousImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::implodeImage(float radius )
	Creates a new image that is a copy of an existing one with the image pixels "implode" by the specified percentage. It allocates the memory necessary for the new Image structure and returns a pointer to the new image.
*/
PHP_METHOD(gmagick, implodeimage)
{
	php_gmagick_object *intern;
	double radius;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radius) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickImplodeImage(intern->magick_wand, radius);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to implode image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::labelImage(string label)
	Adds a label to your image.
*/
PHP_METHOD(gmagick, labelimage)
{
	char *label;
	size_t label_len;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &label, &label_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	status = MagickLabelImage(intern->magick_wand, label);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to label image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::levelImage(float blackPoint, float gamma, float whitePoint[, int channel] )
	Adjusts the levels of an image by scaling the colors falling between specified white and black points to the full available quantum range. The parameters provided represent the black, mid, and white points. The black point specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point specifies a gamma correction to apply to the image.  White point specifies the lightest color in the image. Colors brighter than the white point are set to the maximum quantum value.
*/
PHP_METHOD(gmagick, levelimage)
{
	php_gmagick_object *intern;
	double black_point, gamma, white_point;
	MagickBool status;
	zend_long channel = DefaultChannels;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd|l", &black_point, &gamma, &white_point, &channel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	if (channel == DefaultChannels) {
		status = MagickLevelImage(intern->magick_wand, black_point, gamma, white_point);
	} else {
		status = MagickLevelImageChannel(intern->magick_wand, channel, black_point, gamma, white_point);
	}

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to level image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::magnifyImage()
	Is a convenience method that scales an image proportionally to twice its original size.
*/
PHP_METHOD(gmagick, magnifyimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickMagnifyImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to magnify image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::cycleColormapImage(Gmagick map, bool dither)
	Replaces the colors of an image with the closest color from a reference image.
*/
PHP_METHOD(gmagick, mapimage)
{
	php_gmagick_object *intern, *intern_map;
	zval *map_obj;
	zend_bool dither;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ob", &map_obj, php_gmagick_sc_entry, &dither) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	intern_map = Z_GMAGICK_OBJ_P(map_obj);
	status = MagickMapImage(intern->magick_wand, intern_map->magick_wand, dither);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to map image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::medianFilterImage(float radius)
	Applies a digital filter that improves the quality of a noisy image.  Each pixel is replaced by the median in a set of neighboring pixels as defined by radius.
*/
PHP_METHOD(gmagick, medianfilterimage)
{
	php_gmagick_object *intern;
	double radius;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radius) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickMedianFilterImage(intern->magick_wand, radius);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to median filter image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool Gmagick::negateImage(bool gray[, int channel] )
	Negates the colors in the reference image.  The Grayscale option means that only grayscale values within the image are negated.
*/
PHP_METHOD(gmagick, negateimage)
{
	php_gmagick_object *intern;
	zend_bool gray;
	MagickBool status;
	zend_long channel = DefaultChannels;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b|l", &gray, &channel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickNegateImageChannel(intern->magick_wand, channel, gray);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to negate image");
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::minifyImage()
	Is a convenience method that scales an image proportionally to one-half its original size
*/
PHP_METHOD(gmagick, minifyimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickMinifyImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to minify image");
	}

	GMAGICK_CHAIN_METHOD;

}
/* }}} */

/* {{{ proto Gmagick Gmagick::modulateImage(float brightness, float saturation, float hue)
	Lets you control the brightness, saturation, and hue of an image.  Hue is the percentage of absolute rotation from the current position.  For example 50 results in a counter-clockwise rotation of 90 degrees, 150 results in a clockwise rotation of 90 degrees, with 0 and 200 both resulting in a rotation of 180 degrees.
*/
PHP_METHOD(gmagick, modulateimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	double brightness, saturation, hue;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &brightness, &saturation, &hue) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickModulateImage(intern->magick_wand, brightness, saturation, hue);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to modulate image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::motionBlurImage(float radius, float sigma, float angle)
	Simulates motion blur.  We convolve the image with a Gaussian operator of the given radius and standard deviation (sigma). For reasonable results, radius should be larger than sigma.  Use a radius of 0 and MotionBlurImage() selects a suitable radius for you. Angle gives the angle of the blurring motion.
*/
PHP_METHOD(gmagick, motionblurimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	double radius, sigma, angle;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &radius, &sigma, &angle) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickMotionBlurImage(intern->magick_wand, radius, sigma, angle);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to motion blur image");
	}

	GMAGICK_CHAIN_METHOD;


}
/* }}} */

/* {{{ proto bool Gmagick::nextImage()
	Associates the next image in the image list with an Gmagick object.
*/
PHP_METHOD(gmagick, nextimage)
{
	php_gmagick_object *intern;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickNextImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		intern->next_out_of_bound = 1;
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::newImage(int cols, int rows, string color[, string format] )
 	Creates a new image of given size, background color and format
*/
PHP_METHOD(gmagick, newimage)
{
	php_gmagick_object *intern;
	zend_long columns, rows;
	char *param;
	size_t param_len = 0;
	char *format = NULL;
 	size_t format_len = 0;
	char xc_str[MAX_BUFFER_SIZE];

 	/* Parse parameters given to function */
 	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls|s", &columns, &rows, &param, &param_len, &format, &format_len) == FAILURE) {
 		return;
	}
 	intern = Z_GMAGICK_OBJ_P(getThis());
 	
	if (!param_len) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "The color must not be empty", 1);
	}
	snprintf(xc_str, MAX_BUFFER_SIZE, "xc:%s", param);

	if (MagickReadImage(intern->magick_wand, xc_str) == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to create new image");
	}

 	if (MagickScaleImage(intern->magick_wand, columns, rows) == MagickFalse) {
	 	GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to create new image:size problem");
 	}
 	if (format != NULL && format_len > 0) {
	 	if (MagickSetImageFormat(intern->magick_wand, format) == MagickFalse) {
		 	GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to create new image:format problem");
	 	}
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */ 

/* {{{ proto Gmagick Gmagick::normalizeImage([int channel])
	Enhances the contrast of a color image by adjusting the pixels color to span the entire range of colors available
*/
PHP_METHOD(gmagick, normalizeimage)
{
	MagickBool status;
	php_gmagick_object *intern;
	zend_long channel;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &channel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickNormalizeImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to normalize image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::oilPaintImage(float radius)
	Applies a special effect filter that simulates an oil painting.  Each pixel is replaced by the most frequent color occurring in a circular region defined by radius.
*/
PHP_METHOD(gmagick, oilpaintimage)
{
	double radius;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radius) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickOilPaintImage(intern->magick_wand, radius);

	/* No magick is going to happen */
	if (status == MagickFalse)
	{
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to oilpaint image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool Gmagick::previousImage()
	Assocates the previous image in an image list with the Gmagick object.
*/
PHP_METHOD(gmagick, previousimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickPreviousImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		RETURN_FALSE;
	}
	intern->next_out_of_bound = 0;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::profileImage(string name,string profile)
	Adds or removes a ICC, IPTC, or generic profile from an image.  If the profile is NULL, it is removed from the image otherwise added.  Use a name of '*' and a profile of NULL to remove all profiles from the image.
*/
PHP_METHOD(gmagick, profileimage)
{
	php_gmagick_object *intern;
	char *name;
	unsigned char *profile;
	size_t name_len, profile_len;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &name, &name_len, &profile, &profile_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickProfileImage(intern->magick_wand, name, profile, profile_len);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to profile image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::quantizeImage(int numberColors, int colorspace, int treedepth, bool dither,
    bool measureError)
	Analyzes the colors within a reference image
*/
PHP_METHOD(gmagick, quantizeimage)
{
	php_gmagick_object *intern;
	zend_long number_colors, colorspace, tree_depth;
	zend_bool dither, measure_error;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllbb", &number_colors, &colorspace, &tree_depth, &dither, &measure_error) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickQuantizeImage(intern->magick_wand, number_colors, colorspace, tree_depth, dither, measure_error);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to quantize image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::quantizeImages(int number_colors, int colorspace, int treedepth, bool dither,
    bool measure_error)
	Analyzes the colors within a sequence of images
*/
PHP_METHOD(gmagick, quantizeimages)
{
	php_gmagick_object *intern;
	zend_long number_colors, colorspace, tree_depth;
	zend_bool dither, measure_error;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllbb", &number_colors, &colorspace, &tree_depth, &dither, &measure_error) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickQuantizeImages(intern->magick_wand, number_colors, colorspace, tree_depth, dither, measure_error);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to quantize images");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto array Gmagick::(GmagickDraw draw, string text)
   Returns a 7 element array representing the font metrics
*/
PHP_METHOD(gmagick, queryfontmetrics)
{
	zval *objvar;
	php_gmagick_object *intern;
	php_gmagickdraw_object *internd;
	char *text;
	size_t text_len;
	double *metrics;
	MagickWand *temp_wand = NULL;
	MagickWand *font_image_wand = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Os", &objvar, php_gmagickdraw_sc_entry, &text, &text_len) == FAILURE) {
		return;
	}
	intern = Z_GMAGICK_OBJ_P(getThis());
	internd = Z_GMAGICKDRAW_OBJ_P(objvar);
	if (MagickGetNumberImages(intern->magick_wand) == 0) {
		temp_wand = NewMagickWand();
		MagickReadImage(temp_wand, "XC:white");
		MagickScaleImage(temp_wand, 1, 1);
		font_image_wand = temp_wand;
	}
	else {
		font_image_wand = intern->magick_wand;
	}

	metrics = MagickQueryFontMetrics(font_image_wand, internd->drawing_wand, text);
	if (temp_wand != NULL) {
		DestroyMagickWand(temp_wand);
	}
	if (metrics != (double *)NULL) {
		array_init(return_value);
		add_assoc_double(return_value, "characterWidth", metrics[0]);
		add_assoc_double(return_value, "characterHeight", metrics[1]);
		add_assoc_double(return_value, "ascender", metrics[2]);
		add_assoc_double(return_value, "descender", metrics[3]);
		add_assoc_double(return_value, "textWidth", metrics[4]);
		add_assoc_double(return_value, "textHeight", metrics[5]);
		add_assoc_double(return_value, "maximumHorizontalAdvance", metrics[6]);
		GMAGICK_FREE_MEMORY(double *, metrics);
		return;
	} else {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to query font metrics");
	}
}
/* }}} */

/* {{{ proto array Gmagick::queryFonts([string pattern] )
   Returns fonts supported by GraphicsMagick
*/
PHP_METHOD(gmagick, queryfonts)
{
	char **fonts;
	unsigned long num_fonts = 0, i;
	char *pattern = "*";
	size_t pattern_len = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &pattern, &pattern_len) == FAILURE) {
		return;
	}

	fonts = (char **) MagickQueryFonts(pattern, &num_fonts);
	array_init(return_value);

	for (i = 0 ; i < num_fonts ; i++) {
		add_next_index_string(return_value, fonts[i]);
		GMAGICK_FREE_MEMORY(char *, fonts[i]);
	}

	GMAGICK_FREE_MEMORY(char **, fonts);
	return;
}
/* }}} */

/* {{{ proto array Gmagick::queryFormats([string pattern] )
   Returns formats supported by GraphicsMagick
*/
PHP_METHOD(gmagick, queryformats)
{
	char **supported_formats;
	unsigned long num_formats = 0, i;
	char *pattern = "*";
	size_t pattern_len = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &pattern, &pattern_len) == FAILURE) {
		return;
	}

	supported_formats = (char **) MagickQueryFormats(pattern, &num_formats);
	array_init(return_value);

	for (i = 0 ; i < num_formats ; i++) {
		add_next_index_string(return_value, supported_formats[i]);
		GMAGICK_FREE_MEMORY(char *, supported_formats[i]);
	}

	GMAGICK_FREE_MEMORY(char **, supported_formats);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::radialBlurImage(float angle[, int channel])
	Radial blurs an image.
*/
PHP_METHOD(gmagick, radialblurimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	double angle;
	zend_long channel = DefaultChannels;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d|l", &angle, &channel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	// MagickRadialBlurImageChannel still not available in 1.4 
#if GMAGICK_LIB_MASK >= 1005000
	status = MagickRadialBlurImageChannel(intern->magick_wand, channel, angle);	
#else
	status = MagickRadialBlurImage(intern->magick_wand, angle);
#endif
	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to radial blur image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::raiseImage(int width, int height, int x, int y, bool raise)
	Creates a simulated three-dimensional button-like effect by lightening and darkening the edges of the image.  Members width and height of raise_info define the width of the vertical and horizontal edge of the effect.
*/
PHP_METHOD(gmagick, raiseimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	zend_long width, height, x, y;
	zend_bool raise;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllb", &width, &height, &x, &y, &raise) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickRaiseImage(intern->magick_wand, width, height, x, y, raise);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to raise image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::readImageBlob(string image )
    Reads image from a binary string
*/
PHP_METHOD(gmagick, readimageblob)
{
	unsigned char *image_string;
	char *filename = NULL;
	long filename_len;
	size_t image_string_len;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s!", &image_string, &image_string_len, &filename, &filename_len) == FAILURE) {
		return;
	}

	if (image_string_len == 0) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "Zero size image string passed", 1);
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickReadImageBlob(intern->magick_wand, image_string, image_string_len);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to read image blob");
	}

	/* Even if filename is null we need to give a name here. Otherwise segfaults will happen */
	if (!filename)
		filename = "";

	MagickSetImageFilename(intern->magick_wand, filename);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::readImageFile(resource filehandle )
    Reads image from open filehandle
*/
PHP_METHOD(gmagick, readimagefile)
{
	FILE *fp;
	char *filename = NULL;
	size_t filename_len;
	MagickBool status;
	php_gmagick_object *intern;
	zval *zstream;
	php_stream *stream = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|s!", &zstream, &filename, &filename_len) == FAILURE) {
		return;
	}

	php_stream_from_zval(stream, zstream);

	if (php_stream_can_cast(stream, PHP_STREAM_AS_STDIO | PHP_STREAM_CAST_INTERNAL) == FAILURE) {
		RETURN_FALSE;
	}

	if (php_stream_cast(stream, PHP_STREAM_AS_STDIO | PHP_STREAM_CAST_INTERNAL, (void*)&fp, 0) == FAILURE) {
		RETURN_FALSE;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickReadImageFile(intern->magick_wand, fp);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to read image from filepointer");
	}

	MagickSetImageFilename(intern->magick_wand, filename);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::reduceNoiseImage(float radius)
	Smooths the contours of an image
*/
PHP_METHOD(gmagick, reducenoiseimage)
{
	php_gmagick_object *intern;
	double radius;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radius) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickReduceNoiseImage(intern->magick_wand, radius);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to reduce image noise");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::removeImage()
	Removes an image from the image list.
*/
PHP_METHOD(gmagick, removeimage)
{
	MagickBool status;
	php_gmagick_object *intern;

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickRemoveImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to remove image");
	}
	intern->next_out_of_bound = 0;
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto string Gmagick::removeImageProfile(string name)
	Removes the named image profile and returns it
*/
PHP_METHOD(gmagick, removeimageprofile)
{
	php_gmagick_object *intern;
	char *name;
	unsigned char *profile;
	size_t name_len;
	unsigned long profile_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	profile = MagickRemoveImageProfile(intern->magick_wand, name, &profile_len);

	if (profile == (unsigned char *)NULL) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "The image profile does not exist", 1);
	}

	ZVAL_STRING(return_value, (char *)profile);
	GMAGICK_FREE_MEMORY(unsigned char *, profile);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::resampleImage(float x_resolution, float y_resolution, int filter, float blur)
	Resample image to desired resolution.
*/
PHP_METHOD(gmagick, resampleimage)
{
	double xRes, yRes, blur;
	zend_long filter = 0;
	php_gmagick_object *intern;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddld", &xRes, &yRes, &filter, &blur) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	status = MagickResampleImage(intern->magick_wand, xRes, yRes, filter, blur);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to resample image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::rollImage(int x, int y)
	Offsets an image as defined by x and y.
*/
PHP_METHOD(gmagick, rollimage)
{
	zend_long x, y;
	php_gmagick_object *intern;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	status = MagickRollImage(intern->magick_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to roll image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::rotateImage(GmagickPixel background, float degrees)
	Rotates an image the specified number of degrees. Empty triangles left over from rotating the image are filled with the background color.
*/
PHP_METHOD(gmagick, rotateimage)
{
	zval *param;
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	double degrees;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zd", &param, &degrees) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	status = MagickRotateImage(intern->magick_wand, internp->pixel_wand, degrees);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to rotate image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::scaleImage(int cols, int rows[, bool fit[, bool legacy = false]] )
	Scales the size of an image to the given dimensions. Passing zero as either of
	the arguments will preserve dimension while scaling.  If legacy is true, uses the 
	incorrect behaviour that was present until Gmagick 2.0.1. If false (default) it uses the correct
	behaviour.
*/
PHP_METHOD(gmagick, scaleimage)
{
	zend_long x, y, width, height;
	php_gmagick_object *intern;
	MagickBool status;
	zend_bool fit = 0;
	zend_bool legacy = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll|bb", &x, &y, &fit, &legacy) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	
	if (!php_gmagick_thumbnail_dimensions(intern->magick_wand, fit, x, y, &width, &height, legacy)) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to calculate image dimensions");
	}

	status = MagickScaleImage(intern->magick_wand, width, height);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to scale image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::separateImageChannel(int channel)
	Separates a channel from the image
*/
PHP_METHOD(gmagick, separateimagechannel)
{
	php_gmagick_object *intern;
	zend_long channel;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &channel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSeparateImageChannel(intern->magick_wand, channel);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to separate image channel");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::sharpenImage(float radius, float sigma[, int channel])
    Sharpens an image.  We convolve the image with a Gaussian operator of the given radius  and standard deviation (sigma). For reasonable results, the radius should be larger than sigma.  Use a radius of 0 and selects a suitable radius for you.
*/
PHP_METHOD(gmagick, sharpenimage)
{
	double sigma, radius;
	MagickBool status;
	php_gmagick_object *intern;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &radius, &sigma) == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSharpenImage(intern->magick_wand, radius, sigma);
	
	/* No magick is going to happen */
	if (status == MagickFalse) { 
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to sharpen image");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::shearImage(GmagickPixel background, float x_shear, float y_shear)
	Slides one edge of an image along the X or Y axis
*/
PHP_METHOD(gmagick, shearimage)
{
	zval *param;
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	double x_shear, y_shear;
	MagickBool status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zdd", &param, &x_shear, &y_shear) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	status = MagickShearImage(intern->magick_wand, internp->pixel_wand, x_shear, y_shear);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to shear image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::solarizeImage(float threshold)
	Applies a special effect to the image, similar to the effect achieved in a photo darkroom by selectively exposing areas of photo sensitive paper to light.  Threshold ranges from 0 to QuantumRange and is a measure of the extent of the solarization.
*/
PHP_METHOD(gmagick, solarizeimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	zend_long threshold;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &threshold) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSolarizeImage(intern->magick_wand, threshold);

	/* No magick is going to happen */
	if (status == MagickFalse)
	{
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to solarize image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::spreadImage(float radius )
	Special effects method that randomly displaces each pixel in a block defined by the radius parameter.
*/
PHP_METHOD(gmagick, spreadimage)
{
	double radius;
	php_gmagick_object *intern;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radius) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSpreadImage(intern->magick_wand, radius);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to spread image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::stripImage()
	Strips an image of all profiles and comments.
*/
PHP_METHOD(gmagick, stripimage)
{
	php_gmagick_object *intern;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickStripImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to strip image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::swirlImage(float degrees )
	Swirls the pixels about the center of the image, where degrees indicates the sweep of the arc through which each pixel is moved. You get a more dramatic effect as the degrees move from 1 to 360.
*/
PHP_METHOD(gmagick, swirlimage)
{
	double degrees;
	php_gmagick_object *intern;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &degrees) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSwirlImage(intern->magick_wand, degrees);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to swirl image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::textureImage(Gmagick texture_wand)
	Repeatedly tiles the texture image across and down the image canvas.
*/
PHP_METHOD(gmagick, textureimage)
{
	MagickWand *tmp_wand;
	zval *magick_object;
	php_gmagick_object *intern, *intern_second, *intern_return;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &magick_object, php_gmagick_sc_entry) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	intern_second = Z_GMAGICK_OBJ_P(magick_object);
	GMAGICK_CHECK_NOT_EMPTY(intern_second->magick_wand, 1, 1);

	tmp_wand = MagickTextureImage(intern->magick_wand, intern_second->magick_wand);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Texture image failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::trimImage(double fuzz)
	Remove edges that are the background color from the image.
*/
PHP_METHOD(gmagick, trimimage)
{
	double fuzz;
	php_gmagick_object *intern;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &fuzz) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickTrimImage(intern->magick_wand, fuzz);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to trim image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto string Gmagick::__toString()
   Returns the current image as string
*/
PHP_METHOD(gmagick, __tostring)
{
	php_gmagick_object *intern;
	unsigned char *image;
	char *buffer;
	size_t image_size;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	if(MagickGetNumberImages(intern->magick_wand) == 0) {
		ZVAL_STRING(return_value, "");
		return;
	}

	buffer = MagickGetImageFormat(intern->magick_wand);

	if(!buffer) {
		ZVAL_STRING(return_value, "");
		return;
	} else {
		GMAGICK_FREE_MEMORY(char *, buffer);
	}

	image = MagickWriteImageBlob(intern->magick_wand, &image_size);

	ZVAL_STRINGL(return_value, (char *)image, image_size);
	GMAGICK_FREE_MEMORY(unsigned char *, image);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::flattenImages()
	Merges a sequence of images.  This is useful for combining Photoshop layers into a single image.
*/
PHP_METHOD(gmagick, flattenimages)
{
	php_gmagick_object *intern, *intern_return;
	MagickWand *tmp_wand;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	MagickResetIterator(intern->magick_wand);

	tmp_wand = MagickFlattenImages(intern->magick_wand);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Flatten images failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::sampleImage(int cols, int rows[, bool fit[, bool legacy = false]] )
	Sample the size of an image to the given dimensions. Passing zero as either of
	the arguments will preserve dimension while scaling.
	If legacy is true, uses the 
	incorrect behaviour that was present until Gmagick 2.0.1. If false (default) it uses the correct
	behaviour.
*/
PHP_METHOD(gmagick, sampleimage)
{
	zend_long x, y, width, height;
	php_gmagick_object *intern;
	MagickBool status;
	zend_bool fit = 0;
	zend_bool legacy = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll|bb", &x, &y, &fit, &legacy) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	if (!php_gmagick_thumbnail_dimensions(intern->magick_wand, fit, x, y, &width, &height, legacy)) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to calculate image dimensions");
	}

	status = MagickSampleImage(intern->magick_wand, width, height);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to sample image");
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::cloneImage()
	makes an exact copy of the specified wand.
*/
PHP_METHOD(gmagick, cloneimage)
{
	MagickWand *tmp_wand;
	php_gmagick_object *intern, *intern_return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = CloneMagickWand(intern->magick_wand);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Clone image failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::appendImages()
	append a set of images
*/
PHP_METHOD(gmagick, appendimages)
{
	MagickWand *tmp_wand;
	zend_bool stack = 0;
	php_gmagick_object *intern, *intern_return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickAppendImages(intern->magick_wand, stack);

	if (tmp_wand == (MagickWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Append images failed");
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto bool Gmagick::unsharpMaskImage(float radius, float sigma, float amount, float threshold)
	We convolve the image with a Gaussian operator of the given radius and standard deviation (sigma). For reasonable results, radius should be larger than sigma.  Use a radius of 0 and Gmagick::UnsharpMaskImage() selects a suitable radius for you.
*/
PHP_METHOD(gmagick, unsharpmaskimage)
{
	php_gmagick_object *intern;
	double radius, sigma, amount, threshold;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &radius, &sigma, &amount, &threshold) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	if (php_gmagick_ensure_not_empty (intern->magick_wand) == 0)
		return;

		status = MagickUnsharpMaskImage(intern->magick_wand, radius, sigma, amount, threshold);

	if (status == MagickFalse) {
			GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to unsharp mask image");		
		return;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::setResolution(float x_resolution, float y_resolution, float amount, float threshold)
        Sets the image resolution
*/
PHP_METHOD(gmagick, setresolution)
{
        php_gmagick_object *intern;
        MagickBool status;
        double x_resolution, y_resolution;

        /* Parse parameters given to function */
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x_resolution, &y_resolution) == FAILURE) {
                return;
        }

	intern = Z_GMAGICK_OBJ_P(getThis());
        status = MagickSetResolution(intern->magick_wand, x_resolution, y_resolution);

        if (status == MagickFalse) {
                GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set resolution");
                return;
        }
        RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::adaptiveThresholdImage(int width, int height, int offset)
	Selects an individual threshold for each pixel based on the range of intensity values in its local neighborhood.  This allows for thresholding of an image whose global intensity histogram doesn't contain distinctive peaks.
*/
PHP_METHOD(gmagick, adaptivethresholdimage)
{
	php_gmagick_object *intern;
	long width, height, offset;
	unsigned int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &width, &height, &offset) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickAdaptiveThresholdImage(intern->magick_wand, width, height, offset);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to adaptive threshold image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::affineTransformImage(GmagickDraw drawing_wand)
	Transforms an image as dictated by the affine matrix of the drawing wand.
*/
PHP_METHOD(gmagick, affinetransformimage)
{
	zval *objvar;
	php_gmagick_object *intern;
	php_gmagickdraw_object *internd;
	unsigned int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &objvar, php_gmagickdraw_sc_entry) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	internd = Z_GMAGICKDRAW_OBJ_P(objvar);
	status = MagickAffineTransformImage(intern->magick_wand, internd->drawing_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to affine transform image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::averageImages()
	Average a set of images.
*/
PHP_METHOD(gmagick, averageimages)
{
	MagickWand *tmp_wand;
	php_gmagick_object *intern, *intern_return;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickAverageImages(intern->magick_wand);

	if (tmp_wand == NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Averaging images failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);
	return;
}
/* }}} */

/* {{{ proto bool Gmagick::blackThresholdImage(GmagickPixel threshold)
	Is like MagickThresholdImage() but  forces all pixels below the threshold into black while leaving all pixels above the threshold unchanged.
*/
PHP_METHOD(gmagick, blackthresholdimage)
{
	php_gmagick_object *intern;
	zval *param;
	unsigned int status;
	//PixelWand *color_wand;
	php_gmagickpixel_object *color;
	//zend_bool allocated;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	GMAGICK_CAST_PARAMETER_TO_COLOR(param, color, GMAGICK_CLASS);

	status = MagickBlackThresholdImage(intern->magick_wand, color->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to black threshold image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::colordecisionlist(string color_correction_collection)
	Set whether antialiasing should be used for operations. On by default.
*/

PHP_METHOD(gmagick, colordecisionlist)
{
	php_gmagick_object *intern;
	unsigned int status;

	char *color_correction_collection;
	int ccc_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &color_correction_collection, &ccc_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickCdlImage(intern->magick_wand, color_correction_collection);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to colorDecisionListImage" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::clipImage()
	Clips along the first path from the 8BIM profile, if present.
*/
PHP_METHOD(gmagick, clipimage)
{
	php_gmagick_object *intern;
	unsigned int status;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	status = MagickClipImage(intern->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to clip image" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::clipPathImage(string pathname, bool inside)
	Clips along the named paths from the 8BIM profile, if present. Later operations take effect inside the path.  Id may be a number if preceded with #, to work on a numbered path, e.g., "#1" to use the first path.
*/
PHP_METHOD(gmagick, clippathimage)
{
	php_gmagick_object *intern;
	char *clip_path;
	size_t clip_path_len;
	zend_bool inside;
	unsigned int status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sb", &clip_path, &clip_path_len, &inside) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	status = MagickClipPathImage(intern->magick_wand, clip_path, inside);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to clip path image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;

}
/* }}} */

/* {{{ proto bool Gmagick::colorFloodfillImage(GmagickPixel fill, double fuzz, GmagickPixel bordercolor, int x, int y)
	Changes the color value of any pixel that matches target and is an immediate neighbor.
*/
PHP_METHOD(gmagick, colorfloodfillimage)
{
	php_gmagick_object *intern;
	zval *fill_param, *border_param;
	long x, y;
	double fuzz;
	unsigned int status;
	//PixelWand *fill_wand, *border_wand;
	php_gmagickpixel_object *fill;
	php_gmagickpixel_object *border;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zdzll", &fill_param, &fuzz, &border_param, &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(fill_param, fill, GMAGICK_CLASS);
	GMAGICK_CAST_PARAMETER_TO_COLOR(border_param, border, GMAGICK_CLASS);

	status = MagickColorFloodfillImage(intern->magick_wand, fill->pixel_wand, fuzz, border->pixel_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to color floodfill image" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::colorizeImage(GmagickPixel colorize, GmagickPixel opacity)
	Blends the fill color with each pixel in the image. The 'opacity' color is a 
	per channel strength factor for how strongly the color should be applied. If
	legacy is true, the behaviour of this function is incorrect, but consistent 
	with how it behaved before Gmagick version 3.4.0
*/
PHP_METHOD(gmagick, colorizeimage)
{
	php_gmagick_object *intern;
	zval *color_param, *opacity_param;
	unsigned int status;
	php_gmagickpixel_object *color;
	php_gmagickpixel_object *opacity;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &color_param, &opacity_param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	GMAGICK_CAST_PARAMETER_TO_COLOR(color_param, color, GMAGICK_CLASS);
	GMAGICK_CAST_PARAMETER_TO_COLOR(opacity_param, opacity, GMAGICK_CLASS);

	status = MagickColorizeImage(intern->magick_wand, color->pixel_wand, opacity->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to colorize image" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto array Gmagick::compareImageChannels(Gmagick reference, int channel, int metric)
	Compares one or more image channels of an image to a reconstructed image and returns the difference image.
*/
PHP_METHOD(gmagick, compareimagechannels)
{
	MagickWand *tmp_wand;
	zval *objvar;
	php_gmagick_object *intern, *intern_second, *intern_return;
	long channel_type, metric_type;
	double distortion;
#ifdef ZEND_ENGINE_3
	zval new_wand;
#else
	zval *new_wand;
#endif

	zval *pNewWand;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oll", &objvar, php_gmagick_sc_entry, &channel_type, &metric_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	intern_second = Z_GMAGICK_OBJ_P(objvar);
	if (php_gmagick_ensure_not_empty (intern_second->magick_wand) == 0)
		return;

	tmp_wand = MagickCompareImageChannels(intern->magick_wand, intern_second->magick_wand, channel_type, metric_type, &distortion);

	if (!tmp_wand) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Compare image channels failed" TSRMLS_CC);
		return;
	}

#ifdef ZEND_ENGINE_3
	pNewWand = &new_wand;
#else
	MAKE_STD_ZVAL(new_wand);
	pNewWand = new_wand;
#endif
	array_init(return_value);

	object_init_ex(pNewWand, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(pNewWand);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	add_next_index_zval(return_value, pNewWand);
	add_next_index_double(return_value, distortion);

	return;
}
/* }}} */

/* {{{ proto array Gmagick::compareImageChannels(int metric, int distortion)
	Compares one or more images and returns the difference image.
*/
PHP_METHOD(gmagick, compareimages)
{
	MagickWand *tmp_wand;
	zval *objvar;
	php_gmagick_object *intern, *intern_second, *intern_return;
	long metric_type;
	double distortion;
#ifdef ZEND_ENGINE_3
	zval new_wand;
#else
	zval *new_wand;
#endif

	zval *pNewWand;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &objvar, php_gmagick_sc_entry, &metric_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	intern_second = Z_GMAGICK_OBJ_P(objvar);
	if (php_gmagick_ensure_not_empty (intern_second->magick_wand) == 0)
		return;

#ifdef ZEND_ENGINE_3
	pNewWand = &new_wand;
#else
	MAKE_STD_ZVAL(new_wand);
	pNewWand = new_wand;
#endif
	array_init(return_value);

	tmp_wand = MagickCompareImages(intern->magick_wand, intern_second->magick_wand, metric_type, &distortion);

	if (!tmp_wand) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Compare images failed" TSRMLS_CC);
		return;
	}

	object_init_ex(pNewWand, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(pNewWand);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	add_next_index_zval(return_value, pNewWand);
	add_next_index_double(return_value, distortion);

	return;
}
/* }}} */

/* {{{ proto bool Gmagick::contrastImage(bool sharpen)
	Enhances the intensity differences between the lighter and darker elements of the image.  Set sharpen to a value other than 0 to increase the image contrast otherwise the contrast is reduced.
*/
PHP_METHOD(gmagick, contrastimage)
{
	php_gmagick_object *intern;
	unsigned int status;
	zend_bool contrast;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &contrast) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickContrastImage(intern->magick_wand, contrast);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to contrast image" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::convolveImage(array kernel)
	Applies a custom convolution kernel to the image.
*/
PHP_METHOD(gmagick, convolveimage)
{
	php_gmagick_object *intern;
	unsigned int status;
	zval *kernel_array;
	double *kernel;
	unsigned long order = 0;
	long num_elements = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a",  &kernel_array) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	kernel = php_gmagick_zval_to_double_array(kernel_array, &num_elements TSRMLS_CC);

	if (!kernel) {
		zend_throw_exception(php_gmagick_exception_class_entry, "Unable to read matrix array", 1 TSRMLS_CC);
		return;
	}

	order = (unsigned long) sqrt(num_elements);
	status = MagickConvolveImage(intern->magick_wand, order, kernel);
	efree(kernel);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to convolve image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::extentImage(int width, int height, int x, int y )
	Sets the image size
*/
PHP_METHOD(gmagick, extentimage)
{
	php_gmagick_object *intern;
	unsigned int status;
	long width, height, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &width, &height, &x, &y) == FAILURE)
	{
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickExtentImage(intern->magick_wand, width, height, x, y);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to extent image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto string Gmagick::getImageAttribute(string key )
	Returns a named attribute
*/
PHP_METHOD(gmagick, getimageattribute)
{
	php_gmagick_object *intern;
	char *key, *attribute;
	size_t key_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	attribute = MagickGetImageAttribute(intern->magick_wand, key);

	if (!attribute) {
		RETURN_FALSE;
	}

	ZVAL_STRING(return_value, attribute);
	GMAGICK_FREE_MEMORY(char *, attribute);

	return;
}
/* }}} */

/* {{{ proto array Gmagick::getImageChannelExtrema(int channel)
	Gets the extrema for one or more image channels.  Return value is an associative array with the keys "minima" and "maxima".
*/
PHP_METHOD(gmagick, getimagechannelextrema)
{
	php_gmagick_object *intern;
	long channel_type;
	size_t minima, maxima;
	unsigned int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &channel_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageChannelExtrema(intern->magick_wand, channel_type, &minima, &maxima);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image channel extrema" TSRMLS_CC);
		return;
	}

	array_init(return_value);
	add_assoc_long(return_value, "minima", minima);
	add_assoc_long(return_value, "maxima", maxima);

	return;
}
/* }}} */

/* {{{ proto array Gmagick::getImageChannelMean(int channel)
	Gets the mean and standard deviation of one or more image channels.  Return value is an associative array with the keys "mean" and "standardDeviation".
*/
PHP_METHOD(gmagick, getimagechannelmean)
{
	php_gmagick_object *intern;
	long channel_type;
	double mean, standard_deviation;
	unsigned int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &channel_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageChannelMean(intern->magick_wand, channel_type, &mean, &standard_deviation);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image channel mean" TSRMLS_CC);
		return;
	}

	array_init(return_value);
	add_assoc_double(return_value, "mean", mean);
	add_assoc_double(return_value, "standardDeviation", standard_deviation);

	return;
}
/* }}} */

/* {{{ proto GmagickPixel Gmagick::getImageColormapColor(int index, GmagickPixel color)
	Returns the color of the specified colormap index.
*/
PHP_METHOD(gmagick, getimagecolormapcolor)
{
	php_gmagick_object *intern;
	php_gmagickpixel_object *internp;
	unsigned int status;
	PixelWand *tmp_wand;
	long index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = NewPixelWand();
	status = MagickGetImageColormapColor(intern->magick_wand, index , tmp_wand);

	if (tmp_wand == (PixelWand *)NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image colormap color" TSRMLS_CC);
		return;
	}

	if (status == MagickFalse) {
		DestroyPixelWand(tmp_wand);
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to get image colormap color" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
/* {{{ proto int Gmagick::getImageGravity()
	Gets the image gravity
*/
PHP_METHOD(gmagick, getimagegravity)
{
	php_gmagick_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	RETVAL_LONG(MagickGetImageGravity(intern->magick_wand));
}
/* }}} */
#endif

/* {{{ proto int Gmagick::getImageVirtualPixelMethod()
	Returns the virtual pixel method for the sepcified image.
*/
PHP_METHOD(gmagick, getimagevirtualpixelmethod)
{
	php_gmagick_object *intern;
	long pixelMethod;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	pixelMethod = MagickGetImageVirtualPixelMethod(intern->magick_wand);
	RETVAL_LONG(pixelMethod);
}
/* }}} */

/* {{{ proto bool Gmagick::haldClutImage(Gmagick hald[, int CHANNEL])
   Replaces colors in the image from a Hald color lookup table
*/
PHP_METHOD(gmagick, haldclutimage)
{
	zval *objvar;
	unsigned int status;
	php_gmagick_object *intern, *hald;
	//long channel = DefaultChannels;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &objvar, php_gmagick_sc_entry) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	hald = Z_GMAGICK_OBJ_P(objvar);
	if (php_gmagick_ensure_not_empty (hald->magick_wand) == 0)
		return;

	//status = MagickHaldClutImageChannel(intern->magick_wand, channel, hald->magick_wand);
	status = MagickHaldClutImage(intern->magick_wand, hald->magick_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to hald clut image" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::matteFloodfillImage(float alpha,float fuzz,GmagickPixel bordercolor, int x, int y)
	Changes the transparency value of any pixel that matches target and is an immediate neighbor
*/
PHP_METHOD(gmagick, mattefloodfillimage)
{
	php_gmagick_object *intern;
	zval *param;
	long x, y;
	double alpha, fuzz;
	unsigned int status;
	//PixelWand *color_wand;
	php_gmagickpixel_object *color;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddzll", &alpha, &fuzz, &param, &x, &y) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	GMAGICK_CAST_PARAMETER_TO_COLOR(param, color, GMAGICK_CLASS);

	status = MagickMatteFloodfillImage(intern->magick_wand, alpha, fuzz, color->pixel_wand, x, y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to matte floodfill image" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::montageImage(GmagickDraw drawing_wand, string tile_geometry, string thumbnail_geometry, int mode, string frame)
	Creates a composite image by combining several separate images. The images are tiled on the composite image with the name of the image optionally appearing just below the individual tile.
*/

PHP_METHOD(gmagick, montageimage)
{
	MagickWand *tmp_wand;
	zval *objvar;
	php_gmagick_object *intern, *intern_return;
	php_gmagickdraw_object *internd;
	char *tile_geometry, *thumbnail_geometry, *frame;
	size_t tile_geometry_len, thumbnail_geometry_len, frame_len;
	long montage_mode = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ossls", &objvar, php_gmagickdraw_sc_entry,
		&tile_geometry, &tile_geometry_len,
		&thumbnail_geometry, &thumbnail_geometry_len,
		&montage_mode,
		&frame, &frame_len) == FAILURE)
	{
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	internd = Z_GMAGICKDRAW_OBJ_P(objvar);

	tmp_wand = MagickMontageImage(intern->magick_wand, internd->drawing_wand, tile_geometry, thumbnail_geometry, montage_mode, frame);

	if (tmp_wand == NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Montage image failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::morphImages(int number_frames)
	Method morphs a set of images.  Both the image pixels and size are linearly interpolated to give the appearance of a meta-morphosis from one image to the next.
*/
PHP_METHOD(gmagick, morphimages)
{
	MagickWand *tmp_wand;
	php_gmagick_object *intern, *intern_return;
	long frames;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &frames) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickMorphImages(intern->magick_wand, frames);

	if (!tmp_wand) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Morphing images failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;

}
/* }}} */


/* {{{ proto Gmagick Gmagick::mosaicImages()
	Inlays an image sequence to form a single coherent picture.  It returns a wand with each image in the sequence composited at the location defined by the page offset of the image.
*/
PHP_METHOD(gmagick, mosaicimages)
{
	MagickWand *tmp_wand = NULL;
	php_gmagick_object *intern, *intern_return;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	tmp_wand = MagickMosaicImages(intern->magick_wand);

	if (!tmp_wand) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Mosaic image failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;

}
/* }}} */


PHP_METHOD(gmagick, setimageattribute)
{
	php_gmagick_object *intern;
	char *key, *attribute;
	size_t key_len, attribute_len;
	unsigned int status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &attribute, &attribute_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageAttribute(intern->magick_wand, key, attribute);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image attribute" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}

/* {{{ proto bool Gmagick::setImageColormapColor(int index, GmagickPixel color)
	Sets the color of the specified colormap index
*/
PHP_METHOD(gmagick, setimagecolormapcolor)
{
	php_gmagick_object *intern;
	zval *param;
	long index;
	unsigned int status;
	//PixelWand *color_wand;
	php_gmagickpixel_object *color;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &index, &param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, color, GMAGICK_CLASS);

	status = MagickSetImageColormapColor(intern->magick_wand, index, color->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image color map color" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;

}
/* }}} */
#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
/* {{{ proto bool Gmagick::setImageGravity(int GRAVITY)
	Sets the image gravity
*/
PHP_METHOD(gmagick, setimagegravity)
{
	php_gmagick_object *intern;
	unsigned int status;
	long gravity;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &gravity) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageGravity(intern->magick_wand, gravity);

	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image gravity" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */
#endif

/* {{{ proto bool Gmagick::setImageMatteColor(GmagickPixel matte)
	Sets the image matte color.
*/
PHP_METHOD(gmagick, setimagemattecolor)
{
	zval *param;
	php_gmagick_object *intern;
	unsigned int status;
	php_gmagickpixel_object *color;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, color, GMAGICK_CLASS);

	status = MagickSetImageMatteColor(intern->magick_wand, color->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image matte color" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::setImageVirtualPixelMethod(int method)
	Sets the image virtual pixel method.
*/
PHP_METHOD(gmagick, setimagevirtualpixelmethod)
{
	php_gmagick_object *intern;
	long virtual_pixel;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &virtual_pixel) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	MagickSetImageVirtualPixelMethod(intern->magick_wand, virtual_pixel);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::shaveImage(int columns, int rows)
	Shaves pixels from the image edges.  It allocates the memory necessary for the new Image structure and returns a pointer to the new image.
*/
PHP_METHOD(gmagick, shaveimage)
{
	php_gmagick_object *intern;
	long columns, rows;
	unsigned int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &columns, &rows) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickShaveImage(intern->magick_wand, columns, rows);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to shave image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::steganoImage(Gmagick watermark_wand, int offset)
	Hides a digital watermark within the image. Recover the hidden watermark later to prove that the authenticity of an image.  Offset defines the start position within the image to hide the watermark.
*/
PHP_METHOD(gmagick, steganoimage)
{
	zval *objvar;
	php_gmagick_object *intern, *intern_second, *intern_return;
	long offset;
	MagickWand *tmp_wand;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &objvar, php_gmagick_sc_entry, &offset) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	intern_second = Z_GMAGICK_OBJ_P(objvar);
	if (php_gmagick_ensure_not_empty (intern_second->magick_wand) == 0)
		return;

	tmp_wand = MagickSteganoImage(intern->magick_wand, intern_second->magick_wand, offset);

	if (!tmp_wand) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Stegano image failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);
	return;
}
/* }}} */

/* {{{ proto Gmagick Gmagick::stereoImage(Gmagick offset_wand)
	Composites two images and produces a single image that is the composite of a left and right image of a stereo pair
*/
PHP_METHOD(gmagick, stereoimage)
{
	MagickWand *tmp_wand;
	zval *magick_object;
	php_gmagick_object *intern, *intern_second, *intern_return;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &magick_object, php_gmagick_sc_entry) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	intern_second = Z_GMAGICK_OBJ_P(magick_object);
	if (php_gmagick_ensure_not_empty (intern_second->magick_wand) == 0)
		return;

	tmp_wand = MagickStereoImage(intern->magick_wand, intern_second->magick_wand);

	if (tmp_wand == NULL) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Stereo image failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);
	GMAGICK_REPLACE_MAGICKWAND(intern_return, tmp_wand);

	return;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::transformimage(string crop, string geometry )
	Comfortability method for crop and resize
*/
PHP_METHOD(gmagick, transformimage)
{
	char *crop, *geometry;
	size_t crop_len, geometry_len;
	MagickWand *transformed;
	php_gmagick_object *intern, *intern_return;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &crop, &crop_len, &geometry, &geometry_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	transformed = MagickTransformImage(intern->magick_wand, crop, geometry);

	if (!transformed) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Transforming image failed" TSRMLS_CC);
		return;
	}

	object_init_ex(return_value, php_gmagick_sc_entry);
	intern_return = Z_GMAGICK_OBJ_P(return_value);

	GMAGICK_REPLACE_MAGICKWAND(intern_return, transformed);
	return;
}
/* }}} */


/* {{{ proto bool Gmagick::waveImage(float amplitude, float length )
	Adds wave filter to the image.
*/
PHP_METHOD(gmagick, waveimage)
{
	double amplitude, wave_length;
	php_gmagick_object *intern;
	unsigned int status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &amplitude, &wave_length) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickWaveImage(intern->magick_wand, amplitude, wave_length);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to wave image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::whiteThresholdImage(GmagickPixel threshold)
	Is like ThresholdImage() but  force all pixels above the threshold into white while leaving all pixels below the threshold unchanged.
*/
PHP_METHOD(gmagick, whitethresholdimage)
{
	php_gmagick_object *intern;
	zval *param;
	unsigned int status;
	php_gmagickpixel_object *color;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, color, GMAGICK_CLASS);

	status = MagickWhiteThresholdImage(intern->magick_wand, color->pixel_wand);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to white threshold image" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto array Gmagick::getimageboundingbox(float fuzz)
	MagickGetImageBoundingBox() obtains the crop bounding box required to remove a solid-color border from the image. Color quantums which differ less than the fuzz setting are considered to be the same. If a border is not detected, then the the original image dimensions are returned. The crop bounding box estimation uses the same algorithm as MagickTrimImage().
*/
PHP_METHOD(gmagick, getimageboundingbox)
{
	php_gmagick_object *intern;
	double fuzz;
	MagickBool status;

	unsigned long width, height;
	long x, y; 


	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &fuzz) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickGetImageBoundingBox(intern->magick_wand, fuzz, &width, &height, &x, &y);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image channel depth");
	}


	array_init(return_value);
	add_assoc_double(return_value, "width", width);
	add_assoc_double(return_value, "height", height);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
}
/* }}} */


/* {{{ proto float Gmagick::getimagefuzz()
	MagickGetImageFuzz() returns the color comparison fuzz factor. Colors closer than the fuzz factor are considered to be the same when comparing colors. Note that some other functions such as MagickColorFloodfillImage() implicitly set this value.
*/
PHP_METHOD(gmagick, getimagefuzz)
{
	php_gmagick_object *intern;
	double fuzz;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	fuzz = MagickGetImageFuzz(intern->magick_wand);

	RETURN_DOUBLE(fuzz);
}
/* }}} */

/* {{{ proto int Gmagick::getimagesavedtype()
	MagickGetImageSavedType() gets the image type that will be used when the image is saved. This may be different to the current image type, returned by MagickGetImageType().
	IMGTYPE_*
*/
PHP_METHOD(gmagick, getimagesavedtype)
{
	php_gmagick_object *intern;
	ImageType type;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	type = MagickGetImageSavedType(intern->magick_wand);

	RETURN_LONG(type);
}
/* }}} */

#if !defined(MagickSetDepth)
unsigned int MagickSetDepth(MagickWand *wand,const size_t depth);
#endif //!defined(MagickSetDepth)


/* {{{ proto Gmagick Gmagick::setDepth(int depth)
	MagickSetDepth() sets the sample depth to be used when reading from a raw image or a format which requires that the depth be specified in advance by the user.
*/
PHP_METHOD(gmagick, setdepth)
{
	php_gmagick_object *intern;
	long depth;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &depth) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetDepth(intern->magick_wand, depth);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set depth");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto Gmagick Gmagick::setImageFuzz(float fuzz)
	MagickSetImageFuzz() sets the color comparison fuzz factor. Colors closer than the fuzz factor are considered to be the same when comparing colors. Note that some other functions such as MagickColorFloodfillImage() implicitly set this value.
*/
PHP_METHOD(gmagick, setimagefuzz)
{
	php_gmagick_object *intern;
	double fuzz;
	MagickBool status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &fuzz) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	status = MagickSetImageFuzz(intern->magick_wand, fuzz);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set image channel depth");
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool Gmagick::setimageoption(string format, string key, string value)
	MagickSetImageOption() associates one or options with a particular image format (.e.g MagickSetImageOption(wand,"jpeg","preserve-settings","true").
	
	"jpeg","preserve-settings","true").
*/
PHP_METHOD(gmagick, setimageoption)
{
	php_gmagick_object *intern;
	char *format, *key, *value;
	size_t format_len, key_len, value_len;
	unsigned int	 status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", 
			&format, &format_len,
			&key, &key_len,
			&value, &value_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());

	status = MagickSetImageOption(intern->magick_wand, format, key, value);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set format" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::setimagesavedtype(int type)
	MagickSetImageSavedType() sets the image type that will be used when the image is saved.
*/
PHP_METHOD(gmagick, setimagesavedtype)
{
	php_gmagick_object *intern;
	long type;
	unsigned int status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &type) == FAILURE) {
		return;
	}

	//TODO - check type is known?

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetImageSavedType(intern->magick_wand, type);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set format" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::setFormat(string format)
	Sets the format of the Gmagick object.
	unsigned int MagickSetFormat( MagickWand *wand, const char *format );

MagickSetFormat() sets the file or blob format (e.g. "BMP") to be used when a file or blob is read. Usually this is not necessary because GraphicsMagick is able to auto-detect the format based on the file header (or the file extension), but some formats do not use a unique header or the selection may be ambigious. Use MagickSetImageFormat() to set the format to be used when a file or blob is to be written.
*/
PHP_METHOD(gmagick, setformat)
{
	php_gmagick_object *intern;
	char *format;
	size_t format_len;
	unsigned int  status;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &format, &format_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetFormat(intern->magick_wand, format);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set format" TSRMLS_CC);
		return;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool Gmagick::setresolutionunits(int RESOLUTION_TYPE)
	MagickSetResolutionUnits() sets the resolution units of the magick wand. It should be used in conjunction with MagickSetResolution(). This method works both before and after an image has been read.

Also see MagickSetImageUnits() which specifies the units which apply to the image resolution setting after an image has been read.
*/
PHP_METHOD(gmagick, setresolutionunits)
{
	php_gmagick_object *intern;
	unsigned int status;
	int resolution_type;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &resolution_type) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	status = MagickSetResolutionUnits(intern->magick_wand, resolution_type);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to set resolution" TSRMLS_CC);
		return;
	}
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool Gmagick::writeImageFile(resource $handle[, string $format])
	Writes image to an open filehandle. Optional parameter format defines the format the file
	is stored with
*/
PHP_METHOD(gmagick, writeimagefile)
{
	php_gmagick_object *intern;
	zval *zstream;
	php_stream *stream;
	zend_bool result;
	char *format = NULL;
	size_t format_len;
	char *orig_name = NULL, *buffer;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|s!", &zstream, &format, &format_len) == FAILURE) {
		return;
	}

	intern = Z_GMAGICK_OBJ_P(getThis());
	GMAGICK_CHECK_NOT_EMPTY(intern->magick_wand, 1, 1);

	// Get the current name
	if (format) {
		orig_name = MagickGetImageFilename(intern->magick_wand);

		spprintf (&buffer, 0, "%s:", format);
		MagickSetImageFilename (intern->magick_wand, buffer);
		efree (buffer);
	}

	php_stream_from_zval(stream, zstream);
	result = php_gmagick_stream_handler(intern, stream, GmagickWriteImageFile TSRMLS_CC);

	/* Restore the original name after write */
	if (orig_name) {
		MagickSetImageFilename(intern->magick_wand, orig_name);
		MagickRelinquishMemory(orig_name);
	}

	if (result == 0) {
		if (!EG(exception)) {
			GMAGICK_THROW_GMAGICK_EXCEPTION(intern->magick_wand, "Unable to write image to the filehandle" TSRMLS_CC);
			return;
		}
		return;
	}
	RETURN_TRUE;
}
/* }}} */

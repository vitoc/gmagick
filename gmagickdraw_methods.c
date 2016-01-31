/**
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
   |         Vito Chin <vito@php.net>		                              |
   +----------------------------------------------------------------------+
*/

#include "php_gmagick.h"
#include "php_gmagick_macros.h"
#include "php_gmagick_helpers.h"

/* {{{ proto GmagickDraw GmagickDraw::setStrokeColor(PixelWand stroke_wand)
	Sets the color used for stroking object outlines.
*/
PHP_METHOD(gmagickdraw, setstrokecolor)
{
	zval *param;
	php_gmagickdraw_object *internd;
	php_gmagickpixel_object *internp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 2);

	if (internd->drawing_wand != NULL) {
		DrawSetStrokeColor(internd->drawing_wand, internp->pixel_wand);
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setStrokeWidth(float stroke_width)
	Sets the width of the stroke used to draw object outlines.
*/
PHP_METHOD(gmagickdraw, setstrokewidth)
{
	php_gmagickdraw_object *internd;
	double width;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &width) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	if (internd->drawing_wand != NULL) {
		DrawSetStrokeWidth(internd->drawing_wand, width);
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::ellipse(float ox, float oy, float rx, float ry, float start, float end)
	Draws an ellipse on the image.
*/
PHP_METHOD(gmagickdraw, ellipse)
{
	double ox, oy, rx, ry, start, end;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &ox, &oy, &rx, &ry, &start, &end) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawEllipse(internd->drawing_wand, ox, oy, rx, ry, start, end);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::annotate(float x, float y, string *text)
	Draws text on the image.
*/
PHP_METHOD(gmagickdraw, annotate)
{
	php_gmagickdraw_object *internd;
	double x, y;
	unsigned char *text;
	size_t text_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dds", &x, &y, &text, &text_len) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawAnnotation(internd->drawing_wand, x, y, text);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::affine(array affine)
	Adjusts the current affine transformation matrix with the specified affine transformation matrix. Note that the current affine transform is adjusted rather than replaced.
*/
PHP_METHOD(gmagickdraw, affine)
{
	php_gmagickdraw_object *internd;
	zval *affine_matrix, *current;
	HashTable *affine;
	char *matrix_elements[] = { "sx", "rx", "ry",
							"sy", "tx", "ty" };
	int i = 0;
	double value;
	AffineMatrix *pmatrix;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &affine_matrix) == FAILURE) {
		return;
	}

	/* Allocate space to build matrix */
	pmatrix = emalloc(sizeof(AffineMatrix));

	affine = HASH_OF(affine_matrix);

	ZEND_HASH_FOREACH_VAL(affine, current) {
		if (i >= 6) {
			break;
		} else if (!current) {
			efree(pmatrix);
			GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "AffineMatrix should contain keys: sx, rx, ry, sy, tx and ty", 2);
		} else {
			value = zval_get_double(current);

			if (strcmp(matrix_elements[i], "sx") == 0) {
				pmatrix->sx = value;
			} else if (strcmp(matrix_elements[i], "rx") == 0) {
				pmatrix->rx = value;
			} else if (strcmp(matrix_elements[i], "ry") == 0) {
				pmatrix->ry = value;
			} else if (strcmp(matrix_elements[i], "sy") == 0) {
				pmatrix->sy = value;
			} else if (strcmp(matrix_elements[i], "tx") == 0) {
				pmatrix->tx = value;
			} else if (strcmp(matrix_elements[i], "ty") == 0) {
				pmatrix->ty = value;
			}
		}

		i++;
	} ZEND_HASH_FOREACH_END();
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawAffine(internd->drawing_wand, pmatrix);
	efree(pmatrix);

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::arc(float sx, float sy, float ex, float ey, float sd, float ed)
	Draws an arc falling within a specified bounding rectangle on the image.
*/
PHP_METHOD(gmagickdraw, arc)
{
	double sx, sy, ex, ey, sd, ed;
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &sx, &sy, &ex, &ey, &sd, &ed) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawArc(internd->drawing_wand, sx, sy, ex, ey, sd, ed);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::bezier(array coordinates)
	Draws a bezier curve through a set of points on the image.
*/
PHP_METHOD(gmagickdraw, bezier)
{

	zval *coordinate_array;
	php_gmagickdraw_object *internd;
	PointInfo *coordinates;
	int num_elements = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &coordinate_array) == FAILURE) {
		return;
	}
	coordinates = get_pointinfo_array(coordinate_array, &num_elements TSRMLS_CC);

	if (coordinates == (PointInfo *)NULL) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Unable to read coordinate array", 2);
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawBezier(internd->drawing_wand, num_elements, coordinates);

	efree(coordinates);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickPixel GmagickDraw::getFillColor()
	Returns the fill color used for drawing filled objects.
*/
PHP_METHOD(gmagickdraw, getfillcolor)
{
	php_gmagickpixel_object *internp;
	php_gmagickdraw_object *internd;
	PixelWand *tmp_wand;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	
	tmp_wand = NewPixelWand();
	DrawGetFillColor(internd->drawing_wand, tmp_wand);

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto float GmagickDraw::getFillOpacity()
	Returns the opacity used when drawing using the fill color or fill texture. Fully opaque is 1.0.
*/
PHP_METHOD(gmagickdraw, getfillopacity)
{
	php_gmagickdraw_object *internd;
	double opacity;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	opacity = DrawGetFillOpacity(internd->drawing_wand);

	RETVAL_DOUBLE(opacity);
}
/* }}} */

/* {{{ proto string GmagickDraw::getFont()
	Returns a null-terminaged string specifying the font used when annotating with text. The value returned must be freed by the user when no longer needed.
*/
PHP_METHOD(gmagickdraw, getfont)
{
	php_gmagickdraw_object *internd;
	char *font;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	font = DrawGetFont(internd->drawing_wand);
	if(font == (char *)NULL || *font == '\0') {
		RETURN_FALSE;
	} else {
		ZVAL_STRING(return_value, font);
		GMAGICK_FREE_MEMORY(char *, font);
		return;
	}
}
/* }}} */

/* {{{ proto float GmagickDraw::getFontSize()
	Returns the font pointsize used when annotating with text.
*/
PHP_METHOD(gmagickdraw, getfontsize)
{
	php_gmagickdraw_object *internd;
	double font_size;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	font_size = DrawGetFontSize(internd->drawing_wand);
	ZVAL_DOUBLE(return_value, font_size);
	return;
}
/* }}} */

/* {{{ proto int GmagickDraw::getFontStyle()
	Returns the font style used when annotating with text.
*/
PHP_METHOD(gmagickdraw, getfontstyle)
{
	php_gmagickdraw_object *internd;
	long font_style;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	font_style = DrawGetFontStyle(internd->drawing_wand);
	ZVAL_LONG(return_value, font_style);
	return;
}
/* }}} */

/* {{{ proto int GmagickDraw::getFontWeight()
	Returns the font weight used when annotating with text.
*/
PHP_METHOD(gmagickdraw, getfontweight)
{
	php_gmagickdraw_object *internd;
	long weight;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	weight = DrawGetFontWeight(internd->drawing_wand);
	ZVAL_LONG(return_value, weight);
	return;
}
/* }}} */

/* {{{ proto float GmagickDraw::getStrokeOpacity()
	Returns the opacity of stroked object outlines.
*/
PHP_METHOD(gmagickdraw, getstrokeopacity)
{
	php_gmagickdraw_object *internd;
	double opacity;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	opacity = DrawGetStrokeOpacity(internd->drawing_wand);

	RETVAL_DOUBLE(opacity);
}
/* }}} */

/* {{{ proto GmagickPixel GmagickDraw::getStrokeColor(PixelWand stroke_color)
	Returns the color used for stroking object outlines.
*/
PHP_METHOD(gmagickdraw, getstrokecolor)
{
	php_gmagickpixel_object *internp;
	php_gmagickdraw_object *internd;
	PixelWand *tmp_wand;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	tmp_wand = NewPixelWand();
	DrawGetStrokeColor(internd->drawing_wand, tmp_wand);

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto float GmagickDraw::getStrokeWidth()
	Returns the width of the stroke used to draw object outlines.
*/
PHP_METHOD(gmagickdraw, getstrokewidth)
{
	php_gmagickdraw_object *internd;
	double width;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	width = DrawGetStrokeWidth(internd->drawing_wand);

	RETVAL_DOUBLE(width);
}
/* }}} */

/* {{{ proto int GmagickDraw::getTextDecoration()
	Returns the decoration applied when annotating with text.
*/
PHP_METHOD(gmagickdraw, gettextdecoration)
{
	php_gmagickdraw_object *internd;
	long decoration;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	decoration = DrawGetTextDecoration(internd->drawing_wand);
	ZVAL_LONG(return_value, decoration);
	return;
}
/* }}} */

/* {{{ proto string GmagickDraw::getTextEncoding()
	Returns a null-terminated string which specifies the code set used for text annotations. The string must be freed by the user once it is no longer required.
*/
PHP_METHOD(gmagickdraw, gettextencoding)
{
	php_gmagickdraw_object *internd;
	char *encoding;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	encoding = DrawGetTextEncoding(internd->drawing_wand);

	if(encoding == (char *)NULL || *encoding == '\0') {
		RETURN_FALSE;
	} else {
		ZVAL_STRING(return_value, encoding);
		GMAGICK_FREE_MEMORY(char *, encoding);
		return;
	}
}
/* }}} */

/* {{{ proto bool GmagickDraw::line(float sx, float sy, float ex, float ey)
	Draws a line on the image using the current stroke color, stroke opacity, and stroke width.
*/
PHP_METHOD(gmagickdraw, line)
{
	php_gmagickdraw_object *internd;
	double sx, sy, ex, ey;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &sx, &sy, &ex, &ey) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawLine(internd->drawing_wand, sx, sy, ex, ey);
	GMAGICK_CHAIN_METHOD;
	
}
/* }}} */

/* {{{ proto bool GmagickDraw::point(float x, float y)
	Draws a point using the current stroke color and stroke thickness at the specified coordinates.
*/
PHP_METHOD(gmagickdraw, point)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawPoint(internd->drawing_wand, x, y);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::polygon(array coordinates)
	Draws a polygon using the current stroke, stroke width, and fill color or texture, using the specified array of coordinates.
*/
PHP_METHOD(gmagickdraw, polygon)
{
	zval *coordinate_array;
	php_gmagickdraw_object *internd;
	PointInfo *coordinates;
	int num_elements = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &coordinate_array) == FAILURE) {
		return;
	}

	coordinates = get_pointinfo_array(coordinate_array, &num_elements TSRMLS_CC);

	if (coordinates == (PointInfo *)NULL) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Unable to read coordinate array", 2);
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawPolygon(internd->drawing_wand, num_elements, coordinates);

	efree(coordinates);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::polyline(array coordinates)
	Draws a polyline using the current stroke, stroke width, and fill color or texture, using the specified array of coordinates.
*/
PHP_METHOD(gmagickdraw, polyline)
{
	zval *coordinate_array;
	php_gmagickdraw_object *internd;
	PointInfo *coordinates;
	int num_elements = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &coordinate_array) == FAILURE) {
		return;
	}

	coordinates = get_pointinfo_array(coordinate_array, &num_elements TSRMLS_CC);

	if (coordinates == (PointInfo *)NULL) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Unable to read coordinate array", 2);
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawPolyline(internd->drawing_wand, num_elements, coordinates);

	efree(coordinates);
	GMAGICK_CHAIN_METHOD;

}
/* }}} */

/* {{{ proto bool GmagickDraw::rectangle(float x1, float y1, float x2, float y2)
	Draws a rectangle given two coordinates and using the current stroke, stroke width, and fill settings.
*/
PHP_METHOD(gmagickdraw, rectangle)
{
	double x1, y1, x2, y2;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x1, &y1, &x2, &y2) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawRectangle(internd->drawing_wand, x1, y1, x2, y2);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::rotate(float degrees)
	Applies the specified rotation to the current coordinate space.
*/
PHP_METHOD(gmagickdraw, rotate)
{
	php_gmagickdraw_object *internd;
	double degrees;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &degrees) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawRotate(internd->drawing_wand, degrees);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::roundRectangle(float x1, float y1, float x2, float y2, float rx, float ry)
	Draws a rounted rectangle given two coordinates, x & y corner radiuses and using the current stroke, stroke width, and fill settings.
*/
PHP_METHOD(gmagickdraw, roundrectangle)
{
	double x1, y1, x2, y2, rx, ry;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &x1, &y1, &x2, &y2, &rx, &ry) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawRoundRectangle(internd->drawing_wand, x1, y1, x2, y2, rx, ry);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::scale(float x, float y)
	Adjusts the scaling factor to apply in the horizontal and vertical directions to the current coordinate space.
*/
PHP_METHOD(gmagickdraw, scale)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawScale(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* {{{ proto bool GmagickDraw::setFillColor(PixelWand fill_wand)
	Sets the fill color to be used for drawing filled objects.
*/
PHP_METHOD(gmagickdraw, setfillcolor)
{
	zval *param;
	php_gmagickdraw_object *internd;
	php_gmagickpixel_object *internp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 2);
	DrawSetFillColor(internd->drawing_wand, internp->pixel_wand);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setFillOpacity(float fillOpacity)
	Sets the opacity to use when drawing using the fill color or fill texture. Fully opaque is 1.0.
*/
PHP_METHOD(gmagickdraw, setfillopacity)
{
	php_gmagickdraw_object *internd;
	double fillOpacity;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &fillOpacity) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetFillOpacity(internd->drawing_wand, fillOpacity);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setFont(string font_name)
	Sets the fully-sepecified font to use when annotating with text.
*/
PHP_METHOD(gmagickdraw, setfont)
{
	php_gmagickdraw_object *internd;
	char *font, *absolute;
	size_t font_len;
	int error = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &font, &font_len) == FAILURE) {
		return;
	}

	/* Check that no empty string is passed */
	if (font_len == 0) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Can not set empty font", 2);
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	/* And if it wasn't */
	if (!check_configured_font(font, font_len TSRMLS_CC)) {

		if (!(absolute = expand_filepath(font, NULL TSRMLS_CC))) {
			GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Unable to set font", 2);
		}

		/* Do a safe-mode check for the font */
		GMAGICK_SAFE_MODE_CHECK(absolute, error);
		GMAGICKDRAW_CHECK_READ_OR_WRITE_ERROR(internd, absolute, error, GMAGICK_FREE_FILENAME);

		if (VCWD_ACCESS(absolute, F_OK|R_OK)) {
			zend_throw_exception_ex(php_gmagickdraw_exception_class_entry, 2 TSRMLS_CC,
				"The given font is not found in the GraphicsMagick configuration and the file (%s) is not accessible", absolute);

			efree(absolute);
			return;
		}

		DrawSetFont(internd->drawing_wand, absolute);
		efree(absolute);

	} else {
		DrawSetFont(internd->drawing_wand, font);
	}

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setFontSize(float pointsize)
	Sets the font pointsize to use when annotating with text.
*/
PHP_METHOD(gmagickdraw, setfontsize)
{
	php_gmagickdraw_object *internd;
	double font_size;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &font_size) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetFontSize(internd->drawing_wand, font_size);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setFontStyle(int style)
	Sets the font style to use when annotating with text. The AnyStyle enumeration acts as a wild-card "don't care" option.
*/
PHP_METHOD(gmagickdraw, setfontstyle)
{
	php_gmagickdraw_object *internd;
	zend_long style_id = AnyStyle;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &style_id) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetFontStyle(internd->drawing_wand, style_id);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setFontWeight(int font_weight)
	Sets the font weight to use when annotating with text.
*/
PHP_METHOD(gmagickdraw, setfontweight)
{
	php_gmagickdraw_object *internd;
	zend_long weight;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &weight) == FAILURE) {
		return;
	}

	if (weight >= 100 && weight <= 900) {

		internd = Z_GMAGICKDRAW_OBJ_P(getThis());

		DrawSetFontWeight(internd->drawing_wand, weight);
		GMAGICK_CHAIN_METHOD;

	} else {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Font weight valid range is 100-900", 2);
	}
}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeOpacity(float stroke_opacity)
	Specifies the opacity of stroked object outlines.
*/
PHP_METHOD(gmagickdraw, setstrokeopacity)
{
	php_gmagickdraw_object *internd;
	double opacity;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &opacity) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeOpacity(internd->drawing_wand, opacity);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setTextDecoration(int decoration)
	Specifies a decoration to be applied when annotating with text.
*/
PHP_METHOD(gmagickdraw, settextdecoration)
{
	php_gmagickdraw_object *internd;
	zend_long decoration;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &decoration) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetTextDecoration(internd->drawing_wand, decoration);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{ proto bool GmagickDraw::setGravity(int GRAVITY)
   Sets the gravity value
*/
PHP_METHOD(gmagickdraw, setgravity)
{
	php_gmagickdraw_object *internd;
	zend_long gravity;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &gravity) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetGravity(internd->drawing_wand, gravity);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{ proto int GmagickDraw::getGravity()
   Gets the gravity value
*/
PHP_METHOD(gmagickdraw, getgravity)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	RETVAL_LONG(DrawGetGravity(internd->drawing_wand));
}
/* }}} */

/* {{{ proto bool GmagickDraw::setTextEncoding(string encoding)
	Specifies specifies the code set to use for text annotations. The only character encoding which may be specified at this time is "UTF-8" for representing Unicode as a sequence of bytes. Specify an empty string to set text encoding to the system's default. Successful text annotation using Unicode may require fonts designed to support Unicode.
*/
PHP_METHOD(gmagickdraw, settextencoding)
{
	php_gmagickdraw_object *internd;
	char *encoding;
	size_t encoding_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &encoding, &encoding_len) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetTextEncoding(internd->drawing_wand, encoding);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeAntialias(bool stroke_antialias)
	Controls whether stroked outlines are antialiased. Stroked outlines are antialiased by default.  When antialiasing is disabled stroked pixels are thresholded to determine if the stroke color or underlying canvas color should be used.
*/
PHP_METHOD(gmagickdraw, setstrokeantialias)
{
	php_gmagickdraw_object *internd;
	zend_bool antialias;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &antialias) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeAntialias(internd->drawing_wand, antialias);
		GMAGICK_CHAIN_METHOD;

}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeDashOffset(float dash_offset)
	Specifies the offset into the dash pattern to start the dash.
*/
PHP_METHOD(gmagickdraw, setstrokedashoffset)
{
	php_gmagickdraw_object *internd;
	double offset;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &offset) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeDashOffset(internd->drawing_wand, offset);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeLineCap(int linecap)
	Specifies the shape to be used at the end of open subpaths when they are stroked. Values of LineCap are UndefinedCap, ButtCap, RoundCap, and SquareCap.
*/
PHP_METHOD(gmagickdraw, setstrokelinecap)
{
	php_gmagickdraw_object *internd;
	zend_long line_cap;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &line_cap) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeLineCap(internd->drawing_wand, line_cap);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeLineJoin(int linejoin)
	Specifies the shape to be used at the corners of paths (or other vector shapes) when they are stroked. Values of LineJoin are UndefinedJoin, MiterJoin, RoundJoin, and BevelJoin.
*/
PHP_METHOD(gmagickdraw, setstrokelinejoin)
{	
	php_gmagickdraw_object *internd;
	zend_long line_join;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &line_join) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeLineJoin(internd->drawing_wand, line_join);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeMiterLimit(int miterlimit)
	Specifies the miter limit. When two line segments meet at a sharp angle and miter joins have been specified for 'lineJoin', it is possible for the miter to extend far beyond the thickness of the line stroking the path. The miterLimit' imposes a limit on the ratio of the miter length to the 'lineWidth'.
*/
PHP_METHOD(gmagickdraw, setstrokemiterlimit)
{
	php_gmagickdraw_object *internd;
	zend_long miter_limit;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &miter_limit) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeMiterLimit(internd->drawing_wand, miter_limit);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::getStrokeAntialias()
	Returns the current stroke antialias setting. Stroked outlines are antialiased by default.  When antialiasing is disabled stroked pixels are thresholded to determine if the stroke color or underlying canvas color should be used.
*/
PHP_METHOD(gmagickdraw, getstrokeantialias)
{
	php_gmagickdraw_object *internd;
	MagickBool status;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	status = DrawGetStrokeAntialias(internd->drawing_wand);

	if (status == MagickFalse) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}
/* }}} */

/* {{{ proto float GmagickDraw::getStrokeDashOffset()
	Returns the offset into the dash pattern to start the dash.
*/
PHP_METHOD(gmagickdraw, getstrokedashoffset)
{
	php_gmagickdraw_object *internd;
	double offset;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	offset = DrawGetStrokeDashOffset(internd->drawing_wand);

	RETVAL_DOUBLE(offset);
}
/* }}} */

/* {{{ proto int GmagickDraw::getStrokeLineCap()
	Returns the shape to be used at the end of open subpaths when they are stroked. Values of LineCap are UndefinedCap, ButtCap, RoundCap, and SquareCap.
*/
PHP_METHOD(gmagickdraw, getstrokelinecap)
{
	php_gmagickdraw_object *internd;
	long line_cap;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	line_cap = DrawGetStrokeLineCap(internd->drawing_wand);

	RETVAL_LONG(line_cap);
}
/* }}} */

/* {{{ proto int GmagickDraw::getStrokeLineJoin()
	Returns the shape to be used at the corners of paths (or other vector shapes) when they are stroked. Values of LineJoin are UndefinedJoin, MiterJoin, RoundJoin, and BevelJoin.
*/
PHP_METHOD(gmagickdraw, getstrokelinejoin)
{
	php_gmagickdraw_object *internd;
	long line_join;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	line_join = DrawGetStrokeLineJoin(internd->drawing_wand);

	RETVAL_LONG(line_join);
}
/* }}} */

/* {{{ proto int GmagickDraw::getStrokeMiterLimit()
	Returns the miter limit. When two line segments meet at a sharp angle and miter joins have been specified for 'lineJoin', it is possible for the miter to extend far beyond the thickness of the line stroking the path. The miterLimit' imposes a limit on the ratio of the miter length to the 'lineWidth'.
*/
PHP_METHOD(gmagickdraw, getstrokemiterlimit)
{
	php_gmagickdraw_object *internd;
	unsigned long miter_limit;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	miter_limit = DrawGetStrokeMiterLimit(internd->drawing_wand);

	RETVAL_LONG(miter_limit);
}
/* }}} */


#if GMAGICK_LIB_MASK >= 1003000 
/* {{{ proto array GmagickDraw::getStrokeDashArray()
	Returns an array representing the pattern of dashes and gaps used to stroke paths (see DrawSetStrokeDashArray). The array must be freed once it is no longer required by the user.
*/
PHP_METHOD(gmagickdraw, getstrokedasharray)
{
	php_gmagickdraw_object *internd;
	double *stroke_array;
	unsigned long num_elements, i;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	stroke_array = DrawGetStrokeDashArray(internd->drawing_wand, &num_elements);
	array_init(return_value);

	for (i = 0; i < num_elements ; i++) {
		add_next_index_double(return_value, stroke_array[i]);
	}

	GMAGICK_FREE_MEMORY(double *, stroke_array);
	return;
}
/* }}} */

/* {{{ proto bool GmagickDraw::setStrokeDashArray(array dashArray)
	Specifies the pattern of dashes and gaps used to stroke paths. The strokeDashArray represents an array of numbers that specify the lengths of alternating dashes and gaps in pixels. If an odd number of values is provided, then the list of values is repeated to yield an even number of values. To remove an existing dash array, pass a zero number_elements argument and null dash_array. A typical strokeDashArray_ array might contain the members 5 3 2.
*/
PHP_METHOD(gmagickdraw, setstrokedasharray)
{
	zval *param_array;
	double *double_array;
	long elements;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &param_array) == FAILURE) {
		return;
	}

	double_array = php_gmagick_zval_to_double_array(param_array, &elements TSRMLS_CC);

	if (!double_array) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Cannot read stroke dash array parameter", 2);		
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetStrokeDashArray(internd->drawing_wand, elements, double_array);
	efree(double_array);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

#endif //GMAGICK_LIB_MASK >= 1003000


/* {{{ proto GmagickDraw GmagickDraw::circle(float ox, float oy, float px, float py)
	Draws a circle on the image.
*/
PHP_METHOD(gmagickdraw, circle)
{
	double ox, oy, px, py;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &ox, &oy, &px, &py) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawCircle(internd->drawing_wand, ox, oy, px, py);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

	
/* {{{ proto string GmagickDraw::getClipPath()
	Obtains the current clipping path ID. The value returned must be deallocated by the user when it is no longer needed.
*/
PHP_METHOD(gmagickdraw, getclippath)
{
	php_gmagickdraw_object *internd;
	char *clip_path;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	clip_path = DrawGetClipPath(internd->drawing_wand);

	if (!clip_path) {
		RETURN_FALSE;
	} else {
		ZVAL_STRING(return_value, clip_path);
		MagickRelinquishMemory(clip_path);
		return;
	}
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setClipPath(string clip_mask)
	Associates a named clipping path with the image.  Only the areas drawn on by the clipping path will be modified as long as it remains in effect.
*/
PHP_METHOD(gmagickdraw, setclippath)
{
	php_gmagickdraw_object *internd;
	char *clip_mask;
	size_t clip_mask_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &clip_mask, &clip_mask_len) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawSetClipPath(internd->drawing_wand, clip_mask);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int GmagickDraw::getClipRule()
	Returns the current polygon fill rule to be used by the clipping path.
*/
PHP_METHOD(gmagickdraw, getcliprule)
{
	php_gmagickdraw_object *internd;
	long clip_rule;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	clip_rule = DrawGetClipRule(internd->drawing_wand);

	RETVAL_LONG(clip_rule);
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setClipRule(int fill_rule)
	Set the polygon fill rule to be used by the clipping path.
*/
PHP_METHOD(gmagickdraw, setcliprule)
{
	php_gmagickdraw_object *internd;
	zend_long fill_rule;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &fill_rule) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetClipRule(internd->drawing_wand, fill_rule);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int GmagickDraw::getClipUnits()
	Returns the interpretation of clip path units.
*/
PHP_METHOD(gmagickdraw, getclipunits)
{
	php_gmagickdraw_object *internd;
	long units;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	units = DrawGetClipUnits(internd->drawing_wand);

	RETVAL_LONG(units);
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setClipUnits(int clip_units)
	Sets the interpretation of clip path units.
*/
PHP_METHOD(gmagickdraw, setclipunits)
{	
	php_gmagickdraw_object *internd;
	zend_long units;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &units) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetClipUnits(internd->drawing_wand, units);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::color(float x, float y, int paintMethod)
	Draws color on image using the current fill color, starting at specified position, and using specified paint method. The available paint methods are:
*/
PHP_METHOD(gmagickdraw, color)
{
	php_gmagickdraw_object *internd;
	double x, y;
	long paint_method;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddl", &x, &y, &paint_method) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawColor(internd->drawing_wand, x, y, paint_method);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::comment(string comment)
	Adds a comment to a vector output stream.
*/
PHP_METHOD(gmagickdraw, comment)
{
	php_gmagickdraw_object *internd;
	char *comment;
	size_t comment_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &comment, &comment_len) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawComment(internd->drawing_wand, comment);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setFillPatternURL(string fill_url)
	Sets the URL to use as a fill pattern for filling objects. Only local URLs ("#identifier") are supported at this time.
	These local URLs are normally created by defining a named fill pattern with DrawPushPattern/DrawPopPattern.
*/
PHP_METHOD(gmagickdraw, setfillpatternurl)
{
	php_gmagickdraw_object *internd;
	char *url;
	size_t url_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &url, &url_len) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawSetFillPatternURL(internd->drawing_wand, url);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int GmagickDraw::getFillRule(const DrawingWand *wand)
	Returns the fill rule used while drawing polygons.
*/
PHP_METHOD(gmagickdraw, getfillrule)
{
	php_gmagickdraw_object *internd;
	long fill_rule;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	fill_rule = DrawGetFillRule(internd->drawing_wand);

	RETVAL_LONG(fill_rule);
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::setFillRule(int fill_rule)
	Sets the fill rule to use while drawing polygons.
*/
PHP_METHOD(gmagickdraw, setfillrule)
{
	php_gmagickdraw_object *internd;
	zend_long fill_rule;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &fill_rule) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawSetFillRule(internd->drawing_wand, fill_rule);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto string GmagickDraw::getFontFamily()
	Returns the font family to use when annotating with text. The value returned must be freed by the user when it is no longer needed.
*/
PHP_METHOD(gmagickdraw, getfontfamily)
{
	php_gmagickdraw_object *internd;
	char *font_family;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	font_family = DrawGetFontFamily(internd->drawing_wand);
	if (!font_family) {
		RETURN_FALSE;
	} else {
		ZVAL_STRING(return_value, font_family);
		GMAGICK_FREE_MEMORY(char*, font_family);
		return;
	}
}
/* }}} */

static zend_bool php_gmagick_check_font(char *font, int font_len TSRMLS_DC)
{
	zend_bool retval = 0;
	char **fonts;
	unsigned long i = 0;
	size_t num_fonts = 0;

	/* Check that user is only able to set a proper font */
	fonts = MagickQueryFonts("*", &num_fonts);

	for(i = 0 ; i < num_fonts ; i++) {
		/* Let's see if the font is among configured fonts */
		if (strncasecmp(fonts[i], font, font_len) == 0) {
			retval = 1;
			break;
		}
	}

	GMAGICK_FREE_MEMORY(char**, fonts);

	return retval;
}


/* {{{ proto GmagickDraw GmagickDraw::setFontFamily(string font_family)
	Sets the font family to use when annotating with text.
*/
PHP_METHOD(gmagickdraw, setfontfamily)
{
	php_gmagickdraw_object *internd;
	char *font_family;
	size_t font_family_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &font_family, &font_family_len) == FAILURE) {
		return;
	}

	/* Check that no empty string is passed */
	if (font_family_len == 0) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Can not set empty font family", 2 TSRMLS_CC);
		return;
	}

	if (!php_gmagick_check_font(font_family, font_family_len TSRMLS_CC )) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Unable to set font family; parameter not found in the list of configured fonts", 2 TSRMLS_CC);
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawSetFontFamily(internd->drawing_wand, font_family);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto int GmagickDraw::getFontStretch(int fontStretch)
	Gets the font stretch to use when annotating with text
*/
PHP_METHOD(gmagickdraw, getfontstretch)
{
	php_gmagickdraw_object *internd;

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	RETVAL_LONG(DrawGetFontStretch(internd->drawing_wand));
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setFontStretch(int fontStretch)
	Sets the font stretch to use when annotating with text. The AnyStretch enumeration acts as a wild-card "don't care" option.
*/
PHP_METHOD(gmagickdraw, setfontstretch)
{
	php_gmagickdraw_object *internd;
	zend_long stretch;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &stretch) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawSetFontStretch(internd->drawing_wand, stretch);
	RETURN_TRUE;
}
/* }}} */

// TODO - DrawComposite expects an 'Image' not a 'MagickWand'. The image is in wand->image
// but that is internal to GraphicsMagick.
//
///* {{{ proto bool GmagickDraw::composite(int compose, float x, float y, float width, float height, MagickWand magick_wand)
//	Composites an image onto the current image, using the specified composition operator, specified position, and at the specified size.
//*/
// PHP_METHOD(gmagickdraw, composite)
// {
//	php_gmagickdraw_object *internd;
//	php_gmagick_object *other_image;
//	zval *magick_obj;
//	long compose;
//	double x, y, width, height;
//
//	/* Parse parameters given to function */
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lddddO", &compose, &x, &y, &width, &height, &magick_obj, php_gmagick_sc_entry) == FAILURE) {
//		return;
//	}
//
//	other_image = Z_GMAGICK_OBJ_P(magick_obj);
//
//	if (php_gmagick_ensure_not_empty(other_image->magick_wand) == 0)
//		return;
//
//	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
//	DrawComposite(internd->drawing_wand, compose, x, y, width, height, other_image->magick_wand->image);
//
//	RETURN_TRUE;

//	RETURN_FALSE;
//}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::pathClose()
	Adds a path element to the current path which closes the current subpath by drawing a straight line from the current point to the current subpath's most recent starting point (usually, the most recent moveto point).
*/
PHP_METHOD(gmagickdraw, pathclose)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPathClose(internd->drawing_wand);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToAbsolute(float x1, float y1, float x2, float y2, float x, float y)
	Draws a cubic Bezier curve from the current point to (x,y) using (x1,y1) as the control point at the beginning of the curve and (x2,y2) as the control point at the end of the curve using absolute coordinates. At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetoabsolute)
{
	php_gmagickdraw_object *internd;
	double x1, y1, x2, y2, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &x1, &y1, &x2, &y2, &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToAbsolute(internd->drawing_wand, x1, y1, x2, y2, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToRelative(float x1, float y1, float x2, float y2, float x, float y)
	Draws a cubic Bezier curve from the current point to (x,y) using (x1,y1) as the control point at the beginning of the curve and (x2,y2) as the control point at the end of the curve using relative coordinates. At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetorelative)
{
	php_gmagickdraw_object *internd;
	double x1, y1, x2, y2, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &x1, &y1, &x2, &y2, &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToRelative(internd->drawing_wand, x1, y1, x2, y2, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToQuadraticBezierAbsolute(float x1, float y1, float x, float y)
	Draws a quadratic Bezier curve from the current point to (x,y) using (x1,y1) as the control point using absolute coordinates. At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetoquadraticbezierabsolute)
{
	php_gmagickdraw_object *internd;
	double x1, y1, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x1, &y1, &x, &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToQuadraticBezierAbsolute(internd->drawing_wand, x1, y1, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToQuadraticBezierRelative(float x1, float y1, float x, float y)
	Draws a quadratic Bezier curve from the current point to (x,y) using (x1,y1) as the control point using relative coordinates. At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetoquadraticbezierrelative)
{
	php_gmagickdraw_object *internd;
	double x1, y1, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x1, &y1, &x, &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToQuadraticBezierRelative(internd->drawing_wand, x1, y1, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToQuadraticBezierSmoothAbsolute(float x, float y)
	Draws a quadratic Bezier curve (using relative coordinates) from the current point to (x,y). The control point is assumed to be the reflection of the control point on the previous command relative to the current point. (If there is no previous command or if the previous command was not a DrawPathCurveToQuadraticBezierAbsolute, DrawPathCurveToQuadraticBezierRelative, DrawPathCurveToQuadraticBezierSmoothAbsolut or DrawPathCurveToQuadraticBezierSmoothRelative, assume the control point is coincident with the current point.). At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetoquadraticbeziersmoothabsolute)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToQuadraticBezierSmoothAbsolute(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToQuadraticBezierSmoothRelative(float x, float y)
	Draws a quadratic Bezier curve (using relative coordinates) from the current point to (x, y). The control point is assumed to be the reflection of the control point on the previous command relative to the current point. (If there is no previous command or if the previous command was not a DrawPathCurveToQuadraticBezierAbsolute, DrawPathCurveToQuadraticBezierRelative, DrawPathCurveToQuadraticBezierSmoothAbsolut or DrawPathCurveToQuadraticBezierSmoothRelative, assume the control point is coincident with the current point). At the end of the command, the new current point becomes the final (x, y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetoquadraticbeziersmoothrelative)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToQuadraticBezierSmoothRelative(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToSmoothAbsolute(float x2, float y2, float x, float y)
	Draws a cubic Bezier curve from the current point to (x,y) using absolute coordinates. The first control point is assumed to be the reflection of the second control point on the previous command relative to the current point. (If there is no previous command or if the previous command was not an DrawPathCurveToAbsolute, DrawPathCurveToRelative, DrawPathCurveToSmoothAbsolute or DrawPathCurveToSmoothRelative, assume the first control point is coincident with the current point.) (x2,y2) is the second control point (i.e., the control point at the end of the curve). At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetosmoothabsolute)
{
	php_gmagickdraw_object *internd;
	double x1, y1, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x1, &y1, &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToSmoothAbsolute(internd->drawing_wand, x1, y1, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathCurveToSmoothRelative(float x2, float y2, float x, float y)
	Draws a cubic Bezier curve from the current point to (x,y) using relative coordinates. The first control point is assumed to be the reflection of the second control point on the previous command relative to the current point. (If there is no previous command or if the previous command was not an DrawPathCurveToAbsolute, DrawPathCurveToRelative, DrawPathCurveToSmoothAbsolute or DrawPathCurveToSmoothRelative, assume the first control point is coincident with the current point.) (x2,y2) is the second control point (i.e., the control point at the end of the curve). At the end of the command, the new current point becomes the final (x,y) coordinate pair used in the polybezier.
*/
PHP_METHOD(gmagickdraw, pathcurvetosmoothrelative)
{
	php_gmagickdraw_object *internd;
	double x1, y1, x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x1, &y1, &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathCurveToSmoothRelative(internd->drawing_wand, x1, y1, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathEllipticArcAbsolute(float rx, float ry, float x_axis_rotation, bool large_arc_flag, bool sweep_flag, float x, float y)
	Draws an elliptical arc from the current point to (x, y) using absolute coordinates. The size and orientation of the ellipse are defined by two radii (rx, ry) and an xAxisRotation, which indicates how the ellipse as a whole is rotated relative to the current coordinate system. The center (cx, cy) of the ellipse is calculated automatically to satisfy the constraints imposed by the other parameters. largeArcFlag and sweepFlag contribute to the automatic calculations and help determine how the arc is drawn. If largeArcFlag is true then draw the larger of the available arcs. If sweepFlag is true, then draw the arc matching a clock-wise rotation.
*/
PHP_METHOD(gmagickdraw, pathellipticarcabsolute)
{
	php_gmagickdraw_object *internd;
	double rx, ry, x_axis_rotation, x, y;
	zend_bool large_arc, sweep;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddbbdd", &rx, &ry, &x_axis_rotation, &large_arc, &sweep, &x, &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawPathEllipticArcAbsolute(internd->drawing_wand, rx, ry, x_axis_rotation, large_arc, sweep, x, y);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathEllipticArcRelative(float rx, float ry, float x_axis_rotation, bool large_arc_flag, bool sweep_flag, float x, float y)
	Draws an elliptical arc from the current point to (x, y) using relative coordinates. The size and orientation of the ellipse are defined by two radii (rx, ry) and an xAxisRotation, which indicates how the ellipse as a whole is rotated relative to the current coordinate system. The center (cx, cy) of the ellipse is calculated automatically to satisfy the constraints imposed by the other parameters. largeArcFlag and sweepFlag contribute to the automatic calculations and help determine how the arc is drawn. If largeArcFlag is true then draw the larger of the available arcs. If sweepFlag is true, then draw the arc matching a clock-wise rotation.
*/
PHP_METHOD(gmagickdraw, pathellipticarcrelative)
{
	php_gmagickdraw_object *internd;
	double rx, ry, x_axis_rotation, x, y;
	zend_bool large_arc, sweep;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddbbdd", &rx, &ry, &x_axis_rotation, &large_arc, &sweep, &x, &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawPathEllipticArcRelative(internd->drawing_wand, rx, ry, x_axis_rotation, large_arc, sweep, x, y);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::pathMoveToAbsolute(float x, float y)
	Starts a new sub-path at the given coordinate using absolute coordinates. The current point then becomes the specified coordinate.
*/
PHP_METHOD(gmagickdraw, pathmovetoabsolute)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathMoveToAbsolute(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathMoveToRelative(float x, float y)
	Starts a new sub-path at the given coordinate using relative coordinates. The current point then becomes the specified coordinate.
*/
PHP_METHOD(gmagickdraw, pathmovetorelative)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathMoveToRelative(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::pathLineToAbsolute(float x, float y)
	Draws a line path from the current point to the given coordinate using absolute coordinates. The coordinate then becomes the new current point.
*/
PHP_METHOD(gmagickdraw, pathlinetoabsolute)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathLineToAbsolute(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathLineToRelative(float x, float y)
	Draws a line path from the current point to the given coordinate using relative coordinates. The coordinate then becomes the new current point.
*/
PHP_METHOD(gmagickdraw, pathlinetorelative)
{
	php_gmagickdraw_object *internd;
	double x, y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathLineToRelative(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::pathLineToHorizontalAbsolute(float x)
	Draws a horizontal line path from the current point to the target point using absolute coordinates.  The target point then becomes the new current point.
*/
PHP_METHOD(gmagickdraw, pathlinetohorizontalabsolute)
{
	php_gmagickdraw_object *internd;
	double y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d",  &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathLineToHorizontalAbsolute(internd->drawing_wand, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathLineToHorizontalRelative(float x)
	Draws a horizontal line path from the current point to the target point using relative coordinates.  The target point then becomes the new current point.
*/
PHP_METHOD(gmagickdraw, pathlinetohorizontalrelative)
{
	php_gmagickdraw_object *internd;
	double x;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &x) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathLineToHorizontalRelative(internd->drawing_wand, x);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */



/* {{{ proto GmagickDraw GmagickDraw::pathLineToVerticalAbsolute(float y)
	Draws a vertical line path from the current point to the target point using absolute coordinates.  The target point then becomes the new current point.
*/
PHP_METHOD(gmagickdraw, pathlinetoverticalabsolute)
{
	php_gmagickdraw_object *internd;
	double y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathLineToVerticalAbsolute(internd->drawing_wand, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathLineToVerticalRelative(float y)
	Draws a vertical line path from the current point to the target point using relative coordinates.  The target point then becomes the new current point.
*/
PHP_METHOD(gmagickdraw, pathlinetoverticalrelative)
{
	php_gmagickdraw_object *internd;
	double y;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &y) == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPathLineToVerticalRelative(internd->drawing_wand, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */



/* {{{ proto GmagickDraw GmagickDraw::pathStart()
	Declares the start of a path drawing list which is terminated by a matching DrawPathFinish() command. All other DrawPath commands must be enclosed between a and a DrawPathFinish() command. This is because path drawing commands are subordinate commands and they do not function by themselves.
*/
PHP_METHOD(gmagickdraw, pathstart)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPathStart(internd->drawing_wand);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pathFinish()
	Terminates the current path.
*/  
PHP_METHOD(gmagickdraw, pathfinish)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPathFinish(internd->drawing_wand);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */



/* {{{ proto GmagickDraw GmagickDraw::popClipPath()
	Terminates a clip path definition.
*/
PHP_METHOD(gmagickdraw, popclippath)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPopClipPath(internd->drawing_wand);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::popDefs()
	Terminates a definition list
*/
PHP_METHOD(gmagickdraw, popdefs)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPopDefs(internd->drawing_wand);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::popPattern()
	Terminates a pattern definition.
*/
PHP_METHOD(gmagickdraw, poppattern)
{
	php_gmagickdraw_object *internd;


	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPopPattern(internd->drawing_wand);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pushClipPath(string clip_mask_id)
	Starts a clip path definition which is comprized of any number of drawing commands and terminated by a DrawPopClipPath() command.
*/
PHP_METHOD(gmagickdraw, pushclippath)
{
	php_gmagickdraw_object *internd;
	char *clip_mask;
	size_t clip_mask_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &clip_mask, &clip_mask_len) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPushClipPath(internd->drawing_wand, clip_mask);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pushDefs()
	Indicates that commands up to a terminating DrawPopDefs() command create named elements (e.g. clip-paths, textures, etc.) which may safely be processed earlier for the sake of efficiency.
*/
PHP_METHOD(gmagickdraw, pushdefs)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	
	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPushDefs(internd->drawing_wand);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::pushPattern(string pattern_id, float x, float y, float width, float height)
	Indicates that subsequent commands up to a DrawPopPattern() command comprise the definition of a named pattern. The pattern space is assigned top left corner coordinates, a width and height, and becomes its own drawing space.  Anything which can be drawn may be used in a pattern definition. Named patterns may be used as stroke or brush definitions.
*/
PHP_METHOD(gmagickdraw, pushpattern)
{	
	php_gmagickdraw_object *internd;
	char *pattern_id;
	size_t pattern_id_len;
	double x, y, width, height;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sdddd", &pattern_id, &pattern_id_len, &x, &y, &width, &height) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());

	DrawPushPattern(internd->drawing_wand, pattern_id, x, y, width, height);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::skewX(float degrees)
	Skews the current coordinate system in the horizontal direction.
*/
PHP_METHOD(gmagickdraw, skewx)
{
	double degrees;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &degrees) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawSkewX(internd->drawing_wand, degrees);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::skewY(float degrees)
	Skews the current coordinate system in the vertical direction.
*/
PHP_METHOD(gmagickdraw, skewy)
{
	double degrees;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &degrees) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawSkewY(internd->drawing_wand, degrees);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::setStrokePatternURL(string stroke_url)
	Sets the pattern used for stroking object outlines.
*/
PHP_METHOD(gmagickdraw, setstrokepatternurl)
{
	php_gmagickdraw_object *internd;
	char *url;
	size_t url_len;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &url, &url_len) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	DrawSetStrokePatternURL(internd->drawing_wand, url);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto bool GmagickDraw::getTextAntialias()
	Returns the current text antialias setting, which determines whether text is antialiased.  Text is antialiased by default.
*/
PHP_METHOD(gmagickdraw, gettextantialias)
{
	php_gmagickdraw_object *internd;
	unsigned int text_anti_alias;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());
	text_anti_alias = DrawGetTextAntialias(internd->drawing_wand);

	RETURN_BOOL(text_anti_alias);
}
/* }}} */


/* {{{ proto bool GmagickDraw::getAntialias()
	Returns the antialias property associated with the wand.
*/
PHP_METHOD(gmagickdraw, settextantialias)
{
	php_gmagickdraw_object *internd;
	zend_bool antialias;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &antialias) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawSetTextAntialias(internd->drawing_wand, antialias);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto ImagickPixel GmagickDraw::getTextUnderColor(PixelWand under_color)
	Returns the color of a background rectangle to place under text annotations.
*/
PHP_METHOD(gmagickdraw, gettextundercolor)
{
	php_gmagickpixel_object *internp;
	php_gmagickdraw_object *internd;
	PixelWand *tmp_wand;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	tmp_wand = NewPixelWand();

	if (!tmp_wand) {
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICKDRAW_CLASS, "Failed to allocate space for new PixelWand", 2 TSRMLS_CC);
		return;
	}

	DrawGetTextUnderColor(internd->drawing_wand, tmp_wand);

	object_init_ex(return_value, php_gmagickpixel_sc_entry);
	internp = Z_GMAGICKPIXEL_OBJ_P(return_value);
	GMAGICKPIXEL_REPLACE_PIXELWAND(internp, tmp_wand);

	return;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setTextUnderColor(PixelWand under_wand)
	Specifies the color of a background rectangle to place under text annotations.
*/
PHP_METHOD(gmagickdraw, settextundercolor)
{
	zval *param;
	php_gmagickdraw_object *internd;
	php_gmagickpixel_object *internp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, 1);

	DrawSetTextUnderColor(internd->drawing_wand, internp->pixel_wand);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */



/* {{{ proto GmagickDraw GmagickDraw::translate(float x, float y)
	Applies a translation to the current coordinate system which moves the coordinate system origin to the specified coordinate.
*/
PHP_METHOD(gmagickdraw, translate)
{
	double x, y;
	php_gmagickdraw_object *internd;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawTranslate(internd->drawing_wand, x, y);
	GMAGICK_CHAIN_METHOD;
}
/* }}} */

/* {{{ proto GmagickDraw GmagickDraw::setViewbox(float x1, float y1, float x2, float y2 )
	Sets the overall canvas size to be recorded with the drawing vector data. Usually this will be specified using the same size as the canvas image. When the vector data is saved to SVG or MVG formats, the viewbox is use to specify the size of the canvas image that a viewer will render the vector data on.
*/
PHP_METHOD(gmagickdraw, setviewbox)
{
	php_gmagickdraw_object *internd;
	zend_long x1, y1, x2, y2;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &x1, &y1, &x2, &y2) == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;

	DrawSetViewbox(internd->drawing_wand, x1, y1, x2, y2);
	GMAGICK_CHAIN_METHOD;
}

/* {{{ proto GmagickDraw GmagickDraw::popGraphicContext()
	Destroys the current DrawingWand in the stack, and returns to the previously pushed DrawingWand. Multiple DrawingWands may exist. It is an error to attempt to pop more DrawingWands than have been pushed, and it is proper form to pop all DrawingWands which have been pushed.
*/
PHP_METHOD(gmagickdraw, popGraphicContext)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPopGraphicContext(internd->drawing_wand);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */


/* {{{ proto GmagickDraw GmagickDraw::pushGraphicContext()
	Clones the current DrawingWand to create a new DrawingWand, which is then added to the DrawingWand stack. The original drawing DrawingWand(s) may be returned to by invoking PopDrawingWand(). The DrawingWands are stored on a DrawingWand stack. For every Pop there must have already been an equivalent Push.
*/
PHP_METHOD(gmagickdraw, pushGraphicContext)
{
	php_gmagickdraw_object *internd;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	internd = Z_GMAGICKDRAW_OBJ_P(getThis());;
	DrawPushGraphicContext(internd->drawing_wand);

	GMAGICK_CHAIN_METHOD;
}
/* }}} */

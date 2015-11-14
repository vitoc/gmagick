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

/* {{{ proto GmagickDraw GmagickDraw::annotation(float x, float y, string *text)
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
	long style_id = AnyStyle;

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
	long weight;

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
	long decoration;

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
	long gravity;

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
	long line_cap;

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
	long line_join;

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
	long miter_limit;

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

#endif

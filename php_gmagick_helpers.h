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

#ifndef PHP_GMAGICK_FUNCTIONS_H
# define PHP_GMAGICK_FUNCTIONS_H

/* {{{ void php_gmagick_initialize_constants() */
void php_gmagick_initialize_constants();
/* }}} */

/* {{{ get_pointinfo_array(zval *coordinate_array, int *num_elements TSRMLS_DC) */
void *get_pointinfo_array(zval *coordinate_array, int *num_elements TSRMLS_DC);
/* }}} */

/* {{{ check_configured_font(char *font, int font_len TSRMLS_DC ) */
int check_configured_font(char *font, int font_len TSRMLS_DC );

/* {{{ get_double_array_from_zval(zval *param_array, long *num_elements TSRMLS_DC) */
double *get_double_array_from_zval(zval *param_array, long *num_elements TSRMLS_DC);

/* {{{ count_occurences_of(char needle, char *haystack TSRMLS_DC)
*/
int count_occurences_of(char needle, char *haystack TSRMLS_DC);

/* {{{ zend_bool crop_thumbnail_image(MagickWand *magick_wand, long desired_width, long desired_height TSRMLS_DC)
*/
zend_bool crop_thumbnail_image(MagickWand *magick_wand, long desired_width, long desired_height, zend_bool legacy TSRMLS_DC);

/* {{{ zend_bool php_gmagick_thumbnail_dimensions(MagickWand *magick_wand, zend_bool bestfit, long desired_width, long desired_height, long *new_width, long *new_height)
*/
zend_bool php_gmagick_thumbnail_dimensions(MagickWand *magick_wand, zend_bool bestfit, long desired_width, long desired_height, long *new_width, long *new_height, zend_bool legacy);

/* {{{ zend_bool php_gmagick_ensure_not_empty (MagickWand *magick_wand) */
zend_bool php_gmagick_ensure_not_empty (MagickWand *magick_wand);

/* {{{ double *php_gmagick_zval_to_double_array(zval *param_array, long *num_elements TSRMLS_DC) */
double *php_gmagick_zval_to_double_array(zval *param_array, long *num_elements TSRMLS_DC);

#endif

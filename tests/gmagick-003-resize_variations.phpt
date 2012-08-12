--TEST--
Test resize
--SKIPIF--
<?php
/* $Id: gmagick-003-resize_variations.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick("magick:rose");
$gm->resizeImage(10, 10, 0.5, Gmagick::FILTER_LANCZOS);
$gm->resizeImage(10, 10, 0.5, Gmagick::FILTER_UNDEFINED, true);
$gm->resizeImage(10, 10, 0.5, Gmagick::FILTER_GAUSSIAN, false);
echo "ok";
?>
--EXPECTF--
ok
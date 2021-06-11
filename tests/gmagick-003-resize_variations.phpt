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
$gm->resizeImage(10, 10, Gmagick::FILTER_LANCZOS, 0.5);
$gm->resizeImage(10, 10, Gmagick::FILTER_UNDEFINED, 0.5, true);
$gm->resizeImage(10, 10, Gmagick::FILTER_GAUSSIAN, 0.5, false);
echo "ok";
?>
--EXPECTF--
ok

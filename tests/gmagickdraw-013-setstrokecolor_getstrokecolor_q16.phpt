--TEST--
Test setstrokecolor, getstrokecolor
--SKIPIF--
<?php
/* $Id: gmagickdraw-013-setstrokecolor_getstrokecolor.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 16) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
?>
--FILE--
<?php
$color = "rgb(255,255,255)";
$pixel = new GmagickPixel($color);
$gd = new GMagickDraw();
print_r($gd->setStrokeColor($pixel)->getStrokeColor()->getColor());
?>
--EXPECT--
rgb(65535,65535,65535)

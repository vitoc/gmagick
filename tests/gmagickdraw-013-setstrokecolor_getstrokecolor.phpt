--TEST--
Test setstrokecolor, getstrokecolor
--SKIPIF--
<?php
/* $Id: gmagickdraw-013-setstrokecolor_getstrokecolor.phpt 331869 2013-10-20 11:27:00Z remi $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 8) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
?>
--FILE--
<?php
$color = "rgb(255,255,255)";
$pixel = new GmagickPixel($color);
$gd = new GMagickDraw();
print_r($gd->setStrokeColor($pixel)->getStrokeColor()->getColor());
?>
--EXPECT--
rgb(255,255,255)

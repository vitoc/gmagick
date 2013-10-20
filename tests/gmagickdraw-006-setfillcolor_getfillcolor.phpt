--TEST--
Test setfillcolor, getfillcolor
--SKIPIF--
<?php
/* $Id: gmagickdraw-006-setfillcolor_getfillcolor.phpt 331869 2013-10-20 11:27:00Z remi $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 8) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
?>
--FILE--
<?php
$color = "rgb(255,255,255)";
$pixel = new GmagickPixel($color);
$gd = new GMagickDraw();
print_r($gd->setFillColor($pixel)->getFillColor()->getColor());
?>
--EXPECT--
rgb(255,255,255)

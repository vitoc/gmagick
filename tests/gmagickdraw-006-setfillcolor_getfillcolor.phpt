--TEST--
Test setfillcolor, getfillcolor
--SKIPIF--
<?php
/* $Id: gmagickdraw-006-setfillcolor_getfillcolor.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
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
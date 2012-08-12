--TEST--
Test setColorValue and getColorValue methods
--SKIPIF--
<?php
/* $Id: gmagickpixel-002-setcolorvalue_getcolorvalue.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gp = new GMagickPixel();
echo $gp->getColorValue(Gmagick::COLOR_BLACK). "\n";
$gp->setColorValue(Gmagick::COLOR_BLACK,1);
echo $gp->getColorValue(Gmagick::COLOR_BLACK). "\n";
?>
--EXPECTF--
0
1
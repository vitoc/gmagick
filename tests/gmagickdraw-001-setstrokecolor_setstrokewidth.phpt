--TEST--
Test set stroke color, set stroke width
--SKIPIF--
<?php
/* $Id: gmagickdraw-001-setstrokecolor_setstrokewidth.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$color = "rgb(255,255,123)";
$pixel = new GmagickPixel($color);
$gd = new GMagickDraw();
$gd->setStrokeColor($pixel)->setStrokeWidth(2);
echo "ok";
?>
--EXPECT--
ok
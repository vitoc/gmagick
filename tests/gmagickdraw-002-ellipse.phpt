--TEST--
Test ellipse
--SKIPIF--
<?php
/* $Id: gmagickdraw-002-ellipse.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$color = "rgb(255,255,255)";
$pixel = new GmagickPixel($color);
$gd = new GMagickDraw();
$gd->setFillColor($pixel)->ellipse( 200, 100, 50, 50, 0, 360 );
echo "ok";
?>
--EXPECT--
ok
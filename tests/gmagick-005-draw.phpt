--TEST--
Test read/write
--SKIPIF--
<?php
/* $Id: gmagick-005-draw.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$color = "rgb(255,255,123)";
$pixel = new GmagickPixel($color);
$gd = new GMagickDraw();
$gd->setStrokeColor($pixel)->setStrokeWidth( 2 )->setFillColor($pixel)->ellipse( 200, 100, 50, 50, 0, 360 );
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick("magick:rose");
$gm->drawImage($gd);
$gm->write($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok

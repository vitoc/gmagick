--TEST--
Test getColorcount method
--SKIPIF--
<?php
/* $Id: gmagickpixel-003-getcolorcount.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$color = "rgb(255,255,255)";
$pixel = new GmagickPixel($color);
echo $pixel->getColorCount();
?>
--EXPECTF--
0
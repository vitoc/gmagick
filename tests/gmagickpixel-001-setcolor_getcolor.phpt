--TEST--
Test setColor and getColor methods
--SKIPIF--
<?php
/* $Id: gmagickpixel-001-setcolor_getcolor.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$color = "rgb(255,255,255)";
$pixel = new GmagickPixel($color);
echo strcmp($color, $pixel->getColor()) . "\n";
var_dump($pixel->setColor($pixel->getColor()));
echo strcmp($color, $pixel->getColor()) . "\n";
?>
--EXPECTF--
0
object(GmagickPixel)#%d (%d) {
}
0
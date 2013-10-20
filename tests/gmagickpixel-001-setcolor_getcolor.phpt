--TEST--
Test setColor and getColor methods
--SKIPIF--
<?php
/* $Id: gmagickpixel-001-setcolor_getcolor.phpt 331869 2013-10-20 11:27:00Z remi $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 8) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
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

--TEST--
Imagebordercolor test
--SKIPIF--
<?php
/* $Id: gmagick-027-set_getimagebordercolor.phpt 331869 2013-10-20 11:27:00Z remi $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 8) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$color=new GmagickPixel("rgb(255,255,255)");
$pixel = $gm->setImageBorderColor($color)->getImageBorderColor();
print_r($pixel->getColor());
?>
--EXPECTF--
rgb(255,255,255)

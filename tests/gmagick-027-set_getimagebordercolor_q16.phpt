--TEST--
Imagebordercolor test
--SKIPIF--
<?php
/* $Id: gmagick-027-set_getimagebordercolor.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 16) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
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
rgb(65535,65535,65535)

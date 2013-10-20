--TEST--
Test setImageBackgroundColor and getImageBackgroundColor methods
--SKIPIF--
<?php
/* $Id: gmagick-025-set_and_getimageckgroundcolor.phpt 331869 2013-10-20 11:27:00Z remi $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH != 8) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$color=new GmagickPixel("rgb(255,255,255)");
$pixel =  $gm->setImageBackgroundColor($color)->getimagebackgroundcolor();
print_r($pixel->getColor());
?>
--EXPECTF--
rgb(255,255,255)

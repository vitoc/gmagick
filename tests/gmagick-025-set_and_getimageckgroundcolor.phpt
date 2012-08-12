--TEST--
Test setImageBackgroundColor and getImageBackgroundColor methods
--SKIPIF--
<?php
/* $Id: gmagick-025-set_and_getimageckgroundcolor.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
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
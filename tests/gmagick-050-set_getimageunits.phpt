--TEST--
Set, get imageunits
--SKIPIF--
<?php
/* $Id: gmagick-050-set_getimageunits.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageUnits(2)->getImageUnits();
?>
--EXPECTF--
2
--TEST--
Set, get image gamma
--SKIPIF--
<?php
/* $Id: gmagick-037-set_getimagegamma.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageGamma(0.2)->getImageGamma();
?>
--EXPECTF--
0.2
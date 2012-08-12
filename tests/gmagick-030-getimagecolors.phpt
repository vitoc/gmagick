--TEST--
Getimagecolors test
--SKIPIF--
<?php
/* $Id: gmagick-030-getimagecolors.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
print_r($gm->getImageColors());
?>
--EXPECTF--
3019
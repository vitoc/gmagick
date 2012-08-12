--TEST--
Set, get image interlace scheme
--SKIPIF--
<?php
/* $Id: gmagick-041-set_getimageinterlacescheme.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageInterlaceScheme(1)->getImageInterlaceScheme();
?>
--EXPECTF--
1
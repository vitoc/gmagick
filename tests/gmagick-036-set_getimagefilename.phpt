--TEST--
Set, get imagefilename
--SKIPIF--
<?php
/* $Id: gmagick-036-set_getimagefilename.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageFilename('magickrose.png')->getImageFilename();
?>
--EXPECTF--
magickrose.png
--TEST--
Set, get image height
--SKIPIF--
<?php
/* $Id: gmagick-039-getimageheight.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->getImageHeight();
?>
--EXPECTF--
46
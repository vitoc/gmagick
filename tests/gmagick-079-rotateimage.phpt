--TEST--
rotateImage test
--SKIPIF--
<?php
/* $Id: gmagick-079-rotateimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$color=new GmagickPixel("rgb(255,255,255)");
$gm->rotateImage($color, 0.8);
echo "ok";
?>
--EXPECTF--
ok
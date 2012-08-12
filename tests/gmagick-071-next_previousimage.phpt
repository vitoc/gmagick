--TEST--
next,previousImage test
--SKIPIF--
<?php
/* $Id: gmagick-071-next_previousimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->nextImage();
$gm->previousImage();
echo "ok";
?>
--EXPECTF--
ok

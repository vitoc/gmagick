--TEST--
motionblur test
--SKIPIF--
<?php
/* $Id: gmagick-070-motionblurimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->motionBlurImage(0.2, 0.2, 0.2);
echo "ok";
?>
--EXPECTF--
ok

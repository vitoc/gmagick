--TEST--
oilPaintImage test
--SKIPIF--
<?php
/* $Id: gmagick-072-oilpaintimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->oilPaintImage(0.2);
echo "ok";
?>
--EXPECTF--
ok

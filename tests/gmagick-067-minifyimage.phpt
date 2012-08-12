--TEST--
minifyImage test
--SKIPIF--
<?php
/* $Id: gmagick-067-minifyimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->minifyImage();
echo "ok";
?>
--EXPECTF--
ok

--TEST--
magnifyImage test
--SKIPIF--
<?php
/* $Id: gmagick-064-magnifyimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->magnifyImage();
echo "ok";
?>
--EXPECTF--
ok
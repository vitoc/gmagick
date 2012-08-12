--TEST--
implode image test
--SKIPIF--
<?php
/* $Id: gmagick-061-implodeimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->implodeImage(0.5);
echo "ok";
?>
--EXPECTF--
ok

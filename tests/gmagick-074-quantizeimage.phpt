--TEST--
quantizeImage test
--SKIPIF--
<?php
/* $Id: gmagick-074-quantizeimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->quantizeImage(2, 2, 2, true, true);
echo "ok";
?>
--EXPECTF--
ok

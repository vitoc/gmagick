--TEST--
quantizeImages test
--SKIPIF--
<?php
/* $Id: gmagick-075-quantizeimages.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->quantizeImages(2, 2, 2, true, true);
echo "ok";
?>
--EXPECTF--
ok

--TEST--
spreadImage test
--SKIPIF--
<?php
/* $Id: gmagick-084-spreadimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->spreadImage(0.2);
echo "ok";
?>
--EXPECTF--
ok
--TEST--
Emboss
--SKIPIF--
<?php
/* $Id: gmagick-019-embossimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->embossImage(0.8, 0.5);
echo "ok";
?>
--EXPECTF--
ok
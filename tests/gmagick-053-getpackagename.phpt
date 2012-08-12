--TEST--
get packagename
--SKIPIF--
<?php
/* $Id: gmagick-053-getpackagename.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->getPackageName();
?>
--EXPECTF--
GraphicsMagick
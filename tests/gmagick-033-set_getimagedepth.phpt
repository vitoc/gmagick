--TEST--
Set, getimagedepth
--SKIPIF--
<?php
/* $Id: gmagick-033-set_getimagedepth.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageDepth(2)->getImageDepth();
?>
--EXPECTF--
2
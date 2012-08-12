--TEST--
Set, getimagedepth
--SKIPIF--
<?php
/* $Id: gmagick-034-set_getimagedispose.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageDispose(2)->getImageDispose();
?>
--EXPECTF--
2
--TEST--
Set, get imagetype
--SKIPIF--
<?php
/* $Id: gmagick-049-set_getimagetype.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageType(6)->getImageType();
?>
--EXPECTF--
6
--TEST--
Set, get imagechanneldepth test
--SKIPIF--
<?php
/* $Id: gmagick-028-set_getimagechanneldepth.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageChannelDepth(1,1)->getImageChannelDepth(1);
?>
--EXPECTF--
1
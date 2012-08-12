--TEST--
Set, getimagedelay test 
--SKIPIF--
<?php
/* $Id: gmagick-032-set_getimagedelay.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageDelay(2)->getImageDelay();
?>
--EXPECTF--
2
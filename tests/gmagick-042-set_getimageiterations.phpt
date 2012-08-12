--TEST--
Set, get image iterations
--SKIPIF--
<?php
/* $Id: gmagick-042-set_getimageiterations.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageIterations(2)->getImageIterations();
?>
--EXPECTF--
2
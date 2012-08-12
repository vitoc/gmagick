--TEST--
Set, get imagescene
--SKIPIF--
<?php
/* $Id: gmagick-047-set_getimagescene.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageScene(1)->getImageScene();
?>
--EXPECTF--
1
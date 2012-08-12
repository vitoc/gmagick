--TEST--
Set and get image compose
--SKIPIF--
<?php
/* $Id: gmagick-031-set_getimagecompose.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageCompose(1)->getImageCompose();
?>
--EXPECTF--
1
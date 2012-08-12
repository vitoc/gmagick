--TEST--
Set, get imageprofile
--SKIPIF--
<?php
/* $Id: gmagick-043-set_getimageprofile.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageProfile("test", "test_profile")->getImageProfile("test");
?>
--EXPECTF--
test_profile
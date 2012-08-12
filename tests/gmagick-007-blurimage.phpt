--TEST--
Test blur image
--SKIPIF--
<?php
/* $Id: gmagick-007-blurimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick();
$gm->read("magick:rose");
$gm->blurImage(5, 3);
$gm->writeImage($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok
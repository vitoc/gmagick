--TEST--
Test chop image
--SKIPIF--
<?php
/* $Id: gmagick-012-chopimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm->read("magick:rose");
$gm->chopImage(10, 10, 0, 0);
$gm->write($filename);
echo "ok";
?>
--EXPECTF--
ok
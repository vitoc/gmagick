--TEST--
Test read/write
--SKIPIF--
<?php
/* $Id: gmagick-001-read_and_write.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new Gmagick();
$gm->readImage("magick:rose")->writeImage($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok

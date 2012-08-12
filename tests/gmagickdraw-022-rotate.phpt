--TEST--
Test rotate
--SKIPIF--
<?php
/* $Id: gmagickdraw-022-rotate.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");
$gd->rectangle(20,20,30,30);
$gd->rotate(45);
$gm->drawImage($gd);
$gm->write($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok
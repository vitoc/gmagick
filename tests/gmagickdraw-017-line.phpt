--TEST--
Test line
--SKIPIF--
<?php
/* $Id: gmagickdraw-017-line.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");
$gd->line(8, 8, 18, 18);
$gm->drawImage($gd);
$gm->write($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok
--TEST--
Test annotate
--SKIPIF--
<?php
/* $Id: gmagickdraw-003-annotate.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");//->write($filename);
$gd->annotate(10, 20, "Test Text");
$gm->drawImage($gd);
$gm->write($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok
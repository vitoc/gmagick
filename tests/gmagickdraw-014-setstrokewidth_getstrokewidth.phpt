--TEST--
Test setstrokewidth, getstrokewidth
--SKIPIF--
<?php
/* $Id: gmagickdraw-014-setstrokewidth_getstrokewidth.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setStrokeWidth(2)->getStrokeWidth();
?>
--EXPECT--
2
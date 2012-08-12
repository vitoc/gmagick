--TEST--
Test setstrokeopacity, getstrokeopacity
--SKIPIF--
<?php
/* $Id: gmagickdraw-012-setstrokeopacity_getstrokeopacity.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setStrokeOpacity(0.8)->getStrokeOpacity();
?>
--EXPECT--
0.8
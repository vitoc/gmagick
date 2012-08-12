--TEST--
Test setfillopacity, getfillopacity
--SKIPIF--
<?php
/* $Id: gmagickdraw-007-setfillopacity_getfillopacity.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
$gd->setFillOpacity(0.8);
echo $gd->getFillOpacity();
?>
--EXPECT--
0.2
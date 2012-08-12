--TEST--
Test setfontweight, getfontweight
--SKIPIF--
<?php
/* $Id: gmagickdraw-011-setfontweight_getfontweight.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setFontWeight(101)->getFontWeight();
?>
--EXPECT--
101
--TEST--
Test setfontsize, getfontsize
--SKIPIF--
<?php
/* $Id: gmagickdraw-009-setfontsize_getfontsize.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setFontSize(1)->getFontSize();
?>
--EXPECT--
1
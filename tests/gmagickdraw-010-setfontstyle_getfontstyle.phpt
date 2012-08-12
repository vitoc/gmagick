--TEST--
Test setfontstyle, getfontstyle
--SKIPIF--
<?php
/* $Id: gmagickdraw-010-setfontstyle_getfontstyle.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setFontStyle(Gmagick::STYLE_NORMAL)->getFontStyle();
?>
--EXPECT--
0
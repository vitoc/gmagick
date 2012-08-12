--TEST--
Test setfont, getfont
--SKIPIF--
<?php
/* $Id: gmagickdraw-008-setfont_getfont.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo strstr($gd->setFont(dirname(__FILE__) . "/Vera.ttf")->getFont(),"Vera.ttf");
?>
--EXPECT--
Vera.ttf
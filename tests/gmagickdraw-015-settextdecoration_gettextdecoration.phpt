--TEST--
Test settextdecoration, gettextdecoration
--SKIPIF--
<?php
/* $Id: gmagickdraw-015-settextdecoration_gettextdecoration.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setTextDecoration(Gmagick::DECORATION_UNDERLINE)->getTextDecoration();
?>
--EXPECT--
1
--TEST--
Test settextencoding, gettextencoding
--SKIPIF--
<?php
/* $Id: gmagickdraw-016-settextencoding_gettextencoding.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gd = new GMagickDraw();
echo $gd->setTextEncoding("UTF-8")->getTextEncoding();
?>
--EXPECT--
UTF-8
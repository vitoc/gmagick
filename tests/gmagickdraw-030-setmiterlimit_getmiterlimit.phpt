--TEST--
Test get and set strokeMiterLimit
--SKIPIF--
<?php
/* $Id: gmagickdraw30-setmiterlimit_getmiterlimit.phpt 280206 2013-11-05 12:46:00Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
	$gDraw = new GmagickDraw();
	$gDraw->setStrokeMiterLimit(2);
	echo $gDraw->getStrokeMiterLimit();
?>
--EXPECT--
2

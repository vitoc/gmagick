--TEST--
Test set and get line cap
--SKIPIF--
<?php
/* $Id: gmagickdraw-028-setlinecap_getlinecap.phpt 280206 2013-11-05 12:46:00Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
	$gDraw = new GmagickDraw();
	$gDraw->setStrokeLineCap(2);
	echo $gDraw->getStrokeLineCap();
?>
--EXPECT--
2

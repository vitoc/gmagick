--TEST--
Test stroke line join
--SKIPIF--
<?php
/* $Id: gmagickdraw-0229-setlinejoin_getlinejoin.phpt 280206 2013-11-05 12:46:00Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
	$gDraw = new GmagickDraw();
	$gDraw->setStrokeLineJoin(2);
	echo $gDraw->getStrokeLineJoin();
?>
--EXPECT--
2

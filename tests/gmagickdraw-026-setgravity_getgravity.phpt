--TEST--
Test affine
--SKIPIF--
<?php
/* $Id: gmagickdraw-025-affine.phpt 280206 2010-08-07 12:46:00Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
    $gDraw = new GmagickDraw();
    $gDraw->setGravity(2);
	echo $gDraw->getGravity();
?>
--EXPECT--
2

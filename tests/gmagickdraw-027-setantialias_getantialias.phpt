--TEST--
Test and get anti-alias
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
	$gDraw = new GmagickDraw();
	$gDraw->setStrokeAntiAlias(true);
	echo $gDraw->getStrokeAntiAlias();
?>
--EXPECT--
1

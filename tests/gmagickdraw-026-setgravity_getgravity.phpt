--TEST--
Test affine
--SKIPIF--
<?php
/* $Id: gmagickdraw-025-affine.phpt 280206 2010-08-07 12:46:00Z vito $ */
require_once(dirname(__FILE__) . '/skipif.inc');

checkClassMethods(
    'GmagickDraw',
    array('setGravity', 'getGravity')
);
?>
--FILE--
<?php
    $gDraw = new GmagickDraw();
    $gDraw->setGravity(2);
	echo $gDraw->getGravity();
?>
--EXPECT--
2

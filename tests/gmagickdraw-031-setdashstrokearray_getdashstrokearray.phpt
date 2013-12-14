--TEST--
Test set and get stroke dash array
--SKIPIF--
<?php
/* $Id: gmagickdraw-031-setdashstrokearray_getdashstrokearray.phpt 280206 2013-12-14 18:04:00Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
    $gDraw = new GmagickDraw();
    $gDraw->setStrokeDashArray(array(3, 2));
    print_R($gDraw->getStrokeDashArray());
?>
--EXPECT--
Array
(
    [0] => 3
    [1] => 2
)
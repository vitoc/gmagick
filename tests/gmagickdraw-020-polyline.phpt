--TEST--
Test polyline
--SKIPIF--
<?php
/* $Id: gmagickdraw-020-polyline.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php

$intPoints = array(
    array( 'x' => 3, 'y' => 4 ), 
    array( 'x' => 2, 'y' => 6 ),
    array( 'x' => 5, 'y' => 10 ),
    array( 'x' => 3, 'y' => 4 )
);

$floatPoints = array(
    array( 'x' => 3.5, 'y' => 4.5 ), 
    array( 'x' => 2.5, 'y' => 6.5 ),
    array( 'x' => 5.5, 'y' => 10.5 ),
    array( 'x' => 3.5, 'y' => 4.5 )
);

$tests = array(
    $intPoints,
    $floatPoints
);

foreach ($tests as $polArray) {
    $filename = dirname(__FILE__) . '/test_constructor.jpg';
    $gm = new GMagick();
    $gd = new GMagickDraw();
    $gm->read("magick:rose");  
    $gd->polyline($polArray);
    $gm->drawImage($gd);
    $gm->write($filename);
    unlink($filename);
    echo "ok".PHP_EOL;
}
?>
--EXPECT--
ok
ok
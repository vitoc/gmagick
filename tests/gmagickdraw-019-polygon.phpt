--TEST--
Test polygon
--SKIPIF--
<?php
/* $Id: gmagickdraw-019-polygon.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");
$polArray = array( array( 'x' => 3, 'y' => 4 ), array( 'x' => 2, 'y' => 6 ) ,array( 'x' => 5, 'y' => 10 ), array( 'x' => 3, 'y' => 4 ));
$gd->polygon($polArray);
$gm->drawImage($gd);
$gm->write($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok
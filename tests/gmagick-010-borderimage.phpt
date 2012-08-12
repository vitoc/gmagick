--TEST--
Test border image
--SKIPIF--
<?php
/* $Id: gmagick-010-borderimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm->read("magick:rose");
$color=new GmagickPixel("rgb(255,255,255)");
$gm->borderImage($color,3,3);
$gm->write($filename);
echo "ok";
?>
--EXPECT--
ok
--TEST--
Test charcoal image
--SKIPIF--
<?php
/* $Id: gmagick-011-charcoalimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm->read("magick:rose");
$gm->charcoalImage(3,3);
$gm->write($filename);
echo "ok";
?>
--EXPECT--
ok
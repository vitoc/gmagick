--TEST--
Flip and flop image
--SKIPIF--
<?php
/* $Id: gmagick-022-flip_and_flop_image.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->flipImage()->flopImage();
echo "1";
?>
--EXPECTF--
1
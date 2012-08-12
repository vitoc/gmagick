--TEST--
Test addnoiseimage image
--SKIPIF--
<?php
/* $Id: gmagick-009-addimagenoise.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new GMagick();
$gm->read("magick:rose");
$gm->addNoiseImage(Gmagick::COLOR_BLACK);
echo "ok";
?>
--EXPECT--
ok
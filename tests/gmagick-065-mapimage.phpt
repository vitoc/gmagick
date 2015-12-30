--TEST--
mapImage test
--SKIPIF--
<?php
/* $Id: gmagick-065-mapimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
if (Gmagick::QUANTUM_DEPTH == 8) die('skip QUANTUM_DEPTH='.Gmagick::QUANTUM_DEPTH);
?>
--FILE--
<?php
$gm = new Gmagick();
$gm2 = new Gmagick();
$gm->read("magick:rose");
$gm2->read("magick:rose");
$gm->mapImage($gm2, true);
echo "ok";
?>
--EXPECTF--
ok

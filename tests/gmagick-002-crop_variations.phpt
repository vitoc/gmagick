--TEST--
Test crop with and without an image
--SKIPIF--
<?php
/* $Id: gmagick-002-crop_variations.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose")->cropImage(10, 10, 10, 10);
echo "ok\n--\n";
$gm = new Gmagick();
try {
	$gm->cropImage(10, 10, 10, 10);
} catch (GmagickException $e) {
	echo "got exception";
}
?>
--EXPECTF--
ok
--
got exception
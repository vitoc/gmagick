--TEST--
Test composite variations
--SKIPIF--
<?php
/* $Id: gmagick-004-composite_variations.phpt 294865 2010-02-10 23:50:11Z mkoppanen $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick("magick:rose");
$source = new Gmagick();

try {
	$gm->compositeImage($source, Gmagick::COMPOSITE_OVER, 0, 0);
} catch (Exception $e) {
	echo "got exception\n";
}

$source->read("magick:rose");
$gm->compositeImage($source, Gmagick::COMPOSITE_OVER, 0, 0);

echo "ok";
?>
--EXPECTF--
got exception
ok
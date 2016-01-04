--TEST--
Test contants have symbols.
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$reflClass = new ReflectionClass('Gmagick');
// This just checks that the symbols that Gmagick was compiled with
// are actually present.
$constants = $reflClass->getConstants();

echo "ok";
?>
--EXPECTF--
ok
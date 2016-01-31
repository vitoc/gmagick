--TEST--
Test static methods
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$gmagick = new Gmagick ();

//echo gettype (Gmagick::queryFormats ()) . PHP_EOL;
echo gettype ($gmagick->queryFormats ()) . PHP_EOL;

//echo gettype (Gmagick::queryFonts ()) . PHP_EOL;
echo gettype ($gmagick->queryFonts ()) . PHP_EOL;

echo 'success';

?>
--EXPECT--
array
array
success
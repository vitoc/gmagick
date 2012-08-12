--TEST--
negateImage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->negateImage(TRUE);
echo "ok";
?>
--EXPECTF--
ok

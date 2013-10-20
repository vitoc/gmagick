--TEST--
unsharpmaskimage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->unsharpMaskImage(0 , 0.5 , 1 , 0.05);
echo "ok";
?>
--EXPECTF--
ok

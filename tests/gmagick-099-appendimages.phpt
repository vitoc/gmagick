--TEST--
appendimages test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->newImage(100, 50, "blue");
$image->appendImages();
echo "ok";
?>
--EXPECTF--
ok

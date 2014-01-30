--TEST--
setImageCompression test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->setImageCompression(Gmagick::COMPRESSION_JPEG);
echo $image->getImageCompression();
?>
--EXPECTF--
5
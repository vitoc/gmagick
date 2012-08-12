--TEST--
setInterlaceScheme test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->setInterlaceScheme(Gmagick::INTERLACE_LINE);
echo "ok";
?>
--EXPECTF--
ok

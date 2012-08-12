--TEST--
sampleimage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->sampleimage(5, 5);
echo "ok";
?>
--EXPECTF--
ok

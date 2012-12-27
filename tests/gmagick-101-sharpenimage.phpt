--TEST--
sharpenmage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->sharpenImage(1.5, 1.2);
echo "ok";
?>
--EXPECTF--
ok

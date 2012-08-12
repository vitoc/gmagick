--TEST--
setImage test
--SKIPIF--
<?php
/* $Id: gmagick-086-setcompressionquality.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
print_r($image->getImageGeometry());
?>
--EXPECTF--
Array
(
    [width] => 70
    [height] => 46
)

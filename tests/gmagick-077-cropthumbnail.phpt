--TEST--
cropthumbnail test
--SKIPIF--
<?php
/* $Id: gmagick-077-cropthumbnail.phpt 280549 2009-05-14 21:45:39Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->cropThumbnailImage(3, 3);
echo "ok";
?>
--EXPECTF--
ok

--TEST--
Test add image
--SKIPIF--
<?php
/* $Id: gmagick-008-addimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new GMagick();
$image = new GMagick();
$image->read("magick:rose");
$gm->addImage($image);
echo "ok";
?>
--EXPECT--
ok
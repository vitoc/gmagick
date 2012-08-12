--TEST--
Destroy
--SKIPIF--
<?php
/* $Id: gmagick-017-destroy.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->destroy();
echo "ok";
?>
--EXPECTF--
ok
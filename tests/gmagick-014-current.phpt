--TEST--
Test current
--SKIPIF--
<?php
/* $Id: gmagick-014-current.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm2 = $gm->current();
echo "ok";
?>
--EXPECTF--
ok
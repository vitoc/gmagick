--TEST--
profileImage test
--SKIPIF--
<?php
/* $Id: gmagick-073-profileimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->profileImage('icc', 'test_icc_profile');
echo "ok";
?>
--EXPECTF--
ok

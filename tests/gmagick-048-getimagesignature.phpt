--TEST--
Set, get imagesignature
--SKIPIF--
<?php
/* $Id: gmagick-048-getimagesignature.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->getImageSignature();
?>
--EXPECTF--
8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f
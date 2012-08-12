--TEST--
Gamma image
--SKIPIF--
<?php
/* $Id: gmagick-023-gammaimage.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->gammaImage(0.8);
echo "1";
?>
--EXPECTF--
1
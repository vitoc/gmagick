--TEST--
Set, get imageblueprimary test
--SKIPIF--
<?php
/* $Id: gmagick-026-set_getimageblueprimary.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
print_r($gm->setImageBluePrimary(0.2, 0.2)->getImageBluePrimary());
?>
--EXPECTF--
Array
(
    [x] => 0.2
    [y] => 0.2
)
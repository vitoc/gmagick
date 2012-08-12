--TEST--
Set, get imageredprimary
--SKIPIF--
<?php
/* $Id: gmagick-044-set_getimageredprimary.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
print_r($gm->setImageRedPrimary(0.2, 0.2)->getImageRedPrimary());
?>
--EXPECTF--
Array
(
    [x] => 0.2
    [y] => 0.2
)
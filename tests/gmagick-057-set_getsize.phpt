--TEST--
set,get size test
--SKIPIF--
<?php
/* $Id: gmagick-057-set_getsize.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
print_r($gm->setSize(20, 20)->getSize());
?>
--EXPECTF--
Array
(
    [columns] => 20
    [rows] => 20
)
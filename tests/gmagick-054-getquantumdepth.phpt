--TEST--
get quantumdepth
--SKIPIF--
<?php
/* $Id: gmagick-054-getquantumdepth.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
print_r($gm->getQuantumDepth());
?>
--EXPECTF--
Array
(
    [quantumDepthLong] => 8
    [quantumDepthString] => Q8
)
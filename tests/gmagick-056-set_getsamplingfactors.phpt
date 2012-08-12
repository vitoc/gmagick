--TEST--
Set, getsamplingfactors
--SKIPIF--
<?php
/* $Id: gmagick-056-set_getsamplingfactors.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$samples = array(1, 2);
print_r($gm->setSamplingFactors($samples)->getSamplingFactors());
?>
--EXPECTF--
Array
(
    [0] => 1
    [1] => 2
)
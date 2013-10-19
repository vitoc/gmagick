--TEST--
get quantumdepth
--SKIPIF--
<?php
/* $Id: gmagick-054-getquantumdepth.phpt 331865 2013-10-19 09:28:23Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$q=$gm->getQuantumDepth();
if (is_array($q) && count($q)==2 && isset($q['quantumDepthLong']) && isset($q['quantumDepthString'])) {
   echo "Struct OK\n";
   if ($q['quantumDepthLong']=='8' && $q['quantumDepthString']=='Q8') {
       echo "Quantum OK\n";
   } else if ($q['quantumDepthLong']=='16' && $q['quantumDepthString']=='Q16') {
       echo "Quantum OK\n";
   } else {
       echo "Quantum KO\n";
       print_r($q);
   }
} else {
   echo "Struct KO\n";
   print_r($q);
}
?>
--EXPECTF--
Struct OK
Quantum OK